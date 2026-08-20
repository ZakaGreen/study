#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <locale.h>


static int iCislo, iVysledok, ia;         // Niektore verzie potrebuju globalne premenne
char pole[12] = { 0 };

void uloha1() {
    iCislo = 27;
    ia = 11;
    iVysledok = 0;
    printf("\n%d + %d  =  ?", iCislo, ia);


    __asm {                          
        MOV EAX, iCislo                  
        ADD EAX, ia                           
        MOV iVysledok, EAX                
    }

    printf("\n%d + %d  =  %d", iCislo, ia, iVysledok);

    return;
}

void uloha2() {
    iCislo = 4;
    iVysledok = 0;
    printf("\n%d * %d  = ?", iCislo, 2);


    __asm {
        MOV EAX, iCislo
        SHL EAX, 1
        MOV iVysledok, EAX
    }

    printf("\n%d * %d  = %d", iCislo, 2, iVysledok);

    return;
}

void uloha3() {
    iCislo = 11;
    __asm {
        MOV EAX, iCislo;
        CMP EAX, 10;
        JGE tam;
        ADD EAX, '0';
        JMP end;
        tam: ADD EAX, 55;
        end:;
        MOV iVysledok, EAX;
    }

    printf("%c", iVysledok);

    return;
}

void uloha4() {
    __asm {
        MOV EAX, 0;
        CPUID;
        MOV DWORD PTR[pole], EBX;
        MOV DWORD PTR[pole + 4], EDX;
        MOV DWORD PTR[pole + 8], ECX;
    }

    printf("%s\n", pole);

    return;
}

void uloha22() {
    char pole[] = "architektura_pocitacov_je_super_predmet";
    int pole1[5] = {1, 2, 3, 4, 5};
    puts(pole);
    for (int i = 0; i < 5; i++) {
        printf("%d ", pole1[i]);
    }
    printf("\n");
    char* pointer = &pole;
    int* pointer1 = &pole1;
    printf("%p\n", pointer);
    printf("%p\n", pointer1);
    pointer++;
    *pointer = 'I';
    pointer1++;
    *pointer1 = 11;
    puts(pole);
    for (int i = 0; i < 5; i++) {
        printf("%d ", pole1[i]);
    }
    printf("\n");
//    pointer = pointer + 1111;
//    *pointer = 'K';
    //puts(pole);
}

void uloha24() {
    char c, b;

    mciSendString("open \"D:\\C\\test\\STU\\Project1\\Debug\\cdaudio.mp3\" alias Debug", NULL, sizeof(TCHAR), NULL);
    mciSendString("play Debug", NULL, sizeof(TCHAR), NULL);
    while (1) {
        if ((c = getchar()) == '\n') mciSendString("pause Debug", NULL, sizeof(TCHAR), NULL);
        else { mciSendString("close Debug", NULL, sizeof(TCHAR), NULL); return; }
        if ((c = getchar()) == '\n') mciSendString("play Debug", NULL, sizeof(TCHAR), NULL);
        else { mciSendString("close Debug", NULL, sizeof(TCHAR), NULL); return; }
    }

    /*mciSendString("open \"D:\\C\\test\\STU\\Project1\\Debug\\mys.mpg\" alias Debug", NULL, sizeof(TCHAR), NULL);
    mciSendString("play Debug fullscreen", NULL, sizeof(TCHAR), NULL);

    b = getchar();
    mciSendString("close Debug", NULL, sizeof(TCHAR), NULL);*/
    //error = mciSendString(“prikaz”, szReturn, sizeof(szRetrun) / sizeof(TCHAR), hwnd);
    //2 szReturn - Pointer to a buffer that receives return information.If no return information is needed, this parameter can be NULL.
    //3 sizeof(szRetrun) / sizeof(TCHAR) - Size, in characters, of the return buffer specified by the szReturn parameter.
}

void uloha231() {
    FILE* vchod, * vychod;
    char ch;
    vchod = fopen("1.html", "r"); //read
    vychod = fopen("2.html", "w"); //write
    while ((ch = fgetc(vchod)) != EOF) {
        if (ch == (char)165) ch = (char)188;
        else if (ch == (char)169) ch = (char)138; 
        else if (ch == (char)171) ch = (char)141;
        else if (ch == (char)174) ch = (char)142;
        else if (ch == (char)181) ch = (char)190;
        else if (ch == (char)185) ch = (char)154;
        else if (ch == (char)187) ch = (char)157;
        else if (ch == (char)190) ch = (char)158;
        fputc(ch, vychod);
    }
    fclose(vchod);
    fclose(vychod);
    return;
}

int main3(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    //uloha1();
    //uloha2();
    //uloha3();
    //uloha4();
    //uloha22();
    uloha24();
    //uloha231();

    return(0);
}
