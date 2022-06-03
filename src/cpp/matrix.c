#include "matrix.h"

void matrix_create(Matrix *matrix, int r, int c, int order) {
    float *values = malloc(sizeof(float) * r * c);

    for(int i = 0; i < r * c; i++) {
        values[i] = 0.0f;
    }

    matrix->rows = r;
    matrix->columns = c;
    matrix->order = order;
    matrix->values = values;
}

void matrix_set(Matrix *matrix, int r, int c, float value) {
    int index;

    if(matrix->order == 0) {
        index = (r * matrix->rows) +  c;
    }
    else {
        index = (c * matrix->columns) +  r;
    }

    matrix->values[index] = value;
}

float matrix_get(Matrix *matrix, int r, int c) {
    int index;

    if(matrix->order == 0) {
        index = (r * matrix->rows) +  c;
    }
    else {
        index = (c * matrix->columns) +  r;
    }

    return matrix->values[index];
}

Matrix *matrix_add(Matrix *matrixA, Matrix *matrixB) {
	Matrix product;
	matrix_create(&product, matrixA->rows, matrixA->columns, matrixA->order);

	if(matrixA->rows != matrixB->rows || matrixA->columns != matrixB->columns) {
		return &product;
	}

	for(int r = 0; r < matrixA->rows; r++) {
		for(int c = 0; c < matrixA->columns; c++) {
			matrix_set(&product, r, c, matrix_get(matrixA, r, c) + matrix_get(matrixB, r, c));
		}
	}

	return &product;
}

Matrix *matrix_sub(Matrix *matrixA, Matrix *matrixB) {
	Matrix product;
	matrix_create(&product, matrixA->rows, matrixA->columns, matrixA->order);

	if (matrixA->rows != matrixB->rows || matrixA->columns != matrixB->columns) {
		return &product;
	}

	for(int r = 0; r < matrixA->rows; r++) {
		for(int c = 0; c < matrixA->columns; c++) {
			matrix_set(&product, r, c, matrix_get(matrixA, r, c) - matrix_get(matrixB, r, c));
		}
	}

	return &product;
}

Matrix *matrix_matrix_mul(Matrix *matrixA, Matrix *matrixB) {
	Matrix product;
	matrix_create(&product, matrixA->rows, matrixB->columns, matrixA->order);

	if(matrixA->columns != matrixB->rows) {
		return &product;
	}

	for (int r = 0; r < matrixA->rows; r++) {
		for(int c = 0; c < matrixB->columns; c++) {
			float value = 0.0f;
			for(int i = 0; i < matrixA->columns; i++) {
				float a = matrix_get(matrixA, r, i);
				float b = matrix_get(matrixB, i, c);

				value += a * b;
			}
			matrix_set(&product, r, c, value);
		}
	}

	return &product;
}

Matrix *matrix_scalar_mul(Matrix *matrix, float scalar) {
	Matrix product;
	matrix_create(&product, matrix->rows, matrix->columns, matrix->order);

	for(int r = 0; r < matrix->rows; r++) {
		for(int c = 0; c < matrix->columns; c++) {
			matrix_set(&product, r, c, matrix_get(matrix, r, c) * scalar);
		}
	}

	return &product;
}

void *matrix_identity(Matrix *matrix) {
	if (matrix->rows == matrix->columns) {
		for (int r = 0; r < matrix->rows; r++) {
			matrix_set(matrix, r, r, 1.0f);
		}
	}
}


Matrix *matrix_transpose(Matrix *matrix) {
	Matrix product;
	matrix_create(&product, matrix->columns, matrix->rows, matrix->order);

	for(int r = 0; r < matrix->rows; r++) {
		for(int c = 0; c < matrix->columns; c++) {
			matrix_set(&product, r, c, matrix_get(matrix, c, r));
		}
	}

	return &product;
}

Matrix *matrix_translate(float x, float y, float z) {
	Matrix product;
	matrix_create(&product, 4, 4, COL_MAJOR);
	matrix_identity(&product);

	matrix_set(&product, 0, 3, x);
	matrix_set(&product, 1, 3, y);
	matrix_set(&product, 2, 3, z);

	return &product;
}

Matrix *matrix_rotate(float x, float y, float z) {
	Matrix product;
	matrix_create(&product, 4, 4, COL_MAJOR);
	matrix_identity(&product);

	matrix_set(&product, 0, 0, cos(z) * cos(y));
	matrix_set(&product, 0, 1, (cos(z) * sin(y) * sin(x)) - (sin(z) * cos(x)));
	matrix_set(&product, 0, 2, (cos(z) * sin(y) * cos(x)) + (sin(z) * sin(x)));
	matrix_set(&product, 1, 0, sin(z) * cos(y));
	matrix_set(&product, 1, 1, (sin(z) * sin(y) * sin(x)) + (cos(z) * cos(x)));
	matrix_set(&product, 1, 2, (sin(z) * sin(y) * cos(x)) - (cos(z) * sin(x)));
	matrix_set(&product, 2, 0, -sin(y));
	matrix_set(&product, 2, 1, cos(y) * sin(x));
	matrix_set(&product, 2, 2, cos(y) * cos(x));

	return &product;
}

Matrix *matrix_scale(float x, float y, float z) {
	Matrix product;
	matrix_create(&product, 4, 4, COL_MAJOR);
	matrix_identity(&product);

	matrix_set(&product, 0, 0, x);
	matrix_set(&product, 1, 1, y);
	matrix_set(&product, 2, 2, z);

	return &product;
}


// -----------------------------------
// --------- DEBUG Functions ---------
// -----------------------------------
void matrix_create_debug(Matrix *matrix, int r, int c, int order, char *func, char *file, int line) {
	printf("calling matrix_create from %s in %s at line %d\n", func, file, line);
	float *values = malloc(sizeof(float) * r * c);

	for (int i = 0; i < r * c; i++) {
		values[i] = 0.0f;
	}

	matrix->rows = r;
	matrix->columns = c;
	matrix->order = order;
	matrix->values = values;
}

void matrix_set_debug(Matrix *matrix, int r, int c, float value, char *func, char *file, int line) {
	printf("calling matrix_set from %s in %s at line %d\n", func, file, line);
	int index;

	if (matrix->order == 0) {
		index = (r * matrix->rows) + c;
	}
	else {
		index = (c * matrix->columns) + r;
	}

	matrix->values[index] = value;
}

float matrix_get_debug(Matrix *matrix, int r, int c, char *func, char *file, int line) {
	printf("calling matrix_get from %s in %s at line %d\n", func, file, line);
	int index;

	if (matrix->order == 0) {
		index = (r * matrix->rows) + c;
	}
	else {
		index = (c * matrix->columns) + r;
	}

	return matrix->values[index];
}

Matrix *matrix_add_debug(Matrix *matrixA, Matrix *matrixB, char *func, char *file, int line) {
	printf("calling matrix_add from %s in %s at line %d\n", func, file, line);
	Matrix product;
	matrix_create(&product, matrixA->rows, matrixA->columns, matrixA->order);

	if (matrixA->rows != matrixB->rows || matrixA->columns != matrixB->columns) {
		return &product;
	}

	for (int r = 0; r < matrixA->rows; r++) {
		for (int c = 0; c < matrixA->columns; c++) {
			matrix_set(&product, r, c, matrix_get(matrixA, r, c) + matrix_get(matrixB, r, c));
		}
	}

	return &product;
}

Matrix *matrix_sub_debug(Matrix *matrixA, Matrix *matrixB, char *func, char *file, int line) {
	printf("calling matrix_sub from %s in %s at line %d\n", func, file, line);
	Matrix product;
	matrix_create(&product, matrixA->rows, matrixA->columns, matrixA->order);

	if (matrixA->rows != matrixB->rows || matrixA->columns != matrixB->columns) {
		return &product;
	}

	for (int r = 0; r < matrixA->rows; r++) {
		for (int c = 0; c < matrixA->columns; c++) {
			matrix_set(&product, r, c, matrix_get(matrixA, r, c) - matrix_get(matrixB, r, c));
		}
	}

	return &product;
}

Matrix *matrix_matrix_mul_debug(Matrix *matrixA, Matrix *matrixB, char *func, char *file, int line) {
	printf("calling matrix_matrix_mul from %s in %s at line %d\n", func, file, line);
	Matrix product;
	matrix_create(&product, matrixA->rows, matrixB->columns, matrixA->order);

	if (matrixA->columns != matrixB->rows) {
		return &product;
	}

	for (int r = 0; r < matrixA->rows; r++) {
		for (int c = 0; c < matrixB->columns; c++) {
			float value = 0.0f;
			for (int i = 0; i < matrixA->columns; i++) {
				float a = matrix_get(matrixA, r, i);
				float b = matrix_get(matrixB, i, c);

				value += a * b;
			}
			matrix_set(&product, r, c, value);
		}
	}

	return &product;
}

Matrix *matrix_scalar_mul_debug(Matrix *matrix, float scalar, char *func, char *file, int line) {
	printf("calling matrix_scalar_mul from %s in %s at line %d\n", func, file, line);
	Matrix product;
	matrix_create(&product, matrix->rows, matrix->columns, matrix->order);

	for (int r = 0; r < matrix->rows; r++) {
		for (int c = 0; c < matrix->columns; c++) {
			matrix_set(&product, r, c, matrix_get(matrix, r, c) * scalar);
		}
	}

	return &product;
}

void *matrix_identity_debug(Matrix *matrix, char *func, char *file, int line) {
	printf("calling matrix_identity from %s in %s at line %d\n", func, file, line);
	if (matrix->rows == matrix->columns) {
		for (int r = 0; r < matrix->rows; r++) {
			matrix_set(matrix, r, r, 1.0f);
		}
	}
}


Matrix *matrix_transpose_debug(Matrix *matrix, char *func, char *file, int line) {
	printf("calling matrix_transpose from %s in %s at line %d\n", func, file, line);
	Matrix product;
	matrix_create(&product, matrix->columns, matrix->rows, matrix->order);

	for (int r = 0; r < matrix->rows; r++) {
		for (int c = 0; c < matrix->columns; c++) {
			matrix_set(&product, r, c, matrix_get(matrix, c, r));
		}
	}

	return &product;
}

Matrix *matrix_translate_debug(float x, float y, float z, char *func, char *file, int line) {
	printf("calling matrix_translate from %s in %s at line %d\n", func, file, line);
	Matrix product;
	matrix_create(&product, 4, 4, COL_MAJOR);
	matrix_identity(&product);

	matrix_set(&product, 0, 3, x);
	matrix_set(&product, 1, 3, y);
	matrix_set(&product, 2, 3, z);

	return &product;
}

Matrix *matrix_rotate_debug(float x, float y, float z, char *func, char *file, int line) {
	printf("calling matrix_rotate from %s in %s at line %d\n", func, file, line);
	Matrix product;
	matrix_create(&product, 4, 4, COL_MAJOR);
	matrix_identity(&product);

	matrix_set(&product, 0, 0, cos(z) * cos(y));
	matrix_set(&product, 0, 1, (cos(z) * sin(y) * sin(x)) - (sin(z) * cos(x)));
	matrix_set(&product, 0, 2, (cos(z) * sin(y) * cos(x)) + (sin(z) * sin(x)));
	matrix_set(&product, 1, 0, sin(z) * cos(y));
	matrix_set(&product, 1, 1, (sin(z) * sin(y) * sin(x)) + (cos(z) * cos(x)));
	matrix_set(&product, 1, 2, (sin(z) * sin(y) * cos(x)) - (cos(z) * sin(x)));
	matrix_set(&product, 2, 0, -sin(y));
	matrix_set(&product, 2, 1, cos(y) * sin(x));
	matrix_set(&product, 2, 2, cos(y) * cos(x));

	return &product;
}

Matrix *matrix_scale_debug(float x, float y, float z, char *func, char *file, int line) {
	printf("calling matrix_scale from %s in %s at line %d\n", func, file, line);
	Matrix product;
	matrix_create(&product, 4, 4, COL_MAJOR);
	matrix_identity(&product);

	matrix_set(&product, 0, 0, x);
	matrix_set(&product, 1, 1, y);
	matrix_set(&product, 2, 2, z);

	return &product;
}