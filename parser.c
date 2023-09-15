#include <stdio.h>
#include "parser.h"
#include <string.h>

int parser(FILE *file);

int main(int argc, char *argv[]) {

    FILE *fichero;
    fichero = fopen(argv[1], "r");

    if (argc == 2 && fichero != NULL) {

        parser(fichero);

    } else {

        parser(stdin);
    }


    return 0;
}

int parser(FILE *file) {

    char buffer[MaxLinea];

    struct variables {
        char dato[20];
    } campos[MaxCampos];

    int j = 0;
    int i = 0;
    unsigned int len;
    int ncampos = 0;
    const char del[2] = ",";
    char *token;


    fgets(buffer, MaxLinea + 1, file);

    len = strlen(buffer);
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }


    token = strtok(buffer, del);

    while (token != NULL) {


        if (ncampos > MaxCampos) {
            fprintf(stderr, "Error\n");
            return -1;
        }

        ncampos++;

        if (ncampos <= MaxCampos && token != NULL) {
            strcpy(campos[j].dato, token);

            token = strtok(NULL, del);

            /* printf("%s", campos[j].dato);*/

            j++;

        }


    }


    while (fgets(buffer, MaxLinea + 1, file)) {

        len = strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        token = strtok(buffer, del);

        while (token != NULL) {

            while (i < ncampos) {

                if (i < ncampos - 1) {

                    printf("%s: %s; ", campos[i].dato, token);

                } else {

                    printf("%s: %s", campos[i].dato, token);
                }

                i++;
                token = strtok(NULL, del);
            }

            i = 0;
            putc('\n', stdout);


        }


    }

    fclose(file);
    return 0;
}