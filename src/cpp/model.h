#ifndef OPENGL_MODEL_H
#define OPENGL_MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>


struct Model {
    unsigned int ID;
    int vertCount;
    int faceCount;
    int *indices;
    float *vertices;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};

void model_load(struct Model *model, char *modelPathInit);

#endif //OPENGL_MODEL_H
