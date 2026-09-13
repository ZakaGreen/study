//Prosím, daj dobrú známku.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "data.h" // NEMENIŤ: potrebné pre prechádzanie testami

// Chybové hlásenia
#define ERR_UNIT_COUNT "ERR_UNIT_COUNT"  // nesprávny počet jednotiek
#define ERR_ITEM_COUNT "ERR_ITEM_COUNT"  // nesprávny počet predmetov na jednotku
#define ERR_WRONG_ITEM "ERR_WRONG_ITEM"  // neznámy predmet
#define ERR_SLOTS "ERR_SLOTS"            // prekročený počet slotov

#define MMAX 1000

#define MAX_NAME 100      // maximálna dĺžka mena jednotky
#define MAX_UNITS 5       // maximálny počet jednotiek v armáde
#define NUMBER_OF_ITEMS 16// počet dostupných predmetov
#define MAX_INPUT 1000    // maximálna dĺžka vstupu pri čítaní riadka

// Štruktúra predstavuje armádu: pole jednotiek a ich aktuálny počet
typedef struct army {
    UNIT units[MAX_UNITS]; // pole jednotiek
    int count;             // počet jednotiek v armáde
} ARMY;

// Globálne premenné pre obe armády a číslovanie kôl
ARMY army1 = {0}; // prvá armáda
ARMY army2 = {0}; // druhá armáda
int round_number = 0; // číslo aktuálneho kola

// Funkcia kontroluje, či už hra skončila (jedna armáda vyčerpala jednotky)
bool is_game_over() {
    return army1.count == 0 || army2.count == 0;
}

// Čítanie riadka zo štandardného vstupu
const char *readline() {
    static char buffer[MMAX + 1] = {0};
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // odstránenie '\n'
    return buffer;
}

// Výpis životov (HP) jednotiek oboch armád v tvare "1: meno,hp ..."
void print_units() {
    printf("1: ");
    for (int i = 0; i < army1.count; i++) {
        printf("%s,%d", army1.units[i].name, army1.units[i].hp);
        if (i < army1.count - 1) printf(" "); // medzera medzi jednotkami
    }
    printf("\n");

    printf("2: ");
    for (int i = 0; i < army2.count; i++) {
        printf("%s,%d", army2.units[i].name, army2.units[i].hp);
        if (i < army2.count - 1) printf(" ");
    }
    printf("\n");
}

// Zistenie čísla armády, ktorej jednotka patrí
int get_army_number(UNIT* unit) {
    for (int i = 0; i < army1.count; i++) {
        if (&army1.units[i] == unit) {
            return 1;
        }
    }
    return 2;
}

// Funkcia vykoná útok konkrétnej jednotky s daným predmetom
void attack_with_item(UNIT* attacker, int attacker_pos, ARMY* attacking_army, ARMY* defending_army, const ITEM* item) {
    // kontrola dosahu útoku bez pohybu (range == 0 len pre prvú jednotku)
    if (item->range == 0 && attacker_pos != 0) {
        return;
    }
    // ak je pozícia jednotky za dosahom, neútočí
    if (attacker_pos > item->range) {
        return;
    }

    int army_number = get_army_number(attacker);
    // vypísanie prefixu útoku (číslo armády, meno útočníka, predmet)
    printf("%d,%s,%s:%-*s",
       army_number,
       attacker->name,
       item->name,
       (21 - (int)(strlen(attacker->name) + strlen(item->name) + 4)), // formátovanie
       "");

    // hlavný cieľ: prvá jednotka v obrannom poli
    if (defending_army->count > 0) {
        UNIT* main_target = &defending_army->units[0];
        int defense = (main_target->item1 ? main_target->item1->def : 0) +
                     (main_target->item2 ? main_target->item2->def : 0);
        int damage = item->att - defense;
        damage = damage < 1 ? 1 : damage; // minimálne 1

        printf("[%s,%d]", main_target->name, damage);
        main_target->hp -= damage; // odčítanie zdravia
    }

    // splash efekt: ak má predmet polomer rádiusa (radius)
    if (item->range > 0) {
        for (int i = 1; i <= item->radius && i < defending_army->count; i++) {
            UNIT* defender = &defending_army->units[i];
            int defense = (defender->item1 ? defender->item1->def : 0) +
                         (defender->item2 ? defender->item2->def : 0);
            int splash_damage = item->att - defense;
            splash_damage = splash_damage < 1 ? 1 : splash_damage;

            printf(" [%s,%d]", defender->name, splash_damage);
            defender->hp -= splash_damage;
        }
    }
    printf("\n");
}

// Každá jednotka v armáde vykoná útok podľa svojich predmetov
void attack_army(ARMY* attacking_army, ARMY* defending_army) {
    for (int i = 0; i < attacking_army->count; i++) {
        UNIT* attacker = &attacking_army->units[i];
        int attacker_pos = i;

        if (attacker->item1) {
            attack_with_item(attacker, attacker_pos, attacking_army, defending_army, attacker->item1);
        }
        if (attacker->item2) {
            attack_with_item(attacker, attacker_pos, attacking_army, defending_army, attacker->item2);
        }
    }
}

// Odstránenie mŕtvych jednotiek (hp <= 0) z armády
void update_army(ARMY* army) {
    int new_count = 0;
    for (int i = 0; i < army->count; i++) {
        if (army->units[i].hp > 0) {
            army->units[new_count++] = army->units[i];
        }
    }
    army->count = new_count;
}

// Vyhľadanie predmetu podľa mena v globálnom poli items
const ITEM* find_item_by_name(const char* item_name) {
    if (item_name == NULL) return NULL;

    for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
        if (strcmp(items[i].name, item_name) == 0) {
            return &items[i];
        }
    }
    return NULL;
}

// Vytvorenie jednotky zo vstupného reťazca (meno + voliteľné predmety)
UNIT create_unit_from_string(const char* input) {
    UNIT new_unit = {0};
    new_unit.hp = 100; // štartovacie zdravie každej jednotky

    char input_copy[MAX_INPUT];
    strncpy(input_copy, input, MAX_INPUT - 1);
    input_copy[MAX_INPUT - 1] = '\0';

    char* token = strtok(input_copy, " ");
    int token_count = 0;
    char* tokens[3] = {NULL, NULL, NULL};

    // rozdelenie na jednotlivé slová (meno, predmety)
    while (token != NULL && token_count < 3) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }

    // ak je viac než 3 tokeny, chyba
    if (token != NULL) {
        printf(ERR_ITEM_COUNT);
        exit(EXIT_SUCCESS);
    }

    strncpy(new_unit.name, tokens[0], MAX_NAME);
    new_unit.name[MAX_NAME] = '\0';

    // priradenie prvého predmetu (ak existuje)
    if (token_count > 1) {
        new_unit.item1 = find_item_by_name(tokens[1]);
        if (new_unit.item1 == NULL) {
            printf(ERR_WRONG_ITEM);
            exit(EXIT_SUCCESS);
        }
    }

    // priradenie druhého predmetu (ak existuje)
    if (token_count > 2) {
        new_unit.item2 = find_item_by_name(tokens[2]);
        if (new_unit.item2 == NULL) {
            printf(ERR_WRONG_ITEM);
            exit(EXIT_SUCCESS);
        }
    }

    return new_unit;
}

// Načítanie konfigurácie oboch armád zo vstupu
int initialize_armies() {
    const char *line;

    // prvá armáda: množstvo a jednotky
    scanf("%d", &army1.count);
    getchar();
    if (!(army1.count >= MIN_ARMY && army1.count <= MAX_ARMY)) {
        printf(ERR_UNIT_COUNT);
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < army1.count; i++) {
        line = readline();
        army1.units[i] = create_unit_from_string(line);
        int slots_sum = 0;
        slots_sum += army1.units[i].item1->slots;
        if (army1.units[i].item2) { slots_sum += army1.units[i].item2->slots; }
        if (slots_sum > 2) {
            printf(ERR_SLOTS);
            exit(EXIT_SUCCESS);
        }
    }

    // druhá armáda: množstvo a jednotky
    scanf("%d", &army2.count);
    getchar();
    if (!(army2.count >= MIN_ARMY && army2.count <= MAX_ARMY)) {
        printf(ERR_UNIT_COUNT);
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < army2.count; i++) {
        line = readline();
        army2.units[i] = create_unit_from_string(line);
        int slots_sum = 0;
        slots_sum += army2.units[i].item1->slots;
        if (army2.units[i].item2) { slots_sum += army2.units[i].item2->slots; }
        if (slots_sum > 2) {
            printf(ERR_SLOTS);
            exit(EXIT_SUCCESS);
        }
    }
}

// Výpis detailov armád pred začiatkom bitky
void print_armies() {
    printf("Army 1\n");
    for (int i = 0; i < army1.count; i++) {
        printf("    Unit: %d\n" , i);
        printf("    Name: %s\n", army1.units[i].name);
        printf("    HP: %d\n" , army1.units[i].hp);
        printf("    Item 1: %s,%d,%d,%d,%d,%d\n",
            army1.units[i].item1->name, army1.units[i].item1->att, army1.units[i].item1->def,
            army1.units[i].item1->slots, army1.units[i].item1->range, army1.units[i].item1->radius);
        if (army1.units[i].item2) {
            printf("    Item 2: %s,%d,%d,%d,%d,%d\n",
                army1.units[i].item2->name, army1.units[i].item2->att, army1.units[i].item2->def,
                army1.units[i].item2->slots, army1.units[i].item2->range, army1.units[i].item2->radius);
        }
        printf("\n");
    }
    printf("Army 2\n");
    for (int i = 0; i < army2.count; i++) {
        printf("    Unit: %d\n", i);
        printf("    Name: %s\n", army2.units[i].name);
        printf("    HP: %d\n", army2.units[i].hp);
        printf("    Item 1: %s,%d,%d,%d,%d,%d\n",
            army2.units[i].item1->name, army2.units[i].item1->att, army2.units[i].item1->def,
            army2.units[i].item1->slots, army2.units[i].item1->range, army2.units[i].item1->radius);
        if (army2.units[i].item2) {
            printf("    Item 2: %s,%d,%d,%d,%d,%d\n",
                army2.units[i].item2->name, army2.units[i].item2->att, army2.units[i].item2->def,
                army2.units[i].item2->slots, army2.units[i].item2->range, army2.units[i].item2->radius);
        }
        printf("\n");
    }
}

int main(const int argc, const char * argv[]) {
    // inicializácia armád
    initialize_armies();

    // výpis armád pred prvým kolom
    print_armies();
    int max_round_count;
    if (argc > 1) {
        max_round_count = atoi(argv[1]); // limit kôl z argumentu
        if (max_round_count == 0) {
            return 0;
        }
    }

    // hlavná slučka bitky
    while (!is_game_over()) {
        round_number++;
        printf("Round %d
", round_number);

        print_units();
        attack_army(&army1, &army2); // armáda1 útočí
        attack_army(&army2, &army1); // armáda2 útočí

        update_army(&army1); // odstránenie padlých z armády1
        update_army(&army2); // odstránenie padlých z armády2

        print_units();
        printf("\n");
        if (round_number == max_round_count) {
            return 0; // dosiahnutý limit kôl
        }
    }

    // výsledok bitky: zistenie víťaza alebo remíza
    if (army1.count > 0 && army2.count == 0) {
        printf("WINNER: 1\n");
    } else if (army2.count > 0 && army1.count == 0) {
        printf("WINNER: 2\n");
    } else {
        printf("NO WINNER\n");
    }

    return 0;
}
//Prosím, daj dobrú známku.
