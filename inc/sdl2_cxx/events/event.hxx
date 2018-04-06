/**
 * @file   event.hxx
 * @Author: zie87
 * @Date:   2017-10-18 21:26:49
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-21 15:52:46
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#ifndef SDL2_CXX_EVENTS_EVENT_HXX
#define SDL2_CXX_EVENTS_EVENT_HXX

#include <SDL_events.h>

#include <sdl2_cxx/events/event_types.hxx>
#include <sdl2_cxx/events/keycode.hxx>
#include <sdl2_cxx/events/mouse.hxx>
#include <sdl2_cxx/events/scancode.hxx>

namespace sdl2
{
  namespace detail
  {
    template <typename T>
    class event_data_holder
    {
    public:
      explicit constexpr event_data_holder(const T& data) : m_data(data) {}
      explicit constexpr event_data_holder(const event_data_holder& rhs) = default;
      event_data_holder& operator=(const event_data_holder& rhs) = default;

      constexpr event_type type() const noexcept { return static_cast<event_type>(m_data.type); }
      constexpr const T& get() const noexcept { return m_data; }

    private:
      T m_data;
    };

    template <typename T, typename U = T>
    class basic_event_view : public event_data_holder<T>
    {
    };

    template <typename T>
    class basic_event_view<T, decltype(SDL_Event::common)> : public event_data_holder<T>
    {
    public:
      explicit constexpr basic_event_view(const SDL_Event& event) : event_data_holder<T>(event.common) {}
      constexpr auto timestamp() const { return event_data_holder<T>::get().timestamp; }
    };

    template <typename T>
    class basic_event_view<T, decltype(SDL_Event::window)> : public event_data_holder<T>
    {
    public:
      explicit constexpr basic_event_view(const SDL_Event& event) : event_data_holder<T>(event.window) {}

      enum class id : std::underlying_type_t<SDL_WindowEventID>
      {
        none = SDL_WINDOWEVENT_NONE,
        shown = SDL_WINDOWEVENT_SHOWN,
        hidden = SDL_WINDOWEVENT_HIDDEN,
        exposed = SDL_WINDOWEVENT_EXPOSED,

        moved = SDL_WINDOWEVENT_MOVED,

        resized = SDL_WINDOWEVENT_RESIZED,
        changed = SDL_WINDOWEVENT_SIZE_CHANGED,

        minimized = SDL_WINDOWEVENT_MINIMIZED,
        maximized = SDL_WINDOWEVENT_MAXIMIZED,
        restored = SDL_WINDOWEVENT_RESTORED,

        enter = SDL_WINDOWEVENT_ENTER,
        leave = SDL_WINDOWEVENT_LEAVE,
        focus_gained = SDL_WINDOWEVENT_FOCUS_GAINED,
        focus_lost = SDL_WINDOWEVENT_FOCUS_LOST,
        close = SDL_WINDOWEVENT_CLOSE,
        take_focus = SDL_WINDOWEVENT_TAKE_FOCUS,
        hit_test = SDL_WINDOWEVENT_HIT_TEST
      };

      constexpr auto timestamp() const { return event_data_holder<T>::get().timestamp; }

      constexpr auto windowID() const { return event_data_holder<T>::get().windowID; }

      constexpr id event_id() const { return static_cast<id>(event_data_holder<T>::get().event); }

      constexpr auto data1() const { return event_data_holder<T>::get().data1; }
      constexpr auto data2() const { return event_data_holder<T>::get().data2; }

      constexpr auto moved_x() const { return data1(); }
      constexpr auto moved_y() const { return data2(); }

      constexpr auto resized_w() const { return data1(); }
      constexpr auto resized_h() const { return data2(); }

      constexpr auto changed_w() const { return data1(); }
      constexpr auto changed_h() const { return data2(); }
    };

    template <typename T>
    class basic_event_view<T, decltype(SDL_Event::key)> : public event_data_holder<T>
    {
    public:
      explicit constexpr basic_event_view(const SDL_Event& event) : event_data_holder<T>(event.key) {}

      constexpr auto timestamp() const { return event_data_holder<T>::get().timestamp; }

      constexpr auto windowID() const { return event_data_holder<T>::get().windowID; }
      constexpr button_state state() const { return static_cast<button_state>(event_data_holder<T>::get().state); }
      constexpr auto repeat() const { return event_data_holder<T>::get().repeat; }

      constexpr auto keysym() const { return event_data_holder<T>::get().keysym; }

      constexpr scancode code() const { return static_cast<scancode>(keysym().scancode); }
      constexpr keycode sym() const { return static_cast<keycode>(keysym().sym); }
      constexpr auto mod() const { return keysym().mod; }
    };

    template <typename T>
    class basic_event_view<T, decltype(SDL_Event::edit)> : public event_data_holder<T>
    {
    public:
      using event_data_holder<T>::event_data_holder;
      using event_data_holder<T>::operator=;

      static constexpr std::size_t text_size = SDL_TEXTEDITINGEVENT_TEXT_SIZE;

      explicit constexpr basic_event_view(const SDL_Event& event) : event_data_holder<T>(event.edit) {}

      constexpr auto timestamp() const { return event_data_holder<T>::get().timestamp; }
      constexpr auto windowID() const { return event_data_holder<T>::get().windowID; }
      std::string text() const { return event_data_holder<T>::get().text; }
      constexpr auto start() const { return event_data_holder<T>::get().start; }
      constexpr auto length() const { return event_data_holder<T>::get().length; }
    };

    template <typename T>
    class basic_event_view<T, decltype(SDL_Event::text)> : public event_data_holder<T>
    {
    public:
      using event_data_holder<T>::event_data_holder;
      using event_data_holder<T>::operator=;

      static constexpr std::size_t text_size = SDL_TEXTINPUTEVENT_TEXT_SIZE;
      explicit constexpr basic_event_view(const SDL_Event& event) : event_data_holder<T>(event.text) {}

      constexpr auto timestamp() const { return event_data_holder<T>::get().timestamp; }
      constexpr auto windowID() const { return event_data_holder<T>::get().windowID; }
      std::string text() const { return event_data_holder<T>::get().text; }
    };

    template <typename T>
    class basic_event_view<T, decltype(SDL_Event::motion)> : public event_data_holder<T>
    {
    public:
      using event_data_holder<T>::event_data_holder;
      using event_data_holder<T>::operator=;

      explicit constexpr basic_event_view(const SDL_Event& event) : event_data_holder<T>(event.motion) {}

      constexpr auto timestamp() const { return event_data_holder<T>::get().timestamp; }
      constexpr auto windowID() const { return event_data_holder<T>::get().windowID; }
      constexpr auto which() const { return event_data_holder<T>::get().which; }
      constexpr auto state() const { return event_data_holder<T>::get().state; }
      constexpr auto x() const { return event_data_holder<T>::get().x; }
      constexpr auto y() const { return event_data_holder<T>::get().y; }
      constexpr auto xrel() const { return event_data_holder<T>::get().xrel; }
      constexpr auto yrel() const { return event_data_holder<T>::get().yrel; }
    };

    template <typename T>
    class basic_event_view<T, decltype(SDL_Event::button)> : public event_data_holder<T>
    {
    public:
      using event_data_holder<T>::event_data_holder;
      using event_data_holder<T>::operator=;

      explicit constexpr basic_event_view(const SDL_Event& event) : event_data_holder<T>(event.button) {}

      constexpr auto timestamp() const { return event_data_holder<T>::get().timestamp; }
      constexpr auto windowID() const { return event_data_holder<T>::get().windowID; }
      constexpr auto which() const { return event_data_holder<T>::get().which; }
      constexpr button_state state() const { return static_cast<button_state>(event_data_holder<T>::get().state); }
      constexpr auto x() const { return event_data_holder<T>::get().x; }
      constexpr auto y() const { return event_data_holder<T>::get().y; }
      constexpr auto clicks() const { return event_data_holder<T>::get().clicks; }
      constexpr mouse::button button() const { return static_cast<mouse::button>(event_data_holder<T>::get().button); }
    };

    template <typename T>
    class basic_event_view<T, decltype(SDL_Event::wheel)> : public event_data_holder<T>
    {
    public:
      using event_data_holder<T>::event_data_holder;
      using event_data_holder<T>::operator=;

      enum class direction : uint32_t
      {
        normal = SDL_MOUSEWHEEL_NORMAL,
        flipped = SDL_MOUSEWHEEL_FLIPPED
      };

      explicit constexpr basic_event_view(const SDL_Event& event) : event_data_holder<T>(event.wheel) {}

      constexpr auto timestamp() const { return event_data_holder<T>::get().timestamp; }
      constexpr auto windowID() const { return event_data_holder<T>::get().windowID; }
      constexpr auto which() const { return event_data_holder<T>::get().which; }
      constexpr auto x() const { return event_data_holder<T>::get().x; }
      constexpr auto y() const { return event_data_holder<T>::get().y; }

      constexpr auto get_direction() const { return static_cast<direction>(event_data_holder<T>::get().direction); }
    };

  } // namespace detail

  template <event_type T = event_type::first>
  using event_view = detail::basic_event_view<event_data<T>>;

  using common_event = detail::basic_event_view<decltype(SDL_Event::common)>;
  using window_event = detail::basic_event_view<decltype(SDL_Event::window)>;
  using key_event = detail::basic_event_view<decltype(SDL_Event::key)>;
  using text_editing_event = detail::basic_event_view<decltype(SDL_Event::edit)>;
  using text_event = detail::basic_event_view<decltype(SDL_Event::text)>;
  using motion_event = detail::basic_event_view<decltype(SDL_Event::motion)>;
  using button_event = detail::basic_event_view<decltype(SDL_Event::button)>;
  using wheel_event = detail::basic_event_view<decltype(SDL_Event::wheel)>;

  template <typename T = std::nullptr_t>
  struct basic_event_traits
  {
    using this_event = T;

    static constexpr const this_event& get(const this_event& t) { return t; }
    static constexpr event_type type(const SDL_Event& t) { return static_cast<event_type>(t.type); }
  };

  struct event_traits : basic_event_traits<>
  {
  };

  struct common_event_traits : basic_event_traits<SDL_CommonEvent>
  {
    static constexpr const this_event& get(const SDL_Event& t) { return t.common; }
    static constexpr auto timestamp(const SDL_Event& t) { return get(t).timestamp; }
  };

  template <typename = SDL_WindowEvent>
  struct window_event_traits;

  template <>
  struct window_event_traits<SDL_WindowEvent> : basic_event_traits<SDL_WindowEvent>
  {
    enum class id : std::underlying_type_t<SDL_WindowEventID>
    {
      none = SDL_WINDOWEVENT_NONE,
      shown = SDL_WINDOWEVENT_SHOWN,
      hidden = SDL_WINDOWEVENT_HIDDEN,
      exposed = SDL_WINDOWEVENT_EXPOSED,

      moved = SDL_WINDOWEVENT_MOVED,

      resized = SDL_WINDOWEVENT_RESIZED,
      changed = SDL_WINDOWEVENT_SIZE_CHANGED,

      minimized = SDL_WINDOWEVENT_MINIMIZED,
      maximized = SDL_WINDOWEVENT_MAXIMIZED,
      restored = SDL_WINDOWEVENT_RESTORED,

      enter = SDL_WINDOWEVENT_ENTER,
      leave = SDL_WINDOWEVENT_LEAVE,
      focus_gained = SDL_WINDOWEVENT_FOCUS_GAINED,
      focus_lost = SDL_WINDOWEVENT_FOCUS_LOST,
      close = SDL_WINDOWEVENT_CLOSE,
      take_focus = SDL_WINDOWEVENT_TAKE_FOCUS,
      hit_test = SDL_WINDOWEVENT_HIT_TEST
    };

    static constexpr const this_event& get(const SDL_Event& t) { return t.window; }

    static constexpr auto timestamp(const SDL_Event& t) { return get(t).timestamp; }
    static constexpr auto windowID(const SDL_Event& t) { return get(t).windowID; }
    static constexpr id event_id(const SDL_Event& t) { return static_cast<id>(get(t).event); }
    static constexpr auto data1(const SDL_Event& t) { return get(t).data1; }
    static constexpr auto data2(const SDL_Event& t) { return get(t).data2; }
    static constexpr auto moved_x(const SDL_Event& t) { return data1(t); }
    static constexpr auto moved_y(const SDL_Event& t) { return data2(t); }
    static constexpr auto resized_w(const SDL_Event& t) { return data1(t); }
    static constexpr auto resized_h(const SDL_Event& t) { return data2(t); }
    static constexpr auto changed_w(const SDL_Event& t) { return data1(t); }
    static constexpr auto changed_h(const SDL_Event& t) { return data2(t); }
  };

} // namespace sdl2

#endif