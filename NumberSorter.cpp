/* 
    * Author: Henrique Poleselo @hpoleselo
    * Date: 07-16-2023
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
     * Takes in filename as parameter.
     * Creates a input file stream object to read the provided filename.
     * Stores read numbers to the NumberSorter numbers vector<int> attribute, which is a . 
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
            m.lock();
            // TODO: Set verbosity flag
            // Using this print statement to check if threading was succesfull.
            std::cout << "\nReading number from the user-provided file:" << number;
            numbers.push_back(number);
            m.unlock();
        }
        inputFile.close();

    }

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

    void sortNumbers() {     
        std::sort(numbers.begin(), numbers.end());
    }

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
