#include "vector.h"

void vector_create(Vector *vector, int size, float values[]) {
    float *value_ptr = malloc(sizeof(float) * size);

    for(int i = 0; i < size; i++) {
        value_ptr[i] = values[i];
    }

    vector->size = size;
    vector->values = value_ptr;
}

void vector_set(Vector *vector, int n, float value) {
    vector->values[n] = value;
}

float vector_get(Vector *vector, int n) {
    return vector->values[n];
}

Vector *vector_add(Vector *vectorA, Vector *vectorB) {
    Vector productVec;
    vector_create(&productVec, 3, (float []){0, 0, 0});

    if(vectorA->size != vectorB->size) {
        printf("unable to calculate addition: vectors are of differing sizes");
        return &productVec;
    }
    else {
        vector_set(&productVec, 0, vector_get(vectorA, 0) + vector_get(vectorB, 0));
        vector_set(&productVec, 1, vector_get(vectorA, 1) + vector_get(vectorB, 1));
        vector_set(&productVec, 2, vector_get(vectorA, 2) + vector_get(vectorB, 2));

        return &productVec;
    }
}

Vector *vector_sub(Vector *vectorA, Vector *vectorB) {
    Vector productVec;
    vector_create(&productVec, 3, (float []){0, 0, 0});

    if(vectorA->size != vectorB->size) {
        //printf("unable to calculate subtraction: vectors are of differing sizes");
        return &productVec;
    }
    else {
        vector_set(&productVec, 0, vector_get(vectorA, 0) - vector_get(vectorB, 0));
        vector_set(&productVec, 1, vector_get(vectorA, 1) - vector_get(vectorB, 1));
        vector_set(&productVec, 2, vector_get(vectorA, 2) - vector_get(vectorB, 2));

        return &productVec;
    }
}

Vector *vector_scalar_mul(Vector *vector, float scalar) {
    Vector productVec;
    vector_create(&productVec, 3, (float []){0, 0, 0});

    for(int i = 0; i < 3; i++) {
        vector_set(&productVec, i, vector_get(vector, i) * scalar);
    }

    return &productVec;
}

Vector *vec_scalar_div(Vector *vector, float scalar) {
    Vector productVec;
    vector_create(&productVec, 3, (float []){0, 0, 0});

    for(int i = 0; i < 3; i++) {
        vector_set(&productVec, 1, vector_get(vector, 1) / scalar);
    }

    return &productVec;
}

float vector_dot(Vector *vectorA, Vector *vectorB) {
    if(vectorA->size != vectorB->size) {
        printf("unable to calculate dot product: vectors are of differing sizes");
        return 0.0f;
    }
    else {
        float product = 0.0f;

        for(int i = 0; i < vectorA->size; i++) {
            product += (vectorA->values[i] * vectorB->values[i]);
        }

        return product;
    }
}

Vector *vector_cross(Vector *vectorA, Vector *vectorB) {
    Vector productVec;
    vector_create(&productVec, 3, (float []){0, 0, 0});

    if(vectorA->size != 3 && vectorB->size != 3) {
        printf("unable to calculate cross product: vectors are of differing sizes");
    }
    else {
        vector_create(&productVec, 3, (float []){0, 0, 0});
        vector_set(&productVec, 0, (vector_get(vectorA, 1) * vector_get(vectorB, 2)) - (vector_get(vectorA, 2) * vector_get(vectorB, 1)));
        vector_set(&productVec, 1, (vector_get(vectorA, 2) * vector_get(vectorB, 0)) - (vector_get(vectorA, 0) * vector_get(vectorB, 2)));
        vector_set(&productVec, 2, (vector_get(vectorA, 0) * vector_get(vectorB, 1)) - (vector_get(vectorA, 1) * vector_get(vectorB, 0)));
    }

    return &productVec;
}

void vector_normalize(Vector *vector) {
    float length = vec_length(vector);
    if(length > 0.0) {
        for (int i = 0; i < vector->size; i++) {
            vector_set(vector, i, vector_get(vector, i) / length);
        }
    }
}

float vec_length(Vector *vector) {
    return sqrt(vector_dot(vector, vector));
}


// -----------------------------------
// --------- DEBUG Functions ---------
// -----------------------------------
void vec_create_debug(Vector *vector, int size, float values[], char *func, char *file, int line) {
    printf("calling vector_create from %s in %s at line %d\n", func, file, line);
    float *value_ptr = malloc(sizeof(float) * size);

    for(int i = 0; i < size; i++) {
        value_ptr[i] = values[i];
    }

    vector->size = size;
    vector->values = value_ptr;
}

void vec_set_debug(Vector *vector, int n, float value, char *func, char *file, int line) {
    printf("calling vector_set from %s in %s at line %d\n", func, file, line);
    vector->values[n] = value;
}

float vec_get_debug(Vector *vector, int n, char *func, char *file, int line) {
    printf("calling vector_get from %s in %s at line %d\n", func, file, line);
    return vector->values[n];
}

Vector *vec_add_debug(Vector *vectorA, Vector *vectorB, char *func, char *file, int line) {
    printf("calling vector_add from %s in %s at line %d\n", func, file, line);

    Vector productVec;
    vector_create(&productVec, 3, (float []){0, 0, 0});

    if(vectorA->size != vectorB->size) {
        printf("unable to calculate addition: vectors are of differing sizes %d and %d\n", vectorA->size, vectorB->size);
        return &productVec;
    }
    else {
        vector_set(&productVec, 0, vector_get(vectorA, 0) + vector_get(vectorB, 0));
        vector_set(&productVec, 1, vector_get(vectorA, 1) + vector_get(vectorB, 1));
        vector_set(&productVec, 2, vector_get(vectorA, 2) + vector_get(vectorB, 2));

        return &productVec;
    }
}

Vector *vec_sub_debug(Vector *vectorA, Vector *vectorB, char *func, char *file, int line) {
    printf("calling vector_sub from %s in %s at line %d\n", func, file, line);

    Vector productVec;
    vector_create(&productVec, 3, (float []){0, 0, 0});

    if(vectorA->size != vectorB->size) {
        printf("unable to calculate subtraction: vectors are of differing sizes %d and %d\n", vectorA->size, vectorB->size);
        return &productVec;
    }
    else {
        vector_set(&productVec, 0, vector_get(vectorA, 0) - vector_get(vectorB, 0));
        vector_set(&productVec, 1, vector_get(vectorA, 1) - vector_get(vectorB, 1));
        vector_set(&productVec, 2, vector_get(vectorA, 2) - vector_get(vectorB, 2));

        return &productVec;
    }
}

Vector *vec_scalar_mul_debug(Vector *vector, float scalar, char *func, char *file, int line) {
    printf("calling vector_scalar_mul from %s in %s at line %d\n", func, file, line);

    Vector productVec;
    vector_create(&productVec, 3, (float []){0, 0, 0});

    for(int i = 0; i < 3; i++) {
        vector_set(&productVec, 1, vector_get(vector, 1) / scalar);
    }

    return &productVec;
}

Vector *vec_scalar_div_debug(Vector *vector, float scalar, char *func, char *file, int line) {
    printf("calling vec_scalar_div from %s in %s at line %d\n", func, file, line);

    Vector productVec;
    vector_create(&productVec, 3, (float []){0, 0, 0});

    for(int i = 0; i < 3; i++) {
        vector_set(&productVec, 1, vector_get(vector, 1) / scalar);
    }

    return &productVec;
}

float vec_dot_debug(Vector *vectorA, Vector *vectorB, char *func, char *file, int line) {
    printf("calling vector_dot from %s in %s at line %d\n", func, file, line);

    if(vectorA->size != vectorB->size) {
        printf("unable to calculate dot product: vectors are of differing sizes");
        return 0.0f;
    }
    else {
        float product = 0.0f;

        for(int i = 0; i < vectorA->size; i++) {
            product += (vectorA->values[i] * vectorB->values[i]);
        }

        return product;
    }
}

Vector *vec_cross_debug(Vector *vectorA, Vector *vectorB, char *func, char *file, int line) {
    printf("calling vector_cross from %s in %s at line %d\n", func, file, line);

    Vector productVec;
    vector_create(&productVec, 3, (float []){0, 0, 0});

    if(vectorA->size != 3 && vectorB->size != 3) {
        printf("unable to calculate cross product: vectors are of differing sizes");
    }
    else {
        vector_create(&productVec, 3, (float []){0, 0, 0});
        vector_set(&productVec, 0, (vector_get(vectorA, 1) * vector_get(vectorB, 2)) - (vector_get(vectorA, 2) * vector_get(vectorB, 1)));
        vector_set(&productVec, 1, (vector_get(vectorA, 2) * vector_get(vectorB, 0)) - (vector_get(vectorA, 0) * vector_get(vectorB, 2)));
        vector_set(&productVec, 2, (vector_get(vectorA, 0) * vector_get(vectorB, 1)) - (vector_get(vectorA, 1) * vector_get(vectorB, 0)));
    }

    return &productVec;
}

void vec_norm_debug(Vector *vector, char *func, char *file, int line) {
    printf("calling vector_normalize from %s in %s at line %d\n", func, file, line);

    float length = vec_length(vector);
    if(length > 0.0) {
        for (int i = 0; i < vector->size; i++) {
            vector_set(vector, i, vector_get(vector, i) / length);
        }
    }
}

float vec_length_debug(Vector *vector, char *func, char *file, int line) {
    printf("calling vec_length from %s in %s at line %d\n", func, file, line);

    return sqrt(vector_dot(vector, vector));
}
