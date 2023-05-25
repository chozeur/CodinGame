#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class	Cell {

	public:

		Cell(void);
		Cell(int type, int initial_resources, vector<int> neigh);
		Cell(const Cell& src);
		~Cell(void);

		Cell & operator=(const Cell& src);
		bool operator==(const Cell& src) const;

		int			getType(void) const;
		int			getResources(void) const;
		vector<int>	getNeigh(void) const;

		void	setResources(int resources);
		void	setMyAnts(int my_ants);
		void	setOppAnts(int opp_ants);

	private:

		int			_type;
		int			_resources;
		vector<int>	_neigh;
		int			_my_ants;
		int			_opp_ants;
};

Cell::Cell(void) {
	return ;
}

Cell::Cell(int type, int initial_resources, vector<int> neigh) {
	this->_type = type;
	this->_resources = initial_resources;
	this->_neigh = neigh;
	this->_my_ants = 0;
	this->_opp_ants = 0;
	return ;
}

Cell::Cell(const Cell& src) {
	*this = src;
	return ;
}

Cell::~Cell(void) {
	return ;
}

Cell & Cell::operator=(const Cell& src) {
	if (this != &src) {
		this->_type = src._type;
		this->_resources = src._resources;
		this->_neigh = src._neigh;
		this->_my_ants = src._my_ants;
		this->_opp_ants = src._opp_ants;
	}
	return (*this);
}

bool	Cell::operator==(const Cell& src) const {
	if (this->_neigh != src.getNeigh())
		return (false);
	return (true);
}

int			Cell::getType(void) const {
	return (this->_type);
}

int			Cell::getResources(void) const {
	return (this->_resources);
}

vector<int>	Cell::getNeigh(void) const {
	return (this->_neigh);
}

void	Cell::setResources(int resources) {
	this->_resources = resources;
	return ;
}

void	Cell::setMyAnts(int my_ants) {
	this->_my_ants = my_ants;
	return ;
}

void	Cell::setOppAnts(int opp_ants) {
	this->_opp_ants = opp_ants;
	return ;
}

int main()
{
	int number_of_cells; // amount of hexagonal cells in this map
	cin >> number_of_cells; cin.ignore();
	vector<Cell>	cells(number_of_cells);

	for (int i = 0; i < number_of_cells; i++) {
		int type; // 0 for empty, 1 for eggs, 2 for crystal
		int initial_resources; // the initial amount of eggs/crystals on this cell
		int neigh_0; // the index of the neighbouring cell for each direction
		int neigh_1;
		int neigh_2;
		int neigh_3;
		int neigh_4;
		int neigh_5;
		cin >> type >> initial_resources >> neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5; cin.ignore();
		cells[i] = Cell(type, initial_resources, {neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5});
	}

	int number_of_bases;
	cin >> number_of_bases; cin.ignore();
	vector<int>	my_bases(number_of_bases / 2);
	for (int i = 0; i < number_of_bases; i++) {
		int my_base_index;
		cin >> my_base_index; cin.ignore();
		my_bases[i] = my_base_index;
	}
	vector<int>	opp_bases(number_of_bases / 2);
	for (int i = 0; i < number_of_bases; i++) {
		int opp_base_index;
		cin >> opp_base_index; cin.ignore();
		opp_bases[i] = opp_base_index;
	}

	// game loop
	while (1) {
		for (int i = 0; i < number_of_cells; i++) {
			int resources; // the current amount of eggs/crystals on this cell
			int my_ants; // the amount of your ants on this cell
			int opp_ants; // the amount of opponent ants on this cell
			cin >> resources >> my_ants >> opp_ants; cin.ignore();
			cells[i].setResources(resources);
			cells[i].setMyAnts(my_ants);
			cells[i].setOppAnts(opp_ants);
		}

		

		// WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
		cout << "WAIT" << endl;
	}
}
