#pragma once // NOLINT


#include <limits>
#include <vector>
#include <istream>

#define CONST_COMPARE_PRECISION 7

namespace prep {
class Matrix {
 public:
  explicit Matrix(size_t rows = 0, size_t cols = 0);
  explicit Matrix(std::istream& is);
  Matrix(const Matrix& rhs);
  Matrix& operator=(const Matrix& rhs);
  ~Matrix();

  size_t getRows() const;
  size_t getCols() const;

  double operator()(size_t i, size_t j) const;
  double& operator()(size_t i, size_t j);

  bool operator==(const Matrix& rhs) const;
  bool operator!=(const Matrix& rhs) const;

  Matrix operator+(const Matrix& rhs) const;
  Matrix operator-(const Matrix& rhs) const;
  Matrix operator*(const Matrix& rhs) const;

  Matrix operator*(double val) const;

  friend
  Matrix operator*(double val, const Matrix& matrix);
  friend
  std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

  Matrix transp() const;
  double det() const;
  Matrix adj() const;
  Matrix inv() const;

 private:
  size_t rows_;
  size_t cols_;
  double **matrix_ptr_;

  bool CreateEmptyMatrix(size_t rows = 0, size_t cols = 0);
  bool CopyMatrix(const Matrix& prev_matrix);
  bool ClearMatrixBody(size_t rows) const;
  Matrix AssembleMinor(size_t k, size_t l) const;
  double CalcCofactor(size_t i, size_t j) const;
};

bool CompareDouble(const double first, const double second, const int precis = CONST_COMPARE_PRECISION);

Matrix operator*(double val, const Matrix& matrix);
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
}  // namespace prep
