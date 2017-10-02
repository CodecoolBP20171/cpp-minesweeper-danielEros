#include <iostream>

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
            for(int i=0; i<width; i++) {
                for (int j = 0; j < height; j++) {
                    int counter = 0;

                    *(table + i*width+j) = '1';
                }
            }
            //*table = *tempTable;
            //std::cout << *(tempTable + 99);
        }

        void printTable() const {
            for(int i=0; i<width; i++){
                for(int j=0; j<height; j++){
                    std::cout << *(table + i*width+j) << " ";
                }
                std::cout << std::endl;
            }
        }

    private:
        void fillTable() {
            srand (time(NULL));
            int luckFactor;
            for(int i=0; i<width; i++){
                for(int j=0; j<height; j++){
                    luckFactor = rand() % 100 + 1;
                    *(table + i*width+j) = (luckFactor > 15 ? '.' : '*');
                }
            }
        }

        const size_t width, height;
        char *table;
    };
}

int main() {
    try {
        Minesweeper ms(10, 10);
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