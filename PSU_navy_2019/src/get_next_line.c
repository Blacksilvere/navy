/*
** EPITECH PROJECT, 2018
** bsq
** File description:
** 
*/

#include "../include/my.h"

char *get_next_line(int fd)
{
    static char buff[1 + 1];
    static int r = 0;
    char *output = malloc(500);
    int i = 0;
    int j = 0;
    i = 0;
    while (read(fd, buff, 1) != 0){
        if (buff[0] == '\n') {
            output[i] = buff[0];
            break;
        }
        output[i] = buff[0];
        i++;
    }
    if (output[0] == '\0')
        return (NULL);
    return (output);
}
