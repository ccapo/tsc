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

#include "main.hpp"

// The Default Item Constructor
Item::Item(): x(0), y(0), colour(TCODColor::white), sym(CHAR_MUSHROOM),
              mass(0.1f), activeTime(0.0f), inUse(false)
{
  sprintf(label, "%s", "Unknown Mushroom");              // Label
  sprintf(name, "%s",  "%cUnknown Mushroom         %c"); // Name
  sprintf(desc, "%s",  "Unidentified Mushroom");         // Description

  stats.hpmax = 0;
  stats.hp = 0;
  stats.ap = 0;
  stats.dp = 0;
  stats.str = 0;
  stats.spd = 0;
  stats.mpmax = 0;
  stats.mp = 0;
  stats.map = 0;
  stats.mdp = 0;
  stats.wil = 0;
  stats.acu = 0;
}

// The Item Constructor
Item::Item(const char label0[], const char name0[], const char desc0[],
           int hp0, int str0, int spd0, int mp0, int wil0, int acu0,
           float mass0, float activeTime0): x(0), y(0), colour(TCODColor::white), sym(CHAR_MUSHROOM),
                                            mass(mass0), activeTime(activeTime0), inUse(true)
{
  sprintf(label, "%s", label0); // Label
  sprintf(name, "%s",  name0);  // Name
  sprintf(desc, "%s",  desc0);  // Description

  stats.hpmax = 0;
  stats.hp = hp0;
  stats.ap = 0;
  stats.dp = 0;
  stats.str = str0;
  stats.spd = spd0;
  stats.mpmax = 0;
  stats.mp = mp0;
  stats.map = 0;
  stats.mdp = 0;
  stats.wil = wil0;
  stats.acu = acu0;
}

// Render Item
void Item::render()
{
  CaveMap *cmap = &game.caves[game.caveID];

  if(inUse)
  {
    int cx = x - cmap->display_x, cy = y + 3 - cmap->display_y;
    int dx = x - game.player.x, dy = y - game.player.y, dr = sqrt(dx*dx + dy*dy);
    if(dr < static_cast<int>(TORCH_RADIUS/2.0f) && cmap->getFov2xExplored(x, y))
    {
      if(cmap->getFov2x(x, y))
      {
        TCODConsole::root->setDefaultForeground(colour);
        TCODConsole::root->putChar(cx, cy, sym, TCOD_BKGND_NONE);
      }
      else
      {
        TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
        TCODConsole::root->putChar(cx, cy, '?', TCOD_BKGND_NONE);
      }
    }
    else if(dr < static_cast<int>(TORCH_RADIUS) && cmap->getFov2xExplored(x, y))
    {
      TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
      TCODConsole::root->putChar(cx, cy, '?', TCOD_BKGND_NONE);
    }
  }
}

// The Default Item Inventory Constructor
ItemInventory::ItemInventory(void)
{
  // Item List
  items[POTION_ELIXIR] = Item(
        "Elixir",                           // Label
        "%cElixir                  %c",     // Name
        "Fully Restores HP, MP and Status", // Description
        1000,                               // HP
        0, 0,                               // STR, SPD
        1000,                               // MP
        0, 0,                               // WIL, ACU
        0.25f, 0.0f);                       // Mass, Active Time
  items[POTION_HEALTH] = Item(
        "Health Potion",                    // Label
        "%cHealth Potion           %c",     // Name
        "Restores Health by 10 HP",         // Description
        10,                                 // HP
        0, 0,                               // STR, SPD
        0,                                  // MP
        0, 0,                               // WIL, ACU
        0.1f, 0.0f);                        // Mass, Active Time
  items[POTION_HEALTH_STRONG] = Item(
        "Strong Health Potion",             // Label
        "%cStrong Health Potion    %c",     // Name
        "Restores Health by 50 HP",         // Description
        50,                                 // HP
        0, 0,                               // STR, SPD
        0,                                  // MP
        0, 0,                               // WIL, ACU
        0.1f, 0.0f);                        // Mass, Active Time
  items[POTION_MAGIC] = Item(
        "Magic Potion",                     // Label
        "%cMagic Potion            %c",     // Name
        "Restores Magic by 5 MP",           // Description
        0,                                  // HP
        0, 0,                               // STR, SPD
        5,                                  // MP
        0, 0,                               // WIL, ACU
        0.1f, 0.0f);                        // Mass, Active Time
  items[POTION_MAGIC_STRONG] = Item(
        "Strong Magic Potion",              // Label
        "%cStrong Magic Potion     %c",     // Name
        "Restores Magic by 25 MP",          // Description
        0,                                  // HP
        0, 0,                               // STR, SPD
        25,                                 // MP
        0, 0,                               // WIL, ACU
        0.1f, 0.0f);                        // Mass, Active Time
  items[POTION_POISON_ANTIDOTE] = Item(
        "Poison Antidote",                  // Label
        "%cPoison Antidote         %c",     // Name
        "Heals Poison",                     // Description
        0,                                  // HP
        0, 0,                               // STR, SPD
        0,                                  // MP
        0, 0,                               // WIL, ACU
        0.1f, 0.0f);                        // Mass, Active Time
  items[MUSHROOM_HEALTH] = Item(
        "Mushroom of Health",               // Label
        "%cMushroom of Health      %c",     // Name
        "Restores Health by 10 HP",         // Description
        10,                                 // HP
        0, 0,                               // STR, SPD
        0,                                  // MP
        0, 0,                               // WIL, ACU
        0.1f, 0.0f);                        // Mass, Active Time
  items[MUSHROOM_MAGIC] = Item(
        "Mushroom of Magic",                // Label
        "%cMushroom of Magic       %c",     // Name
        "Restores Magic by 5 MP",           // Description
        0,                                  // HP
        0, 0,                               // STR, SPD
        5,                                  // MP
        0, 0,                               // WIL, ACU
        0.1f, 0.0f);                        // Mass, Active Time
  items[MUSHROOM_POISON] = Item(
        "Mushroom of Poison",               // Label
        "%cMushroom of Poison      %c",     // Name
        "Poisons Health, HP -2",            // Description
        -2,                                 // HP
        0, 0,                               // STR, SPD
        0,                                  // MP
        0, 0,                               // WIL, ACU
        0.1f, 120.0f);                      // Mass, Active Time
  items[MUSHROOM_WEAKNESS] = Item(
        "Mushroom of Weakness",             // Label
        "%cMushroom of Weakness    %c",     // Name
        "Diminishes Strength, STR -2",      // Description
        0,                                  // HP
        -2, 0,                              // STR, SPD
        0,                                  // MP
        0, 0,                               // WIL, ACU
        0.1f, 120.0f);                      // Mass, Active Time
  items[MUSHROOM_SLUGGISHNESS] = Item(
        "Mushroom of Sluggishness",         // Label
        "%cMushroom of Sluggishness%c",     // Name
        "Reduces Speed, SPD -2",            // Description
        0,                                  // HP
        0, -2,                              // STR, SPD
        0,                                  // MP
        0, 0,                               // WIL, ACU
        0.1f, 120.0f);                      // Mass, Active Time
  items[MUSHROOM_FEEBLENESS] = Item(
        "Mushroom of Feebleness",           // Label
        "%cMushroom of Feebleness  %c",     // Name
        "Diminishes Willpower, WIL -2",     // Description
        0,                                  // HP
        0, 0,                               // STR, SPD
        0,                                  // MP
        -2, 0,                              // WIL, ACU
        0.1f, 120.0f);                      // Mass, Active Time
  items[MUSHROOM_CONFUSION] = Item(
        "Mushroom of Confusion",            // Label
        "%cMushroom of Confusion   %c",     // Name
        "Reduces Acuity, ACU -2",           // Description
        0,                                  // HP
        0, 0,                               // STR, SPD
        0,                                  // MP
        0, -2,                              // WIL, ACU
        0.1f, 120.0f);                      // Mass, Active Time
  items[MUSHROOM_UNKNOWN] = Item(
        "Unknown Mushroom",                 // Label
        "%cUnknown Mushroom        %c",     // Name
        "Unidentified Mushroom",            // Description
        0,                                  // HP
        0, 0,                               // STR, SPD
        0,                                  // MP
        0, 0,                               // WIL, ACU
        0.1f, 0.0f);                        // Mass, Active Time

  // Initialize item inventory mass
  mass = 0.0f;
  nitems = 0;

//  for(int i = 0; i < NITEMS; i++)
//  {
//    count[i] = 1;                           // Quantity of Each Item
//    mass += count[i]*items[i].mass;         // Mass of Inventory
//    index[i] = i;                           // Item index
//    nitems++;                               // Number of available Items
//  }

//  count[MUSHROOM_UNKNOWN] = 1;
//  mass += count[MUSHROOM_UNKNOWN]*items[MUSHROOM_UNKNOWN].mass;
//  index[nitems++] = MUSHROOM_UNKNOWN;

  count[POTION_HEALTH] = 2;
  mass += count[POTION_HEALTH]*items[POTION_HEALTH].mass;
  index[nitems++] = POTION_HEALTH;

  count[MUSHROOM_HEALTH] = 2;
  mass += count[MUSHROOM_HEALTH]*items[MUSHROOM_HEALTH].mass;
  index[nitems++] = MUSHROOM_HEALTH;
}
