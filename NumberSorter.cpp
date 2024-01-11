/**
 * @file NumberSorter.cpp
 * @brief NumberSorter is a C++ program that makes use of OOP to implement a NumberSorter class.
 * * Author: Henrique Poleselo @hpoleselo
 * * Date: 07-16-2023
 */

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include "NumberSorter.h"

bool NumberSorter::hasExtension(const std::string& fileName) {

    const std::string& extension = "txt";

    // Find the position of the last dot in the file name (will break with hidden files/folders)
    size_t dotPos = fileName.find_last_of(".");
    if (dotPos != std::string::npos) {
        // Extracts the file extension from the file name
        std::string fileExtension = fileName.substr(dotPos + 1);
        
        // Compare the extracted extension with the desired extension
        return (fileExtension == extension);
    }
    // No file extension found
    return false;
}

bool NumberSorter::isFileEmpty(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.peek() == std::ifstream::traits_type::eof();
}

void NumberSorter::readNumbersFromFile(const std::string& fileName) {

    // Conditional Guard to check before opening the file, checks the file extension
    // to spare resources and avoid future errors.
    if (hasExtension(fileName)) {
        std::cout << "Provided file is a txt file, proceeding with the number reading..." << std::endl;
    } else {
        std::cout << "File does not have the desired extension. Terminating thread/application..." << std::endl;
        std::terminate();
    }

    // Reads file contents
    std::ifstream inputFile(fileName);

    // Checks if file is empty, for now for logging purposes
    if (isFileEmpty(fileName)) {
        std::cout << "Either the file provided doesn't exist or it's empty, generator Thread will generature the numbers anyway..." << std::endl;
    } else {
        std::cout << "File could be read succcesfully." << std::endl;
    }

    int number;

    while (inputFile >> number) {
        // Adds Mutex locking to prevent race condition when using the generatorThread to append values to the object's attribute
        m.lock();
        // TODO: Set verbosity flag
        // Using this print statement to check if threading was succesfull.
        //std::cout << "\nReading number from the user-provided file: " << number;
        numbers.push_back(number);
        // Unlocks it so that next instruction from other thread can be executed
        m.unlock();

        // For validation purposes only, data is appendend to other vector to check and compare later on
        numbersFromFile.push_back(number);
    }
    inputFile.close();


}

void NumberSorter::generateNumbers(int count, int int_interval_max_threshold) {
    std::random_device rd;
    std::mt19937 generator(rd());
    // Generates an uniform integer disitrbution
    std::uniform_int_distribution<int> int_distribution(1, int_interval_max_threshold);

    for (int i = 0; i < count; ++i) {
        m.lock();
        //std::cout << "\nReading number from generator thread..." << i;
        numbers.push_back(int_distribution(generator));
        m.unlock();
    }
}

void NumberSorter::sortNumbers() {     
    std::sort(numbers.begin(), numbers.end());
}


void NumberSorter::showSortedNumbers() {
    std::cout << "\nSorted Numbers: " << std::endl;
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

void NumberSorter::showNumbersFromFile() {
    std::cout << "\nNumbers read from the file: " << std::endl;
    for (const auto& number : numbersFromFile) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}
