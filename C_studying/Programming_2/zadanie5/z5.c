#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// NEMENIT, inak vas kod neprejde testom !!!
#include "data.h" 

#define IN 1 /* внутри слова */
#define OUT 0 /* вне слова */

void cat(FILE *ifp, FILE *ofp){
	int c;
	while ((c = getc(ifp)) != EOF)
	putc(c, ofp);
}

int counter_of_items(char *pole){
	int cnt = 0, k = 0;
	while (pole[k] != '\0') {
		if (pole[k] == '}') cnt++;
		k++;
	}
	
	return cnt;
}

// int hladanie_num(char prikaz[], int num){
// }

char* file_to_buffer(FILE* f, int *rozmer){
	fseek(f, 0, SEEK_END);
    *rozmer = ftell(f);
    rewind(f);
    char* buffer = malloc(*rozmer + 1);
	fread(buffer, 1, *rozmer, f);
    buffer[*rozmer] = '\0';
	return buffer;
}

typedef struct {
	int count_of_items;
    ITEM* items; // items[sizeof(ITEM) * inv.count_of_items]
} INVENTORY;

typedef struct {
	int count_of_units;
    UNIT units[5];
} ARMY;

int counter_slov_for_army(char *pole){
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

void print_items(INVENTORY *inv, int num){
    for (int i = 0; i < inv->count_of_items; i++) {
        fprintf(stdout,"Name: %s\n", inv->items[i].name);
        fprintf(stdout,"Attack: %d\n", inv->items[i].att);
        fprintf(stdout,"Defense: %d\n", inv->items[i].def);
		fprintf(stdout,"Slots: %d\n", inv->items[i].slots);
		fprintf(stdout,"Range: %d\n", inv->items[i].range);
		fprintf(stdout,"Radius: %d\n", inv->items[i].radius);
		fprintf(stdout, "\n");
		// if (i < inv->count_of_items - 1) fprintf(stdout, "\n");
    }
    return;
}

int counter_slov(char *pole, INVENTORY* inv){
    int cnt = 0, state, i = 0;
    state = OUT;
    while ((pole[i] != ']')) {
        if (pole[i] == ' ' || pole[i] == '\n' || pole[i] == '\t' || pole[i] == '"' || pole[i] == ':' || pole[i] == ',' || pole[i] == '[' || pole[i] == '{' || pole[i] == '}')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++cnt;
        }
        i++;
    }
	if ((cnt - (12 * (inv->count_of_items - 1))) < 12){
		if ((cnt % 2) == 0){
			fprintf (stderr, "%s\n", ERR_MISSING_ATTRIBUTE); //ERR_MISSING_VALUE
			exit(0);
		}
		else{
			fprintf (stderr, "%s\n", ERR_MISSING_VALUE); //ERR_MISSING_ATTRIBUTE
			exit(0);
		}
	}
    return cnt;
}

const ITEM* najdi_item(const char* name, INVENTORY* inv) {
    for (int i = 0; i < inv->count_of_items; i++) {
        if (strcmp(inv->items[i].name, name) == 0) { //strcmp(inv->items[i].name, name)
            return &inv->items[i]; //(strstr(inv->items[i].name, name) != NULL)
        }
    }
    return NULL;
}

int parse_of_buffer(char *pole, INVENTORY* inv){
    int nw = 0, state, i = 4, number_of_item = 0;
	char name_of_item[MAX_NAME] = {'\0'};
	char num[16] = {0};
    state = OUT;
    while (pole[i] != ']') {
        if (pole[i] == ' ' || pole[i] == '\n' || pole[i] == '\t' || pole[i] == '"' || pole[i] == ':' || pole[i] == ',' || pole[i] == '[' || pole[i] == '{' || pole[i] == '}'){
            state = OUT;
			//fprintf(stdout, "%c", pole[i]);
		}
        else if (state == OUT) {
            state = IN;
            ++nw;
			//fprintf(stdout, "%c", pole[i]);
			if ((nw - (12 * number_of_item))== 2){
				int p = i, l = 0;
				while((pole[p] != '\0') && (isalnum(pole[p]))){
					name_of_item[l] = pole[p];
					p++; l++;
				}
				strcpy(inv->items[number_of_item].name, name_of_item); 
				memset(name_of_item, 0, sizeof(name_of_item));
			}
			else if((nw - (12 * number_of_item)) == 4){
				int p = i, q = 0;
				while (pole[p] != '\0' && pole[p] != ',' && pole[p] != '\n' && pole[p] != '}' && pole[p] != ' ' && pole[p] != '\\'){
					if (!isdigit(pole[p])){
						fprintf (stderr, "%s\n", ERR_BAD_VALUE);
						exit(0);
					}
					num[q] = pole[p];
					p++; q++;
				}
				inv->items[number_of_item].att = atoi(num);
				memset(num, 0, sizeof(num));
			}
			else if((nw - (12 * number_of_item))== 6){
				int p = i, q = 0;
				while (pole[p] != '\0' && pole[p] != ',' && pole[p] != '\n' && pole[p] != '}' && pole[p] != ' ' && pole[p] != '\\'){
					if (!isdigit(pole[p])){
						fprintf (stderr, "%s\n", ERR_BAD_VALUE);
						exit(0);
					}
					num[q] = pole[p];
					p++; q++;
				}
				inv->items[number_of_item].def = atoi(num);
				memset(num, 0, sizeof(num));
			}
			else if((nw - (12 * number_of_item))== 8){
				int p = i, q = 0;
				while (pole[p] != '\0' && pole[p] != ',' && pole[p] != '\n' && pole[p] != '}' && pole[p] != ' ' && pole[p] != '\\'){
					if (!isdigit(pole[p])){
						fprintf (stderr, "%s\n", ERR_BAD_VALUE);
						exit(0);
					}
					num[q] = pole[p];
					p++; q++;
				}
				inv->items[number_of_item].slots = atoi(num);
				memset(num, 0, sizeof(num));
			}
			else if((nw - (12 * number_of_item))== 10){
				int p = i, q = 0;
				while (pole[p] != '\0' && pole[p] != ',' && pole[p] != '\n' && pole[p] != '}' && pole[p] != ' ' && pole[p] != '\\'){
					if (!isdigit(pole[p])){
						fprintf (stderr, "%s", ERR_BAD_VALUE);
						exit(0);
					}
					num[q] = pole[p];
					p++; q++;
				}
				inv->items[number_of_item].range = atoi(num);
				memset(num, 0, sizeof(num));
			}
			else if((nw - (12 * number_of_item))== 12){
				int p = i, q = 0;
				while (pole[p] != '\0' && pole[p] != ',' && pole[p] != '\n' && pole[p] != '}' && pole[p] != ' ' && pole[p] != '\\'){
					if (!isdigit(pole[p])){
						fprintf (stderr, "%s\n", ERR_BAD_VALUE);
						exit(0);
					}
					num[q] = pole[p];
					p++; q++;
				}
				inv->items[number_of_item].radius = atoi(num);
				memset(num, 0, sizeof(num));
				number_of_item++;
			}
			else continue;
			// printf("\n%c", pole[i]);
        }
        i++;
    }
    return nw;
}

const UNIT* readline(char *input, char* name, UNIT *u, INVENTORY* inv){
    int cnt = 0;
    char item1_name[MAX_NAME], item2_name[MAX_NAME];
    cnt = counter_slov_for_army(input);
    if ((cnt < 2) || (cnt > 3)){
		fprintf(stderr, "%s\n", ERR_ITEM_COUNT); exit(0);
    }
    sscanf(input, "%s %s %s", name, item1_name, item2_name);
    u->item1 = najdi_item(item1_name, inv);
        if (u->item1 == NULL) {
			// fprintf(stdout, "%s %s %d\n", name, item1_name, 1);
			fprintf(stderr, "%s\n", ERR_WRONG_ITEM); exit(0);
        }
    if (cnt == 3) {
        u->item2 = najdi_item(item2_name, inv);
        if (u->item2 == NULL) {
			fprintf(stderr, "%s\n", ERR_WRONG_ITEM); exit(0);
        }
        if (((u->item1->slots) + (u->item2->slots)) > 2){
			fprintf(stderr, "%s\n", ERR_SLOTS); exit(0);
        }
    } 
    else {
        u->item2 = NULL;
    }
    return u;
}

int vytvorenie_armady(ARMY *army, char *pole, INVENTORY* inv){
	char input[100];
	int j = 1, x = 0, t = 0;
	while(!isdigit(pole[t])){
		pole++;
	}
    int a = atoi(pole); // 1 - 5
    if ((a < 1) || (a > 5)){
		fprintf(stderr, "%s\n", ERR_UNIT_COUNT); exit(0); 
    }
    army->count_of_units = a;
    for (int i = 0; i < a; i++){
		j++; x = 0;
        UNIT u;
		while(pole[j] != '\n'){
			input[x++] = pole[j++];
		}
		input[x++] = '\0';
        readline(input, u.name, &u, inv);
        u.hp = 100;
        army->units[i] = u;
		memset(input, 0, sizeof(input));
    }
    return 1;
}

void vypis_armady(ARMY *army, int num){
    fprintf(stdout, "Army %d\n", num);
    for (int i = 0; i < army->count_of_units; i++) {
        fprintf(stdout, "    Unit: %d\n", i);
        fprintf(stdout, "    Name: %s\n", army->units[i].name);
        fprintf(stdout, "    HP: %d\n", army->units[i].hp);
        fprintf(stdout, "    Item 1: %s,%d,%d,%d,%d,%d\n", army->units[i].item1->name, army->units[i].item1->att, army->units[i].item1->def, army->units[i].item1->slots, army->units[i].item1->range, army->units[i].item1->radius);
        if (army->units[i].item2 != NULL)
            fprintf(stdout, "    Item 2: %s,%d,%d,%d,%d,%d\n", army->units[i].item2->name, army->units[i].item2->att, army->units[i].item2->def, army->units[i].item2->slots, army->units[i].item2->range, army->units[i].item2->radius);
        // printf("\n");
        if ((i < army->count_of_units - 1) || (num == 1))  fprintf(stdout, "\n");
    }
    //printf("\n");
    return;
}

int main(const int argc, char *argv[]) {
	INVENTORY inv;
	int rozmer, rozmera1, rozmera2;
	FILE* f;
	f = fopen(ITEMS_FILE, "r");

	if (!f){
		fprintf(stderr, "%s\n", ERR_FILE);
		exit(0);
	}

	char* pole = file_to_buffer(f, &rozmer);
	inv.count_of_items = counter_of_items(pole);
	inv.items = malloc(sizeof(ITEM) * inv.count_of_items);
	rewind(f);
	counter_slov(pole, &inv);
	parse_of_buffer(pole, &inv);

    if(argc == 3) {
		FILE* fa1;
		FILE* fa2;
		ARMY army1, army2;
		fa1 = fopen(argv[1], "r");
		fa2 = fopen(argv[2], "r");
		if ((!fa1) || (!fa2)){
			fprintf(stderr, "%s\n", ERR_FILE);
			exit(0);
		}
		char* polea1 = file_to_buffer(fa1, &rozmera1);
		char* polea2 = file_to_buffer(fa2, &rozmera2);
		vytvorenie_armady(&army1, polea1, &inv);
		vytvorenie_armady(&army2, polea2, &inv);
		vypis_armady(&army1, 1);
		vypis_armady(&army2, 2);
		fprintf(stdout, "\n");
		fclose(f);
		fclose(fa1);
		fclose(fa2);
    }
	else if(argc == 1){ 
		// cat(f, stdout);
		// counter_slov(pole, &inv);
		// parse_of_buffer(pole, &inv);
		print_items(&inv, inv.count_of_items);
		// fprintf(stdout, "\n%d", parse_of_buffer(pole));
		// fprintf(stdout, "\n%s", pole);
		fclose(f);
	}
	else{
		fprintf (stderr, "%s\n", ERR_CMD);
		exit(0);
	}
	return 0;
}

// main(int argc, char *argv[]){
// 	FILE *fp;
// 	void filecopy(FILE *, FILE *);
// 	if (argc == 1) /* нет аргументов; копируется стандартный ввод */
// 		filecopy(stdin, stdout);
// 	else{
// 		while (--argc > 0){
// 			if ((fp = fopen(*++argv, "r")) == NULL) {
// 				printf("cat: не могу открыть файл %s\n", *argv);
// 				return 1;
// 			} 
// 			else {
// 				filecopy(fp, stdout);
// 				fclose(fp);
// 			}
// 		}
// 	return 0;
// }

// main(int argc, char *argv[]){
// 	FILE *fp;
// 	void filecopy(FILE *, FILE *);
// 	char *prog = argv[0]; /* имя программы */
// 	if (argc ==1) /* нет аргументов; копируется станд. ввод */
// 		filecopy(stdin, stdout);
// 	else
// 		while (--argc > 0){
// 			if ((fp = fopen(*++argv, "r")) == NULL) {
// 				fprintf (stderr, "%s: не могу открыть файл %s\n", prog, *argv);
// 				exit(t);
// 			} 
// 			else {
// 				filecopy(fp, stdout);
// 				fclose(fp);
// 			}
// 		}
// 	if (ferror(stdout)) {
// 		fprintf (stderr, "%s: ошибка записи в stdout\n", prog);
// 		exit(0);
// 	}
// 	exit(0);
// }
