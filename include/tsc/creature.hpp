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

enum ECreatureType
{
  CREATURETYPE_INSECT,
  CREATURETYPE_VERMIN,
  CREATURETYPE_REPTILE,
  CREATURETYPE_BEAST,
  CREATURETYPE_TROGLODYTE,
  CREATURETYPE_GIANT,
  CREATURETYPE_SPECIAL,
  NCREATURETYPES
};

enum ECreatureSubType
{
  CREATURESUBTYPE_PEON,
  CREATURESUBTYPE_COMMANDER,
  CREATURESUBTYPE_LEADER,
  CREATURESUBTYPE_SPECIAL,
  NCREATURESUBTYPES
};

enum ENpcType
{
  NPCTYPE_ITEMSHOPKEEPER,
  NPCTYPE_EQUIPSHOPKEEPER,
  NPCTYPE_INNKEEPER,
  NPCTYPE_FERRYMAN,
  NPCTYPE_TOWNSPERSON,
  NPCTYPE_LIGHTGUARDIAN,
  NPCTYPE_FIREGUARDIAN,
  NPCTYPE_WATERGUARDIAN,
  NPCTYPE_WINDGUARDIAN,
  NPCTYPE_EARTHGUARDIAN,
  NPCTYPES
};

class Player;
class CaveMap;

// The class that holds information about creatures
class Creature
{
  public:
  Stats stats;                                           // Creature's Current Stats
  int lvl;                                               // Creature's Level
  int x, y;                                              // Creature Position
  ECreatureType creatureType;                            // Creature Type
  ECreatureSubType creatureSubType;                      // Creature SubType
  char name[CHARMAX];                                    // Creature Name
  TCODColor colour;                                      // Creature Colour
  int sym;                                               // Creature Symbol
  float walkTimer;                                       // Creature's Walk Timer
  float scentThreshold;                                  // Creature's Scent Threshold
  bool inUse;                                            // Creature's In Use flag
  //TCODPath *path;                                      // Creature's Path object

  Creature();                                            // The Default Creature Constructor
  Creature(int x0, int y0, ECreatureType creatureType0); // The CreatureConstructor

  void updateStats();                                    // Update Creature stats

  void chasePlayer(CaveMap *cmap, Player player);        // Creature chases the Player
  void avoidPlayer(CaveMap *cmap, Player player);        // Creature avoids the Player

  void update(Player player, float elapsed);             // Update Creature
  void render(Player player);                            // Render Creature
};

// The class that holds information about corpses
class Corpse
{
  public:
  int x, y;                                              // Corpse Position
  TCODColor colour;                                      // Corpse Colour
  int sym;                                               // Corpse Symbol
  bool inUse;                                            // Corpse In Use flag

  Corpse();                                              // The Default Corpse Constructor
  Corpse(int x0, int y0);                                // The Corpse Constructor

  void render(Player player);                            // Render Corpse
};

// The class that holds information about hides
class Hide
{
  public:
  int x, y;                                              // Hide Position
  ECreatureType creatureType;                            // Hide Creature Type
  char name[CHARMAX];                                    // Hide Name
  char label[CHARMAX];                                   // Hide Label
  TCODColor colour;                                      // Hide Colour
  int sym;                                               // Hide Symbol
  float mass;                                            // Hide Mass
  bool inUse;                                            // Hide In Use flag

  Hide();                                                // The Default Hide Constructor
  Hide(int x0, int y0, ECreatureType creatureType0);     // The Hide Constructor

  void render(Player player);                            // Render Hide
};

// This class holds all the information the hide inventory
class HideInventory
{
  public:
  int maxCount[NCREATURETYPES];                          // Max. Number of Each Hide
  int count[NCREATURETYPES];                             // Quantity of Each Hide
  int index[NCREATURETYPES];                             // Hide index
  int minPrice[NCREATURETYPES];                          // Min. Price of Each Hide
  int maxPrice[NCREATURETYPES];                          // Max. Price of Each Hide
  int price[NCREATURETYPES];                             // Price of Each Hide
  int nhides;                                            // Number of available Hides (i.e. sum(count > 0))
  float mass;                                            // Mass of Hide Inventory

  Hide hides[NCREATURETYPES];                            // Hide List

  HideInventory();                                       // The Hide Inventory Constructor
};

// The class that holds information about NPCs
class Npc
{
  public:
  int x, y;                                              // Npc Position
  int spd;                                               // Npc Speed
  ENpcType npcType;                                      // Npc Type
  char label[CHARMAX];                                   // Npc Label
  TCODColor colour;                                      // Npc Colour
  int sym;                                               // Npc Symbol
  float walkTimer;                                       // Npc Walk Timer
  bool inUse;                                            // Npc In Use flag
  TCODPath *path;                                        // Npc Path object

  Npc();                                                 // The Default Npc Constructor
  Npc(int x0, int y0, int spd0, ENpcType npcType0);      // The Npc Constructor

  void update(Player player, float elapsed);             // Update Npc
  void render(Player player);                            // Render Npc
};
