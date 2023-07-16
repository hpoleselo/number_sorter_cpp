# Number Sorter in C++

NumberSorter is a C++ program that makes use of OOP to implement a NumberSorter class that reads a user-provided `.txt` file containing integer numbers and generates random integer numbers concurrently, sorting them using the sort ALGORITHM which has [O(n) complexity]().

NumberSorter was developed in:

- Ubuntu 20.04
- g++ 9.4.0
- C++ 17

## Running the Application

Clone this repository:

` $ git clone `

There's a compiled version of the program

There's an out-of-the-box `NumbersToBeSorted.txt` file which has some pre-defined integers to validate the application. One can extend this file to contain more numbers, such file is located in the root directory of this repository. Recall the file must contain **integers** separated by spaces, otherwise other cases will be disregarded.

## Building the Application Locally

`$  g++ -std=c++17 NumberSorter.cpp -lpthread -o NumberSorter`

Or if wished to build it with GCC:

`$ gcc `

## Next Steps | Future Implementations

- [ ] Feature: check file consistency, if provided file is using backspaces and add handling for such scenarios.
- [ ] Unit tests and fulfill at least 80% code coverage.
- [ ] Set-up Codacy/Sonarqube to track code smells and so on.
- [ ] Add logging.
- [ ] Trade-off on performance comparison by having a specific thread to sort the data and accounting for the overhead by using Load Testing.
- [ ] Refactor: Unique Lock instead of lock.

## Useful Resources

Resources used to accomplish this task as future reference for myself:

- https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html
- https://www.geeksforgeeks.org/multithreading-in-cpp/
- https://youtu.be/eZ8yKZo-PGw
- https://linuxhint.com/multi-thread-and-data-race-basics-in-cpp/
- https://stackoverflow.com/questions/20516773/stdunique-lockstdmutex-or-stdlock-guardstdmutex
- https://stackoverflow.com/questions/37945859/mutex-lock-vs-unique-lock

