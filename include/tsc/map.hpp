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

// World Map Location Identifiers
enum ETemple
{
  TEMPLE_LIGHT,
  TEMPLE_FIRE,
  TEMPLE_WATER,
  TEMPLE_WIND,
  TEMPLE_EARTH,
  NTEMPLES
};

enum ETown
{
  TOWN_01 = NTEMPLES,
  TOWN_02,
  TOWN_03,
  TOWN_04,
  TOWN_05,
  TOWN_06,
  TOWN_07,
  TOWN_08,
  TOWN_09,
  TOWN_10,
  TOWN_11,
  TOWN_12,
  NTMP,
  NTOWNS = NTMP - NTEMPLES
};

enum ECaves
{
  CAVE_01 = NTEMPLES + NTOWNS,
  CAVE_02,
  CAVE_03,
  CAVE_04,
  CAVE_05,
  CAVE_06,
  CAVE_07,
  NWORLD,
  NCAVES = NWORLD - NTEMPLES - NTOWNS
};

class Player;

// The class that holds information about world maps
class WorldMap
{
  public:
  Cell cells[IMAGE_WIDTH*IMAGE_HEIGHT];
  TCODMap *fov1x;

  SubCell subcells[IMAGE_WIDTH2*IMAGE_HEIGHT2];
  TCODMap *fov2x;

  int nlocations, nnpcs;
  Npc npcs[NPCMAX];
  Location locations[NLOCATIONMAX];

  // Coordinate of console cell (0, 0) in the map
  int display_x, display_y;

  TCODImage *img;
  TCODImage *img_thumb;

  // Switch to display the weather
  bool displayWeather;

  char label[CHARMAX];
  int musicID;

  TCODColor darkWall;
  TCODColor lightWall;
  TCODColor darkGround;
  TCODColor lightGround;

  map<int, Location> locWorld;

  // The default world map constructor
  WorldMap();

  // Updates World Map
  void update();

  // Renders World Map
  void render(Player player);

  // Loads a map
  void loadMap(const char filename[], const char name[], int musicIndex, bool init = true);

  // Moves the display
  void moveDisplay(int x, int y);

  inline bool isFov1xWalkable(int x, int y) { return fov1x->isWalkable(x, y); }
  inline bool isFov1xTransparent(int x, int y) { return fov1x->isTransparent(x, y); }
  inline bool isFov2xWalkable(int x, int y) { return fov2x->isWalkable(x, y); }
  inline bool isFov2xTransparent(int x, int y) { return fov2x->isTransparent(x, y); }

  inline int getLocationID(int x, int y) { return cells[x + IMAGE_WIDTH*y].locationID; }
  void addWorldMapLocations();
  void addLocation(int x, int y, const char name[], TCODColor colour, char sym);

  inline int getNpcID(int x, int y) { return cells[x + IMAGE_WIDTH*y].creatureID; }
  void addNpc(int x, int y, int spd, ENpcType npcType);
  void updateNpcs(Player player, float elapsed);
};

// The class that holds information about the cave maps
class CaveMap
{
  public:
  Cell cells[MAP_WIDTH*MAP_HEIGHT];
  TCODMap *fov1x;

  SubCell subcells[MAP_WIDTH2*MAP_HEIGHT2];
  TCODMap *fov2x;

  int nitems, ncreatures, ncorpses, nhides, nlocations;
  Item items[NITEMMAX];
  Creature creatures[NCREATUREMAX];
  Corpse corpses[NCORPSEMAX];
  Hide hides[NCORPSEMAX];
  Location locations[NLOCATIONMAX];

  int upx, upy, downx, downy;

  // Coordinate of console cell (0, 0) in the map
  int display_x, display_y;

  bool recomputeFov;

  TCODImage *img;
  TCODImage *img_thumb;

  char label[CHARMAX];
  int musicID;

  TCODColor darkWall;
  TCODColor lightWall;
  TCODColor darkGround;
  TCODColor lightGround;

  // The default cave map constructor
  CaveMap();

  // Updates Cave Map
  void update(Player player);

  // Renders Cave Map
  void render(Player player);

  void floodFill(int x, int y, TCODColor fill); // Fill pixels that aren't the fill colour
  void generateHM(TCODHeightMap *hmap);         // Generates a height map
  void generateMap();                           // Generates a map
  void finalizeMap(int level);                  // Finalize a map
  void loadMap();                               // Load a map

  void moveDisplay(int x, int y);               // Moves the display

  inline bool isFov1xWalkable(int x, int y) { return fov1x->isWalkable(x, y); }
  inline bool isFov1xTransparent(int x, int y) { return fov1x->isTransparent(x, y); }
  inline bool inFov1x(int x, int y) { return fov1x->isInFov(x, y); }
  inline bool isFov2xWalkable(int x, int y) { return fov2x->isWalkable(x, y); }
  inline bool isFov2xTransparent(int x, int y) { return fov2x->isTransparent(x, y); }
  inline bool inFov2x(int x, int y) { return fov2x->isInFov(x, y); }

  inline bool getFov2x(int x, int y) { return (inFov2x(2*x, 2*y) || inFov2x(2*x + 1, 2*y) || inFov2x(2*x, 2*y + 1) || inFov2x(2*x + 1, 2*y + 1));}

  inline int getItemID(int x, int y) { return cells[x + MAP_WIDTH*y].itemID; }
  inline int getCreatureID(int x, int y) { return cells[x + MAP_WIDTH*y].creatureID; }
  inline int getCorpseID(int x, int y) { return cells[x + MAP_WIDTH*y].corpseID; }
  inline int getHideID(int x, int y) { return cells[x + MAP_WIDTH*y].hideID; }
  inline int getLocationID(int x, int y) { return cells[x + MAP_WIDTH*y].locationID; }

  inline bool getFirstVisit(int x, int y) { return cells[x + MAP_WIDTH*y].firstVisit; }
  inline void setFirstVisit(int x, int y, bool lvalue) { cells[x + MAP_WIDTH*y].firstVisit = lvalue; }

  inline float getScent(int x, int y) { return cells[x + MAP_WIDTH*y].scent; }
  inline void setScent(int x, int y, float scent) { cells[x + MAP_WIDTH*y].scent = scent; }
  inline float getOldScent(int x, int y) { return cells[x + MAP_WIDTH*y].oldScent; }
  inline void setOldScent(int x, int y, float oldScent) { cells[x + MAP_WIDTH*y].oldScent = oldScent; }

  inline bool getExplored(int x, int y) { return subcells[x + MAP_WIDTH2*y].isExplored; }
  inline void setExplored(int x, int y) { subcells[x + MAP_WIDTH2*y].isExplored = true; }

  inline bool getFov2xExplored(int x, int y) { return (getExplored(2*x, 2*y) || getExplored(2*x + 1, 2*y) || getExplored(2*x, 2*y + 1) || getExplored(2*x + 1, 2*y + 1)); }

  void addItem(int x, int y);
  void removeItem(int x, int y);

  void addCreature(int caveRegion, int x, int y);
  void removeCreature(int x, int y);
  void attackCreature(int x, int y);
  void updateCreatures(Player player, float elapsed);

  void addCorpse(int x, int y);
  void removeCorpse(int x, int y);

  void addHide(int x, int y, ECreatureType creatureType);
  void removeHide(int x, int y);

  void addLocation(int x, int y, const char *name, TCODColor colour, char sym);

  void setupScent();
  void updateScent(int x, int y);

  bool hasLos(int xFrom, int yFrom, int xTo, int yTo, bool ignoreCreatures);
};
