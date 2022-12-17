#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

unsigned int	round = 0;

struct coord {
	int	x;
	int	y;
	coord(int xi, int yi):x(xi),y(yi){}
	coord	&operator=(const coord &src){
		if (this == &src)
			return (*this);
		this->x = src.x;
		this->y = src.y;
	}
	bool	operator==(const coord pos) const {
		this->x == pos.x && this->y == pos.y ? true : false;
	}
};
std::ostream	&operator<<(std::ostream &os, const coord &pos){
	os << pos.x << ' ' << pos.y;
	return (os);
}

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
	Position(void):	_pos({0,0}),_scrapAmount(0),_owner(0),
					_units(0),_recycler(0),_canBuild(0),
					_canSpawn(0),_inRangeOfRecycler(0){}
	~Position(void){}
	void	set_pos(coord pos){this->_pos = pos;}
	void	set_scrapAmount(int scrapAmount){this->_scrapAmount = scrapAmount;}
	void	set_owner(int owner){this->_owner = owner;}
	void	set_units(int units){this->_units = units;}
	void	set_recycler(bool recycler){this->_recycler = recycler;}
	void	set_canbuild(bool canbuild){this->_canBuild = canbuild;}
	void	set_canspawn(bool canspawn){this->_canSpawn = canspawn;}
	void	set_inRangeOfRecycler(bool inRangeOfRecycler){this->_inRangeOfRecycler = inRangeOfRecycler;}
	coord	get_pos(void) const {return (this->_pos);}
	int		get_scrapAmount(void) const {return (this->_scrapAmount);}
	int		get_owner(void) const {return (this->_owner);}
	int		get_units(void) const {return (this->_units);}
	bool	get_recycler(void) const {return (this->_recycler);}
	bool	get_canbuild(void) const {return (this->_canBuild);}
	bool	get_canspawn(void) const {return (this->_canSpawn);}
	bool	get_inRangeOfRecycler(void) const {return (this->_inRangeOfRecycler);}
	void	printDebug(void) const {
		std::cerr <<
		"================" << this->_pos << '(' << (this->_owner?(this->_owner<0?"HERB/FREE":"MINE"):"OPP") << ')' << "================" << std::endl <<
		"scrapAmmount = " << this->_scrapAmount <<	" | units = " << this->_units << std::endl <<
		"recycler     = " << this->_recycler 	<<	" | canBuild = " << this->_canBuild << std::endl <<
		"canspawn     = " << this->_canSpawn	<<	" | inRangeOfRecycler = " << this->_inRangeOfRecycler << std::endl;
	}
};

/* MAP */
class Map {
private:
	Position	**_mapArray;
	int const	_width;
	int const	_height;
public:
	Map(int width, int height):_width(width),_height(height){
		this->_mapArray = new Position*[height];
		for (int i = 0; i < height; ++i)
			this->_mapArray[i] = new Position[width];
		return ;
	}
	~Map(void){
		for(int i = 0; i < this->_height; ++i)
			delete[] this->_mapArray[i];
		delete[] this->_mapArray;
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
	void		printDebug(void) const {
		for (int i = 0; i < this->_height; ++i)
			for (int j = 0; j < this->_width; ++j)
				this->_mapArray[i][j].printDebug();
	}
	coord		firstCanBuild(void) const {
		for (int i = 0; i < this->_height; ++i)
			for (int j = 0; j < this->_width; ++j)
				if (this->_mapArray[i][j].get_canbuild())
					return (this->_mapArray[i][j].get_pos());
	}
	coord		closeMiddleCanBuild(void) const {
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
		return (closest.get_pos());
	}
	coord		move(coord pos, int robots) const {
		if (!robots)
			throw (std::exception());
		for (int i = 0; i < this->_height && robots; ++i){
			for (int j = 0; j < this->_width && robots; ++j){
				if (this->_mapArray[i][j].get_scrapAmount() > 0){
					std::cout << "MOVE 1 " << pos << ' ' << j << ' ' << i << ';';
					--robots;
				}
			}
		}
	}
	coord		firstCanSpawn(void) const {
		for (int i = 0; i < this->_height; ++i)
			for (int j = 0; j < this->_width; ++j)
				if (this->_mapArray[i][j].get_canspawn())
					return (this->_mapArray[i][j].get_pos());
		throw (std::exception());
	}
	coord		closeMiddleCanSpawn(void) const {
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
		return (closest.get_pos());
	}
};

/* PLAYER */
class Player {
private:
	int			_matter;
	Map const	&_map;
public:
	Player(Map &map):_matter(0), _map(map){}
	~Player(void){}
	void	set_matter(int matter){this->_matter = matter;}
	int		get_matter(void) const {return (this->_matter);}
	void	build(void) const {
		if (round % 4){
			try {
				std::cout << "BUILD " << this->_map.closeMiddleCanBuild() << ';';
			} catch (std::exception &e){std::cerr << "Player::build() : Error";}
		}
	}
	void	move(void) const {
		for (int i = 0; i < this->_map.get_height(); ++i){
			for (int j = 0; j < this->_map.get_width(); ++j){
				try {
					this->_map.move({j,i},this->_map.get_mapArray()[i][j].get_units());
				} catch (std::exception &e){}
			}
		}
	}
	void	spawn(void) const {
		if (round % 2){
			try {
				std::cout << "SPAWN 1 " << this->_map.closeMiddleCanSpawn() << ';';
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

	Map	cmap(width, height);

	Player	myself(cmap);

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
