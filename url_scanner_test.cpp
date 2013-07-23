#include <gtest/gtest.h>
#include <url_scanner.hpp>
#include <functional>


TEST(UrlScanner, StaticMatch) {
    std::function<void()> func = []() {  };
    bool result = url_scan<>("/lightly-hopped", "/lightly-hopped", func);
    EXPECT_EQ(result, true);
}

TEST(UrlScanner, StaticNoMatch) {
    std::function<void()> func = []() {  };
    bool result = url_scan<>("hops", "barley", func);
    EXPECT_EQ(result, false);
}

TEST(UrlScanner, StaticNoMatchPatternTooLong) {
    std::function<void()> func = []() {  };
    bool result = url_scan<>("/malted-barley", "/malted", func);
    EXPECT_EQ(result, false);
}

TEST(UrlScanner, StaticNoMatchPathTooLong) {
    std::function<void()> func = []() {  };
    bool result = url_scan<>("/malted", "/malted-barley", func);
    EXPECT_EQ(result, false);
}

TEST(UrlScanner, OneNumber) {
    int value;
    std::function<void(int)> func = [&](int a) { value = a; };
    bool result = url_scan<int>("%", "1", func);
    EXPECT_EQ(result, true);
    EXPECT_EQ(value, 1);
}

TEST(UrlScanner, OneNumberNoMatch) {
    int value = -1;
    std::function<void(int)> func = [&](int a) { value = a; };
    bool result = url_scan<int>("/page/%", "/page/f", func);
    EXPECT_EQ(result, false);
    EXPECT_EQ(value, -1);
}
TEST(UrlScanner, ThreeNumber) {
    int va, vb, vc;
    std::function<void(int,int,int)> func = [&](int a, int b, int c) { va = a; vb = b, vc = c; };
    bool result = url_scan<int,int,int>("/%/%/%", "/1/2/3", func);
    EXPECT_EQ(result, true);
    EXPECT_EQ(va, 1);
    EXPECT_EQ(vb, 2);
    EXPECT_EQ(vc, 3);
}


TEST(UrlScanner, NoMatchAfterLastPercentSymbol) {
    int va = -1;
    int vb = -1;
    std::function<void(int,int)> func = [&](int a, int b) { va = a; vb = b; };
    bool result = url_scan<int,int>("/pages/%/data/%/info", "/pages/3/data/45/question", func);
    EXPECT_EQ(result, false);
    EXPECT_EQ(va, -1);
    EXPECT_EQ(vb, -1);
}
