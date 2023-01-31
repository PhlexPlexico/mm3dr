/**
 * @file scene.h
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "common/types.h"

namespace game {

  /// Scene list: https://wiki.cloudmodding.com/mm/3D:Scene_List
  enum class SceneId : u16 {
    SouthernSwampClear = 0x00,
    TestMap01_01 = 0x01,
    TestMap01_02 = 0x02,
    TestMap01_03 = 0x03,
    TestMap01_04 = 0x04,
    TestMap01_05 = 0x05,
    TestMap01_06 = 0x06,
    Grottos = 0x07,
    Cutscenes = 0x08,
    Test01_09 = 0x09,
    PotionShop = 0x0A,
    MajoraLair = 0x0B,
    BeneathTheGraves = 0x0C,
    CuriosityShop = 0x0D,
    TestMap01_0E = 0x0E,
    TestMap02_0F = 0x0F,
    Barn = 0x10,
    HoneyAndDarling = 0x11,
    MayorResidence = 0x12,
    IkanaCanyon = 0x13,
    PirateFortress = 0x14,
    MilkBar = 0x15,
    StoneTowerTemple = 0x16,
    TreasureChestShop = 0x17,
    StoneTowerTempleInverted = 0x18,
    ClockTowerRooftop = 0x19,
    BeforeThePortalToTermina = 0x1A,
    WoodfallTemple = 0x1B,
    PathToMountainVillage = 0x1C,
    IkanaCastle = 0x1D,
    DekuScrubPlayground = 0x1E,
    OdolwaLair = 0x1F,
    ShootingGalleryTown = 0x20,
    SnowheadTemple = 0x21,
    MilkRoad = 0x22,
    PirateFortressInterior = 0x23,
    ShootingGallerySwamp = 0x24,
    PinnacleRock = 0x25,
    FairyFountain = 0x26,
    SwampSpiderHouse = 0x27,
    OceansideSpiderHouse = 0x28,
    AstralObservatory = 0x29,
    DekuTrial = 0x2A,
    DekuPalace = 0x2B,
    MountainSmithy = 0x2C,
    TerminaField = 0x2D,
    PostOffice = 0x2E,
    MarineResearchLaboratory = 0x2F,
    DampeHouse = 0x30,
    TestMap01_31 = 0x31,
    GoronShrine = 0x32,
    ZoraHall = 0x33,
    TradingPost = 0x34,
    RomaniRanch = 0x35,
    TwinmoldLair = 0x36,
    GreatBayCoast = 0x37,
    ZoraCape = 0x38,
    LotteryShop = 0x39,
    TestMap01_3A = 0x3A,
    PirateFortressExterior = 0x3B,
    FishermanHut = 0x3C,
    GoronShop = 0x3D,
    DekuKingChamber = 0x3E,
    GoronTrial = 0x3F,
    RoadToSouthernSwamp = 0x40,
    DoggyRacetrack = 0x41,
    CuccoShack = 0x42,
    IkanaGraveyard = 0x43,
    GohtLair = 0x44,
    SouthernSwamp = 0x45,
    Woodfall = 0x46,
    ZoraTrial = 0x47,
    GoronVillageSpring = 0x48,
    GreatBayTemple = 0x49,
    WaterfallRapids = 0x4A,
    BeneathTheWell = 0x4B,
    ZoraHallRooms = 0x4C,
    GoronVillageWinter = 0x4D,
    GoronGraveyard = 0x4E,
    SakonHideout = 0x4F,
    MountainVillageWinter = 0x50,
    GhostHut = 0x51,
    DekuShrine = 0x52,
    RoadToIkana = 0x53,
    SwordsmanSchool = 0x54,
    MusicBoxHouse = 0x55,
    IgosDuIkanaLair = 0x56,
    TouristInformation = 0x57,
    StoneTower = 0x58,
    StoneTowerInverted = 0x59,
    MountainVillageSpring = 0x5A,
    PathToSnowhead = 0x5B,
    Snowhead = 0x5C,
    PathToGoronVillageWinter = 0x5D,
    PathToGoronVillageSpring = 0x5E,
    GyorgLair = 0x5F,
    SecretShrine = 0x60,
    StockPotInn = 0x61,
    GreatBayCutscene = 0x62,
    ClockTowerInterior = 0x63,
    WoodsOfMystery = 0x64,
    LostWoods = 0x65,
    LinkTrial = 0x66,
    Moon = 0x67,
    BombShop = 0x68,
    GiantsChamber = 0x69,
    GormanTrack = 0x6A,
    GoronRacetrack = 0x6B,
    EastClockTown = 0x6C,
    WestClockTown = 0x6D,
    NorthClockTown = 0x6E,
    SouthClockTown = 0x6F,
    LaundryPool = 0x70,
    SwampFishingHole = 0x71,
    OceanFishingHole = 0x72,
    TerminaFieldCutscene1 = 0x73,
    TerminaFieldCutscene2 = 0x74,
  };

  struct PathAndSize {
    char path[48];
    u32 size;
  };
  static_assert(sizeof(PathAndSize) == 0x34);

  struct SceneInfo {
    PathAndSize zsi;
    PathAndSize gar;
    u16 field_68;
    u8 field_6A;
    u8 field_6B;
    u32 bgm_id;
  };
  static_assert(sizeof(SceneInfo) == 0x70);

}  // namespace game

#endif