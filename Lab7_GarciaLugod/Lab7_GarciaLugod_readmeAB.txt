Program A, given an array of integers, cubes the even indeces, and negates the odd indeces.
Each integer is given its own pthread to calculate its final value.

Program B computes sin via pthreads and checks its correctness against the sinl() function.
It takes two inputs, N and X.
N is the number of threads to spawn, while X is the argument of sin to be calculated.
An infinite series is used to calculate the value of sin with the terms divided among the pthreads.