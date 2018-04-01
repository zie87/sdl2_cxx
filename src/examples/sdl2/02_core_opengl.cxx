#include <sdl2_cxx/core.hxx>
#include <sdl2_cxx/events.hxx>
#include <sdl2_cxx/time.hxx>
#include <sdl2_cxx/video.hxx>

#include <SDL2/SDL_opengl.h>

static void AspectAdjust(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
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
  static GLubyte indices[36] = {0, 3, 4, 4, 5, 0, 0, 5, 6, 6, 1, 0, 6, 7, 2, 2, 1, 6, 7, 4, 3, 3, 2, 7, 5, 4, 7, 7, 6, 5, 2, 3, 1, 3, 0, 1};

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
  sdl2::init_guard sdl2_guard{sdl2::init_flags::everything};

  constexpr int screen_width = 640;
  constexpr int screen_height = 480;

  sdl2::gl::set_attribute(sdl2::gl::attribute::buffer_size, 16);
  sdl2::gl::set_attribute(sdl2::gl::attribute::context_major_version, 1);

  sdl2::window window{"GLES example",
                      sdl2::windowpos::centered,
                      sdl2::windowpos::centered,
                      screen_width,
                      screen_height,
                      sdl2::window_flags::opengl | sdl2::window_flags::shown};

  // Create our opengl context and attach it to our window
  auto context = sdl2::gl::context(window);
  sdl2::gl::make_current(window, context);

  sdl2::gl::set_swap_interval(sdl2::gl::swap_interval::synchronized);

  sdl2::log::out() << sdl2::log::priority::information << "Vendor     : " << glGetString(GL_VENDOR);
  sdl2::log::out() << sdl2::log::priority::information << "Renderer   : " << glGetString(GL_RENDERER);
  sdl2::log::out() << sdl2::log::priority::information << "Version    : " << glGetString(GL_VERSION);
  sdl2::log::out() << sdl2::log::priority::information << "Extensions : " << glGetString(GL_EXTENSIONS);

  AspectAdjust(screen_width, screen_height);

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
    sdl2::gl::swap_window(window);
  }

  auto now = sdl2::ticks();
  if (now > then)
  {
    sdl2::log::out() << sdl2::log::priority::information << ((double)frames * 1000) / (now - then) << " frames per second\n";
  }

  return 0;
}