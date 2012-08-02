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

  bool inCaves;                                                   // Flag to indicate when in the caves
  bool isFaded;                                                   // Flag to indicate whether the screen has faded to black
  int worldID;                                                    // Current world map ID
  int caveID;                                                     // Current cave map ID
  int magicID;                                                    // Current magic type ID

  int mouse_x, mouse_y;                                           // Cell under mouse cursor

  float elapsedTime;                                              // Elapsed Time

  Player player;                                                  // Player object

  WorldMap world[NWORLD];                                         // All world map objects
  CaveMap caves[NCAVES];                                          // All cave map objects

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
