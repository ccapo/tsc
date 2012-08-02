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

const TCODColor darkWall = TCODColor::darkestGrey;
const TCODColor lightWall = TCODColor(130,110,50);
const TCODColor darkGround = TCODColor::darkerGrey;
const TCODColor lightGround = TCODColor(200,180,50);

// The (actual) game object
Game game;

// The game constructor
Game::Game(): inCaves(false), isFaded(false), worldID(0), caveID(0), magicID(0), mouse_x(0), mouse_y(0), elapsedTime(0.0f)
{
  // Random seed and noise generators
  seed = static_cast<uint32>(time(NULL));
  rng = TCODRandom::getInstance();
  torch = new TCODNoise(1, rng);
  terrain = new TCODNoise(2, rng);
  weather = new TCODNoise(3, rng);

  player.x = IMAGE_WIDTH/2; player.y = IMAGE_HEIGHT/2 + 1;

//  guardian = NULL;
//  boss = NULL;
}

Game::~Game()
{
  if(rng) delete rng;
  rng = NULL;

  if(torch) delete torch;
  torch = NULL;

  if(terrain) delete terrain;
  terrain = NULL;

  if(weather) delete weather;
  weather = NULL;

//  if(guardian) delete guardian;
//  guardian = NULL;

//  if(boss) delete boss;
//  boss = NULL;
}

// This method initializes the game
void Game::startup(int narg, char *argv[])
{
  const char fonts[NFONTS][CHARMAX] = {"data/fonts/arial4x4.png",
                                       "data/fonts/arial6x6.png",
                                       "data/fonts/arial8x8.png"};
  int fontFlags = TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE;
  int iFont = 2, nCol = 32, nRow = 8, maxFps = 25;
  int initialDelay = 100, interval = 10;
  bool fullscreen = false;
  TCOD_renderer_t renderer = TCOD_RENDERER_SDL;

  // Set font
  TCODConsole::setCustomFont(fonts[iFont], fontFlags, nCol, nRow);

  // Initialize root console
  TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "The Serpentine Caves v"VERSION, fullscreen, renderer);

  // Set keyboard repeat delay
  TCODConsole::setKeyboardRepeat(initialDelay, interval);

  // Show cursor
  TCODMouse::showCursor(true);

  // Limit the framerate to maxFps FPS
  TCODSystem::setFps(maxFps);

  // Assign extra ascii keys
  TCODConsole::mapAsciiCodeToFont(TCOD_CHAR_CHARGEBAR, 0, 5);
  //TCODConsole::mapAsciiCodeToFont(TCOD_CHAR_CHARGEBAR, 26, 3);

  // Read seed value from the command line, if present
  if(narg == 2)
  {
    seed = static_cast<uint32>(atoi(argv[1]));
    rng = new TCODRandom(seed, TCOD_RNG_CMWC);
    torch = new TCODNoise(1, rng);
    terrain = new TCODNoise(2, rng);
    weather = new TCODNoise(3, rng);
  }

  // Startup FMODEX, and load all the music files
  sound.startup();

  // Libtcod credits
  TCODConsole::credits();

  // Clear root console
  TCODConsole::root->clear();

  // Play the music for the main menu
  sound.play(SOUND_MAIN_MENU);

  // Update the sound system
  sound.endFrame();
  sound.update();

  // Set cross fade flag
  sound.crossFading = true;
}

// This method shutdowns the game
void Game::shutdown(void)
{
  // Fade out
  for(int fade = 255; fade >= 0; fade -= 5)
  {
    TCODConsole::setFade(fade,TCODColor::black);
    sound.setVolume(sound.activeChannel, static_cast<float>(fade)/static_cast<float>(510));
    TCODConsole::flush();
  }

  // Shutdown FMODEX
  sound.shutdown();
}

// This method updates the title screen
bool Game::updateTitle(float elapsed, TCOD_key_t key)
{
  bool status = false;

  // Handle keyboard input
  if(key.vk == TCODK_BACKSPACE)
  {
    // Save a screenshot
    TCODSystem::saveScreenshot(NULL);
  }
  else if(key.vk == TCODK_PAUSE)
  {
    // Toggle the pause
    sound.togglePause();
  }
  else if(key.lalt && key.vk == TCODK_ENTER)
  {
    // Toggle fullscreen
    TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
    key.vk = TCODK_NONE;
  }

  // Crossfade between the two channels
  if(sound.crossFading) sound.crossFade(elapsed);

  // Select appropriate action
  switch(menu.selection)
  {
    // Start new game
    case MAIN_NEW:
    {
      status = newGame();
      break;
    }

    // Load previous game
    case MAIN_LOAD:
    {
      status = loadGame();
      break;
    }

    // Display Info Page
    case MAIN_HELP:
    {
      menu.displayInfoPage = true;
      break;
    }

    // Quit game
    case MAIN_QUIT:
    {
      // Shutdown
      shutdown();

      // Quit
      exit(0);
      break;
    }
    default: break;
  }

  // If the info menu flag is set
  if(menu.displayInfoPage)
  {
    // Update the info page
    menu.updateInfoPage(key);
  }
  else
  {
    // Update the main menu
    menu.updateMainMenu(key);
  }

  return status;
}

// This method renders the title screen
void Game::renderTitle()
{
  // Render the main menu
  menu.renderMainMenu();

  // Render the info page
  if(menu.displayInfoPage) menu.renderInfoPage();
}

// This method updates the introduction screen
bool Game::updateIntro(float elapsed, TCOD_key_t key)
{
  bool status = true;

  WorldMap *wmap = &world[worldID];

  // Handle keyboard input
  if(key.vk == TCODK_BACKSPACE)
  {
    // Save a screenshot
    TCODSystem::saveScreenshot(NULL);
  }
  else if(key.vk == TCODK_PAUSE)
  {
    // Toggle the pause
    sound.togglePause();
  }
  else if(key.lalt && key.vk == TCODK_ENTER)
  {
    // Toggle fullscreen
    TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
    key.vk = TCODK_NONE;
  }

  // Load new music
  if(sound.first)
  {
    // Play the music for the current map
    sound.play(wmap->musicID);

    // Update the sound system
    sound.endFrame();
    sound.update();

    sound.first = false;
    sound.crossFading = true;
  }

  // Crossfade between the two channels
  if(sound.crossFading) sound.crossFade(elapsed);

  // Update the introduction page
  status = menu.updateIntroPage(key);

  return status;
}

// This method renders the introduction screen
void Game::renderIntro()
{
  static int first = true;
  int x = 3*DISPLAY_WIDTH/4 - 2, y = DISPLAY_HEIGHT + 3;
  int w = DISPLAY_WIDTH/4 + 2, h = NMSGS + 4;

  WorldMap *wmap = &world[worldID];

  // Render the map
  wmap->render(player);

  // Render the player
  player.render();

  // Render level number
  TCODConsole::root->setDefaultBackground(TCODColor::black);
  TCODConsole::root->setDefaultForeground(TCODColor::white);
  TCODConsole::root->printFrame(x, y, w, h, false, TCOD_BKGND_SET, wmap->label);

  // Render the introduction screen
  menu.renderIntroPage();

  // Various UI stuff

  // Render message log
  menu.renderMessageLog();

  // Render player hp bar
  TCODConsole::root->setDefaultForeground(TCODColor::white);
  TCODConsole::root->printEx(1, 1, TCOD_BKGND_NONE, TCOD_LEFT, "HP");
  float hpfraction = static_cast<float>(player.stats.hp)/static_cast<float>(player.stats.hpmax);
  int hpbar = static_cast<int>(20.0f*hpfraction);
  if(hpbar > 0)
  {
    TCODConsole::root->setDefaultBackground(TCODColor::red);
    TCODConsole::root->rect(4, 1, hpbar, 1, true, TCOD_BKGND_SET);
  }
  if(hpbar < 20)
  {
    TCODConsole::root->setDefaultBackground(TCODColor::darkerRed);
    TCODConsole::root->rect(4 + hpbar, 1, 20 - hpbar, 1, true, TCOD_BKGND_SET);
  }

  // Render player mp bar
  TCODConsole::root->setDefaultForeground(TCODColor::white);
  TCODConsole::root->printEx(DISPLAY_WIDTH - 24, 1, TCOD_BKGND_NONE, TCOD_LEFT, "MP");
  float mpfraction = static_cast<float>(player.stats.mp)/static_cast<float>(player.stats.mpmax);
  int mpbar = static_cast<int>(20.0f*mpfraction);
  if(mpbar > 0)
  {
    TCODConsole::root->setDefaultBackground(TCODColor::blue);
    TCODConsole::root->rect(DISPLAY_WIDTH - 21, 1, mpbar, 1, true, TCOD_BKGND_SET);
  }
  if(mpbar < 20)
  {
    TCODConsole::root->setDefaultBackground(TCODColor::darkerBlue);
    TCODConsole::root->rect(DISPLAY_WIDTH - 21 + mpbar, 1, 20 - mpbar, 1, true, TCOD_BKGND_SET);
  }

  // Fade in
  if(first)
  {
    for(int fade = 0; fade <= 255; fade += 25)
    {
      TCODConsole::setFade(fade, TCODColor::black);
      TCODConsole::flush();
    }
    first = false;
  }
}

// This method initializes all the game data
bool Game::newGame()
{
  bool status = true;

  // Initialize all maps
  float fraction = 0.0f;
  displayProgress("Generating Serpentine Caves", fraction);
  for(worldID = 0; worldID < NWORLD; worldID++)
  {
    if(worldID >= 1 && worldID < NTEMPLES + 1)
    {
      world[worldID].loadMap("data/img/templemap.png", "Temple Map", SOUND_TOWN_MAP);
    }
    else if(worldID >= NTEMPLES + 1 && worldID < NTEMPLES + NTOWNS + 1)
    {
      world[worldID].loadMap("data/img/townmap.png", "Town Map", SOUND_TOWN_MAP);
    }
    else
    {
      world[worldID].loadMap("data/img/worldmap.png", "World Map", SOUND_WORLD_MAP);

      // Generate random town names
      for(int i = 5; i < world[worldID].nlocations - 1; i++)
      {
        sprintf(world[worldID].locations[i].name, "%s", NameGenerator::generateCityName(rng));
      }

      // Setup their economy
      setupEconomy();
    }
    fraction = static_cast<float>(worldID)/static_cast<float>(NWORLD + NCAVES - 2);
    displayProgress("Generating Serpentine Caves", fraction);
  }

  for(caveID = 0; caveID < NCAVES; caveID++)
  {
    caves[caveID].finalizeMap(caveID);
    fraction = static_cast<float>(caveID + NWORLD - 1)/static_cast<float>(NWORLD + NCAVES - 2);
    displayProgress("Generating Serpentine Caves", fraction);
  }
  TCODConsole::root->setDefaultBackground(TCODColor::black);

  // Select world map
  worldID = TEMPLE_LIGHT + 1;
  caveID = 0;
  inCaves = false;

  // Update player status
  player.updateStatus();

  sound.first = true;

  // Fade out
  for(int fade = 255; fade >= 0; fade -= 25)
  {
    TCODConsole::setFade(fade, TCODColor::black);
    TCODConsole::flush();
  }

  return status;
}

// This method saves the data to the save file
bool Game::saveGame(bool init)
{
  bool status = true;
  int nb = 0;

  // Define zip object
  zip = new TCODZip();

  float fraction = 0.0f;
  if(init) displayProgress("Saving Serpentine Caves", fraction);

  // Store save file magic number
  zip->putInt(SAVEGAME_MAGIC_NUMBER);

  // Store random seed
  zip->putInt(seed);

  // Store world data
  for(int i = 0; i < NWORLD; i++)
  {
    nb = sizeof(world[i]);
    zip->putInt(nb);
    zip->putData(nb, &world[i]);
    fraction = static_cast<float>(i)/static_cast<float>(NWORLD + NCAVES);
    if(init) displayProgress("Saving Serpentine Caves", fraction);
  }

  // Store cave data
  for(int i = 0; i < NCAVES; i++)
  {
    nb = sizeof(caves[i]);
    zip->putInt(nb);
    zip->putData(nb, &caves[i]);
    fraction = static_cast<float>(i + NWORLD - 1)/static_cast<float>(NWORLD + NCAVES);
    if(init) displayProgress("Saving Serpentine Caves", fraction);
  }

  // Store menu data
  nb = sizeof(menu);
  zip->putInt(nb);
  zip->putData(nb, &menu);
  fraction = static_cast<float>(NWORLD + NCAVES - 1)/static_cast<float>(NWORLD + NCAVES);
  if(init) displayProgress("Saving Serpentine Caves", fraction);

  // Store player data
  nb = sizeof(player);
  zip->putInt(nb);
  zip->putData(nb, &player);
  fraction = static_cast<float>(NWORLD + NCAVES)/static_cast<float>(NWORLD + NCAVES);
  if(init) displayProgress("Saving Serpentine Caves", fraction);

  // Write to save file
  zip->saveToFile(SAVEGAME_FILENAME);

  // Free zip object
  if(zip) delete zip;
  zip = NULL;

  return status;
}

// This method loads the data from the save file
bool Game::loadGame()
{
  bool status = true;
  int nb = 0;

  // Define zip object
  zip = new TCODZip();

  // Test if save file exists
  if(zip->loadFromFile(SAVEGAME_FILENAME) == 0)
  {
    if(zip) delete zip;
    zip = NULL;
    printf("loadGame Error:: Save file does not exist, starting a new game.\n");
    status = newGame(); // Start a new game
    menu.selection = MAIN_NEW;
    return status;
  }

  // Load and compare save file magic number
  uint32 magic = zip->getInt();
  if(magic != SAVEGAME_MAGIC_NUMBER)
  {
    if(zip) delete zip;
    zip = NULL;
    printf("loadGame Error:: magic number does not match!\n");
    status = false;
    return status;
  }

  // Load value of random seed
  seed = zip->getInt();

  // Set the random number generator with the seed value
  rng = new TCODRandom(seed, TCOD_RNG_CMWC);

  // Initialize the all noise generators
  torch = new TCODNoise(1, rng);
  terrain = new TCODNoise(2, rng);
  weather = new TCODNoise(3, rng);

  // Load world data
  float fraction = 0.0f;
  displayProgress("Loading Serpentine Caves", fraction);
  for(worldID = 0; worldID < NWORLD; worldID++)
  {
    nb = zip->getInt();
    zip->getData(nb, &world[worldID]);

    // FOV Maps
    world[worldID].fov1x = new TCODMap(IMAGE_WIDTH, IMAGE_HEIGHT);
    world[worldID].fov2x = new TCODMap(IMAGE_WIDTH2, IMAGE_HEIGHT2);

    // Image and thumbnail
    world[worldID].img = new TCODImage(IMAGE_WIDTH2, IMAGE_HEIGHT2);
    world[worldID].img_thumb = new TCODImage(IMAGE_WIDTH2/4, IMAGE_HEIGHT2/4);

    if(worldID >= 1 && worldID < NTEMPLES + 1)
    {
      world[worldID].loadMap("data/img/templemap.png", "Temple Map", SOUND_TOWN_MAP, false);
      for(int i = 0; i < world[worldID].nnpcs; i++) world[worldID].npcs[i].path = NULL;
    }
    else if(worldID >= NTEMPLES + 1 && worldID < NTEMPLES + NTOWNS + 1)
    {
      world[worldID].loadMap("data/img/townmap.png", "Town Map", SOUND_TOWN_MAP, false);
      for(int i = 0; i < world[worldID].nnpcs; i++) world[worldID].npcs[i].path = NULL;
    }
    else
    {
      world[worldID].loadMap("data/img/worldmap.png", "World Map", SOUND_WORLD_MAP, false);
      for(int i = 0; i < world[worldID].nnpcs; i++) world[worldID].npcs[i].path = NULL;
    }
    fraction = static_cast<float>(worldID)/static_cast<float>(NWORLD + NCAVES);
    displayProgress("Loading Serpentine Caves", fraction);
  }

  // Load cave data
  for(caveID = 0; caveID < NCAVES; caveID++)
  {
    nb = zip->getInt();
    zip->getData(nb, &caves[caveID]);

    // FOV Maps
    caves[caveID].fov1x = new TCODMap(MAP_WIDTH, MAP_HEIGHT);
    caves[caveID].fov2x = new TCODMap(MAP_WIDTH2, MAP_HEIGHT2);

    // Image and thumbnail
    caves[caveID].img = new TCODImage(MAP_WIDTH2, MAP_HEIGHT2);
    caves[caveID].img_thumb = new TCODImage(MAP_WIDTH2/SCALE_FACTOR, MAP_HEIGHT2/SCALE_FACTOR);
    caves[caveID].img_thumb->clear(darkWall);

    caves[caveID].loadMap();
    //for(int i = 0; i < caves[caveID].ncreatures; i++) caves[caveID].creatures[i].path = NULL;

    fraction = static_cast<float>(caveID + NWORLD - 1)/static_cast<float>(NWORLD + NCAVES);
    displayProgress("Loading Serpentine Caves", fraction);
  }
  TCODConsole::root->setDefaultBackground(TCODColor::black);

  // Select world map
  worldID = 0;
  caveID = 0;
  inCaves = false;

  // Load menu data
  nb = zip->getInt();
  zip->getData(nb, &menu);

  menu.selection = NONE;
  menu.displayInfoPage = false;
  menu.displayGameMenu = false;
  menu.displayItemShopMenu = false;
  menu.displayEquipShopMenu = false;
  menu.displayInnMenu = false;
  menu.displayFerryMenu = false;
  menu.displayDeathMsg = false;
  menu.bg_img = new TCODImage("data/img/menu_bg.png");
  menu.con = NULL;
  menu.subcon = NULL;
  menu.msgcon = new TCODConsole(3*DISPLAY_WIDTH/4 - 2, NMSGS + 4);
  menu.msgcon->printFrame(0, 0, 3*DISPLAY_WIDTH/4 - 2, NMSGS + 4, false, TCOD_BKGND_SET, "Message Log");
  for(int i = 0; i < NMSGS; i++) menu.msgcon->print(2, NMSGS + 1 - i, menu.messageLog[i]);

  fraction = static_cast<float>(NWORLD + NCAVES - 1)/static_cast<float>(NWORLD + NCAVES);
  displayProgress("Loading Serpentine Caves", fraction);

  // Load player data
  nb = zip->getInt();
  zip->getData(nb, &player);
  player.path = NULL;

  // Update player stats
  player.updateStats();

  fraction = static_cast<float>(NWORLD + NCAVES)/static_cast<float>(NWORLD + NCAVES);
  displayProgress("Loading Serpentine Caves", fraction);

  // Free zip object
  if(zip) delete zip;
  zip = NULL;

  sound.first = true;

  // Fade out
  for(int fade = 255; fade >= 0; fade -= 25)
  {
    TCODConsole::setFade(fade, TCODColor::black);
    TCODConsole::flush();
  }

  return status;
}

void Game::handleInput(TCOD_key_t *key, TCOD_mouse_t mouse)
{
  // Store current mouse position in the console
  mouse_x = mouse.cx;
  mouse_y = mouse.cy - 3;

  // Keyboard input
  if(key->vk == TCODK_ESCAPE)
  {
    bool otherMenus = (menu.displayItemShopMenu || menu.displayEquipShopMenu || menu.displayInnMenu || menu.displayFerryMenu);
    if(menu.selection == NONE && !otherMenus)
    {
      // Toggle the volume for the game menu
      sound.toggleVolume(0.5f);

      // Toggle the game menu flag
      menu.displayGameMenu = !menu.displayGameMenu;
    }
  }
  else if(key->vk == TCODK_SHIFT)
  {
    // Rotate magic selection
    magicID = (magicID + 1) % MAX(1, NMAGIC);
  }
  else if(key->vk == TCODK_PAUSE)
  {
    // Toggle the pause
    sound.togglePause();
  }
  else if(key->vk == TCODK_BACKSPACE)
  {
    // Screenshot
    TCODSystem::saveScreenshot(NULL);
    //caves[caveID].saveMap();
  }
  else if(key->lalt && key->vk == TCODK_ENTER)
  {
    // Toggle fullscreen
    TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
    key->vk = TCODK_NONE;
  }
}

void Game::setupEconomy()
{
  // Economic Data for Items
  const int maxItemCountLow[2] = {40, 50};
  const int minItemPriceLow[2] = {1, 10};
  const int maxItemPriceLow[2] = {15, 25};
  const int itemProductionRateLow[2] = {4, 5};

  const int maxItemCountMed[2] = {25, 35};
  const int minItemPriceMed[2] = {5, 15};
  const int maxItemPriceMed[2] = {25, 50};
  const int itemProductionRateMed[2] = {3, 4};

  const int maxItemCountHigh[2] = {5, 15};
  const int minItemPriceHigh[2] = {10, 20};
  const int maxItemPriceHigh[2] = {40, 60};
  const int itemProductionRateHigh[2] = {2, 3};

  int maxItemCount[NREGIONS][2];
  int minItemPrice[NREGIONS][2];
  int maxItemPrice[NREGIONS][2];
  int itemProductionRate[NREGIONS][2];

  // Economic Data for Hides
  const int minHidePrice[2] = {1, 3};
  const int maxHidePrice[2] = {5, 4};

  int iLow = 0, iHigh = 2;
  WorldMap *wmap = &world[0];

  for(int i = TOWN_01; i <= TOWN_07; i++)
  {
    // Region 1
    if(wmap->locations[i].x >= IMAGE_WIDTH/2 && wmap->locations[i].y >= IMAGE_HEIGHT/2)
    {
      iLow = 0;
      iHigh = 2;
    }

    // Region 2
    if(wmap->locations[i].x < IMAGE_WIDTH/2 && wmap->locations[i].y >= IMAGE_HEIGHT/2)
    {
      iLow = 1;
      iHigh = 3;
    }

    // Region 3
    if(wmap->locations[i].x < IMAGE_WIDTH/2 && wmap->locations[i].y < IMAGE_HEIGHT/2)
    {
      iLow = 2;
      iHigh = 0;
    }

    // Region 4
    if(wmap->locations[i].x >= IMAGE_WIDTH/2 && wmap->locations[i].y < IMAGE_HEIGHT/2)
    {
      iLow = 3;
      iHigh = 1;
    }

    for(int l = 0; l < NREGIONS; l++)
    {
      if(l == iLow)
      {
        // Items
        for(int m = 0; m < 2; m++) maxItemCount[l][m] = maxItemCountLow[m];
        for(int m = 0; m < 2; m++) minItemPrice[l][m] = minItemPriceLow[m];
        for(int m = 0; m < 2; m++) maxItemPrice[l][m] = maxItemPriceLow[m];
        for(int m = 0; m < 2; m++) itemProductionRate[l][m] = itemProductionRateLow[m];
      }
      else if(l == iHigh)
      {
        // Items
        for(int m = 0; m < 2; m++) maxItemCount[l][m] = maxItemCountHigh[m];
        for(int m = 0; m < 2; m++) minItemPrice[l][m] = minItemPriceHigh[m];
        for(int m = 0; m < 2; m++) maxItemPrice[l][m] = maxItemPriceHigh[m];
        for(int m = 0; m < 2; m++) itemProductionRate[l][m] = itemProductionRateHigh[m];
      }
      else
      {
        // Items
        for(int m = 0; m < 2; m++) maxItemCount[l][m] = maxItemCountMed[m];
        for(int m = 0; m < 2; m++) minItemPrice[l][m] = minItemPriceMed[m];
        for(int m = 0; m < 2; m++) maxItemPrice[l][m] = maxItemPriceMed[m];
        for(int m = 0; m < 2; m++) itemProductionRate[l][m] = itemProductionRateMed[m];
      }

      for(int k = 0; k < NITEMS_REGION; k++)
      {
        int j = l*NITEMS_REGION + k;

        wmap->locations[i].itemInv.maxCount[j] = game.rng->getInt(maxItemCount[l][0], maxItemCount[l][1]);
        wmap->locations[i].itemInv.count[j] = game.rng->getInt(1, wmap->locations[i].itemInv.maxCount[j]);

        wmap->locations[i].itemInv.minPrice[j] = game.rng->getInt(minItemPrice[l][0], minItemPrice[l][1]);
        wmap->locations[i].itemInv.maxPrice[j] = game.rng->getInt(maxItemPrice[l][0], maxItemPrice[l][1]);
        wmap->locations[i].itemInv.price[j] = game.rng->getInt(wmap->locations[i].itemInv.minPrice[j], wmap->locations[i].itemInv.maxPrice[j]);

        wmap->locations[i].itemInv.productionRate[j] = game.rng->getInt(itemProductionRate[l][0], itemProductionRate[l][1]);
      }

      int j = POTION_ELIXIR;
      wmap->locations[i].itemInv.maxCount[j] = 5;
      wmap->locations[i].itemInv.count[j] = 2;

      wmap->locations[i].itemInv.minPrice[j] = 125;
      wmap->locations[i].itemInv.maxPrice[j] = 500;
      wmap->locations[i].itemInv.price[j] = 250;

      wmap->locations[i].itemInv.productionRate[j] = 2;

      for(int j = NITEMS - 6; j < NITEMS; j++)
      {
        wmap->locations[i].itemInv.maxCount[j] = 99;
        wmap->locations[i].itemInv.count[j] = 0;

        wmap->locations[i].itemInv.minPrice[j] = 0;
        wmap->locations[i].itemInv.maxPrice[j] = 2;
        wmap->locations[i].itemInv.price[j] = 2;

        wmap->locations[i].itemInv.productionRate[j] = 0;
      }
    }

    for(int j = 0; j < NCREATURETYPES; j++)
    {
      wmap->locations[i].hideInv.maxCount[j] = 99;
      wmap->locations[i].hideInv.count[j] = game.rng->getInt(1, wmap->locations[i].hideInv.maxCount[j]);

      wmap->locations[i].hideInv.minPrice[j] = minHidePrice[0] + minHidePrice[1]*pow(j, 2);
      wmap->locations[i].hideInv.maxPrice[j] = maxHidePrice[0] + maxHidePrice[1]*pow(j, 2);

      wmap->locations[i].hideInv.price[j] = game.rng->getInt(wmap->locations[i].hideInv.minPrice[j], wmap->locations[i].hideInv.maxPrice[j]);
    }

    int n = 0;
    for(int j = 0; j < NITEMS; j++)
    {
      if(wmap->locations[i].itemInv.count[j] != 0)
      {
        wmap->locations[i].itemInv.index[n] = j;
        n++;
      }
    }
    wmap->locations[i].itemInv.nitems = n;

    n = 0;
    for(int j = 0; j < NCREATURETYPES; j++)
    {
      if(wmap->locations[i].hideInv.count[j] != 0)
      {
        wmap->locations[i].hideInv.index[n] = j;
        n++;
      }
    }
    wmap->locations[i].hideInv.nhides = n;
  }
}

void Game::updateEconomy()
{
  // Items
  int totalItemCount[NITEMS];
  int totalItemMaxCount[NITEMS];

  // Hides
  int totalHideCount[NCREATURETYPES];
  int totalHideMaxCount[NCREATURETYPES];

  WorldMap *wmap = &world[0];

  // Tally the total number of items
  for(int j = 0; j < NITEMS - 6; j++)
  {
    totalItemCount[j] = 0;
    totalItemMaxCount[j] = 0;
    for(int i = TOWN_01; i <= TOWN_07; i++)
    {
      totalItemCount[j] += wmap->locations[i].itemInv.count[j];
      totalItemMaxCount[j] += wmap->locations[i].itemInv.maxCount[j];
    }
  }

  // Tally the total number of hides
  for(int j = 0; j < NCREATURETYPES; j++)
  {
    totalHideCount[j] = 0;
    totalHideMaxCount[j] = 0;
    for(int i = TOWN_01; i <= TOWN_07; i++)
    {
      totalHideCount[j] += wmap->locations[i].hideInv.count[j];
      totalHideMaxCount[j] += wmap->locations[i].hideInv.maxCount[j];
    }
  }

  for(int i = TOWN_01; i <= TOWN_07; i++)
  {
    // Update item prices
    for(int j = 0; j < NITEMS - 6; j++)
    {
      int a = (wmap->locations[i].itemInv.maxPrice[j] - wmap->locations[i].itemInv.minPrice[j])/2;
      float b = 4.0f*(1.0f - 2.0f*static_cast<float>(totalItemCount[j])/static_cast<float>(totalItemMaxCount[j]));
      wmap->locations[i].itemInv.price[j] = a*(tanh(b) + 1) + wmap->locations[i].itemInv.minPrice[j];
      wmap->locations[i].itemInv.price[j] = CLAMP(wmap->locations[i].itemInv.minPrice[j], wmap->locations[i].itemInv.maxPrice[j], wmap->locations[i].itemInv.price[j]);
    }

    // Update the number of each item
    for(int j = 0; j < NITEMS - 6; j++)
    {
      // Sales for each item, from each town
      int sales = game.rng->getInt(1, 5);
      if(wmap->locations[i].itemInv.count[j] <= 0) sales = 0;

      // Update item count
      wmap->locations[i].itemInv.count[j] += wmap->locations[i].itemInv.productionRate[j] - sales;
      wmap->locations[i].itemInv.count[j] = CLAMP(0, wmap->locations[i].itemInv.maxCount[j], wmap->locations[i].itemInv.count[j]);
    }

    // Remove all bad items from town inventories
    for(int j = NITEMS - 6; j < NITEMS; j++) wmap->locations[i].itemInv.count[j] = 0;

    // Update number of active items
    int n = 0;
    for(int j = 0; j < NITEMS - 6; j++)
    {
      if(wmap->locations[i].itemInv.count[j] > 0)
      {
        wmap->locations[i].itemInv.index[n] = j;
        n++;
      }
    }
    wmap->locations[i].itemInv.nitems = CLAMP(0, NITEMS - 1, n);

    // Update hide prices
    for(int j = 0; j < NCREATURETYPES; j++)
    {
      int a = (wmap->locations[i].hideInv.maxPrice[j] - wmap->locations[i].hideInv.minPrice[j])/2;
      float b = 4.0f*(1.0f - 2.0f*static_cast<float>(totalHideCount[j])/static_cast<float>(totalHideMaxCount[j]));
      wmap->locations[i].hideInv.price[j] = a*(tanh(b) + 1) + wmap->locations[i].hideInv.minPrice[j];
      wmap->locations[i].hideInv.price[j] = CLAMP(wmap->locations[i].hideInv.minPrice[j], wmap->locations[i].hideInv.maxPrice[j], wmap->locations[i].hideInv.price[j]);
    }

    // Update the number of each hide
    for(int j = 0; j < NCREATURETYPES; j++)
    {
      // Sales for each hide, from each town
      int sales = game.rng->getInt(1, 2);
      if(wmap->locations[i].hideInv.count[j] <= 0) sales = 0;

      int production = game.rng->getInt(1, 3);

      // Update item count
      wmap->locations[i].hideInv.count[j] += production - sales;
      wmap->locations[i].hideInv.count[j] = CLAMP(0, wmap->locations[i].hideInv.maxCount[j], wmap->locations[i].hideInv.count[j]);
    }

    // Update number of active hides
    n = 0;
    for(int j = 0; j < NCREATURETYPES; j++)
    {
      if(wmap->locations[i].hideInv.count[j] > 0)
      {
        wmap->locations[i].hideInv.index[n] = j;
        n++;
      }
    }
    wmap->locations[i].hideInv.nhides = CLAMP(0, NCREATURETYPES - 1, n);
  }
}

bool Game::update(float elapsed, TCOD_key_t key, TCOD_mouse_t mouse)
{
  bool status = false;
  static int nUpdateEconomy = 0;
  //static AiDirector aiDirector;

  // Increment the elapsed time
  elapsedTime += elapsed;

  // Handle keyboard and mouse input
  handleInput(&key, mouse);

  if(inCaves)
  {
    CaveMap *cmap = &caves[caveID];

    // Load new music
    if(sound.first)
    {
      // Play the music for the current map
      sound.play(cmap->musicID);

      // Update the sound system
      sound.endFrame();
      sound.update();

      sound.first = false;
      sound.crossFading = true;
    }

    // Crossfade between the two sound channels
    if(sound.crossFading) sound.crossFade(elapsed);

    // If the game menu flag is set
    if(menu.displayGameMenu)
    {
      // Update the game menu
      status = menu.updateGameMenu(key);
    }
    else if(menu.displayDeathMsg)
    {
      // Update the death message
      status = menu.updateDeathMsg(key);
    }
    else
    {
      // Update player
      player.update(elapsed, &key, mouse);

      // Move the display
      cmap->moveDisplay(player.x, player.y);

      // Update the player's scent
      cmap->updateScent(player.x, player.y);

      // Update creatures
      //aiDirector.update(elapsed);
      cmap->updateCreatures(player, elapsed);

      // Update magic
      //TCODList <Magic *> magicToRemove;
      //for(Magic **it = magic.begin(); it != magic.end(); it++)
      //{
      //  if(!(*it)->update(elapsed))
      //  {
      //    magicToRemove.push(*it);
      //    it = magic.removeFast(it);
      //  }
      //}
      //magicToRemove.clearAndDelete();
    }
  }
  else
  {
    WorldMap *wmap = &world[worldID];

    // Load new music
    if(sound.first)
    {
      // Play the music for the current map
      sound.play(wmap->musicID);

      // Update the sound system
      sound.endFrame();
      sound.update();

      sound.first = false;
      sound.crossFading = true;
    }

    // Crossfade between the two sound channels
    if(sound.crossFading) sound.crossFade(elapsed);

    // Update the economy when on the world map
    if(worldID == 0)
    {
      if(nUpdateEconomy >= TCODSystem::getFps())
      {
        updateEconomy();
        nUpdateEconomy = 0;
      }
      else
      {
        nUpdateEconomy++;
      }
    }

    bool openMenus = (menu.displayGameMenu || menu.displayItemShopMenu || menu.displayEquipShopMenu || menu.displayInnMenu || menu.displayFerryMenu || menu.displayDeathMsg);
    if(!openMenus)
    {
      // Update Player
      player.update(elapsed, &key, mouse);
    }

    // Update Npcs
    wmap->updateNpcs(player, elapsed);

    // If the game menu flag is set
    if(menu.displayGameMenu)
    {
      // Update the game menu
      status = menu.updateGameMenu(key);
    }
    else if(menu.displayItemShopMenu)
    {
      // Update the item shop menu
      status = menu.updateItemShopMenu(key);
    }
    else if(menu.displayEquipShopMenu)
    {
      // Update the equip shop menu
      status = menu.updateEquipShopMenu(key);
    }
    else if(menu.displayInnMenu)
    {
      // Update the inn menu
      status = menu.updateInnMenu(key);
    }
    else if(menu.displayFerryMenu)
    {
      // Update the ferry menu
      status = menu.updateFerryMenu(key);
    }
    else if(menu.displayDeathMsg)
    {
      // Update the death message
      status = menu.updateDeathMsg(key);
    }
  }
  return status;
}

void Game::render(bool *first)
{
  int x = 3*DISPLAY_WIDTH/4 - 2, y = DISPLAY_HEIGHT + 3;
  int w = DISPLAY_WIDTH/4 + 2, h = NMSGS + 4;

  TCODConsole::root->setDefaultBackground(TCODColor::black);
  TCODConsole::root->clear();

  if(inCaves)
  {
    CaveMap *cmap = &caves[caveID];
    Item *items = cmap->items;
    Creature *creatures = cmap->creatures;
    Corpse *corpses = cmap->corpses;
    Hide *hides = cmap->hides;
    Location *locations = cmap->locations;
  
    // Render the map
    cmap->render(player);

    // Render the player
    player.render();
    
    // Render level number
    TCODConsole::root->setDefaultBackground(TCODColor::black);
    TCODConsole::root->setDefaultForeground(TCODColor::white);
    TCODConsole::root->printFrame(x, y, w, h, false, TCOD_BKGND_SET, cmap->label);

    // Render items under the mouse cursor
    int map_x = mouse_x + cmap->display_x;
    int map_y = mouse_y + cmap->display_y;
    map_x = CLAMP(0, MAP_WIDTH - 1, map_x);
    map_y = CLAMP(0, MAP_HEIGHT - 1, map_y);
    int dx = map_x - player.x, dy = map_y - player.y, dr = sqrt(dx*dx + dy*dy);
    bool isVisible = dr < static_cast<int>(TORCH_RADIUS/2.0f) && cmap->getFov2x(map_x, map_y);
    bool isPlayer = map_x == player.x && map_y == player.y;
    bool explored = cmap->getFov2xExplored(map_x, map_y);
    if(IN_RECTANGLE(mouse_x, mouse_y, DISPLAY_WIDTH, DISPLAY_HEIGHT) && explored)
    {
      int m_x = mouse_x, m_y;
      TCOD_alignment_t align;
      if(map_x < player.x)
      {
        align = TCOD_LEFT;
      }
      else
      {
        align = TCOD_RIGHT;
      }
      if(map_y < player.y)
      {
        m_y = mouse_y + 6;
      }
      else
      {
        m_y = mouse_y;
      }

      int id = cmap->getItemID(map_x, map_y);
      if(id >= 0 && !isPlayer && isVisible)
      {
        TCODConsole::root->setDefaultForeground(items[id].colour);
        TCODConsole::root->printEx(m_x, m_y, TCOD_BKGND_NONE, align, items[id].label);
      }

      id = cmap->getCreatureID(map_x, map_y);
      if(id >= 0 && !isPlayer && isVisible)
      {
        TCODConsole::root->setDefaultForeground(creatures[id].colour);
        TCODConsole::root->printEx(m_x, m_y, TCOD_BKGND_NONE, align, "%s: %d/%d", creatures[id].name, creatures[id].stats.hp, creatures[id].stats.hpmax);
      }

      id = cmap->getHideID(map_x, map_y);
      if(id >= 0 && !isPlayer && isVisible)
      {
        TCODConsole::root->setDefaultForeground(hides[id].colour);
        TCODConsole::root->printEx(m_x, m_y, TCOD_BKGND_NONE, align, hides[id].label);
      }

      id = cmap->getLocationID(map_x, map_y);
      if(id >= 0 && !isPlayer)
      {
        TCODConsole::root->setDefaultForeground(locations[id].colour);
        TCODConsole::root->printEx(m_x, m_y, TCOD_BKGND_NONE, align, locations[id].name);
      }
    }

    // Render boss hp bar
    //if(bossSeen && !bossIsDead)
    //{
    //  float hpfraction = static_cast<float>(boss->hp)/static_cast<float>(boss->stats.hpmax);
    //  int hpbar = static_cast<int>(40.0f*hpfraction);
    //  if(hpbar > 0)
    //  {
    //    TCODConsole::root->setDefaultBackground(TCODColor::lightGreen);
    //    TCODConsole::root->rect(DISPLAY_WIDTH/2 - 20, DISPLAY_HEIGHT, hpbar, 1, true, TCOD_BKGND_SET);
    //  }
    //  if(hpbar < 40)
    //  {
    //    TCODConsole::root->setDefaultBackground(TCODColor::darkerGreen);
    //    TCODConsole::root->rect(DISPLAY_WIDTH/2 - 20 + hpbar, DISPLAY_HEIGHT, 40 - hpbar, 1, true, TCOD_BKGND_SET);
    //  }
    //}
  }
  else
  {
    WorldMap *wmap = &world[worldID];
    Npc *npcs = wmap->npcs;
    Location *locations = wmap->locations;

    // Render the map
    wmap->render(player);

    // Render the player
    player.render();

    // Render level number
    TCODConsole::root->setDefaultBackground(TCODColor::black);
    TCODConsole::root->setDefaultForeground(TCODColor::white);
    TCODConsole::root->printFrame(x, y, w, h, false, TCOD_BKGND_SET, wmap->label);

    // Render items under the mouse cursor
    bool isPlayer = mouse_x == player.x && mouse_y == player.y;
    if(IN_RECTANGLE(mouse_x, mouse_y, DISPLAY_WIDTH, DISPLAY_HEIGHT))
    {
      int m_x = mouse_x, m_y;
      TCOD_alignment_t align;
      if(mouse_x < player.x)
      {
        align = TCOD_LEFT;
      }
      else
      {
        align = TCOD_RIGHT;
      }
      if(mouse_y < player.y)
      {
        m_y = mouse_y + 3 + 2;
      }
      else
      {
        m_y = mouse_y + 3 - 2;
      }

      int id = wmap->getNpcID(mouse_x, mouse_y);
      if(id >= 0 && !isPlayer)
      {
        //TCODConsole::root->setDefaultForeground(wmap->npcs[id].colour);
        TCODConsole::root->setDefaultForeground(TCODColor::white);
        TCODConsole::root->printEx(m_x, m_y, TCOD_BKGND_NONE, align, npcs[id].label);
      }

      id = wmap->getLocationID(mouse_x, mouse_y);
      if(id >= 0 && !isPlayer)
      {
        TCODConsole::root->setDefaultForeground(locations[id].colour);
        TCODConsole::root->printEx(m_x, m_y, TCOD_BKGND_NONE, align, locations[id].name);
      }
    }
  }

  // Various UI stuff
  if(menu.displayGameMenu)
  {
    // Display the game menu
    menu.renderGameMenu();
  }
  else if(menu.displayItemShopMenu)
  {
    // Display the item shop menu
    menu.renderItemShopMenu();
  }
  else if(menu.displayEquipShopMenu)
  {
    // Display the equip shop menu
    menu.renderEquipShopMenu();
  }
  else if(menu.displayInnMenu)
  {
    // Display the inn menu
    menu.renderInnMenu();
  }
  else if(menu.displayFerryMenu)
  {
    // Display the ferry menu
    menu.renderFerryMenu();
  }
  else if(menu.displayDeathMsg)
  {
    // Display the death message
    menu.renderDeathMsg();
  }

  // Render message log
  menu.renderMessageLog();

  // Render player hp bar
  TCODConsole::root->setDefaultForeground(TCODColor::white);
  TCODConsole::root->printEx(1, 1, TCOD_BKGND_NONE, TCOD_LEFT, "HP");
  float hpfraction = static_cast<float>(player.stats.hp)/static_cast<float>(player.stats.hpmax);
  int hpbar = static_cast<int>(20.0f*hpfraction);
  if(hpbar > 0)
  {
    TCODConsole::root->setDefaultBackground(TCODColor::red);
    TCODConsole::root->rect(4, 1, hpbar, 1, true, TCOD_BKGND_SET);
  }
  if(hpbar < 20)
  {
    TCODConsole::root->setDefaultBackground(TCODColor::darkerRed);
    TCODConsole::root->rect(4 + hpbar, 1, 20 - hpbar, 1, true, TCOD_BKGND_SET);
  }

  // Render player mp bar
  TCODConsole::root->setDefaultForeground(TCODColor::white);
  TCODConsole::root->printEx(DISPLAY_WIDTH - 24, 1, TCOD_BKGND_NONE, TCOD_LEFT, "MP");
  float mpfraction = static_cast<float>(player.stats.mp)/static_cast<float>(player.stats.mpmax);
  int mpbar = static_cast<int>(20.0f*mpfraction);
  if(mpbar > 0)
  {
    TCODConsole::root->setDefaultBackground(TCODColor::blue);
    TCODConsole::root->rect(DISPLAY_WIDTH - 21, 1, mpbar, 1, true, TCOD_BKGND_SET);
  }
  if(mpbar < 20)
  {
    TCODConsole::root->setDefaultBackground(TCODColor::darkerBlue);
    TCODConsole::root->rect(DISPLAY_WIDTH - 21 + mpbar, 1, 20 - mpbar, 1, true, TCOD_BKGND_SET);
  }

  // Render player magic selection
  switch(magicID)
  {
    case MAGIC_LIGHT:
    {
      TCODConsole::root->setDefaultForeground(TCODColor::white);
      TCODConsole::root->printEx(DISPLAY_WIDTH/2 - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Light Magic");
      magic_icon = new TCODImage("data/img/magic_light.png");
      magic_icon->blit2x(TCODConsole::root, DISPLAY_WIDTH/2 - 6, 0);
      break;
    }
    case MAGIC_FIRE:
    {
      TCODConsole::root->setDefaultForeground(TCODColor::white);
      TCODConsole::root->printEx(DISPLAY_WIDTH/2 - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Fire Magic");
      magic_icon = new TCODImage("data/img/magic_fire.png");
      magic_icon->blit2x(TCODConsole::root, DISPLAY_WIDTH/2 - 6, 0);
      break;
    }
    case MAGIC_WATER:
    {
      TCODConsole::root->setDefaultForeground(TCODColor::white);
      TCODConsole::root->printEx(DISPLAY_WIDTH/2 - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Water Magic");
      magic_icon = new TCODImage("data/img/magic_water.png");
      magic_icon->blit2x(TCODConsole::root, DISPLAY_WIDTH/2 - 6, 0);
      break;
    }
    case MAGIC_WIND:
    {
      TCODConsole::root->setDefaultForeground(TCODColor::white);
      TCODConsole::root->printEx(DISPLAY_WIDTH/2 - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Wind Magic");
      magic_icon = new TCODImage("data/img/magic_wind.png");
      magic_icon->blit2x(TCODConsole::root, DISPLAY_WIDTH/2 - 6, 0);
      break;
    }
    case MAGIC_EARTH:
    {
      TCODConsole::root->setDefaultForeground(TCODColor::white);
      TCODConsole::root->printEx(DISPLAY_WIDTH/2 - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Earth Magic");
      magic_icon = new TCODImage("data/img/magic_earth.png");
      magic_icon->blit2x(TCODConsole::root, DISPLAY_WIDTH/2 - 6, 0);
      break;
    }
    default: break;
  }

  // Print tool tips
  TCODConsole::root->setDefaultForeground(TCODColor(255,255,255));
  TCODConsole::root->setDefaultBackground(TCODColor(159,159,159));
  for(int i = 0; i < DISPLAY_WIDTH; i++) TCODConsole::root->putChar(i, 4, ' ' ,TCOD_BKGND_MULTIPLY);
  TCODConsole::root->printEx(1, 4, TCOD_BKGND_NONE, TCOD_LEFT, "[alt+enter]: toggle fullscreen, [pause]: toggle music, [backspace]: screen capture");
  TCODConsole::root->printEx(DISPLAY_WIDTH - 2, 4, TCOD_BKGND_NONE, TCOD_RIGHT, "last frame: %3d ms (%3d fps)", static_cast<int>(1000.0f*TCODSystem::getLastFrameLength()), TCODSystem::getFps());

  // Fade in
  if(*first)
  {
    for(int fade = 0; fade <= 255; fade += 25)
    {
      TCODConsole::setFade(fade, TCODColor::black);
      TCODConsole::flush();
    }
    *first = false;
  }
}

void Game::displayProgress(const char msg[], float fraction)
{
  int length = static_cast<int>(fraction*SCREEN_WIDTH/2);
  TCODConsole::root->setDefaultBackground(TCODColor::black);
  TCODConsole::root->setDefaultForeground(TCODColor::white);
  TCODConsole::root->clear();
  TCODConsole::root->printEx(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 4, TCOD_BKGND_NONE, TCOD_CENTER, msg); //"Generating Serpentine Caves");
  if(length > 0)
  {
    TCODConsole::root->setDefaultBackground(TCODColor::red);
    TCODConsole::root->rect(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, length, 2, false, TCOD_BKGND_SET);
  }
  if(length < SCREEN_WIDTH/2)
  {
    TCODConsole::root->setDefaultBackground(TCODColor::darkestRed);
    TCODConsole::root->rect(SCREEN_WIDTH/4 + length, SCREEN_HEIGHT/2, SCREEN_WIDTH/2 - length, 2, false, TCOD_BKGND_SET);
  }
  TCODConsole::root->flush();
}
