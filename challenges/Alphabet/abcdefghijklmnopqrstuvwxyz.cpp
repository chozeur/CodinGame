#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct	point{
	int x;
	int y;
};

class	AlphabetPath{

	public:

		AlphabetPath(void);
		AlphabetPath(int n);
		AlphabetPath(const AlphabetPath & src);
		~AlphabetPath(void);

		AlphabetPath & operator=(const AlphabetPath & src);

		point	findA(void);
		point	findChar(char c, point p);

	private:

		int				_n;
		vector<string>	_map;
};

AlphabetPath::AlphabetPath(void){
	return ;
}

AlphabetPath::AlphabetPath(int n): _n(n){
	_map.resize(n);
	for (int i = 0; i < n; i++){
		cin >> _map[i];
	}
	return ;
}

AlphabetPath::AlphabetPath(const AlphabetPath & src){
	*this = src;
	return ;
}

AlphabetPath::~AlphabetPath(void){
	return ;
}

AlphabetPath & AlphabetPath::operator=(const AlphabetPath & src){
	if (this != &src){

	}
	return (*this);
}

point	AlphabetPath::findA(void){
	point	pfinal, ptmp;
	pfinal.x = 0;	pfinal.y = 0;
	ptmp.x = 0;		ptmp.y = 0;
	for (int itv = 0; itv < _n; itv++){
		ptmp.x = 0;
		for (int its = 0; its < _n; its++){
			if (_map[itv][its] == 'A'){
				try {
					findChar('B', ptmp);
				} catch (exception & e){
					continue ;
				}
				pfinal.x = its;
				pfinal.y = itv;
				return (pfinal);
			}
			ptmp.x++;
		}
		ptmp.y++;
	}
	return (pfinal);
}

point	AlphabetPath::findChar(char C, point p){
	if (p.y){
		if (_map[p.y - 1][p.x] == C){
			p.y--;
			return (p);
		}
	} else if (p.y < _n - 1){
		if (_map[p.y + 1][p.x] == C){
			p.y++;
			return (p);
		}
	} else if (p.x){
		if (_map[p.y][p.x - 1] == C){
			p.x--;
			return (p);
		}
	} else if (p.x < _n - 1){
		if (_map[p.y][p.x + 1] == C){
			p.x++;
			return (p);
		}
	} throw exception();
}

int main(){

	int n;
	cin >> n; cin.ignore();

	AlphabetPath	ap(n);


}
