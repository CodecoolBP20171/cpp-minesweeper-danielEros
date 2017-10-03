#include <iostream>
#include <vector>

namespace {
    class Minesweeper {
    public:
        Minesweeper(const size_t width, const size_t height)
                : width(width), height(height),
                  table(new char[width * height]) {
            fillTable();
        }

        /* In a real implementation there would also be a
         * - copy constructor
         * - assignment operator
         * - move constructor
         * - move assignment operator
         * We will learn about them later
         */

        virtual ~Minesweeper() {
            delete[] table;
        }

        void countNeighbours() {
            for(int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int counter = 0;
                    if(*(table + i*width+j) != '*'){
                       for(int k = std::max(0, i-1); k <= std::min((int)height, i+1); k++){
                           for(int l = std::max(0, j-1); l <= std::min((int)width, j+1); l++){
                               if(*(table + k*width+l) == '*'){
                                   ++counter;
                               }
                           }
                        }
                        char counterChar = '0' + counter;
                        *(table + i*width+j) = counterChar;
                    }
                }
            }
        }

        void printTable() const {
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    std::cout << *(table + i*width+j) << " ";
                }
                std::cout << std::endl;
            }
        }

        std::vector<int> getUserInput(){
            int w, h;
            std::vector<int> result;
            do {
                std::cout << std::endl << "Enter width and height to reveal: " << std::endl;
                try {
                    std::cin >> w >> h;
                } catch (std::exception& e){
                    w = 0;
                    h = 0;
                }
            } while (w < 0 || w > width || h < 0 || h > height);
            result.push_back(w);
            result.push_back(h);
            return result;
        }

        void reveal(const int &w, const int &h){
            if(*(table + h*width+w) == '*'){
                std::cout << "Boooooom!";
                exit(0);
            } else {
                *(table + h*width+w) = '.';
                for(int k = std::max(0, h-1); k <= std::min((int)height, h+1); k++){
                    for(int l = std::max(0, w-1); l <= std::min((int)width, w+1); l++){
                        if(*(table + k*width+l) == '0') {
                            reveal(l, k);
                        }
                    }
                }
            }
        }

    private:
        void fillTable() {
            srand (time(NULL));
            int luckFactor;
            const int mineRatio = 15;
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    luckFactor = rand() % 100 + 1;
                    // increment pointer, and dereference unincremented address
                    *table++ = (luckFactor > mineRatio ? '.' : '*');
                }
            }
            // resetting the pointer to the 0th element of table
            table -= width * height * sizeof(*table);
        }

        const size_t width, height;
        char *table;
    };
}

int main() {
    try {
        Minesweeper ms(70, 15);
        ms.printTable();
        ms.countNeighbours();
        std::cout << std::endl;
        ms.printTable();
        while (true) {
            std::vector<int> userCoordinates = ms.getUserInput();
            ms.reveal(userCoordinates[0], userCoordinates[1]);
            std::cout << std::endl;
            ms.printTable();
        }
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}