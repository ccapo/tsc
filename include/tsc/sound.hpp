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

// Background music identifiers
enum ESound
{
  SOUND_MAIN_MENU,
  SOUND_BUILD_MAP,
  SOUND_WORLD_MAP,
  SOUND_TEMPLE_MAP,
  SOUND_TOWN_MAP,
  SOUND_GOOD_NIGHT,
  SOUND_CAVE_MOOD_01,
  SOUND_CAVE_MOOD_02,
  SOUND_CAVE_MOOD_03,
  SOUND_GUARDIAN_BATTLE,
  SOUND_FINAL_BATTLE,
  SOUND_END_CREDITS,
  NMUSIC
};

class Sound
{
  private:
    bool on;
    bool possible;
    bool updateCalled; // update called this frame
#ifndef NOSOUND
    FMOD_RESULT  result;
    FMOD_SYSTEM  *system;
    FMOD_SOUND   *snd[NMUSIC];
    FMOD_CHANNEL *channel[NCHANNEL];
#endif

  public:
    int activeChannel;
    bool crossFading;
    bool first;

    // Constructor
    Sound(void);

    // System control
    void startup(); 
    void shutdown();
    void unload(int i);
    void endFrame();
    void update();

    // Sound control
    void play(int i);
    void setVolume(int ichannel, float vol);
    void toggleVolume(float setvol);
    void crossFade(float elapsed);
    void setPause(bool pause);
    void togglePause();
};
