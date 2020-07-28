/*
** EPITECH PROJECT, 2018
** my_printf
** File description:
** made by flo
*/

#include "include/my.h"

int enemypid;

void my_putstr_space(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        write(1, &str[i], 1);
        if (str[i + 1] != '\0')
            write(1, " ", 1);
    }
}

void print_navy(char **tab)
{
    int i = 0;
    int j = 0;
    my_putstr(" |A B C D E F G H\n");
    my_putstr("-+---------------\n");
    while (tab[i] != NULL){
        my_put_nbr(i + 1);
        my_putstr("|");
        my_putstr_space(tab[i]);
        my_putstr("\n");
        i++;
    }
}

void host_side_handler(int signum, siginfo_t *siginfo, void *context)
{
    if (signum == SIGUSR1){
        my_putstr("\nenemy connected\n");
        usleep(1000);
        enemypid = siginfo->si_pid;
        kill(siginfo->si_pid, SIGUSR2);
    }
}

void player_side_handler(int signum, siginfo_t *siginfo, void *context)
{
    if (signum == SIGUSR2){
        my_putstr("successfully connected\n");
        enemypid = siginfo->si_pid;
        usleep(1000);
    }
}

void h_player_get_attack(int signum, siginfo_t *siginfo, void *context)
{
    if (signum == SIGUSR2){
        usleep(1000);
    }
}

void display_mypid()
{
    my_putstr("my_pid: ");
    my_put_nbr(getpid());
    my_putstr("\n");
}

void get_attack(t_navy *na)
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = h_player_get_attack;
    sigaction(SIGUSR2, &sa, NULL);
}

void send_attack(t_navy *na, char *str)
{
    int fd = open("save", O_RDWR | O_CREAT, 0644);
    write(fd, str, 2);
    kill(enemypid, SIGUSR2);
}

void h_host_ack(int signum, siginfo_t *siginfo, void *context)
{
    if (signum == SIGUSR2)
        usleep(1000);
}


void update_tab(t_navy *na, char **tab, char *str)
{
    int x = str[0] - '0' - 16;
    int y = str[1] - '0';
    int fd = open("hm", O_RDWR | O_CREAT, 0644);
    
    if (tab[y - 1][x - 1] == '.') {
        tab[y - 1][x - 1] = 'o';
        write(fd, "m", 1);
        my_putstr(str);
        my_putstr(": missed\n");
    } else {
        tab[y - 1][x - 1] = 'x';
        write(fd, "h", 1);
        my_putstr(str);
        my_putstr(": hit\n");
    }
    kill(enemypid, SIGUSR2);
}

void hit_or_miss(t_navy *na, char *str)
{
    char *hm = malloc(1);
    int x = str[0] - '0' - 16 - 1;
    int y = str[1] - '0' - 1;
    int fd = open("hm", O_RDWR);
    str[my_strlen(str) - 1] = '\0';
    read(fd, hm, 1);
    if (hm[0] == 'h') {
        na->adv_tab[y][x] = 'x';
        my_putstr(str);
        my_putstr(": hit\n");
    } else {
        na->adv_tab[y][x] = 'o';
        my_putstr(str);
        my_putstr(": missed\n");
    }
}

int is_valid(char *str)
{
    if (my_strlen(str) != 3)
        return (0);
    if (str[0] < 'A' || str[0] > 'H')
        return (0);
    if (str[1] < '0' || str[1] > '8')
        return (0);
    return (1);
}

int is_winning(t_navy *na)
{
    int i = 0;
    int j = 0;
    int c = 0;
    int cc = 0;
    for (i = 0; na->adv_tab[i] != NULL; i++){
        for (j = 0; na->adv_tab[i][j] != '\0'; j++)
            if (na->adv_tab[i][j] == 'x')
                c++;
    }
    for (i = 0; na->my_tab[i] != NULL; i++){
        for (j = 0; na->my_tab[i][j] != '\0'; j++)
            if (na->my_tab[i][j] == 'x')
                cc++;
    }
    if (c == 14)
        return (1);
    if (cc == 14)
        return (2);
    return (0);
}

int host_play(t_navy *na)
{
    char *str;
    char *tmp = malloc(2);
    char *e_attack = malloc(3);
    int fd;
    struct sigaction sa;
    my_putstr("\n");
    my_putstr("my positions:\n");
    print_navy(na->my_tab);
    my_putstr("\n");
    my_putstr("enemy's positions:\n");
    print_navy(na->adv_tab);
    my_putstr("\n");
    my_putstr("attack: ");
    str = get_next_line(0);
    if (str == NULL)
        return (0);
    while (is_valid(str) != 1) {
        my_putstr("wrong position\n");
        my_putstr("attack: ");
        str = get_next_line(0);
        if (str == NULL)
            return (0);
    }
    send_attack(na, str);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = h_host_ack;
    sigaction(SIGUSR2, &sa, NULL);
    pause();
    hit_or_miss(na, str);
    if (is_winning(na) == 2){
        my_putstr("Enemy won\n");
        return (1);
    }
    if (is_winning(na) == 1){
        my_putstr("I won\n");
        return (0);
    }
    my_putstr("\nwaiting for enemy's attack...\n");
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = h_host_ack;
    sigaction(SIGUSR2, &sa, NULL);
    pause();
    fd = open("save", O_RDWR | O_CREAT, 0644);
    read(fd, e_attack, 2);
    update_tab(na, na->my_tab, e_attack);
    if (is_winning(na) == 2){
        my_putstr("Enemy won\n");
        return (1);
    }
    if (is_winning(na) == 1){
        my_putstr("I won\n");
        return (0);
    }
    return (host_play(na));
}

int player_play(t_navy *na)
{
    struct sigaction sa;
    int fd;
    char *e_attack = malloc(3);
    char *str;
    char *tmp = malloc(2);
    my_putstr("\n");
    my_putstr("my positions:\n");
    print_navy(na->my_tab);
    my_putstr("\n");
    my_putstr("enemy's positions:\n");
    print_navy(na->adv_tab);
    my_putstr("\n");
    my_putstr("waiting for enemy's attack...\n");
    get_attack(na);
    pause();
    fd = open("save", O_RDWR | O_CREAT, 0644);
    read(fd, e_attack, 2);
    update_tab(na, na->my_tab, e_attack);
    if (is_winning(na) == 2){
        my_putstr("Enemy won\n");
        return (1);
    }
    if (is_winning(na) == 1){
        my_putstr("I won\n");
        return (0);
    }
    my_putstr("\nattack: ");
    str = get_next_line(0);
    if (str == NULL)
        return (0);
    while (is_valid(str) != 1) {
        my_putstr("wrong position\n");
        my_putstr("attack: ");
        str = get_next_line(0);
        if (str == NULL)
            return (0);
    }
    send_attack(na, str);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = h_host_ack;
    sigaction(SIGUSR2, &sa, NULL);
    pause();
    hit_or_miss(na, str);
    if (is_winning(na) == 2){
        my_putstr("Enemy won\n");
        return (1);
    }
    if (is_winning(na) == 1){
        my_putstr("I won\n");
        return (0);
    }
    return (player_play(na));
}

int my_put_nav(t_navy *na, char *c1, char *c2, char c)
{
    int ri = (c1[0] - '0' - 17) - (c2[0] - '0' - 17);
    int rj = (c1[1] - '0') - (c2[1] - '0');
    int x = c1[0] - '0' - 17;
    int y = c1[1] - '0';
    if (ri < 0)
        ri = ri * -1;
    if (rj < 0)
        rj = rj * -1;
    if (ri == 0 && rj == 0)
        return (84);
    if (ri > 0 && rj > 0)
        return (84);
    if (ri > 0)
        for (int i = 0; i <= ri; i++)
            na->my_tab[y][x + i] = c;
    if (rj > 0)
        for (int i = 0; i <= rj; i++)
            na->my_tab[y + i][x] = c;
    return (0);
}

int make_map(t_navy *na, char *map)
{
    int fd = open(map, O_RDONLY);
    char *buffer = malloc(1001);
    char **tab;
    char **info;
    int ret = 0;
    read(fd, buffer, 1000);
    if (fd == -1)
        return (84);
    tab = my_str_to_wordtoken(buffer, "\n");
    for (int i = 0; tab[i + 1] != NULL; i++){
        info = my_str_to_wordtoken(tab[i], ":");
        ret = my_put_nav(na, info[1], info[2], info[0][0]);
        if (ret == 84)
            return (84);
    }
    return (0);
}

char **make_navy(char **tab)
{
    int i = 0;
    tab = malloc(sizeof(char *) * (8) + 1);
    for (i = 0; i != 8; i++){
        tab[i] = my_strdup("........\0");
    }
    tab[i] = NULL;
    return (tab);
}

void init_na(t_navy *na)
{
    na->my_tab = make_navy(na->my_tab);
    na->adv_tab = make_navy(na->adv_tab);
}

int player_side(t_navy *na, int pid, char *map)
{
    int ret = 0;
    struct sigaction sa;
    init_na(na);
    ret = make_map(na, map);
    if (ret == 84)
        return (84);
    display_mypid();
    kill(pid, SIGUSR1);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = player_side_handler;
    sigaction(SIGUSR2, &sa, NULL);
    pause();
    player_play(na);
}

int host_side(t_navy *na, char *map)
{
    int ret = 0;
    struct sigaction sa;
    init_na(na);
    ret = make_map(na, map);
    if (ret == 84)
        return (84);
    display_mypid();
    my_putstr("waiting for enemy connection...\n");
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = host_side_handler;
    sigaction(SIGUSR1, &sa, NULL);
    pause();
    return(host_play(na));
}

int main(int ac, char **av){
    t_navy *na = malloc(sizeof(t_navy));
    if (ac == 2)
        return (host_side(na, av[1]));

    if (ac == 3)
        return (player_side(na, my_getnbr(av[1]), av[2]));
        
}
