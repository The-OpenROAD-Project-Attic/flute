#include <stdio.h>
#include <stdlib.h>
#include "flute.h"

int main()
{
    int d=0;
    int x[100], y[100];
    Flute::Tree flutetree;
    int flutewl;
    
    while (!feof(stdin)) {
        scanf("%d %d\n", &x[d], &y[d]);
        d++;
    }
    Flute::FluteState *flute1 = Flute::flute_init(FLUTE_POWVFILE, FLUTE_PORTFILE);

    flutetree = Flute::flute(flute1, d, x, y, FLUTE_ACCURACY);
    printf("FLUTE wirelength = %d\n", flutetree.length);

    flutewl = Flute::flute_wl(flute1, d, x, y, FLUTE_ACCURACY);
    printf("FLUTE wirelength (without RSMT construction) = %d\n", flutewl);
}
