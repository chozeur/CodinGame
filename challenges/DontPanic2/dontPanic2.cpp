#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <limits>

using namespace std;

int	closest_elevator(const vector<int> &floor_elevators, int pos)
{
	for (vector<int>::const_iterator it = floor_elevators.begin(); it != floor_elevators.end(); ++it){
		cerr << *it << endl;
	}

	cerr << "in closest_elevator" << endl;
	int	min = INT32_MAX;
	int	res = 0;
	for (vector<int>::const_iterator it = floor_elevators.begin(); it != floor_elevators.end(); ++it){
		if (abs(*it - pos) < min){
			min = abs(*it - pos);
			res = *it;
		}
	}
	cerr << "out closest_elevator" << endl;
	return (res);

	/* ADD if (abs(*it - pos) == 0) */
}

bool	check_direction(int pos, int elevator_pos, string direction)
{
	cerr << "pos: " << pos << " elevator/exit_pos: " << elevator_pos << " direction: " << direction << endl;
	if (direction == "LEFT" && pos < elevator_pos)
		return (false);
	else if (direction == "RIGHT" && pos > elevator_pos)
		return (false);
	return (true);
}

int main()
{
	// cerr << "BEGIN" << endl;
	int nb_floors; // number of floors
	int width; // width of the area
	int nb_rounds; // maximum number of rounds
	int exit_floor; // floor on which the exit is found
	int exit_pos; // position of the exit on its floor
	int nb_total_clones; // number of generated clones
	int nb_additional_elevators; // number of additional elevators that you can build
	int nb_elevators; // number of elevators
	cin >> nb_floors >> width >> nb_rounds >> exit_floor >> exit_pos >> nb_total_clones >> nb_additional_elevators >> nb_elevators; cin.ignore();

	vector<vector<int>>	elevators;
	elevators.resize(nb_floors);
	for (int i = 0; i < nb_floors; i++){
		elevators[i].reserve(128);
	}
	for (int i = 0; i < nb_elevators; i++) {
		int elevator_floor; // floor on which this elevator is found
		int elevator_pos; // position of the elevator on its floor
		cin >> elevator_floor >> elevator_pos; cin.ignore();
		cerr << elevator_floor << ' ' << elevator_pos << endl;
		elevators[elevator_floor].push_back(elevator_pos);
		// for (vector<int>::iterator it = elevators[elevator_floor].begin(); it != elevators[elevator_floor].end(); ++it){
		// 	cerr << *it << endl;
		// }
		cerr << "elevator_floor: " << elevator_floor << " size = " << elevators[elevator_floor].size() << endl;
	}

	// game loop
	int	round = 0;
	while (++round) {
		int clone_floor; // floor of the leading clone
		int clone_pos; // position of the leading clone on its floor
		string direction; // direction of the leading clone: LEFT or RIGHT
		cin >> clone_floor >> clone_pos >> direction; cin.ignore();
		cerr << "\tROUND" << round << endl;
		// cerr << "\tINITED" << endl;
		if (round == 1){
			if (!elevators[clone_floor].empty()){
				int	target_elevator = closest_elevator(elevators[clone_floor], clone_pos);
				if (!check_direction(clone_pos, target_elevator, direction)){
					cout << "WAIT" << endl;
					cin >> clone_floor >> clone_pos >> direction; cin.ignore();
					cerr << "\tROUND" << ++round << endl;
					cout << "BLOCK" << endl;
				}
				else
					cout << "WAIT" << endl;
				continue ;
			}
			cout << "WAIT" << endl;
			cin >> clone_floor >> clone_pos >> direction; cin.ignore();
			cerr << "\tROUND" << ++round << endl;
			cout << "WAIT" << endl;
			cin >> clone_floor >> clone_pos >> direction; cin.ignore();
			cerr << "\tROUND" << ++round << endl;
			elevators[clone_floor].push_back(clone_pos);
			cout << "ELEVATOR" << endl;
			continue ;
		}
		if (clone_floor == -1){
			cout << "WAIT" << endl;
			continue ;
		}
		if (clone_floor == exit_floor){
			if (check_direction(clone_pos, exit_pos, direction))
				cout << "WAIT" << endl;
			else
				cout << "BLOCK" << endl;
			continue ;
		}
		int	target_elevator;
		cerr << "\tTRYING" << endl;
		if (!elevators[clone_floor].empty()){
			cerr << "\t\ttryIN" << endl;
			cerr << "empty=" << elevators[clone_floor].empty() << endl;
			target_elevator = closest_elevator(elevators[clone_floor], clone_pos);
			cerr << "target_elevator: " << target_elevator << endl;
			cerr << "\t\ttryOUT" << endl;
		} else {
			// cerr << "\t\tcatchIN" << endl;
			cerr << "elevator_floor: " << clone_floor << " size = " << elevators[clone_floor].size() << endl;
			elevators[clone_floor].push_back(clone_pos);
			for (vector<int>::iterator it = elevators[clone_floor].begin(); it != elevators[clone_floor].end(); ++it){
				cerr << "floor:" << clone_floor << " pos:" << *it << endl;
			}
			cout << "ELEVATOR" << endl;
			// cerr << "\t\tcatchOUT" << endl;
			continue ;
		}
		cerr << "\tTRIED" << endl;
		if (!check_direction(clone_pos, target_elevator, direction))
			cout << "BLOCK" << endl;
		else
			cout << "WAIT" << endl;
		cerr << "\tEOR" << endl;
	}
	// cerr << "END" << endl;
	return (0);
}
