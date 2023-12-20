#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * Score points by scanning valuable fish faster than your opponent.
 **/



struct position {
	int	x;
	int	y;
	position(void);
	position(const int x, const int y);
};

position::position(void){
	return ;
}

position::position(const int x, const int y)
:x(x), y(y){
	return ;
}





///////////////////////////////////// CREATURE CLASS ///////////////////////////


class	Creature {

	public:

		Creature(void);
		Creature(const Creature& src);
		~Creature(void);

		const Creature&	operator=(const Creature& rhs);

		int		getId(void) const;
		void	setId(int id);
		int		getColor(void) const;
		void	setColor(int color);
		int		getType(void) const;
		void	setType(int type);
		position	getPosition(void) const;
		void	setPosition(const position pos);
		position	getVelocity(void) const;
		void	setVelocity(const position vel);
		bool	getVisible(void) const;
		void	setVisible(const bool visible);

	private:

		int				_id;
		int				_color;
		int				_type;
		position	_position;
		position	_velocity;
		bool			_isVisible = false;

};

/*------------------------------------------------------------------------*/

Creature::Creature(void){
	return ;
}

Creature::Creature(const Creature& src){
	*this = src;
	return ;
}

Creature::~Creature(void){
	return ;
}

const Creature&	Creature::operator=(const Creature& rhs){
	if (this != &rhs){
		this->_id = rhs._id;
		this->_color = rhs._color;
		this->_type = rhs._type;
	}
	return (*this);
}

int		Creature::getId(void) const{
	return (this->_id);
}

void	Creature::setId(int id){
	this->_id = id;
	return ;
}

int		Creature::getColor(void) const{
	return (this->_color);
}

void	Creature::setColor(int color){
	this->_color = color;
	return ;
}

int		Creature::getType(void) const{
	return (this->_type);
}

void	Creature::setType(int type){
	this->_type = type;
	return ;
}

position	Creature::getPosition(void) const{
	return (this->_position);
}

void	Creature::setPosition(const position pos){
	this->_position = pos;
	return ;
}

position	Creature::getVelocity(void) const{
	return (this->_velocity);
}

void	Creature::setVelocity(const position vel){
	this->_velocity = vel;
	return ;
}

bool	Creature::getVisible(void) const{
	return (this->_isVisible);
}

void	Creature::setVisible(const bool visible){
	this->_isVisible = visible;
	return ;
}









///////////////////////////////////// DRONE CLASS ///////////////////////////

class	Drone {

	public:

		Drone(void);
		Drone(const Drone& src);
		~Drone(void);

		const Drone&	operator=(const Drone& rhs);

		int				getId(void) const;
		void			setId(const int id);
		position	getPosition(void) const;
		void			setPosition(const position pos);
		int				getBattery(void) const;
		void			setBattery(const int battery);

	private:

		int				_id;
		position	_position;
		int				_battery;
};

Drone::Drone(void){
	return ;
}

Drone::Drone(const Drone& src){
	*this = src;
	return ;
}

Drone::~Drone(void){
	return ;
}

const Drone&	Drone::operator=(const Drone& rhs){
	if (this != &rhs){
		this->_id = rhs._id;
		this->_position = rhs._position;
		this->_battery = rhs._battery;
	}
	return (*this);
}

int		Drone::getId(void) const{
	return (this->_id);
}

void	Drone::setId(const int id){
	this->_id = id;
	return ;
}

position	Drone::getPosition(void) const{
	return (this->_position);
}

void	Drone::setPosition(const position pos){
	this->_position = pos;
	return ;
}

int		Drone::getBattery(void) const{
	return (this->_battery);
}

void	Drone::setBattery(const int battery){
	this->_battery = battery;
	return ;
}



















///////////////////////////////////// PLAYER CLASS ///////////////////////////

class	Player {

public:

	Player(void);
	Player(const Player& src);
	~Player(void);

	const Player&	operator=(const Player& rhs);

	int		getScore(void) const;
	void	setScore(int score);
	std::vector<int>	getScans(void) const;
	void	setScans(const std::vector<int> scans);
	std::vector<Drone>	getDrones(void) const;
	void	setDrones(const std::vector<Drone> drones);

	void	updateScore(void);
	void	updateScans(void);
	void	updateDrones(void);

private:

	int									_score;
	std::vector<int>		_scans;
	std::vector<Drone>	_drones;
};

/*------------------------------------------------------------------*/

Player::Player(void){
	return ;
}

Player::Player(const Player& src){
	*this = src;
	return ;
}

Player::~Player(void){
	return ;
}

const Player&	Player::operator=(const Player& rhs){
	if (this != &rhs){
		this->_score = rhs._score;
	}
	return (*this);
}

int	Player::getScore(void) const {
	return (this->_score);
}

void	Player::setScore(int score){
	this->_score = score;
	return ;
}

std::vector<int>	Player::getScans(void) const {
	return (this->_scans);
}

void	Player::setScans(std::vector<int> scans){
	this->_scans = scans;
	return ;
}

std::vector<Drone>	Player::getDrones(void) const {
	return (this->_drones);
}

void	Player::setDrones(std::vector<Drone> drones){
	this->_drones = drones;
	return ;
}

void	Player::updateScore(void){
	int new_score;
	std::cin >> new_score; std::cin.ignore();
	this->_score = new_score;
}

void	Player::updateScans(void){
	int scan_count;
	std::cin >> scan_count; std::cin.ignore();
	std::vector<int>	scans(scan_count);
	for (int i = 0; i < scan_count; i++) {
			int creature_id;
			std::cin >> creature_id; std::cin.ignore();
			scans[i] = creature_id;
	}
	this->_scans = scans;
}

void	Player::updateDrones(void){
	int drone_count;
	std::cin >> drone_count; std::cin.ignore();
	std::vector<Drone>	drones(drone_count);
	for (int i = 0; i < drone_count; i++) {
		int drone_id;
		int drone_x;
		int drone_y;
		int emergency;
		int battery;
		std::cin >> drone_id >> drone_x >> drone_y >> emergency >> battery; std::cin.ignore();

		drones[i].setId(drone_id);
		drones[i].setPosition(position(drone_x, drone_y));
		drones[i].setBattery(battery);
	}
	this->_drones = drones;
}
































//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////	PROGRAM		////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// GLOBAL VARIABLES

Player	myself;
Player	opponent;

std::vector<Creature>	allCreatures;
//



// UTILS FUNCTIONS

Creature&	getCreatureById(const int id){
	for (std::vector<Creature>::iterator it = allCreatures.begin();
	it != allCreatures.end();
	++it){
		if ((*it).getId() == id){
			return (*it);
		}
	} throw (std::__throw_invalid_argument);
}

void	initCreatures(void){

	int creature_count;
	std::cin >> creature_count; std::cin.ignore();
	allCreatures.resize(creature_count);

	for (int i = 0; i < creature_count; i++) {
			int	creature_id;
			int	color;
			int	type;
			std::cin >> creature_id >> color >> type; std::cin.ignore();

			allCreatures[i].setId(creature_id);
			allCreatures[i].setColor(color);
			allCreatures[i].setType(type);
	}

	return ;
}

void	updatePlayersScores(void){

	myself.updateScore();
	opponent.updateScore();

	return ;
}

void	updatePlayersScans(void){

	myself.updateScans();
	opponent.updateScans();

	return ;
}

void	updatePlayersDrones(void){

	myself.updateDrones();
	opponent.updateDrones();

	return ;
}

void	updatePlayers(void){

	updatePlayersScores();

	updatePlayersScans();

	updatePlayersDrones();

	return ;
}

void	updateCreatures(void){

	int visible_creature_count;
	std::cin >> visible_creature_count; std::cin.ignore();
	for (int i = 0; i < visible_creature_count; i++) {
		int creature_id;
		int creature_x;
		int creature_y;
		int creature_vx;
		int creature_vy;
		std::cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy; std::cin.ignore();

		getCreatureById(creature_id).setPosition(position(creature_x, creature_y));
		getCreatureById(creature_id).setVelocity(position(creature_vx, creature_vy));
		getCreatureById(creature_id).setVisible(true);
	}

	return ;
}
//








//################################
//################################
//################################
//################################
//################################
//#############	MAIN	############
//################################
//################################
//################################
//################################
//################################

int main(void){

	initCreatures();

	// game loop
	while (1) {

		updatePlayers();

//?????
		int drone_scan_count;
		std::cin >> drone_scan_count; std::cin.ignore();
		for (int i = 0; i < drone_scan_count; i++) {
			int drone_id;
			int creature_id;
			std::cin >> drone_id >> creature_id; std::cin.ignore();
		}
//?????

		updateCreatures();

//?????
		int radar_blip_count;
		std::cin >> radar_blip_count; std::cin.ignore();
		for (int i = 0; i < radar_blip_count; i++) {
			int drone_id;
			int creature_id;
			std::string radar;
			std::cin >> drone_id >> creature_id >> radar; std::cin.ignore();
		}
//?????

		for (int i = 0; i < myself.getDrones().size(); i++) {

			// Write an action using cout. DON'T FORGET THE "<< endl"
			// To debug: cerr << "Debug messages..." << endl;

			std::cout << "WAIT 1" << std::endl; // MOVE <x> <y> <light (1|0)> | WAIT <light (1|0)>
		}
	}
}
