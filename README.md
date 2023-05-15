# Ray Tracer Testbed

## Description
This repository contains a robust ray tracer testbed for rendering scenes and comparing results with provided solutions. It allows users to specify test files, solution files, statistics files, and even specific pixel coordinates for detailed debugging.

## Usage
The basic usage of the ray tracer is: 

```
./ray_tracer -i <test-file> [ -s <solution-file> ] [ -o <stats-file> ] [ -x <debug-x-coord> -y <debug-y-coord> ]
```

- `-i <test-file>`: Renders the scene described by `<test-file>`. The result is dumped to `output.png`.
- `-s <solution-file>`: Renders the scene described by `<test-file>` and compares this to the solution in `<solution-file>`. It dumps the error to `diff.png` and outputs a measure of the error.
- `-x <debug-x-coord> -y <debug-y-coord>`: These flags allow for the detailed debugging of a single pixel. This can be particularly useful when debugging specific parts of the rendering process. The pixel coordinates are provided as arguments.
- `-o <stats-file>`: This flag is used to redirect the results of your ray tracer to be printed to a file rather than to the standard output. This can be useful to avoid confusion with debugging output.

## Debugging
For debugging a specific pixel, use the `-x` and `-y` flags to specify the pixel of interest. The program will provide detailed information about the rendering of this single pixel, allowing for verbose output without printing this information for every pixel. This is particularly useful when you are getting the wrong results for a test and need to debug the problem.

## Compilation
To compile the program, use a C++ compiler such as `g++.`

```
g++ -o ray_tracer main.cpp
```

Replace `main.cpp` with the name of the file containing the `main` function.
