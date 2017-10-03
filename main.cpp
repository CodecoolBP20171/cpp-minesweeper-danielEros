#include <iostream>
#include <algorithm>

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
            // TODO: step 2 goes here
            //char tempTable[width * height] = new char[width * height];
            //char tempTable[width * height];
            //char *tempTablePointer = tempTable;
            //tempTable(new char[width * height]);
            for(int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int counter = 0;
                    if(*(table + i*width+j) != '*'){
//                        for(int k = std::min(0, i-1); k < std::max(); k++){
//                            //for(int l = )
//                        }
                    }
                }
            }
            //*table = *tempTable;
            //std::cout << *(tempTable + 99);
        }

        void printTable() const {
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    std::cout << *(table + i*width+j) << " ";
                }
                std::cout << std::endl;
            }
        }

    private:
        void fillTable() {
            srand (time(NULL));
            int luckFactor;
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    luckFactor = rand() % 100 + 1;
                    // increment pointer, and dereference unincremented address
                    *table++ = (luckFactor > 15 ? '.' : '*');
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
        Minesweeper ms(20, 10);
        ms.printTable();
        ms.countNeighbours();
        std::cout << std::endl;
        ms.printTable();
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}