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

#include "main.hpp"

// The Default Equip Constructor
Equip::Equip() {}

// The Equip Constructor
Equip::Equip(const char name0[], const char label0[], const char desc0[],
             int hpmax0, int ap0, int dp0, int str0, int spd0,
             int mpmax0, int map0, int mdp0, int wil0, int acu0,
             float mass0, int price0): mass(mass0), price(price0)
{
  sprintf(name, "%s", name0);                // Name
  sprintf(label, "%s", label0);              // Label
  sprintf(desc, "%s", desc0);                // Description

  stats.hpmax = hpmax0;
  stats.hp = 0;
  stats.ap = ap0;
  stats.dp = dp0;
  stats.str = str0;
  stats.spd = spd0;
  stats.mpmax = mpmax0;
  stats.mp = 0;
  stats.map = map0;
  stats.mdp = mdp0;
  stats.wil = wil0;
  stats.acu = acu0;
}

// The Assignment Operator
Equip::Equip &Equip::operator= (const Equip &rhs)
{
  // Do the assignment work
  sprintf(this->name, "%s", rhs.name);       // Name
  sprintf(this->label, "%s", rhs.label);     // Label
  sprintf(this->desc, "%s", rhs.desc);       // Description
  this->stats = rhs.stats;
  this->mass  = rhs.mass;
  this->price = rhs.price;

  return *this;
}

// The Default Equipment Inventory Constructor
EquipInventory::EquipInventory()
{
  // Weapon List
  Weapons[WOODEN_SWORD] = Equip(
        "%cWooden Sword      %c", // Name
        "%cWeapon   %c :: ",      // Label
        "AP +2",                  // Description
        0,                        // HPMAX
        2, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.25f, 10);               // MASS, GP
  Weapons[BRONZE_SWORD] = Equip(
        "%cBronze Sword      %c", // Name
        "%cWeapon   %c :: ",      // Label
        "AP +4",                  // Description
        0,                        // HPMAX
        4, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.5f, 20);                // MASS, GP
  Weapons[IRON_SWORD] = Equip(
        "%cIron Sword        %c", // Name
        "%cWeapon   %c :: ",      // Label
        "AP +8",                  // Description
        0,                        // HPMAX
        8, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        2.0f, 50);                // MASS, GP
  Weapons[ICE_SWORD] = Equip(
        "%cIce Sword         %c", // Name
        "%cWeapon   %c :: ",      // Label
        "AP +10, MAP +2",         // Description
        0,                        // HPMAX
        10, 0,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        2, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        5.0f, 100);               // MASS, GP
  Weapons[FIRE_SWORD] = Equip(
        "%cFire Sword        %c", // Name
        "%cWeapon   %c :: ",      // Label
        "AP +10, MAP +2",         // Description
        0,                        // HPMAX
        10, 0,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        2, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        5.0f, 100);               // MASS, GP
  Weapons[MITHRIL_SWORD] = Equip(
        "%cMithril Sword     %c", // Name
        "%cWeapon   %c :: ",      // Label
        "AP +15, MAP +5",         // Description
        0,                        // HPMAX
        15, 0,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        5, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        10.0f, 500);              // MASS, GP
  Weapons[HYDRASLAYER_SWORD] = Equip(
        "%cHydraslayer Sword %c", // Name
        "%cWeapon   %c :: ",      // Label
        "AP +20, MAP +10",        // Description
        0,                        // HPMAX
        20, 0,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        10, 0,                    // MAP, MDP
        0, 0,                     // WIL, ACU
        12.0f, 750);              // MASS, GP
  Weapons[DRAGONSLAYER_SWORD] = Equip(
        "%cDragonslayer Sword%c", // Name
        "%cWeapon   %c :: ",      // Label
        "AP +25, MAP +15",        // Description
        0,                        // HPMAX
        25, 0,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        15, 0,                    // MAP, MDP
        0, 0,                     // WIL, ACU
        15.0f, 1000);             // MASS, GP
  Weapons[NO_SWORD] = Equip(
        "%cEmpty             %c", // Name
        "%cWeapon   %c :: ",      // Label
        "",                       // Description
        0,                        // HPMAX
        0, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.0f, 0);                 // MASS, GP

  // Shield List
  Shields[WOODEN_SHIELD] = Equip(
        "%cWooden Shield     %c", // Name
        "%cShield   %c :: ",      // Label
        "DP +2        ",          // Description
        0,                        // HPMAX
        0, 2,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.5f, 10);                // MASS, GP
  Shields[REINFORCED_SHIELD] = Equip(
        "%cReinforced Shield %c", // Name
        "%cShield   %c :: ",      // Label
        "DP +4        ",          // Description
        0,                        // HPMAX
        0, 4,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        1.0f, 20);                // MASS, GP
  Shields[LEATHER_SHIELD] = Equip(
        "%cLeather Shield    %c", // Name
        "%cShield   %c :: ",      // Label
        "DP +6        ",          // Description
        0,                        // HPMAX
        0, 6,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        2.0f, 50);                // MASS, GP
  Shields[BRONZE_SHIELD] = Equip(
        "%cBronze Shield     %c", // Name
        "%cShield   %c :: ",      // Label
        "DP +8        ",          // Description
        0,                        // HPMAX
        0, 8,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        5.0f, 100);               // MASS, GP
  Shields[IRON_SHIELD] = Equip(
        "%cIron Shield       %c", // Name
        "%cShield   %c :: ",      // Label
        "DP +10       ",          // Description
        0,                        // HPMAX
        0, 10,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        10.0f, 200);              // MASS, GP
  Shields[MITHRIL_SHIELD] = Equip(
        "%cMithril Shield    %c", // Name
        "%cShield   %c :: ",      // Label
        "DP +15, MDP +5",         // Description
        0,                        // HPMAX
        0, 15,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 5,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        12.0f, 500);              // MASS, GP
  Shields[HYDRASCALE_SHIELD] = Equip(
        "%cHydrascale Shield %c", // Name
        "%cShield   %c :: ",      // Label
        "DP +20, MDP +10",        // Description
        0,                        // HPMAX
        0, 20,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 10,                    // MAP, MDP
        0, 0,                     // WIL, ACU
        14.0f, 1000);             // MASS, GP
  Shields[DRAGONSCALE_SHEILD] = Equip(
        "%cDragonscale Shield%c", // Name
        "%cShield   %c :: ",      // Label
        "DP +25, MDP +15",        // Description
        0,                        // HPMAX
        0, 25,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 15,                    // MAP, MDP
        0, 0,                     // WIL, ACU
        18.0f, 1500);             // MASS, GP
  Shields[NO_SHIELD] = Equip(
        "%cEmpty             %c", // Name
        "%cShield   %c :: ",      // Label
        "",                       // Description
        0,                        // HPMAX
        0, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.0f, 0);                 // MASS, GP

  // Armour List
  Armours[COTTON_ARMOUR] = Equip(
        "%cCotton Tunic      %c", // Name
        "%cArmour   %c :: ",      // Label
        "DP +2        ",          // Description
        0,                        // HPMAX
        0, 2,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        1.0f, 20);                // MASS, GP
  Armours[PADDED_ARMOUR] = Equip(
        "%cPadded Armour     %c", // Name
        "%cArmour   %c :: ",      // Label
        "DP +4        ",          // Description
        0,                        // HPMAX
        0, 4,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        2.0f, 50);                // MASS, GP
  Armours[LEATHER_ARMOUR] = Equip(
        "%cLeather Armour    %c", // Name
        "%cArmour   %c :: ",      // Label
        "DP +6        ",          // Description
        0,                        // HPMAX
        0, 6,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        5.0f, 100);               // MASS, GP
  Armours[BRONZE_ARMOUR] = Equip(
        "%cBronze Armour     %c", // Name
        "%cArmour   %c :: ",      // Label
        "DP +8        ",          // Description
        0,                        // HPMAX
        0, 8,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        10.0f, 200);              // MASS, GP
  Armours[IRON_ARMOUR] = Equip(
        "%cIron Armour       %c", // Name
        "%cArmour   %c :: ",      // Label
        "DP +10       ",          // Description
        0,                        // HPMAX
        0, 10,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        15.0f, 500);              // MASS, GP
  Armours[MITHRIL_ARMOUR] = Equip(
        "%cMithril Armour    %c", // Name
        "%cArmour   %c :: ",      // Label
        "DP +15, MDP +5",         // Description
        0,                        // HPMAX
        0, 15,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 5,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        20.0f, 750);              // MASS, GP
  Armours[HYDRASCALE_ARMOUR] = Equip(

        "%cHydrascale Armour %c", // Name
        "%cArmour   %c :: ",      // Label
        "DP +20, MDP +10",        // Description
        0,                        // HPMAX
        0, 20,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 10,                    // MAP, MDP
        0, 0,                     // WIL, ACU
        25.0f, 1500);             // MASS, GP
  Armours[DRAGONSCALE_ARMOUR] = Equip(
        "%cDragonscale Armour%c", // Name
        "%cArmour   %c :: ",      // Label
        "DP +25, MDP +15",        // Description
        0,                        // HPMAX
        0, 25,                    // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 15,                    // MAP, MDP
        0, 0,                     // WIL, ACU
        30.0f, 2500);             // MASS, GP
  Armours[NO_ARMOUR] = Equip(
        "%cEmpty             %c", // Name
        "%cArmour   %c :: ",      // Label
        "",                       // Description
        0,                        // HPMAX
        0, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.0f, 0);                 // MASS, GP

  // Accessory List
  Accessory[RING_HP_PLUS] = Equip(
        "%cRing of Health    %c", // Name
        "%cAccessory%c :: ",      // Label
        "HP +10       ",          // Description
        10,                       // HPMAX
        0, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.1f, 150);               // MASS, GP
  Accessory[RING_MP_PLUS] = Equip(
        "%cRing of Magic     %c", // Name
        "%cAccessory%c :: ",      // Label
        "MP +10       ",          // Description
        0,                        // HPMAX
        0, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        10,                       // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.1f, 150);               // MASS, GP
  Accessory[RING_ATK_PLUS] = Equip(
        "%cRing of Attack    %c", // Name
        "%cAccessory%c :: ",      // Label
        "AP +2, MAP +2",          // Description
        0,                        // HPMAX
        2, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        2, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.1f, 150);               // MASS, GP
  Accessory[RING_DEF_PLUS] = Equip(
        "%cRing of Defense   %c", // Name
        "%cAccessory%c :: ",      // Label
        "DP +2, MDP +2",          // Description
        0,                        // HPMAX
        0, 2,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 2,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.1f, 150);               // MASS, GP
  Accessory[RING_STR_PLUS] = Equip(
        "%cRing of Strength  %c", // Name
        "%cAccessory%c :: ",      // Label
        "STR +2       ",          // Description
        0,                        // HPMAX
        0, 0,                     // AP, DP
        2, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.1f, 100);               // MASS, GP
  Accessory[RING_SPD_PLUS] = Equip(
        "%cRing of Speed     %c", // Name
        "%cAccessory%c :: ",      // Label
        "SPD +2       ",          // Description
        0,                        // HPMAX
        0, 0,                     // AP, DP
        0, 2,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.1f, 100);               // MASS, GP
  Accessory[RING_WIL_PLUS] = Equip(
        "%cRing of Willpower %c", // Name
        "%cAccessory%c :: ",      // Label
        "WIL +2       ",          // Description
        0,                        // HPMAX
        0, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        2, 0,                     // WIL, ACU
        0.1f, 100);               // MASS, GP
  Accessory[RING_ACU_PLUS] = Equip(
        "%cRing of Acuity    %c", // Name
        "%cAccessory%c :: ",      // Label
        "ACU +2       ",          // Description
        0,                        // HPMAX
        0, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 2,                     // WIL, ACU
        0.1f, 100);               // MASS, GP
  Accessory[NO_ACCESSORY] = Equip(
        "%cEmpty             %c", // Name
        "%cAccessory%c :: ",      // Label
        "",                       // Description
        0,                        // HPMAX
        0, 0,                     // AP, DP
        0, 0,                     // STR, SPD
        0,                        // MPMAX
        0, 0,                     // MAP, MDP
        0, 0,                     // WIL, ACU
        0.0f, 0);                 // MASS, GP

  // Initialize Equipment Inventory Mass
  mass = 0.0f;

  // Current Weapon
  equiped[WEAPON] = Weapons[WOODEN_SWORD];
//  equiped[WEAPON] = Weapons[NO_SWORD];
  mass += equiped[WEAPON].mass;

  // Current Shield
  equiped[SHIELD] = Shields[WOODEN_SHIELD];
//  equiped[SHIELD] = Shields[NO_SHIELD];
  mass += equiped[SHIELD].mass;

  // Current Armour
  equiped[ARMOUR] = Armours[COTTON_ARMOUR];
//  equiped[ARMOUR] = Armours[NO_ARMOUR];
  mass += equiped[ARMOUR].mass;

  // Current Accessory
//  equiped[ACCESSORY] = Accessory[RING_WIL_PLUS];
  equiped[ACCESSORY] = Accessory[NO_ACCESSORY];
  mass += equiped[ACCESSORY].mass;
}
