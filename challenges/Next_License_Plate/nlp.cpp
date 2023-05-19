#include <iostream>

// # define PLATE "QS-456-DF"
// # define N 1000000

class	LicensePlate {

	public:
		LicensePlate(void);
		LicensePlate(const LicensePlate &src);
		LicensePlate(std::string plate);
		~LicensePlate(void);

		LicensePlate	&operator=(const LicensePlate &rhs);

		std::string	getLeft(void) const;
		std::string	getRight(void) const;
		int			getMiddle(void) const;
		std::string	getFMiddle(void) const;

		void	increment(void);

	private:
		std::string	_left;
		std::string	_right;
		int			_middle;

};

LicensePlate::LicensePlate(void) {
	return ;
}

LicensePlate::LicensePlate(const LicensePlate &src) {
	*this = src;
	return ;
}

LicensePlate::LicensePlate(std::string plate) {
	_left = plate.substr(0, 2);
	_middle = std::stoi(plate.substr(3, 3));
	_right = plate.substr(7, 2);
}

LicensePlate::~LicensePlate(void) {
	return ;
}

LicensePlate	&LicensePlate::operator=(const LicensePlate &rhs) {
	if (this != &rhs) {
		_left = rhs._left;
		_middle = rhs._middle;
		_right = rhs._right;
	}
	return (*this);
}

std::string	LicensePlate::getLeft(void) const {return (_left);}

std::string	LicensePlate::getRight(void) const {return (_right);}

int			LicensePlate::getMiddle(void) const {return (_middle);}

std::string	LicensePlate::getFMiddle(void) const {
	std::string	fMiddle;

	if (_middle < 10) {
		fMiddle = "00" + std::to_string(_middle);
	}
	else if (_middle < 100) {
		fMiddle = "0" + std::to_string(_middle);
	}
	else {
		fMiddle = std::to_string(_middle);
	}
	return (fMiddle);
}

void	LicensePlate::increment(void) {
	_middle++;
	if (_middle == 1000) {
		_middle = 1;
		_right[1]++;
		if (_right[1] == 'Z' + 1) {
			_right[1] = 'A';
			_right[0]++;
			if (_right[0] == 'Z' + 1) {
				_right[0] = 'A';
				_left[1]++;
				if (_left[1] == 'Z' + 1) {
					_left[1] = 'A';
					_left[0]++;
					if (_left[0] == 'Z' + 1) {
						_left[0] = 'A';
					}
				}
			}
		}
	}
}

/***********************************************************************/

int main()
{
	std::string plate;
	getline(std::cin, plate);
	int nToLast;
	std::cin >> nToLast; std::cin.ignore();

	std::cerr << "plate = " << plate << std::endl;

	LicensePlate	license(plate);

	for (int i = 0; i < nToLast; i++) {
		license.increment();
	}

	std::cout << license.getLeft() << "-" << license.getFMiddle() << "-" << license.getRight() << std::endl;

	return (0);
}

// int	main(void){

// 	LicensePlate	plate(PLATE);
// 	int				nToLast(N);


// 	for (int i = 0; i < nToLast; i++) {
// 		plate.increment();
// 		std::cout << plate.getLeft() << "-" << plate.getFMiddle() << "-" << plate.getRight() << std::endl;
// 	}
// 	return (0);
// }
