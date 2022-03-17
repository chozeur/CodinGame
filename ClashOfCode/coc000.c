#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int N;
    scanf("%d", &N);
    int W;
    scanf("%d", &W); fgetc(stdin);
    for (int i = 0; i < W; i++) {
        char ROW[257];
        scanf("%[^\n]", ROW); fgetc(stdin);
    }

    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    printf("word1 word2\n");

    return 0;
}