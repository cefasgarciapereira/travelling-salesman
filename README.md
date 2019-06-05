# Travelling Salesman

The aim of this work is the study and the implementation of algorithms to solve
the Traveling Salesman Problem using the following paradigms:

* Brute Force
* Branch and Bound
* Dynamic Programming
* Genetic Algorithm

## Input ##

The input is read from a text file with integers. The first number, n, is the
number of cities (indexed with the numbers 1 to n). The following numbers come
in pairs and represent the coordinates of cities (X and Y). The first pair of
numbers are the coordinates of city 1, the second pair, city 2 and so on up to
city n.Consider that 0 ≤ n ≤ 100 and that 0 ≤ X, Y ≤ 1000.

| Example (four cities) |
| --------------------- |
| 4                     |
| 100 100               |
| 900 100               |
| 900 900               |
| 100 900               |

## Output ##

The output is written to a text file and contains the sum of the distances and a
sequence of numbers, representing the order in which the cities were visited.
It always start this sequence with the city 1.

| Example (four cities) |
| --------------------- |
| 3200.00               |
| 1 2 3 4               |

## Project Structure ##

The project has the folders ```src``` and ```assets```. Inside the folder
```assets``` is the file ```trace.txt``` that is the file which you will
define the number of cities and their coordinates.
  The folder ```src``` contains the implementation of all algorithms. It is very
important that your folder hierarchy be the same as the one in this repository.
Because the code in C will look for the file in the relative source, so if you
need to change it for any reason, remember to also change it in the code.


## Running ##

The project is written in C language. We recommend you to use gcc to compile
the code, as it follows:

```
gcc -o output-file-name input-file-name.c -lm
```

```
./output-file-name
```
