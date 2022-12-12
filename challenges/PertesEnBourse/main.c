#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int bearish(int *vi, int n, int loss);
int bisbearish(int *v, int loss);

int main()
{
    int n;
    scanf("%d", &n);

    int min = INT_MAX;
    int max = INT_MIN;
    int loss = 0;
    int tmp = 0;

    int *v = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        int vn;
        scanf("%d", &vn);
        v[i] = vn;
        if (!i)
        {
            max = v[i];
            min = v[i];
        }
        if (v[i] > max)
        {
            if (loss < tmp)
                tmp = loss;
            loss = 0;
            max = v[i];
            min = v[i];
        }
        if (v[i] < min)
            min = v[i];
        if ((min - max) < loss)
        {
            loss = (min - max);
            if (i + 1 == n && loss < tmp)
                return(printf("%d\n", loss));
        }
    }
    printf("%d\n", tmp);
    return 0;
}
