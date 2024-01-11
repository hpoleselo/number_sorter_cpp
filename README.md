# Number Sorter in C++

NumberSorter is a C++ program that makes use of OOP to implement a NumberSorter class that reads a user-provided `.txt` file containing integer numbers and generates random integer numbers concurrently by making use of Mutexes to avoid data racing between threads, sorting the read/generated numbers by using the sort ``std::sort`` algorithm from Standard Library Template, which has [O(n) complexity](https://en.cppreference.com/w/cpp/algorithm/sort).

NumberSorter was developed in:

- Ubuntu 20.04
- GCC 9.4.0
- C++ 17

## Running the Application

Clone this repository:

`$ git clone git@github.com:hpoleselo/number_sorter_cpp.git`

Run the provided executable:

`$ ./NumberSorter`

There's an out-of-the-box `NumbersToBeSorted.txt` file which has some pre-defined integers to validate the application. One can extend this file to contain more numbers, such file is located in the root directory of this repository. Recall the file must contain **integers separated by spaces**, otherwise other cases will be disregarded.

## Building the Application Locally

`$ g++ -std=c++17 main.cpp NumberSorter.cpp -lpthread -o NumberSorter`

Or if wished to build it with GCC:

`$ gcc -o NumberSorter NumberSorter.cpp -pthread -lstdc++`

## Building and Running the Containerized Application Locally

To avoid any compatibility issues, one is able to run this application containerized using Podman/Docker. Make sure to be in the root folder of this repository and build the image:

`$ podman build -t numbersorter .`

Run the container (in my local it ended up building with the `localhost/` tag prefix):

`$ podman run --rm -it localhost/programsorter:latest`

Expected Output:

![image_2023-07-17_07-43-20](https://github.com/hpoleselo/number_sorter_cpp/assets/24254286/77fc5b05-848d-4e41-bdf5-45051768e5e3)

## Next Steps | Future Implementations

- [ ] Feature: check file consistency, if provided file is using backspaces and add handling for such scenarios.
- [ ] Unit tests and fulfill at least 80% code coverage.
- [ ] Set-up Codacy/Sonarqube to track code smells and so on.
- [ ] [Add logging](https://stackoverflow.com/questions/1255576/what-is-good-practice-for-generating-verbose-output).
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
- https://betterprogramming.pub/4-easy-tips-on-using-threads-and-mutexes-in-c-566eb2927152
