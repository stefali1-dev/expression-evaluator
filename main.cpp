#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <winbgim.h>
#include <graphics.h>

#include "structuri.h"
#include "operatii.h"
#include "functii_mate.h"
#include "functii_stiva.h"
#include "formare_arb.h"

using namespace std;

int main()
{
    char exp[N];
    cin.getline(exp, N-1);
    extragereCuv(E.token, exp);
    //-------- Test extragereCuv -------//

    /*
    for(int i=0; i < E.lungime-1; i++)
    {
        cout << endl << E.token[i];
    }
    cout << endl;
    */

    //---------------------------------//

    if(verifCorect(E))
    {
        // -- afisare rezultat -- //
        formareArbore(E);
        cautaVar(E, L);
        arbore A;
        A = topOpd(Opd);
        float rezultat;
        rezultat = valoareExpresie(A, L);
        cout << "Valoarea expresiei este " << rezultat << ".";

        // -- afisare arb -- //

        inaltimeArb = nrNiveluri(A);
        latimeArb = nrColoane(A);
        inaltimeCel = H / inaltimeArb;
        latimeCel = W / latimeArb;

        initwindow(W, H);
        setlinestyle(0, 0, 3);
        setbkcolor(WHITE);

        deseneaza(A, {-1, -1}, 1, 0);
        getch();
        closegraph();
    }

    return 0;
}
