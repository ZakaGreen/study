#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define IN 1 /* внутри слова */
#define OUT 0 /* вне слова */
#define N 100 /*  */
#define MMAX 1000 /*  */
#define prsize 15

int hladanie_num(char prikaz[], int num){
  char w[5] = {0};
  for (int i = 5; prikaz[i] != '\0'; i++){
    if (prikaz[i] == '-'){
      w[0] = prikaz[i];
    }
    else if ((isdigit(prikaz[i])) && (isdigit(prikaz[i + 2])) && (isdigit(prikaz[i + 1]))){
      return -1000;
    }
    else if ((isdigit(prikaz[i])) && (w[0] != '-') && (isdigit(prikaz[i + 1]))) {
    w[0] = prikaz[i];
    w[1] = prikaz[i + 1];
    num = atoi(w);
    return num;
    }
    else if((isdigit(prikaz[i])) && (w[0] == '-') && (isdigit(prikaz[i + 1]))){
    w[1] = prikaz[i];
    w[2] = prikaz[i + 1];
    num = atoi(w);
    return num;
    }
    else if ((isdigit(prikaz[i])) && w[0] != '-') {
      w[0] = prikaz[i];
      num = atoi(w);
      return num;
    }
    else if((isdigit(prikaz[i])) && w[0] == '-'){
      w[1] = prikaz[i];
      num = atoi(w);
      return num;
    }
  }
}

int conv(char prikaz[]){
  if (strcmp(prikaz, "out op\n") == 0) return 1;
  else if (strcmp(prikaz, "out range\n") == 0) return 2;
  else if (strcmp(prikaz, "out mem\n") == 0) return 3;
  else if ((prikaz[0] == 'm') && (prikaz[5] == 's')) return 4;
  else if ((prikaz[0] == 'm') && (prikaz[5] == 'e')) return 5;
  else if ((prikaz[0] == 's') && (prikaz[6] == 's')) return 6;
  else if ((prikaz[0] == 's') && (prikaz[6] == 'e')) return 7;
  else if ((prikaz[0] == 'e') && (prikaz[4] == 's')) return 8;
  else if ((prikaz[0] == 'e') && (prikaz[4] == 'e')) return 9;
  else if (strcmp(prikaz, "first\n") == 0) return 10;
  else if (strcmp(prikaz, "last\n") == 0) return 11;
  else if (strcmp(prikaz, "prev\n") == 0) return 12;
  else if (strcmp(prikaz, "next\n") == 0) return 13;
  else if ((strcmp(prikaz, "del\n") == 0) || (strcmp(prikaz, "del") == 0)) return 14;
  else if ((strcmp(prikaz, "crop\n") == 0) || (strcmp(prikaz, "crop") == 0)) return 15;
  else if ((strcmp(prikaz, "copy\n") == 0) || (strcmp(prikaz, "copy") == 0)) return 16;
  else if (strcmp(prikaz, "insert mem\n") == 0) return 17;
  else if ((prikaz[0] == 'i')) return 18;
  else if ((strcmp(prikaz, "replace\n") == 0) || (strcmp(prikaz, "replace") == 0)) return 19;
}

const char *readline(char prikaz[]) {
    // staticke pole zostava platne aj po skonceni funkcie
    static char buffer[MMAX + 1] = {'\0'};
    // nacitanie riadku
    fgets(buffer, sizeof(buffer), stdin);
    for (int i = 0; buffer[i] != ' '; i++){
      prikaz[i] = buffer[i];
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    memmove(buffer, buffer + strlen(prikaz) + 1, MMAX - 2);
    if (strlen(buffer) > N){
      printf("ERR_OVERFLOW"); return prikaz;
    }
    return buffer;
}

int main(void) {
  char prikaz[prsize] = {'\0'};
  char op[N + 1] = {'\0'}, mem[N + 1] = {'\0'};
  char *sp = op, *ep = op;
  int num, state = OUT;
  strcpy(op, readline(prikaz));
  sp = op; 
  ep = op + strlen(op);
  memset(prikaz, 0, sizeof(prikaz));
  fgets(prikaz, prsize, stdin);

  while(strcmp(prikaz, "quit\n") != 0){
    switch(conv(prikaz)){
      case 1: 
      printf("%s\n", op); break;

      case 2:
      if (sp > ep){
        printf("ERR_POSITION");
        return 0;
      }
      else{
        int i = 0;
        while(sp != ep){
          printf("%c", *sp);
          sp++;
          i++;
        }
        sp = sp - i;
        printf("\n");
      }
      break;

      // int i = 0;
      // while((sp + i) != (ep)){
      //   printf("%c", *(sp + i));
      //   i++;
      // }
      // printf("\n");
      // break;

      case 3:
      printf("%s\n", mem); break;

      case 4:
      if((num = hladanie_num(prikaz, num)) == -1000){
        printf("ERR_OUT_OF_RANGE"); return 0;
      }
      else if(num >= 0){
        for(int j = 1; j <= num; j++){
          if ((*(sp + 1) == '\0') && (j < num)){
            printf("ERR_OUT_OF_RANGE"); return 0;
          }
          else sp++;
        }
      }
      else{
        for(int z = -1; z >= num; z--){
          if ((sp == op) && (z > num)){
            printf("ERR_OUT_OF_RANGE"); return 0;
          }
          else sp--;
        }
      }
      break;

      case 5:
      if((num = hladanie_num(prikaz, num)) == -1000){
        printf("ERR_OUT_OF_RANGE"); return 0;
      }
      else if(num >= 0){
        for(int j = 0; j < num; j++){
          if (*ep == '\0'){
            printf("ERR_OUT_OF_RANGE"); return 0;
          }
          ep++;
        }
      }
      else{
        for(int z = 0; z > num; z--){
          if ((ep - 1) == op){
            printf("ERR_OUT_OF_RANGE"); return 0;
          }
          ep--;
        }
      }
      break;

      case 6:
      sp = op; break;

      case 7:
      ep = op; break;

      case 8:
      sp = op + strlen(op); break;

      case 9:
      ep = op + strlen(op); break;

      case 10:
      int b = 0;
      while ((op[b] != '\0') && (!isalnum(op[b]))) {
        b++; 
      }

      if (op[b] == '\0') {
        sp = op;
        ep = op;
        break;
      }

      sp = &op[b]; 
      while ((op[b] != '\0') && (isalnum(op[b]))) {
      b++;
      }
      ep = &op[b];
      
      break;

      case 11:
      sp = op + strlen(op);
      while ((sp != op) && (!isalnum(*sp))) {
        sp--; 
      }
      if (sp == op) {
        sp = op + strlen(op);
        ep = op + strlen(op);
        break;
      }
      while ((sp != op) && (isalnum(*sp))){
        sp--;
      }
      if(sp != op){
        sp++;
      }
      ep = sp;
      while((isalnum(*ep)) && (*ep != '\0')){
        ep++;
      }
      break;
      
      // int q = strlen(op) - 1;
      // while ((op[q] != op[0]) && (!isalnum(op[q]))) {
      //   q--; 
      // }
      // if (op[q] == op[0]) {
      //   sp = op + strlen(op);
      //   ep = op + strlen(op);
      //   break;
      // }
      // ep = &op[q + 1];
      // while ((op[q] != op[0]) && (isalnum(op[q]))) {
      //   q--;
      // }
      // sp = &op[q + 1];
      // break;

      case 12:
      if (sp != op){
        while((isalnum(*sp)) && (sp != op)){
          sp--;
        }
        while((!isalnum(*sp)) && (sp != op)){
          sp--;
        }
        while((isalnum(*sp)) && (sp != op)){
          sp--;
        }
        if (sp != op){
          sp++;
        }
      }
      else {
        ep = sp;
        break;
      }
      ep = sp;
      while((isalnum(*ep)) && (*ep != '\0')){
        ep++;
      }
      break;
      // if (ep != sp){
      //   while((!isalnum(*ep)) && (ep != sp)){
      //     ep--;
      //   }
      //   while((isalnum(*ep)) && (ep != sp)){
      //     ep--;
      //   }
      //   while((!isalnum(*ep)) && (ep != sp)){
      //     ep--;
      //   }
      //   if (ep != sp){
      //     ep++;
      //   }
      // }
      // else break;
      
      case 13:
      if (*sp != '\0'){
        while((isalnum(*sp)) && (*sp != '\0')){
          sp++;
        }
        while((!isalnum(*sp)) && (*sp != '\0')){
          sp++;
        }
      }
      else break;
      ep = sp;
      while((isalnum(*ep)) && (*ep != '\0')){
        ep++;
      }
      break;
      // if (ep != sp){
      //   while((isalnum(*ep)) && (*ep != '\0')){
      //     ep++;
      //   }
      //   while((!isalnum(*ep)) && (*ep != '\0')){
      //     ep++;
      //   }
      //   while((isalnum(*ep)) && (*ep != '\0')){
      //     ep++;
      //   }
      // }
      // else break;
      // break;

      case 14:
      if (sp > ep){
        printf("ERR_POSITION");
        return 0;
      }
      else{
        memmove(sp, ep, strlen(ep) + 1);
        ep = sp;
      }
      break;

      case 15:
      if (sp > ep){
        printf("ERR_POSITION"); return 0;
      }
      else{
        memmove(op, sp, ep - sp);
        op[ep - sp] = '\0';
        sp = op;
        ep = op + strlen(op);
      }
      break;

      case 16:
      int e = 0;
      if (sp == ep){
        break;
      }
      else if (sp > ep){
        printf("ERR_POSITION"); return 0;
      }
      else{
        memset(mem, 0, sizeof(mem));
        while (sp != ep){
          mem[e] = *sp;
          e++;
          sp++;
        }
        sp = sp - strlen(mem);
      }
      break;

      case 17:
      if (sp > ep){
        printf("ERR_POSITION"); return 0;
      }
      else if ((strlen(op) + strlen(mem)) > (N + 1)){
        printf("ERR_OVERFLOW"); return 0;
      }
      else{
        memmove(sp + strlen(mem), sp, strlen(sp) + 1);
        memcpy(sp, mem, strlen(mem)); 
        ep = ep + strlen(mem);    
      }
      break;

      case 18:
      char ins[N + 1] = {'\0'};
      num = hladanie_num(prikaz, num);
      for (int m = 0; m < num; m++){
        ins[m] = ' ';
      }
      if (sp > ep){
        printf("ERR_POSITION"); return 0;
      }
      else if ((strlen(op) + num) > N){
        printf("ERR_OVERFLOW"); return 0;
      }
      else{
        memmove(sp + num, sp, strlen(sp) + 1);
        memcpy( sp, ins, num); 
        ep = ep + num;    
      }
      break;

      case 19:
      int cnt = 0;
      if (sp > ep){
        printf("ERR_POSITION"); return 0;
      }
      else{
        for(int p = 0; p < strlen(mem); p++){
          if (sp == ep) break;
          *sp = mem[p];
          sp++;
          cnt++;
        }
        sp = sp - cnt;
      }
      break;

      default:
      return 0;
    }
    // printf("(%c)\n", *sp);
    // printf("(%c)\n", *ep);
    //printf("%d\n", strlen(op));
    memset(prikaz, 0, sizeof(prikaz));
    fgets(prikaz, prsize, stdin);
  } 
  return 0;
}