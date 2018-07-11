/** Constructing the mine field
 * - Given size and number of mine
 * https://techdevguide.withgoogle.com/resources/coding-question-minesweeper/?types=coding-interview-question#!
 *
 * If you hav specific position of the mines. You can generate the mine field by:
 * - placing the mine and add 1 to surrounding position
 * - traverse through the map and count surrounding mine
 *
 * So the key is specify where to put the mine.
 * - A naive solution could be generate the position through a random generator.
 *   However of the number of mine is large compare to number of position. Many
 *   duplicates will appear.
 * - A better solution is to adjust the probability in as the exploration going.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


using namespace std;

template<typename T>
class Matrix {
private:
    vector<T> data_;
    unsigned int nrows;
    unsigned int ncols;

public:
    void resize(int rows, int cols) {
        nrows = rows; ncols = cols;
        data_.resize(rows*cols);
    }

    T& at(int row, int col) {return data_.at(row*ncols +  col);}

    int rows() {return nrows;}
    int cols() {return ncols;}
};

static constexpr int kMine = 9;

class MineField {
private:
    struct Cell {
        bool visibility = 0;
        int value = 0;
    };
    Matrix<Cell> data_;

    void place_mine(int row, int col) {
        Cell& c = data_.at(row, col);
        if(c.value == kMine) return;
        c.value = kMine;
        for (int idx = max(0, row-1); idx <= min(data_.rows()-1, row+1); ++idx)
            for (int jdx = max(0, col-1); jdx <= min(data_.cols()-1, col+1); ++jdx)
                if(data_.at(idx, jdx).value != kMine) data_.at(idx, jdx).value++;
    }

public:
    MineField(int rows, int cols, int nmines) {
        assert(nmines <= rows*cols);
        data_.resize(rows, cols);
        double remaining_mine = nmines;
        random_device rd;
        default_random_engine re(rd());
        uniform_real_distribution<double> urd(0.0, 1.0);
        for (int idx = 0; idx < rows*cols; ++idx) {
            double chance = remaining_mine/(rows*cols -idx);
            if(urd(re) < chance) {
                place_mine(idx/cols, idx%cols);
                --remaining_mine ;
            }
        }
    }

    void print() {
        for (int idx = 0; idx < data_.rows(); ++idx) {
            for (int jdx = 0; jdx < data_.cols(); ++jdx)
                std::cout << data_.at(idx, jdx).value << " ";
             cout << "\n";
        }
    }
};

int main()
{
    MineField m(1,2,1);
    m.print();
    return 0;
}
