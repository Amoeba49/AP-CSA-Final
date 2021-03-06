#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "matrix.h"

struct Shader {
    unsigned int ID;
};

void check_compile_errors(unsigned int shader, char *type);

void shader_load(struct Shader *shader, char *vertexPathInit, char *fragmentPathInit);
void shader_use(struct Shader *shader);

void shader_set_bool(struct Shader *shader, const char *name, int value);
void shader_set_int(struct Shader *shader, const char *name, int value);
void shader_set_float(struct Shader *shader, const char *name, float value);
void shader_set_mat4x4(struct Shader *shader, const char *name, int transpose, Matrix *matrix_ptr);

#endif //OPENGL_SHADER_H