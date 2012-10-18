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

const float longButtonDelay = 0.3f;
const float longSpellMagicTimer = 1.0f;
const float hitFlashDelay = 0.2f;
const TCODColor flashColour = TCODColor::red;

// The player constructor
Player::Player(): lvl(0), xp(0), xpnext(xpLevel(1)), x(MAP_WIDTH/2), y(MAP_HEIGHT/2), colour(TCODColor::white), gp(100), walkWait(0), magicTimer(0.0f), hitFlashTimer(0.0f)
{
  sym = CHAR_PLAYER_DOWN;
  sym_up = CHAR_PLAYER_UP;
  sym_down = CHAR_PLAYER_DOWN;
  sym_left = CHAR_PLAYER_LEFT;
  sym_right = CHAR_PLAYER_RIGHT;

  stats.spd = 18;
}

// Update the player
void Player::update(float elapsed, TCOD_key_t *key, TCOD_mouse_t mouse)
{
  static float mpfraction = 0.0f;

  // Fade in
  if(game.isFaded)
  {
    for(int fade = 0; fade <= 255; fade += 25)
    {
      TCODConsole::setFade(fade, TCODColor::black);
      TCODConsole::flush();
    }
    game.isFaded = false;
  }

  // Replenish MP
  mpfraction += 0.125f*elapsed*static_cast<float>(stats.wil);
  if(mpfraction >= 1.0f)
  {
    stats.mp += static_cast<int>(mpfraction);
    mpfraction = 0.0f;
    stats.mp = CLAMP(0, stats.mpmax, stats.mp);
  }

  if(game.inCaves)
  {
    CaveMap *cmap = &game.caves[game.caveID];

    // Console offset
    int d_x = cmap->display_x;
    int d_y = cmap->display_y;

    // Mouse coordinates
    int map_x = mouse.cx + d_x;
    int map_y = mouse.cy + d_y + 3;
    bool atPlayer = x == map_x && y == map_y;

    // Increment magic timer
    if(mouse.lbutton) magicTimer += elapsed;

    // Left mouse button
    if(mouse.lbutton_pressed)
    {
      //if(!Magic::sparkle || magicTimer < longSpellMagicTimer)
      if(magicTimer > 0.0f && magicTimer < longSpellMagicTimer && stats.mp >= 1)
      {
        // Quick left click: Standard Magic
        if(!atPlayer)
        {
          printf("Cast Standard Magic\n");
          stats.mp -= 1;
          stats.mp = CLAMP(0, stats.mpmax, stats.mp);
          //Magic *m = new Magic(x, y, map_x, map_y, FB_STANDARD);
          //game.addMagic(m);
        }
      }

      //if(Magic::sparkle && magicTimer >= longSpellMagicTimer)
      if(magicTimer >= longSpellMagicTimer && stats.mp >= 5)
      {
        // Long left click: Magic Burst
        if(!atPlayer)
        {
          printf("Cast Magic Burst\n");
          stats.mp -= 5;
          stats.mp = CLAMP(0, stats.mpmax, stats.mp);
          //Magic *m = new Magic(x, y, map_x, map_y, FB_BURST);
          //game.addMagic(m);
        }
      }
      magicTimer = 0.0f;
    }

    if(cmap->getItemID(x, y) >= 0 && cmap->getFirstVisit(x, y))
    {
      if(addItem(MUSHROOM_UNKNOWN))
      {
        cmap->removeItem(x, y);
      }
      else
      {
        cmap->setFirstVisit(x, y, false);
      }
    }

    if(cmap->getHideID(x, y) >= 0 && cmap->getFirstVisit(x, y))
    {
      int hideID = cmap->getHideID(x, y);
      ECreatureType creatureType = cmap->hides[hideID].creatureType;
      if(addHide(creatureType))
      {
        cmap->removeHide(x, y);
        cmap->addCorpse(x, y);
      }
      else
      {
        cmap->setFirstVisit(x, y, false);
      }
    }

    if(walkWait > 0)
    {
      // Decrement walk wait
      walkWait -= 1;
    }
    else
    {
      if(TCODConsole::isKeyPressed(TCODK_UP))
      {
        if(y <= 1) y = 1;
        if(cmap->isFov1xWalkable(x, y - 1))
        {
          if(cmap->getCreatureID(x, y - 1) < 0)
          {
            cmap->setFirstVisit(x, y, false);
            TCODConsole::root->putChar(x - d_x, y + 3 - d_y, ' ', TCOD_BKGND_NONE);
            y--;
            TCODConsole::root->putChar(x - d_x, y + 3 - d_y, sym_up, TCOD_BKGND_NONE);
            sym = sym_up;
            cmap->setFirstVisit(x, y, true);
            cmap->recomputeFov = true;
          }
          else
          {
            // Attack Creature!
            cmap->attackCreature(x, y - 1);
          }
        }
      }
      if(TCODConsole::isKeyPressed(TCODK_DOWN))
      {
        if(y >= MAP_HEIGHT - 2) y = MAP_HEIGHT - 2;
        if(cmap->isFov1xWalkable(x, y + 1))
        {
          if(cmap->getCreatureID(x, y + 1) < 0)
          {
            cmap->setFirstVisit(x, y, false);
            TCODConsole::root->putChar(x - d_x, y + 3 - d_y, ' ', TCOD_BKGND_NONE);
            y++;
            TCODConsole::root->putChar(x - d_x, y + 3 - d_y, sym_down, TCOD_BKGND_NONE);
            sym = sym_down;
            cmap->setFirstVisit(x, y, true);
            cmap->recomputeFov = true;
          }
          else
          {
            // Attack Creature!
            cmap->attackCreature(x, y + 1);
          }
        }
      }
      if(TCODConsole::isKeyPressed(TCODK_LEFT))
      {
        if(x <= 1) x = 1;
        if(cmap->isFov1xWalkable(x - 1, y))
        {
          if(cmap->getCreatureID(x - 1, y) < 0)
          {
            cmap->setFirstVisit(x, y, false);
            TCODConsole::root->putChar(x - d_x, y + 3 - d_y, ' ', TCOD_BKGND_NONE);
            x--;
            TCODConsole::root->putChar(x - d_x, y + 3 - d_y, sym_left, TCOD_BKGND_NONE);
            sym = sym_left;
            cmap->setFirstVisit(x, y, true);
            cmap->recomputeFov = true;
          }
          else
          {
            // Attack Creature!
            cmap->attackCreature(x - 1, y);
          }
        }
      }
      if(TCODConsole::isKeyPressed(TCODK_RIGHT))
      {
        if(x >= MAP_WIDTH - 2) x = MAP_WIDTH - 2;
        if(cmap->isFov1xWalkable(x + 1, y))
        {
          if(cmap->getCreatureID(x + 1, y) < 0)
          {
            cmap->setFirstVisit(x, y, false);
            TCODConsole::root->putChar(x - d_x, y + 3 - d_y, ' ', TCOD_BKGND_NONE);
            x++;
            TCODConsole::root->putChar(x - d_x, y + 3 - d_y, sym_right, TCOD_BKGND_NONE);
            sym = sym_right;
            cmap->setFirstVisit(x, y, true);
            cmap->recomputeFov = true;
          }
          else
          {
            // Attack Creature!
            cmap->attackCreature(x + 1, y);
          }
        }
      }
      if(TCODConsole::isKeyPressed(TCODK_SPACE))
      {
        if(!path->isEmpty())
        {
          int px, py;
          bool isWalkable = path->walk(&px, &py, true);
          if(isWalkable && cmap->getCreatureID(px, py) < 0)
          {
            cmap->setFirstVisit(x, y, false);
            TCODConsole::root->putChar(x - d_x, y + 3 - d_y, ' ', TCOD_BKGND_NONE);
            x = px; y = py;
            TCODConsole::root->putChar(x - d_x, y + 3 - d_y, sym_down, TCOD_BKGND_NONE);
            sym = sym_down;
            cmap->setFirstVisit(x, y, true);
            cmap->recomputeFov = true;
          }
          else
          {
            // Attack Creature!
            cmap->attackCreature(px, py);
          }
        }
      }
      // Reset walk wait
      walkWait = SPDMAX + SPDMIN - stats.spd;
    }

    if(key->lalt && key->vk == TCODK_PAGEUP)
    {
      x = cmap->upx; y = cmap->upy;
    }
    if(key->lalt && key->vk == TCODK_PAGEDOWN)
    {
      if(game.caveID != NCAVE_REGIONS - 1)
      {
        x = cmap->downx; y = cmap->downy;
      }
    }

    if(key->vk == TCODK_ENTER) exitCaveLocation();
  }
  else
  {
    WorldMap *wmap = &game.world[game.worldID];

    if(walkWait > 0)
    {
      // Decrement walk wait
      walkWait -= 1;
    }
    else
    {
      if(TCODConsole::isKeyPressed(TCODK_UP))
      {
        if(y <= 1) y = 1;
        if(wmap->isFov1xWalkable(x, y - 1))
        {
          if(wmap->getNpcID(x, y - 1) < 0)
          {
            TCODConsole::root->putChar(x, y + 3, ' ', TCOD_BKGND_NONE);
            y--;
            TCODConsole::root->putChar(x, y + 3, sym_up, TCOD_BKGND_NONE);
            sym = sym_up;
          }
        }
        if(y <= 0 && game.worldID > 0) exitWorldLocation();
      }
      if(TCODConsole::isKeyPressed(TCODK_DOWN))
      {
        if(y >= IMAGE_HEIGHT - 2) y = IMAGE_HEIGHT - 2;
        if(wmap->isFov1xWalkable(x, y + 1))
        {
          if(wmap->getNpcID(x, y + 1) < 0)
          {
            TCODConsole::root->putChar(x, y + 3, ' ', TCOD_BKGND_NONE);
            y++;
            TCODConsole::root->putChar(x, y + 3, sym_down, TCOD_BKGND_NONE);
            sym = sym_down;
          }
        }
        if(y >= IMAGE_HEIGHT - 1 && game.worldID > 0) exitWorldLocation();
      }
      if(TCODConsole::isKeyPressed(TCODK_LEFT))
      {
        if(x <= 1) x = 1;
        if(wmap->isFov1xWalkable(x - 1, y))
        {
          if(wmap->getNpcID(x - 1, y) < 0)
          {
            TCODConsole::root->putChar(x, y + 3, ' ', TCOD_BKGND_NONE);
            x--;
            TCODConsole::root->putChar(x, y + 3, sym_left, TCOD_BKGND_NONE);
            sym = sym_left;
          }
        }
        if(x <= 0 && game.worldID > 0) exitWorldLocation();
      }
      if(TCODConsole::isKeyPressed(TCODK_RIGHT))
      {
        if(x >= IMAGE_WIDTH - 2) x = IMAGE_WIDTH - 2;
        if(wmap->isFov1xWalkable(x + 1, y))
        {
          if(wmap->getNpcID(x + 1, y) < 0)
          {
            TCODConsole::root->putChar(x, y + 3, ' ', TCOD_BKGND_NONE);
            x++;
            TCODConsole::root->putChar(x, y + 3, sym_right, TCOD_BKGND_NONE);
            sym = sym_right;
          }
        }
        if(x >= IMAGE_WIDTH - 1 && game.worldID > 0) exitWorldLocation();
      }
      // Reset walk wait
      walkWait = SPDMAX + SPDMIN - stats.spd;
    }
    if(key->vk == TCODK_ENTER) actionWorldMap();
  }

  key->vk = TCODK_NONE;

  // Get current player status
  updateStatus();

  // Display a flash if the player is hit
  if(hitFlashTimer > 0.0f)
  {
    hitFlashTimer -= elapsed;
    if(hitFlashTimer > 0.0f)
    {
      int flashLvl = static_cast<int>(255 - 128*hitFlashTimer/hitFlashDelay);
      TCODConsole::setFade(flashLvl, flashColour);
    }
    else
    {
      TCODConsole::setFade(255, flashColour);
    }
  }
}

void Player::render()
{
  static bool blink = false;

  if(game.inCaves)
  {
    CaveMap *cmap = &game.caves[game.caveID];

    // Position in console
    int cx = x - cmap->display_x;
    int cy = y - cmap->display_y + 3;

    // Render player
    TCODConsole::root->setDefaultForeground(colour);
    TCODConsole::root->putChar(cx, cy, sym, TCOD_BKGND_NONE);

    //if(Magic::incandescence && magicTimer > longButtonDelay)
    if(magicTimer > longButtonDelay && stats.mp >= 5)
    {
      // Spell charging bar
      int barLength = 0;
      if(magicTimer < longSpellMagicTimer)
      {
        barLength = 1 + static_cast<int>(1.99f*(magicTimer - longButtonDelay)/(longSpellMagicTimer - longButtonDelay));
      }
      else
      {
        barLength = 3;
      }

      blink = !blink;
      if(barLength == 3 && blink) barLength = 0;

      int barx = cx - 1, bary = cy - 2;
      if(cx <= 0) barx = cx;
      if(cx >= DISPLAY_WIDTH - 1) barx = cx - 2;
      if(cy <= 2) bary = cy + 2;

      for(int i = barx; i < barx + barLength; i++)
      {
        TCODConsole::root->putCharEx(i, bary, CHAR_CHARGEBAR, TCODColor::lightRed, TCODColor::darkRed);
      }
    }
  }
  else
  {
    // Render player
    TCODConsole::root->setDefaultForeground(colour);
    TCODConsole::root->putChar(x, y + 3, sym, TCOD_BKGND_NONE);
  }
}

// Set player stats
void Player::updateStats()
{
  // Reset stats to base values
  stats = base;

  // Add contribution from equipment
  for(int i = 0; i < NEQUIPTYPE; i++) stats += equipInv.equiped[i].stats;

  // Ensure stats stay within acceptable limits
  stats.hpmax = CLAMP(HPMIN, HPMAX, stats.hpmax);
  stats.hp    = CLAMP(0, stats.hpmax, stats.hp);
  stats.ap    = CLAMP(APMIN, APMAX, stats.ap);
  stats.dp    = CLAMP(DPMIN, DPMAX, stats.dp);
  stats.str   = CLAMP(STRMIN, STRMAX, stats.str);
  stats.spd   = CLAMP(SPDMIN, SPDMAX, stats.spd);

  stats.mpmax = CLAMP(MPMIN, MPMAX, stats.mpmax);
  stats.mp    = CLAMP(0, stats.mpmax, stats.mp);
  stats.map   = CLAMP(MAPMIN, MAPMAX, stats.map);
  stats.mdp   = CLAMP(MDPMIN, MDPMAX, stats.mdp);
  stats.wil   = CLAMP(WILMIN, WILMAX, stats.wil);
  stats.acu   = CLAMP(ACUMIN, ACUMAX, stats.acu);
}

// Update player status
void Player::updateStatus()
{
  static bool deathfirst = true;
  char buffer[CHARMAX];

  // Check for physical upgrade
  if(xp >= xpLevel(lvl + 1))
  {
    lvl++;
    base.hpmax = hpLevel(lvl);
    base.hp = base.hpmax;
    base.ap = apLevel(lvl);
    base.dp = dpLevel(lvl);
    base.str = strLevel(lvl);
    base.spd = spdLevel(lvl);

    base.mpmax = mpLevel(lvl);
    base.mp = base.mpmax;
    base.map = mapLevel(lvl);
    base.mdp = mdpLevel(lvl);
    base.wil = wilLevel(lvl);
    base.acu = acuLevel(lvl);

    xpnext = xpLevel(lvl + 1);

    // Update Stats
    updateStats();
  }

  // Update the player's health status
  for(int i = 0; i <= 4; i++) health.status[i] = false; // Reset all
  int istatus = 1 + 3*static_cast<int>(static_cast<float>(stats.hp)/static_cast<float>(stats.hpmax));
  if(stats.hp == 0) istatus = 0;
  health.status[istatus] = true;

  // Update the player's burden status
  if(itemInv.mass + equipInv.mass + hideInv.mass >= static_cast<float>(stats.str))
  {
    health.status[STATUS_BURDENED] = true;
    if(health.burdenedfirst)
    {
      base.spd -= 2;
      health.burdenedfirst = false;
      health.unburdenedfirst = true;
    }
  }
  else
  {
    health.status[STATUS_BURDENED] = false;
    if(health.unburdenedfirst)
    {
      base.spd += 2;
      health.unburdenedfirst = false;
      health.burdenedfirst = true;
    }
  }

  // Death Message
  if(health.status[STATUS_DEAD] && deathfirst)
  {
    game.menu.displayGameMenu = false;
    game.menu.displayItemShopMenu = false;
    game.menu.displayEquipShopMenu = false;
    game.menu.displayInnMenu = false;
    game.menu.displayFerryMenu = false;
    game.menu.displayDeathMsg = true;
    sym = '%';
    colour = TCODColor::darkRed;

    // Print to message log
    sprintf(buffer, "You died\n");
    game.menu.updateMessageLog(buffer);
    deathfirst = false;
  }
}

// Player takes damage
void Player::takeDamage(Creature cr)
{
  int damage = CLAMP(0, 1000, cr.stats.ap/2 - stats.dp/4);

  stats.hp -= damage;
  printf("Player  : %d %d\n", stats.hp, damage);
}

// Player action on the world map
void Player::actionWorldMap()
{
  char buffer[CHARMAX];

  WorldMap *wmap = &game.world[game.worldID];

  for(int i = -2; i <= 2; i++)
  {
    for(int j = -2; j <= 2; j++)
    {
      int id = wmap->getNpcID(x + i, y + j);
      if(id >= 0)
      {
        switch(wmap->npcs[id].npcType)
        {
          case NPCTYPE_ITEMSHOPKEEPER:
          {
            // Toggle the volume for the item shop menu
            game.sound.toggleVolume(0.5f);

            // Toggle the item shop menu flag
            game.menu.displayItemShopMenu = true;

            break;
          }
          case NPCTYPE_EQUIPSHOPKEEPER:
          {
            // Toggle the volume for the item shop menu
            game.sound.toggleVolume(0.5f);

            // Toggle the item shop menu flag
            game.menu.displayEquipShopMenu = true;

            break;
          }
          case NPCTYPE_INNKEEPER:
          {
            // Toggle the volume for the item shop menu
            game.sound.toggleVolume(0.5f);

            // Toggle the item shop menu flag
            game.menu.displayInnMenu = true;

            break;
          }
          case NPCTYPE_FERRYMAN:
          {
            // Toggle the volume for the item shop menu
            game.sound.toggleVolume(0.5f);

            // Toggle the item shop menu flag
            game.menu.displayFerryMenu = true;
          }
          default: break;
        }
      } 
    }
  }

  int id = wmap->getLocationID(x, y);
  if(id >= 0 && id < NTEMPLES + NTOWNS)
  {
    // Fade out
    for(int fade = 255; fade >= 0; fade -= 25)
    {
      TCODConsole::setFade(fade, TCODColor::black);
      TCODConsole::flush();
    }
    game.isFaded = true;

    // Print to message log
    sprintf(buffer, "Entered %s\n", wmap->locations[id].name);
    game.menu.updateMessageLog(buffer);

    game.worldID = id + 1;
    game.sound.first = true;
    wmap = &game.world[game.worldID];
    x = IMAGE_WIDTH/2; y = IMAGE_HEIGHT - 10;
  }
  if(id >= NTEMPLES + NTOWNS)
  {
    // Fade out
    for(int fade = 255; fade >= 0; fade -= 25)
    {
      TCODConsole::setFade(fade, TCODColor::black);
      TCODConsole::flush();
    }
    game.isFaded = true;

    // Print to message log
    sprintf(buffer, "Entered %s\n", wmap->locations[id].name);
    game.menu.updateMessageLog(buffer);

    game.worldID = id + 1;
    game.caveID = 0;
    game.inCaves = true;
    game.sound.first = true;

    CaveMap *ctmp = &game.caves[game.caveID];
    x = ctmp->upx; y = ctmp->upy;
    path = new TCODPath(ctmp->fov1x);
    path->compute(ctmp->upx, ctmp->upy, ctmp->downx, ctmp->downy);

    // Move the display
    ctmp->moveDisplay(x, y);
  }
}

// Player exits a world location
void Player::exitWorldLocation()
{
  char buffer[CHARMAX];

  int id = MAX(0, game.worldID - 1);
  game.worldID = 0;
  game.sound.first = true;
  WorldMap *wmap = &game.world[game.worldID];
  x = wmap->locations[id].x; y = wmap->locations[id].y;

  // Print to message log
  sprintf(buffer, "Left %s\n", wmap->locations[id].name);
  game.menu.updateMessageLog(buffer);

  // Save Game
  game.saveGame();

  // Fade out
  for(int fade = 255; fade >= 0; fade -= 25)
  {
    TCODConsole::setFade(fade, TCODColor::black);
    TCODConsole::flush();
  }
  game.isFaded = true;
}

// Player exits from a cave location to another, or to the world map
void Player::exitCaveLocation()
{
  char buffer[CHARMAX];

  CaveMap *cmap = &game.caves[game.caveID];

  // Remove all hides and corpses
  for(int i = 0; i < NCORPSEMAX; i++)
  {
    if(cmap->hides[i].inUse)
    {
      int hx = cmap->hides[i].x, hy = cmap->hides[i].y;
      cmap->hides[i].inUse = false;
      cmap->cells[hx + MAP_WIDTH*hy].hideID = -1;
    }

    if(cmap->corpses[i].inUse)
    {
      int cx = cmap->corpses[i].x, cy = cmap->corpses[i].y;
      cmap->corpses[i].inUse = false;
      cmap->cells[cx + MAP_WIDTH*cy].corpseID = -1;
    }
  }

  if(x == cmap->downx && y == cmap->downy)
  {
    game.caveID++;

    if(game.caveID < NCAVE_REGIONS)
    {
      // Fade out
      for(int fade = 255; fade >= 0; fade -= 25)
      {
        TCODConsole::setFade(fade, TCODColor::black);
        TCODConsole::flush();
      }
      game.isFaded = true;

      if(path) delete path;
      cmap = &game.caves[game.caveID];
      x = cmap->upx; y = cmap->upy;
      if(game.caveID % NLEVELS_REGION == 0 || game.caveID == NCAVE_REGIONS - 1) game.sound.first = true;
      path = new TCODPath(cmap->fov1x);
      path->compute(cmap->upx, cmap->upy, cmap->downx, cmap->downy);

      // Move the display
      cmap->moveDisplay(x, y);
    }
    else
    {
      game.caveID = NCAVE_REGIONS - 1;
      game.sound.first = true;
    }
  }
  else if(x == cmap->upx && y == cmap->upy)
  {
    game.caveID--;

    if(game.caveID < 0)
    {
      if(path) delete path;
      int id = MAX(0, game.worldID - 1);
      game.caveID = 0;
      game.worldID = 0;
      game.inCaves = false;
      game.sound.first = true;
      WorldMap *wtmp = &game.world[game.worldID];
      x = wtmp->locations[id].x; y = wtmp->locations[id].y;

      // Print to message log
      sprintf(buffer, "Left %s\n", wtmp->locations[id].name);
      game.menu.updateMessageLog(buffer);

      // Move the display
      cmap->moveDisplay(x, y);

      // Save Game
      game.saveGame();

      // Fade out
      for(int fade = 255; fade >= 0; fade -= 25)
      {
        TCODConsole::setFade(fade, TCODColor::black);
        TCODConsole::flush();
      }
      game.isFaded = true;
    }
    else
    {
      // Fade out
      for(int fade = 255; fade >= 0; fade -= 25)
      {
        TCODConsole::setFade(fade, TCODColor::black);
        TCODConsole::flush();
      }
      game.isFaded = true;

      if(path) delete path;
      cmap = &game.caves[game.caveID];
      x = cmap->downx; y = cmap->downy;
      if((game.caveID + 1) % NLEVELS_REGION == 0 || game.caveID == NCAVE_REGIONS - 2) game.sound.first = true;
      path = new TCODPath(cmap->fov1x);
      path->compute(cmap->downx, cmap->downy, cmap->upx, cmap->upy);

      // Move the display
      cmap->moveDisplay(x, y);
    }
  }
}

// Player takes a ferry to location id
void Player::takeFerry(int id)
{
  char buffer[CHARMAX];

  game.worldID = 0;
  game.sound.first = true;
  WorldMap *wmap = &game.world[game.worldID];
  x = wmap->locations[id].x; y = wmap->locations[id].y;

  // Print to message log
  sprintf(buffer, "Travelled to %s\n", wmap->locations[id].name);
  game.menu.updateMessageLog(buffer);

  // Save Game
  game.saveGame();

  // Fade out
  for(int fade = 255; fade >= 0; fade -= 25)
  {
    TCODConsole::setFade(fade, TCODColor::black);
    TCODConsole::flush();
  }
  game.isFaded = true;
}

// Player stays at the inn
void Player::stayInn()
{
  char buffer[CHARMAX];

  int id = game.worldID - 1;
  WorldMap *wmap = &game.world[0];

  // Print to message log
  sprintf(buffer, "Rested at the %s Inn\n", wmap->locations[id].name);
  game.menu.updateMessageLog(buffer);

  game.sound.first = true;

  // Fade out
  for(int fade = 255; fade >= 0; fade -= 2)
  {
    // Load new music
    if(game.sound.first)
    {
      // Play the music for the current map
      game.sound.play(SOUND_GOOD_NIGHT);

      // Update the sound system
      game.sound.endFrame();
      game.sound.update();

      game.sound.first = false;
      game.sound.crossFading = true;
    }

    // Crossfade between the two sound channels
    if(game.sound.crossFading) game.sound.crossFade(TCODSystem::getLastFrameLength());

    TCODConsole::setFade(fade, TCODColor::black);
    TCODConsole::flush();
  }
  TCODSystem::sleepMilli(1750); // Pause for the inn music
  game.isFaded = true;
  game.sound.first = true;

  stats.hp = stats.hpmax; stats.mp = stats.mpmax;
  for(int i = 0; i < NSTATUS; i++) health.status[i] = false;
  health.status[STATUS_HEALTHY] = true;

  // Update the player's status
  updateStatus();
}

// Update flash timer when the Player is hit <== Move to Game Class
void Player::hitFlash()
{
  hitFlashTimer += hitFlashDelay;
  hitFlashTimer = MIN(hitFlashTimer, 5*hitFlashDelay);
}

// A method to add a specified item to the inventory
bool Player::addItem(int itemIndex)
{
  bool status = true;
  char buffer[CHARMAX];

  // Selected item
  Item item = itemInv.items[itemIndex];

  float totalMass = itemInv.mass + item.mass + equipInv.mass + hideInv.mass;

  // Update the quantity of specified item
  if(itemInv.count[itemIndex] < 99 && totalMass < static_cast<float>(stats.str))
  {
    // A new item is added to the inventory
    if(itemInv.count[itemIndex] == 0)
    {
      // Locate the position in the index vector for the new item
      int j = itemInv.nitems;
      for(int i = 0; i < itemInv.nitems; i++)
      {
        if(itemIndex < itemInv.index[i])
        {
          j = i;
          break;
        }
      }

      // Shift down the index vector
      if(j < itemInv.nitems) for(int i = itemInv.nitems - 1; i >= j ; i--) itemInv.index[i + 1] = itemInv.index[i];

      itemInv.index[j] = itemIndex;

      itemInv.nitems++;
    }

    // Add selected item to item inventory, and update mass of item inventory
    itemInv.count[itemIndex]++;
    itemInv.mass += item.mass;

    // Compute the number of active items
    itemInv.nitems = 0;
    for(int i = 0; i < NITEMS; i++) if(itemInv.count[i] > 0) itemInv.nitems++;

    // Update player's status
    updateStatus();

    // Print to message log
    sprintf(buffer, "Found a(n) %s\n", item.label);
    game.menu.updateMessageLog(buffer);

    status = true;
  }
  else
  {
    // Print to message log
    sprintf(buffer, "Cannot carry any more items\n");
    game.menu.updateMessageLog(buffer);

    status = false;
  }
  return status;
}

// Method to use a specified item from the inventory
void Player::useItem(int *cursorIndex)
{
  char buffer[CHARMAX];
  int itemIndex = itemInv.index[*cursorIndex];

  // Consume item only if it exists
  if(itemInv.count[itemIndex] > 0)
  {
    Item item = itemInv.items[itemIndex];

    // Update the player's status
    switch(itemIndex)
    {
      case POTION_ELIXIR:
      {
        for(int i = 0; i < NSTATUS; i++) health.status[i] = false;
        health.status[STATUS_HEALTHY] = true;
        break;
      }
      case POTION_HEALTH: break;
      case POTION_HEALTH_STRONG: break;
      case POTION_MAGIC: break;
      case POTION_MAGIC_STRONG: break;
      case POTION_POISON_ANTIDOTE: health.status[STATUS_POISONED] = false; break;
      case MUSHROOM_HEALTH: break;
      case MUSHROOM_MAGIC: break;
      case MUSHROOM_POISON: health.status[STATUS_POISONED] = true; break;
      case MUSHROOM_WEAKNESS: health.status[STATUS_WEAKENED] = true; break;
      case MUSHROOM_SLUGGISHNESS: health.status[STATUS_SLUGGISH] = true; break;
      case MUSHROOM_FEEBLENESS: health.status[STATUS_FEEBLE] = true; break;
      case MUSHROOM_CONFUSION: health.status[STATUS_CONFUSED] = true; break;
      case MUSHROOM_UNKNOWN:
      {
        // Randomly select a good or bad mushroom
        int index2 = game.rng->getInt(MUSHROOM_HEALTH, MUSHROOM_CONFUSION);
        item = itemInv.items[index2];
        switch(index2)
        {
          case MUSHROOM_HEALTH: break;
          case MUSHROOM_MAGIC: break;
          case MUSHROOM_POISON: health.status[STATUS_POISONED] = true; break;
          case MUSHROOM_WEAKNESS: health.status[STATUS_WEAKENED] = true; break;
          case MUSHROOM_SLUGGISHNESS: health.status[STATUS_SLUGGISH] = true; break;
          case MUSHROOM_FEEBLENESS: health.status[STATUS_FEEBLE] = true; break;
          case MUSHROOM_CONFUSION: health.status[STATUS_CONFUSED] = true; break;
          default: break;
        }
      }
      default: break;
    }

    // Print to message log
    sprintf(buffer, "Consumed a(n) %s\n", item.label);
    game.menu.updateMessageLog(buffer);

    // Update the player's base stats
    base.hp += item.stats.hp;
    base.str += item.stats.str;
    base.spd += item.stats.spd;
    base.mp += item.stats.mp;
    base.wil += item.stats.wil;
    base.acu += item.stats.acu;

    // Decrease the amount of this type of potion, and its mass in the inventory
    itemInv.count[itemIndex]--;
    itemInv.mass -= item.mass;

    // If all the items have been used
    if(itemInv.count[itemIndex] == 0)
    {
      if(itemInv.nitems >= 2)
      {
        // Shift up the index and count vectors
        for(int i = *cursorIndex; i <= itemInv.nitems - 2; i++) itemInv.index[i] = itemInv.index[i + 1];

        // Locate the closet active item, first search up the list
        while(itemInv.count[itemInv.index[*cursorIndex]] == 0)
        {
          *cursorIndex -= 1;
          if(*cursorIndex == 0) break;
        }

        // Then search down the list
        while(itemInv.count[itemInv.index[*cursorIndex]] == 0)
        {
          *cursorIndex += 1;
          if(*cursorIndex == itemInv.nitems - 1) break;
        }

        itemInv.nitems--;
      }
      else
      {
        *cursorIndex = 0;
        itemInv.nitems = 0;
      }
    }

    // Update Stats
    updateStats();

    // Update the player's status
    updateStatus();
  }
}

// A method to buy a specified item to the inventory
void Player::buyItem(int *cursorIndex)
{
  char buffer[CHARMAX];
  int id = game.worldID - 1;
  WorldMap *wmap = &game.world[0];

  int itemIndex = wmap->locations[id].itemInv.index[*cursorIndex];
  int price = wmap->locations[id].itemInv.price[itemIndex];
  Item item = itemInv.items[itemIndex];

  float totalMass = itemInv.mass + item.mass + equipInv.mass + hideInv.mass;

  // Update the quantity of specified item
  if(itemInv.count[itemIndex] < 99 && totalMass < static_cast<float>(stats.str))
  {
    // If the player has enough money
    if(gp >= price)
    {
      // Update amount of money
      gp -= price;

      // A new item is added to the inventory
      if(itemInv.count[itemIndex] == 0)
      {
        // Locate the position in the index vector for the new item
        int j = itemInv.nitems;
        for(int i = 0; i < itemInv.nitems; i++)
        {
          if(itemIndex < itemInv.index[i])
          {
            j = i;
            break;
          }
        }

        // Shift down the index vector
        if(j < itemInv.nitems) for(int i = itemInv.nitems - 1; i >= j ; i--) itemInv.index[i + 1] = itemInv.index[i];

        itemInv.index[j] = itemIndex;
        itemInv.nitems++;
      }

      // Add selected item to item inventory, and update mass of item inventory
      itemInv.count[itemIndex]++;
      itemInv.mass += item.mass;

      // Compute the number of active items
      itemInv.nitems = 0;
      for(int i = 0; i < NITEMS; i++) if(itemInv.count[i] > 0) itemInv.nitems++;

      // Update player's status
      updateStatus();

      // Remove item from town inventory
      wmap->locations[id].itemInv.count[itemIndex]--;
      wmap->locations[id].itemInv.mass -= item.mass;

      // Update number of active items in town inventory
      int n = 0;
      for(int i = 0; i < NITEMS; i++)
      {
        if(wmap->locations[id].itemInv.count[i] > 0)
        {
          wmap->locations[id].itemInv.index[n++] = i;
        }
      }
      wmap->locations[id].itemInv.nitems = CLAMP(0, NITEMS - 1, n);

      // Print to message log
      sprintf(buffer, "Bought a(n) %s\n", item.label);
      game.menu.updateMessageLog(buffer);
    }
    else
    {
      // Print to message log
      sprintf(buffer, "Cannot buy this item\n");
      game.menu.updateMessageLog(buffer);
    }
  }
  else
  {
    // Print to message log
    sprintf(buffer, "Cannot carry any more items\n");
    game.menu.updateMessageLog(buffer);
  }
}

// A method to sell a specified item to the inventory
void Player::sellItem(int *cursorIndex)
{
  char buffer[CHARMAX];
  int id = game.worldID - 1;
  WorldMap *wmap = &game.world[0];

  int itemIndex = itemInv.index[*cursorIndex], itemIndex2 = itemIndex;
  int price = MAX(1, wmap->locations[id].itemInv.price[itemIndex]/2);
  if(itemIndex == MUSHROOM_UNKNOWN)
  {
    // Randomly select a good or bad mushroom
    itemIndex2 = game.rng->getInt(MUSHROOM_HEALTH, MUSHROOM_CONFUSION);
  }
  Item item = itemInv.items[itemIndex2];

  // Update the quantity of specified item
  if(itemInv.count[itemIndex] > 0)
  {
    // Update amount of money
    gp += price;

    // A new item is added to the item shop inventory
    if(wmap->locations[id].itemInv.count[itemIndex2] == 0)
    {
      // Locate the position in the index vector for the new item
      int j = wmap->locations[id].itemInv.nitems;
      for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
      {
        if(itemIndex2 < wmap->locations[id].itemInv.index[i])
        {
          j = i;
          break;
        }
      }

      // Shift down the index vector
      if(j < wmap->locations[id].itemInv.nitems)
      {
        for(int i = wmap->locations[id].itemInv.nitems - 1; i >= j ; i--)
        {
          wmap->locations[id].itemInv.index[i + 1] = wmap->locations[id].itemInv.index[i];
        }
      }

      wmap->locations[id].itemInv.index[j] = itemIndex2;
      wmap->locations[id].itemInv.nitems++;
    }

    // Add selected item to item shop inventory, and update mass of item shop inventory
    wmap->locations[id].itemInv.count[itemIndex2]++;
    wmap->locations[id].itemInv.mass += item.mass;

    // Compute the number of active items in the item shop
    wmap->locations[id].itemInv.nitems = 0;
    for(int i = 0; i < NITEMS; i++)
    {
      if(wmap->locations[id].itemInv.count[i] > 0)
      {
        wmap->locations[id].itemInv.nitems++;
      }
    }

    // Remove item from player's inventory
    itemInv.count[itemIndex]--;
    itemInv.mass -= item.mass;

    // Update number of active items in player's inventory
    int n = 0;
    for(int i = 0; i < NITEMS; i++)
    {
      if(itemInv.count[i] > 0)
      {
        itemInv.index[n++] = i;
      }
    }
    itemInv.nitems = CLAMP(0, NITEMS - 1, n);

    // Update player's status
    updateStatus();

    // Print to message log
    sprintf(buffer, "Sold a(n) %s\n", item.label);
    game.menu.updateMessageLog(buffer);
  }
}

// A method to sell a specified hide to the town inventory
void Player::sellHide(int *cursorIndex)
{
  char buffer[CHARMAX];
  int id = game.worldID - 1;
  WorldMap *wmap = &game.world[0];

  int hideIndex = hideInv.index[*cursorIndex - itemInv.nitems];
  int price = MAX(1, wmap->locations[id].hideInv.price[hideIndex]);
  Hide hide = hideInv.hides[hideIndex];

  // Update the quantity of specified hide
  if(hideInv.count[hideIndex] > 0)
  {
    // Update amount of money
    gp += price;

    // A new hide is added to the item shop inventory
    if(wmap->locations[id].hideInv.count[hideIndex] == 0)
    {
      // Locate the position in the index vector for the new hide
      int j = wmap->locations[id].hideInv.nhides;
      for(int i = 0; i < wmap->locations[id].hideInv.nhides; i++)
      {
        if(hideIndex < wmap->locations[id].hideInv.index[i])
        {
          j = i;
          break;
        }
      }

      // Shift down the index vector
      if(j < wmap->locations[id].hideInv.nhides)
      {
        for(int i = wmap->locations[id].hideInv.nhides - 1; i >= j ; i--)
        {
          wmap->locations[id].hideInv.index[i + 1] = wmap->locations[id].hideInv.index[i];
        }
      }

      wmap->locations[id].hideInv.index[j] = hideIndex;
      wmap->locations[id].hideInv.nhides++;
    }

    // Add selected hide to item shop inventory, and update mass of item shop inventory
    wmap->locations[id].hideInv.count[hideIndex]++;
    wmap->locations[id].hideInv.mass += hide.mass;

    // Compute the number of active hides in the item shop
    wmap->locations[id].hideInv.nhides = 0;
    for(int i = 0; i < NCREATURETYPES; i++)
    {
      if(wmap->locations[id].hideInv.count[i] > 0)
      {
        wmap->locations[id].hideInv.nhides++;
      }
    }

    // Remove hide from player's inventory
    hideInv.count[hideIndex]--;
    hideInv.mass -= hide.mass;

    // Update number of active hides in player's inventory
    int n = 0;
    for(int i = 0; i < NCREATURETYPES; i++)
    {
      if(hideInv.count[i] > 0)
      {
        hideInv.index[n++] = i;
      }
    }
    hideInv.nhides = CLAMP(0, NCREATURETYPES - 1, n);

    // Update player's status
    updateStatus();

    // Print to message log
    sprintf(buffer, "Sold a(n) %s\n", hide.label);
    game.menu.updateMessageLog(buffer);
  }
}

// This method changes the relevant equipment
void Player::changeEquipment(int iEquip, int index)
{
  char buffer[CHARMAX];

  switch(iEquip)
  {
    // Equipment for the right hand
    case WEAPON:
    {
      // Check if index is valid
      if(index < NWEAPON)
      {
        equipInv.mass -= equipInv.equiped[WEAPON].mass;    // Remove mass of current weapon
        base.hpmax -= equipInv.equiped[WEAPON].stats.hpmax;
        base.mpmax -= equipInv.equiped[WEAPON].stats.mpmax;

        equipInv.equiped[WEAPON] = equipInv.Weapons[index];  // Select the specified weapon

        equipInv.mass += equipInv.equiped[WEAPON].mass;    // Add mass of current weapon
        base.hpmax += equipInv.equiped[WEAPON].stats.hpmax;
        base.mpmax += equipInv.equiped[WEAPON].stats.mpmax;
      }
      else
      {
        // Print to message log
        sprintf(buffer, "No such weapon\n");
        game.menu.updateMessageLog(buffer);
      }
      break;
    }
    // Equipment for the left hand
    case SHIELD:
    {
      // Check if index is valid
      if(index < NSHIELD)
      {
        equipInv.mass -= equipInv.equiped[SHIELD].mass;    // Remove mass of current shield
        base.hpmax -= equipInv.equiped[SHIELD].stats.hpmax;
        base.mpmax -= equipInv.equiped[SHIELD].stats.mpmax;

        equipInv.equiped[SHIELD] = equipInv.Shields[index];  // Select the specified shield

        equipInv.mass += equipInv.equiped[SHIELD].mass;    // Add mass of current shield
        base.hpmax += equipInv.equiped[SHIELD].stats.hpmax;
        base.mpmax += equipInv.equiped[SHIELD].stats.mpmax;
      }
      else
      {
        // Print to message log
        sprintf(buffer, "No such shield\n");
        game.menu.updateMessageLog(buffer);
      }
      break;
    }
    // Equipment for the body
    case ARMOUR:
    {
      // Check if index is valid
      if(index < NARMOUR)
      {
        equipInv.mass -= equipInv.equiped[ARMOUR].mass;    // Remove mass of current armour
        base.hpmax -= equipInv.equiped[ARMOUR].stats.hpmax;
        base.mpmax -= equipInv.equiped[ARMOUR].stats.mpmax;

        equipInv.equiped[ARMOUR] = equipInv.Armours[index];  // Select the specified armour

        equipInv.mass += equipInv.equiped[ARMOUR].mass;    // Add mass of current armour
        base.hpmax += equipInv.equiped[ARMOUR].stats.hpmax;
        base.mpmax += equipInv.equiped[ARMOUR].stats.mpmax;
      }
      else
      {
        // Print to message log
        sprintf(buffer, "No such armour\n");
        game.menu.updateMessageLog(buffer);
      }
      break;
    }
    // Equipment for the Accessory
    case ACCESSORY:
    {
      // Check if index is valid
      if(index < NACCESSORY)
      {
        equipInv.mass -= equipInv.equiped[ACCESSORY].mass;    // Remove mass of current right accessory
        base.hpmax -= equipInv.equiped[ACCESSORY].stats.hpmax;
        base.mpmax -= equipInv.equiped[ACCESSORY].stats.mpmax;

        equipInv.equiped[ACCESSORY] = equipInv.Accessory[index];  // Select the specified right accessory

        equipInv.mass += equipInv.equiped[ACCESSORY].mass;    // Add mass of current right accessory
        base.hpmax += equipInv.equiped[ACCESSORY].stats.hpmax;
        base.mpmax += equipInv.equiped[ACCESSORY].stats.mpmax;
      }
      else
      {
        // Print to message log
        sprintf(buffer, "No such accessory\n");
        game.menu.updateMessageLog(buffer);
      }
      break;
    }
    default: break;
  }

  // Update player stats
  updateStats();

  // Update player's status
  updateStatus();
}

// A method to add a specified hide to the inventory
bool Player::addHide(int hideIndex)
{
  bool status = true;
  char buffer[CHARMAX];

  // Selected hide
  Hide hide = hideInv.hides[hideIndex];

  // Update the quantity of specified hide
  if(hideInv.count[hideIndex] < 99 && (itemInv.mass + equipInv.mass + hideInv.mass + hide.mass) < static_cast<float>(stats.str))
  {
    // A new hide is added to the inventory
    if(hideInv.count[hideIndex] == 0)
    {
      // Locate the position in the index vector for the new hide
      int j = hideInv.nhides;
      for(int i = 0; i < hideInv.nhides; i++)
      {
        if(hideIndex < hideInv.index[i])
        {
          j = i;
          break;
        }
      }

      // Shift down the index vector
      if(j < hideInv.nhides) for(int i = hideInv.nhides - 1; i >= j ; i--) hideInv.index[i + 1] = hideInv.index[i];

      hideInv.index[j] = hideIndex;

      hideInv.nhides++;
    }

    // Add selected item to item inventory, and update mass of item inventory
    hideInv.count[hideIndex]++;
    hideInv.mass += hide.mass;

    // Compute the number of active items
    hideInv.nhides = 0;
    for(int i = 0; i < NCREATURETYPES; i++) if(hideInv.count[i] > 0) hideInv.nhides++;

    // Update player's status
    updateStatus();

    // Print to message log
    sprintf(buffer, "Found a(n) %s\n", hide.label);
    game.menu.updateMessageLog(buffer);

    status = true;
  }
  else
  {
    // Print to message log
    sprintf(buffer, "Cannot carry any more hides\n");
    game.menu.updateMessageLog(buffer);

    status = false;
  }
  return status;
}

// This method computes the experience points necessary for a give level
int Player::xpLevel(int level)
{
  return static_cast<int>(1.0e-02 + 2.50e+05*pow(static_cast<double>(level)/static_cast<double>(LEVELMAX),2));
}

// This method computes the Max. HP for a given level
int Player::hpLevel(int level)
{
  return static_cast<int>(HPMIN + (HPMAX - HPMIN)*pow(static_cast<float>(level + 2)/static_cast<float>(LEVELMAX + 2),2));
}

// This method computes the AP for a given level
int Player::apLevel(int level)
{
  return static_cast<int>(APMIN + (APMAX - APMIN)*static_cast<float>(level)/static_cast<float>(LEVELMAX));
}

// This method computes the DP for a given level
int Player::dpLevel(int level)
{
  return static_cast<int>(DPMIN + (DPMAX - DPMIN)*static_cast<float>(level)/static_cast<float>(LEVELMAX));
}

// This method computes the STR for a given level
int Player::strLevel(int level)
{
  return static_cast<int>(STRMIN + (STRMAX - STRMIN)*static_cast<float>(level)/static_cast<float>(LEVELMAX));
}

// This method computes the SPD for a given level
int Player::spdLevel(int level)
{
  return static_cast<int>(SPDMIN + (SPDMAX - SPDMIN)*static_cast<float>(level)/static_cast<float>(LEVELMAX));
}

// This method computes the Max. MP for a given level
int Player::mpLevel(int level)
{
  return static_cast<int>(MPMIN + (MPMAX - MPMIN)*pow(static_cast<float>(level + 2)/static_cast<float>(LEVELMAX + 2),2));
}

// This method computes the MAP for a given level
int Player::mapLevel(int level)
{
  return static_cast<int>(MAPMIN + (MAPMAX - MAPMIN)*static_cast<float>(level)/static_cast<float>(LEVELMAX));
}

// This method computes the MDP for a given level
int Player::mdpLevel(int level)
{
  return static_cast<int>(MDPMIN + (MDPMAX - MDPMIN)*static_cast<float>(level)/static_cast<float>(LEVELMAX));
}

// This method computes the WIL for a given level
int Player::wilLevel(int level)
{
  return static_cast<int>(WILMIN + (WILMAX - WILMIN)*static_cast<float>(level)/static_cast<float>(LEVELMAX));
}

// This method computes the ACU for a given level
int Player::acuLevel(int level)
{
  return static_cast<int>(ACUMIN + (ACUMAX - ACUMIN)*static_cast<float>(level)/static_cast<float>(LEVELMAX));
}
