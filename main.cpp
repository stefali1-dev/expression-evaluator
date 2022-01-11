#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <winbgim.h>
#include <graphics.h>

#define ENTER 13
#define BACKSPACE 8

#include "structuri.h"
#include "functii_grafice.h"
#include "operatii.h"
#include "functii_mate.h"
#include "functii_stiva.h"
#include "formare_arb.h"



using namespace std;

void afisareArbore(arbore A)
{

    Celula.inaltime = Fereastra.H / nrNiveluri(A);
    Celula.latime = Fereastra.W / nrColoane(A);

    setlinestyle(0, 0, 3);
    setbkcolor(WHITE);
    deseneaza(A, {-1, -1}, 1, 0);
}

void proceseazaSir()
{
    cleardevice();
    extragereCuv(E.token, E.sir);
    if(verifCorect(E))
    {
        // -- afisare rezultat -- //
        formareArbore(E);
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
                sprintf(rez_arr, "%f", rezultat);
                strcat(s, rez_arr);
                //cout << "Valoarea expresiei este " << rezultat << ".";
                outtextxy(Fereastra.W/2 - textwidth(s)/2, Fereastra.H/32 - textheight(s)/2, s);
            }
            else
            {
                char s[] = "Valoare expresiei este infinita.";
                outtextxy(Fereastra.W/2 - textwidth(s)/2, Fereastra.H/32 - textheight(s)/2, s);
            }
        }

        // -- afisare arb -- //
        afisareArbore(A);
    }

}

void backSpace(int x, int y, int len)
{
    setfillstyle(EMPTY_FILL,0);
    bar(x - len, y, x, y + textheight("a"));
}

void citesteSir()
{
    int len = 0, leftSpace = 10;
    int i = 0;
    int height = Fereastra.H/10 - textheight("a")/2;
    char c_predecesor = 'a';
    while(i<485)
    {
        char c = -1;
        char c_arr[2];
        c = (char)getch();

        if((int)c == ENTER)
        {
            E.sir[len] = '\0';
            proceseazaSir();
            break;
        }

        if((int)c == BACKSPACE)
        {
            c_arr[0] = c_predecesor;
            c_arr[1] = '\0';
            backSpace(CasetaText.left + leftSpace, height, textwidth(c_arr));
            \
            leftSpace -= textwidth(c_arr);
            len--;
            continue;
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

    char s[] = "Tasteaza functia. Apasa ENTER pentru finalizare, F5 pentru a reseta fereastra";
    outtextxy(W/2 - textwidth(s)/2, H/16 - textheight(s)/2, s);

    CasetaText.left = W/16;
    CasetaText.top = H/10 - textheight(s)/1.5;
    CasetaText.right = W*15/16;
    CasetaText.bottom = H/5 + textheight(s)/1.5;
    rectangle(CasetaText.left, CasetaText.top, CasetaText.right, CasetaText.bottom);

    citesteSir();
}

void initializareFereastra(int W, int H)
{
    initwindow(W, H);
    initializareFrontPage(W, H);
    setbkcolor(WHITE);

    getch();
}

int main()
{
    Fereastra.W = 900;
    Fereastra.H = 700;
    initializareFereastra(Fereastra.W, Fereastra.H);
    // extragere
    /*
    for(int i=0; i<E.lungime-1; i++)
    {
        cout<<E.token[i]<<endl;
    }
    cout<<endl;
    */
    return 0;
}
