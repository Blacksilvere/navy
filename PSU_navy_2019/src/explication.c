/*
** EPITECH PROJECT, 2019
** delivery
** File description:
** -h.C
*/

#include"../include/my.h"

int fs_open_file(char const *filepath)
{
    struct stat buf;
    stat(filepath, &buf);
    int size = buf.st_size + 1;
    char* file = malloc(sizeof(char)*(size));
    int fd = open(filepath,O_RDONLY);
    read(fd,file,size);
    my_putstr(file);
}