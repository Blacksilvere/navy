/*
** EPITECH PROJECT, 2019
** projet
** File description:
** print alpha
*/

#include "../include/my.h"

int nb_len(int nb)
{
    int j = 0;
    while (nb > 0) {
        nb = nb / 10;
        j++;
    }
    return (j);
}

int my_dozen(int nb)
{
    int i = 1;
    int tmp = nb;
    if (nb == 2147483647)
        return (1000000000);
    while (tmp / i > 0)
        i = i * 10;
    return (i / 10);
}

void print(int nb)
{
    int d = my_dozen(nb);
    int n = nb_len(nb);
    int r;
    int tmp = nb;
    int i = 0;

    while (i != nb_len(nb)) {
        tmp = nb / d;
        d = d / 10;
        r = (tmp % 10) + '0';
        write(1, &r, 1);
        i++;
    }
}

int my_put_nbr(int nb)
{
    if (nb == -2147483648){
        write(1, "-2147483648", 11);
        return (0);
    }
    if (nb == 2147483648){
        write(1, "2147483648", 10);
        return (0);
    }
    if (nb > 0){
        print(nb);
    }
    else if (nb < 0){
        nb = nb * -1;
        write(1, "-", 1);
        print(nb);
    } else
        write(1, "0", 1);
}
