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
	int		get_x(void){return this->_x;}
	int		get_y(void){return this->_y;}
	int		get_scrapAmount(void){return this->_scrapAmount;}
	int		get_owner(void){return this->_owner;}
	int		get_units(void){return this->_units;}
	bool	get_recycler(void){return this->_recycler;}
	bool	get_canbuild(void){return this->_canBuild;}
	bool	get_canspawn(void){return this->_canSpawn;}
	bool	get_inRangeOfRecycler(void){return this->_inRangeOfRecycler;}
};

/* PLAYER */
class Player {
private:
	int	_matter;
public:
	Player(void):_matter(0){}
	~Player(void){}
};

/* FUNCTIONS */
void	setMap(Position **Map, int height, int width){
for (int i = 0; i < height; i++){
	for (int j = 0; j < width; j++){
		int scrapAmount;
		int owner; // 1 = me, 0 = foe, -1 = neutral
		int units;
		int recycler;
		int canBuild;
		int canSpawn;
		int inRangeOfRecycler;
		std::cin >> scrapAmount >> owner >> units >> recycler >> canBuild >> canSpawn >> inRangeOfRecycler; std::cin.ignore();
		Map[i][j].set_x(j);
		Map[i][j].set_y(i);
		Map[i][j].set_scrapAmount(scrapAmount);
		Map[i][j].set_owner(owner);
		Map[i][j].set_units(units);
		Map[i][j].set_recycler(recycler);
		Map[i][j].set_canbuild(canBuild);
		Map[i][j].set_canspawn(canSpawn);
		Map[i][j].set_inRangeOfRecycler(inRangeOfRecycler);
	}
}
	return ;
}


int main(){
	int width;
	int height;
	std::cin >> width >> height; std::cin.ignore();

	Position	**Map = new Position*[height];
	for (int i = 0; i < height; ++i)
		Map[i] = new Position[width];

	Player	myself;
	Player	opponent;

	unsigned int	round = 0;
	while (++round){

		int my_matter;
		int opp_matter;
		std::cin >> my_matter >> opp_matter; std::cin.ignore();

		setMap(Map, height, width);
	}

	for(int i = 0; i < height; ++i)
		delete[] Map[i];
	delete[] Map;

	return (0);
}
