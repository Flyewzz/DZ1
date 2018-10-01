//
//  main.c
//  A_1
//
//  Created by Sirius on 01.10.18.
//  Copyright © 2018 Sirius. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef enum {false, true} bool;
char** remove_spaces(char * const *const mas, const unsigned int size) {
    char **array = malloc(size * sizeof(char*));
    posix_memalign((void*)array, 8, size * sizeof(char*));
    register unsigned int top;
    for (int i = 0; i < size; ++i) {
        register bool space = true;
        array[i] = malloc(30);
        top = 0;
        // Работает!
        for (int j = 0; j < strlen(mas[i]); ++j) {
            if (mas[i][j] != ' ') {
                space = false;
                array[i][top++] = mas[i][j];
            }
            else {
                if (!space) {
                    array[i][top++] = mas[i][j];
                    space = true;
                }
                else continue;
            }
        }
    }
    return array;
}

unsigned int MASSIZE = 40;
unsigned int BUFSIZE = 30;

int main(int argc, const char * argv[]) {
    
    register unsigned int top = 0;
    register unsigned int cnt = 0;
    errno = 0;
    char ** mas = malloc(MASSIZE * sizeof(char*));
    posix_memalign((void*)mas, 8, MASSIZE * sizeof(char*));
    char *buffer = malloc(BUFSIZE);
    
    fgets(buffer, BUFSIZE, stdin);
    while (strncmp(buffer, "\n", BUFSIZE)) {
        mas[top++] = buffer;
        if (errno == ENOMEM) {
            printf("[error]");
            return 0;
        }
        ++cnt;
        buffer = malloc(BUFSIZE);
        fgets(buffer, BUFSIZE, stdin);
    }
char **result = remove_spaces(mas, cnt);
    for (int i = 0; i < cnt; ++i)
        printf("%s\n", result[i]);
    free(buffer);
    for (int i = 0; i < cnt; ++i) free(mas[i]);
    free(mas);
    free(result);
    return 0;
}
