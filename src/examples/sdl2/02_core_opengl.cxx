/*
  CCTools SDL plugin GLES example

  Derived from SDL testgles sources:

  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles.h>

#include <sdl2_cxx/core.hxx>
#include <sdl2_cxx/events.hxx>
#include <sdl2_cxx/time.hxx>
#include <sdl2_cxx/video.hxx>

static void AspectAdjust(int w, int h)
{
  float aspectAdjust;

  aspectAdjust = (4.0f / 3.0f) / ((float)w / h);
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrthof(-2.0, 2.0, -2.0 * aspectAdjust, 2.0 * aspectAdjust, -20.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glShadeModel(GL_SMOOTH);
}

static void Render()
{
  static GLubyte color[8][4] = {
      {255, 0, 0, 0}, {255, 0, 0, 255}, {0, 255, 0, 255}, {0, 255, 0, 255}, {0, 255, 0, 255}, {255, 255, 255, 255}, {255, 0, 255, 255}, {0, 0, 255, 255}};
  static GLfloat cube[8][3] = {{0.5, 0.5, -0.5},
                               {0.5f, -0.5f, -0.5f},
                               {-0.5f, -0.5f, -0.5f},
                               {-0.5f, 0.5f, -0.5f},
                               {-0.5f, 0.5f, 0.5f},
                               {0.5f, 0.5f, 0.5f},
                               {0.5f, -0.5f, 0.5f},
                               {-0.5f, -0.5f, 0.5f}};
  static GLubyte indices[36] = {0, 3, 4, 4, 5, 0, 0, 5, 6, 6, 1, 0,

                                6, 7, 2, 2, 1, 6, 7, 4, 3,

                                3, 2, 7, 5, 4, 7, 7, 6, 5,

                                2, 3, 1, 3, 0, 1};

  /* Do our drawing, too. */
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Draw the cube */
  glColorPointer(4, GL_UNSIGNED_BYTE, 0, color);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, cube);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

  glMatrixMode(GL_MODELVIEW);
  glRotatef(5.0, 1.0, 1.0, 1.0);
}

int main(int argc, char* argv[])
{
  static SDL_GLContext context;

  sdl2::init_guard sdl2_guard{sdl2::init_flags::everything};

  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);

  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

  sdl2::window window{
      "GLES example", sdl2::windowpos::centered, sdl2::windowpos::centered, mode.w, mode.h, sdl2::window_flags::opengl | sdl2::window_flags::shown};

  // Create our opengl context and attach it to our window
  context = SDL_GL_CreateContext(sdl2::to_sdl_type(window));
  if (!context)
  {
    sdl2::log::out() << sdl2::log::priority::error << "Unable to create GL context";
    return 1;
  }

  SDL_GL_MakeCurrent(sdl2::to_sdl_type(window), context);

  SDL_GL_SetSwapInterval(1);

  sdl2::log::out() << sdl2::log::priority::information << "Screen bpp : " << SDL_BITSPERPIXEL(mode.format);
  sdl2::log::out() << sdl2::log::priority::information << "Vendor     : " << glGetString(GL_VENDOR);
  sdl2::log::out() << sdl2::log::priority::information << "Renderer   : " << glGetString(GL_RENDERER);
  sdl2::log::out() << sdl2::log::priority::information << "Version    : " << glGetString(GL_VERSION);
  sdl2::log::out() << sdl2::log::priority::information << "Extensions : " << glGetString(GL_EXTENSIONS);

  AspectAdjust(mode.w, mode.h);

  /* Main render loop */
  sdl2::uint32_t frames = 0;
  auto then = sdl2::ticks();

  bool done = false;
  while (!done)
  {
    /* Check for events */
    ++frames;

    sdl2::event_handler::poll([&done](auto e) {
      auto type = sdl2::event_traits::type(e);
      if (type == sdl2::event_type::quit)
      {
        done = true;
      }
    });

    Render();
    SDL_GL_SwapWindow(sdl2::to_sdl_type(window));
  }

  /* Print out some timing information */
  auto now = sdl2::ticks();
  if (now > then)
  {
    sdl2::log::out() << sdl2::log::priority::information << ((double)frames * 1000) / (now - then) << " frames per second\n";
  }

  SDL_GL_DeleteContext(context);

  return 0;
}