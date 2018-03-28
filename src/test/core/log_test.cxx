/**
* @file   log_test.cxx
* @Author: zie87
* @Date:   2017-10-15 01:57:14
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-21 09:39:43
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#include <sdl2_cxx/core/log.hxx>

#include <catch.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace 
{

struct log_entry 
{
  int category;
  SDL_LogPriority priority;
  std::string message;
};

inline bool operator==(const log_entry& lhs, const log_entry& rhs) 
{
  return std::tie(lhs.category, lhs.priority, lhs.message) ==
         std::tie(rhs.category, rhs.priority, rhs.message);
}

void test_log_func(void* user_data, int category, SDL_LogPriority priority, const char* message) 
{
  auto* vec = static_cast<std::vector<log_entry>*>(user_data);
  vec->push_back(log_entry{category, priority, message});
}

// Test class with an overloaded operator<<
struct test_class { std::string msg; };
std::ostream& operator<<(std::ostream& os, const test_class& t) { return os << t.msg; }

}

TEST_CASE("test log priority per category", "[core]") 
{
  sdl2::log::category_priority(sdl2::log::category::custom,  sdl2::log::priority::verbose);
  REQUIRE(SDL_LogGetPriority(SDL_LOG_CATEGORY_CUSTOM) == SDL_LOG_PRIORITY_VERBOSE);

  SDL_LogResetPriorities();

  SDL_LogSetPriority(SDL_LOG_CATEGORY_CUSTOM, SDL_LOG_PRIORITY_WARN);
  REQUIRE(sdl2::log::category_priority(sdl2::log::category::custom) == sdl2::log::priority::warning);

  SDL_LogResetPriorities();
}

TEST_CASE("test basic logging function", "[core]") 
{
  std::vector<log_entry> internal_log;

  SDL_LogOutputFunction old_func = nullptr;
  void* old_user_data = nullptr;
  SDL_LogGetOutputFunction(&old_func, &old_user_data);
  SDL_LogSetOutputFunction(test_log_func, &internal_log);

  SECTION("SDL_Log() is wrapped correctly") 
  {
    sdl2::log::printf("%s %d", "test", 1);
    REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "test 1"}));
  }

  SECTION("SDL_LogVerbose() is wrapped correctly") 
  {
    sdl2::log::verbose(sdl2::log::category::test, "%s %d", "test", 2);
    REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST, SDL_LOG_PRIORITY_VERBOSE,"test 2"}));
  }

  SECTION("SDL_LogDebug() is wrapped correctly") 
  {
    sdl2::log::debug(sdl2::log::category::test, "%s %d", "test", 3);
    REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST, SDL_LOG_PRIORITY_DEBUG, "test 3"}));
  }

  SECTION("SDL_LogInfo() is wrapped correctly") 
  {
    sdl2::log::info(sdl2::log::category::test, "%s %d", "test", 4);
    REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST, SDL_LOG_PRIORITY_INFO, "test 4"}));
  }

  SECTION("SDL_LogWarn() is wrapped correctly") 
  {
    sdl2::log::warn(sdl2::log::category::test, "%s %d", "test", 5);
    REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST, SDL_LOG_PRIORITY_WARN, "test 5"}));
   }

  SECTION("SDL_LogError() is wrapped correctly") 
  {
    sdl2::log::error(sdl2::log::category::test, "%s %d", "test", 6);
    REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST, SDL_LOG_PRIORITY_ERROR, "test 6"}));
  }

  SECTION("SDL_LogCritical() is wrapped correctly") 
  {
    sdl2::log::critical(sdl2::log::category::test, "%s %d", "test", 7);
    REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST, SDL_LOG_PRIORITY_CRITICAL, "test 7"}));
  }

  SECTION("SDL_LogMessage() is wrapped correctly") 
  {
    sdl2::log::message(sdl2::log::category::test, sdl2::log::priority::critical, "%s %d", "test", 8);
    REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST, SDL_LOG_PRIORITY_CRITICAL, "test 8"}));
  }

  SDL_LogSetOutputFunction(old_func, old_user_data);
}

TEST_CASE("test operator<<() for logging", "[core]") 
{
    std::vector<log_entry> internal_log;

    SDL_LogOutputFunction old_func = nullptr;
    void* old_user_data = nullptr;
    SDL_LogGetOutputFunction(&old_func, &old_user_data);
    SDL_LogSetOutputFunction(test_log_func, &internal_log);

    SECTION("Logger can be created") 
    {
        sdl2::log::out() << "test " << 1;
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "test 1"}));
    }

    SECTION("Logger can use custom classes") 
    {
        sdl2::log::out() << test_class{"test 2"};
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,"test 2"}));
    }

    SECTION("Logger can use custom categories") 
    {
        sdl2::log::out() << "test 3" << sdl2::log::category::test;
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST, SDL_LOG_PRIORITY_INFO,"test 3"}));
    }

    SECTION("Logger can use custom priorities") 
    {
        sdl2::log::out() << sdl2::log::priority::critical << "test " << 4;
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "test 4"}));
    }

    SDL_LogSetOutputFunction(old_func, old_user_data);
}



// TEST_CASE("Custom log functions work correctly", "[log]") {

//     std::vector<log_entry> test_log;

//     auto handle = sdl2::log::set_output_function(
//         [&test_log](int cat, sdl2::log::priority prio, const char* msg) {
//             // std::cout << msg << std::endl;
//             test_log.push_back(
//                 log_entry{cat, static_cast<SDL_LogPriority>(prio), msg});
//         });

//     sdl::log() << test_class{"test 1"};
//     REQUIRE((test_log.back() == log_entry{SDL_LOG_CATEGORY_APPLICATION,
//                                           SDL_LOG_PRIORITY_INFO, "test 1"}));
// }
