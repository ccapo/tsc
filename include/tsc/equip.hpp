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
// Mingos' noise demo 2
// Copyright (c) 2010 Dominik Marczuk
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Dominik Marczuk may not be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "global.hpp"

enum EEquipType
{
  WEAPON,
  SHIELD,
  ARMOUR,
  ACCESSORY,
  NEQUIPTYPE
};

enum EWeapon
{
  WOODEN_SWORD,
  BRONZE_SWORD,
  IRON_SWORD,
  ICE_SWORD,
  FIRE_SWORD,
  MITHRIL_SWORD,
  HYDRASLAYER_SWORD,
  DRAGONSLAYER_SWORD,
  NO_SWORD,
  NWEAPON
};

enum EShield
{
  WOODEN_SHIELD,
  REINFORCED_SHIELD,
  LEATHER_SHIELD,
  BRONZE_SHIELD,
  IRON_SHIELD,
  MITHRIL_SHIELD,
  HYDRASCALE_SHIELD,
  DRAGONSCALE_SHEILD,
  NO_SHIELD,
  NSHIELD
};

enum EArmour
{
  COTTON_ARMOUR,
  PADDED_ARMOUR,
  LEATHER_ARMOUR,
  BRONZE_ARMOUR,
  IRON_ARMOUR,
  MITHRIL_ARMOUR,
  HYDRASCALE_ARMOUR,
  DRAGONSCALE_ARMOUR,
  NO_ARMOUR,
  NARMOUR
};

enum EAccessory
{
  RING_HP_PLUS,
  RING_MP_PLUS,
  RING_ATK_PLUS,
  RING_DEF_PLUS,
  RING_STR_PLUS,
  RING_SPD_PLUS,
  RING_WIL_PLUS,
  RING_ACU_PLUS,
  NO_ACCESSORY,
  NACCESSORY
};

// This class holds all the information about equipment
class Equip
{
  public:
  char name[CHARMAX];                  // Equipment Name
  char label[CHARMAX];                 // Equipment Label
  char desc[CHARMAX];                  // Equipment Description
  Stats stats;                         // Equipment Stats
  int hp, mp;                          // Equipment HP and MP
  float mass;                          // Equipment Mass
  int price;                           // Equipment Price

  Equip();                             // The Default Equipment Constructor
  Equip(const char name0[], const char label0[], const char desc0[],
        int hpmax0, int ap0, int dp0, int str0, int spd0,
        int mpmax0, int map0, int mdp0, int wil0, int acu0,
        float mass0, int price0);
  Equip &operator= (const Equip &rhs); // The Assignment Operator
};

// This class holds all the information about the equipment inventory
class EquipInventory
{
  public:
  Equip equiped[NEQUIPTYPE];           // Current Equipment
  float mass;                          // Mass of Equipment Inventory

  Equip Weapons[NWEAPON];              // Weapon List
  Equip Shields[NSHIELD];              // Shield List
  Equip Armours[NARMOUR];              // Armour List
  Equip Accessory[NACCESSORY];         // Accessory List

  EquipInventory();                    // The Equipment Inventory Constructor
};
