#include "matrix.h"
#include "exceptions.h"

namespace prep {
Matrix::Matrix(size_t rows, size_t cols): rows_(rows), cols_(cols), matrix_ptr_(NULL)  {
  CreateEmptyMatrix(rows, cols);
}

Matrix::Matrix(std::istream& is): rows_(0), cols_(0), matrix_ptr_(NULL) {
  if (!is)
    InvalidMatrixStream invalid_matrix_stream;

  is >> rows_ >> cols_;
  CreateEmptyMatrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++)
      is >> matrix_ptr_[i][j];
  }

  if (!is.eof())
    InvalidMatrixStream invalid_matrix_stream;
}

Matrix::Matrix(const Matrix& rhs): rows_(rhs.rows_), cols_(rhs.cols_), matrix_ptr_(NULL) {
  //  todo: проверка матрицы rhs
  CreateEmptyMatrix(rows_, cols_);
  CopyMatrix(rhs);
}

Matrix& Matrix::operator=(const Matrix& rhs) {
  // надо ли делать проверку "существует ли объект, явл-щийся lvalue"
  rows_ = rhs.rows_;
  // приравнивать ли матрицы разных размеров(с приведением типа прирав-моей матрицы к rhs матрице) ??
  cols_ =  rhs.cols_;
  CopyMatrix(rhs);
  return *this;
}

Matrix::~Matrix() {
  for (int count = 0; count < rows_; count++)
    delete [] matrix_ptr_[count];
  delete [] matrix_ptr_;
}

size_t Matrix::getRows() const {
  return rows_;
}

size_t Matrix::getCols() const {
  return cols_;
}

double Matrix::operator()(size_t i, size_t j) const {
  if (i > rows_ || j > cols_) {
    OutOfRange *out_of_range = new OutOfRange(i, j, *this);
    delete out_of_range;
    // OutOfRange out_of_range(i, j, *this);
  }
  return matrix_ptr_[i][j];
}

double& Matrix::operator()(size_t i, size_t j) {
  if (i > rows_ || j > cols_) {
    OutOfRange *out_of_range = new OutOfRange(i, j, *this);
    delete out_of_range;
  }
  double& value = matrix_ptr_[i][j];  // при выходе из скопа value стирается, по идее
  return value;
}

/*bool Matrix::operator==(const Matrix& rhs) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      // if (Matrix::CompareDouble(5.99, 4.44, 7)) // #2
    }
  }
} */

bool Matrix::CreateEmptyMatrix(size_t rows, size_t cols) {
  // надо ли иниц-ть элементы матрицы нулями?
  matrix_ptr_ = new double* [rows];
  for (int count = 0; count < rows; count++)
    matrix_ptr_[count] = new double[cols];
  return true;
}

bool Matrix::CopyMatrix(const Matrix& prev_matrix) {
  if (rows_ != prev_matrix.rows_ || cols_ != prev_matrix.cols_)
    return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++)
      matrix_ptr_[i][j] = prev_matrix.matrix_ptr_[i][j];
  }
  return true;
}

}  // namespace prep
