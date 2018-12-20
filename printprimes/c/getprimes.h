/*
 * getprimes.h
 *
 * A module to contain functions to print a number of primes up to a given integer.
 *
 * The first function in this module does it the most straightforward way possible,
 * by checking each number against all lower numbers to see if it is evenly divisbly
 * by any smaller number.
 *
 * The section function does this more quickly.  It builds a set of prime numbers
 * from previously encountered prime numbers and only checks a new number against
 * previous numbers.  It also special cases the number 2 and then checks only
 * odd numbers to allow the algorithm to skip even numbers greater than 2.
 *
 * Ideally, we could stop checking each number once we have checked the candidate
 * against a prime that is greater than the square root of the number, but we chose
 * not to calculate the square root as that is an expensive calculation.
 *
 */

#ifndef GETPRIMES_H
#define GETPRIMES_H


/* Build an array of primes, given a pointer to an array of unsigned int and the number of values in that array  */

unsigned int get_primes_slowly(unsigned int max_int, unsigned int *primes, unsigned int sizeof_primes);

unsigned int get_primes_faster(unsigned int max_int, unsigned int *primes, unsigned int sizeof_primes);

#endif /* GETPRIMES_H */

