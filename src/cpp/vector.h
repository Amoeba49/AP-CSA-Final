#include <malloc.h>
#include <stdio.h>
#include <math.h>

#ifndef OPENGL_VECTOR_H
#define OPENGL_VECTOR_H

typedef struct Vector {
    int size;
    float *values;
} Vector;

// --------- Constructor, Getter, Setter ---------
void vector_create(Vector *vector, int size, float values[]);
void vector_set(Vector *vector, int n, float value);
float vector_get(Vector *vector, int n);
// --------- Vector Arithmetic ---------
Vector *vector_add(Vector *vectorA, Vector *vectorB);
Vector *vector_sub(Vector *vectorA, Vector *vectorB);
Vector *vector_scalar_mul(Vector *vector, float scalar);
Vector *vec_scalar_div(Vector *vector, float scalar);
// --------- Vector Operations ---------
float vector_dot(Vector *vectorA, Vector *vectorB);
Vector *vector_cross(Vector *vectorA, Vector *vectorB);
void vector_normalize(Vector *vector);
float vec_length(Vector *vector);


// --------- DEBUG Functions ---------
// -----------------------------------
void vec_create_debug(Vector *vector, int size, float values[], char *func, char *file, int line);
void vec_set_debug(Vector *vector, int n, float value, char *func, char *file, int line);
float vec_get_debug(Vector *vector, int n, char *func, char *file, int line);

Vector *vec_add_debug(Vector *vectorA, Vector *vectorB, char *func, char *file, int line);
Vector *vec_sub_debug(Vector *vectorA, Vector *vectorB, char *func, char *file, int line);
Vector *vec_scalar_mul_debug(Vector *vector, float scalar, char *func, char *file, int line);
Vector *vec_scalar_div_debug(Vector *vector, float scalar, char *func, char *file, int line);

float vec_dot_debug(Vector *vectorA, Vector *vectorB, char *func, char *file, int line);
Vector *vec_cross_debug(Vector *vectorA, Vector *vectorB, char *func, char *file, int line);
void vec_norm_debug(Vector *vector, char *func, char *file, int line);
float vec_length_debug(Vector *vector, char *func, char *file, int line);

// --------- DEBUG Header Guard ---------
// --------------------------------------
#ifdef DEBUG_ENABLED

#define vector_create(vector, size, values) vec_create_debug(vector, size, values, __FUNCTION__, __FILE__, __LINE__)
#define vector_set(vector, n, value) vec_set_debug(vector, n, value, __FUNCTION__, __FILE__, __LINE__)
#define vector_get(vector, value) vec_get_debug(vector, value, __FUNCTION__, __FILE__, __LINE__)
#define vector_add(vectorA, vectorB) vec_add_debug(vectorA, vectorB, __FUNCTION__, __FILE__, __LINE__)
#define vector_sub(vectorA, vectorB) vec_sub_debug(vectorA, vectorB, __FUNCTION__, __FILE__, __LINE__)
#define vector_scalar_mul(vector, scalar) vec_scalar_mul_debug(vector, scalar, __FUNCTION__, __FILE__, __LINE__)
#define vec_scalar_div(vector, scalar) vec_scalar_div_debug(vector, scalar, __FUNCTION__, __FILE__, __LINE__)
#define vector_dot(vectorA, vectorB) vec_dot_debug(vectorA, vectorB, __FUNCTION__, __FILE__, __LINE__)
#define vector_cross(vectorA, vectorB) vec_cross_debug(vectorA, vectorB, __FUNCTION__, __FILE__, __LINE__)
#define vector_normalize(vector) vec_norm_debug(vector, __FUNCTION__, __FILE__, __LINE__)

#endif

#endif //OPENGL_VECTOR_H
