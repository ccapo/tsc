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

#include "main.hpp"

// The constructor
Sound::Sound(void)
{
  on = false;
  possible = true;
  updateCalled = false;
  first = false;
  activeChannel = 0;
  crossFading = false;
}

// Startup the sound system
void Sound::startup()
{
#ifndef NOSOUND
  static const char *music_files[NMUSIC] = {
    "data/music/The_Saga_Begins.ogg",       // Main Menu Music
    "data/music/Time.mp3",                  // Build World Music
    "data/music/Woods_of_Eremae.ogg",       // World Music
    "data/music/Virtue_Lost.ogg",           // Temple Music
    "data/music/Desert_Village.mp3",        // Town Music
    "data/music/Rainy_Day.ogg",             // Good Night Music
    "data/music/Cemetery.mp3",              // 1st Tier Cave Music
    "data/music/Suspicion.mp3",             // 2nd Tier Cave Music
    "data/music/The_Hollows.mp3",           // 3rd Tier Cave Music
    "data/music/Daemon.mp3",                // Mini-Boss Battle Music
    "data/music/Battle_Against_Time.mp3",   // Final Battle Music
    "data/music/Far_Away.mp3"};             // End Credits Music

  result = FMOD_System_Create(&system);
  result = FMOD_System_SetOutput(system, FMOD_OUTPUTTYPE_ALSA);
  result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, 0);
  if(result != FMOD_OK)
  {
    printf("Warning: Could not initialize sound system: %s", FMOD_ErrorString(result));
    possible = false;
  }

  for(int i = 0; i < NMUSIC; i++)
  {
    result = FMOD_System_CreateStream(system, music_files[i], FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &snd[i]);
    if(result != FMOD_OK)
    {
      printf("Warning: Could not load sound %s: %s", music_files[i], FMOD_ErrorString(result));
      possible = false;
    }
  }
#else
  possible = false;
#endif
}

// Shutdown the sound system
void Sound::shutdown()
{
#ifndef NOSOUND
  for(int i = 0; i < NMUSIC; i++) unload(i);

  result = FMOD_System_Close(system);
  result = FMOD_System_Release(system);
  if(result != FMOD_OK)
  {
    printf("Warning: Could not shutdown sound system: %s", FMOD_ErrorString(result));
    possible = false;
  }
#endif
}

// Frees the sound object
void Sound::unload(int i)
{
#ifndef NOSOUND
  if(possible)
  {
    result = FMOD_Sound_Release(snd[i]);
    if(result != FMOD_OK)
    {
      printf("Warning: Could not release sound object: %s", FMOD_ErrorString(result));
      possible = false;
    }
  }
#endif
}

// Plays a sound
void Sound::play(int i)
{
#ifndef NOSOUND
  int newChannel = 1 - activeChannel;

  if(possible)
  {
    setVolume(newChannel, 0.0f);
    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, snd[i], false, &channel[newChannel]);
    on = true;
  }
#endif
}

// Sets the actual playing sound's volume
void Sound::setVolume(int ichannel, float vol)
{
#ifndef NOSOUND
  if(possible && on) FMOD_Channel_SetVolume(channel[ichannel], vol);
#endif
}

// Toggle the sound's volume
void Sound::toggleVolume(float setvol)
{
#ifndef NOSOUND
  float vol;

  if(possible && on)
  {
    FMOD_Channel_GetVolume(channel[activeChannel], &vol);
    //vol = (vol >= 1.0f ? 0.5f : 1.0f);
    vol = (1.0f + setvol) - vol;
    FMOD_Channel_SetVolume(channel[activeChannel], vol);
  }
#endif
}


// Toggle pause on and off
void Sound::crossFade(float elapsed)
{
#ifndef NOSOUND
  int newChannel = 1 - activeChannel;
  static float dt = 0.0f;
  static const float rate = 0.1f; // Crossfade rate
  static float vol = 0.0f;

  if(possible)
  {
    if(vol < 1.0f)
    {
      dt += elapsed;
      vol += rate*dt;
      if(vol >= 1.0f)
      {
        vol = 1.0f;
        crossFading = false;
      }
      setVolume(activeChannel, 1.0f - vol);
      setVolume(newChannel, vol);

      if(!crossFading)
      {
        FMOD_Channel_Stop(channel[activeChannel]);
        activeChannel = newChannel;
        dt = 0.0f;
        vol = 0.0f;
      }
    }
  }
#else
  crossFading = false;
#endif
}

// Pause or unpause the sound
void Sound::setPause(bool pause)
{
#ifndef NOSOUND
  if(possible && on) FMOD_Channel_SetPaused(channel[activeChannel], pause);
#endif
}

// Toggle pause on and off
void Sound::togglePause()
{
#ifndef NOSOUND
  FMOD_BOOL p;

  if(possible)
  {
    FMOD_Channel_GetPaused(channel[activeChannel], &p);
    FMOD_Channel_SetPaused(channel[activeChannel], !p);
  }
#endif
}

// End frame
void Sound::endFrame()
{
  updateCalled = false;
}

// Update sound system
void Sound::update()
{
#ifndef NOSOUND
  if(possible && !updateCalled)
  {
    FMOD_System_Update(system);
    updateCalled = true;
  }
#endif
}
