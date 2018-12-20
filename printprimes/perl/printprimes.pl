#!/usr/bin/env perl

#  printprimes.pl
#
#  Copyright 2012 - Jeff R. Stripling - All Rights Reseverd
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
#  printprimes.pl [-m method] [-l limit] [-n numprimes]
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

use strict;
use Getopt::Std;

sub usage()
{
    printf("$ARGV[0] [-m method] [-n numprimes] [-l limit]\n");
}

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

sub get_primes_slowly
{
    my ($max_int, $num_primes) = @_;
    my @primes = ();
	my $found_primes = 0;
    my $x;
    my $y;
    
    return () if ($max_int < 2);
    
    X: for ($x = 2; ($x < $max_int) && ($found_primes < $num_primes); $x++)
    {
        $y = 2;
        
        for ($y = 2; $y < $x; $y++)
        {
            next X unless ($x % $y); # Go to the next candidate unless x divided y has some remainder
        }
        
        # if y has reached x, we have found a prime!  Save it in our array and go to the next X
        push (@primes, $x);
		$found_primes++;
    }
    
    return (@primes);
}

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

sub get_primes_quickly
{
    my ($max_int, $num_primes) = @_;
    my @primes = ();
	my $found_primes = 0;
    my $x;
    my $y;
    
    return () if ($max_int < 2);
    
    # Go ahead and record the first prime
    push(@primes, 2);
	$found_primes++;
    
    X: for (my $x = 3; $x < $max_int && $found_primes < $num_primes; $x += 2)
    {
        foreach my $y (@primes)
        {
            next X unless ($x % $y); # Go to the next candidate unless x divided y has some remainder
        }
        
        # if we have tried all of our current primes, we have found a new prime!  Save it in our array and go to the next X
        push (@primes, $x);
		$found_primes++;
    }
    
    return (@primes);
}

# Main Program
# Parse some command line arguements

my $MaxNumber = 100000;
my $NumPrimes = 100;
my $Method = 0;
my %opt = {};

usage() unless getopts('l:m:n:', \%opt);

$MaxNumber = $opt{l} if $opt{l};
$NumPrimes = $opt{n} if $opt{n};
$Method = $opt{m} if $opt{m};

my @Primes = ();
if ($Method == 0)
{
    @Primes = get_primes_slowly($MaxNumber, $NumPrimes);
}
else
{
    @Primes = get_primes_quickly($MaxNumber, $NumPrimes);
}

print("Found $#Primes primes:\n");

# Print the primes, 10 to a line
my @p = @Primes;
while (@p)
{
    my @line = splice(@p, 0, 10);       # Get up to 10 primes
    my $msg = join(' ', @line) . "\n";  # Join them together on a line
    printf($msg);                       # Print the line
}
