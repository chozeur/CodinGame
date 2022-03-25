#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

long smallest(long *tab, long size)
{
    long i = 0;
    long res = INT_MAX;

    while (i < size)
    {
        if (tab[i] < res)
            res = tab[i];
        i++;
    }
    return (res);
}

long second(long *tab, long size)
{
    long min = smallest(tab, size);
    long i = 0;
    long d = -1;
    long res = INT_MAX;

    while (i < size)
    {
        if (tab[i] == min)
        {
            if (++d)
                return (min);
        }
        else if (tab[i] < res)
            res = tab[i];
    }
    return (res);
}

long main()
{
    long n;
    scanf("%d", &n);
    long *tab = malloc(sizeof(long) * n);
    for (long i = 0; i < n; i++) {
        long num;
        scanf("%d", &num);
        tab[i] = num;
    }
    long min = smallest(tab, n);
    long res = second(tab, n);
    printf("%d", res);
    return 0;
}
