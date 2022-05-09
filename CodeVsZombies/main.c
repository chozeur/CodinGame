/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   main.c											 :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: flcarval <flcarval@student.42.fr>		  +#+  +:+	   +#+		      */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2022/04/19 03:42:27 by flcarval		  #+#	#+#			      */
/*   Updated: 2022/05/09 02:16:49 by flcarval		 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

# define CHECK fprintf(stderr, "check\n");


typedef struct s_vector{
	int	x;
	int	y;
}	t_vector;

typedef struct s_zombie{
	int			id;
	t_vector	pos;
	t_vector	next_pos;
}	t_zombie;

typedef struct s_human{
	int			id;
	t_vector	pos;
	int			fear;
}	t_human;

typedef struct s_data{
	t_zombie	Zombies[2048];
	t_human		Humans[2048];
	int			zombie_count;
	int			human_count;
	int			round;
	t_vector	last_move;
	t_vector	ash_pos;
}	t_data;

static void		loop_get_humans(int human_count, t_data *data);
static void		loop_get_zombies(int zombie_count, t_data *data);
static t_zombie	*id_to_zombie(int id, t_zombie *Zombies, int zombie_count);
static int		fear_indice(t_human human, t_zombie *Zombies, int zombie_count);
static double	distance(t_vector a, t_vector b);
static void		set_fears(t_human *Humans, t_zombie *Zombies, int human_count, int zombie_count);
static void		move(t_data *data);
static t_zombie	*closest(t_vector target, t_zombie *Zombies, int zombie_count);

int main()
{
	t_data	data;

	data.round = 0;
	data.last_move.x = 0;
	data.last_move.y = 0;
	while (1)
	{
		data.round++;
		scanf("%d%d", &data.ash_pos.x, &data.ash_pos.y);
		scanf("%d", &data.human_count);
		loop_get_humans(data.human_count, &data);
		scanf("%d", &data.zombie_count);
		loop_get_zombies(data.zombie_count, &data);
		set_fears(data.Humans, data.Zombies, data.human_count, data.zombie_count);
		move(&data);
	}
	return (0);
}

static void	loop_get_humans(int human_count, t_data *data)
{
	int	human_id;
	int	human_x;
	int	human_y;

	for (int i = 0; i < human_count; i++) {
		scanf("%d%d%d", &human_id, &human_x, &human_y);
		data->Humans[i].id = human_id;
		fprintf(stderr, "[loop_get_humans] Humans[%d].id = %d\n", i, data->Humans[i].id);
		data->Humans[i].pos.x = human_x;
		data->Humans[i].pos.y = human_y;
	}
}

static void	loop_get_zombies(int zombie_count, t_data *data)
{
	int	zombie_id;
	int	zombie_x;
	int	zombie_y;
	int	zombie_xnext;
	int	zombie_ynext;

	for (int i = 0; i < zombie_count; i++) {
		scanf("%d%d%d%d%d", &zombie_id, &zombie_x, &zombie_y, &zombie_xnext, &zombie_ynext);
		data->Zombies[i].id = zombie_id;
		data->Zombies[i].pos.x = zombie_x;
		data->Zombies[i].pos.y = zombie_y;
		data->Zombies[i].next_pos.x = zombie_xnext;
		data->Zombies[i].next_pos.y = zombie_ynext;
	}
}

static int	fear_indice(t_human human, t_zombie *Zombies, int zombie_count)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (i < zombie_count)
	{
		res += distance(Zombies[i].next_pos, human.pos);
		i++;
	}
	res /= zombie_count;
	fprintf(stderr, "[fear_indice] fear = %d\n", res);
	return (res * (-1));
}

static t_zombie	*id_to_zombie(int id, t_zombie *Zombies, int zombie_count)
{
	int	i;

	i = 0;
	while (i < zombie_count)
	{
		fprintf(stderr, "id = %d zombie[%d].id = %d\n", id, i, Zombies[i].id);
		if (Zombies[i].id == id)
			return (&Zombies[i]);
		i++;
	}
	fprintf(stderr, "[id _to_zombie] : error\n");
	return (NULL);
}

static double	distance(t_vector a, t_vector b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) * 1.0));
}

static void		set_fears(t_human *Humans, t_zombie *Zombies, int human_count, int zombie_count)
{
	int	i;

	i = 0;
	while (i < human_count)
	{
		Humans[i].fear = fear_indice(Humans[i], Zombies, zombie_count);
		i++;
	}
}

static void		move(t_data *data)
{
	// if (data->round < 16)
	// 		printf("%d %d\n", data->Humans[0].pos.x, data->Humans[0].pos.y);
	// else
	// 		printf("%d %d\n", data->Zombies[0].pos.x, data->Zombies[0].pos.y); // Your destination coordinates

	fprintf(stderr, "in [move]\n");
	int			min_fear;
	int			i;
	int			id;
	t_vector	move;
	static int			keep = 0;

	min_fear = 0;
	i = 0;
	while (i < data->human_count)
	{
		CHECK
		fprintf(stderr, "i = %d human_count = %d\n", i, data->human_count);
		if (data->Humans[i].fear < min_fear)
		{
			min_fear = data->Humans[i].fear;
			id = data->Humans[i].id;
			fprintf(stderr, "[move] id = %d\n", data->Humans[i].id);
		}
		i++;
	}
	move = data->Humans[id].pos;
	fprintf(stderr, "[move] min_fear = %d\n", min_fear);
	if ((data->ash_pos.x == move.x && data->ash_pos.y == move.y)/* || \
		(closest(data->ash_pos, data->Zombies, data->zombie_count) == closest(data->Humans[id].pos, data->Zombies, data->zombie_count))*/)
		move = closest(data->ash_pos, data->Zombies, data->zombie_count)->pos;
	else if (data->last_move.x && data->last_move.y)
	{
		if (keep > 3)
			keep = 0;
		else
			move = data->last_move;
	}
	printf("%d %d\n", move.x, move.y);
	keep++;
	data->last_move = move;
}

static t_zombie	*closest(t_vector target, t_zombie *Zombies, int zombie_count)
{
	int	i;
	int	dist;
	int	id;

	i = 0;
	dist = 19000;
	while (i < zombie_count)
	{
		if (distance(target, Zombies[i].pos) < dist)
			id = i;
		i++;
	}
	return (&Zombies[id]);
}
