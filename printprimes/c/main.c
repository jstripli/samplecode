/*
 * Copyright 2010-2012, 2018 - Jeff R. Stripling - All Rights Reserved
 *
 * main.c
 *
 * A controlling program created to collect prime numbers in an array and then
 * print them.  A program to exercise the various prime printing functions.
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "getprimes.h"

#define OK 0
#define BAD_PARAM -1
#define PARSE_ERR -2
#define BAD_MEMORY -3

/* Put in a maximum number of primes, just to keep the caller from malloc'ing more memory than we expect */
#define MAX_NUM_PRIMES 1000000

/* Local function prototypes */
static void print_results(unsigned int *primes, unsigned int primes_found);

static void usage(char *prog);

/* -----------------------------------------------------------------------------
 *
 * print_results
 *
 * A function to print an array of primes
 *
 * Inputs:
 *   primes, a pointer to an array of prime numbers
 *   primes_found, the number of elements in the array
 *
 * Returns:
 *   Nothing
 *
 * -----------------------------------------------------------------------------*/

void print_results(unsigned int *primes, unsigned int primes_found)
{
    int x,num_on_line;
    unsigned int *curr_prime;
    
    if (primes == NULL)
    {
        printf("Could not print results");
        return;
    }
    
    printf("Found %d primes:\n", primes_found);
    
    curr_prime = primes;
    num_on_line = 0;
    
    for (x = 0; x < primes_found; x++)
    {
        /* print the primes we found, 10 to a line */
        printf("%d ", *curr_prime++);
        num_on_line = (num_on_line + 1) % 10;
        
        if (! num_on_line)
        {
            printf("\n");
        }
    }
    
    /* If we have printed some on a line but not finished the line, terminate the line */
    if (num_on_line)
    {
        printf("\n");
    }
}


/* -----------------------------------------------------------------------------
 *
 * usage
 *
 * A function to print a short message about how to use the program
 *
 * Inputs:
 *   prog, the name of the program on the command line
 *
 * Returns:
 *   Nothing
 *
 * -----------------------------------------------------------------------------*/


void usage(char *prog)
{
    if (prog == NULL)
    {
        return;
    }
    printf("%s [-m method] [-n numprimes] [-l limit]\n", prog);
}

/* -----------------------------------------------------------------------------
 *
 * usage
 *
 * A function to print a short message about how to use the program
 *
 * Inputs:
 *   prog, the name of the program on the command line
 *
 * Returns:
 *
 *   Zero if everything was OK, a non-zero value if an error occurred
 * 
 *   Specifically:
 * 
 *   OK if the program executed as expected
 *   PARSE_ERR if the program had an error parsing the command line
 *   BAD_PARAM if the user specified a bad parameter
 *   BAD_MEMORY if the program could not allocate memory for the array
 * 
 * -----------------------------------------------------------------------------*/


int main (int argc, char * const argv[])
{
    /* Variables used to calculate primes */
    unsigned int num_primes = 100;    /* The number of primes to find */ 
    unsigned int method = 0;          /* The method to use to calculate the primes */
    unsigned int max_number = 100000; /* the maximum number to check */
    
    unsigned int *primes = NULL;      /* An array to hold our primes */
    unsigned int primes_found = 0;    /* The actual number of primes found by the routine under test */

    int ch = -1;

    /* Parse arguments, print usage string if there is an error */
    while ((ch = getopt(argc, argv, "l:m:n:")) != -1)
    {
        switch (ch)
        {
            /* An option to specify the number of primes to find */
            case 'l':
                if (optarg != NULL)
                {
                    sscanf(optarg, "%d", &max_number);
                }
                else
                {
                    usage(argv[0]);
                    exit(PARSE_ERR);
                }
                break;
                
                
            /* An option to specify the maximum number to check to see if it is prime */
            case 'n':
                if (optarg != NULL)
                {
                    sscanf(optarg, "%d", &num_primes);
                }
                else
                {
                    usage(argv[0]);
                    exit(PARSE_ERR);
                }
                break;
                
            /* An option to specify the method to use to calculate the primes */    
            case 'm':
                if (optarg != NULL)
                {
                    sscanf(optarg, "%d", &method);
                    printf("method: %d\n", method);
                }
                else
                {
                    usage(argv[0]);
                    exit(PARSE_ERR);
                }
                break;
                
            default:
                printf("ch is %d\n", ch);
                usage(argv[0]);
                exit(BAD_PARAM);
                break;
        }
    }
    
    /* Range check the number of primes.
     * We want to find more than zero and less than our limit primes */
    if ((num_primes <= 0) || (num_primes > MAX_NUM_PRIMES))
    {
        usage(argv[0]);
        exit(BAD_PARAM);
    }

    
    /* Allocate some memory to hold our primes */
    primes = malloc(sizeof(unsigned int) * num_primes);
    if (primes == NULL)
    {
        printf("Can not malloc memory");
        exit(BAD_MEMORY);
    }
    
    switch (method)
    {
        case 0: /* Use classic method */
            primes_found = get_primes_slowly(max_number, primes, num_primes);
            break;
        case 1: /* Use quick method */
            primes_found = get_primes_faster(max_number, primes, num_primes);
            break;
    }

    /* Print the array of primes found */
    print_results(primes, primes_found);
    
    /* Free the memory we allocated before, with a safety check to ensure we are not freeing a null pointer */
    if (primes != NULL)
    {
        free(primes);
    }
    
    exit(OK);
}
