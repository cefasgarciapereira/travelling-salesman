# Travelling Salesman

The aim of this work is the study and the implementation of algorithms to solve the
Traveling Salesman Problem using the following paradigms:

* Brute Force
* Branch and Bound
* Dynamic Programming
* Genetic Algorithm

## Input ##

The input is read from a text file with integers. The first number, n, is the
number of cities (indexed with the numbers 1 to n). The following numbers come in
pairs and represent the coordinates of cities (X and Y). The first pair of numbers are the
coordinates of city 1, the second pair, city 2 and so on up to city n.
Consider that 0 ≤ n ≤ 100 and that 0 ≤ X, Y ≤ 1000.

| Example (four cities) |
| --------------------- |
| 4                     |
| 100 100               |
| 900 100               |
| 900 900               |
| 100 900               |

## Output ##

The output must be written to a text file and must contain the sum of the distances and a
sequence of numbers, representing the order in which the cities were visited. Always start
this sequence with the city 1.

Example (four cities):
3200.00
1 2 3 4

| Example (four cities) |
| --------------------- |
| 3200.00               |
| 1 2 3 4               |

## Running ##

The project is written in C language. We recommend you to use gcc to compile the code, as it follows:

```
gcc -o output-file-name input-file-name.c -lm
```

```
./output-file-name
```
