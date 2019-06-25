#include <stdio.h>
#include <stdlib.h>
#include "flute.h"

int main()
{
    int d=0;
    int x[100], y[100];
    FLUTE_TREE flutetree;
    int flutewl;
    
    while (!feof(stdin)) {
        scanf("%d %d\n", &x[d], &y[d]);
        d++;
    }
    FLUTEPTR flute1 = flute_init(POWVFILE, PORTFILE);

    flutetree = flute(flute1, d, x, y, ACCURACY);
    printf("FLUTE wirelength = %d\n", flutetree.length);

    flutewl = flute_wl(flute1, d, x, y, ACCURACY);
    printf("FLUTE wirelength (without RSMT construction) = %d\n", flutewl);
}
