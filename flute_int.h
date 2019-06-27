/* ----------------------------------------------------------------- 
 * Originally written by Chris Chu, Iowa State University:
 -------------- FLUTE - Version 3.1 -----------------
                       by
                Chris C.-N. Chu
       Dept. of ECpE, Iowa State University
             Copyright (c) - 2005
  Iowa State University Research Foundation, Inc.
 ----------------------------------------------------
 * Just fantastic code. Thanks Chris! (WPS).
 * Modified by William Swartz for public use and to reduce memory usage
 * and to remove MAXD constraint.  Flute is now dynamic and reentrant!
 * Copyright (c) 2019 William Swartz.  UTD.  All rights reserved.
----------------------------------------------------------------- */
#ifndef FLUTE_INT_H
#define FLUTE_INT_H

namespace Flute {

/*************************************/
/* Internal Parameters and Functions */
/*************************************/
#define FLUTE_D 9                   // LUT is used for d <= D, D <= 9
#define TAU(A) (8+1.3*(A))
#define D1(A) (25+120/((A)*(A)))     // flute_mr is used for D1 < d <= D2
#define D2(A) ((A)<=6 ? 500 : 75+5*(A))

/* Some MACROS */
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define abs(x) ((x)<0?(-x):(x))
#define ADIFF(x,y) ((x)>(y)?(x-y):(y-x))  // Absolute difference

#if FLUTE_D<=7
#define MGROUP 5040/4  // Max. # of groups, 7! = 5040
#define MPOWV 15  // Max. # of POWVs per group
#elif FLUTE_D==8
#define MGROUP 40320/4  // Max. # of groups, 8! = 40320
#define MPOWV 33  // Max. # of POWVs per group
#elif FLUTE_D==9
#define MGROUP 362880/4  // Max. # of groups, 9! = 362880
#define MPOWV 79  // Max. # of POWVs per group
#endif

#define FLUTE_SOLUTION_STORAGE 15856

typedef struct csoln1 {
    unsigned char neighbor[2*FLUTE_D-2];
    unsigned char row[FLUTE_D-2];  
    unsigned char col[FLUTE_D-2];  
    unsigned char seg[12];  // Add: 0..i, Sub: j..10; seg[i+1]=seg[j-1]=0
    unsigned char parent;
} FLUTE_SOLN, *FLUTE_SOLNPTR ;

typedef struct point {
    FLUTE_DTYPE x, y;
    int o;
} FLUTE_POINT, *FLUTE_POINTPTR ;

typedef struct flute_rec {
  int numgrp[10] ;
  int numsoln[FLUTE_D+1][MGROUP] ;
  FLUTE_SOLNPTR lut[FLUTE_D+1][MGROUP] ;  // storing 4 .. D
  FLUTE_SOLNPTR *storage ;
  int num_alloc ;
  int num_used ;
} FLUTEBOX;

} // namespace

#endif /* FLUTE_INT_H */
