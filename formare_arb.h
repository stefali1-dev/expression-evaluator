#include "alte_functii.h"
//-------------- functii pt formare arbore ------------//


void formareArbore(expr E)
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
            //cout << E.tokenArr[i] << " opd\n";
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
                //cout << "paranteza\n";
                pushOpr(Opr, "(");
            }

            else
            {
                //cout << E.tokenArr[i] << " opr\n";

                while ((Opr.varf != NULL) && !(strchr("()",Opr.varf -> val[0])) &&
                        prioritate(E.token[i]) < prioritate(Opr.varf -> val))
                {

                    anod *noddr, *nod;
                    nod = new anod;
                    strcpy(nod -> val, Opr.varf -> val);

                    noddr = Opd.varf -> nod;
                    nod -> dr = noddr;
                    nod -> st = NULL;

                    if(aritate(Opr.varf -> val) == 2)
                    {
                        nod -> st = Opd.varf -> urm -> nod;
                        popOpd(Opd);
                    }
                    popOpd(Opd);

                    //if(esteSeparator(val[0]) || esteFunctie(val))
                    pushOpd(Opd, nod);
                    popOpr(Opr);
                }

                //depanare
                if (Opr.varf != NULL)
                    if(Opr.varf -> val[0] != '(' || E.token[i][0] != ')')
                        pushOpr(Opr, E.token[i]);

                    else popOpr(Opr);
            }
        }
        i++;
    }
}

float valoareExpresie(arbore A, listaVar L)
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
        return valoareVar(val, L);
    }
    if(esteSeparator(val[0]))
    {
        switch(val[0])
        {
        case '+':
        {
            return Plus(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case '-':
        {
            return Minus(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case '*':
        {
            return Inmultit(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case '^':
        {
            return Putere(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case '/':
        {
            return Impartit(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case '=':
        {
            return Egal(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case '>':
        {
            if(val[1] == '=')
                return MaiMareEgal(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            return MaiMare(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case '<':
        {
            if(val[1] == '=')
                return MaiMicEgal(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            return MaiMic(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case '#':
        {
            return Diferit(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case '%':
        {
            return Rest(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case '@':
        {
            return Plus(0, valoareExpresie(A -> dr, L));
            break;
        }
        case '~':
        {
            return Minus(0, valoareExpresie(A -> dr, L));
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
            return Not(valoareExpresie(A -> dr, L));
            break;
        }
        case 2:
        {
            return And(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case 3:
        {
            return Or(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case 4:
        {
            return Nand(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case 5:
        {
            return Nor(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        case 6:
        {
            return Xor(valoareExpresie(A -> st, L), valoareExpresie(A -> dr, L));
            break;
        }
        }
    }
    else switch(esteFunctie(val))
        {
        //"sin", "cos", "tan", "cotan", "abs", "exp", "sqrt", "floor", "ceil", "round", "arcsin", "arccos", "arctan", "arccot", "sinh", "cosh", "tanh", "cotanh", "log", "log[x]", "root[x]"
        case 1:
        {
            return Sinus(valoareExpresie(A -> dr, L));
            break;
        }
        case 2:
        {
            return Cosinus(valoareExpresie(A -> dr, L));
            break;
        }
        case 3:
        {
            return Tangenta(valoareExpresie(A -> dr, L));
            break;
        }
        case 4:
        {
            return Cotangenta(valoareExpresie(A -> dr, L));
            break;
        }
        case 5:
        {
            return Modul(valoareExpresie(A -> dr, L));
            break;
        }
        case 6:
        {
            return Exponential(valoareExpresie(A -> dr, L));
            break;
        }
        case 7:
        {
            return Radical(valoareExpresie(A -> dr, L));
            break;
        }
        case 8:
        {
            return ParteIntreagaInf(valoareExpresie(A -> dr, L));
            break;
        }
        case 9:
        {
            return ParteIntreagaSup(valoareExpresie(A -> dr, L));
            break;
        }
        case 10:
        {
            return Rotunjit(valoareExpresie(A -> dr, L));
            break;
        }
        case 11:
        {
            return Arcsinus(valoareExpresie(A -> dr, L));
            break;
        }
        case 12:
        {
            return Arccosinus(valoareExpresie(A -> dr, L));
            break;
        }
        case 13:
        {
            return Arctangenta(valoareExpresie(A -> dr, L));
            break;
        }
        case 14:
        {
            return Arccotangenta(valoareExpresie(A -> dr, L));
            break;
        }
        case 15:
        {
            return SinusHiper(valoareExpresie(A -> dr, L));
            break;
        }
        case 16:
        {
            return CosinusHiper(valoareExpresie(A -> dr, L));
            break;
        }
        case 17:
        {
            return TangentaHiper(valoareExpresie(A -> dr, L));
            break;
        }
        case 18:
        {
            return CotangentaHiper(valoareExpresie(A -> dr, L));
            break;
        }
        case 19:
        {
            return Logaritm(valoareExpresie(A -> dr, L));
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
                return LogaritmBazaB(valoareExpresie(A -> dr, L), valoareVar(baza, L));
            }
            if(esteConst(baza))
            {
                b = esteConst(baza);
            }
            else b = atof(baza);
            return LogaritmBazaB(valoareExpresie(A -> dr, L), b);
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
                return RadicalOrdinN(valoareExpresie(A -> dr, L), valoareVar(baza, L));
            }
            if(esteConst(baza))
            {
                b = esteConst(baza);
            }
            else b = atof(baza);
            return RadicalOrdinN(valoareExpresie(A -> dr, L), b);
            break;
        }
        }
}

//-------------- functii pt desenare arbore -----------//

void parcurgereInPreordine(arbore A)
{
    if (A != NULL)
    {
        cout<<A->val<<", ";
        parcurgereInPreordine(A->st);
        parcurgereInPreordine(A->dr);
    }
}

int inaltimeArb, latimeArb, inaltimeCel, latimeCel;

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
    int raza = 10 + max(textwidth(sir) / 2, textheight(sir) / 2);
    fillellipse(pozCurenta.x, pozCurenta.y, raza, raza);
    setcolor(BLACK);
    if(sir[0] == '@')   outtextxy(pozCurenta.x - textwidth("+") / 2, pozCurenta.y - textheight("+") / 2, "+");
    else if(sir[0] == '~')  outtextxy(pozCurenta.x - textwidth("-") / 2, pozCurenta.y - textheight("-") / 2, "-");
    else outtextxy(pozCurenta.x - textwidth(sir) / 2, pozCurenta.y - textheight(sir) / 2, sir);
    setcolor(WHITE);
}

void deseneaza(arbore A, Punct pozAnt, int niv, int col)
{
    if(!esteArboreNul(A))
    {
        Punct pozCurenta;
        pozCurenta.x = (col + nrColoane(A -> st) + 1) * latimeCel - latimeCel / 2;
        pozCurenta.y = niv * inaltimeCel - inaltimeCel / 2;

        deseneaza(A -> st, pozCurenta, niv + 1, col);
        deseneaza(A -> dr, pozCurenta, niv + 1, col + nrColoane(A -> st) + 1);
        desenLinie(pozAnt, pozCurenta);
        desenNod(A -> val, pozCurenta);
    }
}
