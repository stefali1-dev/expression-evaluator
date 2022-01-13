#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <winbgim.h>
#include <graphics.h>

#define ENTER 13
#define BACKSPACE 8
#define TAB 9
#define SPACE 32
#define ESC 27

#include "structuri.h"
#include "functii_grafice.h"
#include "operatii.h"
#include "functii_mate.h"
#include "functii_stiva.h"
#include "formare_arb.h"



using namespace std;

void initializareFrontPage();

void reset()
{
    strcpy(E.sir, "");
    cleardevice();
    Fereastra.paragraf = 1;
    for(int i=0; i<100; i++)
        strcpy(E.token[i], "");
    E.lungime = 0;
    for(int i=0; i<100; i++)
    {
        strcpy(L.var[i].nume, "");
    }
    L.nrElemente = 0;
    initOpd(Opd);
    initOpr(Opr);
}

void afisareArbore(arbore A)
{
    Celula.inaltime = (Fereastra.H - Fereastra.H*0.2) / nrNiveluri(A);
    Celula.latime = (Fereastra.W - Fereastra.W*0.2) / nrColoane(A);
    line(Fereastra.W*0.2, 0, Fereastra.W*0.2, Fereastra.H);
    setlinestyle(0, 0, 3);
    setbkcolor(WHITE);
    setfillstyle(EMPTY_FILL,WHITE);
    deseneaza(A, {-1, -1}, 1, 0);

    setbkcolor(BLACK);
    setfillstyle(EMPTY_FILL,BLACK);
}

void proceseazaSir()
{
    cleardevice();

    extragereCuv(E.token);
    if(verifCorect())
    {
        formareArbore();

        cautaVar();
        arbore A;
        A = topOpd(Opd);

        float rezultat;
        rezultat = valoareExpresie(A);

        line(Fereastra.W*0.2, Fereastra.H*0.2, Fereastra.W, Fereastra.H*0.2);

        char s[] = "Pentru a salva imaginea arborelui apasa SPACE";
        outtextxy(Fereastra.W*0.6 - textwidth(s)/2, Fereastra.H/8 - textheight(s)/2, s);


        if(EsteNaN(rezultat))
        {
            strcpy(s, "Expresia este nedeterminata.");
        }

        else
        {
            if(DifInf(rezultat))
            {
                strcpy(s, "Valoarea expresiei este ");
                char rez_arr[100];
                sprintf(rez_arr, "%.2f", rezultat);
                strcat(s, rez_arr);
            }
            else
            {
                strcpy(s, "Valoare expresiei este infinita.");

            }

        }
        outtextxy(Fereastra.W*0.6 - textwidth(s)/2, Fereastra.H/32 - textheight(s)/2, s);
        afisareArbore(A);
    }

}

void backSpace(int x, int y, int len)
{
    setfillstyle(EMPTY_FILL,BLACK);
    bar(x - len, y, x, y + textheight("a"));
}

void citesteSir()
{
    int len = 0, leftSpace = 10;
    int i = 0;
    int height = Fereastra.H*4/16 - textheight("a")/2;
    char c_predecesor = -1;
    while(i<320)
    {
        char c = -1;
        char c_arr[2];
        c = (char)getch();
        if((int)c == ENTER)
        {
            if(c_predecesor != -1)
            {
                E.sir[len] = '\0';
                proceseazaSir();
                return;
            }
            else
                continue;
        }

        if(c == BACKSPACE)
        {
            if(leftSpace > textwidth(c_arr))
            {
                c_arr[0] = c_predecesor;
                c_arr[1] = '\0';
                backSpace(CasetaText.left + leftSpace, height, textwidth(c_arr));
                leftSpace -= textwidth(c_arr);
                if(len > 0)
                    len--;
            }
            continue;
        }

        if(c == TAB)
        {
            reset();
            initializareFrontPage();
            break;
        }

        else if(c == ESC){
            exit(0);
        }

        E.sir[len] = c;
        len++;
        i++;

        c_arr[0] = c;
        c_arr[1] = '\0';
        if(CasetaText.left + leftSpace + textwidth(c_arr) > CasetaText.right)
        {
            leftSpace = 10;
            height += textheight("a");
        }

        outtextxy(CasetaText.left + leftSpace, height, c_arr);
        leftSpace += textwidth(c_arr);
        c_predecesor = c;
    }
    E.sir[len] = '\0';
    proceseazaSir();
}

void initializareFrontPage()
{
    char s[] = "Tasteaza functia. Apasa ENTER pentru finalizare, TAB pentru a reseta fereastra, BACKSPACE pentru a da cu un caracter inapoi,";
    outtextxy(Fereastra.W/2 - textwidth(s)/2, Fereastra.H/16 - textheight(s)/2, s);
    strcpy(s, "ESC pentru a termina programul");
    outtextxy(Fereastra.W/2 - textwidth(s)/2, Fereastra.H*2/16 - textheight(s)/2, s);

    CasetaText.left = Fereastra.W*3/16;
    CasetaText.top = Fereastra.H*4/16 - textheight(s)/1.5;
    CasetaText.right = Fereastra.W*13/16;
    CasetaText.bottom = Fereastra.H*5/16 + textheight(s)/1.5;
    rectangle(CasetaText.left, CasetaText.top, CasetaText.right, CasetaText.bottom);

    citesteSir();
}

void mainLoop()
{
    reset();
    initializareFrontPage();
    char c = (char)getch();
    if(c == SPACE)
    {
        writeimagefile("ArboreExpr.bmp", Fereastra.W*0.2, Fereastra.H*0.2, Fereastra.W, Fereastra.H);
    }
    else if(c == ESC)
        exit(0);
    mainLoop();
}

int main()
{
    Fereastra.W = 1300;
    Fereastra.H = 950;
    initwindow(Fereastra.W, Fereastra.H);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
    mainLoop();
    return 0;
}
