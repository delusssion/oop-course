#include <gtest/gtest.h>
#include "array_ops.h"

TEST(ArrayOps, CreateAndDelete) {
    int* arr = array_create(5);
    ASSERT_NE(arr, nullptr);
    for (std::size_t i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], 0);
    }
    array_delete(arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayOps, CreateEmpty) {
    int* arr = array_create(0);
    EXPECT_EQ(arr, nullptr);
    array_delete(arr);
}

TEST(ArrayOps, InsertMiddle) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr = array_insert(arr, size, 1, 10);
    ASSERT_EQ(size, 4u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[2], 2);
    EXPECT_EQ(arr[3], 3);
    array_delete(arr);
}

TEST(ArrayOps, InsertIntoEmpty) {
    std::size_t size = 0;
    int* arr = nullptr;
    arr = array_insert(arr, size, 0, 7);
    ASSERT_EQ(size, 1u);
    EXPECT_EQ(arr[0], 7);
    array_delete(arr);
}

TEST(ArrayOps, Remove) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr = array_remove(arr, size, 0);
    ASSERT_EQ(size, 2u);
    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 3);
    arr = array_remove(arr, size, 5);
    EXPECT_EQ(size, 2u);
    array_delete(arr);
}

TEST(ArrayOps, Resize) {
    std::size_t size = 2;
    int* arr = array_create(size);
    arr[0] = 4;
    arr[1] = 5;
    arr = array_resize(arr, size, 4);
    size = 4;
    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr[1], 5);
    EXPECT_EQ(arr[2], 0);
    arr = array_resize(arr, size, 1);
    size = 1;
    EXPECT_EQ(arr[0], 4);
    array_delete(arr);
}

TEST(GnomeSort, SortsArray) {
    int arr[] = {2, 5, 2, 8, 2, 1};
    array_gnome_sort(arr, 6);
    int expected[] = {1, 2, 2, 2, 5, 8};
    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(GnomeSort, EmptyAndOne) {
    array_gnome_sort(nullptr, 0);
    int one[] = {42};
    array_gnome_sort(one, 1);
    EXPECT_EQ(one[0], 42);
}

TEST(BinarySearch, Found) {
    int arr[] = {1, 3, 5, 7, 9};
    std::size_t index = 100;
    EXPECT_TRUE(array_binary_search(arr, 5, 7, index));
    EXPECT_EQ(index, 3u);
    EXPECT_TRUE(array_binary_search(arr, 5, 1, index));
    EXPECT_EQ(index, 0u);
}

TEST(BinarySearch, NotFoundAndEmpty) {
    int arr[] = {1, 3, 5};
    std::size_t index = 100;
    EXPECT_FALSE(array_binary_search(arr, 3, 4, index));
    EXPECT_FALSE(array_binary_search(arr, 3, 0, index));
    EXPECT_FALSE(array_binary_search(nullptr, 0, 1, index));
    EXPECT_EQ(index, 100u);
}

TEST(RemoveAll, ExampleFromTask) {
    int arr[] = {2, 5, 2, 8, 2, 1};
    std::size_t size = 6;
    std::size_t removed = array_remove_all(arr, size, 2);
    EXPECT_EQ(removed, 3u);
    ASSERT_EQ(size, 3u);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 8);
    EXPECT_EQ(arr[2], 1);
}

TEST(RemoveAll, NothingOrEverything) {
    int arr[] = {4, 4, 4};
    std::size_t size = 3;
    EXPECT_EQ(array_remove_all(arr, size, 1), 0u);
    EXPECT_EQ(size, 3u);
    EXPECT_EQ(array_remove_all(arr, size, 4), 3u);
    EXPECT_EQ(size, 0u);

    std::size_t empty_size = 0;
    EXPECT_EQ(array_remove_all(nullptr, empty_size, 4), 0u);
}

TEST(Variant, SortThenRemoveAll) {
    std::size_t size = 6;
    int* arr = array_create(size);
    int data[] = {3, 1, 3, 2, 3, 0};
    for (std::size_t i = 0; i < size; i++) {
        arr[i] = data[i];
    }
    array_gnome_sort(arr, size);
    std::size_t removed = array_remove_all(arr, size, 3);
    EXPECT_EQ(removed, 3u);
    ASSERT_EQ(size, 3u);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 2);
    array_delete(arr);
}
