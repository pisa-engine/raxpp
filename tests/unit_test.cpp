#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <iostream>

#include <raxpp.hpp>

raxpp::Radix_Tree<int> tree() {
    raxpp::Radix_Tree<int> rt;
    rt.insert("foo", 1);
    rt.insert("foobar", 2);
    rt.insert("footer", 3);
    return rt;
}

TEST_CASE("Empty tree", "[unit]")
{
    raxpp::Radix_Tree<int> rt;

    REQUIRE(rt.size() == 0);
    REQUIRE(rt.empty());

    //SECTION("insert")
    //{
    //    REQUIRE(rt.insert("a", 1));
    //    REQUIRE(rt.size() == 1);
    //    REQUIRE(rt.contains("a"));
    //    REQUIRE(rt.insert("b", 2));
    //    REQUIRE(rt.size() == 2);
    //    REQUIRE(rt.contains("b"));
    //    REQUIRE(rt.insert("c", 3));
    //    REQUIRE(rt.size() == 3);
    //    REQUIRE(rt.contains("c"));

    //    REQUIRE(rt.at("a") == 1);
    //    REQUIRE(rt.at("b") == 2);
    //    REQUIRE(rt.at("c") == 3);
    //}
}

// TODO
// TEST_CASE("Copy constructor and assignment", "[unit]")
//{
//    auto rt = tree();
//    auto rt2(rt);
//    REQUIRE(rt.size() == 3);
//    REQUIRE(rt.at("foo") == 1);
//    REQUIRE(rt2.size() == 3);
//    REQUIRE(rt2.at("foo") == 1);
//    raxpp::Radix_Tree<int> rt3;
//    rt3.insert("dog", 4);
//    rt3 = rt2;
//    REQUIRE(rt3.size() == 3);
//    REQUIRE(rt3.at("foo") == 1);
//    REQUIRE(rt2.size() == 3);
//    REQUIRE(rt2.at("foo") == 1);
//}

TEST_CASE("Move constructor and assignment", "[unit]")
{
    auto rt = tree();
    auto rt2(std::move(rt));
    REQUIRE(rt2.size() == 3);
    REQUIRE(rt2.at("foo") == 1);
    rt = std::move(rt2);
    REQUIRE(rt.size() == 3);
    REQUIRE(rt.at("foo") == 1);
}

TEST_CASE("Size", "[unit]")
{
    REQUIRE(tree().size() == 3);
    REQUIRE_FALSE(tree().empty());
}

//TEST_CASE("Lookup", "[unit]")
//{
//    GIVEN("a test tree")
//    {
//        raxpp::Radix_Tree<int> rt;
//        rt.insert("foo", 1);
//        rt.insert("foobar", 2);
//        rt.insert("footer", 3);
//
//        auto [key, value] = GENERATE(
//            table<std::string, int>({{"foo", 1}, {"foobar", 2}, {"footer", 3}}));
//        WHEN("Lookup " << key) { REQUIRE(rt.at(key) == value); }
//
//        REQUIRE_THROWS_AS(rt.at("football"), std::out_of_range);
//    }
//}
