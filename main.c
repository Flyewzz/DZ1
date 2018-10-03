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
bool error_status = false;
char** remove_spaces(char * const *const mas, const unsigned int size) {
    if (size == 0 || error_status == true) return NULL;
    char **array = malloc(size * sizeof(char*));
   // posix_memalign((void*)array, 64, size * sizeof(char*));
    register unsigned int top;
    for (int i = 0; i < size; ++i) {
        register bool space = true;
        if (strlen(mas[i]) == 0) {
          for (int j = 0; j < i; ++j) free(array[j]);
            free(array);
            return NULL;
        }
        unsigned long len = strlen(mas[i]);
        array[i] = malloc((len+1)*sizeof(char));
        for (int j = 0; j < len+1; ++j) array[i][j] = '\0';
        top = 0;
        for (int j = 0; j < len; ++j) {
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
   // posix_memalign((void*)mas, 64, MASSIZE * sizeof(char*));
    char *buffer = (char*)malloc(BUFSIZE*sizeof(char));
    buffer[0]='\0';
    char c;
    int symbol_count = 0; //Счетчик символов в строке
 //   while (strncmp(buffer, "\n", strlen(buffer))) {
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            if (symbol_count == 0) {error_status = true; break;}
            if (top >= MASSIZE)
                mas = (char**)realloc(mas, ++MASSIZE * sizeof(char*));
            mas[top++] = buffer;
            buffer = (char*)malloc(BUFSIZE*sizeof(char));
            buffer[0] = '\0';
            ++cnt;
            symbol_count = 0;
            continue;
        }
        if (symbol_count >= BUFSIZE)
            buffer = (char*)realloc(buffer, (BUFSIZE+=2) * sizeof(char));
        buffer[symbol_count++] = c;
        buffer[symbol_count] = '\0';
    }
    if (symbol_count != 0) {
        if (top >= MASSIZE)
            mas = (char**)realloc(mas, ++MASSIZE * sizeof(char*));
        mas[top] = buffer;
        buffer = (char*)malloc(BUFSIZE*sizeof(char));
        ++cnt;
    }
    free(buffer);
char **result = remove_spaces(mas, cnt);
    if (error_status == false)
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
