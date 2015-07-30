Parallel Eratasthone's Sieve

An Eratasthone's Sieve finds prime numbers. I have parallelized and optimized an E sieve and compared it to a serial E sieve.
Will work best if you have a processor that can run 8 threads, but even if you don't you can see how more threads isn't always better.

To build:
$ gcc -fopenmp e_sieve_parallel.c -o sieve
in cygwin - must have openmp package installed
