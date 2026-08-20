#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "data.h" // NEMENIT, inak vas kod neprejde testom !!!

// chybove hlasenia
#define ERR_UNIT_COUNT "ERR_UNIT_COUNT"
#define ERR_ITEM_COUNT "ERR_ITEM_COUNT"
#define ERR_WRONG_ITEM "ERR_WRONG_ITEM"
#define ERR_SLOTS "ERR_SLOTS"

#define IN 1 /* внутри слова */
#define OUT 0 /* вне слова */

int maxf(int a, int b) {
    return (a > b) ? a : b;
}

int minf(int a, int b) {
    return (a < b) ? a : b;
}

int counter_slov(char *pole){
    int nw = 0, state, i = 0;
    state = OUT;
    while ((pole[i] != '\0')) {
        if (pole[i] == ' ' || pole[i] == '\n' || pole[i] == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
        i++;
    }
    return nw;
}

const ITEM* najdi_item(const char* name) {
    for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
        if (strcmp(items[i].name, name) == 0) {
            return &items[i];
        }
    }
    return NULL;
}

const UNIT* readline(char *input, char* name, UNIT *u){
    int cnt = 0;
    char item1_name[MAX_NAME], item2_name[MAX_NAME];
    fgets(input, 100, stdin);
    cnt = counter_slov(input);
    if ((cnt < 2) || (cnt > 3)){
        printf("%s\n", ERR_ITEM_COUNT); return NULL;
    }
    sscanf(input, "%s %s %s", name, item1_name, item2_name);
    u->item1 = najdi_item(item1_name);
        if (u->item1 == NULL) {
            printf("%s\n", ERR_WRONG_ITEM); return NULL;
        }
    if (cnt == 3) {
        u->item2 = najdi_item(item2_name);
        if (u->item2 == NULL) {
            printf("%s\n", ERR_WRONG_ITEM); return NULL;
        }
        if (((u->item1->slots) + (u->item2->slots)) > 2){
            printf("%s\n", ERR_SLOTS); return NULL;
        }
    } 
    else {
        u->item2 = NULL;
        // if (u->item1->slots != 2){
        //     printf(ERR_SLOTS);
        //     return NULL;
        // }
    }
    return u;
}

typedef struct {
    UNIT units[5];
    int count_of_units;
} ARMY;

typedef struct {
    int number_of_who, dmg1, dmg2; 
    char who[MAX_NAME], whom[MAX_NAME];
    const ITEM* by_what1, *by_what2;
} DAMAGE;

// void stavba(ARMY *army, UNIT pole[5]){
//     for (int j = 0; j < army->count_of_units; j++){
//         pole[j] = army->units[j];
//     }
//     return;
// }

int vytvorenie_armady(ARMY *army){
    char input[100];
    int a; // 1 - 5
    scanf("%d", &a);
    getchar();
    if ((a < 1) || (a > 5)){
        printf("%s", ERR_UNIT_COUNT); return 0; 
    }
    army->count_of_units = a;
    for (int i = 0; i < a; i++){
        UNIT u;
        if (readline(input, u.name, &u) == NULL) return 0;
        u.hp = 100;
        army->units[i] = u;
    }
    return 1;
}

void vypis_armady(ARMY *army, int num){
    printf("Army %d\n", num);
    for (int i = 0; i < army->count_of_units; i++) {
        printf("    Unit: %d\n", i);
        printf("    Name: %s\n", army->units[i].name);
        printf("    HP: %d\n", army->units[i].hp);
        printf("    Item 1: %s,%d,%d,%d,%d,%d\n", army->units[i].item1->name, army->units[i].item1->att, army->units[i].item1->def, army->units[i].item1->slots, army->units[i].item1->range, army->units[i].item1->radius);
        if (army->units[i].item2 != NULL)
            printf("    Item 2: %s,%d,%d,%d,%d,%d\n", army->units[i].item2->name, army->units[i].item2->att, army->units[i].item2->def, army->units[i].item2->slots, army->units[i].item2->range, army->units[i].item2->radius);
        // printf("\n");
        if ((i < army->count_of_units - 1) || (num == 1)) printf("\n");
    }
    // printf("\n");
    return;
}

void print_units(ARMY *army1, ARMY *army2){
    printf("%d: ", 1);
    for (int i = 0; i < army1->count_of_units; i++) {
        printf("%s,", army1->units[i].name);
        printf("%d ", army1->units[i].hp);
    }
    printf("\n%d: ", 2);
    for (int i = 0; i < army2->count_of_units; i++) {
        printf("%s,", army2->units[i].name);
        printf("%d ", army2->units[i].hp);
    }
    printf("\n");
    return;
}

void attack_army(ARMY *first, ARMY *second, int num){
    // DAMAGE damage;
    int dmg_att = 0, dmg_item1 = 0, dmg_item2 = 0, totaldef = 0, step = 0;
    char name_with[256] = {0};
    for (int i = 0; i < first->count_of_units; i++) {
        // damage.number_of_who = num;
        if (first->units[i].item2 != NULL){
                if ((first->units[i].item1->range >= i) && (first->units[i].item2->range < i)){
                    snprintf(name_with, sizeof(name_with), "%d,%s,%s:", num, first->units[i].name, first->units[i].item1->name);
                    printf("%-21s", name_with);
                    totaldef = second->units[0].item1->def;
                    if (second->units[0].item2 != NULL){
                        totaldef += second->units[0].item2->def;
                    }
                    dmg_item1 = maxf(1, first->units[i].item1->att - totaldef);
                    dmg_item2 = 0;
                    // damage.dmg1 = dmg_item1;
                    // damage.dmg2 = dmg_item2;
                    dmg_att = dmg_item1 + dmg_item2;
                    second->units[0].hp -= dmg_att;
                    printf("[%s,%d]", second->units[0].name, dmg_item1);
                    if (first->units[i].item1->radius > 0){
                        step = minf(first->units[i].item1->radius, second->count_of_units - 1);
                        for (int j = 1; j <= step; j++) { 
                            totaldef = second->units[j].item1->def;
                            if (second->units[j].item2 != NULL){
                                totaldef += second->units[j].item2->def;
                            }
                            dmg_item1 = maxf(1, first->units[i].item1->att - totaldef);
                            // damage.dmg1 = dmg_item1;
                            // damage.dmg2 = 0;
                            dmg_att = dmg_item1;
                            second->units[j].hp -= dmg_att;
                            printf(" [%s,%d]", second->units[j].name, dmg_item1);
                        }
                        printf("\n");
                    }
                    else printf("\n");
                }
                else if ((first->units[i].item1->range < i) && (first->units[i].item2->range >= i)){
                    snprintf(name_with, sizeof(name_with), "%d,%s,%s:", num, first->units[i].name, first->units[i].item2->name);
                    printf("%-21s", name_with);
                    totaldef = second->units[0].item1->def;
                    if (second->units[0].item2 != NULL){
                        totaldef += second->units[0].item2->def;
                    }
                    dmg_item1 = 0;
                    dmg_item2 = maxf(1, first->units[i].item2->att - totaldef);
                    // damage.dmg1 = dmg_item1;
                    // damage.dmg2 = dmg_item2;
                    dmg_att = dmg_item1 + dmg_item2;
                    second->units[0].hp -= dmg_att;
                    printf("[%s,%d]", second->units[0].name, dmg_item2);
                    if (first->units[i].item2->radius > 0){
                        step = minf(first->units[i].item2->radius, second->count_of_units - 1);
                        for (int j = 1; j <= step; j++) { 
                            totaldef = second->units[j].item1->def;
                            if (second->units[j].item2 != NULL){
                                totaldef += second->units[j].item2->def;
                            }
                            dmg_item2 = maxf(1, first->units[i].item2->att - totaldef);
                            // damage.dmg1 = 0;
                            // damage.dmg2 = dmg_item2;
                            dmg_att = dmg_item2;
                            second->units[j].hp -= dmg_att;
                            printf(" [%s,%d]", second->units[j].name, dmg_item2);
                        }
                        printf("\n");
                    }
                    else printf("\n");
                }
                else if ((first->units[i].item1->range < i) && (first->units[i].item2->range < i)){
                    continue;
                }
                else{
                    int by_what2[6] = {-1, -1, -1, -1, -1, -1};
                    char whom2[5][20] = { {0} };
                    snprintf(name_with, sizeof(name_with), "%d,%s,%s:", num, first->units[i].name, first->units[i].item1->name);
                    printf("%-21s", name_with);
                    totaldef = second->units[0].item1->def;
                    if (second->units[0].item2 != NULL){
                        totaldef += second->units[0].item2->def;
                    }
                    dmg_item1 = maxf(1, first->units[i].item1->att - totaldef);
                    dmg_item2 = maxf(1, first->units[i].item2->att - totaldef);
                    by_what2[0] = dmg_item2;
                    // damage.dmg1 = dmg_item1;
                    // damage.dmg2 = dmg_item2;
                    dmg_att = dmg_item1 + dmg_item2;
                    second->units[0].hp -= dmg_att;
                    printf("[%s,%d]", second->units[0].name, dmg_item1);
                    memset(name_with, 0, sizeof(name_with));
                    if ((first->units[i].item1->radius > 0) && (first->units[i].item2->radius == 0)){
                        step = minf(first->units[i].item1->radius, second->count_of_units - 1);
                        for (int j = 1; j <= step; j++) { 
                            totaldef = second->units[j].item1->def;
                            if (second->units[j].item2 != NULL){
                                totaldef += second->units[j].item2->def;
                            }
                            dmg_item1 = maxf(1, first->units[i].item1->att - totaldef);
                            // damage.dmg1 = dmg_item1;
                            // damage.dmg2 = 0;
                            dmg_att = dmg_item1;
                            second->units[j].hp -= dmg_att;
                            printf(" [%s,%d]", second->units[j].name, dmg_item1);
                        }
                        printf("\n");
                        snprintf(name_with, sizeof(name_with), "%d,%s,%s:", num, first->units[i].name, first->units[i].item2->name);
                        printf("%-21s[%s,%d]\n", name_with, second->units[0].name, dmg_item2);
                    }
                    else if ((first->units[i].item1->radius == 0) && (first->units[i].item2->radius > 0)){
                        printf("\n");
                        snprintf(name_with, sizeof(name_with), "%d,%s,%s:", num, first->units[i].name, first->units[i].item2->name);
                        printf("%-21s[%s,%d]", name_with, second->units[0].name, dmg_item2);
                        step = minf(first->units[i].item2->radius, second->count_of_units - 1);
                        for (int j = 1; j <= step; j++) { 
                            totaldef = second->units[j].item1->def;
                            if (second->units[j].item2 != NULL){
                                totaldef += second->units[j].item2->def;
                            }
                            dmg_item2 = maxf(1, first->units[i].item2->att - totaldef);
                            // damage.dmg1 = 0;
                            // damage.dmg2 = dmg_item2;
                            dmg_att = dmg_item2;
                            second->units[j].hp -= dmg_att;
                            printf(" [%s,%d]", second->units[j].name, dmg_item2);
                        }
                        printf("\n");
                    }
                    else if ((first->units[i].item1->radius == 0) && (first->units[i].item2->radius == 0)){
                        printf("\n");
                        snprintf(name_with, sizeof(name_with), "%d,%s,%s:", num, first->units[i].name, first->units[i].item2->name);
                        printf("%-21s[%s,%d]\n", name_with, second->units[0].name, dmg_item2);
                        continue;
                    }
                    else{
                        int k = 1;
                        if (first->units[i].item1->radius == maxf(first->units[i].item1->radius, first->units[i].item2->radius)){
                            step = minf(first->units[i].item1->radius, second->count_of_units - 1);
                            for (int j = 1; j <= step; j++) {
                                totaldef = second->units[j].item1->def;
                                if (second->units[j].item2 != NULL){
                                    totaldef += second->units[j].item2->def;
                                }
                                dmg_item1 = maxf(1, first->units[i].item1->att - totaldef);
                                if (j <= first->units[i].item2->radius){
                                    dmg_item2 = maxf(1, first->units[i].item2->att - totaldef);
                                    by_what2[j] = dmg_item2;
                                    strcpy(whom2[j - 1], second->units[j].name);
                                }
                                else{
                                    dmg_item2 = 0;
                                }
                                // damage.dmg1 = dmg_item1;
                                // damage.dmg2 = dmg_item2;
                                dmg_att = dmg_item1 + dmg_item2;
                                second->units[j].hp -= dmg_att;
                                printf(" [%s,%d]", second->units[j].name, dmg_item1);
                            }
                            printf("\n");
                            snprintf(name_with, sizeof(name_with), "%d,%s,%s:", num, first->units[i].name, first->units[i].item2->name);
                            printf("%-21s[%s,%d]", name_with, second->units[0].name, by_what2[0]);
                            while(by_what2[k] != -1){
                                printf(" [%s,%d]", whom2[k - 1], by_what2[k]);
                                k++;
                            }
                            printf("\n");
                        }
                        else{
                            step = minf(first->units[i].item2->radius, second->count_of_units - 1);
                            for (int j = 1; j <= step; j++) {
                                totaldef = second->units[j].item1->def;
                                if (second->units[j].item2 != NULL){
                                    totaldef += second->units[j].item2->def;
                                }
                                dmg_item2 = maxf(1, first->units[i].item2->att - totaldef);
                                by_what2[j] = dmg_item2;
                                strcpy(whom2[j - 1], second->units[j].name);
                                if (j <= first->units[i].item1->radius){
                                    dmg_item1 = maxf(1, first->units[i].item1->att - totaldef);
                                    printf(" [%s,%d]", second->units[j].name, dmg_item1);
                                }
                                else{
                                    dmg_item1 = 0;
                                }
                                // damage.dmg1 = dmg_item1;
                                // damage.dmg2 = dmg_item2;
                                dmg_att = dmg_item1 + dmg_item2;
                                second->units[j].hp -= dmg_att;
                            }
                            printf("\n");
                            snprintf(name_with, sizeof(name_with), "%d,%s,%s:", num, first->units[i].name, first->units[i].item2->name);
                            printf("%-21s[%s,%d]", name_with, second->units[0].name, by_what2[0]);
                            while(by_what2[k] != -1){
                                printf(" [%s,%d]", whom2[k - 1], by_what2[k]);
                                k++;
                            }
                            printf("\n");
                        }
                    }   
                }
        }
        else{
            if (first->units[i].item1->range >= i){
                snprintf(name_with, sizeof(name_with), "%d,%s,%s:", num, first->units[i].name, first->units[i].item1->name);
                printf("%-21s", name_with);
                totaldef = second->units[0].item1->def;
                if (second->units[0].item2 != NULL){
                    totaldef += second->units[0].item2->def;
                }
                dmg_item1 = maxf(1, first->units[i].item1->att - totaldef);
                dmg_item2 = 0;
                // damage.dmg1 = dmg_item1;
                // damage.dmg2 = dmg_item2;
                dmg_att = dmg_item1 + dmg_item2;
                second->units[0].hp -= dmg_att;
                printf("[%s,%d]", second->units[0].name, dmg_item1);
                if (first->units[i].item1->radius > 0){
                    step = minf(first->units[i].item1->radius, second->count_of_units - 1);
                    for (int j = 1; j <= step; j++) { 
                        totaldef = second->units[j].item1->def;
                        if (second->units[j].item2 != NULL){
                            totaldef += second->units[j].item2->def;
                        }
                        dmg_item1 = maxf(1, first->units[i].item1->att - totaldef);
                        // damage.dmg1 = dmg_item1;
                        // damage.dmg2 = 0;
                        dmg_att = dmg_item1;
                        second->units[j].hp -= dmg_att;
                        printf(" [%s,%d]", second->units[j].name, dmg_item1);
                    }
                    printf("\n");
                }
                else printf("\n");
            }
        }
    }
    return;
}

int update_army(ARMY *army){
    UNIT new_units[5];
    int new_count_of_units = 0;
    for (int i = 0; i < army->count_of_units; i++){
        if (army->units[i].hp > 0){
            new_units[new_count_of_units++] = army->units[i];
        }
    }
    for (int j = 0; j < new_count_of_units; j++) {
        army->units[j] = new_units[j];
    }
    army->count_of_units = new_count_of_units;
    if (army->count_of_units == 0){
        return 0;
    }
    else{
        return 1;
    }
}

int suboj(ARMY army1, ARMY army2, int n){
    // DAMAGE all_info_dmg[111];
    // int damage_index = 0;
    int q = 1, w1, w2;
    if (n != -1){
        for(int i = 0; i < n; i++){ //!is_game_over()
            printf("\nRound %d\n", q);
            print_units(&army1, &army2); // vypis armad na zaciatku kola
            attack_army(&army1, &army2, 1); // armada 1 vykona utok
            attack_army(&army2, &army1, 2); // armada 2 vykona utok
            // print_damage(all_info_dmg, damage_index); // vypis sposobenych zraneni
            w1 = update_army(&army1);
            w2 = update_army(&army2);
            if ((w1 == 0) && (w2 == 0)){
                print_units(&army1, &army2);
                printf("\nNO WINNER\n");
                return 0;
            }
            if (w2 == 0){
                print_units(&army1, &army2);
                printf("\nWINNER: 1\n");
                return 0;
            }
            if (w1 == 0){
                print_units(&army1, &army2);
                printf("\nWINNER: 2\n");
                return 0;
            }
            print_units(&army1, &army2); // vypis armad na konci kola
            // printf("\n");
            q++;
        }
        printf("\n");
    }
    else{
        while(1){ //!is_game_over()
            printf("\nRound %d\n", q);
            print_units(&army1, &army2); // vypis armad na zaciatku kola
            attack_army(&army1, &army2, 1); // armada 1 vykona utok
            attack_army(&army2, &army1, 2); // armada 2 vykona utok
            // print_damage(all_info_dmg, damage_index); // vypis sposobenych zraneni
            w1 = update_army(&army1);
            w2 = update_army(&army2);
            if ((w1 == 0) && (w2 == 0)){
                print_units(&army1, &army2);
                printf("\nNO WINNER\n");
                return 0;
            }
            if (w2 == 0){
                print_units(&army1, &army2);
                printf("\nWINNER: 1\n");
                return 0;
            }
            if (w1 == 0){
                print_units(&army1, &army2);
                printf("\nWINNER: 2\n");
                return 0;
            }
            print_units(&army1, &army2); // vypis armad na konci kola
            // printf("\n");
            q++;
        }
    }
    return 0;
}

int main(const int argc, char *argv[]) {
    int n = -1;
    if(argc == 2) {
        n = atoi(argv[1]);
     }
    ARMY army1, army2;
    if (vytvorenie_armady(&army1) == 0) return 0;
    if (vytvorenie_armady(&army2) == 0) return 0;
    vypis_armady(&army1, 1);
    
    vypis_armady(&army2, 2);
    if (n == 0){
        return 0;
    }
    // stavba(&army1, pole1);
    // stavba(&army2, pole2);
    suboj(army1, army2, n);
    return 0;
}
