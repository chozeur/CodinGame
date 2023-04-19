#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct  s_pos {
	int x;
	int y;
}t_pos;

class	Cell {

	public:

/* CONSTRUCTORS / DESTRUCTOR */
		Cell(void){
			this->_pos.x = -1;
			this->_pos.y = -1;
			return ;
		}

		Cell(int x, int y){
			this->_pos.x = x;
			this->_pos.y = y;
			this->_owner = 0;
			return ;
		}

		Cell(int x, int y, int owner){
			this->_pos.x = x;
			this->_pos.y = y;
			this->_owner = owner;
			return ;
		}

		Cell(const Cell& src){
			*this = src;
			return ;
		}

		~Cell(void){
			return ;
		}

/* OPERATORS */
		Cell&	operator=(const Cell& rhs){
			if (this != &rhs){
				this->_pos = rhs._pos;
				this->_owner = rhs._owner;
			}
			return (*this);
		}

		bool	operator==(const Cell& rhs) const {
			if (this->_pos.x == rhs._pos.x && this->_pos.y == rhs._pos.y)
				return (true);
			return (false);
		}

/* GETTERS */
		t_pos	getPos(void) const {
			return (this->_pos);
		}

		int		getOwner(void) const {
			return (this->_owner);
		}

/* SETTERS */
		void	setPos(t_pos pos){
			this->_pos = pos;
			return ;
		}

		void	setOwner(int owner){
			this->_owner = owner;
			return ;
		}

/* METHODS */


	private:

		t_pos	_pos;
		// 0 = empty, 1 = me, -1 = opponent
		int		_owner;
};

std::ostream&	operator<<(std::ostream& o, const Cell& rhs){
	o << "Cell: " << " " << "Pos: " << rhs.getPos().x << ":" << rhs.getPos().y
	<< " " << "Owner: " << rhs.getOwner();
	return (o);
}

class Grid {

	public:

/* CONSTRUCTORS / DESTRUCTOR */
		Grid(void){
			return ;
		}

		Grid(const Grid& src){
			*this = src;
			return ;
		}

		~Grid(void){
			return ;
		}

/* OPERATORS */
		Grid&	operator=(const Grid& rhs){
			if (this != &rhs){
				this->_pos = rhs._pos;
			}
			return (*this);
		}

/* GETTERS */
		t_pos	getPos(void) const {
			return (this->_pos);
		}

/* SETTERS */
		void	setPos(t_pos pos){
			this->_pos = pos;
			return ;
		}

/* METHODS */


	private:

		t_pos			_pos;
		vector<Cell>	_cells;
};

std::ostream&	operator<<(std::ostream& o, const Grid& rhs){
	o << "Grid: " << "Pos: " << rhs.getPos().x << ":" << rhs.getPos().y;
	return (o);
}

class	Board {

	public:

/* CONSTRUCTORS / DESTRUCTOR */
		Board(void){
			this->_cells.resize(9*9);
			this->_grids.resize(9);
			return ;
		}

		Board(const Board& src){
			*this = src;
			return ;
		}

		~Board(void){
			return ;
		}

/* OPERATORS */
		Board&	operator=(const Board& rhs){
			if (this != &rhs){
				this->_cells = rhs._cells;
				this->_grids = rhs._grids;
			}
			return (*this);
		}

/* GETTERS */
		vector<Cell>	getCells(void) const {
			return (this->_cells);
		}

		vector<Grid>	getGrids(void) const {
			return (this->_grids);
		}

/* SETTERS */
		void	setCells(vector<Cell> cells){
			this->_cells = cells;
			return ;
		}

		void	setGrids(vector<Grid> grids){
			this->_grids = grids;
			return ;
		}

/* METHODS */
		void	meTakeCell(int x, int y){
			Cell	cell(x, y);
			vector<Cell>::iterator	it = find(this->_cells.begin(), this->_cells.end(), cell);
			if (it != this->_cells.end()){
				it->setOwner(1);
			}
			return ;
		}

		void	opponentTakeCell(int x, int y){
			Cell	cell(x, y);
			vector<Cell>::iterator	it = find(this->_cells.begin(), this->_cells.end(), cell);
			if (it != this->_cells.end()){
				it->setOwner(-1);
			}
			return ;
		}

		Cell	getCell(int x, int y){
			Cell	cell(x, y);
			vector<Cell>::iterator	it = find(this->_cells.begin(), this->_cells.end(), cell);
			if (it != this->_cells.end()){
				return (*it);
			}
			return (Cell());
		}

	private:

		vector<Cell>	_cells;
		vector<Grid>	_grids;

};

int main()
{

	Board	board;

	// game loop
	while (1) {
/* OPPONENT LAST PLAY */
		int	opponent_row;
		int	opponent_col;
		cin >> opponent_row >> opponent_col; cin.ignore();
		board.opponentTakeCell(opponent_row, opponent_col);

/* VALID CELLS */
		int valid_action_count;
		cin >> valid_action_count; cin.ignore();
		vector<Cell>	valid_cells(valid_action_count);
		for (int i = 0; i < valid_action_count; i++) {
			int row;
			int col;
			cin >> row >> col; cin.ignore();
			valid_cells[i] = Cell(row, col, board.getCell(row, col).getOwner());
		}

/* PLAY RANDOM CELL */
		int	rand_cell = rand() % valid_cells.size();
		board.meTakeCell(valid_cells[rand_cell].getPos().x, valid_cells[rand_cell].getPos().y);
		cout << valid_cells[rand_cell].getPos().x << " " << valid_cells[rand_cell].getPos().y << endl;

	}
}
