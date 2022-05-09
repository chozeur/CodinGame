/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flcarval <flcarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:58:37 by flcarval          #+#    #+#             */
/*   Updated: 2022/05/09 02:50:08 by flcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int	main(int ac, char **av)
{
	printf("Distance = %f\n", (sqrt(((atof(av[3]) - atof(av[1])) * (atof(av[3]) - atof(av[1]))) + \
		((atof(av[4]) - atof(av[2])) * (atof(av[4]) - atof(av[2]))))));
	return (0);
}
