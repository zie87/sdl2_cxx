/**
* @file   log.hxx
* @Author: zie87
* @Date:   2017-10-15 01:35:18
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-15 02:33:33
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_CORE_LOG_HXX
#define SDL2_CXX_CORE_LOG_HXX

#include <SDL_log.h>

#include <sstream>
#include <sdl2_cxx/detail/bitmask.hxx>

namespace sdl2
{
    struct log final 
    {
        enum class category : int 
        {
            application = SDL_LOG_CATEGORY_APPLICATION,
            error = SDL_LOG_CATEGORY_ERROR,
            assert = SDL_LOG_CATEGORY_ASSERT,
            system = SDL_LOG_CATEGORY_SYSTEM,
            audio = SDL_LOG_CATEGORY_AUDIO,
            video = SDL_LOG_CATEGORY_VIDEO,
            render = SDL_LOG_CATEGORY_RENDER,
            input = SDL_LOG_CATEGORY_INPUT,
            test = SDL_LOG_CATEGORY_TEST,
            reserved1 = SDL_LOG_CATEGORY_RESERVED1,
            reserved2 = SDL_LOG_CATEGORY_RESERVED2,
            reserved3 = SDL_LOG_CATEGORY_RESERVED3,
            reserved4 = SDL_LOG_CATEGORY_RESERVED4,
            reserved5 = SDL_LOG_CATEGORY_RESERVED5,
            reserved6 = SDL_LOG_CATEGORY_RESERVED6,
            reserved7 = SDL_LOG_CATEGORY_RESERVED7,
            reserved8 = SDL_LOG_CATEGORY_RESERVED8,
            reserved9 = SDL_LOG_CATEGORY_RESERVED9,
            reserved10 = SDL_LOG_CATEGORY_RESERVED10,
            custom = SDL_LOG_CATEGORY_CUSTOM,
        };

        enum class priority : std::underlying_type_t<SDL_LogPriority> 
        {
            verbose = SDL_LOG_PRIORITY_VERBOSE,
            debug = SDL_LOG_PRIORITY_DEBUG,
            information = SDL_LOG_PRIORITY_INFO,
            warning = SDL_LOG_PRIORITY_WARN,
            error = SDL_LOG_PRIORITY_ERROR,
            critical = SDL_LOG_PRIORITY_CRITICAL,
            num = SDL_NUM_LOG_PRIORITIES
        };

        using callback = SDL_LogOutputFunction;

        static inline void set_priorities(priority priority) noexcept { SDL_LogSetAllPriority(static_cast<SDL_LogPriority>(priority)); }
        static inline void reset_priorities() noexcept { SDL_LogResetPriorities(); }

        static inline void category_priority(category category, priority priority) noexcept { SDL_LogSetPriority(underlying_cast(category), static_cast<SDL_LogPriority>(priority)); }
        static inline priority category_priority(category category) noexcept { return static_cast<priority>(SDL_LogGetPriority(underlying_cast(category)));}


        template <typename ...Args>
        static void printf(const char *fmt, Args &&...args) noexcept { SDL_Log(fmt, std::forward<Args>(args)...); }

        template <typename ...Args>
        static void verbose(category category, const char *fmt, Args &&...args) noexcept { SDL_LogVerbose(underlying_cast(category), fmt, std::forward<Args>(args)...); }

        template <typename ...Args>
        static void debug(category category, const char *fmt, Args &&...args) noexcept { SDL_LogDebug(underlying_cast(category), fmt, std::forward<Args>(args)...);}

        template <typename ...Args>
        static void information(category category, const char *fmt, Args &&...args) noexcept { SDL_LogInfo(underlying_cast(category), fmt, std::forward<Args>(args)...); }

        template <typename ...Args>
        static void warning(category category, const char *fmt, Args &&...args) noexcept { SDL_LogWarn(underlying_cast(category), fmt, std::forward<Args>(args)...); }

        template <typename ...Args>
        static void error(category category, const char *fmt, Args &&...args) noexcept { SDL_LogError(underlying_cast(category), fmt, std::forward<Args>(args)...); }

        template <typename ...Args>
        static void critical(category category, const char *fmt, Args &&...args) noexcept {SDL_LogCritical(underlying_cast(category), fmt, std::forward<Args>(args)...); }

        template <typename ...Args>
        static void message(category category, priority priority, const char *fmt, Args &&...args) noexcept { SDL_LogMessage(underlying_cast(category), static_cast<SDL_LogPriority>(priority), fmt, std::forward<Args>(args)...); }

        template <typename ...Args>
        static void message(category category, priority priority, const char *fmt, va_list ap) noexcept { SDL_LogMessageV(underlying_cast(category), static_cast<SDL_LogPriority>(priority), fmt, ap); }

        static void output(callback *pcallback, void **puserdata) noexcept { SDL_LogGetOutputFunction(pcallback, puserdata); }
        static void output(callback callback, void *userdata) noexcept { SDL_LogSetOutputFunction(callback, userdata); }
    

        private:
            struct logger final
            {
                public:
                    logger() = default;
                    logger(logger&&) = default;
                    logger(const logger&) = delete;

                    ~logger() { message( m_category, m_priority, "%s", m_message.c_str() ); }

                    logger& operator<<(category c) 
                    {
                        m_category = c;
                        return *this;
                    }

                    logger& operator<<(priority p) 
                    {
                        m_priority = p;
                        return *this;
                    }

                    template <typename T>
                    logger& operator<<(T&& entry)
                    {
                        std::ostringstream ss;
                        ss << std::forward<T>(entry);
                        m_message.append(ss.str());

                        return *this;
                    }

                private:
                    std::string m_message;
                    category m_category = category::application;
                    priority m_priority = priority::information;
            };

        public:
            static inline auto out() { return logger{}; }
    };
}

#endif