//
//  main.c
//  A_1
//
//  Created by Sirius on 01.10.18.
//  Copyright © 2018 Sirius. All rights reserved.
//

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef enum {false, true} bool;
char** remove_spaces(char * const *const mas, const unsigned int size) {
    if (size == 0) return NULL;
    char **array = malloc(size * sizeof(char*));
  //  posix_memalign((void*)array, 64, size * sizeof(char*));
    register unsigned int top;
    for (int i = 0; i < size; ++i) {
        register bool space = true;
        array[i] = malloc(30);
        top = 0;
        for (int j = 0; j < strlen(mas[i]); ++j) {
            if (mas[i][j] == ' ') {
                if (space == true) continue;
                space = true;
            }
            else space = false;
            array[i][top++] = mas[i][j];
        }
    }
    return array;
}

size_t MASSIZE = 1;
size_t BUFSIZE = 2;

int main(int argc, const char * argv[]) {
    
    register unsigned int top = 0;
    register unsigned int cnt = 0;
    char ** mas = malloc(MASSIZE * sizeof(char*));
  //  posix_memalign((void*)mas, 64, MASSIZE * sizeof(char*));
    char *buffer;
 //   while (strncmp(buffer, "\n", strlen(buffer))) {
    while (1) {
        buffer = malloc(BUFSIZE * sizeof(char));
        getline(&buffer, &BUFSIZE, stdin);
        buffer = (char*)realloc(buffer, BUFSIZE * sizeof(char));
        if (!strcmp(buffer, "\n")) { free(buffer); break;}
        if (top >= MASSIZE)
            mas = (char**)realloc(mas, ++MASSIZE);
        mas[top++] = buffer;
        ++cnt;
    }

char **result = remove_spaces(mas, cnt);
    for (int i = 0; i < cnt; ++i) {
     printf("%s\n", result[i]);
        free(result[i]);
    }
    for (int i = 0; i < cnt; ++i) free(mas[i]);
    free(mas);
    if (result == NULL) printf("[error]\n");
    else
        free(result);
    return 0;
}
