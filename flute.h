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
#ifndef FLUTE_H
#define FLUTE_H

/*****************************/
/*  User-Defined Parameters  */
/*****************************/
/* Flute is now dynamic #define MAXD 3000   max. degree that can be handled */
#define FLUTE_ACCURACY 3  		// Default accuracy
#define FLUTE_ROUTING 1   	// 1 to construct routing, 0 to estimate WL only
#define FLUTE_LOCAL_REFINEMENT 0      // Suggestion: Set to 1 if ACCURACY >= 5
#define FLUTE_REMOVE_DUPLICATE_PIN 0  // Remove dup. pin for flute_wl() & flute()

/* Types of tables */
#define FLUTE_POWVFILE "POWV9.dat"        // LUT for POWV (Wirelength Vector)
#define FLUTE_POSTFILE "POST9.dat"        // LUT for POST (Steiner Tree)
#define FLUTE_PORTFILE "PORT9.dat"        // LUT for POST (Routing Tree)

#ifndef FLUTE_DTYPE   // Data type for distance
#define FLUTE_DTYPE int
#endif


#ifdef FLUTE_INTERNAL_VARS
#include <flute_int.h>
#endif /* FLUTE_INTERNAL_VARS */

namespace Flute {

typedef struct flute_rec FluteState ;

typedef struct {
  FLUTE_DTYPE x, y ;   	// starting point of the branch
  int n ;        	// index of neighbor
} Branch ;

typedef struct {	/* in proper packing order */
    Branch *branch ;   	// array of tree branches
    FLUTE_DTYPE length;		// total wirelength
    int deg ;   		// degree
} Tree ;

// User-Callable Functions
FluteState *flute_init( const char *wirelength_vector_file, const char *steiner_tree_file ) ;
void flute_free( FluteState * flute_p ) ;
FLUTE_DTYPE flute_wl( FluteState *flute_p,int d, FLUTE_DTYPE *x, FLUTE_DTYPE *y, int acc);

//Macro: DTYPE flutes_wl(int d, DTYPE xs[], DTYPE ys[], int s[], int acc);
Tree flute( FluteState *flute, int d, FLUTE_DTYPE *x, FLUTE_DTYPE *y, int acc);

// Free memory associated with flute tree.
void free_tree( FluteState * flute_p, Tree tree ) ;

//Macro: Tree flutes( FluteState * flute_p,int d, DTYPE *xs, DTYPE *ys, int *s, int acc);
FLUTE_DTYPE wirelength( Tree tree) ;
void printtree( Tree tree ) ;
void plottree( Tree tree ) ;

// Other useful functions
FLUTE_DTYPE flutes_wl_LD(FluteState *flute,int d, FLUTE_DTYPE *xs, FLUTE_DTYPE *ys, int *s);
FLUTE_DTYPE flutes_wl_MD(FluteState *flute,int d, FLUTE_DTYPE *xs, FLUTE_DTYPE *ys, int *s, int acc);
extern FLUTE_DTYPE flutes_wl_RDP(FluteState * flute_p,int d, FLUTE_DTYPE *xs, FLUTE_DTYPE ys[], int *s, int acc);
extern Tree flutes_LD(FluteState * flute_p,int d, FLUTE_DTYPE *xs, FLUTE_DTYPE ys[], int *s);
extern Tree flutes_MD(FluteState * flute_p,int d, FLUTE_DTYPE *xs, FLUTE_DTYPE ys[], int *s, int acc);
extern Tree flutes_HD(FluteState * flute_p,int d, FLUTE_DTYPE *xs, FLUTE_DTYPE ys[], int *s, int acc);
extern Tree flutes_RDP(FluteState * flute_p,int d, FLUTE_DTYPE *xs, FLUTE_DTYPE ys[], int *s, int acc);

#if REMOVE_DUPLICATE_PIN==1
  #define flutes_wl(flute_xz, d, xs, ys, s, acc) flutes_wl_RDP(flute_xz, d, xs, ys, s, acc) 
  #define flutes(flute_xz, d, xs, ys, s, acc) flutes_RDP(flute_xz, d, xs, ys, s, acc) 
#else
  #define flutes_wl(flute_xz, d, xs, ys, s, acc) flutes_wl_ALLD(flute_xz, d, xs, ys, s, acc) 
  #define flutes(flute_xz, d, xs, ys, s, acc) flutes_ALLD(flute_xz, d, xs, ys, s, acc) 
#endif

#define flutes_wl_ALLD(flute_xz, d, xs, ys, s, acc) flutes_wl_LMD(flute_xz, d, xs, ys, s, acc)

#if defined(USE_FLUTE_HD)
#define flutes_ALLD(flute_xz, d, xs, ys, s, acc) \
    (d<=FLUTE_D ? flutes_LD(flute_xz, d, xs, ys, s) \
          : (d<=D1(acc) ? flutes_MD(flute_xz, d, xs, ys, s, acc) \
                        : flutes_HD(flute_xz, d, xs, ys, s, acc)))
#else
#define flutes_ALLD(flute_xz, d, xs, ys, s, acc) flutes_LMD(flute_xz, d, xs, ys, s, acc)
#endif

#define flutes_wl_LMD(flute_xz, d, xs, ys, s, acc) \
    (d<=FLUTE_D ? flutes_wl_LD(flute_xz, d, xs, ys, s) : flutes_wl_MD(flute_xz, d, xs, ys, s, acc))
#define flutes_LMD(flute_xz, d, xs, ys, s, acc) \
    (d<=FLUTE_D ? flutes_LD(flute_xz, d, xs, ys, s) : flutes_MD(flute_xz, d, xs, ys, s, acc))

#ifdef __cplusplus
} ;
#endif /* __cplusplus */

#endif /* FLUTE_H */
