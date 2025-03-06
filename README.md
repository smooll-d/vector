# vector
Custom implementation of C++20 std::vector.

>![CAUTION]
>Before building make sure to edit the `main.cpp` file in `src/`. You can use the vector from there. It's designed this way because this vector is not supposed to be used as a library, it was made as an exercise to see if I could actually finish a project.

## Building
To build this project you need CMake and a compiler which supports C++20.

```bash
$ git clone https://github.com/smooll-d/vector
$ cd vector
$ cmake -S . -B build
$ cmake --build
$ build/vector
```

The last command will run the executable.

## Usage
If you've ever used std::vector before, you know what to do and I don't have to tell you. This vector has the same function names as it's Standard Library counterpart.
