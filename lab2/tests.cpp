#include <gtest/gtest.h>
#include <sstream>
#include <utility>
#include "my_string.h"

TEST(StringBasic, DefaultIsEmpty) {
    String s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
    EXPECT_EQ(s.capacity(), 1u);
    EXPECT_STREQ(s.c_str(), "");
}

TEST(StringBasic, FromCString) {
    String s("Hello");
    EXPECT_EQ(s.size(), 5u);
    EXPECT_STREQ(s.c_str(), "Hello");
    EXPECT_EQ(s[1], 'e');
}

TEST(StringBasic, CopyIsDeep) {
    String a("abc");
    String b(a);
    b[0] = 'x';
    EXPECT_STREQ(a.c_str(), "abc");
    EXPECT_STREQ(b.c_str(), "xbc");
}

TEST(StringBasic, MoveLeavesSourceEmpty) {
    String a("Hello");
    String b(std::move(a));
    EXPECT_STREQ(b.c_str(), "Hello");
    EXPECT_EQ(a.size(), 0u);
    EXPECT_STREQ(a.c_str(), "");
    a.append("ok");
    EXPECT_STREQ(a.c_str(), "ok");
}

TEST(StringBasic, CopyAssignment) {
    String a("first");
    String b("second");
    a = b;
    EXPECT_STREQ(a.c_str(), "second");
    b[0] = 'S';
    EXPECT_STREQ(a.c_str(), "second");
}

TEST(StringBasic, MoveAssignment) {
    String a("first");
    String b("second");
    a = std::move(b);
    EXPECT_STREQ(a.c_str(), "second");
    EXPECT_TRUE(b.empty());
}

TEST(StringBasic, SelfAssignment) {
    String a("same");
    String& ref = a;
    a = ref;
    EXPECT_STREQ(a.c_str(), "same");
}

TEST(StringBasic, PushBackDoublesCapacity) {
    String s;
    s.push_back('a');
    EXPECT_EQ(s.capacity(), 1u);
    s.push_back('b');
    EXPECT_EQ(s.capacity(), 2u);
    s.push_back('c');
    EXPECT_EQ(s.capacity(), 4u);
    EXPECT_STREQ(s.c_str(), "abc");
}

TEST(StringBasic, AppendAndFind) {
    String s("Hello");
    s.append(", World!");
    EXPECT_STREQ(s.c_str(), "Hello, World!");
    EXPECT_EQ(s.find("World"), 7u);
    EXPECT_EQ(s.find("xyz"), String::npos);
}

TEST(StringBasic, AppendEmptyAndSelf) {
    String s("ab");
    String empty;
    s.append(empty);
    EXPECT_STREQ(s.c_str(), "ab");
    s.append(s);
    EXPECT_STREQ(s.c_str(), "abab");
}

TEST(StringBasic, PrintToStream) {
    String s("text");
    std::ostringstream out;
    s.print(out);
    out << " " << s;
    EXPECT_EQ(out.str(), "text text");
}

TEST(Rle, CompressExample) {
    String s("AAABCC");
    String packed = s.rle_compress();
    EXPECT_STREQ(packed.c_str(), "A3B1C2");
    EXPECT_STREQ(s.c_str(), "AAABCC");
}

TEST(Rle, DecompressExample) {
    String packed("A3B1C2");
    packed.rle_decompress();
    EXPECT_STREQ(packed.c_str(), "AAABCC");
}

TEST(Rle, RoundTrip) {
    String s("aaaaabbbcddddddddddddx");
    String packed = s.rle_compress();
    EXPECT_STREQ(packed.c_str(), "a5b3c1d12x1");
    packed.rle_decompress();
    EXPECT_TRUE(packed == s);
}

TEST(Rle, EmptyAndSingle) {
    String empty;
    String packed = empty.rle_compress();
    EXPECT_TRUE(packed.empty());
    packed.rle_decompress();
    EXPECT_TRUE(packed.empty());

    String one("z");
    EXPECT_STREQ(one.rle_compress().c_str(), "z1");
}

TEST(Rle, DecompressWithoutCount) {
    String s("AB2");
    s.rle_decompress();
    EXPECT_STREQ(s.c_str(), "ABB");
}
