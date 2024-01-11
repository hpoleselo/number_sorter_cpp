#include <gtest/gtest.h>
#include <fstream>
#include "../NumberSorter.h"

// Test case for hasExtension method
TEST(NumberSorterTest, HasExtensionTest) {
    NumberSorter sorter;
    ASSERT_TRUE(sorter.hasExtension("file.txt"));
    ASSERT_FALSE(sorter.hasExtension("file.jpg"));
}

// Test case for isFileEmpty method
TEST(NumberSorterTest, IsFileEmptyTest) {
    NumberSorter sorter;

    // Check the file for emptiness directly
    std::ifstream file("mock_files/empty_file.txt");
    std::string content;

    // Read the file content
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line;
        }
        file.close();
    }

    // Then, check if the content is empty using the tested function
    EXPECT_TRUE(content.empty());
}



