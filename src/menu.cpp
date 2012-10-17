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

// The constructor
Menu::Menu(): selection(NONE), subselection(NONE), displayInfoPage(false), displayGameMenu(false), displayItemShopMenu(false), displayEquipShopMenu(false), displayInnMenu(false), displayFerryMenu(false), displayDeathMsg(false), inGame(false)
{
  //int w = 3*DISPLAY_WIDTH/4 - 2, h = NMSGS + 4;
  //int x = 0, y = DISPLAY_HEIGHT + 3;

  // Background image for main menu
  bg_img = new TCODImage("data/img/menu_bg.png");

  con = NULL;
  subcon = NULL;
  msgcon = NULL;
}

// This method updates the main menu
void Menu::updateMainMenu(TCOD_key_t key)
{
  static int menuCursor = 0;
  //int w = 24, h = DISPLAY_HEIGHT/2;
  int w = 64, h = DISPLAY_HEIGHT/2;
  const char options[NMAIN][CHARMAX] = {
            "%cNew Game %c",
            "%cLoad Game%c",
            "%cGame Info%c",
            "%cQuit Game%c"};

  // Main menu screen
  con = new TCODConsole(w, h);

  // Key handler
  switch(key.vk)
  {
    case TCODK_DOWN:
    {
      // Move the cursor position down
      menuCursor = (menuCursor + 1) % NMAIN;
      break;
    }
    case TCODK_UP:
    {
      // Move the cursor position up
      menuCursor--;
      if(menuCursor < 0) menuCursor = NMAIN - 1;
      break;
    }
    case TCODK_ENTER:
    {
      // Select the item at the current cursor position
      selection = menuCursor;
      break;
    }
    default: break;
  }

  // Print game title and by line
  con->setAlignment(TCOD_LEFT);
  con->setBackgroundFlag(TCOD_BKGND_SET);
  con->setDefaultBackground(TCODColor::black);
  con->setDefaultForeground(TCODColor::white);
  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::white, TCODColor::lightBlue);

  int x = 2, y = 2;
  con->print(x, y, "%cThe Serpentine Caves%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
  con->print(x, h - 3, "%cv"VERSION"%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
  //con->print(x, h - 1, "%cChris Capobianco%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

  //int istart = 256;
  //for(int i = 0; i < 32; i++) con->putChar(x + i, h - 12, istart + i, TCOD_BKGND_NONE); istart += 32;
  //for(int i = 0; i < 32; i++) con->putChar(x + i, h - 11, istart + i, TCOD_BKGND_NONE); istart += 32;
  //for(int i = 0; i < 32; i++) con->putChar(x + i, h - 10, istart + i, TCOD_BKGND_NONE); istart += 32;
  //for(int i = 0; i < 32; i++) con->putChar(x + i, h - 9,  istart + i, TCOD_BKGND_NONE); istart += 32;
  //for(int i = 0; i < 32; i++) con->putChar(x + i, h - 8,  istart + i, TCOD_BKGND_NONE); istart += 32;
  //for(int i = 0; i < 32; i++) con->putChar(x + i, h - 7,  istart + i, TCOD_BKGND_NONE); istart += 32;

  // Print the menu options
  y = NMAIN;
  for(int i = 0; i < NMAIN; i++)
  {
    y += 2;
    if(i == menuCursor)
    {
      // Print currently selected item
      con->print(x, y, options[i], TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    }
    else
    {
      // Print all other menu items
      con->print(x, y, options[i], TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    }
  }
}

// This method renders the main menu
void Menu::renderMainMenu()
{
  //int w = 24, w2 = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int w = 64, w2 = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;

  // Blit the background image to the root console
  TCODConsole::root->clear();
  bg_img->blit2x(TCODConsole::root, 0, h/4);

  // Blit the main menu to the root console
  TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, w2/4, 3*h/4, 1.0f, 1.0f);
}

// This method updates the info page
void Menu::updateInfoPage(TCOD_key_t key)
{
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int xend = w - 8, yend = h - 4;
  const char options[NINFO][CHARMAX] = {
            "Move/Attack        :: Arrow Keys       ",
            "Use Magic          :: Left Mouse Button",
            "Select Magic       :: Control          ",
            "Toggle Menu/Cancel :: Escape           ",
            "Select/Action      :: Enter            ",
            "Toggle Music       :: Pause            ",
            "Toggle Fullscreen  :: Alt + Enter      ",
            "Screen Capture     :: Backspace        "};

  // The info screen
  subcon = new TCODConsole(w, h);

  if(key.vk == TCODK_ENTER)
  {
    selection = NONE;
    displayInfoPage = false;
  }

  // Set colours for frame and title
  subcon->setAlignment(TCOD_LEFT);
  subcon->setBackgroundFlag(TCOD_BKGND_SET);
  subcon->setDefaultBackground(TCODColor::black);
  subcon->setDefaultForeground(TCODColor::white);
  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);

  // Print frame and title
  subcon->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Game Info");

  // Print the information page contents
  int x = 4, y = 6;
  subcon->print(x, y, "%cCommands%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

  y += 2;
  for(int i = 0; i < NINFO; i++) subcon->print(x, y++, options[i]);

  x = 4; y += 4;
  subcon->print(x, y, "%cSaving%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
  y += 2;
  subcon->printRect(x, y, xend, yend, "Whenever the Player returns to the %cWorld Map%c, the game will automatically overwrite the existing save file.\n\n\nIf the Player expires, death is %cpermanent%c as the save file is %cdeleted%c.", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

  subcon->print(xend, yend + 2, "%c[Enter]%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
}

// This method renders the info page
void Menu::renderInfoPage()
{
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2, h2;

  // Blit the info screen to the root console
  if(inGame)
  {
    h2 = h/2;
    TCODConsole::blit(subcon, 0, 0, w, h, TCODConsole::root, w/2, h2, 1.0f, 1.0f);
  }
  else
  {
    h2 = SCREEN_HEIGHT/2 - h/2 + 1;
    TCODConsole::blit(subcon, 0, 0, w, h, TCODConsole::root, w/2, h2, 1.0f, 0.75f);
  }
}

// This method updates the introduction page
bool Menu::updateIntroPage(TCOD_key_t key)
{
  static int intro_page = INTRO_01;
  bool status = true;
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int xstart = 4, ystart = 9, xend = w - 8, yend = h - 4;

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);

  // The Introduction Screen
  con = new TCODConsole(w, h);

  if(key.vk == TCODK_ENTER)
  {
    selection = NONE;
    intro_page++;

    if(intro_page >= NINTRO) status = false;
  }

  switch(intro_page)
  {
    case INTRO_01:
    {
      // Clear the menu screen
      con->clear();

      // Set colours
      con->setAlignment(TCOD_LEFT);
      con->setBackgroundFlag(TCOD_BKGND_SET);
      con->setDefaultBackground(TCODColor::black);
      con->setDefaultForeground(TCODColor::white);

      // Print frame and title
      con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Introduction");

      // Print the introduction page contents
      con->printRect(xstart, ystart, xend, yend, "Welome brave adventurer, thank you for heeding my pleas for help.\n\n\nI am the %cGuardian of Light%c, one of the five entrusted to protect this world.\n\n\nA %cPowerful Ancient Menace%c is gathering once again in the shadows, and threatens to destroy the peace and harmony of these lands.\n\n\nThis is why I have summoned you here, I must impress upon you to persue a perilous quest to rid the world of this threat.", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

      con->print(xend, yend + 2, "%c[Enter]%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

      break;
    }
    case INTRO_02:
    {
      // Clear the menu screen
      con->clear();

      // Set colours
      con->setAlignment(TCOD_LEFT);
      con->setBackgroundFlag(TCOD_BKGND_SET);
      con->setDefaultBackground(TCODColor::black);
      con->setDefaultForeground(TCODColor::white);

      // Print frame and title
      con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Introduction");

      // Print the introduction page contents
      con->printRect(xstart, ystart, xend, yend, "We know this power is gathering deep within\n%cThe Serpentine Caves%c, but where we know not.\n\n\nIt will be a difficult journey, so seek out the other four %cElemental Guardians%c for assistance. If they deem you worthy, they will grant you the ability to use their power.\n\n\nTo aid you on your quest I will grant my %cPower of Light%c, and any creature of the dark will be startled by its brilliance. Use this power wisely.\n\n\nGood luck brave hero, and may the record of your deeds be sung throughout the ages.", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

      con->print(xend, yend + 2, "%c[Enter]%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

      break;
    }
    default: break;
  }
  return status;
}

// This method renders the introduction page
void Menu::renderIntroPage()
{
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;

  // Blit the introduction screen to the root console
  TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, w/2, h/2, 1.0f, 0.75f);
}

// This method updates the game menu
bool Menu::updateGameMenu(TCOD_key_t key)
{
  static int menuCursor = 0;
  static int subMenuCursor = 0;
  static int subSubMenuCursor = -1;
  int neq;
  bool status = false;
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int ws = w - 17, hs = h - 2;
  const char options[NGAME][CHARMAX] = {
            "%cEquipment%c",
            "%cInventory%c",
            "%cExit Game%c"};

  // Game menu screen
  con = new TCODConsole(w, h);

  // Game submenu screen
  subcon = new TCODConsole(ws, hs);

  game.player.updateStats();

  // Key handler
  switch(key.vk)
  {
    case TCODK_DOWN:
    {
      // Move the cursor position down
      if(selection == GAME_EQUIP)
      {
        if(subselection == CHANGE_EQUIP)
        {
          switch(subMenuCursor)
          {
            case WEAPON: neq = NWEAPON; break;
            case SHIELD: neq = NSHIELD; break;
            case ARMOUR: neq = NARMOUR; break;
            case ACCESSORY: neq = NACCESSORY; break;
            default: break;
          }
          subSubMenuCursor = (subSubMenuCursor + 1) % MAX(1, neq);
        }
        else
        {
          subMenuCursor = (subMenuCursor + 1) % MAX(1, NEQUIPTYPE);
        }
      }
      else if(selection == GAME_ITEMS)
      {
        subMenuCursor = (subMenuCursor + 1) % MAX(1, game.player.itemInv.nitems);
      }
      else
      {
        menuCursor = (menuCursor + 1) % NGAME;
      }
      break;
    }
    case TCODK_UP:
    {
      // Move the cursor position up
      if(selection == GAME_EQUIP)
      {
        if(subselection == CHANGE_EQUIP)
        {
          switch(subMenuCursor)
          {
            case WEAPON: neq = NWEAPON; break;
            case SHIELD: neq = NSHIELD; break;
            case ARMOUR: neq = NARMOUR; break;
            case ACCESSORY: neq = NACCESSORY; break;
            default: break;
          }
          subSubMenuCursor--;
          if(subSubMenuCursor < 0) subSubMenuCursor = MAX(0, neq - 1);
        }
        else
        {
          subMenuCursor--;
          if(subMenuCursor < 0) subMenuCursor = MAX(0, NEQUIPTYPE - 1);
        }
      }
      else if(selection == GAME_ITEMS)
      {
        subMenuCursor--;
        if(subMenuCursor < 0) subMenuCursor = MAX(0, game.player.itemInv.nitems - 1);
      }
      else
      {
        menuCursor--;
        if(menuCursor < 0) menuCursor = NGAME - 1;
      }
      break;
    }
    case TCODK_ENTER:
    {
      // Select the item at the current cursor position
      if(selection == GAME_EQUIP)
      {
        if(subselection == CHANGE_EQUIP)
        {
          game.player.changeEquipment(subMenuCursor, subSubMenuCursor);
        }
        else
        {
          subSubMenuCursor = 0;
        }
        subselection = CHANGE_EQUIP;
      }
      else if(selection == GAME_ITEMS && game.player.itemInv.nitems > 0)
      {
        game.player.useItem(&subMenuCursor);
      }
      else
      {
        selection = menuCursor;
      }
      break;
    }
    case TCODK_ESCAPE:
    {
      if(selection == GAME_EQUIP)
      {
        if(subselection == CHANGE_EQUIP)
        {
          // Reset submenu cursor
          subselection = NONE;
          subSubMenuCursor = -1;
        }
        else
        {
          // Reset submenu cursor
          selection = NONE;
          subselection = NONE;
          subMenuCursor = 0;
          subSubMenuCursor = -1;
        }
      }
      else if(selection == GAME_ITEMS)
      {
        // Reset submenu cursor
        selection = NONE;
        subselection = NONE;
        subMenuCursor = 0;
        subSubMenuCursor = -1;
      }
      else
      {
        // Reset menu cursor
        menuCursor = 0;
      }
      break;
    }
    default: break;
  }

  if(selection == GAME_EXIT)
  {
    menuCursor = 0;
    subMenuCursor = 0;
    subSubMenuCursor = -1;
    displayGameMenu = false;
    status = true;
  }

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);

  // Set colours for frame and title
  con->setAlignment(TCOD_LEFT);
  con->setBackgroundFlag(TCOD_BKGND_SET);
  con->setDefaultBackground(TCODColor::black);
  con->setDefaultForeground(TCODColor::white);

  // Set colours for submenu
  subcon->setAlignment(TCOD_LEFT);
  subcon->setBackgroundFlag(TCOD_BKGND_SET);
  subcon->setDefaultBackground(TCODColor::black);
  subcon->setDefaultForeground(TCODColor::white);

  // Print frame and title
  con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET);
  con->printFrame(1, 1, 15, 2*NGAME + 3, false, TCOD_BKGND_SET);
  con->printFrame(1, 2*NGAME + 4, 15, h - 11, false, TCOD_BKGND_SET);

  int x = 3, y = 12;
  con->print(x, y, "%cHP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x + 4, y++, "%d/%d", game.player.stats.hp, game.player.stats.hpmax);
  y++;

  con->print(x, y, "%cMP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x + 4, y++, "%d/%d", game.player.stats.mp, game.player.stats.mpmax);
  y++;

  con->print(x, y++, "%cStatus:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  for(int i = 0; i < 5; i++) if(game.player.health.status[i]) con->print(x, y, "%s", game.player.health.name[i]);

  for(int i = 5; i < NSTATUS; i++)
  {
    if(game.player.health.status[i])
    {
      y++;
      con->print(x, y, "%s", game.player.health.name[i]);
    }
  }

  y = 29;
  con->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x + 4, y++, "%d", game.player.gp);
  y++;

  // Compute the elapsed time in convenient units
  int nhours = static_cast<int>(game.elapsedTime/(60.0f*60.0f));
  float time = game.elapsedTime - (60.0f*60.0f)*static_cast<float>(nhours);
  int nmins = static_cast<int>(time/60.0f);
  int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

  con->print(x, y++, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x, y, "%02d:%02d:%02d", nhours, nmins, nsecs);

  // Print the menu options
  y = 1;
  for(int i = 0; i < NGAME; i++)
  {
    y += 2;
    if(i == menuCursor)
    {
      // Print each item
      con->print(x, y, options[i], TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

      switch(menuCursor)
      {
        case GAME_EQUIP:
        {
          subcon->printFrame(0, 0, ws, NEQUIPTYPE + 8, false, TCOD_BKGND_SET);
          subcon->printFrame(0, NEQUIPTYPE + 8, 20, hs - (NEQUIPTYPE + 8), false, TCOD_BKGND_SET);
          subcon->printFrame(20, NEQUIPTYPE + 8, ws - 20, hs - (NEQUIPTYPE + 8), false, TCOD_BKGND_SET);
          updateEquipMenu(subMenuCursor, subSubMenuCursor);
          break;
        }
        case GAME_ITEMS:
        {
          subcon->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);
          updateItemMenu(subMenuCursor);
          break;
        }
        default:
        {
          subcon->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);
          break;
        }
      }
    }
    else
    {
      // Print each item
      con->print(x, y, options[i], TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    }
  }
  return status;
}

// This method renders the game menu
void Menu::renderGameMenu()
{
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int ws = w - 17, hs = h - 2;

  // Blit the game menu and submenu to the root console
  TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, w/2, h/2, 1.0f, 1.0f);
  TCODConsole::blit(subcon, 0, 0, ws, hs, TCODConsole::root, w/2 + 16, h/2 + 1, 1.0f, 1.0f);
}

// This method updates the stats menu
void Menu::updateEquipMenu(int subMenuCursor, int subSubMenuCursor)
{
  int h = DISPLAY_HEIGHT/2, hs = h - 2;
  int z, zp;
  char tmp[CHARMAX];

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

  // Equipment
  int x = 3, y = 3;
  subcon->print(x, y, "%cEquipment%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
  y += 2;

  if(selection == GAME_EQUIP)
  {
    // List Current Equipment
    for(int i = 0; i < NEQUIPTYPE; i++)
    {
      // Highlight Selection
      if(i == subMenuCursor)
      {
        subcon->print(x, y, game.player.equipInv.equiped[i].label, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
        subcon->print(x + 13, y, game.player.equipInv.equiped[i].name, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x, y, game.player.equipInv.equiped[i].label, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
        subcon->print(x + 13, y, game.player.equipInv.equiped[i].name, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
      y++;
    }

    Stats stats = game.player.stats;
    y = NEQUIPTYPE + 11;
    switch(subMenuCursor)
    {
      case WEAPON:
      {
        subcon->print(x + 20, y, "%cWeapon List%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
        y += 2;

        for(int j = 0; j < NWEAPON; j++)
        {
          if(j == subSubMenuCursor)
          {
            subcon->print(x + 20, y++, game.player.equipInv.Weapons[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
            subcon->print(x + 20, hs - 3, game.player.equipInv.Weapons[j].desc);

            stats -= game.player.equipInv.equiped[WEAPON].stats;
            stats.hpmax -= game.player.equipInv.equiped[WEAPON].stats.hpmax;
            stats.mpmax -= game.player.equipInv.equiped[WEAPON].stats.mpmax;

            stats += game.player.equipInv.Weapons[j].stats;
            stats.hpmax += game.player.equipInv.Weapons[j].stats.hpmax;
            stats.mpmax += game.player.equipInv.Weapons[j].stats.mpmax;
          }
          else
          {
            subcon->print(x + 20, y++, game.player.equipInv.Weapons[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
          }
        }
        break;
      }
      case SHIELD:
      {
        subcon->print(x + 20, y, "%cShield List%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
        y += 2;

        for(int j = 0; j < NSHIELD; j++)
        {
          if(j == subSubMenuCursor)
          {
            subcon->print(x + 20, y++, game.player.equipInv.Shields[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
            subcon->print(x + 20, hs - 3, game.player.equipInv.Shields[j].desc);

            stats -= game.player.equipInv.equiped[SHIELD].stats;
            stats.hpmax -= game.player.equipInv.equiped[SHIELD].stats.hpmax;
            stats.mpmax -= game.player.equipInv.equiped[SHIELD].stats.mpmax;

            stats += game.player.equipInv.Shields[j].stats;
            stats.hpmax += game.player.equipInv.Shields[j].stats.hpmax;
            stats.mpmax += game.player.equipInv.Shields[j].stats.mpmax;
          }
          else
          {
            subcon->print(x + 20, y++, game.player.equipInv.Shields[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
          }
        }
        break;
      }
      case ARMOUR:
      {
        subcon->print(x + 20, y, "%cArmour List%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
        y += 2;

        for(int j = 0; j < NARMOUR; j++)
        {
          if(j == subSubMenuCursor)
          {
            subcon->print(x + 20, y++, game.player.equipInv.Armours[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
            subcon->print(x + 20, hs - 3, game.player.equipInv.Armours[j].desc);

            stats -= game.player.equipInv.equiped[ARMOUR].stats;
            stats.hpmax -= game.player.equipInv.equiped[ARMOUR].stats.hpmax;
            stats.mpmax -= game.player.equipInv.equiped[ARMOUR].stats.mpmax;

            stats += game.player.equipInv.Armours[j].stats;
            stats.hpmax += game.player.equipInv.Armours[j].stats.hpmax;
            stats.mpmax += game.player.equipInv.Armours[j].stats.mpmax;
          }
          else
          {
            subcon->print(x + 20, y++, game.player.equipInv.Armours[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
          }
        }
        break;
      }
      case ACCESSORY:
      {
        subcon->print(x + 20, y, "%cAccessory List%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
        y += 2;

        for(int j = 0; j < NACCESSORY; j++)
        {
          if(j == subSubMenuCursor)
          {
            subcon->print(x + 20, y++, game.player.equipInv.Accessory[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
            subcon->print(x + 20, hs - 3, game.player.equipInv.Accessory[j].desc);

            stats -= game.player.equipInv.equiped[ACCESSORY].stats;
            stats.hpmax -= game.player.equipInv.equiped[ACCESSORY].stats.hpmax;
            stats.mpmax -= game.player.equipInv.equiped[ACCESSORY].stats.mpmax;

            stats += game.player.equipInv.Accessory[j].stats;
            stats.hpmax += game.player.equipInv.Accessory[j].stats.hpmax;
            stats.mpmax += game.player.equipInv.Accessory[j].stats.mpmax;
          }
          else
          {
            subcon->print(x + 20, y++, game.player.equipInv.Accessory[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
          }
        }
        break;
      }
      default: break;
    }

    // List Current Stats
    y = NEQUIPTYPE + 11;
    subcon->print(x, y, "%cStats%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
    subcon->putChar(x + 8, y, game.player.sym_right, TCOD_BKGND_NONE);
    y += 2;

    float xpfraction = static_cast<float>(game.player.xp)/static_cast<float>(game.player.xpnext);
    int xpbar = static_cast<int>(15.0f*xpfraction);
    if(xpbar > 0)
    {
      subcon->setDefaultBackground(TCODColor::darkGreen);
      subcon->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
    }
    if(xpbar < 15)
    {
      subcon->setDefaultBackground(TCODColor::darkerGreen);
      subcon->rect(x + xpbar, y + 1, 15 - xpbar, 1, true, TCOD_BKGND_SET);
    }
    subcon->setDefaultBackground(TCODColor::black);
    subcon->print(x, y, "%cLVL%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.lvl);
    subcon->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", game.player.xp, game.player.xpnext);

    y += 2;
    subcon->print(x, y,   "%cHPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y,   "%2d", game.player.stats.hpmax);
    if(subselection == CHANGE_EQUIP)
    {
      subcon->print(x + 10, y, "%c", TCOD_CHAR_ARROW_E);
      z = game.player.stats.hpmax; zp = stats.hpmax;
      sprintf(tmp, "%s%2d%s", "%c", zp, "%c");
      if(zp > z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else if(zp < z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
    }

    subcon->print(x, ++y,   "%cMPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y,   "%2d", game.player.stats.mpmax);
    if(subselection == CHANGE_EQUIP)
    {
      subcon->print(x + 10, y, "%c", TCOD_CHAR_ARROW_E);
      z = game.player.stats.mpmax; zp = stats.mpmax;
      sprintf(tmp, "%s%2d%s", "%c", zp, "%c");
      if(zp > z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else if(zp < z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
    }

    y++;
    subcon->print(x, ++y,   "%cATK%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y,   "%2d", game.player.stats.ap);
    if(subselection == CHANGE_EQUIP)
    {
      subcon->print(x + 10, y, "%c", TCOD_CHAR_ARROW_E);
      z = game.player.stats.ap; zp = stats.ap;
      sprintf(tmp, "%s%2d%s", "%c", zp, "%c");
      if(zp > z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else if(zp < z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
    }

    subcon->print(x, ++y,   "%cDEF%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y,   "%2d", game.player.stats.dp);
    if(subselection == CHANGE_EQUIP)
    {
      subcon->print(x + 10, y,   "%c", TCOD_CHAR_ARROW_E);
      z = game.player.stats.dp; zp = stats.dp;
      sprintf(tmp, "%s%2d%s", "%c", zp, "%c");
      if(zp > z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else if(zp < z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
    }

    subcon->print(x, ++y,   "%cSTR%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y,   "%2d", game.player.stats.str);
    if(subselection == CHANGE_EQUIP)
    {
      subcon->print(x + 10, y,   "%c", TCOD_CHAR_ARROW_E);
      z = game.player.stats.str; zp = stats.str;
      sprintf(tmp, "%s%2d%s", "%c", zp, "%c");
      if(zp > z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else if(zp < z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
    }

    subcon->print(x, ++y,   "%cSPD%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y,   "%2d", game.player.stats.spd);
    if(subselection == CHANGE_EQUIP)
    {
      subcon->print(x + 10, y,   "%c", TCOD_CHAR_ARROW_E);
      z = game.player.stats.spd; zp = stats.spd;
      sprintf(tmp, "%s%2d%s", "%c", zp, "%c");
      if(zp > z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else if(zp < z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
    }

    y++;
    subcon->print(x, ++y,   "%cM.ATK%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y,   "%2d", game.player.stats.map);
    if(subselection == CHANGE_EQUIP)
    {
      subcon->print(x + 10, y,   "%c", TCOD_CHAR_ARROW_E);
      z = game.player.stats.map; zp = stats.map;
      sprintf(tmp, "%s%2d%s", "%c", zp, "%c");
      if(zp > z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else if(zp < z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
    }

    subcon->print(x, ++y,   "%cM.DEF%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y,   "%2d", game.player.stats.mdp);
    if(subselection == CHANGE_EQUIP)
    {
      subcon->print(x + 10, y,   "%c", TCOD_CHAR_ARROW_E);
      z = game.player.stats.mdp; zp = stats.mdp;
      sprintf(tmp, "%s%2d%s", "%c", zp, "%c");
      if(zp > z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else if(zp < z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
    }

    subcon->print(x, ++y,   "%cWIL%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y,   "%2d", game.player.stats.wil);
    if(subselection == CHANGE_EQUIP)
    {
      subcon->print(x + 10, y,   "%c", TCOD_CHAR_ARROW_E);
      z = game.player.stats.wil; zp = stats.wil;
      sprintf(tmp, "%s%2d%s", "%c", zp, "%c");
      if(zp > z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else if(zp < z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
    }

    subcon->print(x, ++y,   "%cACU%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y,   "%2d", game.player.stats.acu);
    if(subselection == CHANGE_EQUIP)
    {
      subcon->print(x + 10, y,   "%c", TCOD_CHAR_ARROW_E);
      z = game.player.stats.acu; zp = stats.acu;
      sprintf(tmp, "%s%2d%s", "%c", zp, "%c");
      if(zp > z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else if(zp < z)
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x + 12, y, tmp, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
    }
  }
  else
  {
    for(int i = 0; i < NEQUIPTYPE; i++)
    {
      subcon->print(x, y, game.player.equipInv.equiped[i].label, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      subcon->print(x + 13, y, game.player.equipInv.equiped[i].name, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      y++;
    }

    y = NEQUIPTYPE + 11;
    subcon->print(x, y, "%cStats%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
    subcon->putChar(x + 8, y, game.player.sym_right, TCOD_BKGND_NONE);
    y += 2;

    float xpfraction = static_cast<float>(game.player.xp)/static_cast<float>(game.player.xpnext);
    int xpbar = static_cast<int>(15.0f*xpfraction);
    if(xpbar > 0)
    {
      subcon->setDefaultBackground(TCODColor::darkGreen);
      subcon->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
    }
    if(xpbar < 15)
    {
      subcon->setDefaultBackground(TCODColor::darkerGreen);
      subcon->rect(x + xpbar, y + 1, 15 - xpbar, 1, true, TCOD_BKGND_SET);
    }
    subcon->setDefaultBackground(TCODColor::black);
    subcon->print(x, y, "%cLVL%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.lvl);
    subcon->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", game.player.xp, game.player.xpnext);

    y += 2;
    subcon->print(x, y,   "%cHPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.stats.hpmax);
    subcon->print(x, y,   "%cMPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.stats.mpmax);

    y++;
    subcon->print(x, y,   "%cATK%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.stats.ap);
    subcon->print(x, y,   "%cDEF%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.stats.dp);

    subcon->print(x, y,   "%cSTR%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.stats.str);
    subcon->print(x, y,   "%cSPD%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.stats.spd);

    y++;
    subcon->print(x, y,   "%cM.ATK%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.stats.map);
    subcon->print(x, y,   "%cM.DEF%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.stats.mdp);

    subcon->print(x, y,   "%cWIL%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.stats.wil);
    subcon->print(x, y,   "%cACU%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 7, y++, "%2d", game.player.stats.acu);
  }
}

void Menu::updateItemMenu(int subMenuCursor)
{
  int yend = DISPLAY_HEIGHT/2 - 5;

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

  int x = 3, y = 3;
  subcon->print(x, y, "%cItem Inventory%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
  subcon->print(x + 27, y++, "%cQty%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

  if(selection == GAME_ITEMS)
  {
    for(int i = 0; i < game.player.itemInv.nitems; i++)
    {
      int j = game.player.itemInv.index[i];
      if(i == subMenuCursor)
      {
        subcon->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
        subcon->print(x + 24, y, " :: %2d", game.player.itemInv.count[j]);
        subcon->print(x, yend, game.player.itemInv.items[j].desc);
      }
      else
      {
        subcon->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
        subcon->print(x + 24, y, " :: %2d", game.player.itemInv.count[j]);
      }
    }
  }
  else
  {
    for(int i = 0; i < game.player.itemInv.nitems; i++)
    {
      int j = game.player.itemInv.index[i];
      subcon->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      subcon->print(x + 24, y, " :: %2d", game.player.itemInv.count[j]);
    }
  }

  y = DISPLAY_HEIGHT/2 - 16;
  subcon->print(x, y, "%cHide Inventory%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
  subcon->print(x + 27, y++, "%cQty%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

  for(int i = 0; i < game.player.hideInv.nhides; i++)
  {
    int j = game.player.hideInv.index[i];
    subcon->print(x, ++y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    subcon->print(x + 24, y, " :: %2d", game.player.hideInv.count[j]);
  }
}

// This method updates the item shop menu
bool Menu::updateItemShopMenu(TCOD_key_t key)
{
  static int menuCursor = 0;
  static int subMenuCursor = 0;
  bool status = false;
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int ws = w - 17, hs = h - 2;
  int xstart = 3, ystart = 3, xend = ws - 6, yend = hs - 6;
  const char options[NITEMSHOP][CHARMAX] = {
              "%cBuy Items %c",
              "%cSell Items%c",
              "%cExit Shop %c"};

  // Game menu screen
  con = new TCODConsole(w, h);

  // Game submenu screen
  subcon = new TCODConsole(ws, hs);

  int id = game.worldID - 1;
  WorldMap *wmap = &game.world[0];

  // Key handler
  switch(key.vk)
  {
    case TCODK_DOWN:
    {
      // Move the cursor position down
      if(selection == ITEMSHOP_BUY)
      {
        subMenuCursor = (subMenuCursor + 1) % MAX(1, wmap->locations[id].itemInv.nitems);
      }
      else if(selection == ITEMSHOP_SELL)
      {
        subMenuCursor = (subMenuCursor + 1) % MAX(1, game.player.itemInv.nitems + game.player.hideInv.nhides);
      }
      else
      {
        menuCursor = (menuCursor + 1) % NITEMSHOP;
      }
      break;
    }
    case TCODK_UP:
    {
      // Move the cursor position up
      if(selection == ITEMSHOP_BUY)
      {
        subMenuCursor--;
        if(subMenuCursor < 0) subMenuCursor = MAX(0, wmap->locations[id].itemInv.nitems - 1);
      }
      else if(selection == ITEMSHOP_SELL)
      {
        subMenuCursor--;
        if(subMenuCursor < 0) subMenuCursor = MAX(0, game.player.itemInv.nitems + game.player.hideInv.nhides - 1);
      }
      else
      {
        menuCursor--;
        if(menuCursor < 0) menuCursor = NITEMSHOP - 1;
      }
      break;
    }
    case TCODK_ENTER:
    {
      // Select the item at the current cursor position
      if(selection == ITEMSHOP_BUY)
      {
        game.player.buyItem(&subMenuCursor);
      }
      else if(selection == ITEMSHOP_SELL)
      {
        if(subMenuCursor < game.player.itemInv.nitems)
        {
          game.player.sellItem(&subMenuCursor);
        }
        else
        {
          game.player.sellHide(&subMenuCursor);
        }
      }
      else
      {
        selection = menuCursor;
      }
      break;
    }
    case TCODK_ESCAPE:
    {
      if(selection == ITEMSHOP_BUY || selection == ITEMSHOP_SELL)
      {
        // Reset submenu cursor
        selection = NONE;
        subMenuCursor = 0;
      }
      break;
    }
    default: break;
  }

  if(selection == ITEMSHOP_EXIT)
  {
    selection = NONE;
    menuCursor = 0;
    subMenuCursor = 0;
    displayItemShopMenu = false;

    // Toggle the volume for the item shop menu
    game.sound.toggleVolume(0.5f);
  }

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);

  // Set colours for frame and title
  con->setAlignment(TCOD_LEFT);
  con->setBackgroundFlag(TCOD_BKGND_SET);
  con->setDefaultBackground(TCODColor::black);
  con->setDefaultForeground(TCODColor::white);

  // Set colours for submenu
  subcon->setAlignment(TCOD_LEFT);
  subcon->setBackgroundFlag(TCOD_BKGND_SET);
  subcon->setDefaultBackground(TCODColor::black);
  subcon->setDefaultForeground(TCODColor::white);

  // Print frame and title
  con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Item Shop");
  con->printFrame(1, 1, 15, 2*NITEMSHOP + 3, false, TCOD_BKGND_SET);
  con->printFrame(1, 2*NITEMSHOP + 4, 15, h - 11, false, TCOD_BKGND_SET);

  int x = 3, y = 29;
  con->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x + 4, y++, "%d", game.player.gp);

  // Compute the elapsed time in convenient units
  int nhours = static_cast<int>(game.elapsedTime/(60.0f*60.0f));
  float time = game.elapsedTime - (60.0f*60.0f)*static_cast<float>(nhours);
  int nmins = static_cast<int>(time/60.0f);
  int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

  con->print(x, ++y, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x, ++y, "%02d:%02d:%02d", nhours, nmins, nsecs);

  // Print the menu options
  y = NITEMSHOP - 2;
  for(int i = 0; i < NITEMSHOP; i++)
  {
    y += 2;
    if(i == menuCursor)
    {
      // Print each item
      con->print(x, y, options[i], TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

      subcon->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

      switch(menuCursor)
      {
        case ITEMSHOP_BUY:
        {
          updateItemShopBuyMenu(subMenuCursor);
          break;
        }
        case ITEMSHOP_SELL:
        {
          updateItemShopSellMenu(subMenuCursor);
          break;
        }
        default:
        {
          // Hurry Back!
          subcon->printRect(xstart, ystart, xend, yend, "Come back any time.");
          break;
        }
      }
    }
    else
    {
      // Print each item
      con->print(x, y, options[i], TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    }
  }
  return status;
}

// This method renders the item shop menu
void Menu::renderItemShopMenu()
{
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int ws = w - 17, hs = h - 2;

  // Blit the game menu and submenu to the root console
  TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, w/2, h/2, 1.0f, 1.0f);
  TCODConsole::blit(subcon, 0, 0, ws, hs, TCODConsole::root, w/2 + 16, h/2 + 1, 1.0f, 1.0f);
}

// This method updates the item shop buy submenu
void Menu::updateItemShopBuyMenu(int subMenuCursor)
{
  int yend = DISPLAY_HEIGHT/2 - 5;

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

  int x = 3, y = 3;
  subcon->print(x, y, "%cItem Inventory%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
  subcon->print(x + 27, y++, "%cQty  GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

  int id = game.worldID - 1;
  WorldMap *wmap = &game.world[0];

  if(selection == ITEMSHOP_BUY)
  {
    for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
    {
      int j = wmap->locations[id].itemInv.index[i];
      if(i == subMenuCursor)
      {
        subcon->print(x, ++y, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
        subcon->print(x, yend, wmap->locations[id].itemInv.items[j].desc);
      }
      else
      {
        subcon->print(x, ++y, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      subcon->print(x + 24, y, " :: %2d", wmap->locations[id].itemInv.count[j]);
      subcon->print(x + 30, y, " %3d", wmap->locations[id].itemInv.price[j]);
    }
  }
  else
  {
    for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
    {
      int j = wmap->locations[id].itemInv.index[i];
      subcon->print(x, ++y, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      subcon->print(x + 24, y, " :: %2d", wmap->locations[id].itemInv.count[j]);
      subcon->print(x + 30, y, " %3d", wmap->locations[id].itemInv.price[j]);
    }
  }
}

// This method updates the item shop sell submenu
void Menu::updateItemShopSellMenu(int subMenuCursor)
{
  int yend = DISPLAY_HEIGHT/2 - 5;

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

  int x = 3, y = 3;
  subcon->print(x, y, "%cItem Inventory%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
  subcon->print(x + 27, y++, "%cQty  GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

  int id = game.worldID - 1;
  WorldMap *wmap = &game.world[0];

  if(selection == ITEMSHOP_SELL)
  {
    for(int i = 0; i < game.player.itemInv.nitems; i++)
    {
      int j = game.player.itemInv.index[i];
      if(i == subMenuCursor)
      {
        subcon->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
        subcon->print(x, yend, game.player.itemInv.items[j].desc);
      }
      else
      {
        subcon->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      subcon->print(x + 24, y, " :: %2d", game.player.itemInv.count[j]);
      subcon->print(x + 30, y, " %3d", MAX(1, wmap->locations[id].itemInv.price[j]/2));
    }

    y = DISPLAY_HEIGHT/2 - 16;
    subcon->print(x, y, "%cHide Inventory%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
    subcon->print(x + 27, y++, "%cQty  GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

    for(int i = 0; i < game.player.hideInv.nhides; i++)
    {
      int j = game.player.hideInv.index[i];
      if(i == subMenuCursor - game.player.itemInv.nitems)
      {
        subcon->print(x, ++y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
        subcon->print(x, yend, game.player.hideInv.hides[j].name, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      }
      else
      {
        subcon->print(x, ++y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      subcon->print(x + 24, y, " :: %2d", game.player.hideInv.count[j]);
      subcon->print(x + 30, y, " %3d", MAX(1, wmap->locations[id].hideInv.price[j]));
    }
  }
  else
  {
    for(int i = 0; i < game.player.itemInv.nitems; i++)
    {
      int j = game.player.itemInv.index[i];
      subcon->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      subcon->print(x + 24, y, " :: %2d", game.player.itemInv.count[j]);
      subcon->print(x + 30, y, " %3d", MAX(1, wmap->locations[id].itemInv.price[j]/2));
    }

    y = DISPLAY_HEIGHT/2 - 16;
    subcon->print(x, y, "%cHide Inventory%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
    subcon->print(x + 27, y++, "%cQty  GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

    for(int i = 0; i < game.player.hideInv.nhides; i++)
    {
      int j = game.player.hideInv.index[i];
      subcon->print(x, ++y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      subcon->print(x + 24, y, " :: %2d", game.player.hideInv.count[j]);
      subcon->print(x + 30, y, " %3d", MAX(1, wmap->locations[id].hideInv.price[j]));
    }
  }
}

// This method updates the equip shop menu
bool Menu::updateEquipShopMenu(TCOD_key_t key)
{
  static int menuCursor = 0;
  static int subMenuCursor = 0;
  bool status = false;
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int ws = w - 17, hs = h - 2;
  int xstart = 3, ystart = 3, xend = ws - 6, yend = hs - 6;
  const char options[NEQUIPSHOP][CHARMAX] = {
              "%cBuy Equip %c",
              "%cSell Equip%c",
              "%cExit Shop %c"};

  int id = game.worldID - 1;
  WorldMap *wmap = &game.world[0];

  // Game menu screen
  con = new TCODConsole(w, h);

  // Game submenu screen
  subcon = new TCODConsole(ws, hs);

  // Key handler
  switch(key.vk)
  {
    case TCODK_DOWN:
    {
      // Move the cursor position down
      if(selection == EQUIPSHOP_BUY)
      {
        subMenuCursor = (subMenuCursor + 1) % MAX(1, wmap->locations[id].itemInv.nitems);
      }
      else if(selection == EQUIPSHOP_SELL)
      {
        subMenuCursor = (subMenuCursor + 1) % MAX(1, NEQUIPTYPE);
      }
      else
      {
        menuCursor = (menuCursor + 1) % NEQUIPSHOP;
      }
      break;
    }
    case TCODK_UP:
    {
      // Move the cursor position up
      if(selection == EQUIPSHOP_BUY)
      {
        subMenuCursor--;
        if(subMenuCursor < 0) subMenuCursor = MAX(0, wmap->locations[id].itemInv.nitems - 1);
      }
      else if(selection == EQUIPSHOP_SELL)
      {
        subMenuCursor--;
        if(subMenuCursor < 0) subMenuCursor = MAX(0, NEQUIPTYPE - 1);
      }
      else
      {
        menuCursor--;
        if(menuCursor < 0) menuCursor = NEQUIPSHOP - 1;
      }
      break;
    }
    case TCODK_ENTER:
    {
      // Select the item at the current cursor position
      if(selection == EQUIPSHOP_BUY)
      {
        //game.player.buyEquip(&subMenuCursor);
        printf("Buy Equipment\n");
      }
      else if(selection == EQUIPSHOP_SELL)
      {
        //game.player.sellEquip(&subMenuCursor);
        printf("Sell Equipment\n");
      }
      else
      {
        selection = menuCursor;
      }
      break;
    }
    case TCODK_ESCAPE:
    {
      if(selection == EQUIPSHOP_BUY || selection == EQUIPSHOP_SELL)
      {
        // Reset submenu cursor
        selection = NONE;
        subMenuCursor = 0;
      }
      break;
    }
    default: break;
  }

  if(selection == EQUIPSHOP_EXIT)
  {
    selection = NONE;
    menuCursor = 0;
    subMenuCursor = 0;
    displayEquipShopMenu = false;

    // Toggle the volume for the equip shop menu
    game.sound.toggleVolume(0.5f);
  }

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);

  // Set colours for frame and title
  con->setAlignment(TCOD_LEFT);
  con->setBackgroundFlag(TCOD_BKGND_SET);
  con->setDefaultBackground(TCODColor::black);
  con->setDefaultForeground(TCODColor::white);

  // Set colours for submenu
  subcon->setAlignment(TCOD_LEFT);
  subcon->setBackgroundFlag(TCOD_BKGND_SET);
  subcon->setDefaultBackground(TCODColor::black);
  subcon->setDefaultForeground(TCODColor::white);

  // Print frame and title
  con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Equipment Shop");
  con->printFrame(1, 1, 15, 2*NITEMSHOP + 3, false, TCOD_BKGND_SET);
  con->printFrame(1, 2*NITEMSHOP + 4, 15, h - 11, false, TCOD_BKGND_SET);

  int x = 3, y = 29;
  con->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x + 4, y++, "%d", game.player.gp);

  // Compute the elapsed time in convenient units
  int nhours = static_cast<int>(game.elapsedTime/(60.0f*60.0f));
  float time = game.elapsedTime - (60.0f*60.0f)*static_cast<float>(nhours);
  int nmins = static_cast<int>(time/60.0f);
  int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

  con->print(x, ++y, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x, ++y, "%02d:%02d:%02d", nhours, nmins, nsecs);

  // Print the menu options
  y = NEQUIPSHOP - 2;
  for(int i = 0; i < NEQUIPSHOP; i++)
  {
    y += 2;
    if(i == menuCursor)
    {
      // Print each item
      con->print(x, y, options[i], TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

      subcon->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

      switch(menuCursor)
      {
        case ITEMSHOP_BUY:
        {
          updateEquipShopBuyMenu(subMenuCursor);
          break;
        }
        case ITEMSHOP_SELL:
        {
          updateEquipShopSellMenu(subMenuCursor);
          break;
        }
        default:
        {
          // Hurry Back!
          subcon->printRect(xstart, ystart, xend, yend, "Come back any time.");
          break;
        }
      }
    }
    else
    {
      // Print each item
      con->print(x, y, options[i], TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    }
  }
  return status;
}

// This method renders the equip shop menu
void Menu::renderEquipShopMenu()
{
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int ws = w - 17, hs = h - 2;

  // Blit the equip shop menu and submenu to the root console
  TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, w/2, h/2, 1.0f, 1.0f);
  TCODConsole::blit(subcon, 0, 0, ws, hs, TCODConsole::root, w/2 + 16, h/2 + 1, 1.0f, 1.0f);
}

// This method updates the equip shop buy submenu
void Menu::updateEquipShopBuyMenu(int subMenuCursor)
{
  int yend = DISPLAY_HEIGHT/2 - 5;

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

  int x = 3, y = 3;
  subcon->print(x, y, "%cEquipment Inventory%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
  subcon->print(x + 27, y++, "%cQty  GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

  int id = game.worldID - 1;
  WorldMap *wmap = &game.world[0];

  if(selection == EQUIPSHOP_BUY)
  {
    for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
    {
      int j = wmap->locations[id].itemInv.index[i];
      if(i == subMenuCursor)
      {
        subcon->print(x, ++y, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
        subcon->print(x, yend, wmap->locations[id].itemInv.items[j].desc);
      }
      else
      {
        subcon->print(x, ++y, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      subcon->print(x + 24, y, " :: %2d", wmap->locations[id].itemInv.count[j]);
      subcon->print(x + 30, y, " %3d", wmap->locations[id].itemInv.price[j]);
    }
  }
  else
  {
    for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
    {
      int j = wmap->locations[id].itemInv.index[i];
      subcon->print(x, ++y, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      subcon->print(x + 24, y, " :: %2d", wmap->locations[id].itemInv.count[j]);
      subcon->print(x + 30, y, " %3d", wmap->locations[id].itemInv.price[j]);
    }
  }
}

// This method updates the equip shop sell submenu
void Menu::updateEquipShopSellMenu(int subMenuCursor)
{
  int yend = DISPLAY_HEIGHT/2 - 5;

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

  int x = 3, y = 3;
  subcon->print(x, y++, "%cEquipment Inventory%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

  if(selection == EQUIPSHOP_SELL)
  {
    for(int i = 0; i < NEQUIPTYPE; i++)
    {
      if(i == subMenuCursor)
      {
        subcon->print(x, ++y, game.player.equipInv.equiped[i].label, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
        subcon->print(x, yend, game.player.equipInv.equiped[i].desc);
      }
      else
      {
        subcon->print(x, ++y, game.player.equipInv.equiped[i].label, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      subcon->print(x + 9, y, " :: %s", game.player.equipInv.equiped[i].name);
    }
  }
  else
  {
    for(int i = 0; i < NEQUIPTYPE; i++)
    {
      subcon->print(x, ++y, game.player.equipInv.equiped[i].label, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      subcon->print(x + 9, y, " :: %s", game.player.equipInv.equiped[i].name);
    }
  }
}

// This method updates the inn menu
bool Menu::updateInnMenu(TCOD_key_t key)
{
  static int menuCursor = 0;
  bool status = false;
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int ws = w - 17, hs = h - 2;
  int xstart = 3, ystart = 3, xend = ws - 6, yend = hs - 6;
  const char options[NINN][CHARMAX] = {
            "%cStay at Inn%c",
            "%cExit Inn   %c"};

  // Game menu screen
  con = new TCODConsole(w, h);

  // Game submenu screen
  subcon = new TCODConsole(ws, hs);

  // Key handler
  switch(key.vk)
  {
    case TCODK_DOWN:
    {
      // Move the cursor position down
      menuCursor = (menuCursor + 1) % NINN;
      break;
    }
    case TCODK_UP:
    {
      // Move the cursor position up
      menuCursor--;
      if(menuCursor < 0) menuCursor = NINN - 1;
      break;
    }
    case TCODK_ENTER:
    {
      // Select the item at the current cursor position
      if(menuCursor == INN_STAY)
      {
        if(game.player.gp >= 15)
        {
          // Goodnight
          subcon->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);
          subcon->printRect(xstart, ystart, xend, yend, "Goodnight.");

          // Blit the inn submenu to the root console
          TCODConsole::blit(subcon, 0, 0, ws, hs, TCODConsole::root, w/2 + 16, h/2 + 1, 1.0f, 1.0f);

          game.player.gp -= 15;
          game.player.stayInn();
          selection = INN_EXIT;
        }
      }
      else
      {
        selection = menuCursor;
      }
      break;
    }
    default: break;
  }

  if(selection == INN_EXIT)
  {
    selection = NONE;
    menuCursor = 0;
    displayInnMenu = false;

    // Toggle the volume for the item shop menu
    game.sound.toggleVolume(0.5f);
  }

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);

  // Set colours for frame and title
  con->setAlignment(TCOD_LEFT);
  con->setBackgroundFlag(TCOD_BKGND_SET);
  con->setDefaultBackground(TCODColor::black);
  con->setDefaultForeground(TCODColor::white);

  // Set colours for submenu
  subcon->setAlignment(TCOD_LEFT);
  subcon->setBackgroundFlag(TCOD_BKGND_SET);
  subcon->setDefaultBackground(TCODColor::black);
  subcon->setDefaultForeground(TCODColor::white);

  // Print frame and title
  con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Inn");
  con->printFrame(1, 1, 15, 2*(NINN + 1) + 3, false, TCOD_BKGND_SET);
  con->printFrame(1, 2*(NINN + 1) + 4, 15, h - 11, false, TCOD_BKGND_SET);

  int x = 3, y = 29;
  con->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x + 4, y++, "%d", game.player.gp);

  // Compute the elapsed time in convenient units
  int nhours = static_cast<int>(game.elapsedTime/(60.0f*60.0f));
  float time = game.elapsedTime - (60.0f*60.0f)*static_cast<float>(nhours);
  int nmins = static_cast<int>(time/60.0f);
  int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

  con->print(x, ++y, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x, ++y, "%02d:%02d:%02d", nhours, nmins, nsecs);

  // Print the menu options
  y = NINN - 1;
  for(int i = 0; i < NINN; i++)
  {
    y += 2;
    if(i == menuCursor)
    {
      // Print each item
      con->print(x, y, options[i], TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

      subcon->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

      if(menuCursor == INN_STAY)
      {
        // Stay Night at Inn
        subcon->printRect(xstart, ystart, xend, yend, "Hello there young traveller.\n\n\nCan I interest you in a nice hearty meal, and a warm comfortable bed?\n\n\nWe charge %c15 GP%c per night, meal included.\n\n\nWould you care to stay?", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else
      {
        // Hurry Back!
        subcon->printRect(xstart, ystart, xend, yend, "It is a shame to see you leave.\n\n\nPlease hurry back!");
      }
    }
    else
    {
      // Print each item
      con->print(x, y, options[i], TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    }
  }
  return status;
}

// This method renders the inn menu
void Menu::renderInnMenu()
{
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int ws = w - 17, hs = h - 2;

  // Blit the inn menu and submenu to the root console
  TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, w/2, h/2, 1.0f, 1.0f);
  TCODConsole::blit(subcon, 0, 0, ws, hs, TCODConsole::root, w/2 + 16, h/2 + 1, 1.0f, 1.0f);
}

// This method updates the ferry menu
bool Menu::updateFerryMenu(TCOD_key_t key)
{
  static int menuCursor = 0;
  bool status = false;
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int ws = w - 17, hs = h - 2;
  int xstart = 3, ystart = 3, xend = ws - 6, yend = hs - 6;
  //WorldMap *wmap = &game.world[0];
  int id = game.worldID - 1, idprev = id - 1, idnext = id + 1;
  char options[NFERRY][CHARMAX] = {
            "%cTake Ferry%c",
            "%cExit Ferry%c"};

  if(idprev < TOWN_01) idprev = TOWN_07;
  if(idnext > TOWN_07) idnext = TOWN_01;

  //sprintf(options[0], "%s%s%s", "%c", wmap->locations[idprev].name, "%c");
  //sprintf(options[1], "%s%s%s", "%c", wmap->locations[idnext].name, "%c");

  // Game menu screen
  con = new TCODConsole(w, h);

  // Game submenu screen
  subcon = new TCODConsole(ws, hs);

  // Key handler
  switch(key.vk)
  {
    case TCODK_DOWN:
    {
      // Move the cursor position down
      menuCursor = (menuCursor + 1) % NFERRY;
      break;
    }
    case TCODK_UP:
    {
      // Move the cursor position up
      menuCursor--;
      if(menuCursor < 0) menuCursor = NFERRY - 1;
      break;
    }
    case TCODK_ENTER:
    {
      // Select the item at the current cursor position
      if(menuCursor == FERRY_TAKE)
      {
        //if(game.player.gp >= 25)
        //{
        //  game.player.gp -= 25;
        //  game.player.takeFerry(idprev);
        //  selection = FERRY_EXIT;
        //}
      }
      else
      {
        selection = menuCursor;
      }
      break;
    }
    default: break;
  }

  if(selection == FERRY_EXIT)
  {
    selection = NONE;
    menuCursor = 0;
    displayFerryMenu = false;

    // Toggle the volume for the item shop menu
    game.sound.toggleVolume(0.5f);
  }

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);

  // Set colours for frame and title
  con->setAlignment(TCOD_LEFT);
  con->setBackgroundFlag(TCOD_BKGND_SET);
  con->setDefaultBackground(TCODColor::black);
  con->setDefaultForeground(TCODColor::white);

  // Set colours for submenu
  subcon->setAlignment(TCOD_LEFT);
  subcon->setBackgroundFlag(TCOD_BKGND_SET);
  subcon->setDefaultBackground(TCODColor::black);
  subcon->setDefaultForeground(TCODColor::white);

  // Print frame and title

  con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Ferry");
  con->printFrame(1, 1, 15, 2*NFERRY + 5, false, TCOD_BKGND_SET);
  con->printFrame(1, 2*NFERRY + 6, 15, h - 11, false, TCOD_BKGND_SET);

  int x = 3, y = 29;
  con->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x + 4, y++, "%d", game.player.gp);

  // Compute the elapsed time in convenient units
  int nhours = static_cast<int>(game.elapsedTime/(60.0f*60.0f));
  float time = game.elapsedTime - (60.0f*60.0f)*static_cast<float>(nhours);
  int nmins = static_cast<int>(time/60.0f);
  int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

  con->print(x, ++y, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  con->print(x, ++y, "%02d:%02d:%02d", nhours, nmins, nsecs);

  // Print the menu options
  y = 1;
  for(int i = 0; i < NFERRY; i++)
  {
    y += 2;
    if(i == menuCursor)
    {
      // Print each item
      con->print(x, y, options[i], TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

      subcon->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

      if(menuCursor == FERRY_TAKE)
      {
        // Travel to the previous town
        subcon->printRect(xstart, ystart, xend, yend, "Where are you headed?\n\n\nMy fee is %c25 GP%c per trip.", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
      }
      else
      {
        // Hurry Back!
        subcon->printRect(xstart, ystart, xend, yend, "Come back any time.");
      }
    }
    else
    {
      // Print each item
      con->print(x, y, options[i], TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    }
  }
  return status;
}

// This method renders the ferry menu
void Menu::renderFerryMenu()
{
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int ws = w - 17, hs = h - 2;

  // Blit the ferry menu and submenu to the root console
  TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, w/2, h/2, 1.0f, 1.0f);
  TCODConsole::blit(subcon, 0, 0, ws, hs, TCODConsole::root, w/2 + 16, h/2 + 1, 1.0f, 1.0f);
}

// This method updates the death message
bool Menu::updateDeathMsg(TCOD_key_t key)
{
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;
  int xstart = 4, ystart = 11, xend = w - 8, yend = h - 4;
  bool status = false;

  // The death message screen
  con = new TCODConsole(w, h);

  if(key.vk == TCODK_ENTER)
  {
    selection = GAME_EXIT;
    displayDeathMsg = false;
    status = true;
  }

  // Delete the current save file
  if(TCODSystem::fileExists(SAVEGAME_FILENAME)) TCODSystem::deleteFile(SAVEGAME_FILENAME);

  // Set colours
  con->setAlignment(TCOD_LEFT);
  con->setBackgroundFlag(TCOD_BKGND_SET);
  con->setDefaultBackground(TCODColor::black);
  con->setDefaultForeground(TCODColor::white);
  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);

  // Print frame and title
  con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Game Over");

  // Print the death page contents
  con->printRect(xstart, ystart, xend, yend, "While your valiant efforts should be commended, they were all for naught.\n\n\nThe %cAncient Menance%c spread across these lands, killing all those that could fight and enslaving the rest.\n\n\nEventhough your part in this tale is over, perhaps a %cNew Hero%c will one day emerge from the remnants of these broken and shattered people.", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

  con->print(xend, yend + 2, "%c[Enter]%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

  return status;
}

// This method renders the death message
void Menu::renderDeathMsg()
{
  int w = DISPLAY_WIDTH/2, h = DISPLAY_HEIGHT/2;

  // Blit the death message screen to the root console
  TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, w/2, h/2, 1.0f, 0.75f);
}

// This method updates the message log
void Menu::updateMessageLog(char msg[])
{
  int w = 3*DISPLAY_WIDTH/4 - 2, h = NMSGS + 4;

  // The message log
  msgcon = new TCODConsole(w, h);

  // Set colours for frame and title
  msgcon->setAlignment(TCOD_LEFT);
  msgcon->setBackgroundFlag(TCOD_BKGND_SET);
  msgcon->setDefaultBackground(TCODColor::black);
  msgcon->setDefaultForeground(TCODColor::white);

  // Print frame and title
  msgcon->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Message Log");

  // Shift previous entries down one index
  for(int i = NMSGS - 1; i > 0; i--) sprintf(messageLog[i], "%s", messageLog[i - 1]);

  // Store new message in the first entry of the activity log
  sprintf(messageLog[0], "%s", msg);

  // Print contents of activity log to con
  int x = 2, y = NMSGS + 1;
  for(int i = 0; i < NMSGS; i++) msgcon->print(x, y--, messageLog[i]);
}

// This method renders the message log
void Menu::renderMessageLog()
{
  int w = 3*DISPLAY_WIDTH/4 - 2, h = NMSGS + 4;
  int x = 0, y = DISPLAY_HEIGHT + 3;

  // Blit the message log to the root console
  TCODConsole::blit(msgcon, 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
}
