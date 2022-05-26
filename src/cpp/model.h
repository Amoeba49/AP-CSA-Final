//
// Created by Andrue on 5/23/2022.
//

#ifndef OPENGL_MODEL_H
#define OPENGL_MODEL_H

#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Model {
    unsigned int ID;
};

void model_load(struct Model *model, char *modelPathInit);

#endif //OPENGL_MODEL_H
