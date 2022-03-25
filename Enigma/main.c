#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int iinstr(char c, char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
        {
            //printf("i de %c = %d\n", c, i);
            return (i);
        }
        i++;
    }
    return (-1);
}

void    cesar(char *str, int n)
{
    int i;

    i = 0;
    while (str[i])
    {
        str[i] += i + n;
        i++;
    }
}

void    rotorize(char *str, char *rotor)
{
    char    alpha[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        j = iinstr(str[i], alpha);
        //printf("j = %d\trotor[j] = %c\n", j, rotor[j]);
        str[i] = rotor[j];
        //printf("%s\n", str);
        i++;
    }
    //printf("//////////////\n");
}

void    encode(char *str, int n, char **rotors)
{
    int i;

    cesar(str, n);
    //printf("cesar = %s\n",str);
    i = 0;
    while (rotors[i])
    {
        //printf("// %s //\n", rotors[i]);
        rotorize(str, rotors[i]);
        //printf("<<<<%s>>>>\n", str);
        i++;
    }
}

int main()
{
char **rotors;
int j;

rotors = malloc(sizeof(char *) * 4);
if (rotors == NULL)
    return (-1);
j = 0;
while (j < 3)
{
    rotors[j] = malloc(sizeof(char) * 28);
    if (rotors[j] == NULL)
        return (-1);
    j++;
}
rotors[j] = 0;
/*..........................................................*/    
    char operation[257];
    scanf("%[^\n]", operation);
    int nb;
    scanf("%d", &nb); fgetc(stdin);
    int i;
    i = 0;
    while (i < 3) {
        scanf("%[^\n]", rotors[i]); fgetc(stdin);
        //printf("\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n||||||||||||||||||||||||||\n01234567890123456789012345\n||||||||||||||||||||||||||\n");
        //printf("%s\n----------------------------\n", rotors[i]);
        i++;
    }
    char message[1025];
    scanf("%[^\n]", message);
/*..........................................................*/
    //printf("// %s //\n", rotors[0]);
    //printf("// %s //\n", rotors[1]);
    //printf("// %s //\n", rotors[2]);
    if (operation[0] == 'E')
    {
        encode(message, nb, rotors);
    }


    printf("%s\n", message);

    return 0;
}