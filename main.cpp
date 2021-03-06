#include <iostream>
#include <vector>

namespace {
    class Minesweeper {
    public:
        Minesweeper(const size_t width, const size_t height)
                : width(width), height(height),
                  table(new char[width * height]), isRevealedTable(new bool[width * height]) {
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
            delete[] isRevealedTable;
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

        void printGameTable() const {
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    if(*(isRevealedTable + i*width+j)){
                        std::cout << *(table + i*width+j) << " ";
                    } else {
                        std::cout << '#' << " ";
                    }
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
                if(*(isRevealedTable + h*width+w) == false) {
                    numberOfRevealedCells++;
                }
                *(isRevealedTable + h*width+w) = true;
                for(int k = std::max(0, h-1); k <= std::min((int)height-1, h+1); k++){
                    for(int l = std::max(0, w-1); l <= std::min((int)width-1, w+1); l++){
                        std::cout << k << l << std::endl;
                        if(*(table + k*width+l) == '0') {
                            reveal(l, k);
                        }
                        if(*(isRevealedTable + k*width+l) == false) {
                            numberOfRevealedCells++;
                        }
                        *(isRevealedTable + k*width+l) = true;
                    }
                }
            }
        }

        bool isWon(){
            return numberOfRevealedCells == width * height;
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
                    *isRevealedTable++ = false;
                }
            }
            // resetting the pointers to the 0th element of tables
            table -= width * height * sizeof(*table);
            isRevealedTable -= width * height * sizeof(*isRevealedTable);
        }

        const size_t width, height;
        char *table;
        bool *isRevealedTable;
        int numberOfRevealedCells = 0;
    };
}


int main() {
    try {
        Minesweeper ms(5, 5);
        ms.printTable();
        ms.countNeighbours();
        std::cout << std::endl;
        ms.printTable();
        std::cout << std::endl;
        ms.printGameTable();
        while (true) {
            std::vector<int> userCoordinates = ms.getUserInput();
            ms.reveal(userCoordinates[0], userCoordinates[1]);
            std::cout << std::endl;
            ms.printGameTable();
            if(ms.isWon()){
                std::cout << "Congratulations, you won!" << std::endl;
                exit(0);
            }
        }
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}