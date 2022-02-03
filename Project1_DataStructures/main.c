/*Copyright 2021 Ilie David */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./header.h"

#define MAX_STRING_SIZE 64

int main() {
    doubly_linked_list_t *galaxie;
    int nr_commands, i;
    galaxie = dll_create(sizeof(struct planet));

    scanf("%d", &nr_commands);

    for (i = 0; i < nr_commands; i++) {
        char command[16], name[64], sens;
        int nr_shield, ind_shield, ind_planet, val, unit;
        scanf("%s", command);

        if (strcmp(command, "ADD") == 0) {
            scanf("%s", name);
            scanf("%d", &ind_planet);
            scanf("%d", &nr_shield);
            add_planet(galaxie, ind_planet, name, nr_shield);
        }
        if (strcmp(command, "BLH") == 0) {
            scanf("%d", &ind_planet);

            if (ind_planet >= (int)galaxie->size) {
                printf("Planet out of bounds!\n");
            } else {
                black_hole(galaxie, ind_planet);
            }
        }
        if (strcmp(command, "UPG") == 0) {
            scanf("%d %d %d", &ind_planet, &ind_shield, &val);
            upgrade(galaxie, ind_planet, ind_shield, val);
        }
        if (strcmp(command, "EXP") == 0) {
            scanf("%d %d", &ind_planet, &val);
            expand(galaxie, ind_planet, val);
        }
        if (strcmp(command, "RMV") == 0) {
            scanf("%d %d", &ind_planet, &ind_shield);
            remove_shield(galaxie, ind_planet, ind_shield);
        }
        if (strcmp(command, "COL") == 0) {
            int ind_planet2;
            scanf("%d %d", &ind_planet, &ind_planet2);
            collision(galaxie, ind_planet, ind_planet2);
        }
        if (strcmp(command, "ROT") == 0) {
            scanf("%d %c %d", &ind_planet, &sens, &unit);
            rotate(galaxie, ind_planet, sens, unit);
        }
        if (strcmp(command, "SHW") == 0) {
            scanf("%d", &ind_planet);
            show(galaxie, ind_planet);
        }
    }
    shields_free(&galaxie);
    dll_free(&galaxie);

    return 0;
}
