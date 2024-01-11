#ifndef NUMBERSORTER_H
#define NUMBERSORTER_H

#include <mutex>
#include <vector>
#include <string>

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

        // Variable to store numbers read from the file. Not necessary since we're using shared data
        // But using for validation purposes to check if the algorithm is working properly.
        std::vector<int> numbersFromFile;

        /**
         * @brief: Auxiliary function to provide file handling before actually start processing the test file.
         * By default the extension is set to txt.
         * @param: TODO
        */
        bool hasExtension(const std::string& fileName);

        /**
         * @brief: Auxiliary function to check if file is empty.
        */
        bool isFileEmpty(const std::string& fileName);

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
    void readNumbersFromFile(const std::string& fileName);

    /**
     * @brief Generate random integer numbers.  
     * 1. Takes in user-defined parameters for setting the total numbers of integers to be generated and the maximal threshold value.
     * 2. Generated numbers are stored in the same NumberSorter's numbers attribute and makes use of mutex to avoid data racing between threads.
    */
    void generateNumbers(int count, int int_interval_max_threshold);

    /**
     * @brief Sort numbers using std::sort from C++ STL.  
     * The choice for such algorithm was for its simplicity: doesn't require additional implementation and
     * provides solid performance for moderated size list of numbers with complexity of O(N logN).
    */
    void sortNumbers();

    /**
     * @brief Shows sorted numbers to the current terminal session.
    */
    void showSortedNumbers();

    /**
     * @brief Shows numbers read from the file in the current terminal session.
     * Main purpose of this method is to validate if the algorithm is reading and sorting the numbers
     * read from the file correctly.
     * This method makes use of the numbersFromFile attribute, which was created specifically for that.
    */
    void showNumbersFromFile();

};


#endif /* NUMBERSORTER_H */
