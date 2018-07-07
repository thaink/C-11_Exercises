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


using namespace std;

template<typename T>
class Matrix {
public:
  void resize(int rows, int cols) {
      data_.resize(rows*cols);
      ncols = cols;
      nrows = rows;
  }

  T& at(int row, int col) {
    return data_.at(row * ncols + col);
  }

  int rows() {return nrows;}
  int cols() {return ncols;}

private:
  vector<T> data_;
  unsigned int ncols;
  unsigned int nrows;
};

constexpr unsigned int kMine = 9;
using std::min;
using std::max;

class MineField {
private:
    struct Cell {
        int value = 0;
        bool visability = false;
    };
    Matrix<Cell> mField_;

    void place_mine(int rrow, int rcol) {
        if(mField_.at(rrow, rcol).value == kMine) return;
        mField_.at(rrow, rcol).value = kMine;

        int rows = mField_.rows();
        int cols = mField_.cols();
        for (int idx = max(0, rrow-1); idx <= min(rows-1, rrow+1); ++idx)
            for (int jdx = max(0, rcol-1); jdx <= min(cols-1, rcol+1); ++jdx)
                if(mField_.at(idx, jdx).value != kMine)
                    mField_.at(idx, jdx).value++;
    }

public:
    MineField(int rows, int cols, int nmines) {
        mField_.resize(rows, cols);

        if(nmines > rows*cols) throw 20;
        int mine_count = 0;
        while (mine_count < nmines) {
            int rcol = rand() % cols;
            int rrow = rand() % rows;

            if(mField_.at(rrow, rcol).value == kMine) continue;
            mine_count++;
            place_mine(rrow, rcol);
        }
    }

    MineField(int rows, int cols, int nmines, bool op) {
        mField_.resize(rows, cols);

        if(nmines > rows*cols) throw 20;

        //loop through position vector
        std::random_device rd;
        std::default_random_engine re(rd());
        std::uniform_real_distribution<double> real_dist(0.0,1.0);

        double mine_remain_count = nmines;
        double position_remain_count = cols*rows;
        for (int idx = 0; idx<cols*rows; ++idx) {
            double posibility = mine_remain_count/position_remain_count;
            double rand_post  = real_dist(re);
            if (rand_post < posibility) {
                place_mine(idx/cols, idx%cols);
                --mine_remain_count;
            }

            --position_remain_count;
        }
    }

    void print() {
        for (int idx = 0; idx < mField_.rows(); ++idx) {
            for (int jdx = 0; jdx < mField_.cols(); ++jdx)
                std::cout << mField_.at(idx, jdx).value << " ";
             cout << "\n";
        }
    }
};

int main()
{
    MineField m(9,9,12,true);
    m.print();
    return 0;
}

