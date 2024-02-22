#ifndef _RND_SETTINGS_H_
#define _RND_SETTINGS_H_

#include "common/advanced_context.h"
#include "game/common_data.h"
#include "z3d/z3DVec.h"

namespace rnd {
  enum class BooleanSetting : u8 {
    OFF,
    ON,
  };

  enum class SkipSetting : u8 {
    DONT_SKIP,
    SKIP,
  };

  enum class LogicSetting : u8 {
    LOGIC_GLITCHLESS,
    LOGIC_NONE,
    LOGIC_VANILLA,
    LOGIC_GLITCHED,
  };

  enum class AmmoDropsSetting : u8 {
    AMMODROPS_VANILLA,
    AMMODROPS_BOMBCHU,
    AMMODROPS_NONE,
  };

  enum class HeartDropRefillSetting : u8 {
    HEARTDROPREFILL_VANILLA,
    HEARTDROPREFILL_NODROP,
    HEARTDROPREFILL_NOREFILL,
    HEARTDROPREFILL_NODROPREFILL,
  };

  enum class RewardShuffleSetting : u8 {
    REWARDSHUFFLE_END_OF_DUNGEON,
    REWARDSHUFFLE_ANY_DUNGEON,
    REWARDSHUFFLE_OVERWORLD,
    REWARDSHUFFLE_ANYWHERE,
  };

  enum class GreatFairyRewardShuffleSetting : u8 {
    GFREWARDSHUFFLE_VANILLA,
    GFREWARDSHUFFLE_ALL_GREAT_FARIES,
    GFREWARDSHUFFLE_ANYWHERE,
  };

  enum class LinksPocketSetting : u8 {
    LINKSPOCKETITEM_ADVANCEMENT,
    LINKSPOCKETITEM_NOTHING,
  };

  enum class SongShuffleSetting : u8 {
    SONGSHUFFLE_SONG_LOCATIONS,
    SONGSHUFFLE_DUNGEON_REWARDS,
    SONGSHUFFLE_ANYWHERE,
  };

  enum class ShopsanitySetting : u8 {
    SHOPSANITY_OFF,
    SHOPSANITY_ZERO,
    SHOPSANITY_ONE,
    SHOPSANITY_TWO,
    SHOPSANITY_THREE,
    SHOPSANITY_FOUR,
    SHOPSANITY_RANDOM,
  };

  /*enum class TokensanitySetting : u8 {
    TOKENSANITY_OFF,
    TOKENSANITY_DUNGEONS,
    TOKENSANITY_OVERWORLD,
    TOKENSANITY_ALL_TOKENS,
  };*/

  enum class ScrubsanitySetting : u8 {
    SCRUBSANITY_OFF,
    SCRUBSANITY_AFFORDABLE,
    SCRUBSANITY_EXPENSIVE,
    SCRUBSANITY_RANDOM_PRICES,
  };

  enum class ShuffleMerchantsSetting : u8 {
    SHUFFLEMERCHANTS_OFF,
    SHUFFLEMERCHANTS_NO_HINTS,
    SHUFFLEMERCHANTS_HINTS,
  };

  enum class MapsAndCompassesSetting : u8 {
    MAPSANDCOMPASSES_VANILLA,
    MAPSANDCOMPASSES_START_WITH,
    MAPSANDCOMPASSES_OWN_DUNGEON,
    MAPSANDCOMPASSES_ANY_DUNGEON,
    MAPSANDCOMPASSES_OVERWORLD,
    MAPSANDCOMPASSES_ANYWHERE,
  };

  enum class KeysanitySetting : u8 {
    KEYSANITY_VANILLA,
    KEYSANITY_START_WITH,
    KEYSANITY_OWN_DUNGEON,
    KEYSANITY_ANY_DUNGEON,
    KEYSANITY_OVERWORLD,
    KEYSANITY_ANYWHERE,
  };

  enum class BossKeysanitySetting : u8 {
    BOSSKEYSANITY_VANILLA,
    BOSSKEYSANITY_START_WITH,
    BOSSKEYSANITY_OWN_DUNGEON,
    BOSSKEYSANITY_ANY_DUNGEON,
    BOSSKEYSANITY_OVERWORLD,
    BOSSKEYSANITY_ANYWHERE,
  };

  enum class ExcludeLocationSetting : u8 {
    INCLUDE,
    EXCLUDE,
  };

  enum class StartingInventorySetting : u8 {
    STARTINGINVENTORY_NONE,
  };

  enum class LogicTrickSetting : u8 {
    TRICK_DISABLED,
    TRICK_ENABLED,
  };

  enum class DamageMultiplierSetting : u8 {
    DAMAGEMULTIPLIER_HALF,
    DAMAGEMULTIPLIER_DEFAULT,
    DAMAGEMULTIPLIER_DOUBLE,
    DAMAGEMULTIPLIER_QUADRUPLE,
    DAMAGEMULTIPLIER_OCTUPLE,
    DAMAGEMULTIPLIER_SEXDECUPLE,
    DAMAGEMULTIPLIER_OHKO,
  };

  enum class GossipStoneHintsSetting : u8 {
    HINTS_NO_HINTS,
    HINTS_NEED_NOTHING,
    HINTS_MASK_OF_TRUTH,
  };

  enum class ItemPoolSetting : u8 {
    ITEMPOOL_PLENTIFUL,
    ITEMPOOL_BALANCED,
    ITEMPOOL_SCARCE,
    ITEMPOOL_MINIMAL,
  };

  enum class IceTrapSetting : u8 {
    ICETRAPS_OFF,
    ICETRAPS_EXTRA,
    ICETRAPS_MAYHEM,
    ICETRAPS_ONSLAUGHT,
  };

  enum class StartingBottleSetting : u8 {
    STARTINGBOTTLE_NONE,
    STARTINGBOTTLE_EMPTY_BOTTLE = 0x12,
    STARTINGBOTTLE_RED_POTION,
    STARTINGBOTTLE_GREEN_POTION,
    STARTINGBOTTLE_BLUE_POTION,
    STARTINGBOTTLE_FAIRY,
    STARTINGBOTTLE_DEKU_PRINCESS,
    STARTINGBOTTLE_MILK,
    STARTINGBOTTLE_MILK_HALF,
    STARTINGBOTTLE_FISH,
    STARTINGBOTTLE_BUGS,
    STARTINGBOTTLE_BIG_POE = 0x1E,
    STARTINGBOTTLE_SPRING_WATER,
    STARTINGBOTTLE_HOT_SPRING_WATER,
    STARTINGBOTTLE_ZORA_EGG,
    STARTINGBOTTLE_GOLD_DUST,
    STARTINGBOTTLE_MAGICAL_MUSHROOM,
    STARTINGBOTTLE_SEAHORSE,
    STARTINGBOTTLE_CHATEAU_ROMANI,
    STARTINGBOTTLE_MYSTERY_MILK,
    STARTINGBOTTLE_MYSTERY_MILK_SPOILED,
  };

  enum class StartingWalletSetting : u8 {
    STARTINGWALLET_NONE,
    STARTINGWALLET_ADULT,
    STARTINGWALLET_GIANT,
    STARTINGWALLET_TYCOON,
  };

  enum class StartingSwordSetting : u8 {
    STARTINGSWORD_KOKIRI,
    STARTINGSWORD_RAZOR,
    STARTINGSWORD_GILDED,
    STARTINGSWORD_NONE,
  };

  enum class StartingSheildSetting : u8 {
    STARTINGSHIELD_HERO,
    STARTINGSHIELD_MIRROR,
    STARTINGSHIELD_NONE,
  };

  enum class StartingSpinSetting : u8 {
    STARTINGSPIN_REGULAR,
    STARTINGSPIN_GREAT,
  };

  enum class StartingTradeItemSetting : u8 {
    STARTINGTRADEITEM_MOON_TEAR,
    STARTINGTRADEITEM_LAND_TITLE_DEED,
    STARTINGTRADEITEM_SWAMP_TITLE_DEED,
    STARTINGTRADEITEM_MOUNTAIN_TITLE_DEED,
    STARTINGTRADEITEM_OCEAN_TITLE_DEED,
    STARTINGTRADEITEM_ROOM_KEY,
    STARTINGTRADEITEM_LETTER_TO_MAMA,
    STARTINGTRADEITEM_LETTER_TO_KAFEI,
    STARTINGTRADEITEM_PENDANT_OF_MEMORIES,
  };
  enum class ShuffleChestsSetting : u8 {
    SHUFFLECHESTS_VANILLA,
    SHUFFLECHESTS_RANDOM,
  };
  enum class StrayFairySanitySetting : u8 {
    STRAYFAIRYSANITY_VANILLA,
    STRAYFAIRYSANITY_ANYWHERE,
  };
  enum class ShuffleKokiriSwordSetting : u8 {
    SHUFFLEKOKIRISWORD_VANILLA,
    SHUFFLEKOKIRISWROD_ANYWHERE,
  };

  typedef enum {
    DUNGEON_NEITHER,
    DUNGEON_BARREN,
    DUNGEON_WOTH,
  } DungeonInfo;

  typedef enum {
    PLAY_ON_CONSOLE,
    PLAY_ON_CITRA,
  } PlayOption;

  typedef struct {
    u8 hashIndexes[5];

    u8 playOption;

    u8 logic;
    u8 locationsReachable;

    u8 shuffleDungeonEntrances;
    u8 bombchusInLogic;
    u8 ammoDrops;
    u8 heartDropRefill;

    u8 shuffleRewards;
    u8 shuffleGreatFairyRewards;
    u8 linksPocketItem;
    u8 shuffleSongs;
    u8 tokensanity;
    u8 scrubsanity;
    u8 shopsanity;
    u8 shuffleKokiriSword;
    u8 shuffleStartingShield;
    u8 shuffleMagicBeans;
    u8 shuffleMerchants;
    u8 shuffleChests;

    u8 mapsAndCompasses;
    u8 keysanity;
    u8 bossKeysanity;

    u8 skipEponaRace;
    u8 skipMinigamePhases;
    u8 skipBombersMinigame;

    u8 freeScarecrow;

    u8 skipBeansTest;
    u8 skipPowerKegTest;

    u8 damageMultiplier;
    u8 gossipStoneHints;
    u8 chestAnimations;
    u8 chestSize;
    u8 compassesShowWotH;
    u8 generateSpoilerLog;
    u8 ingameSpoilers;
    u8 menuOpeningButton;
    u8 randomTrapDmg;

    u8 itemPoolValue;
    u8 iceTrapValue;

    u8 customTunicColors;
    u8 coloredKeys;
    u8 coloredBossKeys;

    u8 odolwaTrialSkip;
    u8 gohtTrialSkip;
    u8 gyorgTrialSkip;
    u8 twinmoldTrialSkip;

    u8 progressiveGildedSword;
    u8 startingSpinSettting;

    u32 linksTradeItemBitMask;

    u8 startingConsumables;
    u8 startingMaxRupees;
    u8 startingOcarina;
    u8 startingHerosBow;
    u8 startingFireArrows;
    u8 startingIceArrows;
    u8 startingLightArrows;
    u8 startingBombBag;
    u8 startingBombchus;
    u8 startingStickCapacity;
    u8 startingNutCapacity;
    u8 startingMagicBean;
    u8 startingPowderKeg;
    u8 startingPictographBox;
    u8 startingLensOfTruth;
    u8 startingHookshot;
    u8 startingGreatFairySword;
    u8 startingBottle1;
    u8 startingBottle2;
    u8 startingBottle3;
    u8 startingBottle4;
    u8 startingBottle5;
    u8 startingBottle6;
    u8 startingBottle7;

    u8 startingKokiriSword;
    u8 startingShield;
    u8 startingMagicMeter;
    u8 startingDoubleDefense;
    u8 startingHealth;

    // Songs
    u8 startingOathToOrder;
    u8 startingEponasSong;
    u8 startingSongOfStorms;
    u8 startingSonataOfAwakening;
    u8 startingGoronsLullaby;
    u8 startingNewWaveBossaNova;
    u8 startingElegyOfEmptiness;
    u8 startingSongOfSoaring;
    u8 startingSongOfHealing;
    u8 startingWallet;
    // BossRemains
    u8 startingOdolwaRemains;
    u8 startingGohtRemains;
    u8 startingGyorgRemains;
    u8 startingTwinmoldRemains;
    // Tokens
    u8 startingSwampTokens;
    u8 startingOceanTokens;
    // Masks
    u8 startingDekuMask;
    u8 startingGoronMask;
    u8 startingZoraMask;
    u8 startingBunnyHood;
    u8 startingKeatonMask;
    u8 startingPostmanHat;
    u8 startingAllNightMask;
    u8 startingBlastMask;
    u8 startingStoneMask;
    u8 startingGreatFairyMask;
    u8 startingBremenMask;
    u8 startingDonGerosMask;
    u8 startingMaskOfScents;
    u8 startingRomanisMask;
    u8 startingCircusLeadersMask;
    u8 startingKafeiMask;
    u8 startingCouplesMask;
    u8 startingKamarosMask;
    u8 startingGibdosMask;
    u8 startingGaroMask;
    u8 startingCaptainsHat;
    u8 startingGiantsMask;
    u8 startingFierceDeityMask;
    u8 startingMaskOfTruth;

    // TODO: Break out into individual bitfield values.
    u32 startingQuestItems;
    u32 startingDungeonReward;
    u32 startingEquipment;
    u32 startingUpgrades;
    game::PlayerData::OwlStatues startingOwlStatues;

    // ARM Patch Checks / Restoration Checks
    u8 enableFastZoraSwim;
    u8 enableOcarinaDiving;
    u8 enableFastElegyStatues;
    u8 maskOfTruthRequiredForGossip;
    u8 enableFastMaskTransform;
    u8 enableFastOcarina;
    u8 enableFastArrowSwap;

    // Cutscene Skips
    u8 skipHMSCutscenes;
    u8 skipMikauCutscene;
    u8 skipDarmaniCutscene;

    // Custom Buttons
    u32 customMapButton = 0;
    u32 customItemButton = 0;
    u32 customMaskButton = 0;
    u32 customNotebookButton = 0;
    u32 customIngameSpoilerButton = 0;

    // Extra MM Settings
    u8 blastMaskCooldown;
  } SettingsContext;

  extern "C" SettingsContext gSettingsContext;
  extern const char hashIconNames[62][25];

  s32 Settings_ApplyDamageMultiplier(game::GlobalContext*, s32);
  u32 Hash(u32);
  u8 Bias(u32);
}  // namespace rnd
#endif
