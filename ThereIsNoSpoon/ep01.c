#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/**
 * Don't let the machines win. You are humanity's last hope...
 **/

typedef struct s_node{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	x3;
	int	y3;
	int	last;
}   t_node;

static t_node	*set_node_nodes(char **strnodes, int height, int width);
static int	isnode(int x1, int y1, t_node *nodes);
static void	set_neighborhood(t_node *nodes, int width);
static void	set_no_neighboor_right(t_node *node, int i);
static void	set_no_neighboor_below(t_node *node, int i);
static void	print_nodes(t_node *nodes);

int main()
{
	// the number of cells on the X axis
	int	width;
	scanf("%d", &width);
	// the number of cells on the Y axis
	int	height;
	scanf("%d", &height); fgetc(stdin);
	char	**strnodes = malloc(sizeof(char *) * height);
	if (!strnodes)
		return (-1);
	for (int i = 0; i < height; i++) {
		// width characters, each either 0 or .
		char	line[32];
		scanf("%[^\n]", line); fgetc(stdin);
		strnodes[i] = strdup(line);
		fprintf(stderr, "%s\n", strnodes[i]);
	}
	t_node	*nodes = set_node_nodes(strnodes, height, width);
	set_neighborhood(nodes, width);
	print_nodes(nodes);
	return 0;
}

static t_node	*set_node_nodes(char **strnodes, int height, int width)
{
	int		i;
	int		j;
	int		k;
	t_node	*nodes;

	if (!(nodes = malloc(sizeof(t_node) * ((height * width) + 1))))
		return (NULL);
	i = 0;
	k = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			fprintf(stderr, "%c", strnodes[i][j]);
			if (strnodes[i][j] == '0')
			{
				nodes[k].x1 = j;
				nodes[k].y1 = i;
				nodes[k].last = 0;
				set_no_neighboor_right(&nodes[k], -2);
				set_no_neighboor_below(&nodes[k], -2);
				k++;
			}
			j++;
		}
		fprintf(stderr, "\n");
		i++;
	}
	nodes[k].last = 1;
	return (nodes);
}

static int	isnode(int x1, int y1, t_node *nodes)
{
	int	i;

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

static void	set_neighborhood(t_node *nodes, int width)
{
	int	i;
	int	j;

	i = 0;
	while (!nodes[i].last)
	{
		j = 1;
		while (j < width || j == 1)
		{
			if (isnode(nodes[i].x1 + j, nodes[i].y1, nodes))
			{
				if (nodes[i].x2 == -2 && nodes[i].y2 == -2)
				{
					nodes[i].x2 = nodes[i].x1 + j;
					nodes[i].y2 = nodes[i].y1;
				}
			}
			else if (nodes[i].x2 == -2 && nodes[i].y2 == -2 && j >= width - 1)
				set_no_neighboor_right(&nodes[i], -1);
			if (isnode(nodes[i].x1, nodes[i].y1 + j, nodes))
			{
				if (nodes[i].x3 == -2 && nodes[i].y3 == -2)
				{
					nodes[i].x3 = nodes[i].x1;
					nodes[i].y3 = nodes[i].y1 + j;
				}
			}
			else if (nodes[i].x3 == -2 && nodes[i].y3 == -2 && j >= width - 1)
				set_no_neighboor_below(&nodes[i], -1);
			j++;
		}
		i++;
	}
}

static void	set_no_neighboor_right(t_node *node, int i)
{
	node->x2 = i;
	node->y2 = i;
}

static void	set_no_neighboor_below(t_node *node, int i)
{
	node->x3 = i;
	node->y3 = i;
}

static void	print_nodes(t_node *nodes)
{
	int	i;

	i = 0;
	while (!nodes[i].last)
	{
		printf("%d %d %d %d %d %d\n", nodes[i].x1, nodes[i].y1, \
			nodes[i].x2, nodes[i].y2, nodes[i].x3, nodes[i].y3);
		i++;
	}
}
