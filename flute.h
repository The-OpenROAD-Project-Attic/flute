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

#ifdef __cplusplus

extern "C" {

#endif /* __cplusplus */

/*****************************/
/*  User-Defined Parameters  */
/*****************************/
/* Flute is now dynamic #define MAXD 3000   max. degree that can be handled */
#define ACCURACY 3  		// Default accuracy
#define FLUTE_ROUTING 1   	// 1 to construct routing, 0 to estimate WL only
#define LOCAL_REFINEMENT 0      // Suggestion: Set to 1 if ACCURACY >= 5
#define REMOVE_DUPLICATE_PIN 0  // Remove dup. pin for flute_wl() & flute()

/* Types of tables */
#define POWVFILE "POWV9.dat"        // LUT for POWV (Wirelength Vector)
#define POSTFILE "POST9.dat"        // LUT for POST (Steiner Tree)
#define PORTFILE "PORT9.dat"        // LUT for POST (Routing Tree)

#ifndef DTYPE   // Data type for distance
#define DTYPE int
#endif


#ifdef FLUTE_INTERNAL_VARS

#include <flute_int.h>

#else

typedef struct flute_rec * FLUTEPTR ;

#endif /* FLUTE_INTERNAL_VARS */

typedef struct flute_branch_rec {
  DTYPE x, y ;   	// starting point of the branch
  int n ;        	// index of neighbor
} FLUTE_BRANCH, *FLUTE_BRANCHPTR ;

typedef struct flute_tree_rec {	/* in proper packing order */
    FLUTE_BRANCHPTR branch ;   	// array of tree branches
    DTYPE length;   		// total wirelength
    int deg ;   		// degree
} FLUTE_TREE, *FLUTE_TREEPTR ;

// User-Callable Functions
extern FLUTEPTR flute_init( char *wirelength_vector_file, char *steiner_tree_file ) ;
extern void flute_free( FLUTEPTR flute_p ) ;
extern DTYPE flute_wl( FLUTEPTR flute_p,int d, DTYPE *x, DTYPE *y, int acc);

//Macro: DTYPE flutes_wl(int d, DTYPE xs[], DTYPE ys[], int s[], int acc);
extern FLUTE_TREE flute( FLUTEPTR flute_p, int d, DTYPE *x, DTYPE *y, int acc);

// Free memory associated with flute tree.
extern void flute_free_tree( FLUTEPTR flute_p, FLUTE_TREE tree ) ;

//Macro: FLUTE_TREE flutes( FLUTEPTR flute_p,int d, DTYPE *xs, DTYPE *ys, int *s, int acc);
extern DTYPE flute_wirelength( FLUTE_TREE tree_p) ;
extern void flute_printtree( FLUTE_TREE tree_p ) ;
extern void flute_plottree( FLUTE_TREE tree_p ) ;

// Other useful functions
extern DTYPE flutes_wl_LD(FLUTEPTR flute_p,int d, DTYPE *xs, DTYPE *ys, int *s);
extern DTYPE flutes_wl_MD(FLUTEPTR flute_p,int d, DTYPE *xs, DTYPE *ys, int *s, int acc);
extern DTYPE flutes_wl_RDP(FLUTEPTR flute_p,int d, DTYPE *xs, DTYPE ys[], int *s, int acc);
extern FLUTE_TREE flutes_LD(FLUTEPTR flute_p,int d, DTYPE *xs, DTYPE ys[], int *s);
extern FLUTE_TREE flutes_MD(FLUTEPTR flute_p,int d, DTYPE *xs, DTYPE ys[], int *s, int acc);
extern FLUTE_TREE flutes_HD(FLUTEPTR flute_p,int d, DTYPE *xs, DTYPE ys[], int *s, int acc);
extern FLUTE_TREE flutes_RDP(FLUTEPTR flute_p,int d, DTYPE *xs, DTYPE ys[], int *s, int acc);

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
