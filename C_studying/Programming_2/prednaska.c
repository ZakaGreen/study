#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

int print_rand_nums(FILE* file, int n){
    for (int i = 0; i < n; i++){
        fprintf(file, "%d\n", rand()); //f для работы с файлами
    }
    return n;
}

#define DEFAULT_NUM 100


// void uloha() {

//     return;
// }


int main(int argc, char* argv[]){

    FILE* f;
    
    f = fopen("data.txt", "w");

    if (f == NULL) return -1;

    print_rand_nums(f, DEFAULT_NUM);

    fclose(f);

    return(0);
}