#include "model.h"

void model_load(struct Model *model, char *modelPathInit) {
    FILE *modelFile = fopen(modelPathInit, "r");

	unsigned int VBO, VAO, EBO;

    int charCount = 0;
    int bufferSize = sizeof(char) * 300;
    char *str = malloc(bufferSize);
    char *modelBuffer = malloc(bufferSize);

    unsigned int vertCount = 0;
    unsigned int textCount = 0;
    unsigned int normCount = 0;
    unsigned int faceCount = 0;

    int vertSize = (sizeof(float) * 3) * 10;
    float *verts = malloc(vertSize);
    int textSize = (sizeof(float) * 2) * 10;
    float *texts = malloc(textSize);
    //int normSize;
    //float *norms;
    int faceSize = (sizeof(int) * 6) * 10;
    int *faces = malloc(faceSize);

    if (modelFile==NULL) perror ("Error opening model\n");
    else {
        while ((fgets(str, sizeof(char) * 300, modelFile)) != NULL) {
            if(str[0] == 'v') {
                if(str[1] == ' ') {
                    int coordCount = 0;
                    vertCount++;

                    char *coord = "";
                    int i = 2;
                    int j = 0;
                    while(str[i - 1] != '\n') {
                        if(str[i] == ' ' || str[i] == '\n') {
                            coordCount++;
                            verts[((vertCount - 1) * 3) + (coordCount - 1)] = atof(coord);
                            memset(coord,0,strlen(coord));
                            j = 0;
                        }
                        else {
                            coord[j] = str[i];
                            j++;
                        }
                        i++;
                    }
                    if(vertCount * sizeof(float) * 3 >= vertSize) {
                        vertSize += (sizeof(float) * 3) * 10;
                        verts = realloc(verts, vertSize);
                    }
                }
                else if(str[1] == 't') {
                    if(str[2] == ' ') {
                        int coordCount = 0;
                        textCount++;

                        char *coord = "";
                        int i = 3;
                        int j = 0;
                        while(str[i - 1] != '\n') {
                            if(str[i] == ' ' || str[i] == '\n') {
                                coordCount++;
                                texts[((textCount - 1) * 2) + (coordCount - 1)] = atof(coord);
                                memset(coord,0,strlen(coord));
                                j = 0;
                            }
                            else {
                                coord[j] = str[i];
                                j++;
                            }
                            i++;
                        }
                        if(textCount * sizeof(float) * 2 >= textSize) {
                            textSize += (sizeof(float) * 2) * 10;
                            texts = realloc(texts, textSize);
                        }
                    }
                }
                else if(str[1] == 'n') {
                    normCount++;
                }
            }
            if(str[0] == 'f') {
                int indexCount = 0;
                faceCount++;

                char *index = "";
                int i = 2;
                int j = 0;
                while(str[i - 1] != '\n') {
                    if(str[i] == '/') {
                        indexCount++;
                        faces[((faceCount - 1) * 6) + (indexCount - 1)] = atoi(index);
                        memset(index,0,strlen(index));
                        j = 0;
                    }
                    else if(str[i] == ' ' || str[i] == '\n') {
                        indexCount++;
                        faces[((faceCount - 1) * 6) + (indexCount - 1)] = atoi(index);
                        memset(index,0,strlen(index));
                        j = 0;
                    }
                    else {
                        index[j] = str[i];
                        j++;
                    }
                    i++;
                }
                if(faceCount * sizeof(int) * 6 >= faceSize - (sizeof(int) * 6)) {
                    faceSize += (sizeof(int) * 6) * 10;
                    faces = realloc(faces, faceSize);
                }
            }
            strcpy(&modelBuffer[charCount], str);
            charCount += sizeof(char) * strlen(str);
            if(charCount * sizeof(char) >= bufferSize - (sizeof(char) * 300)) {
                bufferSize += sizeof(char) * 2000;
                modelBuffer = realloc(modelBuffer, bufferSize);
            }
        }
        while (charCount < bufferSize) {
            modelBuffer[charCount++] = 0x00;
        }
    }

    int *indices = malloc(sizeof(int) * faceCount * 3);
    int p = 0;
    if(normCount == 0) {
        for(int i = 0; i < 6 * faceCount; i += 6) {
            indices[p] = faces[i] - 1;
            indices[p + 1] = faces[i + 2] - 1;
            indices[p + 2] = faces[i + 4] - 1;
            p += 3;
        }
    }
    else {
        for(int i = 0; i < 9 * faceCount; i += 9) {
            indices[p] = faces[i] - 1;
            indices[p + 1] = faces[i + 3] - 1;
            indices[p + 2] = faces[i + 6] - 1;
            p += 3;
        }
    }

    int *correspondence;
    if(textCount > 0) {
        correspondence = malloc(sizeof(int) * vertCount);
        for(int i = 0; i < ((faceCount - 1) * 6) + 5; i += 2) {
            correspondence[faces[i]] = faces[i + 1];
        }
    }

    float *vertices = malloc(sizeof(float) * vertCount * 5);

    int j = 0;
    int k = 0;
    for(int i = 0; i < vertCount; i++) {
        vertices[j] = verts[k];
        vertices[j+1] = verts[k+1];
        vertices[j+2] = verts[k+2];
        if(textCount > 0) {
            vertices[j + 3] = texts[(correspondence[i + 1] - 1) * 2];
            vertices[j + 4] = texts[((correspondence[i + 1] - 1) * 2) + 1];
            j += 5;
            k += 3;
        }
        else {
            j += 3;
            k += 3;
        }
    }

    printf("\n");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * vertCount, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * faceCount, indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    model->vertices = vertices;
    model->indices = indices;
    model->faceCount = faceCount;
    model->vertCount = vertCount;
	model->VAO = VAO;
	model->VBO = VBO;
	model->EBO = EBO;
}
