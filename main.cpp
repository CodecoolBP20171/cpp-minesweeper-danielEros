#include <iostream>

namespace {
    class Minesweeper {
    public:
        Minesweeper(const size_t width, const size_t height)
                : mWidth(width), mHeight(height),
                  mTable(new char[width * height]) {
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
            delete[] mTable;
        }

        void countNeighbours() {
            // step 2 goes here
        }

        void printTable() const {
            // step 3 goes here
        }

    private:
        void fillTable() {
            // step 1 goes here
        }

        const size_t mWidth, mHeight;
        char *mTable;
    };
}

int main() {
    try {
        Minesweeper ms(100, 50);
        ms.printTable();
        ms.countNeighbours();
        ms.printTable();
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}