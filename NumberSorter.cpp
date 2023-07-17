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

/**
 * @brief This class represents a NumberSorter object.
 *
 * It provides functionality for:
 * 1. Reading a file containing numbers separated by spaces (readNumbersFromFile) in a decoupled thread
 * 2. Generate extra random numbers in a separated thread (generateNumbers).
 * 3. Sort the numbers from the file and the generated numbers (sortNumbers).
 * 4. Output the sorted numbers in the terminal session (showSortedNumbers).
 */
class NumberSorter {

private:
    // Critical section/region which leads to race condition
    std::vector<int> numbers;
    
    // Mutex to avoid race condition between readNumbersFromFile and generateNumbers threads
    std::mutex m;

    /**
     * @brief: Auxiliary function to provide file handling before actually start processing the test file.
     * By default the extension is set to txt.
     * @param: TODO
    */
    bool hasExtension(const std::string& fileName) {

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

    /**
     * @brief: Auxiliary function to check if file is empty.
    */
    bool isFileEmpty(const std::string& fileName) {
        std::ifstream file(fileName);
        return file.peek() == std::ifstream::traits_type::eof();
    }


public:

    /**
     * @brief Reads integer numbers separated by space from a .txt file.
     * 
     * 1. Checks if the file name conforms with the expected .txt format.
     * 2. Takes in filename as parameter.
     * 3. Creates a input file stream object to read the provided filename.
     * 4. Check if file is empty.
     * 5. Stores read numbers to the numbers object's attribute by using mutex.
    */
    void readNumbersFromFile(const std::string& fileName) {

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
            std::cout << "\nReading number from the user-provided file:" << number;
            numbers.push_back(number);
            // Unlocks it so that next instruction from other thread can be executed
            m.unlock();
        }
        inputFile.close();

    }

    /**
     * @brief Generate random integer numbers.  
     * 1. Takes in user-defined parameters for setting the total numbers of integers to be generated and the maximal threshold value.
     * 2. Generated numbers are stored in the same NumberSorter's numbers attribute and makes use of mutex to avoid data racing between threads.
    */
    void generateNumbers(int count, int int_interval_max_threshold) {
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

    /**
     * @brief Sort numbers using std::sort from C++ STL.  
     * The choice for such algorithm was for its simplicity: doesn't require additional implementation and
     * provides solid performance for moderated size list of numbers with complexity of O(N logN).
    */
    void sortNumbers() {     
        std::sort(numbers.begin(), numbers.end());
    }


    /**
     * @brief Shows sorted numbers to the current terminal session.
    */
    void showSortedNumbers() {
        std::cout << "\nSorted Numbers: " << std::endl;
        for (const auto& number : numbers) {
            std::cout << number << " ";
        }
        std::cout << std::endl;
    }

};

int main() {
    // Insantiates NumberSorter Object
    NumberSorter sorter;

    // Thread to read nymbers from the user-provided file concurrently
    std::string fileName = "IntegerNumbersToBeSorted.txt";
    std::thread readerThread([&sorter, &fileName]() {
        sorter.readNumbersFromFile(fileName);
    });

    // Sets number of numbers to be generated and number max threshold
    int additionalGeneratedNumbers = 200;
    int generatedNumbersMaxValue = 3000;

    // Creates thread to generate files concurrently
    std::thread generatorThread([&sorter, additionalGeneratedNumbers, generatedNumbersMaxValue]() {
        sorter.generateNumbers(additionalGeneratedNumbers, generatedNumbersMaxValue);
    });
    

    // Waits all thhreads to finish
    readerThread.join();
    generatorThread.join();

    // Sort numbers
    sorter.sortNumbers();

    // Shows the sorted numbers
    sorter.showSortedNumbers();

    return 0;
}
