#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/**
 * Don't let the machines win. You are humanity's last hope...
 **/

typedef struct s_node{
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
    int last;
}   t_node;

static t_node *set_node_nodes(char **strnodes, int height, int width);
static int isnode(int x1, int y1, t_node *nodes);
static void set_neighborhood(t_node *nodes);
static void set_no_neighboor(t_node node);
static void print_nodes(t_node *nodes);

int main()
{
    // the number of cells on the X axis
    int width;
    scanf("%d", &width);
    // the number of cells on the Y axis
    int height;
    scanf("%d", &height); fgetc(stdin);
    char **strnodes = malloc(sizeof(char *) * height);
    if (!strnodes)
        return (-1);
    for (int i = 0; i < height; i++) {
        // width characters, each either 0 or .
        char line[32];
        scanf("%[^\n]", line); fgetc(stdin);
        strnodes[i] = line;
        fprintf(stderr, "%s\n", strnodes[i]);
    }
    t_node *nodes = set_node_nodes(strnodes, height, width);
    set_neighborhood(nodes);
    print_nodes(nodes);
    return 0;
}

static t_node *set_node_nodes(char **strnodes, int height, int width)
{
    int i;
    int j;
    t_node *nodes;

    if (!(nodes = malloc(sizeof(t_node) * ((height * width) + 1))))
        return (NULL);
    i = 0;
    while (i < height)
    {
        j = 0;
        while (strnodes[i][j])
        {
            if (strnodes[i][j] == '0')
            {
                nodes[i].x1 = j;
                nodes[i].y1 = i;
                nodes[i].last = 0;
            }
            j++;
        }
        i++;
    }
    nodes[i].last = 1;
    return (nodes);
}

static int isnode(int x1, int y1, t_node *nodes)
{
    int i;

    i = 0;
    while (!nodes[i].last)
    {
        if (nodes[i].x1 == x1)
            if (nodes[i].y1 == y1)
                return (1);
        i++;
    }
    return (0);
}

static void set_neighborhood(t_node *nodes)
{
    int i;

    i = 0;
    while (!nodes[i].last)
    {
        set_no_neighboor(nodes[i]);
        if (isnode(nodes[i].x1 + 1, nodes[i].y1, nodes))
        {
            nodes[i].x2 = nodes[i].x1 + 1;
            nodes[i].y2 = nodes[i].y1;
        }
        else
        {
            nodes[i].x2 = -1;
            nodes[i].y2 = -1;
        }
        if (isnode(nodes[i].x1, nodes[i].y1 + 1, nodes))
        {
            nodes[i].x3 = nodes[i].x1;
            nodes[i].y3 = nodes[i].y1 + 1;
        }
        else
        {
            nodes[i].x3 = -1;
            nodes[i].y3 = -1;
        }
        i++;
    }
}

static void set_no_neighboor(t_node node)
{
    node.x2 = -1;
    node.y2 = -1;
    node.x3 = -1;
    node.y3 = -1;
}

static void print_nodes(t_node *nodes)
{
    int i;

    i = 0;
    while (!nodes[i].last)
    {
        fprintf(stderr, "%d %d %d %d %d %d\n", nodes[i].x1, nodes[i].y1, nodes[i].x2, nodes[i].y2, nodes[i].x3, nodes[i].y3);
        i++;
    }
}
