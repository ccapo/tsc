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

// The default creature constructor
Creature::Creature(): lvl(1), x(0), y(0), creatureType(CREATURETYPE_INSECT), colour(TCODColor::yellow), sym('i'), walkTimer(1.0f), inUse(false)
{
  sprintf(name, "%s", "Yellow Insect");
  //path = NULL;
}

// The creature constructor
Creature::Creature(int x0, int y0, ECreatureType creatureType0): x(x0), y(y0), creatureType(creatureType0), walkTimer(1.0f), inUse(true)
{
  switch(creatureType)
  {
    case CREATURETYPE_INSECT:
    {
      sprintf(name, "%s", "Yellow Insect");           // Name
      lvl = 1;                                        // Level
      stats.hpmax = 5; stats.mpmax = 0;               // Max. HP, Max. MP
      stats.hp = stats.hpmax; stats.mp = stats.mpmax; // HP, MP
      stats.spd = 4;                                  // SPD
      colour = TCODColor::yellow; sym = 'i';          // Colour, Symbol
      break;
    }
    case CREATURETYPE_VERMIN:
    {
      sprintf(name, "%s", "Brown Vermin");            // Name
      lvl = 1;                                        // Level
      stats.hpmax = 10; stats.mpmax = 0;              // Max. HP, Max. MP
      stats.hp = stats.hpmax; stats.mp = stats.mpmax; // HP, MP
      stats.spd = 4;                                  // SPD
      colour = TCODColor::lightestSepia; sym = 'v';   // Colour, Symbol
      break;
    }
    case CREATURETYPE_REPTILE:
    {
      sprintf(name, "%s", "Green Lizard");            // Name
      lvl = 1;                                        // Level
      stats.hpmax = 15; stats.mpmax = 0;              // Max. HP, Max. MP
      stats.hp = stats.hpmax; stats.mp = stats.mpmax; // HP, MP
      stats.spd = 4;                                  // SPD
      colour = TCODColor::green; sym = 'L';           // Colour, Symbol
      break;
    }
    case CREATURETYPE_BEAST:
    {
      sprintf(name, "%s", "Blue Beast");              // Name
      lvl = 2;                                        // Level
      stats.hpmax = 20; stats.mpmax = 0;              // Max. HP, Max. MP
      stats.hp = stats.hpmax; stats.mp = stats.mpmax; // HP, MP
      stats.spd = 8;                                  // SPD
      colour = TCODColor::blue; sym = 'B';            // Colour, Symbol
      break;
    }
    case CREATURETYPE_TROGLODYTE:
    {
      sprintf(name, "%s", "Green Troglodyte");        // Name
      lvl = 5;                                        // Level
      stats.hpmax = 30; stats.mpmax = 0;              // Max. HP, Max. MP
      stats.hp = stats.hpmax; stats.mp = stats.mpmax; // HP, MP
      stats.spd = 6;                                  // SPD
      colour = TCODColor::darkGreen; sym = 'T';       // Colour, Symbol
      break;
    }
    case CREATURETYPE_GIANT:
    {
      sprintf(name, "%s", "Orange Giant");            // Name
      lvl = 10;                                       // Level
      stats.hpmax = 50; stats.mpmax = 0;              // Max. HP, Max. MP
      stats.hp = stats.hpmax; stats.mp = stats.mpmax; // HP, MP
      stats.spd = 4;                                  // SPD
      colour = TCODColor::orange; sym = 'G';          // Colour, Symbol
      break;
    }
    case CREATURETYPE_SPECIAL:
    {
      sprintf(name, "%s", "Hunter-Seeker");           // Name
      lvl = 15;                                       // Level
      stats.hpmax = 65; stats.mpmax = 10;             // Max. HP, Max. MP
      stats.hp = stats.hpmax; stats.mp = stats.mpmax; // HP, MP
      stats.spd = 10;                                 // SPD
      colour = TCODColor::red; sym = 'H';             // Colour, Symbol
      break;
    }
    default: break;
  }
  //path = NULL;
}

// Update Creature stats
void Creature::updateStats()
{
  // Ensure stats stay within acceptable limits
  stats.hp  = CLAMP(0, stats.hpmax, stats.hp);
  stats.ap  = CLAMP(0, APMAX, stats.ap);
  stats.dp  = CLAMP(0, DPMAX, stats.dp);
  stats.str = CLAMP(0, STRMAX, stats.str);
  stats.spd = CLAMP(0, SPDMAX, stats.spd);
  stats.mp  = CLAMP(0, stats.mpmax, stats.mp);
  stats.map = CLAMP(0, MAPMAX, stats.map);
  stats.mdp = CLAMP(0, MDPMAX, stats.mdp);
  stats.wil = CLAMP(0, WILMAX, stats.wil);
  stats.acu = CLAMP(0, ACUMAX, stats.acu);
}

void Creature::chasePlayer(CaveMap *cmap, Player player)
{
  const int dx[NBORDER] = {-1, 0, 1, -1, 1, -1, 0, 1};
  const int dy[NBORDER] = {-1, -1, -1, 0, 0, 1, 1, 1};

  // Chase the player's scent
  bool scentFound = false;
  int xnew = x, ynew = y;
  float maxScent = 0.0f;
  for(int z = 0; z < NBORDER; z++)
  {
    int xz = x + dx[z], yz = y + dy[z];
    float scent = cmap->getScent(xz, yz);
    bool atPlayer = xz == player.x && yz == player.y;
    bool atCreature = cmap->getCreatureID(xz, yz) >= 0;
    bool atTunnelUp = xz == cmap->upx && yz == cmap->upy;
    bool atTunnelDown = xz == cmap->downx && yz == cmap->downy;
    bool isWalkable = cmap->isFov1xWalkable(xz, yz);
    if(scent > maxScent && isWalkable && !atPlayer && !atCreature && !atTunnelUp && !atTunnelDown)
    {
      maxScent = scent;
      xnew = xz; ynew = yz;
      scentFound = true;
    }
  }

  // If didn't find any scent, move in a random direction
  if(!scentFound)
  {
    int z = game.rng->getInt(0, 7);
    xnew = x + dx[z]; ynew = y + dy[z];
    bool atPlayer = xnew == player.x && ynew == player.y;
    bool atCreature = cmap->getCreatureID(xnew, ynew) >= 0;
    bool atTunnelUp = xnew == cmap->upx && ynew == cmap->upy;
    bool atTunnelDown = xnew == cmap->downx && ynew == cmap->downy;
    bool isWalkable = cmap->isFov1xWalkable(xnew, ynew);
    if(isWalkable && !atPlayer && !atCreature && !atTunnelUp && !atTunnelDown)
    {
      int creatureID = cmap->cells[x + MAP_WIDTH*y].creatureID;
      cmap->cells[x + MAP_WIDTH*y].creatureID = -1;
      x = xnew; y = ynew;
      cmap->cells[x + MAP_WIDTH*y].creatureID = creatureID;
    }
  }
  else
  {
    int creatureID = cmap->cells[x + MAP_WIDTH*y].creatureID;
    cmap->cells[x + MAP_WIDTH*y].creatureID = -1;
    x = xnew; y = ynew;
    cmap->cells[x + MAP_WIDTH*y].creatureID = creatureID;
  }
}

void Creature::avoidPlayer(CaveMap *cmap, Player player)
{
  const int dx[NBORDER] = {-1, 0, 1, -1, 1, -1, 0, 1};
  const int dy[NBORDER] = {-1, -1, -1, 0, 0, 1, 1, 1};

  // Avoid the player's scent
  int xnew = x, ynew = y;
  float minScent = 100.0f;
  for(int z = 0; z < NBORDER; z++)
  {
    int xz = x + dx[z], yz = y + dy[z];
    float scent = cmap->getScent(xz, yz);
    bool atPlayer = xz == player.x && yz == player.y;
    bool atCreature = cmap->getCreatureID(xz, yz) >= 0;
    bool atTunnelUp = xz == cmap->upx && yz == cmap->upy;
    bool atTunnelDown = xz == cmap->downx && yz == cmap->downy;
    bool isWalkable = cmap->isFov1xWalkable(xz, yz);
    if(scent < minScent && isWalkable && !atPlayer && !atCreature && !atTunnelUp && !atTunnelDown)
    {
      minScent = scent;
      xnew = xz; ynew = yz;
    }
  }

  // Move away from the player, otherwise don't move
  int creatureID = cmap->cells[x + MAP_WIDTH*y].creatureID;
  cmap->cells[x + MAP_WIDTH*y].creatureID = -1;
  x = xnew; y = ynew;
  cmap->cells[x + MAP_WIDTH*y].creatureID = creatureID;
}

// Update Creature
void Creature::update(Player player, float elapsed)
{
  CaveMap *cmap = &game.caves[game.caveID];

  if(inUse)
  {
    // Increment walk timer
    walkTimer += elapsed;

    if(walkTimer*static_cast<float>(stats.spd) >= 1.0f)
    {
      walkTimer = 0.0f;

      switch(creatureType)
      {
        case CREATURETYPE_INSECT:
        {
          // Avoid the player's scent
          avoidPlayer(cmap, player);
          break;
        }
        case CREATURETYPE_VERMIN:
        {
          // Avoid the player's scent
          avoidPlayer(cmap, player);

          break;
        }
        case CREATURETYPE_REPTILE:
        {
          if(stats.hp > stats.hpmax/2)
          {
            // Chase the player's scent
            chasePlayer(cmap, player);
          }
          else
          {
            // Avoid the player's scent
            avoidPlayer(cmap, player);
          }
          break;
        }
        case CREATURETYPE_BEAST:
        {
          if(stats.hp > stats.hpmax/4)
          {
            // Chase the player's scent
            chasePlayer(cmap, player);
          }
          else
          {
            // Avoid the player's scent
            avoidPlayer(cmap, player);
          }
          break;
        }
        case CREATURETYPE_TROGLODYTE:
        {
          // Chase the player's scent
          chasePlayer(cmap, player);
          break;
        }
        case CREATURETYPE_GIANT:
        {
          // Chase the player's scent
          chasePlayer(cmap, player);
          break;
        }
        case CREATURETYPE_SPECIAL:
        {
          // Chase the player's scent
          chasePlayer(cmap, player);
          break;
        }
        default: break;
      }
    }
  }
}

// Render Creature
void Creature::render(Player player)
{
  CaveMap *cmap = &game.caves[game.caveID];

  if(inUse)
  {
    int cx = x - cmap->display_x, cy = y + 3 - cmap->display_y;
    int dx = x - player.x, dy = y - player.y, dr = sqrt(dx*dx + dy*dy);
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

// The default corpse constructor
Corpse::Corpse(): x(0), y(0), colour(TCODColor::lightGrey), sym('%'), inUse(false) {}

// The corpse constructor
Corpse::Corpse(int x0, int y0): x(x0), y(y0), colour(TCODColor::lightGrey), sym('%'), inUse(true) {}

// Render Corpse
void Corpse::render(Player player)
{
  CaveMap *cmap = &game.caves[game.caveID];

  if(inUse)
  {
    int cx = x - cmap->display_x, cy = y + 3 - cmap->display_y;
    int dx = x - player.x, dy = y - player.y, dr = sqrt(dx*dx + dy*dy);
    if(dr < static_cast<int>(TORCH_RADIUS/2.0f) && cmap->getFov2xExplored(x, y))
    {
      if(cmap->getFov2x(x, y))
      {
        TCODConsole::root->setDefaultForeground(colour);
        TCODConsole::root->putChar(cx, cy, sym, TCOD_BKGND_NONE);
      }
      else
      {
        TCODConsole::root->setDefaultForeground(colour);
        TCODConsole::root->putChar(cx, cy, '?', TCOD_BKGND_NONE);
      }
    }
    else if(dr < static_cast<int>(TORCH_RADIUS) && cmap->getFov2xExplored(x, y))
    {
      TCODConsole::root->setDefaultForeground(colour);
      TCODConsole::root->putChar(cx, cy, '?', TCOD_BKGND_NONE);
    }
  }
}

// The default hide constructor
Hide::Hide(): x(0), y(0), creatureType(CREATURETYPE_INSECT), colour(TCODColor::lightRed), sym('%'), mass(0.0f), inUse(false) {}

// The hide constructor
Hide::Hide(int x0, int y0, ECreatureType creatureType0): x(x0), y(y0), creatureType(creatureType0), colour(TCODColor::lightRed), sym('%'), inUse(true)
{
  switch(creatureType)
  {
    case CREATURETYPE_INSECT:
    {
      sprintf(label, "%s", "Insect Carapace");    // Label
      sprintf(name, "%s", "%cInsect Carapace          %c");  // Name
      mass = 0.1f;          // Mass
      break;
    }
    case CREATURETYPE_VERMIN:
    {
      sprintf(label, "%s", "Vermin Pelt");      // Label
      sprintf(name, "%s", "%cVermin Pelt              %c");  // Name
      mass = 0.1f;          // Mass
      break;
    }
    case CREATURETYPE_REPTILE:
    {
      sprintf(label, "%s", "Reptile Hide");      // Label
      sprintf(name, "%s", "%cReptile Hide             %c");  // Name
      mass = 0.1f;          // Mass
      break;
    }
    case CREATURETYPE_BEAST:
    {
      sprintf(label, "%s", "Beast Hide");      // Label
      sprintf(name, "%s", "%cBeast Hide               %c");  // Name
      mass = 0.15f;          // Mass
      break;
    }
    case CREATURETYPE_TROGLODYTE:
    {
      sprintf(label, "%s", "Troglodyte Hide");    // Label
      sprintf(name, "%s", "%cTroglodyte Hide          %c");  // Name
      mass = 0.25f;          // Mass
      break;
    }
    case CREATURETYPE_GIANT:
    {
      sprintf(label, "%s", "Giant Hide");      // Label
      sprintf(name, "%s", "%cGiant Hide               %c");  // Name
      mass = 0.5f;          // Mass
      break;
    }
    case CREATURETYPE_SPECIAL:
    {
      sprintf(label, "%s", "Rare Hide");      // Label
      sprintf(name, "%s", "%cRare Hide                %c");  // Name
      mass = 0.5f;          // Mass
      break;
    }
    default: break;
  }
}

// Render Hide
void Hide::render(Player player)
{
  CaveMap *cmap = &game.caves[game.caveID];

  if(inUse)
  {
    int cx = x - cmap->display_x, cy = y + 3 - cmap->display_y;
    int dx = x - player.x, dy = y - player.y, dr = sqrt(dx*dx + dy*dy);
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

// The Default Hide Inventory Constructor
HideInventory::HideInventory(void)
{
  // Hide List                          x  y  Creature Type
  hides[CREATURETYPE_INSECT]     = Hide(0, 0, CREATURETYPE_INSECT);
  hides[CREATURETYPE_VERMIN]     = Hide(0, 0, CREATURETYPE_VERMIN);
  hides[CREATURETYPE_REPTILE]    = Hide(0, 0, CREATURETYPE_REPTILE);
  hides[CREATURETYPE_BEAST]      = Hide(0, 0, CREATURETYPE_BEAST);
  hides[CREATURETYPE_TROGLODYTE] = Hide(0, 0, CREATURETYPE_TROGLODYTE);
  hides[CREATURETYPE_GIANT]      = Hide(0, 0, CREATURETYPE_GIANT);
  hides[CREATURETYPE_SPECIAL]    = Hide(0, 0, CREATURETYPE_SPECIAL);

  // Initialize item inventory mass
  mass = 0.0f;
  nhides = 0;

//  for(int i = 0; i < NCREATURETYPES; i++)
//  {
//    count[i] = 1;                   // Quantity of Each Hide
//    mass += count[i]*hides[i].mass; // Mass of Inventory
//    index[i] = i;                   // Hide index
//    nhides++;                       // Number of available Hides
//  }
}

// The default Npc constructor
Npc::Npc(): x(0), y(0), spd(3), npcType(NPCTYPE_TOWNSPERSON), colour(TCODColor::lightSepia), sym('@'), walkTimer(1.0f), inUse(false)
{
  sprintf(label, "%s", "Townsperson");
  path = NULL;
}

// The Npc constructor
Npc::Npc(int x0, int y0, int spd0, ENpcType npcType0): x(x0), y(y0), spd(spd0), npcType(npcType0), sym('@'), walkTimer(1.0f), inUse(true)
{
  switch(npcType)
  {
    case NPCTYPE_LIGHTGUARDIAN:
    {
      sprintf(label, "%s", "Guardian of Light");
      colour = TCODColor::lighterYellow;
      break;
    }
    case NPCTYPE_FIREGUARDIAN:
    {
      sprintf(label, "%s", "Guardian of Fire");
      colour = TCODColor::red;
      break;
    }
    case NPCTYPE_WATERGUARDIAN:
    {
      sprintf(label, "%s", "Guardian of Water");
      colour = TCODColor::blue;
      break;
    }
    case NPCTYPE_WINDGUARDIAN:
    {
      sprintf(label, "%s", "Guardian of Wind");
      colour = TCODColor::yellow;
      break;
    }
    case NPCTYPE_EARTHGUARDIAN:
    {
      sprintf(label, "%s", "Guardian of Earth");
      colour = TCODColor::green;
      break;
    }
    case NPCTYPE_ITEMSHOPKEEPER:
    {
      sprintf(label, "%s", "Item Shopkeeper");
      colour = TCODColor::lightBlue;
      break;
    }
    case NPCTYPE_EQUIPSHOPKEEPER:
    {
      sprintf(label, "%s", "Equipment Shopkeeper");
      colour = TCODColor::lightBlue;
      break;
    }
    case NPCTYPE_INNKEEPER:
    {
      sprintf(label, "%s", "Innkeeper");
      colour = TCODColor::lightYellow;
      break;
    }
    case NPCTYPE_FERRYMAN:
    {
      sprintf(label, "%s", "Ferryman");
      colour = TCODColor::darkerSepia;
      break;
    }
    case NPCTYPE_TOWNSPERSON:
    {
      //sprintf(label, "%s", "Townsperson");
      sprintf(label, "%s", NameGenerator::generateFantasyName(game.rng, game.rng->getInt(0, 1) == 0));
      colour = TCODColor::darkSepia;
      break;
    }
    default: break;
  }
  path = NULL;
}

// Update Npc
void Npc::update(Player player, float elapsed)
{
  WorldMap *wmap = &game.world[game.worldID];

  if(inUse)
  {
    if(IN_RECTANGLE(x, y + 3, DISPLAY_WIDTH, DISPLAY_HEIGHT))
    {
      // Increment walk timer
      walkTimer += elapsed;

      if(walkTimer*static_cast<float>(spd) >= 1.0f)
      {
        walkTimer = 0.0f;

        if(path)
        {
          if(!path->isEmpty())
          {
            int xnew, ynew;
            path->get(0, &xnew, &ynew);
            bool atPlayer = xnew == player.x && ynew == player.y;
            bool atNpc = wmap->getNpcID(xnew, ynew) >= 0;
            bool isWalkable = path->walk(&xnew, &ynew, true) && !atPlayer && !atNpc;
            if(isWalkable)
            {
              int npcID = wmap->cells[x + IMAGE_WIDTH*y].creatureID;
              wmap->cells[x + IMAGE_WIDTH*y].creatureID = -1;
              x = xnew; y = ynew;
              wmap->cells[x + IMAGE_WIDTH*y].creatureID = npcID;
            }
          }
          else
          {
            delete path;
            path = NULL;
            walkTimer = -12.0f*elapsed;
          }
        }
        else
        {
          path = new TCODPath(wmap->fov1x);
          int dice = game.rng->getInt(1, 100);
          int dx, dy;
          if(dice < 15)
          {
            // Visit the item shop 15% of the time
            dx = wmap->npcs[0].x + 2;
            dy = wmap->npcs[0].y;
          }
          else if(dice >= 15 && dice < 20)
          {
            // Visit the equip shop 5% of the time
            dx = wmap->npcs[1].x - 2;
            dy = wmap->npcs[1].y;
          }
          else if(dice >= 20 && dice < 35)
          {
            // Visit the inn 15% of the time
            dx = wmap->npcs[2].x;
            dy = wmap->npcs[2].y + 2;
          }
          else if(dice >= 35 && dice < 40)
          {
            // Visit the ferry 5% of the time
            dx = wmap->npcs[3].x;
            dy = wmap->npcs[3].y;
          }
          else if(dice >= 40 && dice < 42)
          {
            // Visit left mansion 2% of the time
            dx = IMAGE_WIDTH/4 + 7;
            dy = IMAGE_HEIGHT/4 + 6;
          }
          else if(dice >= 42 && dice < 44)
          {
            // Visit right mansion 2% of the time
            dx = 3*IMAGE_WIDTH/4 - 8;
            dy = IMAGE_HEIGHT/4 + 6;
          }
          else if(dice >= 44 && dice < 46)
          {
            // Visit left hovel 2% of the time
            dx = 46;
            dy = 47;
          }
          else if(dice >= 46 && dice < 48)
          {
            // Visit right hovel 2% of the time
            dx = 75;
            dy = 47;
          }
          else
          {
            // Visit the town square 52% of the time
            float r = game.rng->getFloat(2.0f, 5.0f);
            float theta = game.rng->getFloat(0.0f, 2.0f*M_PI);
            dx = IMAGE_WIDTH/2 + static_cast<int>(r*cos(theta));
            dy = IMAGE_HEIGHT/2 + static_cast<int>(r*sin(theta));
          }
          path->compute(x, y, dx, dy);
        }
      }
    }
  }
}

// Render Npc
void Npc::render(Player player)
{
  if(inUse)
  {
    int cx = x, cy = y + 3;
    if(IN_RECTANGLE(cx, cy, DISPLAY_WIDTH, DISPLAY_HEIGHT))
    {
      TCODConsole::root->setDefaultForeground(colour);
      TCODConsole::root->putChar(cx, cy, sym, TCOD_BKGND_NONE);
      if(x == player.x && y == player.y)
      {
        TCODConsole::root->setDefaultForeground(colour);
        TCODConsole::root->printEx(cx, cy - 2, TCOD_BKGND_NONE, TCOD_LEFT, label);
      }
    }
  }
}
