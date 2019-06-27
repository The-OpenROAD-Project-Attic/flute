# Flute 3.1

Flute 3.1 with UTD improvments using CMake instead of Fred Flintstone
era autotools, remove UTD utility dependency, restore original test
program flute-net, define a flute namespace and add prefixes to macro
definitions.

### UTD-flute

This repository contains the original flute (unused) and a streamlined
version which is reentrant and dynamic, that is MAXD has been completely
eliminated.   In addition, there are no known memory leaks and the
library has been tested using Purify.  Originally, FLUTE was written
using stack memory and was subject to stack size limitations.  It
was observed that this coding could fail with net sizes as small as
345 with MAXD set to 1000 and was input dependent.  This library 
does not encode the lookup tables into the binary but reads them 
from files.   The advantage is that 29MB of memory can be freed when
the flute object is freed.

Here are some results running on a 2014 Mac 2.8Ghz Intel Core i7 with
16GB DDR3 RAM:

 Number of Pins          Running Time in Milliseconds       Memory Usage
 --------------          ----------------------------       -----------
   1,000,000                     6,152,125                    298MB
     100,000                       509,173                     56MB
      10,000                        45,238                     32MB
       1,000                         3,842                     29MB
         100                           196                     29MB
          10                             0* 0.002 note 1       29MB
           2                             0* 0.000062 note 2    29MB

Note 1: too small for interrupt timer.  Calculated 2ms / 1000 calls
Note 2: too small for interrupt timer.  Calculated 62ms / 1,000,000 calls

### FLUTE 3.1

-------------- FLUTE - Version 3.1 -----------------
                       by
                Chris C.-N. Chu
       Dept. of ECpE, Iowa State University
             Copyright (c) - 2005
  Iowa State University Research Foundation, Inc.
----------------------------------------------------

This package contains the following files:

 flute.c -- The rectilinear Steiner minimal tree and wirelength estimation
	    algorithm described in the ICCAD 04 and ISPD 05 papers with
	    some improvements described in TCAD 07 paper.
 flute.h -- The interface to use flute.
 flute_mst.c -- The net breaking and merging techniques described in the
	    VLSIDAT 08 paper.
 dist.[ch], dl.[ch], err.[ch], heap.[ch], mst2.[ch], neighbors.[ch],
	    global.h -- Utility functions used by flute_mst.c
 POWV9.dat -- The lookup-table of optimal POWVs up to degree 9.
 POST9.dat -- The lookup-table for optimal Steiner trees up to degree 9.
 flute-net.c -- A program to evaluate the wirelength of a net. It takes
	    input from stdin as a list of points.
 rand-pts.c -- A program to generate a list of random points.
 flute-ckt.c -- A program to find FLUTE and half-perimeter wirelength
	    of a circuit in bookshelf format.
 bookshelf_IO.[ch] -- Functions for flute-ckt.c to read bookshelf files.
 memAlloc.[ch] -- Functions for flute-ckt.c to allocate memory.
 ibm01/ibm01.* -- ibm01 bookshelf files that can be read by flute-ckt.c
 license.txt -- License agreement.
 ChangeLog.txt
 Makefile
 Readme

To run the programs, first do a 'make'. POWV9.dat and POST9.dat is assume
to be in the current directory.  Some example commands:

 rand-pts | flute-net
 rand-pts 20 | flute-net	    // 20-pin nets
 rand-pts -r 20 | flute-net	    // randomized
 flute-ckt ibm01 ibm01.aux ibm01/ibm01.pl
