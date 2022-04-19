/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flcarval <flcarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 03:42:27 by flcarval          #+#    #+#             */
/*   Updated: 2022/04/19 04:23:59 by flcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct s_zombie{
	int	id;
	int	x;
	int	y;
	int	xnext;
	int	ynext;
}	t_zombie;

typedef struct s_human{
	int	id;
	int	x;
	int	y;
}	t_human;

typedef struct s_data{
	t_zombie	Zombies[2048];
	t_human		Humans[2048];
}	t_data;

static void	loop_get_humans(int human_count, t_data *data);
static void	loop_get_zombies(int zombie_count, t_data *data);

int main()
{
	t_data	data;
	int	x;
	int	y;
	int	human_count;
	int	zombie_count;

	while (1)
	{
		scanf("%d%d", &x, &y);
		scanf("%d", &human_count);
		loop_get_humans(human_count, &data);
		scanf("%d", &zombie_count);
		loop_get_zombies(zombie_count, &data);

		////////////////////////////////////////////////
		printf("%d %d\n", data.Zombies[0].x, data.Zombies[0].y); // Your destination coordinates
		////////////////////////////////////////////////
	}
	return (0);
}

static void	loop_get_humans(int human_count, t_data *data)
{

	for (int i = 0; i < human_count; i++) {
		int	human_id;
		int	human_x;
		int	human_y;
		scanf("%d%d%d", &human_id, &human_x, &human_y);
		data->Humans[i].id = human_id;
		data->Humans[i].x = human_x;
		data->Humans[i].y = human_y;
	}
}

static void	loop_get_zombies(int zombie_count, t_data *data)
{

	for (int i = 0; i < zombie_count; i++) {
		int	zombie_id;
		int	zombie_x;
		int	zombie_y;
		int	zombie_xnext;
		int	zombie_ynext;
		scanf("%d%d%d%d%d", &zombie_id, &zombie_x, &zombie_y, &zombie_xnext, &zombie_ynext);
		data->Zombies[i].id = zombie_id;
		data->Zombies[i].x = zombie_x;
		data->Zombies[i].y = zombie_y;
		data->Zombies[i].xnext = zombie_xnext;
		data->Zombies[i].ynext = zombie_ynext;
	}
}
