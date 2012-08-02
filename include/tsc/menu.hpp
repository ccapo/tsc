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

// Main menu option identifiers
enum EMainMenu
{
  MAIN_NEW,
  MAIN_LOAD,
  MAIN_HELP,
  MAIN_QUIT,
  NMAIN,
  NONE = 99
};

// Intro page identifiers
enum EIntroPage
{
  INTRO_01,
  INTRO_02,
  NINTRO
};

// Game menu option identifiers
enum EGameMenu
{
  GAME_EQUIP,
  GAME_ITEMS,
  GAME_EXIT,
  NGAME,
  CHANGE_EQUIP
};

// Item shop menu option identifiers
enum EItemShopMenu
{
  ITEMSHOP_BUY,
  ITEMSHOP_SELL,
  ITEMSHOP_EXIT,
  NITEMSHOP
};

// Equip shop menu option identifiers
enum EEquipShopMenu
{
  EQUIPSHOP_BUY,
  EQUIPSHOP_SELL,
  EQUIPSHOP_EXIT,
  NEQUIPSHOP
};

// Inn menu option identifiers
enum EInnMenu
{
  INN_STAY,
  INN_EXIT,
  NINN
};

// Ferry menu option identifiers
enum EFerryMenu
{
  FERRY_TAKE,
  FERRY_EXIT,
  NFERRY
};

// This class holds what's necessary for the menus and pages
class Menu
{
  public:
  int selection, subselection;      // Menu and Submenu Selection
  bool displayInfoPage;        // Switch to display Info Page
  bool displayGameMenu;        // Switch to display Game Menu
  bool displayItemShopMenu;      // Switch to display Item Shop Menu
  bool displayEquipShopMenu;      // Switch to display Equip Shop Menu
  bool displayInnMenu;        // Switch to display Inn Menu
  bool displayFerryMenu;        // Switch to display Ferry Menu
  bool displayDeathMsg;        // Switch to display Death Message

  TCODImage *bg_img;        // Background image for main menu

  TCODConsole *con;        // Menu Screen
  TCODConsole *subcon;        // Submenu Screen
  TCODConsole *msgcon;        // Message Screen

  char messageLog[NMSGS][CHARMAX];    // Message Log

  Menu();            // The Menu Constructor

  void updateMainMenu(TCOD_key_t key);      // Updates the main menu
  void renderMainMenu();        // Renders the main menu

  void updateInfoPage(TCOD_key_t key);      // Updates the info page
  void renderInfoPage();        // Renders the info page

  bool updateIntroPage(TCOD_key_t key);     // Updates the introduction page
  void renderIntroPage();       // Renders the introduction page

  bool updateGameMenu(TCOD_key_t key);      // Updates the game menu
  void renderGameMenu();        // Renders the game menu

  void updateEquipMenu(int subMenuCursor, int subSubMenuCursor);  // Updates the game equip submenu
  void updateItemMenu(int subMenuCursor);    // Updates the game item submenu

  bool updateItemShopMenu(TCOD_key_t key);    // Updates the item shop menu
  void renderItemShopMenu();        // Renders the item shop menu

  void updateItemShopBuyMenu(int subMenuCursor);  // Updates the item shop buy submenu
  void updateItemShopSellMenu(int subMenuCursor);  // Updates the item shop sell submenu

  bool updateEquipShopMenu(TCOD_key_t key);    // Updates the equip shop menu
  void renderEquipShopMenu();        // Renders the equip shop menu

  void updateEquipShopBuyMenu(int subMenuCursor);  // Updates the equip shop buy submenu
  void updateEquipShopSellMenu(int subMenuCursor);// Updates the equip shop sell submenu

  bool updateInnMenu(TCOD_key_t key);      // Updates the inn menu
  void renderInnMenu();          // Renders the inn menu

  bool updateFerryMenu(TCOD_key_t key);      // Updates the ferry menu
  void renderFerryMenu();        // Renders the ferry menu

  bool updateDeathMsg(TCOD_key_t key);      // Updates the death message
  void renderDeathMsg();        // Renders the death message

  void updateMessageLog(char msg[]);    // Updates the message log
  void renderMessageLog();      // Renders the message log
};
