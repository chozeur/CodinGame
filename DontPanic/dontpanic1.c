/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dontpanic1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flcarval <flcarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 05:50:07 by flcarval          #+#    #+#             */
/*   Updated: 2022/03/17 05:50:09 by flcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct	s_clone{
	int	floor;
	int	pos;
	char	*direction;
}	t_clone;

typedef struct	s_exit{
	int	floor;
	int	pos;
}	t_exit;

typedef struct s_elevator{
	int	floor;
	int	pos;
}	t_elevator;

typedef struct	s_place{
	int	floor;
	int	pos;
}	t_place;

static void			WAIT(void);
static void			BLOCK(void);
static int			go_to_elevator(t_clone clone, t_elevator *Elevators, int nb_elevators);
static t_elevator	*which_elevator(t_clone clone, t_elevator *Elevators, int nb_elevators);
static int			is_good_direction(t_clone clone, t_elevator *target);

int main()
{
    // number of floors
    int nb_floors;
    // width of the area
    int width;
    // maximum number of rounds
    int nb_rounds;
    // floor on which the exit is found
    int exit_floor;
    // position of the exit on its floor
    int exit_pos;
    // number of generated clones
    int nb_total_clones;
    // ignore (always zero)
    int nb_additional_elevators;
    // number of elevators
    int nb_elevators;
    scanf("%d%d%d%d%d%d%d%d", &nb_floors, &width, &nb_rounds, &exit_floor, &exit_pos, &nb_total_clones, &nb_additional_elevators, &nb_elevators);

	t_exit	exit;
	exit.floor = exit_floor;
	exit.pos = exit_pos;

	t_elevator	*Elevators;
	if (!(Elevators = malloc(sizeof(t_elevator) * nb_elevators)))
		return (-1);

    for (int i = 0; i < nb_elevators; i++) {
        // floor on which this elevator is found
        int elevator_floor;
        // position of the elevator on its floor
        int elevator_pos;
        scanf("%d%d", &elevator_floor, &elevator_pos);
		Elevators[i].floor = elevator_floor;
		Elevators[i].pos = elevator_pos;
    }

	t_clone	clone;

    // game loop
	int	round = 0;
    while (1) {
		round++;
		t_place	start;
        // floor of the leading clone
        int clone_floor;
        // position of the leading clone on its floor
        int clone_pos;
        // direction of the leading clone: LEFT or RIGHT
        char direction[11];
        scanf("%d%d%s", &clone_floor, &clone_pos, direction);
		clone.floor = clone_floor;
		clone.pos = clone_pos;
		clone.direction = &direction[0];
		if (round == 1)
		{
			start.floor = clone.floor;
			start.pos = clone.pos;
		}
		if (clone.floor == start.floor && clone.pos == start.pos)
			WAIT();
		else if (go_to_elevator(clone, Elevators, nb_elevators))
			WAIT();
		else
			BLOCK();
    }

    return 0;
}

static int	go_to_elevator(t_clone clone, t_elevator *Elevators, int nb_elevators)
{
	t_elevator	*target;
	static int	state = 0;

	target = which_elevator(clone, Elevators, nb_elevators);
	if (is_good_direction(clone, target))
		return (1);
	return (0);
}

static t_elevator	*which_elevator(t_clone clone, t_elevator *Elevators, int nb_elevators)
{
	int	i;

	i = 0;
	while (i < nb_elevators)
	{
		if (&Elevators[i].floor == clone.floor)
			return (&Elevators[i]);
		i++;
	}
}

static int	is_good_direction(t_clone clone, t_elevator *target)
{
	if (clone.pos > target->pos)
	{
		if (clone.direction[0] == 'L')
			return (1);
		else
			return (0);
	}
	else if (clone.pos < target->pos)
	{
		if (clone.direction[0] == 'R')
			return (1);
		else
			return (0);
	}
	else
		return (-1);
}

static void	WAIT(void)
{
	printf("WAIT\n");
}

static void	BLOCK(void)
{
	printf("BLOCK\n");
}

