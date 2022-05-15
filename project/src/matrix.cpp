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

bool CopyMatrix(Matrix& prev_matrix, Matrix& new_matrix) {
  // todo
}

Matrix::Matrix(const Matrix& rhs): rows_(rhs.rows_), cols_(rhs.cols_), matrix_ptr_(NULL) { //todo: проверка матрицы rhs
  CreateEmptyMatrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++)
      matrix_ptr_[i][j] = rhs.matrix_ptr_[i][j];
  }
}

Matrix& Matrix::operator=(const Matrix& rhs) {

}

a*b
b*a

Matrix::~Matrix() {
  for (int count = 0; count < rows_; count++)
    delete [] matrix_ptr_[count];
  delete [] matrix_ptr_;
}

bool Matrix::CreateEmptyMatrix(size_t rows, size_t cols) {
  matrix_ptr_ = new double* [rows];
  for (int count = 0; count < rows; count++)
    matrix_ptr_[count] = new double[cols];
  return true;
}

size_t Matrix::getRows() const {
  return rows_;
}

size_t Matrix::getCols() const {
  return cols_;
}

double Matrix::operator()(size_t i, size_t j) const {
  if (i > rows_ || j > cols_)
    OutOfRange out_of_range(i, j, *this);
  return matrix_ptr_[i][j];
}

double& Matrix::operator()(size_t i, size_t j) { // #1
  if (i > rows_ || j > cols_)
    OutOfRange out_of_range(i, j, *this);
  double& value = matrix_ptr_[i][j];
  return value;
}

bool Matrix::operator==(const Matrix& rhs) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++)
      if (Matrix::CompareDouble(5.99, 4.44, 7)) // #2
  }
} // #3 epsilon?

}  // namespace prep
