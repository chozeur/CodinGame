/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainBU.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flcarval <flcarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:45:56 by flcarval          #+#    #+#             */
/*   Updated: 2022/04/26 02:45:15 by flcarval         ###   ########.fr       */
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

# define MALLOC_ERROR 1

typedef struct s_vector{
    int x;
    int y;
}   t_vector;

typedef struct s_entity{
    // Unique identifier
    int         id;
    // 0=monster, 1=your hero, 2=opponent hero
    int         type;
    // Position of this entity
    t_vector    position;
    // Ignore for this league; Count down until shield spell fades
    int         shield_life;
    // Ignore for this league; Equals 1 when this entity is under a\
    control spell
    int         is_controlled;
    // Remaining health of this monster
    int         health;
    // Trajectory of this monster
    t_vector    direction;
    // 0=monster with no target yet, 1=monster targeting a base
    int         near_base;
    // Given this monster's trajectory, is it a threat to 1=your base,\
    2=your opponent's base, 0=neither
    int         target;
}   t_entity;

typedef struct s_data{
    // The corner of the map representing your base
    t_vector    base;
    // Your base health
    int         health;
    // Amount of heros and monsters you can see
    int         entity_count;
    t_entity    *Entities;
    t_entity    *Heroes;
    t_entity    *Opponents;
    t_entity    *Monsters;
}   t_data;

t_entity    *set_Heroes(t_entity *Entities);

int main()
{
    t_data  data;
    // Always 3
    int         heroes_per_player;
    // Ignore in the first league; Spend ten mana to cast a spell
    int         mana;
    int         i;

    scanf("%d%d", &(data.base.x), &(data.base.y));
    scanf("%d", &heroes_per_player);
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
        i = 0;
        while (i < heroes_per_player)
        {

            i++;
        }
        free(data.Entities);
    }
    return 0;

}

