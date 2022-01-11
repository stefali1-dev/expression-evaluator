#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <winbgim.h>
#include <graphics.h>

#define ENTER 13
#define BACKSPACE 8
#define ESC 27
#define SPACE 32

#include "structuri.h"
#include "functii_grafice.h"
#include "operatii.h"
#include "functii_mate.h"
#include "functii_stiva.h"
#include "formare_arb.h"



using namespace std;

void initializareFrontPage(int W, int H);

void reset()
{
    strcpy(E.sir, "");
    cleardevice();
    Fereastra.paragraf = 1;
    for(int i=0; i<100; i++)
        strcpy(E.token[i], "");
    E.lungime = 0;
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
    char c = (char)getch();
    if(c == ESC || c == ENTER || c == BACKSPACE)
    {
        reset();
        initializareFrontPage(Fereastra.W, Fereastra.H);
    }
}

void proceseazaSir()
{
    cleardevice();

    extragereCuv(E.token, E.sir);
    if(verifCorect(E))
    {
        // -- afisare rezultat -- //
        formareArbore(E);

        line(Fereastra.W*0.2, 0, Fereastra.W*0.2, Fereastra.H);

        cautaVar(E, L);
        arbore A;
        A = topOpd(Opd);

        float rezultat;
        rezultat = valoareExpresie(A, L);

        if(EsteNaN(rezultat))
        {
            char s[] = "Expresia este nedeterminata.";
            outtextxy(Fereastra.W/2 - textwidth(s)/2, Fereastra.H/32 - textheight(s)/2, s);
        }

        else
        {
            if(DifInf(rezultat))
            {
                char s[] = "Valoarea expresiei este ";
                char rez_arr[100];
                sprintf(rez_arr, "%.2f", rezultat);
                strcat(s, rez_arr);
                //cout << "Valoarea expresiei este " << rezultat << ".";
                outtextxy(Fereastra.W*0.6 - textwidth(s)/2, Fereastra.H/32 - textheight(s)/2, s);
            }
            else
            {
                char s[] = "Valoare expresiei este infinita.";
                outtextxy(Fereastra.W*0.6 - textwidth(s)/2, Fereastra.H/32 - textheight(s)/2, s);
            }
            line(Fereastra.W*0.2, Fereastra.H*0.2, Fereastra.W, Fereastra.H*0.2);

            char s[] = "Pentru a salva imaginea arborelui apasa SPACE";
            outtextxy(Fereastra.W*0.6 - textwidth(s)/2, Fereastra.H/8 - textheight(s)/2, s);

            afisareArbore(A);

        }
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
    int height = Fereastra.H/10 - textheight("a")/2;
    char c_predecesor = -1;
    while(i<485)
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
                break;
            }
            else
                continue;
        }

        if((int)c == BACKSPACE)
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

        if((int)c == ESC)
        {
            reset();
            initializareFrontPage(Fereastra.W, Fereastra.H);
            break;
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
}

void initializareFrontPage(int W, int H)
{
    char s[] = "Tasteaza functia. Apasa ENTER pentru finalizare, ESC pentru a reseta fereastra, BACKSPACE pentru a da cu un caracter inapoi";
    outtextxy(W/2 - textwidth(s)/2, H/16 - textheight(s)/2, s);

    CasetaText.left = W*3/16;
    CasetaText.top = H/10 - textheight(s)/1.5;
    CasetaText.right = W*13/16;
    CasetaText.bottom = H/5 + textheight(s)/1.5;
    rectangle(CasetaText.left, CasetaText.top, CasetaText.right, CasetaText.bottom);

    citesteSir();
}

void mainLoop(int W, int H)
{
    reset();
    initializareFrontPage(W, H);
    char c = (char)getch();
    if(c == SPACE)
    {
        writeimagefile("ArboreExpr.bmp", Fereastra.W*0.2, Fereastra.H*0.2, Fereastra.W, Fereastra.H);
    }
    mainLoop(W, H);
}

int main()
{
    Fereastra.W = 1300;
    Fereastra.H = 950;
    initwindow(Fereastra.W, Fereastra.H);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
    mainLoop(Fereastra.W, Fereastra.H);
    // extragere

    return 0;
}
