//
// Created by Andrue on 5/23/2022.
//
#include "model.h"

void model_load(struct Model *model, char *modelPathInit) {
    FILE *modelFile = fopen(modelPathInit, "r");

    int n = 0;
    int size = sizeof (char) * 200;
    char c[100] = "\0";
    char *modelBuffer = malloc(size);
    if (modelFile==NULL) perror ("Error opening model\n");
    else {
        while ((fgets(c, sizeof c, modelFile)) != NULL) {
            strcpy(&modelBuffer[n], c);
            n += sizeof(char) * strlen(c);
            if(n >= size) {
                size += sizeof (char) * 200;
                modelBuffer = realloc(modelBuffer, size);
            }
        }
        while (n < size) {
            modelBuffer[n++] = 0x00;
        }
        modelBuffer[n] = '\n';
    }

    printf("%s", modelBuffer);

}
