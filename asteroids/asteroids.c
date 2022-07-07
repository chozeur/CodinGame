#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*

*/

typedef struct s_vect{
	int	x;
	int	y;
}	t_vect;

typedef struct s_ast{
	char	name;
	t_vect	pos_1;
	t_vect	pos_2;
	t_vect	pos_3;
	t_vect	dir;
}	t_ast;

typedef struct s_data{
	int		W;
	int		H;
	int		T1;
	int		T2;
	int		T3;
	char	**first;
	char	**second;
	char	**third;
	t_ast	*asteroids;
}	t_data;

t_vect	get_pos(char ast, char **map);
t_vect	get_dir(t_vect pos1, t_vect pos2);
int		count_ast(char **map);
t_ast	*set_asteroids(char **first, char **second);
int		is_pos(t_vect pos, int W, int H);
t_vect	*get_next_pos(t_vect before, t_vect dir);
char	**setup_third(int W, int H);

int main()
{
	t_data	data;
	int		i;

	scanf("%d%d%d%d%d", &data.W, &data.H, &data.T1, &data.T2, &data.T3);
	data.third = setup_third(data.W, data.H);
	///////////////////////////////////////////////////////////////
	// get two maps input
	for (int i = 0; i < data.H; i++) {
		scanf("%s%s", data.first[i], data.second[i]);
	}
	///////////////////////////////////////////////////////////////
	// set an ast tab
	data.asteroids = set_asteroids(first);
	///////////////////////////////////////////////////////////////
	// set all t3 positions
	i = 0;
	while (data.asteroids[i])
	{
		if (is_pos(get_next_pos(data.asteroids[i].pos_2, data.asteroids[i].dir), \
			data.W, data.H))
			data.asteroids[i].pos_3 = get_next_pos(data.asteroids[i].pos_2, data.asteroids[i].dir);
		else
		{
			data.asteroids[i].pos_3.x = 0;
			data.asteroids[i].pos_3.y = 0;
		}
		i++;
	}
	///////////////////////////////////////////////////////////////
	
	return 0;
}

t_vect	get_pos(char ast, char **map)
{
	t_vect	pos;

	pos.y = 0;
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			if (map[pos.y][pos.x] == ast)
				return (pos);
			pos.x++;
		}
		pos.y++;
	}
	return (pos);
}

t_vect	get_dir(t_vect pos1, t_vect pos2)
{
	t_vect	dir;

	dir.x = pos2.x - pos1.x;
	dir.y = pos2.y - pos1.y;
	return (dir);
}

int		count_ast(char **map)
{
	int	count = 0;
	int	i, j;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] >= 65 && map[i][j] <= 90)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

t_ast	*set_asteroids(char **first, char **second)
{
	t_ast	*asteroids;
	int		i, j, k;

	*asteroids = calloc(count_ast(first) + 1, sizeof(t_ast));
	i = 0;
	k = 0;
	while (first[i])
	{
		j = 0;
		while (first[i][j])
		{
			if (first[i][j] >= 65 && first[i][j] <= 90)
			{
				asteroids[k].name = first[i][j];
				asteroids[k].pos_1 = get_pos(first[i][j], first);
				asteroids[k].pos_2 = get_pos(first[i][j], second);
				asteroids[k].dir = get_dir(asteroids[k].pos_1, asteroids[k].pos_2);
				k++;
			}
			j++;
		}
		i++;
	}
	return (asteroids);
}

int		is_pos(t_vect pos, int W, int H)
{
	if (pos.x <= W && pos.y <= H)
		return (1);
	return (0);
}

t_vect	*get_next_pos(t_vect before, t_vect dir)
{
	t_vect	*after;

	after->x = before.x + dir.x;
	after->y = before.y + dir.y;
	return (after);
}

char	**setup_third(int W, int H)
{
	char	**doted;
	int		i, j;

	doted = calloc(H + 1, sizeof(cahr *));
	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			doted[i][j] = '.';
			j++;
		}
		i++;
	}
	return (doted);
}
