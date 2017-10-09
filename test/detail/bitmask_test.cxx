/**
* @file   bitmask_test.cxx
* @Author: zie87
* @Date:   2017-10-09 20:21:14
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-09 22:05:58
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/


#include <sdl2_cxx/detail/bitmask.hxx>

#include <catch.hpp>

enum class enum_test_a : unsigned char
{
    zero    =0b00000000,
    one     =0b00000001,
    two     =0b00000010,
    three   =0b00000011
};

namespace sdl2
{
    template<>
    struct enable_bitmask_operators<enum_test_a>{ static const bool enable=true; };
}


TEST_CASE( "bitmask combination", "[detail]" ) 
{
    using namespace sdl2;

    enum_test_a a1 = enum_test_a::one | enum_test_a::two;
    REQUIRE( a1 == enum_test_a::three );

    a1 = enum_test_a::one;
    a1 |= enum_test_a::two;
    REQUIRE( a1 == enum_test_a::three );

    enum_test_a a2 = enum_test_a::one & enum_test_a::two;
    REQUIRE( a2 == enum_test_a::zero);

    a2 = enum_test_a::one;
    a2 &= enum_test_a::three;
    REQUIRE( a2 == enum_test_a::one );

    enum_test_a a3 = enum_test_a::one ^ enum_test_a::three;
    REQUIRE( a3 == enum_test_a::two );

    a3 = enum_test_a::one;
    a3 ^= enum_test_a::three;
    REQUIRE( a3 == enum_test_a::two );

    auto a4 = static_cast<unsigned short>( ~a2 );
    REQUIRE( a4 == 254 );
}
