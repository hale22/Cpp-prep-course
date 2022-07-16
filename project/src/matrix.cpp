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
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++)
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
  if (this == &rhs)   // защита от самоприсваивания(self assignment)
    return *this;

  // надо ли делать проверку "существует ли объект, явл-щийся lvalue"
  rows_ = rhs.rows_;
  // приравнивать ли матрицы разных размеров(с приведением типа прирав-моей матрицы к rhs матрице) ??
  cols_ =  rhs.cols_;
  CopyMatrix(rhs);
  return *this;
}

Matrix::~Matrix() {
  for (size_t count = 0; count < rows_; count++)
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

bool Matrix::operator==(const Matrix& rhs) const {
  if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
    DimensionMismatch *dimension_mismatch = new DimensionMismatch(*this, rhs);
    delete dimension_mismatch;
  }

  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      if (!CompareDouble(matrix_ptr_[i][j], rhs.matrix_ptr_[i][j]))
        return false;
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix& rhs) const {
  return !Matrix::operator==(rhs);
}

Matrix Matrix::operator+(const Matrix& rhs) const {
  if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
    DimensionMismatch *dimension_mismatch = new DimensionMismatch(*this, rhs);
    delete dimension_mismatch;
  }
  Matrix temp_matrix(rows_, cols_);

  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++)
      temp_matrix.matrix_ptr_[i][j] = matrix_ptr_[i][j] + rhs.matrix_ptr_[i][j];
  }
  return temp_matrix;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
  return operator+((-1)*rhs);   // мягко говоря, не самое производительное вычитание
}

Matrix Matrix::operator*(const Matrix& rhs) const {
  if (cols_ != rhs.rows_) {
    DimensionMismatch *dimension_mismatch = new DimensionMismatch(*this, rhs);
    delete dimension_mismatch;
  }

  Matrix temp_matrix(rows_, rhs.cols_);
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < rhs.cols_; j++) {
      for (size_t k = 0; k < cols_; k++)
        temp_matrix.matrix_ptr_[i][j] += matrix_ptr_[i][k] * rhs.matrix_ptr_[k][j];
    }
  }
  return temp_matrix;
}

Matrix Matrix::operator*(double val) const {
  Matrix temp_matrix(rows_, cols_);

  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++)
      temp_matrix.matrix_ptr_[i][j] = matrix_ptr_[i][j] * val;
  }
  return temp_matrix;
}

Matrix operator*(double val, const Matrix& matrix) {
  return matrix.operator*(val);
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
  os << matrix.rows_ << matrix.cols_;
  for (size_t i = 0; i < matrix.rows_; i++) {
    for (size_t j = 0; j < matrix.cols_; j++)
      os << matrix.matrix_ptr_[i][j];
  }
  return os;
}

bool Matrix::CreateEmptyMatrix(size_t rows, size_t cols) {
  // надо ли иниц-ть элементы матрицы нулями?
  matrix_ptr_ = new double* [rows];
  for (size_t count = 0; count < rows; count++)
    matrix_ptr_[count] = new double[cols];
  return true;
}

bool Matrix::CopyMatrix(const Matrix& prev_matrix) {
  if (rows_ != prev_matrix.rows_ || cols_ != prev_matrix.cols_)
    return false;
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++)
      matrix_ptr_[i][j] = prev_matrix.matrix_ptr_[i][j];
  }
  return true;
}

bool CompareDouble(const double first, const double second, const int precis) {
  if (std::abs(first - second) >= (precis*std::numeric_limits<double>::epsilon()))
    return false;
  return true;
}

}  // namespace prep
