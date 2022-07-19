#include <cmath>
#include <iomanip>

#include "matrix.h"
#include "exceptions.h"

namespace prep {
Matrix::Matrix(size_t rows, size_t cols): rows_(rows), cols_(cols), matrix_ptr_(NULL)  {
  CreateEmptyMatrix(rows, cols);
}

Matrix::Matrix(std::istream& is): rows_(0), cols_(0), matrix_ptr_(NULL) {
	if (!is)
    throw InvalidMatrixStream();

  is >> rows_ >> cols_;
  CreateEmptyMatrix(rows_, cols_);
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++)
      is >> matrix_ptr_[i][j];
  }

	if (is.fail())
		throw InvalidMatrixStream();
}

Matrix::Matrix(const Matrix& rhs): rows_(rhs.rows_), cols_(rhs.cols_), matrix_ptr_(NULL) {
  //  todo: проверка матрицы rhs
  CreateEmptyMatrix(rows_, cols_);
  CopyMatrix(rhs);
}

Matrix& Matrix::operator=(const Matrix& rhs) {
  if (this == &rhs)   // защита от самоприсваивания(self assignment)
    return *this;

  ClearMatrixBody(rows_);

  // надо ли делать проверку "существует ли объект, явл-щийся lvalue"
  rows_ = rhs.rows_;
  cols_ =  rhs.cols_;

  CreateEmptyMatrix(rows_, cols_);
  CopyMatrix(rhs);
  return *this;
}

Matrix::~Matrix() {
  ClearMatrixBody(rows_);
}

size_t Matrix::getRows() const {
  return rows_;
}

size_t Matrix::getCols() const {
  return cols_;
}

double Matrix::operator()(size_t i, size_t j) const {
  if (i == rows_ || j == cols_)
    throw OutOfRange(i, j, *this);
  return matrix_ptr_[i][j];
}

double& Matrix::operator()(size_t i, size_t j) {
  if (i == rows_ || j == cols_)
    throw OutOfRange(i, j, *this);

  double& value = matrix_ptr_[i][j];  // при выходе из скопа value стирается, по идее
  return value;
}

bool Matrix::operator==(const Matrix& rhs) const {
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
  if (rows_ != rhs.rows_ || cols_ != rhs.cols_)
    throw DimensionMismatch(*this, rhs);
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
  if (cols_ != rhs.rows_)
    throw DimensionMismatch(*this, rhs);

  Matrix temp_matrix(rows_, rhs.cols_);
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < rhs.cols_; j++) {
      temp_matrix.matrix_ptr_[i][j] = 0;
      for (size_t k = 0; k < cols_; k++) {
        temp_matrix.matrix_ptr_[i][j] += matrix_ptr_[i][k] * rhs.matrix_ptr_[k][j];
			}
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
  os << matrix.rows_ << " " << matrix.cols_  << "\n";
  for (size_t i = 0; i < matrix.rows_; i++) {
    for (size_t j = 0; j < matrix.cols_; j++)
      os << std::setprecision(std::numeric_limits<double>::max_digits10)
        << std::setw(30) << matrix.matrix_ptr_[i][j];
    os << "\n";
  }
  return os;
}

Matrix Matrix::transp() const {
  Matrix temp_matrix(cols_, rows_);
  for (size_t i = 0; i < temp_matrix.rows_; i++) {
    for (size_t j = 0; j < temp_matrix.cols_; j++)
      temp_matrix.matrix_ptr_[i][j] = matrix_ptr_[j][i];
  }

  return temp_matrix;
}

double Matrix::det() const {
  if (rows_ != cols_)
    throw DimensionMismatch(*this);

  //  todo: функция для оптимального выбора строки, по которой выч-ть опре-ль
  // те строка с самым большим числом нулей

  double deter = 0;
  for (size_t i = 0; i < cols_; i++) {
    if (rows_ == 1)
      return matrix_ptr_[1][i];
    else
      deter+= matrix_ptr_[1][i] * CalcCofactor(1, i);
  }
  return deter;
}

Matrix Matrix::adj() const {
  if (rows_ != cols_)
    throw DimensionMismatch(*this);

  Matrix temp_matrix(rows_, cols_);
  for (size_t i = 0; i < temp_matrix.rows_; i++) {
    for (size_t j = 0; j < temp_matrix.cols_; j++)
      temp_matrix.matrix_ptr_[i][j] = CalcCofactor(i, j);
  }
  return temp_matrix.transp();
}

Matrix Matrix::inv() const {
  if (rows_ != cols_)
    throw DimensionMismatch(*this);

  double deter = det();
  if (deter == 0) {
    SingularMatrix sing_matr;
  }
  return adj()*(1/det());
}

bool Matrix::CreateEmptyMatrix(size_t rows, size_t cols) {
  // надо ли иниц-ть элементы матрицы нулями?
  matrix_ptr_ = new double* [rows];
  for (size_t count = 0; count < rows; count++)
    matrix_ptr_[count] = new double[cols];
  return true;
}

bool Matrix::ClearMatrixBody(size_t rows) const {
  for (size_t count = 0; count < rows; count++)
    delete [] matrix_ptr_[count];
  delete [] matrix_ptr_;
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

Matrix Matrix::AssembleMinor(size_t k, size_t l) const {
  Matrix temp_matrix(rows_ - 1, cols_ - 1);
  size_t m = 0;
  size_t n = 0;
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      if (i != k && j != l) {
        temp_matrix.matrix_ptr_[m][n] = matrix_ptr_[i][j];
        if (n == temp_matrix.cols_) {
          if (m == temp_matrix.rows_)
            break;
          n = 0;
          m++;
        }
      }
    }
  }
  return temp_matrix;
}

double Matrix::CalcCofactor(size_t i, size_t j) const {
  Matrix temp_matrix = AssembleMinor(i, j);
  return pow(-1, i+j) * temp_matrix.det();
}

}  // namespace prep
