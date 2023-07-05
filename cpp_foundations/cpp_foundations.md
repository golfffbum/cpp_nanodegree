# Cpp Foundations

# Intro
## Includes
```
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
```

## Build & Compile
``` g++ main.cpp && ./a.out ```

# Basics 
## Vectors

```cpp    
    vector<int> v_1 = {3, 4, 5};
    vector<vector<int>> v {{1,2}, {3,4}};
        vector<vector<int>> board = {{0, 1, 0, 0, 0, 0},
                                 {0, 1, 0, 0, 0, 0},
                                 {0, 1, 0, 0, 0, 0},
                                 {0, 1, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 1, 0}};
```

### Insert and Size
```cpp
    // Push 4 to the back of the vector
    v_1.push_back(4);

    // Size: 
    board[0].size();
```

## Arrays
An array is a C++ container much like a vector, although without the ability to change size after initialization.

## Loops

```cpp
    for(int i=0; i <5; i++)
    {
        cout << i << "\n";
    }

    // range based for loops 
    for(int i : v_1)
    {
        cout << i << "\n";
    }

    for (auto v : board) //set vector v to each inner vector in b 
    {
        for (int j : v) //for each inner vector, set j to each element in inner vector
        {
            cout << j << "\n";
        }
    }
```

## Enums
```cpp
    enum class Color {white, red, blue};
    Color my_color = Color::blue;
```

## Functions
```cpp
    return_type FunctionName(parameter_list) {
        //Body of function here.
    }
```


## Istream
```cpp
    string a("1 2 3");

    istringstream my_stream(a);
```

### "extraction operator": >>
The extraction operator will read until whitespace is reached or until the stream fails.
- writes the stream to the variable on the right of the operator and returns the istringstream object, 
- so the entire expression my_stream >> n is an istringstream object and can be used as a boolean! 

Testing to see if the stream was successful and printing results.
```cpp
    while (my_stream >> n) {
      cout << "That stream was successful: " << n << "\n";
    }
    cout << "The stream has failed." << "\n";

    // OR check for int followed by char 
    char c;
    int n;

    while (my_stream >> n >> c){

    }
```

# A*
path finder, find a path, if one exists between any two nodes in a graph

Planning Problem:
given,
- map 
- starting location 
- goal location 
- cost 
goal, 
- find minimum cost path 


Search(grid, initial_point, goal_point)
1. init an empty list 
2. init a starting node w/ x,y at starting point, g=0, g is cost for each move, h given by the heuristic function
3. add the new node to the list of open nodes
4. while list of open nodes is nonempty:
    - Sort the open list by f-value
    - Pop the optimal cell (called the current cell).
    - Mark the cell's coordinates in the grid as part of the path.
    - if the current cell is the goal cell: return the grid.

The A* algorithm finds a path from the start node to the end node by checking for open neighbors of the current node, computing a heuristic for each of the neighbors, and adding those neighbors to the list of open nodes to explore next. The next node to explore is the one with the lowest total cost + heuristic (g + h). This process is repeated until the end is found, as long as there are still open nodes to explore.

# Pass by...

## Value (a copy)
When a function is called on some data, a copy of that data is made, and the function operates on a copy of the data instead of the original data. This is referred to as pass by value, since only a copy of the values of an object are passed to the function, and not the actual objects itself.

 ## Reference
 &a, change so that the passed variable can be directly modified by the function
 example,
 ```cpp
 int MultiplyByTwo(int &i) {
    i = 2*i;
    return i;
}

int main() {
    int a = 5;
    cout << "The int a equals: " << a << "\n"; //5
    int b = MultiplyByTwo(a);
    cout << "The int b equals: " << b << "\n"; //10
    cout << "The int a now equals: " << a << "\n"; //10
}
```

## C++ supports two notions of immutability:
- const: meaning roughly " I promise not to change this value."...The compiler enforces the promise made by const....
- constexpr: meaning roughly "to be evaluated at compile time." This is used primarily to specify constants...

```cpp
int main()
{
    int i;
    std::cout << "Enter an integer value for i: ";
    std::cin >> i;
    const int j = i * 2;  // "j can only be evaluated at run time."
                          // "But I promise not to change it after it is initialized."
    
    constexpr int k = 3;  // "k, in contrast, can be evaluated at compile time."
    
    std::cout << "j = " << j << "\n";
    std::cout << "k = " << k << "\n";
}
```

### compiler will catch a const/constexpr variable that changes
```cpp
int main()
{
    const int i = 2; // "I promise not to change this."
    i++;             // "I just broke my promise."

    constexpr int i = 2;  // "i can be evaluated at compile time."
    i++;                  // "But changing a constexpr variable triggers an error."
}
```

### when to use const
A common usage of const is to guard against accidentally changing a variable, especially when it is passed-by-reference as a function argument.
When in doubt, use const, especially to guard against accidentally modifying a variable.
```cpp
int sum(const std::vector<int> &v) //passing by reference, if passed as a variable const wouldnt be necessary, const makes sure v doesnt get modified in sum function
{
    int sum = 0;
    for(int i : v)
        sum += i;
    // v.push_back(5), would cause a compile error
        return sum;
}
```

# Header Files
Header files, or .h files, allow related function, method, and class declarations to be collected in one place

The #include statement for the header used quotes " " around the file name, and not angle brackets <>. We have stored the header in the same directory as the .cpp file, and the quotes tell the preprocessor to look for the file in the same directory as the current file - not in the usual set of directories where libraries are typically stored.

- Finally, there is a preprocessor directive, an "include guard"
  ```cpp
  #ifndef HEADER_EXAMPLE_H
  #define HEADER_EXAMPLE_H
  ``` 
Since the header will be included into another file, and `#include` just pastes contents into a file, the include guard prevents the same file from being pasted multiple times into another file. This might happen if multiple files include the same header, and then are all included into the same `main.cpp`, for example. 
The `ifndef` checks if `HEADER_EXAMPLE_H` has not been defined in the file already. If it has not been defined yet, then it is defined with `#define HEADER_EXAMPLE_H`, and the rest of the header is used. If `HEADER_EXAMPLE_H` has already been defined, then the preprocessor does not enter the `ifndef` block.


## Object files
- The preprocessor runs and executes any statement beginning with a hash symbol: #, such as #include statements. This ensures all code is in the correct location and ready to compile.
- Each file in the source code is compiled into an "object file" (a .o file). Object files are platform-specific machine code that will be used to create an executable.
- The object files are "linked" together to make a single executable. In the examples you have seen so far, this executable is a.out, but you can specify whatever name you want.

## CMakeList.txt
CMakeList.txt files are simple text configuration files that tell CMake how to build your project. These files can be used to specify the locations of necessary packages, set build flags and environment variables, specify build target names and locations, and other actions.

1. first specify the minimum versions of cmake and C++ required to build the project.
```cpp
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 14)
```
- These lines set the minimum cmake version required to 3.5.1 and set the environment variable CMAKE_CXX_STANDARD so CMake uses C++ 14.
2. CMake requires that we name the project, project(<your_project_name>)
3. add an executable, with the add_executable command by specifying the executable name, along with the locations of all the source files that you will need. CMake has the ability to automatically find source files in a directory
4. A typical CMake project will have a build directory in the same place as the top-level CMakeLists.txt
5. From within the build directory, you can now run CMake as follows:
```
root@abc123defg:/home/workspace/cmake_example/build# cmake ..
root@abc123defg:/home/workspace/cmake_example/build# make
```

- The first line directs the cmake command at the top-level CMakeLists.txt file with ... This command uses the CMakeLists.txt to configure the project and create a Makefile in the build directory.
- In the second line, make finds the Makefile and uses the instructions in the Makefile to build the project.

### build 
```
mkdir build 
cd build 
cmake ..
make 
```

# Pointers 
However, much like the pass-by-reference example that you saw previously, it can often be far more efficient to perform an operation with a pointer to an object than performing the same operation using the object itself.

At this point, you might be wondering why the same symbol & can be used to both access memory addresses and, as you've seen before, pass references into a function. This is a great thing to wonder about. The overloading of the ampersand symbol & and the * symbol probably contribute to much of the confusion around pointers.

The symbols & and * have a different meaning, depending on which side of an equation they appear.

-  For the & symbol, if it appears on the left side of an equation (e.g. when declaring a variable), it means that the variable is declared as a reference.
- If the & appears on the right side of an equation, or before a previously defined variable, it is used to return a memory address, as in the example above.

Once a memory address is accessed, you can store it using a pointer. A pointer can be declared by using the * operator in the declaration. See the following code for an example:
```
    int i = 5;
    // A pointer pointer_to_i is declared and initialized to the address of i.
    int* pointer_to_i = &i;
    
    // Print the memory addresses of i and j
    cout << "The address of i is:          " << &i << "\n";
    cout << "The variable pointer_to_i is: " << pointer_to_i << "\n";

    The address of i is:          0x7f508c4f42cc
    The variable pointer_to_i is: 0x7f508c4f42cc
```

Once you have a pointer, you may want to retrieve the object it is pointing to. In this case, the * symbol can be used again. This time, however, it will appear on the right hand side of an equation or in front of an already-defined variable, so the meaning is different. In this case, it is called the "dereferencing operator", and it returns the object being pointed to. You can see how this works with the code below:
```
cout << "The value of the variable pointed to by pointer_to_i is: " << *pointer_to_i << "\n";
```

Pointers can be used in another form of pass-by-reference when working with functions. When used in this context, they work much like the references that you used for pass-by reference previously. If the pointer is pointing to a large object, it can be much more efficient to pass the pointer to a function than to pass a copy of the object as with pass-by-value.

## References vs pointers
References	Pointers
- References must be initialized when they are declared. This means that a reference will always point to data that was intentionally assigned to it.	- Pointers can be declared without being initialized, which is dangerous. If this happens mistakenly, the pointer could be pointing to an arbitrary address in memory, and the data associated with that address could be meaningless, leading to undefined behavior and difficult-to-resolve bugs.
- References can not be null. This means that a reference should point to meaningful data in the program.
- Pointers can be null. In fact, if a pointer is not initialized immediately, it is often best practice to initialize to nullptr, a special type which indicates that the pointer is null.
- When used in a function for pass-by-reference, the reference can be used just as a variable of the same type would be.
- When used in a function for pass-by-reference, a pointer must be dereferenced in order to access the underlying object.

References are generally easier and safer than pointers. As a decent rule of thumb, references should be used in place of pointers when possible.

However, there are times when it is not possible to use references. One example is object initialization. You might like one object to store a reference to another object. However, if the other object is not yet available when the first object is created, then the first object will need to use a pointer, not a reference, since a reference cannot be null. The reference could only be initialized once the other object is created.

references only refer to one thing and that is it 


The arrow operator -> is used to simultaneously

dereference a pointer to an object and
access an attribute or method.
For example, in the code below, cp is a pointer to a Car object, and the following two are equivalent:

// Simultaneously dereference the pointer and 
// access IncrementDistance().
cp->IncrementDistance();

// Dereference the pointer using *, then 
// access IncrementDistance() with traditional 
// dot notation.
(*cp).IncrementDistance();

### this pointer 
It is possible to make this explicit in C++ by using the this pointer, which points to the current class instance. Using this can sometimes be helpful to add clarity to more complicated code:

## Map or hash table
A map (alternatively hash table, hash map, or dictionary) is a data structure that uses key/value pairs to store data

In the cell below, we have created a hash table (unordered_map) to store the data from the example above. To create an unordered_map in C++, you must include the <unordered_map> header, and the sytnax for declaring an unordered_map is as follows:

unordered_map <key_type, value_type> variable_name;
In the code below, we check if the key is in the unordered_map using the .find() method. If the key does not exist in the map, then .find() returns an unordered_map::end() type. Otherwise, .find() returns a C++ iterator, which is a pointer that points to the beginning of the iterable key-value pair

```
    unordered_map <string, vector<string>> my_dictionary;

    // Check if key is in the hash table.
    if (my_dictionary.find(key) == my_dictionary.end()) {
        cout << "The key 'word' is not in the dictionary." << "\n";
        cout << "Inserting a key-value pair into the dictionary." << "\n\n";
        // Set the value for the key.
        my_dictionary[key] = vector<string> {def_1, def_2, def_3, def_4};
    }

    // The key should now be in the hash table. You can access the
    // value corresponding to the key with square brackets [].
    // Here, the value my_dictionary[key] is a vector of strings.
    // We iterate over the vector and print the strings.
    cout << key << ": \n";
    auto definitions = my_dictionary[key];
    for (string definition : definitions) {
        cout << definition << "\n";
    }
```

## Inheritance 

class Sedan : public Car {
    // Sedan class declarations/definitions here.
};

each Sedan class instance will have access to any of the public methods and attributes of Car

## new 
The new operator allocates memory on the "heap" for a new Car. In general, this memory must be manually managed (deallocated) to avoid memory leaks in your program. Memory management is the primary focus of one of the later courses in this Nanodegree program, so we won't go into greater depth about the difference between stack and heap in this lesson.



## pROJECT
- node provides a single point on the map 

### files 
cmake** ** This directory contains some .cmake files that are needed for the project to find the necessary libraries. You will not need to work with this directory for this project.

src The source code for the project is contained here, and this is where you will be doing all of the project work. See the next classroom concepts for more information about the contents of this directory.

test This directory contains unit tests for various exercises, implemented using the Google Test framework. As you are developing your code, it may be helpful to look at the relevant tests in this directory to see the expected results and corresponding code. The code written here can be used to understand how different classes and objects in your work. If your code fails a test, the console message will indicate which is the failing test.

thirdparty This directory contains third-party libraries that have been included with this project. You will not need to work directly with this code.

### model.h and model.cpp
The model.h and model.cpp files come from the IO2D example code. We provide an overview of only the model.h file, as the method implementations in model.cpp file are beyond the scope of the course.

These files are used to define the data structures and methods that read in and store OSM data. OSM data is stored in a Model class which contains nested structs for Nodes, Ways, Roads, and other OSM objects. Have a look at the video above for an overview of the code in the header file.

## emplace_back vs push_back
push_back: This function is used to add an element at the end of the vector by creating a copy of the provided element. It takes the element as a parameter and appends a copy of it to the vector.

emplace_back: This function constructs the element in-place at the end of the vector, directly within the vector's memory. It takes the constructor arguments for the element as parameters and constructs the element within the vector without creating a separate copy.

The main advantage of emplace_back over push_back is that it avoids unnecessary copying or moving of elements. When constructing complex objects or objects with expensive copy/move operations, emplace_back can be more efficient by directly constructing the object in the vector's memory, eliminating the need for an additional copy.

When we say that an element is "constructed in place," it means that the element is created directly within the container's memory space without any additional copies or moves. In other words, the memory required for the element is allocated within the container itself.

## to ask 
when to use a reference? instead of just sending the variable

what is link libraries needed for? 
### link the following libraries to executable OSM_A_star_search
target_link_libraries(OSM_A_star_search
    PRIVATE io2d::io2d
    PUBLIC pugixml
)

## what is the point of sorting in the project? 



## namespace vs classes? 
linux parser when to use?
- could be extented to different systems? 
- 