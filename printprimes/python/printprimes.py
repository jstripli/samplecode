#!/usr/bin/env python
#
#  printprimes.py
#
#  Copyright 2010-2012, 2018 - Jeff R. Stripling - All Rights Reseverd
#
# A program created to collect prime numbers in an array and then print them.
#
# The first function in this module does it the most straightforward way possible,
# by checking each number against all lower numbers to see if it is evenly divisbly
# by any smaller number
#
# The section function does this more quickly.  It builds a set of prime numbers
# from previously encountered prime numbers and only checks a new number against
# previous numbers.  It also special cases the number 2 and then checks only
# odd numbers to allow the algorithm to skip even numbers greater than 2.
#
# Usage:
#
#  printprimes.py [-m method] [-l limit] [-n numprimes]
#
#   -m            Specify 0 for the slow method
#                         1 for the fast method
#
#   -l limit      Stop searching for primes when the candidate number
#                 reaches this limit.  For example, specifing 10,000 will
#                 search all numbers from 2 to 10,000 for primes, stopping if
#                 the maximum number of primes requested is found.  If omitted
#                 the program will stop searching at 100,000
#
#
#   -n numprimes  Stop searching when this many number of primes has been found.
#                 If omitted, the program will stop after 100 primes are found.
# 

import getopt
import sys

def usage():
    printf("$ARGV[0] [-m method] [-n numprimes] [-l limit]\n");

# -------------------------------------------------------------------------------
#
# get_primes_slowly
#
# A subroutine to slowly find prime numbers.  This routine works by going through
# each number from 2 up to max_int.  Each number is checked against all of the
# numbers lower than it.  If this number is evenly divisible by any of the numbers
# below it, the number is not prime.  Otherwise, the number is prime and is added
# to our list of primes
#
# -------------------------------------------------------------------------------

def get_primes_slowly(max_int, num_primes):
    primes = []
    x = 0;
    y = 0;
    
    for x in range(2, max_int + 1):
    
        for y in range(2, x):
            # If x is evenly divisible by y, x is not prime, go to the next candidate        
            if ((x % y) == 0):
                break
        else: # for loop made it to the end without breaking
        
            # We checked every number and reached the end of the list, so we have a new prime!
            # Save it in our array and go to the next X
            if (len(primes) < num_primes):
                primes.append(x)
            
            # If we have now found the max number of primes, stop finding more and return
            if (len(primes) >= num_primes):
                return primes
    
    return primes

# -------------------------------------------------------------------------------
#
# get_primes_quickly
#
# A subroutine to quickly find prime numbers.  This routine works by going through
# each number from 2 up to max_int.  Each number is checked against the set of
# prime numbers found that are less than this number.  If this number is evenly
# divisible by any of the previously found primes, than this number is not prime.
# Otherwise, this number is prime and is added to the array of primes.
#
# Additionally, this routine takes advantage of the fact that 2 is the only even
# prime number by considering only odd numbers after "finding" the first even prime.
# This cuts down the number of numbers to be considered by half.
#
# -------------------------------------------------------------------------------

def get_primes_quickly(max_int, num_primes):
    primes = []

    # First, special case 2 so that we can skip the even primes
    if (max_int > 1):
        if (len(primes) < num_primes):
            primes.append(2)
    
        # If we have now found the max number of primes, stop finding more and return
        if (len(primes) >= num_primes):
            return primes
    
    # Now go through all odd candidates    
    for x in range(3, max_int + 1, 2):
    
        for y in primes:
            
            # If x is evenly divisible by y, x is not prime, go to the next candidate        
            if ((x % y) == 0):
                break            
        else:
            # for loop made it to the end without breaking
            # We checked every found prime and reached the end of the list, so we have a new prime!
            # Save it in our array and go to the next X
            if (len(primes) < num_primes):
                primes.append(x)
            
                # If we have now found the max number of primes, stop finding more and return
                if (len(primes) >= num_primes):
                    return primes
    
    return primes


# Main Program
# Parse some command line arguements

MaxNumber = 100000
NumPrimes = 100
Method = 0

try:
    options, extra = getopt.getopt(sys.argv[1:], 'l:m:n:')
except getopt.GetoptError, err:
    print str(err)
    usage()
    sys.exit(2)

for opt, arg in options:
    if opt == '-l':
        MaxNumber = int(arg)
    elif opt == '-m':
        Method = int(arg)
    elif opt == '-n':
        NumPrimes = int(arg)

Primes = [];
if Method == 0:
    Primes = get_primes_slowly(MaxNumber, NumPrimes)
else:
    Primes = get_primes_quickly(MaxNumber, NumPrimes)

print "Found %d primes:\n" % len(Primes)

# Print the primes, 10 to a line
x = 0
while x < len(Primes):
    # Join up to 10 together on a line
    msg = ' '.join(str(x) for x in Primes[x:x+10])  
    print msg
    x += 10
