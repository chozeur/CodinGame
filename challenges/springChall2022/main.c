/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flcarval <flcarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 00:39:09 by flcarval          #+#    #+#             */
/*   Updated: 2022/04/30 05:43:43 by flcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// In the first league: MOVE <x> <y> | WAIT; \
In later leagues: | SPELL <spellParams>;
// Write an action using printf(). DON'T FORGET THE TRAILING \n
// To debug: //fprintf(stderr, "Debug messages...\n");

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

# define MALLOC_ERROR 111
# define FUNCTION_ERROR 222
# define HERO 1
# define OPPONENT 2
# define MONSTER 0

typedef struct s_vector{
	int x;
	int y;
}	t_vector;

typedef struct s_entity{
	// Unique identifier
	int			id;
	// 0=monster, 1=your hero, 2=opponent hero
	int			type;
	// Position of this entity
	t_vector	position;
	t_vector	defense_position;
	// Ignore for this league; Count down until shield spell fades
	int			shield_life;
	// Ignore for this league; Equals 1 when this entity is under a\
	control spell
	int			is_controlled;
	// Remaining health of this monster
	int			health;
	// Trajectory of this monster
	t_vector	direction;
	// 0=monster with no target yet, 1=monster targeting a base
	int			near_base;
	// Given this monster's trajectory, is it a threat to 1=your base,\
	2=your opponent's base, 0=neither
	int			target;
}	t_entity;

typedef struct s_data{
	// The corner of the map representing your base
	t_vector	base;
	// Your base health
	int		health;
	// Amount of heros and monsters you can see
	int		entity_count;
	t_entity	*Entities;
	t_entity	*Heroes;
	t_entity	*Opponents;
	t_entity	*Monsters;
	int			round;
}	t_data;

int			count_entity(t_data *data, int entity);
void		set_entity(t_data *data, int entity);
void		set_defense_position(t_data *data, int Heroes_i);
int			malloc_entity(t_data *data, int entity);
int			free_entity(t_data *data, int entity);
int			move(t_data *data, int hero);
t_vector	pid_to_pos(t_data *data, int eid);
double		distance(t_vector a, t_vector b);
t_vector	is_spider_close(t_data *data, t_vector pos);
void		print_hero(t_entity hero);

int main()
{
	t_data  data;
	// Always 3
	int		heroes_per_player;
	// Ignore in the first league; Spend ten mana to cast a spell
	int		mana;
	int		i;

	scanf("%d%d", &(data.base.x), &(data.base.y));
	scanf("%d", &heroes_per_player);
	data.round = 0;
	while (1) {
		//fprintf(stderr, "infinite\n");
		i = 0;
		while (i < 2) {
			scanf("%d%d", &(data.health), &mana);
			i++;
		}
		scanf("%d", &(data.entity_count));
		data.Entities = malloc(sizeof(t_entity) * data.entity_count);
		if (!data.Entities)
			return (MALLOC_ERROR);
		i = 0;
		while (i < data.entity_count)
		{
			//fprintf(stderr, "\tentity gathering\n");
			scanf("%d%d%d%d%d%d%d%d%d%d%d", &(data.Entities[i].id), &(data.Entities[i].type), \
				&(data.Entities[i].position.x), &(data.Entities[i].position.y), \
				&(data.Entities[i].shield_life), &(data.Entities[i].is_controlled), \
				&(data.Entities[i].health), \
				&(data.Entities[i].direction.x), &(data.Entities[i].direction.y), \
				&(data.Entities[i].near_base), &(data.Entities[i].target));
			i++;
		}
		set_entity(&data, HERO);
		set_entity(&data, OPPONENT);
		set_entity(&data, MONSTER);
		i = 0;
		//fprintf(stderr, "hpp = %d\n", heroes_per_player);
		while (i < heroes_per_player)
		{
			//fprintf(stderr, "\tmove #%d\n", i);
			move(&data, i);
			printf("MOVE %d %d\n", data.Heroes[i].direction.x, data.Heroes[i].direction.y);
			i++;
			data.round++;
			//fprintf(stderr, "moved\n");
		}
		free(data.Entities);
		free_entity(&data, HERO);
		free_entity(&data, OPPONENT);
		free_entity(&data, MONSTER);
	}
	return 0;
}

int count_entity(t_data *data, int entity)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (i < data->entity_count)
	{
		// //fprintf(stderr, "//count entity #%d\n", entity);
		if (data->Entities[i].type == entity)
			res++;
		i++;
	}
	//fprintf(stderr, "//1 HERO\n2 OPPONENT\n0 MONSTER\n");
	//fprintf(stderr, "//entities %d : %d\n----------------------------------------------\n", entity, res);
	return (res);
}

int malloc_entity(t_data *data, int entity)
{
	if (entity == HERO)
	{
		data->Heroes = malloc(sizeof(t_entity) * count_entity(data, entity));
		if (!data->Heroes)
			return (MALLOC_ERROR);
	}
	else if (entity == OPPONENT)
	{
		data->Opponents = malloc(sizeof(t_entity) * count_entity(data, entity));
		if (!data->Opponents)
			return (MALLOC_ERROR);
	}
	else if (entity == MONSTER)
	{
		data->Monsters = malloc(sizeof(t_entity) * count_entity(data, entity));
		if (!data->Monsters)
			return (MALLOC_ERROR);
	}
	else
		return (FUNCTION_ERROR);
}

int free_entity(t_data *data, int entity)
{
	if (entity == HERO)
		free(data->Heroes);
	else if (entity == OPPONENT)
		free(data->Opponents);
	else if (entity == MONSTER)
		free(data->Monsters);
	else
		return (FUNCTION_ERROR);
}

void	set_entity(t_data *data, int entity)
{
	int i;
	int j;

	if (malloc_entity(data, entity) == FUNCTION_ERROR)
		return (FUNCTION_ERROR);
	i = 0;
	j = 0;
	while (i < count_entity(data, entity))
	{
		//fprintf(stderr, "//set entity #%d", entity);
		if (data->Entities[i].type == entity)
		{
			if (entity == HERO)
			{
				data->Heroes[j] = data->Entities[i];
				set_defense_position(data, j);
			}
			if (entity == OPPONENT)
				data->Opponents[j] = data->Entities[i];
			if (entity == MONSTER)
				data->Monsters[j] = data->Entities[i];
			j++;
		}
		i++;
	}
}

void	set_defense_position(t_data *data, int Heroes_i)
{
	if (Heroes_i == 0)
	{
		data->Heroes[Heroes_i].defense_position.x = 1400;
		data->Heroes[Heroes_i].defense_position.y = 4800;
	}
	if (Heroes_i == 1)
	{
		data->Heroes[Heroes_i].defense_position.x = 4000;
		data->Heroes[Heroes_i].defense_position.y = 3000;
	}
	if (Heroes_i == 2)
	{
		data->Heroes[Heroes_i].defense_position.x = 5000;
		data->Heroes[Heroes_i].defense_position.y = 650;
	}
}

int	 move(t_data *data, int i_Heroes)
{
	t_entity	*hero;

	//fprintf(stderr, "in [move]\n");
	hero = &data->Heroes[i_Heroes];
	print_hero(*hero);
	if (data->round < 15)
	{
		//fprintf(stderr, "\t[move] second if()\n");
		data->Heroes[i_Heroes].direction.x = hero->defense_position.x;
		data->Heroes[i_Heroes].direction.y = hero->defense_position.y;
	}
	else if (is_spider_close(data, hero->position).x != 18000 && is_spider_close(data, hero->position).y != 8900)
	{
		fprintf(stderr, "\t[move] third if()\n");
		data->Heroes[i_Heroes].direction = is_spider_close(data, hero->position);
		fprintf(stderr, "direction.x = %d\ndirection.y = %d\n", data->Heroes[i_Heroes].direction.x, data->Heroes[i_Heroes].direction.y);
	}
	else if (distance(data->base, hero->position) >= 60000)
	{
		//fprintf(stderr, "\t[move] first if()\n");
		data->Heroes[i_Heroes].direction.x = hero->defense_position.x;
		data->Heroes[i_Heroes].direction.y = hero->defense_position.y;
	}
	return (0);
}

double	distance(t_vector a, t_vector b)
{
	//fprintf(stderr, "in [distance]\n");
	//fprintf(stderr, "distance %d/%d - %d/%d = %f\n", a.x, a.y, b.x, b.y, \
		sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) * 1.0));
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) * 1.0));
}

t_vector	pid_to_pos(t_data *data, int eid)
{
	int	i;

	i = 0;
	while (data->Entities[i].id != eid)
	{
		//fprintf(stderr, "//way to pid_to_pos\n");
		i++;
	}
	return (data->Entities[i].position);
}

t_vector	is_spider_close(t_data *data, t_vector pos)
{
	t_vector	res;
	int			i;

	//fprintf(stderr, "in [is_spider_close 1]%d\n", count_entity(data, MONSTER));
	res.x = 18000;
	res.y = 8900;
	i = 0;
	//fprintf(stderr, "in [is_spider_close 1bis]%d\n", i);
	while (i < count_entity(data, MONSTER))
	{
		//fprintf(stderr, "//check is_spider_close\n");
		if (distance(pos, data->Monsters[i].position) <= 8000 \
			&& distance(pos, data->Monsters[i].position) < \
			distance(res, data->Monsters[i].position))
			res = data->Monsters[i].position;
		i++;
	}
	//fprintf(stderr, "in [is_spider_close 2]%d\n", count_entity(data, MONSTER));
	fprintf(stderr, "spider.x = %d\nspider.y = %d\n", res.x, res.y);
	return (res);
}

void	print_hero(t_entity hero)
{
	//fprintf(stderr, "in [print_hero]\n");
	//fprintf(stderr, "--__--__--__--\nid : %d\nhealth : %d\nposition : %d/%d\ndefense position : %d/%d\n",hero.id, hero.health, hero.position.x, hero.position.y, hero.defense_position.x, hero.defense_position.y);
}
