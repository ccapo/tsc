// The Serpentine Caves
// Copyright (c) 2011, 2012 Christopher Claudio Capobianco
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Christopher Claudio Capobianco may not be used to endorse
//       or promote products derived from this software without specific prior
//       written permission.
//
// THIS SOFTWARE IS PROVIDED BY CHRISTOPHER CLAUDIO CAPOBIANCO ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL CHRISTOPHER CLAUDIO CAPOBIANCO BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2009 J.C.Wilk
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of J.C.Wilk may not be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY J.C.WILK ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL J.C.WILK BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "global.hpp"

enum EMagic
{
  MAGIC_LIGHT,
  MAGIC_FIRE,
  MAGIC_WATER,
  MAGIC_WIND,
  MAGIC_EARTH,
  NMAGIC
};

// Tile Identifiers
enum EChar
{
  // Magic charge bar
  CHAR_CHARGEBAR = 256,

  // Player Tiles
  CHAR_PLAYER_RIGHT,
  CHAR_PLAYER_DOWN,
  CHAR_PLAYER_LEFT,
  CHAR_PLAYER_UP,

  // NPC Tiles
  CHAR_GUARDIAN,
  CHAR_KEEPER,
  CHAR_PERSON,

  // Monster Tiles
  CHAR_GUARD_GREY,
  CHAR_GUARD_RED,
  CHAR_GUARD_GOLD,

  CHAR_WARLOCK_PURPLE,
  CHAR_WARLOCK_WHITE,
  CHAR_WARLOCK_RED,

  CHAR_NECROMANCER_APPENTICE,
  CHAR_NECROMANCER_MASTER,

  CHAR_DARKELF_ARCHER,
  CHAR_DARKELF_WARRIOR,
  CHAR_DARKELF_MAGE,

  CHAR_DWARF_WARRIOR,
  CHAR_DWARF_AXEBEARER,
  CHAR_DWARF_MAGE,
  CHAR_DWARF_HERO,

  CHAR_UNDEAD_DWARF_WARRIOR,
  CHAR_UNDEAD_DWARF_AXEBEARER,
  CHAR_UNDEAD_DWARF_MAGE,
  CHAR_UNDEAD_DWARF_HERO,

  CHAR_GOBLIN_PEON,
  CHAR_GOBLIN_WARRIOR,
  CHAR_GOBLIN_MAGE,

  CHAR_IMP_BLUE,
  CHAR_IMP_RED,

  CHAR_ORGE_PEON_GREEN,
  CHAR_ORGE_WARRIOR_GREEN,

  CHAR_ORGE_PEON_RED,
  CHAR_ORGE_WARRIOR_RED,

  CHAR_SKELETON_PEON,
  CHAR_SKELETON_WARRIOR,
  CHAR_SKELETON_HERO,
  CHAR_SKELETON_MAGE,

  CHAR_SPRITE_RED,
  CHAR_SPRITE_BLUE,
  CHAR_SPRITE_GREEN,
  CHAR_SPRITE_YELLOW,

  CHAR_ORC_PEON,
  CHAR_ORC_WARRIOR,
  CHAR_ORC_HERO,
  CHAR_ORC_MAGE,

  CHAR_DEMON_PEON,
  CHAR_DEMON_HERO,
  CHAR_DEMON_MAGE,

  CHAR_FLAYER_WARRIOR,
  CHAR_FLAYER_MAGE,

  CHAR_SKULL,

  CHAR_GOLEM_GREY,
  CHAR_GOLEM_BROWN,
  CHAR_GOLEM_RED,

  CHAR_SLIME_BROWN,
  CHAR_SLIME_GREEN,

  CHAR_EYEBALL,

  CHAR_VERMIN_BROWN,
  CHAR_VERMIN_GREEN,

  CHAR_SNAKE_PURLE,
  CHAR_SNAKE_GREEN,

  CHAR_SCORPIAN_YELLOW,
  CHAR_SCORPIAN_BLACK,

  CHAR_SPIDER_BLACK,
  CHAR_SPIDER_RED,
  CHAR_SPIDER_GREEN,

  CHAR_PYTHON_RED,
  CHAR_PYTHON_BROWN,
  CHAR_PYTHON_YELLOW,

  CHAR_BAT_BROWN,
  CHAR_BAT_BLUE,

  // Environment Tiles
  CHAR_TREE_A,
  CHAR_TREE_B,
  CHAR_TREE_C,
  CHAR_TREE_D,
  CHAR_TREE_E,
  CHAR_TREE_F,
  CHAR_TREE_G,

  CHAR_SHRUB_A,
  CHAR_SHRUB_B,
  CHAR_SHRUB_C,
  CHAR_SHRUB_D,
  CHAR_MUSHROOM,
  CHAR_FLOWERS_WHITE,
  CHAR_FLOWERS_BLUE,

  CHAR_TEMPLE,
  CHAR_TOWN,
  CHAR_CAVE,

  CHAR_BED,
  CHAR_TABLE,
  CHAR_BOOKCASE,
  CHAR_CHAIR_RIGHT,
  CHAR_CHAIR_LEFT,

  // Minor Boss Tiles (Upper Portion)
  CHAR_DEMONLORD_WHITE_UL,
  CHAR_DEMONLORD_WHITE_UR,

  CHAR_DEMONLORD_RED_UL,
  CHAR_DEMONLORD_RED_UR,

  CHAR_CYCLOPS_UL,
  CHAR_CYCLOPS_UR,

  CHAR_DRAGON_LARGE_RED_UL,
  CHAR_DRAGON_LARGE_RED_UR,

  CHAR_DRAGON_LARGE_YELLOW_UL,
  CHAR_DRAGON_LARGE_YELLOW_UR,

  CHAR_DRAGON_LARGE_GREEN_UL,
  CHAR_DRAGON_LARGE_GREEN_UR,

  CHAR_DRAGON_LARGE_BLUE_UL,
  CHAR_DRAGON_LARGE_BLUE_UR,

  CHAR_DRAGON_LARGE_GREY_UL,
  CHAR_DRAGON_LARGE_GREY_UR,

  CHAR_MINOTAUR_UL,
  CHAR_MINOTAUR_UR,

  CHAR_LIZARD_GIANT_UL,
  CHAR_LIZARD_GIANT_UR,

  CHAR_MEDUSA_UL,
  CHAR_MEDUSA_UR,

  CHAR_FLYING_BRAIN_UL,
  CHAR_FLYING_BRAIN_UR,

  CHAR_SLIMELORD_UL,
  CHAR_SLIMELORD_UR,

  CHAR_BEHOLDER_UL,
  CHAR_BEHOLDER_UR,

  CHAR_BEHEMOTH_UL,
  CHAR_BEHEMOTH_UR,

  // Final Boss Tiles (Upper Portion)
  CHAR_FINAL_BOSS_UL,
  CHAR_FINAL_BOSS_UR,

  // Minor Boss Tiles (Lower Portion)
  CHAR_DEMONLORD_WHITE_LL,
  CHAR_DEMONLORD_WHITE_LR,

  CHAR_DEMONLORD_RED_LL,
  CHAR_DEMONLORD_RED_LR,

  CHAR_CYCLOPS_LL,
  CHAR_CYCLOPS_LR,

  CHAR_DRAGON_LARGE_RED_LL,
  CHAR_DRAGON_LARGE_RED_LR,

  CHAR_DRAGON_LARGE_YELLOW_LL,
  CHAR_DRAGON_LARGE_YELLOW_LR,

  CHAR_DRAGON_LARGE_GREEN_LL,
  CHAR_DRAGON_LARGE_GREEN_LR,

  CHAR_DRAGON_LARGE_BLUE_LL,
  CHAR_DRAGON_LARGE_BLUE_LR,

  CHAR_DRAGON_LARGE_GREY_LL,
  CHAR_DRAGON_LARGE_GREY_LR,

  CHAR_MINOTAUR_LL,
  CHAR_MINOTAUR_LR,

  CHAR_LIZARD_GIANT_LL,
  CHAR_LIZARD_GIANT_LR,

  CHAR_MEDUSA_LL,
  CHAR_MEDUSA_LR,

  CHAR_FLYING_BRAIN_LL,
  CHAR_FLYING_BRAIN_LR,

  CHAR_SLIMELORD_LL,
  CHAR_SLIMELORD_LR,

  CHAR_BEHOLDER_LL,
  CHAR_BEHOLDER_LR,

  CHAR_BEHEMOTH_LL,
  CHAR_BEHEMOTH_LR,

  // Final Boss Tiles (Lower Portion)
  CHAR_FINAL_BOSS_LL,
  CHAR_FINAL_BOSS_LR
};

// The class that holds information about the game engine
class Game
{
  public:
  // Random seed and noise generators
  uint32 seed;
  TCODRandom *rng;
  TCODNoise *torch;
  TCODNoise *terrain;
  TCODNoise *weather;

  float p, offsetW, offsetC;

  bool inCaves;                                                   // Flag to indicate when in the caves
  bool isFaded;                                                   // Flag to indicate whether the screen has faded to black
  int worldID;                                                    // Current world map ID
  int caveID;                                                     // Current cave map ID
  int magicID;                                                    // Current magic type ID

  int mouse_x, mouse_y;                                           // Cell under mouse cursor

  float elapsedTime;                                              // Elapsed Time

  Player player;                                                  // Player object

  WorldMap world[NWORLD];                                         // All world map objects
  CaveMap caves[NCAVE_REGIONS*NLEVELS_REGION];                    // All cave map objects

  Sound sound;                                                    // Sound object
  Menu menu;                                                      // Menu object

  //bool bossSeen, bossIsDead;                                    // Final boss flags
  //Guardian *guardian;                                           // Guardian object
  //Boss *boss;                                                   // Final boss object (Angra Mainyu)

  Game();                                                         // Game Constructor
  ~Game();                                                        // Game Destructor

  void startup(int narg, char *argv[]);                           // Startup the game
  void shutdown();                                                // Shutdown the game

  bool updateTitle(float elapsed, TCOD_key_t key);                // Update the title screen
  void renderTitle();                                             // Render the title screen

  bool updateIntro(float elapsed, TCOD_key_t key);                // Update the intro screen
  void renderIntro();                                             // Render the intro screen

  bool newGame();                                                 // Creates a new game
  bool saveGame(bool init = true);                                // Saves the game
  bool loadGame();                                                // Loads the saved game

  void handleInput(TCOD_key_t *key, TCOD_mouse_t mouse);          // Handles the keyboard and mouse input

  void setupEconomy();                                            // Setup the economy for all towns
  void updateEconomy();                                           // Update the economy for all towns

  bool update(float elapsed, TCOD_key_t key, TCOD_mouse_t mouse); // Updates the game
  void render(bool *first);                                       // Renders the game

  // Renders a progress bar and flush
  void displayProgress(const char msg[], float fraction);

  // Magic
  TCODImage *magic_icon;
  //TCODList <Magic *> magic;
  //void addMagic(Magic *m) { magic.push(m); }

  private:
  TCODZip *zip;
};

// The (extern) game object
extern Game game;
