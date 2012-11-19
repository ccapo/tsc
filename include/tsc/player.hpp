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

// The class that holds information about the player
class Player
{
  public:
  Stats base;                                   // Player's Base Stats
  Stats stats;                                  // Player's Current Stats
  int hp, mp;                                   // Player's Current HP and MP
  Health health;                                // Player's Health Status
  int lvl;                                      // Player's Level
  int xp, xpnext;                               // Experience Points, Experience Points for Next Level
  int x, y;                                     // Player Position
  TCODColor colour;                             // Player Colour
  int sym;                                      // Player Symbol
  int sym_up;                                   // Player Symbol
  int sym_down;                                 // Player Symbol
  int sym_left;                                 // Player Symbol
  int sym_right;                                // Player Symbol
  int gp;                                       // Player Gold Points
  float displacement;                           // Player's Displacement
  float magicTimer;                             // Player's Magic Timer
  float hitFlashTimer;                          // Player's Hit Flash Timer
  TCODPath *path;                               // Player's path object

  ItemInventory itemInv;                        // Item Inventory
  EquipInventory equipInv;                      // Equipment Inventory
  HideInventory hideInv;                        // Hide Inventory

  Player();                                     // Player Constructor

  void update(float elapsed, TCOD_key_t *key, TCOD_mouse_t mouse);  // Update Player
  void render();                                // Render Player

  void updateStats();                           // Update Player stats
  void updateStatus();                          // Update Player status
  void takeDamage(Creature cr);                 // Player Take Damage

  // World and Cave Maps
  void actionWorldMap();                        // Player Action on the World Map
  void exitWorldLocation();                     // Player Exits a World Location
  void exitCaveLocation();                      // Player Exits a Cave Location
  void takeFerry(int id);                       // Player Takes a Ferry to Location id
  void stayInn();                               // Player Stays at the Inn

  void hitFlash();                              // Update flash timer when the Player is hit

  // Item Inventory
  bool addItem(int itemIndex);                  // Method to add a specified item to inventory
  void useItem(int *cursorIndex);               // Method to use a specified item from inventory
  void buyItem(int *cursorIndex);               // Method to buy a specified item from town inventory
  void sellItem(int *cursorIndex);              // Method to sell a specified item to town inventory

  // Equipment Inventory
  void changeEquipment(int iEquip, int index);  // Method to Change Equipment

  // Hide Inventory
  bool addHide(int hideIndex);                  // Method to add a specified hide to inventory
  void sellHide(int *cursorIndex);              // Method to sell a specified hide to town inventory

  int xpLevel(int level);                       // XP for a given level
  int hpLevel(int level);                       // Max. HP for a given level
  int apLevel(int level);                       // AP for a given level
  int dpLevel(int level);                       // DP for a given level
  int strLevel(int level);                      // STR for a given level
  int spdLevel(int level);                      // SPD for a given level
  int mpLevel(int level);                       // Max. MP for a given level
  int mapLevel(int level);                      // MAP for a given level
  int mdpLevel(int level);                      // MDP for a given level
  int wilLevel(int level);                      // WIL for a given level
  int acuLevel(int level);                      // ACU for a given level
};
