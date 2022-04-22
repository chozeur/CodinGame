/* ************************************************************************** */
/*														 */
/*											 :::	  ::::::::	*/
/*	main.c									 :+:	  :+:	:+:	*/
/*										 +:+ +:+		+:+	 */
/*	By: flcarval <flcarval@student.42.fr>		 +#+  +:+		+#+		*/
/*									 +#+#+#+#+#+	+#+			*/
/*	Created: 2022/04/22 00:45:56 by flcarval		 #+#	#+#			*/
/*	Updated: 2022/04/22 22:44:48 by flcarval		###	########.fr		*/
/*														 */
/* ************************************************************************** */


// In the first league: MOVE <x> <y> | WAIT; \
In later leagues: | SPELL <spellParams>;
// Write an action using printf(). DON'T FORGET THE TRAILING \n
// To debug: fprintf(stderr, "Debug messages...\n");

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
t_vector	*is_spider_close(t_data *data, t_vector pos);


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
		while (i < heroes_per_player)
			move(&data, i++);
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
		if (data->Entities[i].type == entity)
			res++;
		i++;
	}
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
		data->Heroes[Heroes_i].defense_position.x = 14000;
		data->Heroes[Heroes_i].defense_position.y = 5000;
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
	t_vector	direction;

	hero = &(data->Heroes[i_Heroes]);
	if (distance(data->base, hero->position) >= 42000)
	{
		direction.x = 0;
		direction.y = 0;
	}
	else if (!is_spider_close(data, hero->position))
	{
		direction.x = hero->defense_position.x;
		direction.y = hero->defense_position.y;
	}
	else if (is_spider_close(data, hero->position))
	{
		direction = *(is_spider_close(data, hero->position));
	}
	printf("MOVE %d %d\n", direction.x, direction.y);
}

double	distance(t_vector a, t_vector b)
{
	return (sqrt(((atof(b.x) - atof(a.x)) * (atof(b.x) - atof(a.x))) + \
		((atof(b.y) - atof(a.y)) * (atof(b.y) - atof(a.y)))));
}

t_vector	pid_to_pos(t_data *data, int eid)
{
	int	i;

	i = 0;
	while (data->Entities[i].id != eid)
		i++;
	return (data->Entities[i].position);
}

t_vector	*is_spider_close(t_data *data, t_vector pos)
{
	t_vector	*res;
	int			i;

	res->x = 17630;
	res->y = 90000;
	i = 0;
	while (i < count_entity(data, MONSTER))
	{
		if (distance(pos, data->Monsters[i].position) <= 2400 \
			&& distance(pos, data->Monsters[i].position) < \
			distance(*res, data->Monsters[i].position))
			*res = data->Monsters[i].position;
		i++;
	}
	if (res->x != 17630 && res->y != 90000)
		return (res);
	return (NULL);
}
