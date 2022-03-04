/*DEBUG --> fprintf(stderr, "Debug messages...\n") */
/*HEADER*/
/*-------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct  s_player{
    int num;
    char c;
    int *opponents;
    struct s_player *next;
}   t_player;

t_player	*ft_lstnew(int num, char c);
    void	ft_lstadd_back(t_player **alst, t_player *new);
t_player	*ft_lstlast(t_player *lst);
    int	    ft_lstsize(t_player *lst);
t_player    *duel(int round, t_player *play_1, t_player *play_2);
t_player    *set_op(int round, t_player *win, t_player *lose);
    void    print_op(t_player *win);
    void	print_list(t_player **alst);
t_player    *play_game(t_player **alst_a);
    void    play_round(int round, t_player **alst_a);
    void	push(t_player *lst_a, t_player **alst_b);
/*-------------------------------------------------------*/
/*MAIN*/
/*-------------------------------------------------------*/
int main()
{
    int N;
    t_player	*lst_a;
    t_player	**alst_a;
    t_player    *win;

    lst_a = NULL;
    alst_a = &lst_a;    
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int NUMPLAYER;
        char SIGNPLAYER[2];
        scanf("%d%s", &NUMPLAYER, SIGNPLAYER);
        lst_a = ft_lstnew(NUMPLAYER, SIGNPLAYER[0]);
        ft_lstadd_back(alst_a, lst_a);
    }
//    print_list(alst_a);
    win = play_game(alst_a);
////////////////////////////////////
    printf("%d\n", win->num);
    print_op(win);
////////////////////////////////////
    return 0;
}
/*-------------------------------------------------------*/
/*FUNCTIONS*/
/*-------------------------------------------------------*/

t_player    *play_game(t_player **alst_a)
{
    int round;

    round = 0;
    while (ft_lstsize(*alst_a) > 2)
    {
        play_round(round, alst_a);
        round++;
    }
    return (duel(round, (*alst_a), (*alst_a)->next));
}

void    play_round(int round, t_player **alst_a)
{
    t_player    *even;
    t_player    *odd;
    t_player	*lst_b;
    t_player	**alst_b;
    t_player    *tof;
    t_player    *tmp;
    
    lst_b = NULL;
    alst_b = &lst_b;
    even = *alst_a;
    odd = (*alst_a)->next;
    while (even)
    {
        push(duel(round, even, odd), alst_b);
        even = even->next->next;
        if (odd->next)
            odd = odd->next->next;
    }
    tof = *alst_a;
    alst_a = alst_b;
    while (tof)
    {
        tmp = tof->next;
        free(tof);
        tof = tmp;
    }
}


t_player    *duel(int round, t_player *play_1, t_player *play_2)
{
    if (play_1->c == 'C')
    {
        if (play_2->c == 'P' || play_2->c == 'L')
            return (set_op(round, play_1, play_2));
        else
            return (set_op(round, play_2, play_1));
    }
    else if (play_1->c == 'P')
    {
        if (play_2->c == 'R' || play_2->c == 'S')
            return (set_op(round, play_1, play_2));
        else
            return (set_op(round, play_2, play_1));
    }
    else if (play_1->c == 'R')
    {
        if (play_2->c == 'L' || play_2->c == 'C')
            return (set_op(round, play_1, play_2));
        else
            return (set_op(round, play_2, play_1));        
    }
    else if (play_1->c == 'L')
    {
        if (play_2->c == 'S' || play_2->c == 'P')
            return (set_op(round, play_1, play_2));
        else
            return (set_op(round, play_2, play_1));        
    }
    else    // 'S'
    {
        if (play_2->c == 'C' || play_2->c == 'R')
            return (set_op(round, play_1, play_2));
        else
            return (set_op(round, play_2, play_1));
    }
}



t_player    *set_op(int round, t_player *win, t_player *lose)
{
    win->opponents[round] = lose->num;
    return (win);
}

void    print_op(t_player *win)
{
    int i;

    i = 0;
    while (win->opponents[i] != INT_MIN)
        printf("%d ", win->opponents[i++]);
}

t_player	*ft_lstnew(int num, char c)
{
	t_player	*res;

	res = malloc(sizeof(t_player));
	if (res == NULL)
		return (NULL);
	res->num = num;
    res->c = c;
	res->next = NULL;
    res->opponents = malloc(sizeof(int) * 2048);
	return (res);
}

t_player	*ft_lstlast(t_player *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (NULL);
}

void	ft_lstadd_back(t_player **alst, t_player *new)
{
	t_player	*last;

	if (alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
	}
}

int	ft_lstsize(t_player *lst)
{
	t_player	*count;
	int			i;

	count = lst;
	i = 0;
	while (count != NULL)
	{
        fprintf(stderr, "here\n");
		count = count->next;
		i++;
	}
	return (i);
}

void	print_list(t_player **alst)
{
	t_player	*player;

	if (!(*alst) || !alst)
		return ;
	player = *alst;
	while (player)
	{
        fprintf(stderr, "player %d\n", player->num);
		player = player->next;
	}
}

void	push(t_player *lst_a, t_player **alst_b)
{
    t_player    *new;

    new = ft_lstnew(lst_a->num, lst_a->c);
    new->opponents = lst_a->opponents;
    ft_lstadd_back(alst_b, new);
}
/*-------------------------------------------------------*/

