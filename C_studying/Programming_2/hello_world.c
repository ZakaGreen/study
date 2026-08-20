#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <conio.h>
#include <ctype.h>

int is_cons(char c){
     if (!isalpha(c))
          return 0;
     c = tolower(c);
     switch(c){
          case 'a':
          case 'e':
          case 'i':
          case 'o':
          case 'u':
          case 'y':
          return 0;
          default: return 1;
     }

     
}

int is_imposter(const char* name){
     int is_a_not_end = 0, is_a_wrong = 0;
     for (int i = 0; name[i] != '\0'; i++){
          if (name[i] == 'a'){
          is_a_not_end = name[i + 1] != '\0';
          is_a_wrong = !(name[i+1] == 'i' || is_cons(name[i+1]));
          }
     }
     int pravy = is_a_not_end && !is_a_wrong;
     return !pravy;
}

int main(){
     char name[10];
     while(1){
          scanf("%9s", name);
          printf("%s: %s\n", is_imposter(name) ? "Impostor" : "Dwarf", name);
          is_imposter("main");
     }
     _getch();  
     return(0);
 } 