#include "alte_functii.h"


//-------------- functii pt formare arbore ------------//


void formareArbore()
{
    initOpr(Opr);
    initOpd(Opd);
    int i = 0;
    pushOpr(Opr, "(");

    while (i < E.lungime && Opr.varf != NULL)
    {
        // este operand
        if (esteNumar(E.token[i]) || esteVar(E.token[i])|| esteConst(E.token[i]))
        {
            anod *nod_nou;
            nod_nou = new anod;
            strcpy(nod_nou -> val, E.token[i]);
            nod_nou->st = nod_nou->dr = NULL;
            pushOpd(Opd, nod_nou);
        }

        // este operator
        else
        {
            if(E.token[i][0] == '(')
            {
                pushOpr(Opr, "(");
            }

            else
            {

                while ((Opr.varf != NULL) && !(strchr("()",Opr.varf -> val[0])) &&
                        prioritate(Opr.varf -> val) >= prioritate(E.token[i]))
                {
                    if(prioritate(E.token[i]) == 3)
                        break;
                    anod *noddr, *nod;
                    nod = new anod;
                    strcpy(nod -> val, Opr.varf -> val);

                    // nod dreapta
                    noddr = Opd.varf -> nod;
                    nod -> dr = noddr;

                    nod -> st = NULL;

                    if(aritate(Opr.varf -> val) == 2)
                    {
                        // nod stanga
                        nod -> st = Opd.varf -> urm -> nod;
                        popOpd(Opd);
                    }
                    popOpd(Opd);

                    pushOpd(Opd, nod);
                    popOpr(Opr);
                }

                //depanare
                if (Opr.varf != NULL)
                    if(Opr.varf -> val[0] != '(' || E.token[i][0] != ')')
                        pushOpr(Opr, E.token[i]);

                    else popOpr(Opr); // stergem '('
            }
        }
        i++;
    }
}

float valoareExpresie(arbore A)
{
    char val[20];
    strcpy(val, A -> val);
    if(esteNumar(val))
    {
        return atof(val);
    }
    if(esteConst(val))
    {
        return esteConst(val);
    }
    if(esteVar(val))
    {
        return valoareVar(val);
    }
    if(esteSeparator(val[0]))
    {
        switch(val[0])
        {
        case '+':
        {
            return Plus(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case '-':
        {
            return Minus(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case '*':
        {
            return Inmultit(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case '^':
        {
            return Putere(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case '/':
        {
            return Impartit(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case '=':
        {
            return Egal(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case '>':
        {
            if(val[1] == '=')
                return MaiMareEgal(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            return MaiMare(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case '<':
        {
            if(val[1] == '=')
                return MaiMicEgal(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            return MaiMic(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case '#':
        {
            return Diferit(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case '%':
        {
            return Rest(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case '@':
        {
            return Plus(0, valoareExpresie(A -> dr));
            break;
        }
        case '~':
        {
            return Minus(0, valoareExpresie(A -> dr));
            break;
        }
        }
    }
    else if(esteOperatorLogic(val).id)
    {
        switch(esteOperatorLogic(val).id)
        {
        case 1:
        {
            return Not(valoareExpresie(A -> dr));
            break;
        }
        case 2:
        {
            return And(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case 3:
        {
            return Or(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case 4:
        {
            return Nand(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case 5:
        {
            return Nor(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        case 6:
        {
            return Xor(valoareExpresie(A -> st), valoareExpresie(A -> dr));
            break;
        }
        }
    }
    else switch(esteFunctie(val))
        {
        //"sin", "cos", "tan", "cotan", "abs", "exp", "sqrt", "floor", "ceil", "round", "arcsin", "arccos", "arctan", "arccot", "sinh", "cosh", "tanh", "cotanh", "log", "log[x]", "root[x]"
        case 1:
        {
            return Sinus(valoareExpresie(A -> dr));
            break;
        }
        case 2:
        {
            return Cosinus(valoareExpresie(A -> dr));
            break;
        }
        case 3:
        {
            return Tangenta(valoareExpresie(A -> dr));
            break;
        }
        case 4:
        {
            return Cotangenta(valoareExpresie(A -> dr));
            break;
        }
        case 5:
        {
            return Modul(valoareExpresie(A -> dr));
            break;
        }
        case 6:
        {
            return Exponential(valoareExpresie(A -> dr));
            break;
        }
        case 7:
        {
            return Radical(valoareExpresie(A -> dr));
            break;
        }
        case 8:
        {
            return ParteIntreagaInf(valoareExpresie(A -> dr));
            break;
        }
        case 9:
        {
            return ParteIntreagaSup(valoareExpresie(A -> dr));
            break;
        }
        case 10:
        {
            return Rotunjit(valoareExpresie(A -> dr));
            break;
        }
        case 11:
        {
            return Arcsinus(valoareExpresie(A -> dr));
            break;
        }
        case 12:
        {
            return Arccosinus(valoareExpresie(A -> dr));
            break;
        }
        case 13:
        {
            return Arctangenta(valoareExpresie(A -> dr));
            break;
        }
        case 14:
        {
            return Arccotangenta(valoareExpresie(A -> dr));
            break;
        }
        case 15:
        {
            return SinusHiper(valoareExpresie(A -> dr));
            break;
        }
        case 16:
        {
            return CosinusHiper(valoareExpresie(A -> dr));
            break;
        }
        case 17:
        {
            return TangentaHiper(valoareExpresie(A -> dr));
            break;
        }
        case 18:
        {
            return CotangentaHiper(valoareExpresie(A -> dr));
            break;
        }
        case 19:
        {
            return Logaritm(valoareExpresie(A -> dr));
            break;
        }
        case 20:
        {
            char baza[100];
            int i, j;
            float b;
            i = 4;
            j = 0;
            while(val[i] != ']')
            {
                //log[x]
                baza[j++] = val[i++];
            }
            baza[j] = '\0';
            if(esteVar(baza))
            {
                return LogaritmBazaB(valoareExpresie(A -> dr), valoareVar(baza));
            }
            if(esteConst(baza))
            {
                b = esteConst(baza);
            }
            else b = atof(baza);
            return LogaritmBazaB(valoareExpresie(A -> dr), b);
            break;
        }
        case 21:
        {
            char baza[100];
            int i, j;
            float b;
            i = 5;
            j = 0;
            while(val[i] != ']')
            {
                //root[x]
                baza[j++] = val[i++];
            }
            baza[j] = '\0';
            if(esteVar(baza))
            {
                return RadicalOrdinN(valoareExpresie(A -> dr), valoareVar(baza));
            }
            if(esteConst(baza))
            {
                b = esteConst(baza);
            }
            else b = atof(baza);
            return RadicalOrdinN(valoareExpresie(A -> dr), b);
            break;
        }
        }
}

//-------------- functii pt desenare arbore -----------//

struct Punct
{
    int x, y;
};

bool esteArboreNul(arbore A)
{
    return (A == NULL);
}

void initializareArb(arbore &A)
{
    if (!esteArboreNul(A))
        A = NULL;
}

int nrNiveluri(arbore A)
{
    if(esteArboreNul(A))
        return 0;
    else
    {
        int n1 = nrNiveluri(A -> st);
        int n2 = nrNiveluri(A -> dr);
        return 1 + max(n1, n2);
    }
}

int nrColoane(arbore A)
{
    if(esteArboreNul(A))
        return 0;
    else
    {
        int n1 = nrColoane(A -> st);
        int n2 = nrColoane(A -> dr);
        return 1 + n1 + n2;
    }
}

void desenLinie(Punct pozAnt, Punct pozCurenta)
{
    if(pozAnt.x != -1 && pozAnt.y != -1)
        line(pozAnt.x, pozAnt.y, pozCurenta.x, pozCurenta.y);
}

void desenNod(char sir[], Punct pozCurenta)
{
    char sir_nou[100];
    inlocuireUnar(sir, sir_nou);
    int raza = 10 + max(textwidth(sir_nou) / 2, textheight(sir_nou) / 2);
    fillellipse(pozCurenta.x, pozCurenta.y, raza, raza);
    setcolor(BLACK);
    outtextxy(pozCurenta.x - textwidth(sir_nou) / 2, pozCurenta.y - textheight(sir_nou) / 2, sir_nou);
    setcolor(WHITE);
}

void deseneaza(arbore A, Punct pozAnt, int niv, int col)
{
    if(!esteArboreNul(A))
    {
        Punct pozCurenta;
        pozCurenta.x = (col + nrColoane(A -> st) + 1) * Celula.latime - Celula.latime / 2 + Fereastra.W*0.2;
        pozCurenta.y = niv * Celula.inaltime - Celula.inaltime / 2 + Fereastra.H*0.2;

        deseneaza(A -> st, pozCurenta, niv + 1, col);
        deseneaza(A -> dr, pozCurenta, niv + 1, col + nrColoane(A -> st) + 1);
        desenLinie(pozAnt, pozCurenta);
        desenNod(A -> val, pozCurenta);
    }
}
