/* ----------------------------------------------------------------- 
 * Copyright (c) 2019 William Swartz.  UTD.  All rights reserved.
----------------------------------------------------------------- */
#ifndef FLUTE_MALLOC_H
#define FLUTE_MALLOC_H

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif /* HAVE_STDLIB_H */

#ifdef __cplusplus

extern "C" {

#endif /* __cplusplus */

#ifndef UTDMALLOC

#define UTDMALLOC(n, els)              (els *) malloc((n)*sizeof(els))
#define UTDCALLOC(n, els)              (els *) calloc(n, sizeof(els))
#define UTDREALLOC(ar,n,els)           (els *) realloc(ar,(n)*sizeof(els))
#define UTDFREE(els)                   free(els)

#endif /* UTDMALLOC */

#ifdef __cplusplus
} ;
#endif /* __cplusplus */

#endif /* FLUTE_MALLOC_H */
