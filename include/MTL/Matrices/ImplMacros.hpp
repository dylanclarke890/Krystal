
#pragma region Base

#define KRYS_MATRIX_PROPERTIES(RL, CL)                                                                       \
private:                                                                                                     \
  static constexpr vec_length_t RowLength = RL;                                                              \
  static constexpr vec_length_t ColLength = CL;                                                              \
                                                                                                             \
public:                                                                                                      \
  using component_t = TComponent;                                                                            \
  using row_t = Vector<component_t, ColLength>;                                                              \
  using column_t = Vector<component_t, RowLength>;                                                           \
                                                                                                             \
  using mat_t = Matrix<component_t, RowLength, ColLength>;                                                   \
  using transpose_t = Matrix<component_t, ColLength, RowLength>;                                             \
                                                                                                             \
private:                                                                                                     \
  column_t _values[ColLength]

#define KRYS_MATRIX_ELEMENT_ACCESS()                                                                         \
  NO_DISCARD constexpr vec_length_t GetColLength() const noexcept                                            \
  {                                                                                                          \
    return ColLength;                                                                                        \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr vec_length_t GetRowLength() const noexcept                                            \
  {                                                                                                          \
    return RowLength;                                                                                        \
  }                                                                                                          \
                                                                                                             \
  template <vec_length_t Index>                                                                              \
  REQUIRES((Index < ColLength))                                                                              \
  NO_DISCARD constexpr const column_t &Get() const noexcept                                                  \
  {                                                                                                          \
    return _values[Index];                                                                                   \
  }                                                                                                          \
                                                                                                             \
  template <vec_length_t Index>                                                                              \
  REQUIRES((Index < ColLength))                                                                              \
  NO_DISCARD constexpr column_t &Get() noexcept                                                              \
  {                                                                                                          \
    return _values[Index];                                                                                   \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr const column_t &operator[](vec_length_t col) const noexcept                           \
  {                                                                                                          \
    KRYS_ASSERT(col < ColLength, "Index out of bounds", 0);                                                  \
    return _values[col];                                                                                     \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr column_t &operator[](vec_length_t col) noexcept                                       \
  {                                                                                                          \
    KRYS_ASSERT(col < ColLength, "Index out of bounds", 0);                                                  \
    return _values[col];                                                                                     \
  }

#pragma endregion Base

#pragma region Two Column Matrices

#define KRYS_MATRIX_TWO_COLUMNS_COMMON_CONSTRUCTORS()                                                        \
  explicit constexpr Matrix() noexcept : _values {column_t(component_t(0)), column_t(component_t(0))}        \
  {                                                                                                          \
  }                                                                                                          \
                                                                                                             \
  explicit constexpr Matrix(const column_t &col0, const column_t &col1) noexcept                             \
      : _values {column_t(col0), column_t(col1)}                                                             \
  {                                                                                                          \
  }                                                                                                          \
                                                                                                             \
  constexpr Matrix(const mat_t &other) noexcept : _values(other._values[0], other._values[1])                \
  {                                                                                                          \
  }                                                                                                          \
                                                                                                             \
  constexpr Matrix(mat_t &&other) noexcept : _values(std::move(other._values))                               \
  {                                                                                                          \
  }

#define KRYS_MATRIX_TWO_COLUMNS_ASSIGNMENT()                                                                 \
  constexpr mat_t &operator=(const mat_t &other) noexcept                                                    \
  {                                                                                                          \
    _values[0] = other._values[0];                                                                           \
    _values[1] = other._values[1];                                                                           \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  constexpr mat_t &operator=(mat_t &&other) noexcept                                                         \
  {                                                                                                          \
    _values[0] = std::move(other._values[0]);                                                                \
    _values[1] = std::move(other._values[1]);                                                                \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_TWO_COLUMNS_EQUALITY()                                                                   \
  constexpr bool operator==(const mat_t &other) const noexcept                                               \
  {                                                                                                          \
    return _values[0] == other._values[0] && _values[1] == other._values[1];                                 \
  }                                                                                                          \
                                                                                                             \
  constexpr bool operator!=(const mat_t &other) const noexcept                                               \
  {                                                                                                          \
    return !(*this == other);                                                                                \
  }

#define KRYS_MATRIX_TWO_COLUMNS_ADDITION()                                                                   \
  NO_DISCARD constexpr mat_t operator+(const mat_t &other) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] + other._values[0], _values[1] + other._values[1]);                              \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t operator+(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] + scalar, _values[1] + scalar);                                                  \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator+=(const mat_t &other) noexcept                                        \
  {                                                                                                          \
    *this = *this + other;                                                                                   \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator+=(component_t scalar) noexcept                                        \
  {                                                                                                          \
    *this = *this + scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_TWO_COLUMNS_SUBTRACTION()                                                                \
  NO_DISCARD constexpr mat_t operator-(const mat_t &other) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] - other._values[0], _values[1] - other._values[1]);                              \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t operator-(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] - scalar, _values[1] - scalar);                                                  \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator-=(const mat_t &other) noexcept                                        \
  {                                                                                                          \
    *this = *this - other;                                                                                   \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator-=(component_t scalar) noexcept                                        \
  {                                                                                                          \
    *this = *this - scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_TWO_COLUMNS_DIVISION()                                                                   \
  NO_DISCARD constexpr mat_t operator/(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    KRYS_ASSERT(scalar != 0, "Division by zero", 0);                                                         \
    return mat_t(_values[0] / scalar, _values[1] / scalar);                                                  \
  }                                                                                                          \
                                                                                                             \
  constexpr mat_t &operator/=(component_t scalar) noexcept                                                   \
  {                                                                                                          \
    *this = *this / scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_TWO_COLUMNS_COMMON_MULTIPLICATION()                                                      \
  NO_DISCARD constexpr mat_t operator*(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] * scalar, _values[1] * scalar);                                                  \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator*=(const mat_t &other) noexcept                                        \
  {                                                                                                          \
    *this = *this * other;                                                                                   \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator*=(component_t scalar) noexcept                                        \
  {                                                                                                          \
    *this = *this * scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_TWO_COLUMNS_UNARY()                                                                      \
  NO_DISCARD constexpr mat_t operator-() const noexcept                                                      \
  {                                                                                                          \
    return mat_t(-_values[0], -_values[1]);                                                                  \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t operator+() const noexcept                                                      \
  {                                                                                                          \
    return *this;                                                                                            \
  }

#pragma endregion Two Column Matrices

#pragma region Three Column Matrices

#define KRYS_MATRIX_THREE_COLUMNS_COMMON_CONSTRUCTORS()                                                      \
  explicit constexpr Matrix() noexcept                                                                       \
      : _values {column_t(component_t(0)), column_t(component_t(0)), column_t(component_t(0))}               \
  {                                                                                                          \
  }                                                                                                          \
                                                                                                             \
  explicit constexpr Matrix(const column_t &col0, const column_t &col1, const column_t &col2) noexcept       \
      : _values {column_t(col0), column_t(col1), column_t(col2)}                                             \
  {                                                                                                          \
  }                                                                                                          \
                                                                                                             \
  constexpr Matrix(const mat_t &other) noexcept                                                              \
      : _values(other._values[0], other._values[1], other._values[2])                                        \
  {                                                                                                          \
  }                                                                                                          \
                                                                                                             \
  constexpr Matrix(mat_t &&other) noexcept : _values(std::move(other._values))                               \
  {                                                                                                          \
  }

#define KRYS_MATRIX_THREE_COLUMNS_ASSIGNMENT()                                                               \
  constexpr mat_t &operator=(const mat_t &other) noexcept                                                    \
  {                                                                                                          \
    _values[0] = other._values[0];                                                                           \
    _values[1] = other._values[1];                                                                           \
    _values[2] = other._values[2];                                                                           \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  constexpr mat_t &operator=(mat_t &&other) noexcept                                                         \
  {                                                                                                          \
    _values[0] = std::move(other._values[0]);                                                                           \
    _values[1] = std::move(other._values[1]);                                                                           \
    _values[2] = std::move(other._values[2]);                                                                           \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_THREE_COLUMNS_EQUALITY()                                                                 \
  constexpr bool operator==(const mat_t &other) const noexcept                                               \
  {                                                                                                          \
    return _values[0] == other._values[0] && _values[1] == other._values[1]                                  \
           && _values[2] == other._values[2];                                                                \
  }                                                                                                          \
                                                                                                             \
  constexpr bool operator!=(const mat_t &other) const noexcept                                               \
  {                                                                                                          \
    return !(*this == other);                                                                                \
  }

#define KRYS_MATRIX_THREE_COLUMNS_ADDITION()                                                                 \
  NO_DISCARD constexpr mat_t operator+(const mat_t &other) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] + other._values[0], _values[1] + other._values[1],                               \
                 _values[2] + other._values[2]);                                                             \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t operator+(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] + scalar, _values[1] + scalar, _values[2] + scalar);                             \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator+=(const mat_t &other) noexcept                                        \
  {                                                                                                          \
    *this = *this + other;                                                                                   \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator+=(component_t scalar) noexcept                                        \
  {                                                                                                          \
    *this = *this + scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_THREE_COLUMNS_SUBTRACTION()                                                              \
  NO_DISCARD constexpr mat_t operator-(const mat_t &other) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] - other._values[0], _values[1] - other._values[1],                               \
                 _values[2] - other._values[2]);                                                             \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t operator-(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] - scalar, _values[1] - scalar, _values[2] - scalar);                             \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator-=(const mat_t &other) noexcept                                        \
  {                                                                                                          \
    *this = *this - other;                                                                                   \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator-=(component_t scalar) noexcept                                        \
  {                                                                                                          \
    *this = *this - scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_THREE_COLUMNS_DIVISION()                                                                 \
  NO_DISCARD constexpr mat_t operator/(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    KRYS_ASSERT(scalar != 0, "Division by zero", 0);                                                         \
    return mat_t(_values[0] / scalar, _values[1] / scalar, _values[2] / scalar);                             \
  }                                                                                                          \
                                                                                                             \
  constexpr mat_t &operator/=(component_t scalar) noexcept                                                   \
  {                                                                                                          \
    *this = *this / scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_THREE_COLUMNS_COMMON_MULTIPLICATION()                                                    \
  NO_DISCARD constexpr mat_t operator*(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] * scalar, _values[1] * scalar, _values[2] * scalar);                             \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator*=(const mat_t &other) noexcept                                        \
  {                                                                                                          \
    *this = *this * other;                                                                                   \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator*=(component_t scalar) noexcept                                        \
  {                                                                                                          \
    *this = *this * scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_THREE_COLUMNS_UNARY()                                                                    \
  NO_DISCARD constexpr mat_t operator-() const noexcept                                                      \
  {                                                                                                          \
    return mat_t(-_values[0], -_values[1], -_values[2]);                                                     \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t operator+() const noexcept                                                      \
  {                                                                                                          \
    return *this;                                                                                            \
  }

#pragma endregion Three Column Matrices

#pragma region Four Column Matrices

#define KRYS_MATRIX_FOUR_COLUMNS_COMMON_CONSTRUCTORS()                                                       \
  explicit constexpr Matrix() noexcept                                                                       \
      : _values {column_t(component_t(0)), column_t(component_t(0)), column_t(component_t(0)),               \
                 column_t(component_t(0))}                                                                   \
  {                                                                                                          \
  }                                                                                                          \
                                                                                                             \
  explicit constexpr Matrix(const column_t &col0, const column_t &col1, const column_t &col2,                \
                            const column_t &col3) noexcept                                                   \
      : _values {column_t(col0), column_t(col1), column_t(col2), column_t(col3)}                             \
  {                                                                                                          \
  }                                                                                                          \
                                                                                                             \
  constexpr Matrix(const mat_t &other) noexcept                                                              \
      : _values(other._values[0], other._values[1], other._values[2], other._values[3])                      \
  {                                                                                                          \
  }                                                                                                          \
                                                                                                             \
  constexpr Matrix(mat_t &&other) noexcept : _values(std::move(other._values))                               \
  {                                                                                                          \
  }

#define KRYS_MATRIX_FOUR_COLUMNS_ASSIGNMENT()                                                                \
  constexpr mat_t &operator=(const mat_t &other) noexcept                                                    \
  {                                                                                                          \
    _values[0] = other._values[0];                                                                           \
    _values[1] = other._values[1];                                                                           \
    _values[2] = other._values[2];                                                                           \
    _values[3] = other._values[3];                                                                           \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  constexpr mat_t &operator=(mat_t &&other) noexcept                                                         \
  {                                                                                                          \
    _values[0] = std::move(other._values[0]);                                                                           \
    _values[1] = std::move(other._values[1]);                                                                           \
    _values[2] = std::move(other._values[2]);                                                                           \
    _values[3] = std::move(other._values[3]);                                                                           \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_FOUR_COLUMNS_EQUALITY()                                                                  \
  constexpr bool operator==(const mat_t &other) const noexcept                                               \
  {                                                                                                          \
    return _values[0] == other._values[0] && _values[1] == other._values[1]                                  \
           && _values[2] == other._values[2] && _values[3] == other._values[3];                              \
  }                                                                                                          \
                                                                                                             \
  constexpr bool operator!=(const mat_t &other) const noexcept                                               \
  {                                                                                                          \
    return !(*this == other);                                                                                \
  }

#define KRYS_MATRIX_FOUR_COLUMNS_ADDITION()                                                                  \
  NO_DISCARD constexpr mat_t operator+(const mat_t &other) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] + other._values[0], _values[1] + other._values[1],                               \
                 _values[2] + other._values[2], _values[3] + other._values[3]);                              \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t operator+(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] + scalar, _values[1] + scalar, _values[2] + scalar, _values[3] + scalar);        \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator+=(const mat_t &other) noexcept                                        \
  {                                                                                                          \
    *this = *this + other;                                                                                   \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator+=(component_t scalar) noexcept                                        \
  {                                                                                                          \
    *this = *this + scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_FOUR_COLUMNS_SUBTRACTION()                                                               \
  NO_DISCARD constexpr mat_t operator-(const mat_t &other) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] - other._values[0], _values[1] - other._values[1],                               \
                 _values[2] - other._values[2], _values[3] - other._values[3]);                              \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t operator-(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] - scalar, _values[1] - scalar, _values[2] - scalar, _values[3] - scalar);        \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator-=(const mat_t &other) noexcept                                        \
  {                                                                                                          \
    *this = *this - other;                                                                                   \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator-=(component_t scalar) noexcept                                        \
  {                                                                                                          \
    *this = *this - scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_FOUR_COLUMNS_DIVISION()                                                                  \
  NO_DISCARD constexpr mat_t operator/(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    KRYS_ASSERT(scalar != 0, "Division by zero", 0);                                                         \
    return mat_t(_values[0] / scalar, _values[1] / scalar, _values[2] / scalar, _values[3] / scalar);        \
  }                                                                                                          \
                                                                                                             \
  constexpr mat_t &operator/=(component_t scalar) noexcept                                                   \
  {                                                                                                          \
    *this = *this / scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_FOUR_COLUMNS_COMMON_MULTIPLICATION()                                                     \
  NO_DISCARD constexpr mat_t operator*(component_t scalar) const noexcept                                    \
  {                                                                                                          \
    return mat_t(_values[0] * scalar, _values[1] * scalar, _values[2] * scalar, _values[3] * scalar);        \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator*=(const mat_t &other) noexcept                                        \
  {                                                                                                          \
    *this = *this * other;                                                                                   \
    return *this;                                                                                            \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t &operator*=(component_t scalar) noexcept                                        \
  {                                                                                                          \
    *this = *this * scalar;                                                                                  \
    return *this;                                                                                            \
  }

#define KRYS_MATRIX_FOUR_COLUMNS_UNARY()                                                                     \
  NO_DISCARD constexpr mat_t operator-() const noexcept                                                      \
  {                                                                                                          \
    return mat_t(-_values[0], -_values[1], -_values[2], -_values[3]);                                        \
  }                                                                                                          \
                                                                                                             \
  NO_DISCARD constexpr mat_t operator+() const noexcept                                                      \
  {                                                                                                          \
    return *this;                                                                                            \
  }

#pragma endregion Four Column Matrices
