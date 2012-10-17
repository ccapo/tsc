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

enum EItem
{
  POTION_ELIXIR,
  POTION_HEALTH,
  POTION_HEALTH_STRONG,
  POTION_MAGIC,
  POTION_MAGIC_STRONG,
  POTION_POISON_ANTIDOTE,
  MUSHROOM_HEALTH,
  MUSHROOM_MAGIC,
  MUSHROOM_POISON,
  MUSHROOM_WEAKNESS,
  MUSHROOM_SLUGGISHNESS,
  MUSHROOM_FEEBLENESS,
  MUSHROOM_CONFUSION,
  MUSHROOM_UNKNOWN,
  NITEMS
};

// This class holds all the information about items
class Item
{
  public:
  char label[CHARMAX];        // Item Label
  char name[CHARMAX];         // Item Name
  char desc[CHARMAX];         // Item Description
  Stats stats;                // Item Stats
  int x, y;                   // Item Position
  TCODColor colour;           // Item Colour
  int sym;                   // Item Symbol
  float mass;                 // Item Mass
  float activeTime;           // Length of time an item is active
  bool inUse;                 // Item In Use flag

  Item();                     // The Default Item Constructor
  Item(const char label0[], const char name0[], const char desc0[],
       int hp0, int str0, int spd0, int mp0, int wil0, int acu0,
       float mass0, float activeTime0);
  void render();              // Render Item
};

// This class holds all the information the item inventory
class ItemInventory
{
  public:
  int maxCount[NITEMS];       // Max. Number of Each Item
  int count[NITEMS];          // Quantity of Each Item
  int index[NITEMS];          // Item index
  int minPrice[NITEMS];       // Min. Price of Each Item
  int maxPrice[NITEMS];       // Max. Price of Each Item
  int price[NITEMS];          // Price of Each Item
  int productionRate[NITEMS]; // Production Rate of Each Item
  int nitems;                 // Number of available Items (i.e. sum(count > 0))
  float mass;                 // Mass of Item Inventory

  Item items[NITEMS];         // Item List

  ItemInventory();            // The Item Inventory Constructor
};
