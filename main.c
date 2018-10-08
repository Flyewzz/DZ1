//
//  main.c
//  A_1
//
//  Created by Sirius on 01.10.18.
//  Copyright © 2018 Sirius. All rights reserved.
//
/*
 Run Id = 9031
 Submit a solution for A- (Variant 8)
 Задача A-8. Задача об удалении лишних пробелов
 Time limit:    14 s
 Memory limit:    64 M
 Один из вариантов ускорения загрузки web-страниц - это уменьшить их размер. Например, за счет удаления незначащих пробелов.
 
 Составить программу построчной обработки текста, в результате которой каждая группа повторяющихся пробелов заменяется на один пробел.
 Текстовые строки подаются на стандартный ввод программы, результат программы должен подаваться на стандартный вывод.
 
 Процедура обработки должна быть оформлена в виде отдельной функции, которой подается на вход массив строк, выделенных в динамической памяти, и его длина.
 На выход функция должна возвращать массив обработанных строк.
 
 Программа должна уметь обрабатывать возникающие ошибки (например, ошибки выделения памяти).
 В случае возникновения ошибки нужно вывести в поток стандартного вывода сообщение "[error]" и завершить выполнение программы.
 
 ВАЖНО! Программа в любом случае должна возвращать 0. Не пишите return -1, exit(1) и т.п. Даже если обнаружилась какая-то ошибка, все равно необходимо вернуть 0! (и напечатать [error] в stdout).
 
 Examples
 Input    Output
 Hello,     World!
 singleword
 Hello, World!
 singleword
*/
#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef enum {false, true} bool;
bool error_status = false;
char** remove_spaces(char * const *const mas, const unsigned int size) {
    if (error_status == true) return NULL;
    char **array = malloc(size * sizeof(char*));
   // posix_memalign((void*)array, 64, size * sizeof(char*));
    register unsigned int top;
    for (int i = 0; i < size; ++i) {
        if (strlen(mas[i]) == 0) {
          for (int j = 0; j < i; ++j) free(array[j]);
            free(array);
            return NULL;
        }
        unsigned long len = strlen(mas[i]);
        array[i] = malloc((len+1)*sizeof(char));
        register bool space = false;
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
            if (symbol_count == 0) {
                if (symbol_count+1 >= BUFSIZE)
                    buffer = (char*)realloc(buffer, (BUFSIZE+=2) * sizeof(char));
                buffer[symbol_count++] = c;
                buffer[symbol_count] = '\0';
                continue;
            }
            if (top >= MASSIZE)
                mas = (char**)realloc(mas, ++MASSIZE * sizeof(char*));
            mas[top++] = buffer;
            buffer = (char*)malloc(BUFSIZE*sizeof(char));
            buffer[0] = '\0';
            ++cnt;
            symbol_count = 0;
            continue;
        }
        if (symbol_count+1 >= BUFSIZE)
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
    if (result != NULL) free(result);
    return 0;
}
