/*
 * Copyright 2010-2012, 2018 - Jeff R. Stripling - All Rights Reserved
 *
 * printprimes.c
 *
 * A module to contain functions to print a number of primes up to a given integer.
 *
 * The first function in this module does it the most straightforward way possible,
 * by checking each number against all lower numbers to see if it is evenly divisbly
 * by any smaller number
 *
 * The section function does this more quickly.  It builds a set of prime numbers
 * from previously encountered prime numbers and only checks a new number against
 * previous numbers.  It also special cases the number 2 and then checks only
 * odd numbers to allow the algorithm to skip even numbers greater than 2.
 */

/*
 * Print each prime from 1 to k, return the number of primes found
 */

#include "stdio.h"

unsigned int get_primes_slowly(unsigned int max_int, unsigned int *primes, unsigned int sizeof_primes)
{
    unsigned int x,y;
    unsigned int *curr_prime;
    unsigned int num_primes;
    
    if ((primes == NULL) || (sizeof_primes < 1) || (max_int < 2))
    {
	    return (0);
    }

    /* Set X to the first possible prime number */
    curr_prime = primes;
    num_primes = 0;

    x = 2;
    while ((x < max_int) && (num_primes < sizeof_primes))
    {
        /* Set Y to the first possible prime number */
        y = 2;

        /* While y is less than x and x is not divisible by y */ 
        while ((y < x) && (x % y))
        {
            y++;
        }

        /* if y is now x, we counted all the way from y to x without any y being divisible by x, so x is prime */
        if (y == x)
        {
            /* save this prime and move on */
            *curr_prime++ = x;
            num_primes++;
        }
        x++;
    }

    return (num_primes);
}

/*
 * Build an array of primes, given a pointer to an array of unsigned int and the number of values in that array 
 */

unsigned int get_primes_faster(unsigned int max_int, unsigned int *primes, unsigned int sizeof_primes)
{
    unsigned int x,num_primes;
    unsigned int *curr_prime;
    unsigned int prime_idx;

    if ((primes == NULL) || (sizeof_primes < 1) || (max_int < 2))
    {
	    return (0);
    }
	
    /* Process 2 first, so that we may only check odd numbers */
    *primes = 2;
    num_primes = 1;
    
    /* We can now start looking for primes at 3 */
    x = 3;

    while ((x < max_int) && (num_primes < sizeof_primes))
    {
        /* Start at the beginning of our primes array */
        curr_prime = primes;
        prime_idx = 0;

        /* While we have more primes to check and x is not divisible by the current prime */ 
        while ((prime_idx < num_primes) && (x % *curr_prime))
    	{
    	    /* Go to the next prime */
    		curr_prime++;
    		prime_idx++;
    	}

        /* If this number is not divisible by any of the previous primes, it is prime.
         * Add it to the list */
    	if (prime_idx == num_primes)
    	{
    		*curr_prime = x;
    		num_primes++;
    	}

        /* Increment by two to skip the even numbers, since 2 is the only even prime number */
        x += 2;
    }

    /* Return the number of primes found.  If the number of primes equals sizeof_primes
     * we may not have found all of the possible primes below max_int */
    return (num_primes); 
}

