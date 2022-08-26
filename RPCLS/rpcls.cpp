#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int	g_round = 0;

class	Player{

public:
	bool	set_num(int num);
	int		get_num(void) const;
	bool	set_sign(string sign);
	string	get_sign(void) const;
	bool	init_opponents(int nb_players);
	bool	add_opponent(int opponent_id);
	int		*get_opponents(void);
	Player(void);
	~Player(void);

private:
	int		_num;
	string	_sign;
	int		*_opponents;
};


bool	Player::set_num(int num)
{
	this->_num = num;
	return (true);
}

int	Player::get_num(void) const
{
	return (this->_num);
}

bool	Player::set_sign(string sign)
{
	this->_sign = sign;
	return (true);
}

string	Player::get_sign(void) const
{
	return (this->_sign);
}

bool	Player::init_opponents(int nb_players)
{
	this->_opponents = new int[nb_players];
	if (!this->_opponents)
		return (false);
	return (true);
}

bool	Player::add_opponent(int opponent_id)
{
	this->_opponents[g_round] = opponent_id;
	return (true);
}

int	*Player::get_opponents(void)
{
	return (this->_opponents);
}

Player::Player(void)
{
	return ;
}

Player::~Player(void)
{
	delete[] (this->_opponents);
	return ;
}

Player	*duel(Player *a, Player *b);
Player	*match(Player *a, Player *b);
Player	**play_round(Player **players, int nb_players);

int main(void)
{
	Player	**players;
	int 	n;

	cin >> n; cin.ignore();
	players = new Player*[n];
	if (!players)
		exit(EXIT_FAILURE);
	for (int i = 0; i < n; i++) {
		int numplayer;
		string signplayer;
		cin >> numplayer >> signplayer; cin.ignore();
		players[i] = new Player;
		players[i]->set_num(numplayer);
		players[i]->set_sign(signplayer);
	}
	while (n > 1)
	{
		players = play_round(players, n);
		g_round++;
		n /= 2;
	}
	cout << players[0]->get_num() << endl;
	for (int i = 0; i < g_round; i++)
	{
		cout << players[0]->get_opponents()[i];
		if (i < g_round - 1)
			cout << ' ';
	}
	cout << endl;
	return (0);
}

/*
	Rock (R) wins L C
	Paper (P) wins R S
	sCissors (C) P L
	Lizard (L) S P
	Spock (S) C R
*/

Player	*duel(Player *a, Player *b)
{
	if (a->get_sign()[0] == b->get_sign()[0])
		return (a->get_num() < b->get_num()) ? a : b;
	if (a->get_sign()[0] == 'R')
		return (b->get_sign()[0] == 'L' || b->get_sign()[0] == 'C') ? a : b;
	else if (a->get_sign()[0] == 'P')
		return (b->get_sign()[0] == 'R' || b->get_sign()[0] == 'S') ? a : b;
	else if (a->get_sign()[0] == 'C')
		return (b->get_sign()[0] == 'P' || b->get_sign()[0] == 'L') ? a : b;
	else if (a->get_sign()[0] == 'L')
		return (b->get_sign()[0] == 'S' || b->get_sign()[0] == 'P') ? a : b;
	else if (a->get_sign()[0] == 'S')
		return (b->get_sign()[0] == 'C' || b->get_sign()[0] == 'R') ? a : b;
	else
		return (NULL);
}

Player	*match(Player *a, Player *b)
{
	Player	*winner;

	winner = duel(a, b);
	if (!winner)
		return (NULL);
	if (winner == a)
		winner->add_opponent(b->get_num());
	else
		winner->add_opponent(a->get_num());
	return (winner);
}

Player	**play_round(Player **players, int nb_players)
{
	Player	**next_round;
	int		i, j;

	next_round = new Player*[nb_players / 2];
	if (!next_round)
		return (NULL);
	i = 0;
	j = 0;
	while (i < nb_players)
	{
		next_round[j] = match(players[i], players[i + 1]);
		i += 2;
		j++;
	}
	delete[] players;
	return (next_round);
}
