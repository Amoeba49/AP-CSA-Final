#include <malloc.h>
#include <math.h>

#ifndef OPENGL_MATRIX_H
#define OPENGL_MATRIX_H
#define ROW_MAJOR 0
#define COL_MAJOR 1

typedef struct Matrix {
    int rows;
    int columns;
    int order;
    float *values;
} Matrix;

// --------- Constructor, Getter, Setter ---------
void matrix_create(Matrix *matrix, int r, int c, int order);
void matrix_set(Matrix *matrix, int r, int c, float value);
float matrix_get(Matrix *matrix, int r, int c);
// --------- Matrix Arithmetic ---------
Matrix *matrix_add(Matrix *matrixA, Matrix *matrixB);
Matrix *matrix_sub(Matrix *matrixA, Matrix *matrixB);
Matrix *matrix_matrix_mul(Matrix *matrixA, Matrix *matrixB);
Matrix *matrix_scalar_mul(Matrix *matrix, float scalar);
// --------- Matrix Operations ---------
void *matrix_identity(Matrix *matrix);
Matrix *matrix_transpose(Matrix *matrix);
Matrix *matrix_translate(float x, float y, float z);
Matrix *matrix_rotate(float x, float y, float z);
Matrix *matrix_scale(float x, float y, float z);


// --------- DEBUG Functions ---------
// -----------------------------------
void matrix_create_debug(Matrix *matrix, int r, int c, int order, char *func, char *file, int line);
void matrix_set_debug(Matrix *matrix, int r, int c, float value, char *func, char *file, int line);
float matrix_get_debug(Matrix *matrix, int r, int c, char *func, char *file, int line);

Matrix *matrix_add_debug(Matrix *matrixA, Matrix *matrixB, char *func, char *file, int line);
Matrix *matrix_sub_debug(Matrix *matrixA, Matrix *matrixB, char *func, char *file, int line);
Matrix *matrix_matrix_mul_debug(Matrix *matrixA, Matrix *matrixB, char *func, char *file, int line);
Matrix *matrix_scalar_mul_debug(Matrix *matrix, float scalar, char *func, char *file, int line);

void *matrix_identity_debug(Matrix *matrix, char *func, char *file, int line);
Matrix *matrix_transpose_debug(Matrix *matrix, char *func, char *file, int line);
Matrix *matrix_translate_debug(float x, float y, float z, char *func, char *file, int line);
Matrix *matrix_rotate_debug(float x, float y, float z, char *func, char *file, int line);
Matrix *matrix_scale_debug(float x, float y, float z, char *func, char *file, int line);


// --------- DEBUG Header Guard ---------
// --------------------------------------
#ifdef DEBUG_ENABLED

#define matrix_create(matrix, r, c, order) matrix_create_debug(matrix, r, c, order, __FUNCTION__, __FILE__, __LINE__)
#define matrix_set(matrix, r, c, value)  matrix_set_debug(matrix, r, c, value, __FUNCTION__, __FILE__, __LINE__)
#define matrix_get(matrix, r, c)  matrix_set_debug(matrix, r, c, __FUNCTION__, __FILE__, __LINE__)
#define matrix_add(matrixA, matrixB) matrix_add_debug(matrixA, matrixB, __FUNCTION__, __FILE__, __LINE__)
#define matrix_sub(matrixA, matrixB) matrix_sub_debug(matrixA, matrixB, __FUNCTION__, __FILE__, __LINE__)
#define matrix_scalar_mul(matrix, scalar) matrix_scalar_mul_debug(matrix, scalar, __FUNCTION__, __FILE__, __LINE__)
#define matrix_matrix_mul(matrixA, matrixB) matrix_matrix_mul_debug(matrixA, matrixB, __FUNCTION__, __FILE__, __LINE__)
#define matrix_identity(matrix) matrix_identity_debug(matrix, __FUNCTION__, __FILE__, __LINE__)
#define matrix_transpose(matrix) matrix_transpose_debug(matrix, __FUNCTION__, __FILE__, __LINE__)
#define matrix_translate(x, y, z) matrix_translate_debug(x, y, z, __FUNCTION__, __FILE__, __LINE__)
#define matrix_rotate(x, y, z) matrix_rotate_debug(x, y, z, __FUNCTION__, __FILE__, __LINE__)
#define matrix_scale(x, y, z) matrix_scale_debug(x, y, z, __FUNCTION__, __FILE__, __LINE__)

#endif

#endif //OPENGL_MATRIX_H
