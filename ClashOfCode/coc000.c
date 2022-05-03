#include <stdio.h>
int main()
{
    int H,W,x;
    scanf("%d%d%d", &H, &W, &x); fgetc(stdin);
    for (int i = 0; i < H; i++) {
        char row[W + 1];
        scanf("%[^\n]", row); fgetc(stdin);
        if (row[x]=='\\')
            x++;
        else if (row[x]=='/')
            x--;
    }
    printf("%d",x);
    return 0;
}
