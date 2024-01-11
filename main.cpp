#include <thread>
#include "NumberSorter.h"


int main () {
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

    // Show numbers read from the file
    sorter.showNumbersFromFile();

    // Shows the sorted numbers
    sorter.showSortedNumbers();

    return 0;
}