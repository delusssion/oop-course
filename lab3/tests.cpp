#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <utility>
#include "date_set.h"

TEST(DateTest, Validation) {
    EXPECT_TRUE(Date(29, 2, 2024).is_valid());
    EXPECT_FALSE(Date(29, 2, 2023).is_valid());
    EXPECT_FALSE(Date(29, 2, 1900).is_valid());
    EXPECT_TRUE(Date(29, 2, 2000).is_valid());
    EXPECT_FALSE(Date(31, 4, 2024).is_valid());
    EXPECT_FALSE(Date(1, 13, 2024).is_valid());
    EXPECT_FALSE(Date(0, 1, 2024).is_valid());
}

TEST(DateTest, CompareAndPrint) {
    EXPECT_TRUE(Date(31, 12, 2023) < Date(1, 1, 2024));
    EXPECT_TRUE(Date(1, 2, 2024) < Date(2, 2, 2024));
    EXPECT_FALSE(Date(1, 1, 2024) < Date(1, 1, 2024));
    EXPECT_TRUE(Date(5, 6, 2024) == Date(5, 6, 2024));
    std::ostringstream out;
    out << Date(5, 6, 2024);
    EXPECT_EQ(out.str(), "05.06.2024");
}

TEST(DateSetTest, EmptySet) {
    DateSet s;
    EXPECT_EQ(s.size(), 0u);
    EXPECT_TRUE(s.empty());
    EXPECT_FALSE(s.contains(Date(1, 1, 2024)));
}

TEST(DateSetTest, AddNewAndDuplicate) {
    DateSet s;
    EXPECT_TRUE(s.add(Date(1, 1, 2024)));
    EXPECT_FALSE(s.add(Date(1, 1, 2024)));
    EXPECT_EQ(s.size(), 1u);
}

TEST(DateSetTest, AddInvalidDate) {
    DateSet s;
    EXPECT_FALSE(s.add(Date(30, 2, 2024)));
    EXPECT_TRUE(s.empty());
}

TEST(DateSetTest, KeepsSortedOrder) {
    DateSet s;
    s += Date(3, 3, 2024);
    s += Date(1, 1, 2024);
    s += Date(2, 2, 2023);
    ASSERT_EQ(s.size(), 3u);
    EXPECT_EQ(s[0], Date(2, 2, 2023));
    EXPECT_EQ(s[1], Date(1, 1, 2024));
    EXPECT_EQ(s[2], Date(3, 3, 2024));
    EXPECT_THROW(s[3], std::out_of_range);
}

TEST(DateSetTest, Remove) {
    DateSet s;
    s += Date(1, 1, 2024);
    s += Date(2, 1, 2024);
    EXPECT_TRUE(s.remove(Date(1, 1, 2024)));
    EXPECT_FALSE(s.remove(Date(1, 1, 2024)));
    EXPECT_FALSE(s.remove(Date(5, 5, 2020)));
    EXPECT_EQ(s.size(), 1u);
    EXPECT_TRUE(s.remove(Date(2, 1, 2024)));
    EXPECT_TRUE(s.empty());
}

TEST(DateSetTest, ContainsAndCallOperatorAgree) {
    DateSet s;
    s += Date(10, 10, 2010);
    EXPECT_TRUE(s.contains(Date(10, 10, 2010)));
    EXPECT_TRUE(s(Date(10, 10, 2010)));
    EXPECT_FALSE(s.contains(Date(11, 10, 2010)));
    EXPECT_FALSE(s(Date(11, 10, 2010)));
}

TEST(DateSetTest, CopyIsIndependent) {
    DateSet a;
    a += Date(1, 1, 2024);
    DateSet b(a);
    b += Date(2, 2, 2024);
    EXPECT_EQ(a.size(), 1u);
    EXPECT_EQ(b.size(), 2u);

    DateSet c;
    c = a;
    c -= Date(1, 1, 2024);
    EXPECT_TRUE(a.contains(Date(1, 1, 2024)));
}

TEST(DateSetTest, SelfAssignment) {
    DateSet a;
    a += Date(1, 1, 2024);
    DateSet& ref = a;
    a = ref;
    EXPECT_EQ(a.size(), 1u);
    a = std::move(ref);
    EXPECT_EQ(a.size(), 1u);
}

TEST(DateSetTest, MoveLeavesSourceEmpty) {
    DateSet a;
    a += Date(1, 1, 2024);
    DateSet b(std::move(a));
    EXPECT_EQ(b.size(), 1u);
    EXPECT_EQ(a.size(), 0u);
    EXPECT_FALSE(a.contains(Date(1, 1, 2024)));

    DateSet c;
    c = std::move(b);
    EXPECT_EQ(c.size(), 1u);
    EXPECT_TRUE(b.empty());
    b += Date(5, 5, 2005);
    EXPECT_EQ(b.size(), 1u);
}

TEST(DateSetTest, SetOperations) {
    DateSet a;
    a += Date(1, 1, 2024);
    a += Date(2, 1, 2024);
    a += Date(3, 1, 2024);
    DateSet b;
    b += Date(2, 1, 2024);
    b += Date(3, 1, 2024);
    b += Date(4, 1, 2024);

    DateSet u = a | b;
    DateSet i = a & b;
    DateSet d = a - b;

    EXPECT_EQ(u.size(), 4u);
    EXPECT_EQ(i.size(), 2u);
    EXPECT_TRUE(i.contains(Date(2, 1, 2024)));
    EXPECT_TRUE(i.contains(Date(3, 1, 2024)));
    ASSERT_EQ(d.size(), 1u);
    EXPECT_EQ(d[0], Date(1, 1, 2024));
    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(b.size(), 3u);
}

TEST(DateSetTest, OperationsWithEmpty) {
    DateSet a;
    a += Date(1, 1, 2024);
    DateSet empty;
    EXPECT_TRUE((a | empty) == a);
    EXPECT_TRUE((a & empty).empty());
    EXPECT_TRUE((a - empty) == a);
    EXPECT_TRUE((empty - a).empty());
}

TEST(DateSetTest, EqualityIgnoresInsertOrder) {
    DateSet a;
    a += Date(1, 1, 2024);
    a += Date(5, 5, 2024);
    DateSet b;
    b += Date(5, 5, 2024);
    b += Date(1, 1, 2024);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    b += Date(6, 6, 2024);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(DateSetTest, OutputFormat) {
    DateSet s;
    std::ostringstream empty_out;
    empty_out << s;
    EXPECT_EQ(empty_out.str(), "{ }");

    s += Date(15, 3, 2024);
    s += Date(1, 1, 2024);
    std::ostringstream out;
    out << s;
    EXPECT_EQ(out.str(), "{ 01.01.2024, 15.03.2024 }");
}

TEST(DateSetTest, ChainedOperators) {
    DateSet s;
    s += Date(1, 1, 2024);
    (s += Date(2, 1, 2024)) += Date(3, 1, 2024);
    (s -= Date(1, 1, 2024)) -= Date(2, 1, 2024);
    EXPECT_EQ(s.size(), 1u);
}

TEST(DateSetTest, Stress) {
    DateSet s;
    std::size_t added = 0;
    for (int year = 2000; added < 1000; year++) {
        for (int month = 1; month <= 12 && added < 1000; month++) {
            for (int day = 1; day <= 28 && added < 1000; day++) {
                EXPECT_TRUE(s.add(Date(day, month, year)));
                added++;
            }
        }
    }
    EXPECT_EQ(s.size(), 1000u);
    EXPECT_FALSE(s.add(Date(1, 1, 2000)));
    EXPECT_EQ(s.size(), 1000u);
    for (std::size_t i = 0; i + 1 < s.size(); i++) {
        EXPECT_TRUE(s[i] < s[i + 1]);
    }
}
