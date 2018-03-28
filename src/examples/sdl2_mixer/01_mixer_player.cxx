

#include <sdl2_cxx/core/init.hxx>
#include <sdl2_cxx/time/timer.hxx>

#include <SDL_mixer.h>

#define WAV_PATH EXAMPLE_DATA "/heartbeat1.wav"
#define MUS_PATH EXAMPLE_DATA "/0477.ogg"

// Our wave file
Mix_Chunk* wave = NULL;
// Our music file
Mix_Music* music = NULL;

int main(int argc, char* args[])
{
  sdl2::init_guard sdl_guard{sdl2::init_flags::audio, sdl2::init_flags::video};

  // Initialize SDL_mixer
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return -1;

  // Load our sound effect
  wave = Mix_LoadWAV(WAV_PATH);
  if (wave == NULL) return -1;

  // Load our music
  music = Mix_LoadMUS(MUS_PATH);
  if (music == NULL) return -1;

  if (Mix_PlayChannel(-1, wave, 0) == -1) return -1;

  if (Mix_PlayMusic(music, -1) == -1) return -1;

  using namespace std::chrono_literals;
  sdl2::delay(2s);

  // clean up our resources
  Mix_FreeChunk(wave);
  Mix_FreeMusic(music);

  // quit SDL_mixer
  Mix_CloseAudio();

  return 0;
}