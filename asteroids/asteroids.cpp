#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <tgmath.h>

using namespace std;

int	g_nbAsteroids;

struct	s_vect{
	int	x;
	int	y;
};

/* ASTEROID */

class	Asteroid{

public:
	bool	set_pos(int posId, int x, int y);
	s_vect	get_pos(int posId) const;
	bool	set_id(char id);
	char	get_id(void) const;
	bool	calculate_pos3(int t1, int t2, int t3);
	Asteroid();
	~Asteroid();

private:
	char	_id;
	s_vect	_pos1;
	s_vect	_pos2;
	s_vect	_pos3;
};

bool	Asteroid::set_pos(int posId, int x, int y)
{
	if (posId == 1)
	{
		this->_pos1.x = x;
		this->_pos1.y = y;
	}
	else if (posId == 2)
	{
		this->_pos2.x = x;
		this->_pos2.y = y;
	}
	else
	{
		this->_pos3.x = x;
		this->_pos3.y = y;
	}
	return (true);
}

s_vect	Asteroid::get_pos(int posId) const
{
	if (posId == 1)
		return (this->_pos1);
	else if (posId == 2)
		return (_pos2);
	else
		return (_pos3);
}

bool	Asteroid::set_id(char id)
{
	this->_id = id;
	return (true);
}

char	Asteroid::get_id(void) const
{
	return (this->_id);
}

bool	Asteroid::calculate_pos3(int t1, int t2, int t3)
{
	s_vect	move;
	float	fact = (t3 - t2) / (t2 - t1);

	move.x = this->_pos2.x - this->_pos1.x;
	move.y = this->_pos2.y - this->_pos1.y;
	this->_pos3.x = this->_pos2.x + floor(fact * move.x);
	this->_pos3.y = this->_pos2.y + floor(fact * move.y);
	return (true);
}

Asteroid::Asteroid(void)
{
	return ;
}

Asteroid::~Asteroid(void)
{
	return ;
}

/* PICTURE */

class	Picture{

public:
	bool	set_h(int h);
	int		get_h(void) const;
	bool	set_t(int t);
	int		get_t(void) const;
	bool	set_pic(string *pic);
	string	*get_pic(void) const;
	Picture(int h, int t, string *pic);
	~Picture(void);

private:
	int		_h;
	int		_t;
	string	*_pic;
};

bool	Picture::set_h(int h)
{
	this->_h = h;
	return (true);
}

int		Picture::get_h(void) const
{
	return (this->_h);
}

bool	Picture::set_t(int t)
{
	this->_t = t;
	return (true);
}

int		Picture::get_t(void) const
{
	return (this->_t);
}

bool	Picture::set_pic(string *pic)
{
	this->_pic = pic;
	return (true);
}

string	*Picture::get_pic(void) const
{
	return (this->_pic);
}

Picture::Picture(int h, int t, string *pic): _h(h), _t(t), _pic(pic)
{
	return ;
}

Picture::~Picture(void)
{
	delete[] this->_pic;
	return ;
}

/* MAIN */

int			count_asteroids(string *picture, int h);
Asteroid	*getAsteroids(Picture pic1, Picture pic2);
bool		genThirdPic(Asteroid *asteroids, int w, int h);
char		*whosThere(Asteroid *asteroids, int x, int y);

int	main()
{
	int w, h, t1, t2, t3;
	cin >> w >> h >> t1 >> t2 >> t3; cin.ignore();
	string	*first_pic = new string[h];
	string	*second_pic = new string[h];
	for (int i = 0; i < h; i++)
		cin >> first_pic[i] >> second_pic[i]; cin.ignore();
	Picture	pic1(h, t1, first_pic), pic2(h, t2, second_pic), pic3(h, t3, NULL);
	Asteroid	*asteroids = getAsteroids(pic1, pic2);
	if (!asteroids)
		return (1);
	g_nbAsteroids = count_asteroids(pic1.get_pic(), pic1.get_h());
	for (int i = 0; i < g_nbAsteroids; i++)
		asteroids[i].calculate_pos3(t1, t2, t3);
	if (!genThirdPic(asteroids, w, h))
		return (1);
	delete[] asteroids;
	return (0);
}

int	count_asteroids(string *picture, int h)
{
	int	count = 0;

	for (int i = 0; i < h; i++)
		for (int j = 0; picture[i][j]; j++)
			if (isalpha(picture[i][j]))
				count++;
	return (count);
}

Asteroid	*getAsteroids(Picture pic1, Picture pic2)
{
	Asteroid	*asteroids = new Asteroid[g_nbAsteroids];
	int	k = 0;
	if (!asteroids)
		return (NULL);
	for (int i = 0; i < pic1.get_h(); i++)
		for (int j = 0; pic1.get_pic()[i][j]; j++)
			if (isalpha(pic1.get_pic()[i][j]))
			{
				asteroids[k].set_id(pic1.get_pic()[i][j]);
				asteroids[k].set_pos(1, j, i);
				k++;
			}
	for (int i = 0; i < pic2.get_h(); i++)
		for (int j = 0; pic2.get_pic()[i][j]; j++)
			if (isalpha(pic2.get_pic()[i][j]))
				for (int l = 0; l < g_nbAsteroids; l++)
					if (asteroids[l].get_id() == pic2.get_pic()[i][j])
						asteroids[l].set_pos(2, j, i);
	return (asteroids);
}

bool	genThirdPic(Asteroid *asteroids, int w, int h)
{
	string	*pic3 = new string[h];
	if (!pic3)
		return (false);
	for (int i = 0; i < h; i++)
	{
		pic3[i].clear();
		for (int j = 0; j < w; j++)
			pic3[i].append(whosThere(asteroids, j, i));
		cout << pic3[i] << endl;
	}
	return (true);
}

char	*whosThere(Asteroid *asteroids, int x, int y)
{
	char	I[2] = {'\0', '\0'};

	for (int i = 0; i < g_nbAsteroids; i++)
	{
		if (asteroids[i].get_pos(3).x == x && asteroids[i].get_pos(3).y == y)
		{
			if (!I[0])
				I[0] = asteroids[i].get_id();
			else
				(I[0] < asteroids[i].get_id()) ? I[0] = I[0] : I[0] = asteroids[i].get_id();
		}
	}
	if (!I[0])
		I[0] = '.';
	return (I);
}
