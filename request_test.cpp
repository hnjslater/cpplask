#include <gtest/gtest.h>
#include <request.hpp>
#include <functional>

using namespace cpplask;

TEST(Request, NoHeaders) {
    request r("GET", "", std::vector<std::pair<std::string, std::string>>());

    auto result = r.headers(std::string("host"));
    EXPECT_TRUE(result.empty());
}

TEST(Request, SingleHeader) {
    std::vector<std::pair<std::string, std::string>> headers { { "haaa", "vaaa" } };
    request r("GET", "", headers);

    auto result = r.headers(std::string("haaa"));
    EXPECT_EQ(1, std::distance(result.begin(), result.end()));
    EXPECT_EQ("vaaa", *result.begin());
}

TEST(Request, LotsOfHeaders) {
    std::vector<std::pair<std::string, std::string>> headers {
        { "haaa", "vaaa" },
        { "hbbb", "vbbb" },
        { "hccc", "vccc" },
        { "hddd", "vddd" },
    };
    request r("GET", "", headers);

    auto result = r.headers(std::string("haaa"));
    EXPECT_EQ(1, std::distance(result.begin(), result.end()));
    EXPECT_EQ("vaaa", *result.begin());
}

TEST(Request, LotsOfValues) {
    std::vector<std::pair<std::string, std::string>> headers {
        { "haaa", "vaaa1" },
        { "haaa", "vaaa2" },
        { "hbbb", "vbbb1" },
        { "hbbb", "vbbb2" },
        { "hccc", "vccc1" },
        { "hddd", "vddd1" },
    };
    request r("GET", "", headers);

    auto result = r.headers(std::string("hbbb"));
    EXPECT_EQ(2, std::distance(result.begin(), result.end()));
    EXPECT_EQ("vbbb1", *result.begin());
    EXPECT_EQ("vbbb2", *(result.begin()+1));
}
