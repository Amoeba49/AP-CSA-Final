//
// Created by Andrue on 5/21/2022.
//
#include "shader.h"

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void check_compile_errors(unsigned int shader, char *type) {
    int success;
    char infoLog[1024];
    if (type[0] != '\n') {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- \n", type, infoLog);
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- \n", type, infoLog);
        }
    }
}

void shader_load(struct Shader *shader, char *vertexPathInit, char *fragmentPathInit) {
    shader->ID = glCreateProgram();

    FILE *vShaderFile;
    FILE *fShaderFile;

    // open files
    vShaderFile = fopen(vertexPathInit, "r");
    fShaderFile = fopen(fragmentPathInit, "r");

    int n = 0;
    int size = sizeof (char) * 20;
    int c;

    char *vBuff = malloc(size);
    if (vShaderFile==NULL) perror ("Error opening vertex shader\n");
    else {
        while ((c = fgetc(vShaderFile)) != EOF) {
            if(n >= size) {
                size += sizeof (char) * 20;
                vBuff = realloc(vBuff, size);
            }
            vBuff[n++] = c;
        }
        while (n < size) {
            vBuff[n++] = 0x00;
        }
        vBuff[n] = '\n';
    }

    n = 0;
    size = sizeof (char) * 20;
    char *fBuff = malloc(size);
    if (fShaderFile==NULL) perror ("Error opening fragment shader\n");
    else {
        while ((c = fgetc(fShaderFile)) != EOF) {
            if(n >= size-1) {
                size += sizeof (char) * 20;
                fBuff = realloc(fBuff, size);
            }
            fBuff[n++] = c;
        }
        while (n < size) {
            fBuff[n++] = 0x00;
        }
        fBuff[n] = '\n';
    }

    // compile shaders
    unsigned int vertex, fragment;
    const char *vShaderCode = vBuff;
    const char *fShaderCode = fBuff;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT");
    // shader Program
    glAttachShader(shader->ID, vertex);
    glAttachShader(shader->ID, fragment);
    glLinkProgram(shader->ID);
    check_compile_errors(shader->ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
// activate the shader
// ------------------------------------------------------------------------
void shader_use(struct Shader *shader) {
    glUseProgram(shader->ID);
}
// utility uniform functions
// ------------------------------------------------------------------------
void shader_set_bool(struct Shader *shader, const char *name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}
// ------------------------------------------------------------------------
void shader_set_int(struct Shader *shader, const char *name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}
// ------------------------------------------------------------------------
void shader_set_float(struct Shader *shader, const char *name, float value) {
    glUniform1f(glGetUniformLocation(shader->ID, name), value);
}
