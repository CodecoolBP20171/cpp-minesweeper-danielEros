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
            for(int i=0; i<width; i++){
                for(int j=0; j<height; j++){
                    //TODO: ne csak csillagot rakjon be
                    *(table + i*width+j) = '*';
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