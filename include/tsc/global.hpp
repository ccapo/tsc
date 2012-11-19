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

using namespace std;

// Version
#define VERSION "0.3.0"

// Save game magic number
#define SAVEGAME_MAGIC_NUMBER 0xFD051E4F

// Save game file name
#define SAVEGAME_FILENAME "data/.save/savedgame.gz"

// Size of the map portion shown on-screen
#define DISPLAY_WIDTH 120
#define DISPLAY_HEIGHT 72

// Size of the window
#define SCREEN_WIDTH (DISPLAY_WIDTH)
#define SCREEN_HEIGHT (5*DISPLAY_HEIGHT/4 + 5)

// Size of the map
#define MAP_WIDTH (2*DISPLAY_WIDTH)
#define MAP_HEIGHT (2*DISPLAY_HEIGHT)

// Size of the 2x map
#define MAP_WIDTH2 (2*MAP_WIDTH)
#define MAP_HEIGHT2 (2*MAP_HEIGHT)
#define SCALE_FACTOR (2*MAP_WIDTH2/DISPLAY_WIDTH)

// Size of the static image maps
#define IMAGE_WIDTH 120
#define IMAGE_HEIGHT 72

// Size of the static image maps
#define IMAGE_WIDTH2 (2*IMAGE_WIDTH)
#define IMAGE_HEIGHT2 (2*IMAGE_HEIGHT)

// Maximum frame rate
#define FPSMAX 25

// Range of the height map
#define HM_MIN 0.75f
#define HM_MAX 0.95f

// Number of fonts
#define NFONTS 3

// Max. size of lists
#define NITEMMAX 64
#define NCREATUREMAX 1024
#define NCORPSEMAX 1024
#define NPCMAX 64
#define NLOCATIONMAX 32

// Number of regions
#define NREGIONS 4
#define NITEMS_REGION (NITEMS/NREGIONS)

// Number of world maps
#define NWORLDMAPS (NTEMPLES + NTOWNS + 1)

// Number of cave regions
#define NCAVE_REGIONS 3

// Number of cave levels per region
#define NLEVELS_REGION 5

// Number of cave maps
#define NCAVEMAPS (NCAVE_REGIONS*NLEVELS_REGION + 1)

// Number of commands in the info menu
#define NINFO 8

// Max. of messages
#define NMSGS 16

// Number of cells that border a cell
#define NBORDER 8

// Torch Information
#define TORCH_RADIUS 24.0f
#define SQUARED_TORCH_RADIUS (TORCH_RADIUS*TORCH_RADIUS)

// Number of sound channels
#define NCHANNEL 2

// Maximum size for character strings
#define CHARMAX 128

#define LEVELMAX 50

#define HPMIN 25
#define HPMAX 750

#define APMIN 4
#define APMAX 50

#define DPMIN 2
#define DPMAX 50

#define STRMIN 10
#define STRMAX 50

#define SPDMIN 1
#define SPDMAX FPSMAX

#define MPMIN 15
#define MPMAX 250

#define MAPMIN 2
#define MAPMAX 50

#define MDPMIN 1
#define MDPMAX 50

#define WILMIN 2
#define WILMAX 50

#define ACUMIN 1
#define ACUMAX 50

// Macros (Ugly, I know...)
#define IN_RECTANGLE(x,y,w,h) ((unsigned)(x) < (unsigned)(w) && (unsigned)(y) < (unsigned)(h))

#define SQRDIST(x1,y1,x2,y2) (((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2)))

#define ALL9FOV1XWALKABLE(x,y) (fov1x->isWalkable((x)-1,(y)-1) && fov1x->isWalkable((x),(y)-1) && fov1x->isWalkable((x)+1,(y)-1) && fov1x->isWalkable((x)-1,(y)) && fov1x->isWalkable((x),(y)) && fov1x->isWalkable((x)+1,(y)) && fov1x->isWalkable((x)-1,(y)+1) && fov1x->isWalkable((x),(y)+1) && fov1x->isWalkable((x)+1,(y)+1))

#define ANY9FOV1XWALKABLE(x,y) (fov1x->isWalkable((x)-1,(y)-1) || fov1x->isWalkable((x),(y)-1) || fov1x->isWalkable((x)+1,(y)-1) || fov1x->isWalkable((x)-1,(y)) || fov1x->isWalkable((x),(y)) || fov1x->isWalkable((x)+1,(y)) || fov1x->isWalkable((x)-1,(y)+1) || fov1x->isWalkable((x),(y)+1) || fov1x->isWalkable((x)+1,(y)+1))

#define ALL25FOV2XWALKABLE(x,y) (fov2x->isWalkable((x)-2,(y)-2) && fov2x->isWalkable((x)-1,(y)-2) && fov2x->isWalkable((x),(y)-2) && fov2x->isWalkable((x)+1,(y)-2) && fov2x->isWalkable((x)+2,(y)-2) && fov2x->isWalkable((x)-2,(y)-1) && fov2x->isWalkable((x)-1,(y)-1) && fov2x->isWalkable((x),(y)-1) && fov2x->isWalkable((x)+1,(y)-1) && fov2x->isWalkable((x)+2,(y)-1) && fov2x->isWalkable((x)-2,(y)) && fov2x->isWalkable((x)-1,(y)) && fov2x->isWalkable((x),(y)) && fov2x->isWalkable((x)+1,(y)) && fov2x->isWalkable((x)+2,(y)) && fov2x->isWalkable((x)-2,(y)+1) && fov2x->isWalkable((x)-1,(y)+1) && fov2x->isWalkable((x),(y)+1) && fov2x->isWalkable((x)+1,(y)+1) && fov2x->isWalkable((x)+2,(y)+1) && fov2x->isWalkable((x)-2,(y)+2) && fov2x->isWalkable((x)-1,(y)+2) && fov2x->isWalkable((x),(y)+2) && fov2x->isWalkable((x)+1,(y)+2) && fov2x->isWalkable((x)+2,(y)+2))

#define ANY25FOV2XWALKABLE(x,y) (fov2x->isWalkable((x)-2,(y)-2) || fov2x->isWalkable((x)-1,(y)-2) || fov2x->isWalkable((x),(y)-2) || fov2x->isWalkable((x)+1,(y)-2) || fov2x->isWalkable((x)+2,(y)-2) || fov2x->isWalkable((x)-2,(y)-1) || fov2x->isWalkable((x)-1,(y)-1) || fov2x->isWalkable((x),(y)-1) || fov2x->isWalkable((x)+1,(y)-1) || fov2x->isWalkable((x)+2,(y)-1) || fov2x->isWalkable((x)-2,(y)) || fov2x->isWalkable((x)-1,(y)) || fov2x->isWalkable((x),(y)) || fov2x->isWalkable((x)+1,(y)) || fov2x->isWalkable((x)+2,(y)) || fov2x->isWalkable((x)-2,(y)+1) || fov2x->isWalkable((x)-1,(y)+1) || fov2x->isWalkable((x),(y)+1) || fov2x->isWalkable((x)+1,(y)+1) || fov2x->isWalkable((x)+2,(y)+1) || fov2x->isWalkable((x)-2,(y)+2) || fov2x->isWalkable((x)-1,(y)+2) || fov2x->isWalkable((x),(y)+2) || fov2x->isWalkable((x)+1,(y)+2) || fov2x->isWalkable((x)+2,(y)+2))
