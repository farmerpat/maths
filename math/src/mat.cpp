#include <math.h>

#include <cmath>
#include <iostream>

template <typename T>
class Matrix2d {
 public:
  Matrix2d(int rows, int cols) : _rows(rows), _cols(cols) {
    _matrix = (T *)std::malloc(sizeof(T) * rows * cols);
  }

  void init(T val) {
    for (int row = 0; row < _rows; row++) {
      for (int col = 0; col < _cols; col++) {
        // std::cout << "setting " << val << " at " << row << ", " << col
        //           << std::endl;
        _matrix[row * _cols + col] = val;
      }
    }
  }

  void set_value(int row, int col, T val) {
    if (row >= _rows || col >= _cols) {
      std::cout << "row/col out of bounds: " << row << ", " << col << std::endl;
      return;
    }

    _matrix[row * _cols + col] = val;
  }

  T get_value(int row, int col) {
    if (row >= _rows || col >= _cols) {
      std::cout << "row/col out of bounds: " << row << ", " << col << std::endl;
      return T();
    }

    return _matrix[row * _cols + col];
  }

  void print() {
    for (int row = 0; row < _rows; row++) {
      for (int col = 0; col < _cols; col++) {
        std::cout << get_value(row, col) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  // TODO: maybe override [][] somekinda way...
  // Also, could add member function that accepts function
  // which returns T as an arg...could perform fn on cords and replace?
  // e.g.
  // do_at(fn, row, col);

  ~Matrix2d() {
    if (_matrix) {
      free(_matrix);
    }
  }

 protected:
  T *_matrix = nullptr;
  int _rows;
  int _cols;
};
