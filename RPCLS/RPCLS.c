#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_player
{
	int		num;
	char	*sign;
	t_list	**opp;
}	t_player;

typedef struct s_data
{
	int		nb_players;
	t_list	**players;
}	t_data;

//	LISTS
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

//	UTILS
t_player	*create_player(int init);
void		play_game(void);
t_list		**play_round(void);
t_player	*duel(t_player *a, t_player *b);
t_player	*duplicate_player(t_player *player);

t_data	g_data;

int main(int ac, char **av, char **envp)
{
	// g_data.players = NULL;
	scanf("%d", &g_data.nb_players);
	for (int i = 0; i < g_data.nb_players; i++) {
		ft_lstadd_back(g_data.players, ft_lstnew(create_player(1)));
	}
	play_game();
	return 0;
}

t_player	*create_player(int init)
{
	t_player	*new;

	new->sign = malloc(sizeof(char) * 64);
	if (init)
		scanf("%d%s", &new->num, new->sign);
	new->opp = NULL;
	return (new);
}

void	play_game(void)
{
	int	round;

	round = g_data.nb_players;
	while (round / 2)
	{
		g_data.players = play_round();
		round /= 2;
	}
	printf("%d\n", ((t_player *)((*g_data.players)->content))->num);
}

t_list	**play_round(void)
{
	t_list	**new = NULL;
	t_list	*a;
	t_list	*b;

	a = *g_data.players;
	b = (*g_data.players)->next;
	while (a)
	{
		t_list	*_new = ft_lstnew(duel(a->content, b->content));
		if (duel(a->content, b->content)->num == ((t_player *)(a->content))->num)
			ft_lstadd_back(((t_player *)(_new->content))->opp, ft_lstnew(duplicate_player(b->content)));
		else
			ft_lstadd_back(((t_player *)(_new->content))->opp, ft_lstnew(duplicate_player(a->content)));
		ft_lstadd_back(new, _new);
		a = a->next->next;
		b = b->next->next;
	}
	return (new);
}

/*
	Rock (R) wins L C
	Paper (P) wins R S
	sCissors (C) P L
	Lizard (L) S P
	Spock (S) C R
*/

t_player	*duel(t_player *a, t_player *b)
{
	if (a->sign[0] == 'R')
	{
		if (b->sign[0] == 'R')
		{
			if ((a->num < b->num))
				return (duplicate_player(a));
			else
				return (duplicate_player(b));
		}
		if (b->sign[0] == 'L' \
			|| b->sign[0] == 'C')
			return (duplicate_player(a));
	}
	else if (a->sign[0] == 'P')
	{
		if (b->sign[0] == 'P')
		{
			if ((a->num < b->num))
				return (duplicate_player(a));
			else
				return (duplicate_player(b));
		}
		if (b->sign[0] == 'R' \
			|| b->sign[0] == 'S')
			return (duplicate_player(a));
	}
	else if (a->sign[0] == 'C')
	{
		if (b->sign[0] == 'C')
		{
			if ((a->num < b->num))
				return (duplicate_player(a));
			else
				return (duplicate_player(b));
		}
		if (b->sign[0] == 'P' \
			|| b->sign[0] == 'L')
			return (duplicate_player(a));
	}
	else if (a->sign[0] == 'L')
	{
		if (b->sign[0] == 'L')
		{
			if ((a->num < b->num))
				return (duplicate_player(a));
			else
				return (duplicate_player(b));
		}
		if (b->sign[0] == 'S' \
			|| b->sign[0] == 'P')
			return (duplicate_player(a));
	}
	else if (a->sign[0] == 'S')
	{
		if (b->sign[0] == 'S')
		{
			if ((a->num < b->num))
				return (duplicate_player(a));
			else
				return (duplicate_player(b));
		}
		if (b->sign[0] == 'C' \
			|| b->sign[0] == 'R')
			return (duplicate_player(a));
	}
	else
		return (NULL);
	return (duplicate_player(b));
}

t_player	*duplicate_player(t_player *player)
{
	t_player	*new;

	new = create_player(0);
	new->num = player->num;
	new->sign[0] = player->sign[0];
	new->sign[1] = player->sign[1];
	new->sign[2] = player->sign[2];
	new->opp = player->opp;
	return (new);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

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

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	*alst = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*i;
	t_list	*j;

	if (lst)
	{
		i = *lst;
		while (i)
		{
			j = i->next;
			ft_lstdelone(i, del);
			i = j;
		}
		*lst = NULL;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	(*del)(lst->content);
	free(lst);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*i;

	i = lst;
	while (i)
	{
		(*f)(i->content);
		i = i->next;
	}
}

t_list	*ft_lstlast(t_list *lst)
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

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;

	(void)del;
	if (lst == NULL)
		return (NULL);
	res = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	// res = malloc(sizeof(t_list));
	// if (res == NULL)
	// 	return (NULL);
	res->content = content;
	res->next = NULL;
	return (res);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*count;
	int		i;

	count = lst;
	i = 0;
	while (count != NULL)
	{
		count = count->next;
		i++;
	}
	return (i);
}
