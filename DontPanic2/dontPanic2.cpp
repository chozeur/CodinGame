#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <limits>

using namespace std;

int	closest_elevator(int pos, list<int> floor_elevators)
{
	if (floor_elevators.empty())
		throw (exception());

	int	min = INT32_MAX;
	for (list<int>::iterator it = floor_elevators.begin(); it != floor_elevators.end(); it++)
		if (abs(*it - pos) < min)
			min = abs(*it - pos);
	return (min);

	/* ADD if (abs(*it - pos) == 0) */
}

bool	check_direction(int pos, int elevator_pos, std::string direction)
{
	(direction == "LEFT") ? (pos >= elevator_pos ? true : false) : (pos <= elevator_pos ? true : false);
}

int main()
{
	cerr << "TOP" << endl;
	int nb_floors; // number of floors
	int width; // width of the area
	int nb_rounds; // maximum number of rounds
	int exit_floor; // floor on which the exit is found
	int exit_pos; // position of the exit on its floor
	int nb_total_clones; // number of generated clones
	int nb_additional_elevators; // number of additional elevators that you can build
	int nb_elevators; // number of elevators
	cin >> nb_floors >> width >> nb_rounds >> exit_floor >> exit_pos >> nb_total_clones >> nb_additional_elevators >> nb_elevators; cin.ignore();

	list<int>	elevators[nb_floors];
	for (int i = 0; i < nb_elevators; i++) {
		int elevator_floor; // floor on which this elevator is found
		int elevator_pos; // position of the elevator on its floor
		cin >> elevator_floor >> elevator_pos; cin.ignore();
		elevators[elevator_floor].push_back(elevator_pos);
	}
	for (int i = 0; i < nb_floors; i++)
		elevators[i].sort();

	// game loop
	int	round = 0;
	while (++round) {
		cerr << "BEGIN" << endl;
		int clone_floor; // floor of the leading clone
		int clone_pos; // position of the leading clone on its floor
		string direction; // direction of the leading clone: LEFT or RIGHT
		cin >> clone_floor >> clone_pos >> direction; cin.ignore();
		cerr << "INITED" << endl;
		int	target_elevator;
		try {
			target_elevator = closest_elevator(clone_pos, elevators[clone_floor]);
		} catch (exception &e) {
			cout << "ELEVATOR" << endl;
			elevators[clone_floor].push_back(clone_pos);
			elevators[clone_floor].sort();
			continue ;
		}
		cerr << "TRIED" << endl;
		if (!check_direction(clone_pos, target_elevator, direction))
			cout << "BLOCK" << endl;
		else
			cout << "WAIT" << endl;
		cerr << "END" << endl;
	}
	cerr << "BOT" << endl;
	return (0);
}
