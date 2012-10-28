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

int main(int narg, char *argv[])
{
  bool startGame = false, newGame = false;
  bool firstFade = false, endGame = false;
	float elapsed = 1.0f/static_cast<float>(FPSMAX);
  TCOD_key_t key;
  TCOD_mouse_t mouse;

  // Startup Game
  game.startup(narg, argv);

  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, &mouse);

  // Loop Title Screen
  while(!startGame && !TCODConsole::isWindowClosed())
  {
    // Update the game
    startGame = game.updateTitle(elapsed, key);

    // Render the game screen
    game.renderTitle();

    // Flush updates to screen
    TCODConsole::root->flush();

    // Get keyboard and mouse input
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, &mouse);
  }

  // Loop Introdution Screen (New Games Only)
  newGame = (game.menu.selection == MAIN_NEW);
  firstFade = !newGame;
  game.menu.inGame = true;
  while(newGame)
  {
    // Update the game
    newGame = game.updateIntro(elapsed, key);

    // Render the game screen
    game.renderIntro();

    // Flush updates to screen
    TCODConsole::root->flush();

    // Get keyboard and mouse input
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, &mouse);
  }

  // Loop Game
  while(!endGame && !TCODConsole::isWindowClosed())
  {
    // Update the game
    endGame = game.update(elapsed, key, mouse);

    // Render the game screen
    game.render(&firstFade);

    // Flush updates to screen
    TCODConsole::root->flush();

    // Get keyboard and mouse input
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &key, &mouse);
  }

  // Shutdown Game
  game.shutdown();

  return 0;  
}
