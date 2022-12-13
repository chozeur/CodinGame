#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/* POSITION */
class Position {
private:
	int		_x;
	int		_y;
	int		_scrapAmount;
	int		_owner;
	int		_units;
	bool	_recycler;
	bool	_canBuild;
	bool	_canSpawn;
	bool	_inRangeOfRecycler;
public:
	Position(void):	_x(0),_y(0),_scrapAmount(0),_owner(0),
					_units(0),_recycler(0),_canBuild(0),
					_canSpawn(0),_inRangeOfRecycler(0){}
	~Position(void){}
	void	set_x(int x){this->_x = x;}
	void	set_y(int y){this->_y = y;}
	void	set_scrapAmount(int scrapAmount){this->_scrapAmount = scrapAmount;}
	void	set_owner(int owner){this->_owner = owner;}
	void	set_units(int units){this->_units = units;}
	void	set_recycler(bool recycler){this->_recycler = recycler;}
	void	set_canbuild(bool canbuild){this->_canBuild = canbuild;}
	void	set_canspawn(bool canspawn){this->_canSpawn = canspawn;}
	void	set_inRangeOfRecycler(bool inRangeOfRecycler){this->_inRangeOfRecycler = inRangeOfRecycler;}
	int		get_x(void) const {return (this->_x);}
	int		get_y(void) const {return (this->_y);}
	int		get_scrapAmount(void) const {return (this->_scrapAmount);}
	int		get_owner(void) const {return (this->_owner);}
	int		get_units(void) const {return (this->_units);}
	bool	get_recycler(void) const {return (this->_recycler);}
	bool	get_canbuild(void) const {return (this->_canBuild);}
	bool	get_canspawn(void) const {return (this->_canSpawn);}
	bool	get_inRangeOfRecycler(void) const {return (this->_inRangeOfRecycler);}
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
	void	set_mapArray(void){
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
				this->_mapArray[i][j].set_x(j);
				this->_mapArray[i][j].set_y(i);
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
	void	move(void) const {
		/* ADD HERE */
	}
	void	build(void) const {
		/* ADD HERE */
	}
	void	spawn(void) const {
		/* ADD HERE */
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
	// Player	opponent(cmap);

	unsigned int	round = 0;
	while (++round){

		int my_matter;
		int opp_matter;
		std::cin >> my_matter >> opp_matter; std::cin.ignore();

		cmap.set_mapArray();

		myself.move();
		myself.build();
		myself.spawn();

		std::cout << "WAIT" << std::endl;
	}

	return (0);
}
