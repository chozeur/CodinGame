#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

# define TAB_SIZE 128

class   Landscape {
    
    public:

        Landscape(void){

            this->_tab = new char*[TAB_SIZE];
            for (int i = 0; i < TAB_SIZE; ++i){
                this->_tab[i] = new char[TAB_SIZE];
                for (int j = 0; j < TAB_SIZE; ++j)
                    this->_tab[i][j] = ' ';
            }

            this->_index = this->_highest = 0;

            return ;
        }
    
        Landscape(const Landscape& src){
            *this = src;
            return ;
        }
    
        ~Landscape(void){return ;}
    
        Landscape&  operator=(const Landscape& rhs){
            if (this != &rhs){
                for (int i = 0; i < TAB_SIZE; ++i)
                    for (int j = 0; j < TAB_SIZE; ++j)
                        this->_tab[i][j] = rhs._tab[i][j];

            }
            return (*this);
        }

        char**  get_tab(void) const {return (this->_tab);}
        int     get_index(void) const {return (this->_index);}
        int     get_highest(void) const {return (this->_highest);}

        void    set_tab(char** tab){
            for (int i = 0; i < TAB_SIZE; ++i)
                    for (int j = 0; j < TAB_SIZE; ++j)
                        this->_tab[i][j] = tab[i][j];

            return ;
        }

        void    drawMountain(int height){
            if (height > this->_highest)
                this->_highest = height;

            for (int i = 0; i < height; ++i){
                int ground = TAB_SIZE - 1 - i;
                this->_tab[ground][this->_index++] = '/';
            }
            
            for (int i = 0; i < height; ++i){
                int ground = TAB_SIZE - height + i;
                this->_tab[ground][this->_index++] = '\\';
            }

            return ;
        }

        void    printLandscape(void) const {
            for (int i = TAB_SIZE - this->_highest; i < TAB_SIZE; ++i){
                    for (int j = 0; j < this->_index; ++j){
                        char    item = this->_tab[i][j];
                        if (item == ' '){
                            for (int k = j + 1; k < this->_index; ++k){
                                if (this->_tab[i][k] != ' '){
                                    cout << item;
                                    break ;
                                }
                            }
                        } else
                            cout << item;
                    }
                cout << endl;
            }
        }

    private:

        char**  _tab;
        int     _index;
        int     _highest;

};

int main(void){
    int n; // the number of mountains
    cin >> n; cin.ignore();
    
    Landscape   land;

    for (int i = 0; i < n; i++) {
        int height; // height of the mountain
        cin >> height; cin.ignore();

        land.drawMountain(height);
    }

    land.printLandscape();

    return (0);
}
