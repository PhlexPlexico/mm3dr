#include "rnd/gfx.h"

namespace rnd {
  static u8 GfxInit = 0;
  static u32 closingButton = 0;
  static u8 currentSphere = 0;
  static s16 spoilerScroll = 0;

  static s16 allItemsScroll = 0;
  static s16 groupItemsScroll = 0;
  static s8 currentItemGroup = 1;

  static s32 curMenuIdx = 0;
  static bool showingLegend = false;
  static u64 lastTick = 0;
  static u64 ticksElapsed = 0;
  static bool isAsleep = false;
  DungeonInfo rDungeonInfoData[10];

  u32 pressed;
  bool handledInput;
  const char* spoilerCollectionGroupNames[] = {
      "All Item Locations", "South Clock Town", "Laundry Pool",       "East Clock Town",       "StockPotInn",
      "West Clock Town",    "North Clock Town", "Termina Field",      "Southern Swamp",        "Deku Palace",
      "Woodfall",           "Snowhead",         "Mountain Village",   "Twin Islands",          "Goron Village",
      "Milk Road",          "Romani Ranch",     "Great Bay Coast",    "Pinnacle Rock",         "Zora Cape",
      "Zora Hall",          "Ikana Canyon",     "Ikana Graveyard",    "Stone Tower",           "Woodfall Temple",
      "Snowhead Temple",    "Great Bay Temple", "Stone Tower Temple", "Pirate Fortress",       "Beneath the Well",
      "Ikana Castle",       "Secret Shrine",    "The Moon",           "Swamp Skulltula House", "Ocean Skulltula House",
  };

  static s8 spoilerGroupDungeonIds[] = {
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      -1,
      GROUP_DUNGEON_WOODFALL_TEMPLE,
      GROUP_DUNGEON_SNOWHEAD_TEMPLE,
      GROUP_DUNGEON_GREAT_BAY,
      GROUP_DUNGEON_STONE_TOWER,
      GROUP_DUNGEON_PIRATE_FORTRESS,
      GROUP_DUNGEON_BENEATH_THE_WELL,
      GROUP_DUNGEON_IKANA_CASTLE,
      GROUP_DUNGEON_SECRET_SHRINE,
      GROUP_DUNGEON_THE_MOON,
      GROUP_SWAMP_SKULLTULA_HOUSE,
      GROUP_OCEAN_SKULLTULA_HOUSE,
  };

  static bool IsDungeonDiscovered(s8 dungeonId) {
    game::SaveData& saveData = game::GetCommonData().save;
    if (dungeonId == DUNGEON_THE_MOON) {
      return false;
    }

    u8 idToModeKnown[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    if (idToModeKnown[dungeonId]) {
      return true;
    }

    // A dungeon is considered discovered if we've visited the dungeon, have the map,
    // Or known bc of settings
    bool hasMap = 0;
    if (dungeonId == 0) {
      hasMap = saveData.inventory.woodfall_dungeon_items.map.Value();
    } else if (dungeonId == 1) {
      hasMap = saveData.inventory.snowhead_dungeon_items.map.Value();
    } else if (dungeonId == 2) {
      hasMap = saveData.inventory.great_bay_dungeon_items.map.Value();
    } else if (dungeonId == 3) {
      hasMap = saveData.inventory.stone_tower_dungeon_items.map.Value();
    }
    return (hasMap = 1);  // to-do: check overworld map for GB & Ikana areas for other dungeons. & scene check.
  }

  static bool CanShowSpoilerGroup(SpoilerCollectionCheckGroup group) {
    s8 dungeonId = spoilerGroupDungeonIds[group];
    return dungeonId == -1 || IsDungeonDiscovered(dungeonId);
  }

  static void Gfx_DrawScrollBar(u16 barX, u16 barY, u16 barSize, u16 currentScroll, u16 maxScroll, u16 pageSize) {
    Draw_DrawRect(barX, barY, SCROLL_BAR_THICKNESS, barSize, COLOR_SCROLL_BAR_BG);

    float thumbSizePercent = pageSize / (float)maxScroll;
    if (thumbSizePercent > 1.0f) {
      thumbSizePercent = 1.0f;
    }
    u16 thumbSize = (u16)(thumbSizePercent * barSize);
    if (thumbSize < SCROLL_BAR_MIN_THUMB_SIZE) {
      thumbSize = SCROLL_BAR_MIN_THUMB_SIZE;
    }
    float barThumbPosPercent = (float)currentScroll / (float)(maxScroll - pageSize);
    u16 barThumbPosY = (u16)(barThumbPosPercent * (barSize - thumbSize));
    Draw_DrawRect(barX, barY + barThumbPosY, SCROLL_BAR_THICKNESS, thumbSize, COLOR_WHITE);
  }

  static void NextItemGroup() {
    groupItemsScroll = 0;
    s8 prevGroup = currentItemGroup;
    do {
      ++currentItemGroup;
      if (currentItemGroup >= SPOILER_COLLECTION_GROUP_COUNT) {
        currentItemGroup = 1;
      }
    } while (gSpoilerData.GroupItemCounts[currentItemGroup] == 0 && currentItemGroup != prevGroup);
  }

  static void PrevItemGroup() {
    groupItemsScroll = 0;
    s8 prevGroup = currentItemGroup;
    do {
      --currentItemGroup;
      if (currentItemGroup < 1) {
        currentItemGroup = SPOILER_COLLECTION_GROUP_COUNT - 1;
      }
    } while (gSpoilerData.GroupItemCounts[currentItemGroup] == 0 && currentItemGroup != prevGroup);
  }

  static void Gfx_DrawButtonPrompts(void) {
    u32 promptY = SCREEN_BOT_HEIGHT - 16;
    u32 textY = promptY - 1;
    // Close prompt, always shown
    Draw_DrawIcon(SCREEN_BOT_WIDTH - 50, promptY, COLOR_BUTTON_B, ICON_BUTTON_B);
    Draw_DrawString(SCREEN_BOT_WIDTH - 38, textY, COLOR_TITLE, "Close");

    static const u8 buttonSpacing = 12;
    u16 offsetX = 10;
    const char* nextStr = NULL;

    if (curMenuIdx == PAGE_DUNGEONITEMS) {
      Draw_DrawIcon(offsetX, promptY, COLOR_BUTTON_A, ICON_BUTTON_A);
      offsetX += buttonSpacing;
      Draw_DrawString(offsetX, textY, COLOR_TITLE, "Toggle Legend");
    } else if (curMenuIdx == PAGE_SPHERES) {
      Draw_DrawIcon(offsetX, promptY, COLOR_WHITE, ICON_BUTTON_DPAD);
      offsetX += buttonSpacing;
      Draw_DrawString(offsetX, textY, COLOR_TITLE, "Browse spoiler log");
    } else if (curMenuIdx == PAGE_ITEMTRACKER_ALL || curMenuIdx == PAGE_ITEMTRACKER_GROUPS ||
               curMenuIdx == PAGE_ENTRANCETRACKER_ALL || curMenuIdx == PAGE_ENTRANCETRACKER_GROUPS) {
      Draw_DrawIcon(offsetX, promptY, COLOR_WHITE, ICON_BUTTON_DPAD);
      offsetX += buttonSpacing;
      nextStr = "Browse entries";
      Draw_DrawString(offsetX, textY, COLOR_TITLE, nextStr);
      offsetX += (strlen(nextStr) + 1) * SPACING_X;
      if (curMenuIdx == PAGE_ITEMTRACKER_GROUPS || curMenuIdx == PAGE_ENTRANCETRACKER_GROUPS) {
        Draw_DrawIcon(offsetX, promptY, COLOR_BUTTON_Y, ICON_BUTTON_Y);
        offsetX += 8;
        Draw_DrawString(offsetX, textY, COLOR_TITLE, "/");
        offsetX += 8;
        Draw_DrawIcon(offsetX, promptY, COLOR_BUTTON_A, ICON_BUTTON_A);
        offsetX += buttonSpacing;
        nextStr = "Change group";
        Draw_DrawString(offsetX, textY, COLOR_TITLE, nextStr);
        offsetX += (strlen(nextStr) + 1) * SPACING_X;
      } else if (curMenuIdx == PAGE_ITEMTRACKER_ALL || curMenuIdx == PAGE_ENTRANCETRACKER_ALL) {
        Draw_DrawIcon(offsetX, promptY, COLOR_BUTTON_A, ICON_BUTTON_A);
        offsetX += buttonSpacing;
        nextStr = "Toggle Legend";
        Draw_DrawString(offsetX, textY, COLOR_TITLE, nextStr);
        offsetX += (strlen(nextStr) + 1) * SPACING_X;
      }
    }
  }

  static void Gfx_UpdatePlayTime(void) {
    u64 currentTick = svcGetSystemTick();
    if (!isAsleep) {
      ticksElapsed += currentTick - lastTick;
      if (ticksElapsed > MAX_TICK_DELTA) {
        // Assume that if more ticks than MAX_TICK_DELTA have passed, it has been a long
        // time since we last checked, which means the the system may have been asleep or the home button pressed.
        // Reset the timer so we don't artificially inflate the play time.
        ticksElapsed = 0;
      } else {
        while (ticksElapsed >= TICKS_PER_SEC) {
          ticksElapsed -= TICKS_PER_SEC;
          ++gExtSaveData.playtimeSeconds;
        }
      }
    }
    lastTick = currentTick;
  }

  static void Gfx_DrawSeedHash(void) {
    u8 offsetY = 0;
    Draw_DrawFormattedString(10, 16 + (SPACING_Y * offsetY++), COLOR_TITLE, "Seed Hash:");
    for (u32 hashIndex = 0; hashIndex < ARR_SIZE(gSettingsContext.hashIndexes); ++hashIndex) {
      Draw_DrawFormattedString(10 + (SPACING_X * 4), 16 + (SPACING_Y * offsetY++), COLOR_WHITE, "%s",
                               hashIconNames[gSettingsContext.hashIndexes[hashIndex]]);
    }
    offsetY++;

    Draw_DrawString(10, 16 + (SPACING_Y * offsetY++), COLOR_TITLE, "Play time:");
    u32 hours = gExtSaveData.playtimeSeconds / 3600;
    u32 minutes = (gExtSaveData.playtimeSeconds / 60) % 60;
    u32 seconds = gExtSaveData.playtimeSeconds % 60;
    Draw_DrawFormattedString(10 + (SPACING_X * 4), 16 + (SPACING_Y * offsetY++), COLOR_WHITE, "%02u:%02u:%02u", hours,
                             minutes, seconds);
    offsetY++;
  }

  static void Gfx_DrawDungeonItems(void) {
    static const u8 spacingY = 13;
    game::SaveData& saveData = game::GetCommonData().save;
    if (showingLegend) {
      u8 offsetY = 0;

      Draw_DrawString(10, 16 + (spacingY * offsetY++), COLOR_TITLE, "Dungeon Items Legend");
      offsetY++;
      Draw_DrawIcon(10, 16 + (spacingY * offsetY), COLOR_WHITE, ICON_SMALL_KEY);
      Draw_DrawString(24, 16 + (spacingY * offsetY++), COLOR_WHITE, "Small Keys: Have / Found");
      Draw_DrawIcon(10, 16 + (spacingY * offsetY), COLOR_ICON_BOSS_KEY, ICON_BOSS_KEY);
      Draw_DrawString(24, 16 + (spacingY * offsetY++), COLOR_WHITE, "Boss Key");
      Draw_DrawIcon(10, 16 + (spacingY * offsetY), COLOR_ICON_MAP, ICON_MAP);
      Draw_DrawString(24, 16 + (spacingY * offsetY++), COLOR_WHITE, "Map");
      Draw_DrawIcon(10, 16 + (spacingY * offsetY), COLOR_ICON_COMPASS, ICON_COMPASS);
      Draw_DrawString(24, 16 + (spacingY * offsetY++), COLOR_WHITE, "Compass");
      offsetY++;
      Draw_DrawIcon(10, 16 + (spacingY * offsetY), COLOR_ICON_WOTH, ICON_TRIFORCE);
      Draw_DrawString(24, 16 + (spacingY * offsetY++), COLOR_WHITE, "Way of the Hero");
      Draw_DrawIcon(10, 16 + (spacingY * offsetY), COLOR_ICON_FOOL, ICON_FOOL);
      Draw_DrawString(24, 16 + (spacingY * offsetY++), COLOR_WHITE, "Barren Location");
      Draw_DrawString(10, 16 + (spacingY * offsetY), COLOR_WHITE, "-");
      Draw_DrawString(24, 16 + (spacingY * offsetY++), COLOR_WHITE, "Non-WotH / Non-Barren Location");
      return;
    }
    Draw_DrawString(10, 16, COLOR_TITLE, "Dungeon Items");
    // Draw header icons
    Draw_DrawIcon(214, 16, COLOR_WHITE, ICON_SMALL_KEY);
    Draw_DrawIcon(240, 16, COLOR_WHITE, ICON_BOSS_KEY);
    Draw_DrawIcon(260, 16, COLOR_WHITE, ICON_MAP);
    Draw_DrawIcon(280, 16, COLOR_WHITE, ICON_COMPASS);
    if (gSettingsContext.compassesShowWotH) {
      Draw_DrawIcon(300, 16, COLOR_WHITE, ICON_TRIFORCE);
    }

    u8 yPos = 30;
    for (u32 dungeonId = 0; dungeonId <= DUNGEON_STONE_TOWER; ++dungeonId) {
      bool hasBossKey = 0;
      if ((dungeonId == DUNGEON_WOODFALL)) {
        hasBossKey = saveData.inventory.woodfall_dungeon_items.boss_key.Value();
      }
      if ((dungeonId == DUNGEON_SNOWHEAD)) {
        hasBossKey = saveData.inventory.snowhead_dungeon_items.boss_key.Value();
      }
      if ((dungeonId == DUNGEON_GREAT_BAY)) {
        hasBossKey = saveData.inventory.great_bay_dungeon_items.boss_key.Value();
      }
      if ((dungeonId == DUNGEON_STONE_TOWER)) {
        hasBossKey = saveData.inventory.stone_tower_dungeon_items.boss_key.Value();
      }
      bool hasCompass = 0;
      if ((dungeonId == DUNGEON_WOODFALL)) {
        hasCompass = saveData.inventory.woodfall_dungeon_items.compass.Value();
      }
      if ((dungeonId == DUNGEON_SNOWHEAD)) {
        hasCompass = saveData.inventory.snowhead_dungeon_items.compass.Value();
      }
      if ((dungeonId == DUNGEON_GREAT_BAY)) {
        hasCompass = saveData.inventory.great_bay_dungeon_items.compass.Value();
      }
      if ((dungeonId == DUNGEON_STONE_TOWER)) {
        hasCompass = saveData.inventory.stone_tower_dungeon_items.compass.Value();
      }
      bool hasMap = 0;
      if ((dungeonId == DUNGEON_WOODFALL)) {
        hasMap = saveData.inventory.woodfall_dungeon_items.map.Value();
      }
      if ((dungeonId == DUNGEON_SNOWHEAD)) {
        hasMap = saveData.inventory.snowhead_dungeon_items.map.Value();
      }
      if ((dungeonId == DUNGEON_GREAT_BAY)) {
        hasMap = saveData.inventory.great_bay_dungeon_items.map.Value();
      }
      if ((dungeonId == DUNGEON_STONE_TOWER)) {
        hasMap = saveData.inventory.stone_tower_dungeon_items.map.Value();
      }

      Draw_DrawString(24, yPos, COLOR_WHITE, DungeonNames[dungeonId]);

      // Small Keys
      if (dungeonId <= DUNGEON_STONE_TOWER) {
        u8 keysHave = 0;
        if ((dungeonId == DUNGEON_WOODFALL)) {
          keysHave = saveData.inventory.woodfall_temple_keys == 255 ? 0 : saveData.inventory.woodfall_temple_keys;
        }
        if ((dungeonId == DUNGEON_SNOWHEAD)) {
          keysHave = saveData.inventory.snowhead_temple_keys == 255 ? 0 : saveData.inventory.snowhead_temple_keys;
        }
        if ((dungeonId == DUNGEON_GREAT_BAY)) {
          keysHave = saveData.inventory.great_bay_temple_keys == 255 ? 0 : saveData.inventory.great_bay_temple_keys;
        }
        if ((dungeonId == DUNGEON_STONE_TOWER)) {
          keysHave = saveData.inventory.stone_tower_temple_keys == 255 ? 0 : saveData.inventory.stone_tower_temple_keys;
        }
        Draw_DrawFormattedString(208, yPos, keysHave > 0 ? COLOR_WHITE : COLOR_DARK_GRAY, "%d", keysHave);
        Draw_DrawString(214, yPos, COLOR_WHITE, "/");

        u8 keysFound = Dungeon_FoundSmallKeys(dungeonId);
        if ((gSettingsContext.keysanity == u8(rnd::KeysanitySetting::KEYSANITY_START_WITH)) &&
            (dungeonId <= DUNGEON_STONE_TOWER)) {
          keysFound += Dungeon_KeyAmount(dungeonId);
        }
        u32 keysFoundColor = COLOR_WHITE;
        if (keysFound >= Dungeon_KeyAmount(dungeonId) || IsDungeonDiscovered(dungeonId)) {
          keysFoundColor = COLOR_GREEN;
        } else if (keysFound == 0) {
          keysFoundColor = COLOR_DARK_GRAY;
        }
        Draw_DrawFormattedString(220, yPos, keysFoundColor, "%d", keysFound);
      }

      // Boss Key
      if ((dungeonId <= DUNGEON_STONE_TOWER)) {
        Draw_DrawIcon(240, yPos, hasBossKey ? COLOR_ICON_BOSS_KEY : COLOR_DARK_GRAY, ICON_BOSS_KEY);
      }

      // Map and Compasses
      if (dungeonId <= DUNGEON_STONE_TOWER) {
        Draw_DrawIcon(260, yPos, hasMap ? COLOR_ICON_MAP : COLOR_DARK_GRAY, ICON_MAP);
        Draw_DrawIcon(280, yPos, hasCompass ? COLOR_ICON_COMPASS : COLOR_DARK_GRAY, ICON_COMPASS);

        // Way of the Hero
        if (gSettingsContext.compassesShowWotH) {
          if (hasCompass) {
            if (rDungeonInfoData[dungeonId] == DUNGEON_WOTH) {
              Draw_DrawIcon(300, yPos, COLOR_ICON_WOTH, ICON_TRIFORCE);
            } else if (rDungeonInfoData[dungeonId] == DUNGEON_BARREN) {
              Draw_DrawIcon(300, yPos, COLOR_ICON_FOOL, ICON_FOOL);
            } else {
              Draw_DrawCharacter(300, yPos, COLOR_WHITE, '-');
            }
          } else {
            Draw_DrawCharacter(300, yPos, COLOR_DARK_GRAY, '?');
          }
        }
      }

      yPos += spacingY;
    }
  }

  static void Gfx_DrawSpoilerData(void) {
    if (gSpoilerData.SphereCount > 0) {
      u16 itemCount = gSpoilerData.Spheres[currentSphere].ItemCount;

      Draw_DrawFormattedString(10, 16, COLOR_TITLE, "Spoiler Log - Sphere %i / %i", currentSphere + 1,
                               gSpoilerData.SphereCount);

      u16 sphereItemLocOffset = gSpoilerData.Spheres[currentSphere].ItemLocationsOffset;
      u16 listTopY = 32;
      for (u32 item = 0; item < MAX_ENTRY_LINES; ++item) {
        u32 locIndex = item + spoilerScroll;
        if (locIndex >= gSpoilerData.Spheres[currentSphere].ItemCount) {
          break;
        }

        u32 locPosY = listTopY + ((SPACING_SMALL_Y + 1) * item * 2);
        u32 itemPosY = locPosY + SPACING_SMALL_Y;
        u16 itemIndex = gSpoilerData.SphereItemLocations[sphereItemLocOffset + locIndex];
        u32 color = COLOR_WHITE;
        if (SpoilerData_GetIsItemLocationCollected(itemIndex)) {
          if (SpoilerData_CollectType(itemIndex) == COLLECTTYPE_REPEATABLE) {
            color = COLOR_BLUE;
          } else if (SpoilerData_CollectType(itemIndex) == COLLECTTYPE_NEVER) {
            color = COLOR_ORANGE;
          } else {
            color = COLOR_GREEN;
          }
        }
        Draw_DrawString_Small(10, locPosY, color, SpoilerData_GetItemLocationString(itemIndex));
        Draw_DrawString_Small(10 + (SPACING_SMALL_X * 2), itemPosY, color, SpoilerData_GetItemNameString(itemIndex));
      }

      Gfx_DrawScrollBar(SCREEN_BOT_WIDTH - 3, listTopY, SCREEN_BOT_HEIGHT - 40 - listTopY, spoilerScroll, itemCount,
                        MAX_ENTRY_LINES);
    } else {
      Draw_DrawString(10, 16, COLOR_TITLE, "Spoiler Log");
      Draw_DrawString(10, 46, COLOR_WHITE, "No spoiler log generated!");
    }
  }

  static u8 ViewingGroups() {
    return curMenuIdx == PAGE_ITEMTRACKER_GROUPS || curMenuIdx == PAGE_ENTRANCETRACKER_GROUPS;
  }

  static void Gfx_DrawItemTracker(void) {
    if (!ViewingGroups() && showingLegend) {
      Draw_DrawString(10, 16, COLOR_TITLE, "Item Color Legend");

      static const u8 squareWidth = 9;
      u16 offsetY = 2;
      Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_GREEN);
      Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Collected");
      Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_BLUE);
      Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Repeatable");
      Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_ORANGE);
      Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Uncollectable");
      return;
    }
    if (ViewingGroups() && !CanShowSpoilerGroup(SpoilerCollectionCheckGroup(currentItemGroup))) {
      Draw_DrawString(10, 16, COLOR_TITLE, spoilerCollectionGroupNames[currentItemGroup]);
      Draw_DrawString(10, 46, COLOR_WHITE, "Reveal this dungeon to see the item list.");
      Draw_DrawString(10, 57, COLOR_WHITE, " - Enter the dungeon at least once");

      return;
    }

    u16 itemCount = ViewingGroups() ? gSpoilerData.GroupItemCounts[currentItemGroup] : gSpoilerData.ItemLocationsCount;
    u16 startIndex = ViewingGroups() ? gSpoilerData.GroupOffsets[currentItemGroup] : 0;
    s16* itemScroll = ViewingGroups() ? &groupItemsScroll : &allItemsScroll;

    // Gather up completed items to calculate how far along this group is
    u16 completeItems = 0;
    u16 uncollectableItems = 0;
    for (u32 i = 0; i < itemCount; ++i) {
      u32 locIndex = i + startIndex;
      if (SpoilerData_GetIsItemLocationCollected(locIndex)) {
        completeItems++;
      } else if (SpoilerData_ItemLoc(locIndex)->CollectType == COLLECTTYPE_NEVER ||
                 (SpoilerData_ItemLoc(locIndex)->CollectType == COLLECTTYPE_REPEATABLE &&
                  SpoilerData_GetIsItemLocationRevealed(locIndex))) {
        uncollectableItems++;
      }
    }
    u16 collectableItems = itemCount - uncollectableItems;
    float groupPercent = ((float)completeItems / (float)collectableItems) * 100.0f;
    Draw_DrawFormattedString(SCREEN_BOT_WIDTH - 10 - (SPACING_X * 6), 16,
                             completeItems == collectableItems ? COLOR_GREEN : COLOR_WHITE, "%5.1f%%", groupPercent);

    u16 firstItem = *itemScroll + 1;
    u16 lastItem = *itemScroll + MAX_ENTRY_LINES;
    if (lastItem > itemCount) {
      lastItem = itemCount;
    }
    Draw_DrawFormattedString(10, 16, COLOR_TITLE, "%s - (%d - %d) / %d",
                             spoilerCollectionGroupNames[ViewingGroups() ? currentItemGroup : 0], firstItem, lastItem,
                             itemCount);

    u16 listTopY = 32;
    u32 itemGroupIndex = 1;  // Keep the last picked group index around to start the search from
    for (u32 item = 0; item < MAX_ENTRY_LINES; ++item) {
      u32 locIndex = item + startIndex + *itemScroll;
      if (item >= itemCount) {
        break;
      }

      u32 locPosY = listTopY + ((SPACING_SMALL_Y + 1) * item * 2);
      u32 itemPosY = locPosY + SPACING_SMALL_Y;
      bool isCollected = SpoilerData_GetIsItemLocationCollected(locIndex);

      // Find this item's group index, so we can see if we should hide
      // its name because it's located in an undiscovered dungeon
      for (u32 group = itemGroupIndex; group < SPOILER_COLLECTION_GROUP_COUNT; ++group) {
        u16 groupOffset = gSpoilerData.GroupOffsets[group];
        if (locIndex >= groupOffset && locIndex < groupOffset + gSpoilerData.GroupItemCounts[group]) {
          itemGroupIndex = group;
          break;
        }
      }
      bool canShowGroup = isCollected || CanShowSpoilerGroup(SpoilerCollectionCheckGroup(itemGroupIndex));

      u32 color = COLOR_WHITE;

      if (isCollected) {
        if (SpoilerData_CollectType(locIndex) == COLLECTTYPE_REPEATABLE) {
          color = COLOR_BLUE;
        } else if (SpoilerData_CollectType(locIndex) == COLLECTTYPE_NEVER) {
          color = COLOR_ORANGE;
        } else {
          color = COLOR_GREEN;
        }
      }

      bool itemRevealed = canShowGroup && (isCollected || SpoilerData_GetIsItemLocationRevealed(locIndex));

      if (canShowGroup) {
        Draw_DrawString_Small(10, locPosY, color, SpoilerData_GetItemLocationString(locIndex));
      } else {
        Draw_DrawFormattedString_Small(10, locPosY, color, "%s (Undiscovered)",
                                       spoilerCollectionGroupNames[itemGroupIndex]);
      }
      const char* itemText = itemRevealed ? SpoilerData_GetItemNameString(locIndex) : "???";
      Draw_DrawString_Small(10 + (SPACING_SMALL_X * 2), itemPosY, color, itemText);
    }

    Gfx_DrawScrollBar(SCREEN_BOT_WIDTH - 3, listTopY, SCREEN_BOT_HEIGHT - 40 - listTopY, *itemScroll, itemCount,
                      MAX_ENTRY_LINES);
  }

  static void (*menu_draw_funcs[])(void) = {
      // Make sure these line up with the GfxPage enum above
      Gfx_DrawSeedHash,    Gfx_DrawDungeonItems, Gfx_DrawSpoilerData,
      Gfx_DrawItemTracker,  // All
      Gfx_DrawItemTracker,  // Groups
                            // Gfx_DrawEntranceTracker, // All
                            // Gfx_DrawEntranceTracker, // Groups
                            // Gfx_DrawOptions,
  };

  static void Gfx_DrawHeader() {
    const u32 totalTabsWidth = 280;
    u32 tabsCount = ARR_SIZE(menu_draw_funcs);
    u32 tabWidthPlusSpace = totalTabsWidth / tabsCount;
    u32 tabXStart = 20;
    u32 tabYStart = 3;
    u32 tabHeightSmall = 4;
    u32 tabHeightBig = 6;

    Draw_DrawIcon(3, 2, COLOR_WHITE, ICON_BUTTON_L_WIDE_1);
    Draw_DrawIcon(11, 2, COLOR_WHITE, ICON_BUTTON_L_WIDE_2);
    Draw_DrawIcon(SCREEN_BOT_WIDTH - 19, 2, COLOR_WHITE, ICON_BUTTON_R_WIDE_1);
    Draw_DrawIcon(SCREEN_BOT_WIDTH - 11, 2, COLOR_WHITE, ICON_BUTTON_R_WIDE_2);

    for (u32 i = 0; i < tabsCount; i++) {
      bool isAvailable = menu_draw_funcs[i] != NULL;
      bool isCurrent = static_cast<u32>(curMenuIdx) == i;
      u32 tabX = (u32)(i * tabWidthPlusSpace);
      Draw_DrawRect(tabXStart + tabX, isCurrent ? tabYStart : tabYStart + 2,
                    i == tabsCount - 1 ? totalTabsWidth - tabX : (tabWidthPlusSpace - 1),
                    isCurrent ? tabHeightBig : tabHeightSmall,
                    isCurrent ? COLOR_WHITE : (isAvailable ? COLOR_LIGHT_GRAY : COLOR_DARK_GRAY));
    }
  }

  static s16 Gfx_Scroll(s16 current, s16 scrollDelta, u16 itemCount) {
    s16 maxScroll = itemCount > MAX_ENTRY_LINES ? itemCount - MAX_ENTRY_LINES : 0;
    current += scrollDelta;
    if (current < 0) {
      current = 0;
    } else if (current > maxScroll) {
      current = maxScroll;
    }
    return current;
  }

  static void Gfx_ShowMenu(void) {
    pressed = 0;
    Draw_ClearFramebuffer();
    if (gSettingsContext.playOption == PLAY_ON_CONSOLE) {
      Draw_FlushFramebuffer();
    }
    do {
      // End the loop if the system has gone to sleep, so the game can properly respond
      if (isAsleep) {
        break;
      }

      handledInput = false;
      // Controls for spoiler log and all-items pages come first, as the user may have chosen
      // one of the directional buttons as their menu open/close button and we need to use them
      if (curMenuIdx == PAGE_DUNGEONITEMS) {
        if (pressed & BUTTON_A) {
          showingLegend = !showingLegend;
          handledInput = true;
        }
      } else if (curMenuIdx == PAGE_SPHERES && gSpoilerData.SphereCount > 0) {
        // Spoiler log
        u16 itemCount = gSpoilerData.Spheres[currentSphere].ItemCount;
        if (pressed & (BUTTON_LEFT | CPAD_LEFT)) {
          if (currentSphere == 0) {
            currentSphere = gSpoilerData.SphereCount - 1;
          } else {
            currentSphere--;
          }
          spoilerScroll = 0;
          handledInput = true;
        } else if (pressed & (BUTTON_RIGHT | CPAD_RIGHT)) {
          if (currentSphere < gSpoilerData.SphereCount - 1) {
            currentSphere++;
          } else {
            currentSphere = 0;
          }
          spoilerScroll = 0;
          handledInput = true;
        } else if (pressed & (BUTTON_UP | CPAD_UP)) {
          spoilerScroll = Gfx_Scroll(spoilerScroll, -1, itemCount);
          handledInput = true;
        } else if (pressed & (BUTTON_DOWN | CPAD_DOWN)) {
          spoilerScroll = Gfx_Scroll(spoilerScroll, 1, itemCount);
          handledInput = true;
        }
      } else if (curMenuIdx == PAGE_ITEMTRACKER_ALL && gSpoilerData.ItemLocationsCount > 0) {
        // All Items list
        if (pressed & BUTTON_A) {
          showingLegend = !showingLegend;
          handledInput = true;
        } else if (!showingLegend) {
          u16 itemCount = gSpoilerData.ItemLocationsCount;
          if (pressed & (BUTTON_LEFT | CPAD_LEFT)) {
            allItemsScroll = Gfx_Scroll(allItemsScroll, -MAX_ENTRY_LINES * 10, itemCount);
            handledInput = true;
          } else if (pressed & (BUTTON_RIGHT | CPAD_RIGHT)) {
            allItemsScroll = Gfx_Scroll(allItemsScroll, MAX_ENTRY_LINES * 10, itemCount);
            handledInput = true;
          } else if (pressed & (BUTTON_UP | CPAD_UP)) {
            allItemsScroll = Gfx_Scroll(allItemsScroll, -MAX_ENTRY_LINES, itemCount);
            handledInput = true;
          } else if (pressed & (BUTTON_DOWN | CPAD_DOWN)) {
            allItemsScroll = Gfx_Scroll(allItemsScroll, MAX_ENTRY_LINES, itemCount);
            handledInput = true;
          }
        }
      } else if (curMenuIdx == PAGE_ITEMTRACKER_GROUPS && gSpoilerData.ItemLocationsCount > 0) {
        // Grouped Items list
        u16 itemCount = gSpoilerData.GroupItemCounts[currentItemGroup];
        if (pressed & (BUTTON_LEFT | CPAD_LEFT)) {
          groupItemsScroll = Gfx_Scroll(groupItemsScroll, -MAX_ENTRY_LINES, itemCount);
          handledInput = true;
        } else if (pressed & (BUTTON_RIGHT | CPAD_RIGHT)) {
          groupItemsScroll = Gfx_Scroll(groupItemsScroll, MAX_ENTRY_LINES, itemCount);
          handledInput = true;
        } else if (pressed & (BUTTON_UP | CPAD_UP)) {
          groupItemsScroll = Gfx_Scroll(groupItemsScroll, -1, itemCount);
          handledInput = true;
        } else if (pressed & (BUTTON_DOWN | CPAD_DOWN)) {
          groupItemsScroll = Gfx_Scroll(groupItemsScroll, 1, itemCount);
          handledInput = true;
        } else if (pressed & BUTTON_A) {
          NextItemGroup();
          handledInput = true;
        } else if (pressed & BUTTON_Y) {
          PrevItemGroup();
          handledInput = true;
        }
      }

      if (!handledInput) {
        if (pressed & closingButton) {
          showingLegend = false;
          Draw_ClearBackbuffer();
          Draw_CopyBackBuffer();
          if (gSettingsContext.playOption == PLAY_ON_CONSOLE) {
            Draw_FlushFramebuffer();
          }
          break;
        } else if (pressed & BUTTON_R1) {
          showingLegend = false;
          do {
            curMenuIdx++;
            if (static_cast<u32>(curMenuIdx) >= ARR_SIZE(menu_draw_funcs)) {
              curMenuIdx = 0;
            }
          } while (menu_draw_funcs[curMenuIdx] == NULL);
          handledInput = true;
        } else if (pressed & BUTTON_L1) {
          showingLegend = false;
          do {
            curMenuIdx--;
            if (curMenuIdx < 0) {
              curMenuIdx = (ARR_SIZE(menu_draw_funcs) - 1);
            }
          } while (menu_draw_funcs[curMenuIdx] == NULL);
          handledInput = true;
        }
      }

      // Keep updating while in the in-game menu
      Draw_ClearBackbuffer();
      Draw_ClearFramebuffer();

      // Continue counting up play time while in the in-game menu
      Gfx_UpdatePlayTime();

      menu_draw_funcs[curMenuIdx]();
      Gfx_DrawButtonPrompts();
      Gfx_DrawHeader();
      Draw_CopyBackBuffer();
      if (gSettingsContext.playOption == PLAY_ON_CONSOLE) {
        Draw_FlushFramebuffer();
      }
      pressed = Input_WaitWithTimeout(1000, closingButton);

    } while (true);
  }

  void Gfx_Init(void) {
    Draw_SetupFramebuffer();
    Draw_ClearBackbuffer();

    // Setup the title screen logo edits
    // gActorOverlayTable[0x171].initInfo->init = EnMag_rInit;

    if (gSettingsContext.menuOpeningButton == 0)
      closingButton = BUTTON_B | BUTTON_SELECT;
    else if (gSettingsContext.menuOpeningButton == 1)
      closingButton = BUTTON_B | BUTTON_START;
    else if (gSettingsContext.menuOpeningButton == 2)
      closingButton = BUTTON_B | BUTTON_UP;
    else if (gSettingsContext.menuOpeningButton == 3)
      closingButton = BUTTON_B | BUTTON_DOWN;
    else if (gSettingsContext.menuOpeningButton == 4)
      closingButton = BUTTON_B | BUTTON_RIGHT;
    else if (gSettingsContext.menuOpeningButton == 5)
      closingButton = BUTTON_B | BUTTON_LEFT;

    if (!gSettingsContext.ingameSpoilers) {
      menu_draw_funcs[PAGE_SPHERES] = NULL;
    }
    if (gSpoilerData.ItemLocationsCount == 0) {
      menu_draw_funcs[PAGE_ITEMTRACKER_ALL] = NULL;
      menu_draw_funcs[PAGE_ITEMTRACKER_GROUPS] = NULL;
    }

    // Call these to go to the first non-empty group page
    if (gSpoilerData.ItemLocationsCount > 0 && gSpoilerData.GroupItemCounts[currentItemGroup] == 0) {
      NextItemGroup();
    }

    // InitOptions();

    GfxInit = 1;
  }

  static u8 openingButton() {
    return (gSettingsContext.customIngameSpoilerButton != 0 &&
            rInputCtx.cur.val == gSettingsContext.customIngameSpoilerButton);
  }

  extern "C" {
  void Gfx_Update() {
    if (!GfxInit) {
      Gfx_Init();
      lastTick = svcGetSystemTick();
    }
    // The update is called here so it works while in different game modes (title screen, file select, boss challenge,
    // credits, MQ unlock)
    static u64 lastTickM = 0;
    static u64 elapsedTicksM = 0;
    elapsedTicksM += svcGetSystemTick() - lastTickM;
    if (elapsedTicksM >= TICKS_PER_SEC) {
      elapsedTicksM = 0;
    }
    lastTickM = svcGetSystemTick();

    Gfx_UpdatePlayTime();

    if (!isAsleep && openingButton()) {  //&& context.has_initialised
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      rnd::util::Print("%s: Attempting to show menu. Are we asleep? %u openingButtons is %u.\n", __func__, isAsleep,
                       openingButton());
#endif
      Gfx_ShowMenu();
      // Check again as it's possible the system was put to sleep while the menu was open
      if (!isAsleep) {
        svcSleepThread(1000 * 1000 * 300LL);
        // Update lastTick one more time so we don't count the added 0.3s sleep
        lastTick = svcGetSystemTick();
      }
    }
  }

  void Gfx_SleepQueryCallback() {
    ticksElapsed = 0;
    isAsleep = true;
  }

  void Gfx_AwakeCallback() {
    ticksElapsed = 0;
    lastTick = svcGetSystemTick();
    isAsleep = false;
  }
  }

}  // namespace rnd
