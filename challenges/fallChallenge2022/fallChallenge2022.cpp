/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fallChallenge2022.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flcarval <flcarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:46:08 by flcarval          #+#    #+#             */
/*   Updated: 2022/12/18 05:17:55 by flcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

unsigned int	round = 0;

struct coord {
	int	x;
	int	y;
	coord(void):x(0),y(0){}
	coord(int xi, int yi):x(xi),y(yi){}
	coord(coord const &src){*this = src;}
	coord	&operator=(const coord &src){
		if (this == &src)
			return (*this);
		this->x = src.x;
		this->y = src.y;
	}
	bool	operator==(const coord pos) const {
		(this->x == pos.x && this->y == pos.y) ? true : false;
	}
};
std::ostream	&operator<<(std::ostream &os, const coord &pos){
	os << pos.x << ' ' << pos.y;
	return (os);
}
coord	TL, T, TR, L, CTR, R, BL, B, BR;

/* POSITION */
class Position {
private:
	coord	_pos;
	int		_scrapAmount;
	int		_owner;
	int		_units;
	bool	_recycler;
	bool	_canBuild;
	bool	_canSpawn;
	bool	_inRangeOfRecycler;
public:
	Position(void):_pos({0,0}),_scrapAmount(0),_owner(0),
					_units(0),_recycler(0),_canBuild(0),
					_canSpawn(0),_inRangeOfRecycler(0){}
	Position(Position const &src){*this = src;}
	~Position(void){}
	Position	&operator=(Position const &src){
		if (this == &src)
			return (*this);
		this->_pos = src._pos;
		this->_scrapAmount = src._scrapAmount;
		this->_owner = src._owner;
		this->_units = src._units;
		this->_recycler = src._recycler;
		this->_canBuild = src._canBuild;
		this->_canSpawn = src._canSpawn;
		this->_inRangeOfRecycler = src._inRangeOfRecycler;
		return (*this);
	}
	void		set_pos(coord pos){this->_pos = pos;}
	void		set_scrapAmount(int scrapAmount){this->_scrapAmount = scrapAmount;}
	void		set_owner(int owner){this->_owner = owner;}
	void		set_units(int units){this->_units = units;}
	void		set_recycler(bool recycler){this->_recycler = recycler;}
	void		set_canbuild(bool canbuild){this->_canBuild = canbuild;}
	void		set_canspawn(bool canspawn){this->_canSpawn = canspawn;}
	void		set_inRangeOfRecycler(bool inRangeOfRecycler){this->_inRangeOfRecycler = inRangeOfRecycler;}
	coord		get_pos(void) const {return (this->_pos);}
	int			get_scrapAmount(void) const {return (this->_scrapAmount);}
	int			get_owner(void) const {return (this->_owner);}
	int			get_units(void) const {return (this->_units);}
	bool		get_recycler(void) const {return (this->_recycler);}
	bool		get_canbuild(void) const {return (this->_canBuild);}
	bool		get_canspawn(void) const {return (this->_canSpawn);}
	bool		get_inRangeOfRecycler(void) const {return (this->_inRangeOfRecycler);}
	void		printDebug(void) const {
		std::cerr <<
		"================" << this->_pos << '(' << (this->_owner?(this->_owner<0?"HERB/FREE":"MINE"):"OPP") << ')' << "================" << std::endl <<
		"scrapAmmount = " << this->_scrapAmount <<	" | units = " << this->_units << std::endl <<
		"recycler     = " << this->_recycler 	<<	" | canBuild = " << this->_canBuild << std::endl <<
		"canspawn     = " << this->_canSpawn	<<	" | inRangeOfRecycler = " << this->_inRangeOfRecycler << std::endl;
	}
};
std::ostream	&operator<<(std::ostream &os, const Position &pos){
	pos.printDebug();
	return (os);
}

/* MAP */

class	Map {
private:
	Position	**_mapArray;
	int			_width;
	int			_height;
public:
	Map(int width, int height):_width(width),_height(height){
		this->_mapArray = new Position*[height];
		for (int i = 0; i < height; ++i)
			this->_mapArray[i] = new Position[width];
		return ;
	}
	Map(Map const &src):_width(src._width),_height(src._height){*this = src;}
	~Map(void){
		for(int i = 0; i < this->_height; ++i)
			delete[] this->_mapArray[i];
		delete[] this->_mapArray;
	}
	Map			&operator=(Map const &src){
		if (this == &src)
			return (*this);
		for(int i = 0; i < this->_height; ++i)
			delete[] this->_mapArray[i];
		delete[] this->_mapArray;
		this->_mapArray = new Position*[src._height];
		for (int i = 0; i < src._height; ++i)
			this->_mapArray[i] = new Position[src._width];
		for (int i = 0; i < src._height; ++i)
			for (int j = 0; j < src._width; ++j)
				this->_mapArray[i][j] = src._mapArray[i][j];
		this->_width = src._width;
		this->_height = src._height;
	}
	void		set_mapArray(void){
		for (int i = 0; i < this->_height; ++i){
			for (int j = 0; j < this->_width; ++j){
				int scrapAmount;
				int owner; // 1 = me, 0 = foe, -1 = neutral
				int units;
				int recycler;
				int canBuild;
				int canSpawn;
				int inRangeOfRecycler;
				std::cin >> scrapAmount >> owner >> units >> recycler >> canBuild >> canSpawn >> inRangeOfRecycler; std::cin.ignore();
				this->_mapArray[i][j].set_pos({j,i});
				this->_mapArray[i][j].set_scrapAmount(scrapAmount);
				this->_mapArray[i][j].set_owner(owner);
				this->_mapArray[i][j].set_units(units);
				this->_mapArray[i][j].set_recycler(recycler);
				this->_mapArray[i][j].set_canbuild(canBuild);
				this->_mapArray[i][j].set_canspawn(canSpawn);
				this->_mapArray[i][j].set_inRangeOfRecycler(inRangeOfRecycler);
			}
		}
		return ;
	}
	Position	**get_mapArray(void) const {return (this->_mapArray);}
	int			get_width(void) const {return (this->_width);}
	int			get_height(void) const {return (this->_height);}
	Position	coordToPos(coord c) const {
		for (int i = 0; i < this->_height; ++i){
			for (int j = 0; j < this->_width; ++j){
				if (this->_mapArray[i][j].get_pos().x == c.x && this->_mapArray[i][j].get_pos().y == c.y)
					return (this->_mapArray[i][j]);
			}
		}
		throw (std::exception());
	}
	void		printDebug(void) const {
		for (int i = 0; i < this->_height; ++i){
			for (int j = 0; j < this->_width; ++j){
				this->_mapArray[i][j].printDebug();
				std::cerr << "AREA = " << this->area(_mapArray[i][j]) << std::endl;
			}
		}
	}
	Position	firstCanBuild(void) const {
		for (int i = 0; i < this->_height; ++i)
			for (int j = 0; j < this->_width; ++j)
				if (this->_mapArray[i][j].get_canbuild())
					return (this->_mapArray[i][j]);
	}
	Position	closeMiddleCanBuild(void) const {
		int top = 0, bottom = this->_height - 1, left = 0, right = this->_width - 1, dir = 1;
		Position	closest;
		while (top <= bottom && left <= right){
			if (dir == 1){			// moving left->right -> mA[top][i]
				for (int i = left; i <= right; ++i)
					if (this->_mapArray[top][i].get_canbuild())
						closest = this->_mapArray[top][i];
				++top;
				dir = 2;
			}
			else if (dir == 2){		// moving top->bottom -> mA[i][right]
				for (int i = top; i <= bottom; ++i)
					if (this->_mapArray[i][right].get_canbuild())
						closest = this->_mapArray[i][right];
				--right;
				dir = 3;
			}
			else if (dir == 3){		 // moving right->left -> mA[bottom][i]
				for (int i = right; i >= left; --i)
					if (this->_mapArray[bottom][i].get_canbuild())
						closest = this->_mapArray[bottom][i];
				--bottom;
				dir = 4;
			}
			else if (dir == 4){		 // moving bottom->up -> mA[i][left]
				for (int i = bottom; i >= top; --i)
					if (this->_mapArray[i][left].get_canbuild())
						closest = this->_mapArray[i][left];
				++left;
				dir = 1;
			}
		}
		if (closest.get_pos().x == -1)
		{
			std::cerr << closest.get_pos().x << ' ' << closest.get_pos().y << std::endl;
			throw (std::exception());
		}
		return (closest);
	}
	bool		threatened(Position const &pos) const {
		static int	dir = 0;
		coord		check;
		if (dir == 1)
			goto down;
		else if (dir == 2)
			goto left;
		else if (dir == 3)
			goto up;
		else
			goto right;
right:
		check = {pos.get_pos().x + 1,pos.get_pos().y};
		if (!this->coordToPos(check).get_owner() && this->coordToPos(check).get_units() > 0){
			dir = 1;
			return (true);
		}
down:
		check = {pos.get_pos().x,pos.get_pos().y + 1};
		if (!this->coordToPos(check).get_owner() && this->coordToPos(check).get_units() > 0){
			dir = 2;
			return (true);
		}
left:
		check = {pos.get_pos().x - 1,pos.get_pos().y};
		if (!this->coordToPos(check).get_owner() && this->coordToPos(check).get_units() > 0){
			dir = 3;
			return (true);
		}
up:
		check = {pos.get_pos().x,pos.get_pos().y - 1};
		if (!this->coordToPos(check).get_owner() && this->coordToPos(check).get_units() > 0){
			dir = 0;
			return (true);
		}
		throw (std::exception());
	}
	Position	inDanger(void) const {	//	FROM MIDDLE SPIRAL
		int top = 0, bottom = this->_height - 1, left = 0, right = this->_width - 1, dir = 1;
		Position	closest;
		while (top <= bottom && left <= right){
			if (dir == 1){			// moving left->right -> mA[top][i]
				for (int i = left; i <= right; ++i)
					if (this->threatened(this->_mapArray[top][i]))
						closest = this->_mapArray[top][i];
				++top;
				dir = 2;
			}
			else if (dir == 2){		// moving top->bottom -> mA[i][right]
				for (int i = top; i <= bottom; ++i)
					if (this->threatened(this->_mapArray[i][right]))
						closest = this->_mapArray[i][right];
				--right;
				dir = 3;
			}
			else if (dir == 3){		 // moving right->left -> mA[bottom][i]
				for (int i = right; i >= left; --i)
					if (this->threatened(this->_mapArray[bottom][i]))
						closest = this->_mapArray[bottom][i];
				--bottom;
				dir = 4;
			}
			else if (dir == 4){		 // moving bottom->up -> mA[i][left]
				for (int i = bottom; i >= top; --i)
					if (this->threatened(this->_mapArray[i][left]))
						closest = this->_mapArray[i][left];
				++left;
				dir = 1;
			}
		}
		if (closest.get_pos().x == -1)
		{
			std::cerr << closest.get_pos().x << ' ' << closest.get_pos().y << std::endl;
			throw (std::exception());
		}
		return (closest);
	}
	Position	move(Position pos) const {
		if (!pos.get_units())
			throw (std::exception());
		if (round < 4)
			return (this->startDirection(pos));
		try{
			return (this->closestNotOwned(pos));
		} catch (std::exception &e){
			/* go safe */
		}

	}
	Position	closestNotOwned(Position const &pos) const {
		static int	dir = 0;
		coord		check;
		if (dir == 1)
			goto down;
		else if (dir == 2)
			goto left;
		else if (dir == 3)
			goto up;
		else
			goto right;
right:
		check = {pos.get_pos().x + 1,pos.get_pos().y};
		if (this->coordToPos(check).get_owner() != 1 && this->coordToPos(check).get_scrapAmount() > 0){
			dir = 1;
			return (this->coordToPos(check));
		}
down:
		check = {pos.get_pos().x,pos.get_pos().y + 1};
		if (this->coordToPos(check).get_owner() != 1 && this->coordToPos(check).get_scrapAmount() > 0){
			dir = 2;
			return (this->coordToPos(check));
		}
left:
		check = {pos.get_pos().x - 1,pos.get_pos().y};
		if (this->coordToPos(check).get_owner() != 1 && this->coordToPos(check).get_scrapAmount() > 0){
			dir = 3;
			return (this->coordToPos(check));
		}
up:
		check = {pos.get_pos().x,pos.get_pos().y - 1};
		if (this->coordToPos(check).get_owner() != 1 && this->coordToPos(check).get_scrapAmount() > 0){
			dir = 0;
			return (this->coordToPos(check));
		}
		throw (std::exception());
	}
	Position	firstCanSpawn(void) const {
		for (int i = 0; i < this->_height; ++i)
			for (int j = 0; j < this->_width; ++j)
				if (this->_mapArray[i][j].get_canspawn())
					return (this->_mapArray[i][j]);
		throw (std::exception());
	}
	Position	closeMiddleCanSpawn(void) const {
		int top = 0, bottom = this->_height - 1, left = 0, right = this->_width - 1, dir = 1;
		Position	closest;
		while (top <= bottom && left <= right){
			if (dir == 1){			// moving left->right -> mA[top][i]
				for (int i = left; i <= right; ++i)
					if (this->_mapArray[top][i].get_canspawn())
					{
						closest = this->_mapArray[top][i];
						// this->_mapArray[top][i].printDebug();
					}
				++top;
				dir = 2;
			}
			else if (dir == 2){		// moving top->bottom -> mA[i][right]
				for (int i = top; i <= bottom; ++i)
					if (this->_mapArray[i][right].get_canspawn())
					{
						closest = this->_mapArray[i][right];
						// this->_mapArray[i][right].printDebug();
					}
				--right;
				dir = 3;
			}
			else if (dir == 3){		// moving right->left -> mA[bottom][i]
				for (int i = right; i >= left; --i)
					if (this->_mapArray[bottom][i].get_canspawn())
					{
						closest = this->_mapArray[bottom][i];
						// this->_mapArray[bottom][i].printDebug();
					}
				--bottom;
				dir = 4;
			}
			else if (dir == 4){		 // moving bottom->up -> mA[i][left]
				for (int i = bottom; i >= top; --i)
					if (this->_mapArray[i][left].get_canspawn())
					{
						closest = this->_mapArray[i][left];
						// this->_mapArray[i][left].printDebug();
					}
				++left;
				dir = 1;
			}
		}
		if (closest.get_pos().x == -1)
		{
			std::cerr << closest.get_pos().x << ' ' << closest.get_pos().y << std::endl;
			throw (std::exception());
		}
		return (closest);
	}
/* 	void		printpiral(int size) const {
		int x = 0; // current position; x
		int y = 0; // current position; y
		int d = 0; // current direction; 0=RIGHT, 1=DOWN, 2=LEFT, 3=UP
		int c = 0; // counter
		int s = 1; // chain size

		// starting point
		x = ((int)floor(size/2.0))-1;
		y = ((int)floor(size/2.0))-1;

		for (int k=1; k<=(size-1); k++){
			for (int j=0; j<(k<(size-1)?2:3); j++){
				for (int i=0; i<s; i++){
					std::cout << this->get_mapArray()[x][y] << " ";
					c++;

					switch (d){
						case 0: y = y + 1; break;
						case 1: x = x + 1; break;
						case 2: y = y - 1; break;
						case 3: x = x - 1; break;
					}
				}
				d = (d+1)%4;
			}
			s = s + 1;
		}
	}
 */
	std::string	area(Position &pos) const {
		std::string	area("");
		if (pos.get_pos().y <= (this->_height - 1) / 3)
			area += "top";
		else if (pos.get_pos().y >= 2 * (this->_height - 1) / 3 + (this->_height - 1) % 3)
			area += "bottom";
		if (pos.get_pos().x <= (this->_width - 1) / 3)
			area += (area == "" ? "left" : "-left");
		else if (pos.get_pos().x >= 2 * (this->_width - 1) / 3 + (this->_width - 1) % 3)
			area += (area == "" ? "right" : "-right");
		if (area == "")
			area += "center";
		return (area);
	}
	Position	startDirection(Position &pos) const {
		static bool	state = true;
		std::map<std::string, coord>	areaToOppositePos		{{"top-left",BR},{"top",B},{"top-right",BL},
																{"left",R},{"center",CTR},{"right",L},
																{"bottom-left",TR},{"bottom",T},{"bottom-right",TL}};
		std::map<std::string, coord>	areaToSameOppositePos	{{"top-left",BL},{"top",B},{"top-right",BR},
																{"left",BL},{"center",CTR},{"right",TR},
																{"bottom-left",TL},{"bottom",T},{"bottom-right",TR}};
		std::cerr << "startDirection(" << pos.get_pos() << ") = " << this->coordToPos((state ? areaToOppositePos : areaToSameOppositePos)[this->area(pos)]).get_pos() << std::endl;
		state = !state;
		return (this->coordToPos(areaToOppositePos[this->area(pos)]));
	}
};

/* class FifthMap : public Map {
private:
public:
	FifthMap(Map &fullMap, unsigned int const index):Map(index == 4 ? fullMap._width / 5 + fullMap._width % 5 : fullMap._width / 5, fullMap._height),_index(index){
		for (int i = 0; i < this->_height; ++i){
			for (int j = 0; j < this->_width; ++j){
				this->_mapArray[i][j] = fullMap._mapArray[i][j + index * this->_width];
				if (index == 4 && j == this->_width - 1){
					while (j + index * this->_width != fullMap.get_width()){
						this->_mapArray[i][j] = fullMap._mapArray[i][j + index * this->_width];
						++j;
					}
				}
			}
		}
	}
	~FifthMap(void){}
	FifthMap	&operator=(FifthMap const &src){
		if (this == &src)
			return (*this);
		Map::operator=(src);
		this->_index = src._index;
		return (*this);
	}
private:
	FifthMap(void){}
	unsigned int const	_index;
};
*/

/* PLAYER */
class Player {
private:
	int			_matter;
	Map			*_map;
public:
	Player(Map *map):_matter(0), _map(map){}
	Player(Player const &src){*this = src;}
	~Player(void){}
	Player	&operator=(Player const &src){
		if (this == &src)
			return (*this);
		this->_matter = src._matter;
		this->_map = src._map;
	}
	void	set_matter(int matter){this->_matter = matter;}
	int		get_matter(void) const {return (this->_matter);}
	void	build(void) const {
		try {
			std::cerr << "BUILD " << this->_map->inDanger() << ';';
		} catch (std::exception &e){
			if (!(round % 4)){
				try {
					std::cout << "BUILD " << this->_map->closeMiddleCanBuild().get_pos() << ';';
				} catch (std::exception &e){std::cerr << "Player::build() : Error";}
			}
		}
	}
	void	move(void) const {
		for (int i = 0; i < this->_map->get_height(); ++i){
			for (int j = 0; j < this->_map->get_width(); ++j){
				try {
					this->_map->move(this->_map->get_mapArray()[i][j]);
					std::cout << "MOVE " << this->_map->get_mapArray()[i][j].get_units() << ' ' << j << ' ' << i << ' ' << this->_map->move(this->_map->get_mapArray()[i][j]).get_pos() << ';';
				} catch (std::exception &e){}
			}
		}
	}
	void	spawn(void) const {
		if (round % 2){
			try {
				std::cout << "SPAWN 1 " << this->_map->closeMiddleCanSpawn().get_pos() << ';';
			} catch (std::exception &e){std::cerr << "Player::spawn() : Error";}
		}
	}
};

/* FUNCTIONS */

/* MAIN */

int main(void){
	int width;
	int height;
	std::cin >> width >> height; std::cin.ignore();

	TL = {0,0};					T = {(width - 1) / 2,0};					TR = {width - 1,0};
	L  = {0,(height - 1) / 2};	CTR = {(width - 1) / 2,(height - 1) / 2};	R = {width - 1,(height - 1) / 2};
	BL = {0,height - 1};		B = {(width - 1) / 2,height - 1};			BR = {width - 1,height - 1};

	Map	cmap(width, height);

	Player	myself(&cmap);

	while (++round){

		int my_matter;
		int opp_matter;
		std::cin >> my_matter >> opp_matter; std::cin.ignore();
		myself.set_matter(my_matter);
		cmap.set_mapArray();

		myself.build();
		myself.move();
		myself.spawn();
		std::cout << std::endl;
	}

	return (0);
}
