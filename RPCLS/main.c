#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct s_player{
	int		num;
	char	sign;
	int		*opponents;
}	t_player;

typedef struct s_data{
	t_player	*Players;
	int			nb_players;
	int			round;
}	t_data;

t_player	set_player(int num, char *sign, int players);
void		play_round(t_data *data);
t_player	*duel(t_player *a_player, t_player *b_player, int round);

int main()
{
	t_data	data;
	int		N;
	scanf("%d", &N);
	t_player	*Players;
	Players = malloc(sizeof(t_player) * N);
	for (int i = 0; i < N; i++) {
		int		num;
		char	sign[2];
		scanf("%d%s", &num, sign);
		Players[i] = set_player(num, sign, N);
	}
	data.nb_players = N;
	data.Players = Players;
	data.round = 0;
	while (data.nb_players > 1)
	{
		fprintf(stderr, "play round %d\n", data.round);
		play_round(&data);
		fprintf(stderr, "played round %d\n", data.round);
		data.round++;
	}
	printf("%d\n", data.Players[0].num);
	for (int i = 0; data.Players[0].opponents[i]; i++) {
		printf("%d\n", data.Players[0].opponents[i]);
		if (data.Players[0].opponents[i + 1])
			printf(" ");
		else
			printf("\n");
	}
	return 0;
}

t_player	set_player(int num, char *sign, int players)
{
	t_player	player;
	int			i;

	player.num = num;
	player.sign = sign[0];
	player.opponents = malloc(sizeof(int) * players);
	i = 0;
	while (i < players)
	{
		player.opponents[i] = 0;
		i++;
	}
}

void		play_round(t_data *data)
{
	t_player	*Winners;
	int			i, j;

	Winners = malloc(sizeof(t_player) * (data->nb_players / 2));
	i = 0;
	j = 0;
	while (i < data->nb_players)
	{
		Winners[j] = *duel(&data->Players[i], &data->Players[i + 1], data->round);
		j++;
		i += 2;
	}
	data->nb_players /= 2;
	free(data->Players);
	data->Players = Winners;
}

t_player	*duel(t_player *a_player, t_player *b_player, int round)
{
	t_player	*win;

	if (a_player->sign == 'C')
	{
		if (b_player->sign == 'P' || b_player->sign == 'L')
			win = a_player;
		else
			win = b_player;
	}
	else if (a_player->sign == 'P')
	{
		if (b_player->sign == 'R' || b_player->sign == 'S')
			win = a_player;
		else
			win = b_player;
	}
	else if (a_player->sign == 'R')
	{
		if (b_player->sign == 'L' || b_player->sign == 'C')
			win = a_player;
		else
			return b_player;
	}
	else if (a_player->sign == 'L')
	{
		if (b_player->sign == 'P' || b_player->sign == 'S')
			win = a_player;
		else
			win = b_player;
	}
	else if (a_player->sign == 'S')
	{
		if (b_player->sign == 'C' || b_player->sign == 'R')
			win = a_player;
		else
			win = b_player;
	}
	else
		fprintf(stderr, "error\n");
	if (win == a_player)
		win->opponents[round] = b_player->num;
	else
		win->opponents[round] = a_player->num;
	return (win);
}
