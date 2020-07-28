/*
** EPITECH PROJECT, 2019
** delivery
** File description:
** verif_navy.c
*/

#include "../include/my.h"

int verif_bat(t_navy *na)
{
    int tres_petit_bat = 0;
    int petit_bat = 0;
    int moyen_bat = 0;
    int grand_bat = 0;

    for(int i = 0; na->my_tab[i] != NULL; i++){
        for(int x = 0; na->my_tab[i][x] != '\0'; x++){
            if (na->my_tab[i][x] == 2){
                tres_petit_bat++;
            }
            if (na->my_tab[i][x] == 3){
                petit_bat++;
            }
            if (na->my_tab[i][x] == 4){
                moyen_bat++;
            }
            if (na->my_tab[i][x] == 5){
                grand_bat++;
            }
        }
    }
    if (tres_petit_bat == 2 && petit_bat == 3 
    && moyen_bat == 4 && grand_bat == 5){
        return (0);
    }
    else{
        return (84);
    }
    return (0);
}

int verif_map(t_navy *na, int y, int x)
{
    if (na->adv_tab[y][x] == 'o' | na->adv_tab[y][x] == 'x'){
        my_putstr("wrong position\n");
    }
    if (na->my_tab[y][x] == 'o' | na->my_tab[y][x] == 'x'){
        my_putstr("wrong position\n");
    }
}