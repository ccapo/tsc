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

// Colour map
const float hWater = 0.0f;
const float hSand = 0.1f;
const float hGrass = 0.5f;
const float hMax = 1.0f;
const TCODColor colourMap[NCOLOURMAP] = {
  TCODColor(47,47,64),    // 0, deep water
  TCODColor(111,127,159), // 1, water-sand transition
  TCODColor(191,191,159), // 2, sand
  TCODColor(63,127,31),   // 3, sand-grass transition
  TCODColor(31,63,31)};   // 4, grass

const TCODColor darkWall = TCODColor::darkestGrey;
const TCODColor lightWall = TCODColor(130,110,50);
const TCODColor darkGround = TCODColor::darkerGrey;
const TCODColor lightGround = TCODColor(200,180,50);

// The explicit construction of the world map locations
const Location locWorld[NWORLDMAPLOCATIONS] = {
  Location(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, "Light Temple", TCODColor::lighterYellow, TCOD_CHAR_RADIO_SET),
  Location(76, 24, "Fire Temple",  TCODColor::red, TCOD_CHAR_RADIO_SET),
  Location(61, 66, "Water Temple", TCODColor::blue, TCOD_CHAR_RADIO_SET),
  Location(13,  6, "Wind Temple",  TCODColor::yellow, TCOD_CHAR_RADIO_SET),
  Location(22, 47, "Earth Temple", TCODColor::green, TCOD_CHAR_RADIO_SET),
  Location(57,  6, "Rivendell",    TCODColor::black, TCOD_CHAR_RADIO_SET),
  Location( 9, 16, "Edoras",       TCODColor::black, TCOD_CHAR_RADIO_SET),
  Location(38, 22, "Erebor",       TCODColor::black, TCOD_CHAR_RADIO_SET),
  Location(76, 53, "Dol Amroth",   TCODColor::black, TCOD_CHAR_RADIO_SET),
  Location(37, 59, "Khazad-dum",   TCODColor::black, TCOD_CHAR_RADIO_SET),
  Location(95, 40, "Isengard",     TCODColor::black, TCOD_CHAR_RADIO_SET),
  Location(67, 30, "Minas Tirith", TCODColor::black, TCOD_CHAR_RADIO_SET),
  Location(103, 62, "Serpentine Caves", TCODColor::darkSepia, TCOD_CHAR_RADIO_SET)};

// The default map constructor
WorldMap::WorldMap(): nlocations(0), displayWeather(true), musicID(SOUND_WORLD_MAP)
{
  // FOV Maps
  fov1x = new TCODMap(IMAGE_WIDTH, IMAGE_HEIGHT);
  fov2x = new TCODMap(IMAGE_WIDTH2, IMAGE_HEIGHT2);

  // Image and thumbnail
  img = new TCODImage(IMAGE_WIDTH2, IMAGE_HEIGHT2);
  img_thumb = new TCODImage(IMAGE_WIDTH2/4, IMAGE_HEIGHT2/4);
}

// Updates World Map
void WorldMap::update()
{
  static float offsetW = 0.18f; // This is the noise offset to make it scroll for waves
  static float offsetC = 0.23f; // This is the noise offset to make it scroll for clouds

  if(displayWeather)
  {
    // Cycle through all the cells
    for(int x = 0; x < IMAGE_WIDTH2; x++)
    {
      for(int y = 0; y < IMAGE_HEIGHT2; y++)
      {
        // Now for the fun part!
        float c[3], w[3];
        w[0] = 60.0f*(x + 0.4f*offsetW)/IMAGE_WIDTH2;
        w[1] = 60.0f*(y + 0.6f*offsetW)/IMAGE_HEIGHT2;
        w[2] = (60*offsetW)/IMAGE_WIDTH2; // Z axis for the waves
        c[0] = 2.0f*(x + 0.33f*offsetC)/IMAGE_WIDTH2;
        c[1] = (y + offsetC)/IMAGE_HEIGHT2;
        c[2] = (2*offsetC)/IMAGE_WIDTH2;  // Z axis for the clouds

        // First, reset the colour to base
        int offset = x + IMAGE_WIDTH2*y;
        subcells[offset].finalColour = subcells[offset].baseColour;
        float coefW = game.weather->get(w)*0.2f;     // Get the waves value
        float coefC = game.weather->getFbm(c, 5.0f); // Get the clouds value

        // Apply colours, waves first
        if(subcells[offset].isWater)
        {
          // If waves value is over 0, lerp with white
          if(coefW >= 0.0f)
          {
            subcells[offset].finalColour = TCODColor::lerp(subcells[offset].finalColour, TCODColor::white, coefW);
          }
          // In other case, lerp with black
          else
          {
            subcells[offset].finalColour = TCODColor::lerp(subcells[offset].finalColour, TCODColor::black, ABS(coefW));
          }
        }

        // After the waves have been done (or not), lerp the colour with white by the clouds value.
        // Here we only take in account values > 0.25, so there are clear patches as well.
        if(coefC > 0.25f) subcells[offset].finalColour = TCODColor::lerp(subcells[offset].finalColour, TCODColor::white, coefC - 0.25f);
        img->putPixel(x, y, subcells[offset].finalColour);
      }
    }
    offsetW += 0.23f; // increase the waves offset to scroll the noises in the next frame
    offsetC += 0.27f; // increase the clouds offset to scroll the noises in the next frame
  }
}

// Renders World Map
void WorldMap::render(Player player)
{
  int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
  int tx = 3*DISPLAY_WIDTH/4 - 1, ty = DISPLAY_HEIGHT + 4;

  // Render the map
  for(int x = 0; x < IMAGE_WIDTH2; x++)
  {
    for(int y = 0; y < IMAGE_HEIGHT2; y++)
    {
      int offset = x + IMAGE_WIDTH2*y;
      img->putPixel(x, y, subcells[offset].baseColour);
      img_thumb->putPixel(x/4, y/4, subcells[offset].baseColour);
    }
  }

  // Update map
  update();

  // Send them to the root console
  img->blit2x(TCODConsole::root, 0, 3, 0, 0, w, h);
  for(int i = 0; i < nlocations; i++)
  {
    int lx = locations[i].x, ly = locations[i].y;
    img_thumb->putPixel(2*lx/4, 2*ly/4, locations[i].colour);
  }
  for(int i = 0; i < nnpcs; i++)
  {
    int lx = npcs[i].x, ly = npcs[i].y;
    img_thumb->putPixel(2*lx/4, 2*ly/4, npcs[i].colour);
  }
  img_thumb->putPixel(2*player.x/4, 2*player.y/4, player.colour);
  img_thumb->blit2x(TCODConsole::root, tx, ty);

  // Render the Npcs
  for(int i = 0; i < NPCMAX; i++) npcs[i].render(player);

  // Render Locations
  for(int i = 0; i < NLOCATIONMAX; i++) locations[i].render();
}

// Adds nHill randomly to the height map
void WorldMap::addHill(TCODHeightMap *hmap, int nHill, float baseRadius, float radiusVar, float h)
{
  for(int i = 0; i < nHill; i++)
  {
    float hillMinRadius = baseRadius*(1.0f - radiusVar);
    float hillMaxRadius = baseRadius*(1.0f + radiusVar);
    float radius = game.rng->getFloat(hillMinRadius, hillMaxRadius);
    float theta = game.rng->getFloat(0.0f, 2.0f*M_PI);  // Between (0.0, 2.0*pi)
    float dist = game.rng->getFloat(0.0f, static_cast<float>(MIN(IMAGE_WIDTH2, IMAGE_HEIGHT2)/2 - radius));
    int xh = static_cast<int>(IMAGE_WIDTH2/2 + cos(theta)*dist);
    int yh = static_cast<int>(IMAGE_HEIGHT2/2 + sin(theta)*dist);
    hmap->addHill(static_cast<float>(xh), static_cast<float>(yh), radius, h);
  }
}

// Builds the world heightmap
void WorldMap::generateHM(TCODHeightMap *hmap)
{
  hmap->clear();
  addHill(hmap, 600, 16.0*IMAGE_WIDTH2/400, 0.7f, 0.3f);
  hmap->normalize();
  //        mulx      muly      addx  addy  octaves  delta  scale
  hmap->addFbm(game.terrain,  2.20*IMAGE_WIDTH2/800,  2.20*IMAGE_HEIGHT2/800,  -20.0f,  15.0f,  32.0f,  0.0f,  2.0f);
  hmap->normalize(-hMax, hMax);

  hmap->add(-0.1f);
  hmap->clamp(-hMax, hMax);
  hmap->normalize(-hMax, hMax);
}

// Method for constructing the world map
void WorldMap::generateMap()
{
  TCODHeightMap *hmap = new TCODHeightMap(IMAGE_WIDTH2, IMAGE_HEIGHT2);

  generateHM(hmap);

  for(int x = 0; x < IMAGE_WIDTH2; x++)
  {
    for(int y = 0; y < IMAGE_HEIGHT2; y++)
    {
      int offset = x + IMAGE_WIDTH2*y;
      float h = hmap->getValue(x, y);

      if(h >= hGrass)
      {
        float coef = (h - hGrass)/(hMax - hGrass);
        subcells[offset].baseColour = TCODColor::lerp(colourMap[3], colourMap[4], coef);
        fov2x->setProperties(x, y, true, true);
      }
      else if(h >= hSand)
      {
        float coef = (h - hSand)/(hGrass - hSand);
        subcells[offset].baseColour = TCODColor::lerp(colourMap[2], colourMap[3], coef);
        fov2x->setProperties(x, y, true, true);
      }
      else if(h >= hWater)
      {
        float coef = (h - hWater)/(hSand - hWater);
        subcells[offset].baseColour = TCODColor::lerp(colourMap[1], colourMap[2], coef);
        fov2x->setProperties(x, y, true, false);
      }
      else
      {
        float coef = ABS(h);
        subcells[offset].baseColour = TCODColor::lerp(colourMap[1], colourMap[0], coef);
        subcells[offset].isWater = true;
        fov2x->setProperties(x, y, true, false);
      }
      img->putPixel(x, y, subcells[offset].baseColour);
      //img_thumb->putPixel(x, y, subcells[offset].baseColour);
    }
  }

  // Set walk and transparent information in the normal resolution map
  for(int x = 0; x < IMAGE_WIDTH; x++)
  {
    for(int y = 0; y < IMAGE_HEIGHT; y++)
    {
      bool trans = true, walk = true;
      if(!isFov2xTransparent(2*x    , 2*y    )) trans = false;
      if(!isFov2xTransparent(2*x + 1, 2*y    )) trans = false;
      if(!isFov2xTransparent(2*x    , 2*y + 1)) trans = false;
      if(!isFov2xTransparent(2*x + 1, 2*y + 1)) trans = false;
      if(!isFov2xWalkable(2*x    , 2*y    )) walk = false;
      if(!isFov2xWalkable(2*x + 1, 2*y    )) walk = false;
      if(!isFov2xWalkable(2*x    , 2*y + 1)) walk = false;
      if(!isFov2xWalkable(2*x + 1, 2*y + 1)) walk = false;
      fov1x->setProperties(x, y, trans, walk);
    }
  }

  // Assign the location of all the places on the world map
  nlocations = NWORLD;
  for(int i = 0; i < nlocations; i++)
  {
    addLocation(locWorld[i].x, locWorld[i].y, locWorld[i].name, locWorld[i].colour, locWorld[i].sym);
  }

  delete hmap;
  hmap = NULL;
  //img->save("data/img/worldmap0.png");
  //img_thumb->save("data/img/worldmap_thumb0.png");
}

// Method for loading a map
void WorldMap::loadMap(const char filename[], const char name[], int musicIndex, bool init)
{
  sprintf(label, "%s", name);
  musicID = musicIndex;

  // Image and thumbnail
  img = new TCODImage(filename);
  //img_thumb = new TCODImage(filename);

  // Cycle through all the map's cells
  for(int x = 0; x < IMAGE_WIDTH2; x++)
  {
    for(int y = 0; y < IMAGE_HEIGHT2; y++)
    {
      // Assign colours according to it
      int offset = x + IMAGE_WIDTH2*y;
      TCODColor c = img->getPixel(x, y);
      subcells[offset].baseColour = c;
      subcells[offset].isWater = false;
      fov2x->setProperties(x, y, true, true);

      // Locate the pixels that are assigned to be water (World)
      if((c.r <= 111 && c.r >= 47) && (c.g <= 127 && c.g >= 47) && (c.b <= 159 && c.b >= 64))
      {
        subcells[offset].isWater = true;
        fov2x->setProperties(x, y, true, false);
      }

      // Locate the pixels that are assigned to be sand (World)
      if((c.r >= 111 && c.r <= 191) && (c.g >= 127 && c.g <= 191) && (c.b == 159))
      {
        fov2x->setProperties(x, y, true, false);
      }

      // Locate the pixels that are assigned to be a flagstones (Towns/Temples)
      if(c.r == c.g && c.g == c.b && c.b == c.r)
      {
        fov2x->setProperties(x, y, true, true);
      }

      // Locate the pixels that are assigned to be a wall (Towns/Temples)
      if(c.r == 95 && c.g == 95 && c.b == 95)
      {
        fov2x->setProperties(x, y, true, false);
      }

      // Locate the pixels that are assigned to be a table/desk (Towns/Temples)
      //if(c.r == 159 && c.g == 106 && c.b == 39)
      //{
      //  fov2x->setProperties(x, y, true, false);
      //}
    }
  }

  // Set walk and transparent information in the normal resolution map
  for(int x = 0; x < IMAGE_WIDTH; x++)
  {
    for(int y = 0; y < IMAGE_HEIGHT; y++)
    {
      bool trans = true, walk = true;
      if(!isFov2xTransparent(2*x    , 2*y    )) trans = false;
      if(!isFov2xTransparent(2*x + 1, 2*y    )) trans = false;
      if(!isFov2xTransparent(2*x    , 2*y + 1)) trans = false;
      if(!isFov2xTransparent(2*x + 1, 2*y + 1)) trans = false;
      if(!isFov2xWalkable(2*x    , 2*y    )) walk = false;
      if(!isFov2xWalkable(2*x + 1, 2*y    )) walk = false;
      if(!isFov2xWalkable(2*x    , 2*y + 1)) walk = false;
      if(!isFov2xWalkable(2*x + 1, 2*y + 1)) walk = false;
      fov1x->setProperties(x, y, trans, walk);
    }
  }

  if(game.worldID == 0)
  {
    // Assign the location of all the places on the world map
    if(init)
    {
      nlocations = NWORLD;
      nnpcs = 0;
      for(int i = 0; i < nlocations; i++)
      {
        addLocation(locWorld[i].x, locWorld[i].y, locWorld[i].name, locWorld[i].colour, locWorld[i].sym);
      }
    }
    displayWeather = true;
  }
  else
  {
    // Assign Npcs to the appropriate towns and temples
    if(init)
    {
      int id = game.worldID - 1;
      if(id == TEMPLE_LIGHT)
      {
        nlocations = 0;
        nnpcs = 1;
        addNpc(IMAGE_WIDTH/2, IMAGE_HEIGHT/2, 6, NPCTYPE_LIGHTGUARDIAN);
      }
      else if(id == TEMPLE_FIRE)
      {
        nlocations = 0;
        nnpcs = 1;
        addNpc(IMAGE_WIDTH/2, IMAGE_HEIGHT/2, 6, NPCTYPE_FIREGUARDIAN);
      }
      else if(id == TEMPLE_WATER)
      {
        nlocations = 0;
        nnpcs = 1;
        addNpc(IMAGE_WIDTH/2, IMAGE_HEIGHT/2, 6, NPCTYPE_WATERGUARDIAN);
      }
      else if(id == TEMPLE_WIND)
      {
        nlocations = 0;
        nnpcs = 1;
        addNpc(IMAGE_WIDTH/2, IMAGE_HEIGHT/2, 6, NPCTYPE_WINDGUARDIAN);
      }
      else if(id == TEMPLE_EARTH)
      {
        nlocations = 0;
        nnpcs = 1;
        addNpc(IMAGE_WIDTH/2, IMAGE_HEIGHT/2, 6, NPCTYPE_EARTHGUARDIAN);
      }
      else if(id >= TOWN_01 && id <= TOWN_07)
      {
        nlocations = 1;
        addLocation(IMAGE_WIDTH/2, IMAGE_HEIGHT/2, "Town Centre", TCODColor::gold, ' ');

        nnpcs = 4 + 5 + 16;
        addNpc(IMAGE_WIDTH/4, IMAGE_HEIGHT/2, 0, NPCTYPE_ITEMSHOPKEEPER);
        addNpc(3*IMAGE_WIDTH/4 - 1, IMAGE_HEIGHT/2, 0, NPCTYPE_EQUIPSHOPKEEPER);
        addNpc(IMAGE_WIDTH/2, IMAGE_HEIGHT/4, 0, NPCTYPE_INNKEEPER);
        addNpc(IMAGE_WIDTH/2 + 4, IMAGE_HEIGHT/8 - 4, 0, NPCTYPE_FERRYMAN);

        addNpc(IMAGE_WIDTH/4 + 4, IMAGE_HEIGHT/4 + 4, 0, NPCTYPE_TOWNSPERSON);
        addNpc(IMAGE_WIDTH/4 + 9, IMAGE_HEIGHT/4 + 4, 0, NPCTYPE_TOWNSPERSON);
        addNpc(3*IMAGE_WIDTH/4 - 10, IMAGE_HEIGHT/4 + 4, 0, NPCTYPE_TOWNSPERSON);
        addNpc(3*IMAGE_WIDTH/4 - 5, IMAGE_HEIGHT/4 + 4, 0, NPCTYPE_TOWNSPERSON);
        addNpc(IMAGE_WIDTH/2 + 2, IMAGE_HEIGHT/2 + 1, 0, NPCTYPE_TOWNSPERSON);

        for(int i = 4 + 5; i < nnpcs; i++)
        {
          int x = 0, y = 0, sum = -1;
          while(sum < i - (4 + 5))
          {
            float r = game.rng->getFloat(2.0f, 12.0f);
            float theta = game.rng->getFloat(0.0f, 2.0f*M_PI);
            x = IMAGE_WIDTH/2 + static_cast<int>(r*cos(theta));
            y = IMAGE_HEIGHT/2 + static_cast<int>(r*sin(theta));
            sum = 0;
            for(int j = i - 1; j >= 4 + 5; j--)
            {
              if(x != npcs[j].x && y != npcs[j].y) sum++;
            }
          }
          addNpc(x, y, 3, NPCTYPE_TOWNSPERSON);
        }
      }
    }
    displayWeather = false;
  }
  //img->save("data/img/worldmap.png");
  //img_thumb->save("data/img/worldmap_thumb.png");
}

// Add a location to the map
void WorldMap::addLocation(int x, int y, const char name[], TCODColor colour, char sym)
{
  for(int i = 0; i < NLOCATIONMAX; i++)
  {
    if(!locations[i].inUse)
    {
      locations[i] = Location(x, y, name, colour, sym);
      cells[x + IMAGE_WIDTH*y].locationID = i;
      break;
    }
  }
}

// Add a Npc to the map
void WorldMap::addNpc(int x, int y, int spd, ENpcType npcType)
{
  for(int i = 0; i < NPCMAX; i++)
  {
    if(!npcs[i].inUse)
    {
      npcs[i] = Npc(x, y, spd, npcType);
      cells[x + IMAGE_WIDTH*y].creatureID = i;
      break;
    }
  }
}

// Update all the Npcs on the map
void WorldMap::updateNpcs(Player player, float elapsed)
{
  if(game.worldID >= NTEMPLES + 1 && game.worldID < NTEMPLES + NTOWNS + 1)
  {
    for(int i = 4; i < NPCMAX; i++) npcs[i].update(player, elapsed);
  }
}

// The default map constructor
CaveMap::CaveMap(): nitems(0), ncreatures(0), ncorpses(0), nlocations(0), upx(-1), upy(-1), downx(-1), downy(-1), display_x(0), display_y(0), recomputeFov(true), musicID(SOUND_CAVE_MOOD_01)
{
  // FOV Maps
  fov1x = new TCODMap(MAP_WIDTH, MAP_HEIGHT);
  fov2x = new TCODMap(MAP_WIDTH2, MAP_HEIGHT2);

  // Image and thumbnail
  img = new TCODImage(MAP_WIDTH2, MAP_HEIGHT2);
  img_thumb = new TCODImage(MAP_WIDTH2/SCALE_FACTOR, MAP_HEIGHT2/SCALE_FACTOR);
  img_thumb->clear(darkWall);
}

// Updates Cave Map
void CaveMap::update(Player player)
{
  static float torchx = 0.0f;
  int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
  int posx = 2*display_x, posy = 2*display_y;

  if(player.stats.hp > 0)
  {
    // Calculate the field of view from the player position
    if(recomputeFov)
    {
      recomputeFov = false;
      fov2x->computeFov(2*player.x, 2*player.y, static_cast<int>(TORCH_RADIUS), true, FOV_RESTRICTIVE);
    }

    // Torch position & intensity variation
    float dx = 0.0f, dy = 0.0f, di = 0.0f;

    // Slightly change the perlin noise parameter
    torchx += 0.2f;

    // Randomize the light position between -3.0 and 3.0
    float tdx = torchx + 20.0f;
    dx = 3.0f*game.torch->get(&tdx);
    tdx += 30.0f;
    dy = 3.0f*game.torch->get(&tdx);

    // Randomize the light intensity between -0.15 and 0.15
    di = 0.15f*game.torch->get(&torchx);

    // Update the cave map
    for(int x = posx; x < posx + w; x++)
    {
      for(int y = posy; y < posy + h; y++)
      {
        // Cell distance to torch (squared)
        float dxx = static_cast<float>(x - 2*player.x) + dx;
        float dyy = static_cast<float>(y - 2*player.y) + dy;
        float r2 = dxx*dxx + dyy*dyy;

        int offset = x + MAP_WIDTH2*y;
        bool visible = inFov2x(x, y) && (r2 < SQUARED_TORCH_RADIUS);
        bool wall = !isFov2xWalkable(x, y);
        bool explored = getExplored(x, y);

        if(visible)
        {
          setExplored(x, y);

          // Torch flickering FX
          TCODColor base = subcells[offset].baseColour;
          TCODColor light = (wall ? lightWall : lightGround);
          if(r2 < SQUARED_TORCH_RADIUS)
          {
            // l = 1.0 at player position, 0.0 at a radius of TORCH_RADIUS cells
            float coef1 = 1.0f/(1.0f + r2/20.0f);
            float coef2 = coef1 - 1.0f/(1.0f + SQUARED_TORCH_RADIUS);
            float l = coef2/(1.0f - 1.0f/(1.0f + SQUARED_TORCH_RADIUS)) + di;
            l = CLAMP(0.0f, 1.0f, l);

            // Interpolate the colour
            base = TCODColor::lerp(base, light, l);
          }
          light = base;
          subcells[offset].finalColour = light;
        }
        else
        {
          if(explored)
          {
            if(subcells[offset].baseColour != darkWall)
            {
              subcells[offset].finalColour = 0.5f*subcells[offset].baseColour;
            }
            else
            {
              subcells[offset].finalColour = darkWall;
            }
          }
          else
          {
            subcells[offset].finalColour = darkWall;
          }
        }
        img->putPixel(x, y, subcells[offset].finalColour);
        img_thumb->putPixel(x/SCALE_FACTOR, y/SCALE_FACTOR, subcells[offset].finalColour);
      }
    }
  }
  else
  {
    // Cycle through all the cells
    for(int x = posx; x < posx + w; x++)
    {
      for(int y = posy; y < posy + h; y++)
      {
        // Now reset the colour to base colour
        int offset = x + MAP_WIDTH2*y;
        bool explored = getExplored(x, y);
        if(explored)
        {
          subcells[offset].finalColour = subcells[offset].baseColour;
        }
        else
        {
          subcells[offset].finalColour = darkWall;
        }
        img->putPixel(x, y, subcells[offset].finalColour);
        img_thumb->putPixel(x/SCALE_FACTOR, y/SCALE_FACTOR, subcells[offset].finalColour);
      }
    }
  }
}

// Renders Cave Map
void CaveMap::render(Player player)
{
  int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
  int tx = 3*DISPLAY_WIDTH/4 - 1, ty = DISPLAY_HEIGHT + 4;
  int posx = 2*display_x, posy = 2*display_y;

  for(int x = posx; x < posx + w; x++)
  {
    for(int y = posy; y < posy + h; y++)
    {
      int offset = x + MAP_WIDTH2*y;
      img->putPixel(x, y, subcells[offset].baseColour);
      img_thumb->putPixel(x/SCALE_FACTOR, y/SCALE_FACTOR, subcells[offset].baseColour);
    }
  }

  // Render the magic
  //for(Magic **it = magic.begin(); it != magic.end(); it++) (*it)->render();

  // Update map
  update(player);

  // Send them to the root console
  img->blit2x(TCODConsole::root, 0, 3, posx, posy, w, h);
  for(int i = 0; i < nlocations; i++)
  {
    int lx = locations[i].x, ly = locations[i].y + 3;
    if(getFov2xExplored(lx, ly))
    {
      img_thumb->putPixel(2*lx/SCALE_FACTOR, 2*ly/SCALE_FACTOR, locations[i].colour);
    }
  }
  img_thumb->putPixel(2*player.x/SCALE_FACTOR, 2*player.y/SCALE_FACTOR, player.colour);
  img_thumb->blit2x(TCODConsole::root, tx, ty);

  // Render the corpses
  for(int i = 0; i < NCORPSEMAX; i++) corpses[i].render(player);

  // Render the hides
  for(int i = 0; i < NCORPSEMAX; i++) hides[i].render(player);

  // Render the items
  for(int i = 0; i < NITEMMAX; i++) items[i].render();

  // Render the creatures
  for(int i = 0; i < NCREATUREMAX; i++) creatures[i].render(player);

  // Render locations
  for(int i = 0; i < NLOCATIONMAX; i++) locations[i].render();
}

// Builds the cave heightmap
void CaveMap::generateHM(TCODHeightMap *hmap)
{
  hmap->clear();
  //        mulx  muly  addx  addy  octaves  delta  scale
  hmap->addFbm(game.terrain,  8.0f,  8.0f,  0.0f,  0.0f,  8.0f,  0.0f,  1.0f);
  hmap->normalize(HM_MIN, HM_MAX);
}

// Fill (over write) all pixels that are not the fill color
void CaveMap::floodFill(int x, int y, TCODColor fill)
{
  // Test subcell base colour
  int offset = x + MAP_WIDTH2*y;
  if(subcells[offset].baseColour != fill)
  {
    subcells[offset].baseColour = fill;
    fov2x->setProperties(x, y, false, false);
    img->putPixel(x, y, fill);
    //img_thumb->putPixel(x, y, fill);

    floodFill(x - 1, y    , fill);
    floodFill(x + 1, y    , fill);
    floodFill(x    , y - 1, fill);
    floodFill(x    , y + 1, fill);
  }
}

void CaveMap::generateMap()
{
  static int xcentre = MAP_WIDTH2/2, ycentre = MAP_HEIGHT2/2;
  TCODHeightMap *hmap = new TCODHeightMap(MAP_WIDTH2, MAP_HEIGHT2);

  generateHM(hmap);

  for(int x = 0; x < MAP_WIDTH2; x += MAP_WIDTH2 - 1)
  {
    for(int y = 0; y < MAP_HEIGHT2; y++)
    {
      int offset = x + MAP_WIDTH2*y;
      subcells[offset].baseColour = darkWall;
      fov2x->setProperties(x, y, false, false);
      img->putPixel(x, y, subcells[offset].baseColour);
      //img_thumb->putPixel(x, y, subcells[offset].baseColour);

      int lx = xcentre, ly = ycentre;
      float zmax = hmap->getValue(lx, ly);
      TCODLine::init(lx, ly, x, y);
      while(!TCODLine::step(&lx, &ly)) zmax += hmap->getValue(lx, ly);

      lx = xcentre; ly = ycentre;
      float zthres = hmap->getValue(x, y);
      float ztotal = hmap->getValue(lx, ly)/zmax;
      TCODLine::init(lx, ly, x, y);

      int loffset = lx + MAP_WIDTH2*ly;
      float coef = (hmap->getValue(lx, ly) - HM_MIN)/(HM_MAX - HM_MIN);
      subcells[loffset].baseColour = TCODColor::lerp(darkWall, darkGround, coef);
      fov2x->setProperties(lx, ly, true, true);
      img->putPixel(lx, ly, subcells[loffset].baseColour);
      //img_thumb->putPixel(lx, ly, subcells[loffset].baseColour);

      while(!TCODLine::step(&lx, &ly))
      {
        loffset = lx + MAP_WIDTH2*ly;
        if(ztotal < zthres)
        {
          float coef = (hmap->getValue(lx, ly) - HM_MIN)/(HM_MAX - HM_MIN);
          subcells[loffset].baseColour = TCODColor::lerp(darkWall, darkGround, coef);
          fov2x->setProperties(lx, ly, true, true);
        }
        else
        {
          subcells[loffset].baseColour = darkWall;
          fov2x->setProperties(lx, ly, false, false);
        }
        ztotal += hmap->getValue(lx, ly)/zmax;
        img->putPixel(lx, ly, subcells[loffset].baseColour);
        //img_thumb->putPixel(lx, ly, subcells[loffset].baseColour);
      }
    }
  }

  for(int y = 0; y < MAP_HEIGHT2; y += MAP_HEIGHT2 - 1)
  {
    for(int x = 0; x < MAP_WIDTH2; x++)
    {
      int offset = x + MAP_WIDTH2*y;
      subcells[offset].baseColour = darkWall;
      fov2x->setProperties(x, y, false, false);
      img->putPixel(x, y, subcells[offset].baseColour);
      //img_thumb->putPixel(x, y, subcells[offset].baseColour);

      int lx = xcentre, ly = ycentre;
      float zmax = hmap->getValue(lx, ly);
      TCODLine::init(lx, ly, x, y);
      while(!TCODLine::step(&lx, &ly)) zmax += hmap->getValue(lx, ly);

      lx = xcentre; ly = ycentre;
      float zthres = hmap->getValue(x, y);
      float ztotal = hmap->getValue(lx, ly)/zmax;
      TCODLine::init(lx, ly, x, y);

      int loffset = lx + MAP_WIDTH2*ly;
      float coef = (hmap->getValue(lx, ly) - HM_MIN)/(HM_MAX - HM_MIN);
      subcells[loffset].baseColour = TCODColor::lerp(darkWall, darkGround, coef);
      fov2x->setProperties(lx, ly, true, true);
      img->putPixel(lx, ly, subcells[loffset].baseColour);
      //img_thumb->putPixel(lx, ly, subcells[loffset].baseColour);

      while(!TCODLine::step(&lx, &ly))
      {
        loffset = lx + MAP_WIDTH2*ly;
        if(ztotal < zthres)
        {
          float coef = (hmap->getValue(lx, ly) - HM_MIN)/(HM_MAX - HM_MIN);
          subcells[loffset].baseColour = TCODColor::lerp(darkWall, darkGround, coef);
          fov2x->setProperties(lx, ly, true, true);
        }
        else
        {
          subcells[loffset].baseColour = darkWall;
          fov2x->setProperties(lx, ly, false, false);
        }
        ztotal += hmap->getValue(lx, ly)/zmax;
        img->putPixel(lx, ly, subcells[loffset].baseColour);
        //img_thumb->putPixel(lx, ly, subcells[loffset].baseColour);
      }
    }
  }

  for(int x = 1; x < MAP_WIDTH2 - 1; x++)
  {
    for(int y = 1; y < MAP_HEIGHT2 - 1; y++)
    {
      int offset = x + MAP_WIDTH2*y;
      float z = hmap->getValue(x, y);
      if(z < 0.83f)
      {
        subcells[offset].baseColour = darkWall;
        fov2x->setProperties(x, y, false, false);
        img->putPixel(x, y, subcells[offset].baseColour);
        //img_thumb->putPixel(x, y, subcells[offset].baseColour);
      }
      subcells[offset].isExplored = false;
    }
  }
  delete hmap;
  hmap = NULL;
  //img->save("data/img/cavemap0.png");
  //img_thumb->save("data/img/cavemap_thumb0.png");
}

void CaveMap::finalizeMap(int level)
{
  static int caveRegion = 0;
  static int seed = game.seed;
  TCODDijkstra *dijkstra;
  int nWalkable, px, py;
  float fWalkable = 0.0f;

  if(level < NCAVES - 1)
  {
    nitems = 4 + static_cast<int>((NITEMMAX - 4)*(static_cast<float>(level)/static_cast<float>(NCAVES - 1)));
    ncreatures = 16 + static_cast<int>((NCREATUREMAX - 16)*(static_cast<float>(level)/static_cast<float>(NCAVES - 1)));
    ncorpses = nhides = NCORPSEMAX;
    nlocations = 2;

    sprintf(label, "Cave Depth %d", level + 1);
    if(level % NLEVELS == 0) caveRegion++;
    switch(caveRegion)
    {
      case 1: musicID = SOUND_CAVE_MOOD_01; break;
      case 2: musicID = SOUND_CAVE_MOOD_02; break;
      case 3: musicID = SOUND_CAVE_MOOD_03; break;
      default: break;
    }

    dijkstra = new TCODDijkstra(fov2x);
    TCODPath *path = new TCODPath(fov1x);
    path->compute(-1, -1, -1, -1);

    while(path->isEmpty())
    {
      while(fWalkable < 0.4f)
      {
        // Increment the seed value
        seed++;
        game.rng = new TCODRandom(seed, TCOD_RNG_CMWC);
        game.terrain = new TCODNoise(2, game.rng);

        // Generate a cave map using the new seed value
        generateMap();

        // Pick a reference location
        px = game.rng->getInt(2, MAP_WIDTH2 - 3);
        py = game.rng->getInt(2, MAP_HEIGHT2 - 3);
        while(!ALL25FOV2XWALKABLE(px, py))
        {
          px = game.rng->getInt(2, MAP_WIDTH2 - 3);
          py = game.rng->getInt(2, MAP_HEIGHT2 - 3);
        }

        dijkstra = new TCODDijkstra(fov2x);  // allocate the path
        dijkstra->compute(px, py);    // calculate distance from (px, py) to all other nodes
        nWalkable = 0;

        for(int x = 0; x < MAP_WIDTH2; x++)
        {
          for(int y = 0; y < MAP_HEIGHT2; y++)
          {
            if(isFov2xWalkable(x, y))
            {
              if(!dijkstra->setPath(x, y))
              {
                floodFill(x, y, darkWall);
              }
              else
              {
                nWalkable++;
              }
            }
          }
        }
        fWalkable = static_cast<float>(nWalkable)/static_cast<float>(MAP_WIDTH2*MAP_HEIGHT2);

        // Set walk and transparent information in the normal resolution map
        for(int x = 0; x < MAP_WIDTH; x++)
        {
          for(int y = 0; y < MAP_HEIGHT; y++)
          {
            bool trans = true, walk = true;
            if(!isFov2xTransparent(2*x    , 2*y    )) trans = false;
            if(!isFov2xTransparent(2*x + 1, 2*y    )) trans = false;
            if(!isFov2xTransparent(2*x    , 2*y + 1)) trans = false;
            if(!isFov2xTransparent(2*x + 1, 2*y + 1)) trans = false;
            if(!isFov2xWalkable(2*x    , 2*y    )) walk = false;
            if(!isFov2xWalkable(2*x + 1, 2*y    )) walk = false;
            if(!isFov2xWalkable(2*x    , 2*y + 1)) walk = false;
            if(!isFov2xWalkable(2*x + 1, 2*y + 1)) walk = false;
            fov1x->setProperties(x, y, trans, walk);
          }
        }
      }

      // Assign the location of the up and down stairs, ensuring they are sufficiently far apart
      upx = game.rng->getInt(1, MAP_WIDTH - 2);
      upy = game.rng->getInt(1, MAP_HEIGHT - 2);
      while(!ALL9FOV1XWALKABLE(upx, upy))
      {
        upx = game.rng->getInt(1, MAP_WIDTH - 2);
        upy = game.rng->getInt(1, MAP_HEIGHT - 2);
      }

      downx = game.rng->getInt(1, MAP_WIDTH - 2);
      downy = game.rng->getInt(1, MAP_HEIGHT - 2);
      while(!(ALL9FOV1XWALKABLE(downx, downy) && pow(downx - upx, 2) + pow(downy - upy, 2) >= 10000))
      {
        downx = game.rng->getInt(1, MAP_WIDTH - 2);
        downy = game.rng->getInt(1, MAP_HEIGHT - 2);
      }

      path = new TCODPath(fov1x);
      path->compute(upx, upy, downx, downy);
    }
    addLocation(upx, upy, "Tunnel Up", TCODColor::lightGrey, TCOD_CHAR_ARROW2_N);
    addLocation(downx, downy, "Tunnel Down", TCODColor::lightGrey, TCOD_CHAR_ARROW2_S);

    for(int i = 0; i < ncreatures; i++)
    {
      int qx = game.rng->getInt(0, MAP_WIDTH - 1);
      int qy = game.rng->getInt(0, MAP_HEIGHT - 1);
      while(!(isFov1xWalkable(qx, qy) && (pow(qx - upx, 2) + pow(qy - upy, 2)) >= 100 && (pow(qx - downx, 2) + pow(qy - downy, 2)) >= 100))
      {
        qx = game.rng->getInt(0, MAP_WIDTH - 1);
        qy = game.rng->getInt(0, MAP_HEIGHT - 1);
      }
      addCreature(caveRegion, qx, qy);
    }

    for(int i = 0; i < nitems; i++)
    {
      int qx = game.rng->getInt(0, MAP_WIDTH - 1);
      int qy = game.rng->getInt(0, MAP_HEIGHT - 1);
      while(!(isFov1xWalkable(qx, qy) && (pow(qx - upx, 2) + pow(qy - upy, 2)) >= 100 && (pow(qx - downx, 2) + pow(qy - downy, 2)) >= 100))
      {
        qx = game.rng->getInt(0, MAP_WIDTH - 1);
        qy = game.rng->getInt(0, MAP_HEIGHT - 1);
      }
      addItem(qx, qy);
    }

    delete path;
    path = NULL;
  }
  else
  {
    ncorpses = nhides = NCORPSEMAX;
    nlocations = 1;
    sprintf(label, "%s", "Final Battle Map");
    musicID = SOUND_FINAL_BATTLE;

    dijkstra = new TCODDijkstra(fov2x);

    while(fWalkable < 0.4f)
    {
      // Increment the seed value
      seed++;
      game.rng = new TCODRandom(seed, TCOD_RNG_CMWC);
      game.terrain = new TCODNoise(2, game.rng);

      // Generate a cave map using the new seed value
      generateMap();

      // Pick a reference location
      px = game.rng->getInt(2, MAP_WIDTH2 - 3);
      py = game.rng->getInt(2, MAP_HEIGHT2 - 3);
      while(!ALL25FOV2XWALKABLE(px, py))
      {
        px = game.rng->getInt(2, MAP_WIDTH2 - 3);
        py = game.rng->getInt(2, MAP_HEIGHT2 - 3);
      }

      dijkstra = new TCODDijkstra(fov2x);  // allocate the path
      dijkstra->compute(px, py);    // calculate distance from (px, py) to all other nodes
      nWalkable = 0;

      for(int x = 0; x < MAP_WIDTH2; x++)
      {
        for(int y = 0; y < MAP_HEIGHT2; y++)
        {
          if(isFov2xWalkable(x, y))
          {
            if(!dijkstra->setPath(x, y))
            {
              floodFill(x, y, darkWall);
            }
            else
            {
              nWalkable++;
            }
          }
        }
      }
      fWalkable = static_cast<float>(nWalkable)/static_cast<float>(MAP_WIDTH2*MAP_HEIGHT2);

      // Set walk and transparent information in the normal resolution map
      for(int x = 0; x < MAP_WIDTH; x++)
      {
        for(int y = 0; y < MAP_HEIGHT; y++)
        {
          bool trans = true, walk = true;
          if(!isFov2xTransparent(2*x    , 2*y    )) trans = false;
          if(!isFov2xTransparent(2*x + 1, 2*y    )) trans = false;
          if(!isFov2xTransparent(2*x    , 2*y + 1)) trans = false;
          if(!isFov2xTransparent(2*x + 1, 2*y + 1)) trans = false;
          if(!isFov2xWalkable(2*x    , 2*y    )) walk = false;
          if(!isFov2xWalkable(2*x + 1, 2*y    )) walk = false;
          if(!isFov2xWalkable(2*x    , 2*y + 1)) walk = false;
          if(!isFov2xWalkable(2*x + 1, 2*y + 1)) walk = false;
          fov1x->setProperties(x, y, trans, walk);
        }
      }
    }

    // Assign the location of the up and down stairs, ensuring they are sufficiently far apart
    upx = game.rng->getInt(1, MAP_WIDTH - 2);
    upy = game.rng->getInt(1, MAP_HEIGHT - 2);
    while(!ALL9FOV1XWALKABLE(upx, upy))
    {
      upx = game.rng->getInt(1, MAP_WIDTH - 2);
      upy = game.rng->getInt(1, MAP_HEIGHT - 2);
    }
    addLocation(upx, upy, "Tunnel Up", TCODColor::lightGrey, TCOD_CHAR_ARROW2_N);
  }

  // Setup player scent
  setupScent();

  delete dijkstra;
  dijkstra = NULL;
  //img->save("data/img/cavemap.png");
  //img_thumb->save("data/img/cavemap_thumb.png");
}

// Method for loading a cave map
void CaveMap::loadMap()
{
  // Cycle through all the map's cells
  for(int x = 0; x < MAP_WIDTH2; x++)
  {
    for(int y = 0; y < MAP_HEIGHT2; y++)
    {
      // Subcell offset
      int offset = x + MAP_WIDTH2*y;
      bool explored = getExplored(x, y);

      // Locate the pixels that are assigned to be an impassable wall
      if(subcells[offset].baseColour == darkWall)
      {
        fov2x->setProperties(x, y, false, false);
      }
      else
      {
        fov2x->setProperties(x, y, true, true);
      }

      if(explored)
      {
        subcells[offset].finalColour = subcells[offset].baseColour;
      }
      else
      {
        subcells[offset].finalColour = darkWall;
      }
      img_thumb->putPixel(x/SCALE_FACTOR, y/SCALE_FACTOR, subcells[offset].finalColour);
    }
  }

  // Set walk and transparent information in the normal resolution map
  for(int x = 0; x < MAP_WIDTH; x++)
  {
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
      bool trans = true, walk = true;
      if(!isFov2xTransparent(2*x    , 2*y    )) trans = false;
      if(!isFov2xTransparent(2*x + 1, 2*y    )) trans = false;
      if(!isFov2xTransparent(2*x    , 2*y + 1)) trans = false;
      if(!isFov2xTransparent(2*x + 1, 2*y + 1)) trans = false;
      if(!isFov2xWalkable(2*x    , 2*y    )) walk = false;
      if(!isFov2xWalkable(2*x + 1, 2*y    )) walk = false;
      if(!isFov2xWalkable(2*x    , 2*y + 1)) walk = false;
      if(!isFov2xWalkable(2*x + 1, 2*y + 1)) walk = false;
      fov1x->setProperties(x, y, trans, walk);
    }
  }
  //img->save("data/img/cavemap.png");
  //img_thumb->save("data/img/cavemap_thumb.png");
}

void CaveMap::moveDisplay(int x, int y)
{
  // New display coordinates (top-left corner of the screen relative to the map)
  // Coordinates so that the target is at the center of the screen
  int cx = x - DISPLAY_WIDTH/2;
  int cy = y - DISPLAY_HEIGHT/2;

  // Make sure the DISPLAY doesn't see outside the map
  if(cx < 0) cx = 0;
  if(cy < 0) cy = 0;
  if(cx > MAP_WIDTH - DISPLAY_WIDTH - 1) cx = MAP_WIDTH - DISPLAY_WIDTH - 1;
  if(cy > MAP_HEIGHT - DISPLAY_HEIGHT - 1) cy = MAP_HEIGHT - DISPLAY_HEIGHT - 1;

  if(cx != display_x || cy != display_y) recomputeFov = true;

  display_x = cx; display_y = cy;
}

void CaveMap::addItem(int x, int y)
{
  for(int i = 0; i < NITEMMAX; i++)
  {
    if(!items[i].inUse)
    {
      items[i].inUse = true;
      items[i].x = x;
      items[i].y = y;
      cells[x + MAP_WIDTH*y].itemID = i;
      break;
    }
  }
}

void CaveMap::removeItem(int x, int y)
{
  int id = cells[x + MAP_WIDTH*y].itemID;
  items[id].inUse = false;
  cells[x + MAP_WIDTH*y].itemID = -1;
}

void CaveMap::addCreature(int caveRegion, int x, int y)
{
  // Percentage of creature types
  int pInsect, pVermin, pReptile, pBeast, pTroglodyte, pGiant;

  for(int i = 0; i < NCREATUREMAX; i++)
  {
    if(!creatures[i].inUse)
    {
      // Select the percentage of creature types for each cave region
      switch(caveRegion)
      {
        case 1:
        {
          pInsect = 40; pVermin = 60;
          pReptile = 80; pBeast = 90;
          pTroglodyte = 101; pGiant = 102;
          break;
        }
        case 2:
        {
          pInsect = 20; pVermin = 40;
          pReptile = 60; pBeast = 80;
          pTroglodyte = 95; pGiant = 101;
          break;
        }
        case 3:
        {
          pInsect = 0; pVermin = 20;
          pReptile = 40; pBeast = 60;
          pTroglodyte = 80; pGiant = 99;
          break;
        }
        default:
        {
          pInsect = 40; pVermin = 60;
          pReptile = 80; pBeast = 90;
          pTroglodyte = 101; pGiant = 102;
          break;
        }
      }

      // Select a creature type according to given percentage
      int dice = game.rng->getInt(1, 100);
      ECreatureType creatureType;
      if(dice < pInsect)
      {
        // Insect Type: pInsect% of the time, if positive
        creatureType = CREATURETYPE_INSECT;
      }
      else if(dice >= pInsect && dice < pVermin)
      {
        // Vermin Type: (pVermin - pInsect)% of the time, if positive
        creatureType = CREATURETYPE_VERMIN;
      }
      else if(dice >= pVermin && dice < pReptile)
      {
        // Reptile Type: (pReptile - pVermin)% of the time
        creatureType = CREATURETYPE_REPTILE;
      }
      else if(dice >= pReptile && dice < pBeast)
      {
        // Beast Type: (pBeast - pReptile)% of the time, if positive
        creatureType = CREATURETYPE_BEAST;
      }
      else if(dice >= pBeast && dice < pTroglodyte)
      {
        // Troglodyte Type: (pTroglodyte - pBeast)% of the time, if positive
        creatureType = CREATURETYPE_TROGLODYTE;
      }
      else if(dice >= pTroglodyte && dice < pGiant)
      {
        // Giant Type: (pGiant - pTroglodyte)% of the time, if positive
        creatureType = CREATURETYPE_GIANT;
      }
      else
      {
        // Special Type: (100 - pGiant)% of the time, if positive
        creatureType = CREATURETYPE_SPECIAL;
      }

      // Assign selected creature type at given location
      creatures[i] = Creature(x, y, creatureType);
      cells[x + MAP_WIDTH*y].creatureID = i;
      break;
    }
  }
}

void CaveMap::removeCreature(int x, int y)
{
  int id = cells[x + MAP_WIDTH*y].creatureID;
  creatures[id].inUse = false;
  cells[x + MAP_WIDTH*y].creatureID = -1;
}

// Update all the Creatures in the cave
void CaveMap::updateCreatures(Player player, float elapsed)
{
  for(int i = 0; i < NCREATUREMAX; i++) creatures[i].update(player, elapsed);
}

void CaveMap::attackCreature(int x, int y)
{
  char buffer[CHARMAX];

  int id = getCreatureID(x, y);
  if(creatures[id].stats.hp > 0)
  {
    creatures[id].stats.hp -= CLAMP(0, 1000, game.player.stats.ap/2 - creatures[id].stats.dp/4);
    printf("Attacking %s: %d/%d\n", creatures[id].name, creatures[id].stats.hp, creatures[id].stats.hpmax);
          
    if(creatures[id].stats.hp <= 0)
    {
      game.player.xp += creatures[id].stats.hpmax/2;
      sprintf(buffer, "The %s Died!\n", creatures[id].name);
      game.menu.updateMessageLog(buffer);
      addHide(x, y, creatures[id].creatureType);
      removeCreature(x, y);
    }
  }
}

void CaveMap::addCorpse(int x, int y)
{
  for(int i = 0; i < NCORPSEMAX; i++)
  {
    if(!corpses[i].inUse)
    {
      corpses[i] = Corpse(x, y);
      cells[x + MAP_WIDTH*y].corpseID = i;
      break;
    }
  }
}

void CaveMap::removeCorpse(int x, int y)
{
  int id = cells[x + MAP_WIDTH*y].corpseID;
  corpses[id].inUse = false;
  cells[x + MAP_WIDTH*y].corpseID = -1;
}

void CaveMap::addHide(int x, int y, ECreatureType creatureType)
{
  for(int i = 0; i < NCORPSEMAX; i++)
  {
    if(!hides[i].inUse)
    {
      hides[i] = Hide(x, y, creatureType);
      cells[x + MAP_WIDTH*y].hideID = i;
      break;
    }
  }
}

void CaveMap::removeHide(int x, int y)
{
  int id = cells[x + MAP_WIDTH*y].hideID;
  hides[id].inUse = false;
  cells[x + MAP_WIDTH*y].hideID = -1;
}

void CaveMap::addLocation(int x, int y, const char name[], TCODColor colour, char sym)
{
  for(int i = 0; i < NLOCATIONMAX; i++)
  {
    if(!locations[i].inUse)
    {
      locations[i] = Location(x, y, name, colour, sym);
      cells[x + MAP_WIDTH*y].locationID = i;
      break;
    }
  }
}

// Setup the scent in the cave
void CaveMap::setupScent()
{
  for(int x = 0; x < MAP_WIDTH; x++)
  {
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
      cells[x + MAP_WIDTH*y].scent = 0.0f;
      cells[x + MAP_WIDTH*y].oldScent = 0.0f;
    }
  }
}

// Update the scent in the cave
void CaveMap::updateScent(int px, int py)
{
  const int dx[NBORDER] = {-1, 0, 1, -1, 1, -1, 0, 1};
  const int dy[NBORDER] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const float scent_0 = 1.0f, dcoef = 1.0f/32.0f, lambda = 1.0f;

  setOldScent(px, py, scent_0);

  for(int x = 1; x < MAP_WIDTH - 1; x++)
  {
    for(int y = 1; y < MAP_HEIGHT - 1; y++)
    {
      if(isFov1xWalkable(x, y))
      {
        float sdiff = 0.0f;
        for(int z = 0; z < NBORDER; z++)
        {
          sdiff += getOldScent(x + dx[z], y + dy[z]) - getOldScent(x, y);
        }
        setScent(x, y, lambda*(getOldScent(x, y) + dcoef*sdiff));
      }
      else
      {
        setScent(x, y, 0.0f);
      }
    }
  }

  for(int x = 1; x < MAP_WIDTH - 1; x++)
  {
    for(int y = 1; y < MAP_HEIGHT - 1; y++)
    {
      setOldScent(x, y, getScent(x, y));
    }
  }
}

bool CaveMap::hasLos(int xFrom, int yFrom, int xTo, int yTo, bool ignoreCreatures)
{
  TCODLine::init(xFrom, yFrom, xTo, yTo);
  while(!TCODLine::step(&xFrom, &yFrom))
  {
    if(!fov1x->isTransparent(xFrom, yFrom)) return false;
    if(!ignoreCreatures && (getCreatureID(xFrom, yFrom) >= 0)) return false;
  }
  return true;
}

void CaveMap::saveMap()
{
  char fname[CHARMAX];
  sprintf(fname, "cavemap_%02d.png", game.caveID + 1);

  // Save the map as a PNG
  TCODImage tmp(MAP_WIDTH2, MAP_HEIGHT2);

  for(int x = 0; x < MAP_WIDTH2; x++)
  {
    for(int y = 0; y < MAP_HEIGHT2; y++)
    {
      tmp.putPixel(x, y, fov2x->isTransparent(x,y) ? TCODColor::lightGrey : TCODColor::darkGrey);
    }
  }

  tmp.putPixel(2*game.player.x    , 2*game.player.y - 1, TCODColor::blue);
  tmp.putPixel(2*game.player.x - 1, 2*game.player.y    , TCODColor::blue);
  tmp.putPixel(2*game.player.x    , 2*game.player.y    , TCODColor::blue);
  tmp.putPixel(2*game.player.x + 1, 2*game.player.y    , TCODColor::blue);
  tmp.putPixel(2*game.player.x    , 2*game.player.y + 1, TCODColor::blue);

  tmp.putPixel(2*upx    , 2*upy - 1, TCODColor::green);
  tmp.putPixel(2*upx - 1, 2*upy    , TCODColor::green);
  tmp.putPixel(2*upx    , 2*upy    , TCODColor::green);
  tmp.putPixel(2*upx + 1, 2*upy    , TCODColor::green);
  tmp.putPixel(2*upx    , 2*upy + 1, TCODColor::green);

  tmp.putPixel(2*downx    , 2*downy - 1, TCODColor::red);
  tmp.putPixel(2*downx - 1, 2*downy    , TCODColor::red);
  tmp.putPixel(2*downx    , 2*downy    , TCODColor::red);
  tmp.putPixel(2*downx + 1, 2*downy    , TCODColor::red);
  tmp.putPixel(2*downx    , 2*downy + 1, TCODColor::red);

  tmp.save(fname);
}
