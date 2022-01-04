#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <winbgim.h>
#include <graphics.h>
#define N 10000
#define infinit INT_MAX
#define epsi 0.00001
using namespace std;


// ------------ functii matematice -----------//

const float p = 3.1415926536;
const float e = 2.7182818284;
const float phi = 1.6180339887;

bool DifInf(float x)
{
    return fabs(infinit-fabs(x)) > infinit / 2.0;
}

float Logaritm(float x)
{
    if (x>epsi && DifInf(x))
        return log(x);
    else
        return infinit;
}

float Exponential(float x)
{
    if (DifInf(x)) return exp(x);
    else return infinit;
}

float Inmultit(float x, float y)
{
    if (fabs(x) < epsi || fabs(y) < epsi) return 0;
    else if (DifInf(x) && DifInf(y)) return x*y;
    else return infinit;
}

float Putere(float x, float y)
{
    // float p;
    if (x == 0) return 0;
    else if (y == 0) return 1;
    else if (x == infinit || y == infinit) return infinit;
    else if (pow(x,y) > epsi) return pow(x,y);
    else return 0;
}

float Egal(float x, float y)
{
    return x == y;
}

float Diferit(float x, float y)
{
    return x != y;
}

bool MaiMic(float x, float y)
{
    return x < y;
}

bool MaiMicEgal(float x, float y)
{
    return x <= y;
}

bool MaiMare(float x, float y)
{
    return x > y;
}

bool MaiMareEgal(float x, float y)
{
    return x >= y;
}

float Plus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return x+y;
    else return infinit;
}

float Minus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return x-y;
    else return infinit;
}

float Impartit(float x, float y)
{
    if (fabs(y) > epsi) return x/y;
    else return infinit;
}

float Rest(float x, float y)
{
    if (DifInf(x) && fabs(y) > epsi) return fmod(x, y);
    else return infinit;
}

bool Not(float x)
{
    return !x;
}

bool And(float x, float y)
{
    return x && y;
}

bool Or(float x, float y)
{
    return x || y;
}

bool Nand(float x, float y)
{
    return !(x && y);
}

bool Nor(float x, float y)
{
    return !(x || y);
}

bool Xor(float x, float y)
{
    return ((x && !y) || (!x && y));
}

float Sinus(float x)
{
    if (DifInf(x))
    {
        if(fabs(sin(x)) > epsi) return sin(x);
        else return 0;
    }
    else return infinit;
}

float Cosinus(float x)
{
    if (DifInf(x))
    {
        if(fabs(cos(x)) > epsi) return cos(x);
        else return 0;
    }
    else return infinit;
}

float Tangenta(float x)
{
    if (DifInf(x))
    {
        if(fabs(tan(x)) > epsi) return tan(x);
        else return 0;
    }
    else return infinit;
}

float Cotangenta(float x)
{
    if (DifInf(x))
    {
        if(fabs(1/tan(x)) > epsi) return 1/tan(x);
        else return 0;
    }
    else return infinit;
}

float Modul(float x)
{
    if (DifInf(x))
    {
        if(fabs(x) > epsi) return fabs(x);
        else return 0;
    }
    else return infinit;
}

float Radical(float x)
{
    if (DifInf(x))
    {
        if(x < 0) return NAN;
        else if(sqrt(x) > epsi) return sqrt(x);
        else return 0;
    }
    else return infinit;
}

float ParteIntreagaInf(float x)
{
    if (DifInf(x)) return floor(x);
    else return infinit;
}

float ParteIntreagaSup(float x)
{
    if (DifInf(x)) return ceil(x);
    else return infinit;
}

float Rotunjit(float x)
{
    if (DifInf(x))
    {
        if(x - floor(x) < ceil(x) - x)
            return floor(x);
        else return ceil(x);
    }
    else return infinit;
}

float Arcsinus(float x)
{
    if (DifInf(x))
    {
        if(fabs(asin(x)) > epsi) return asin(x);
        else return 0;
    }
    else return infinit;
}

float Arccosinus(float x)
{
    if (DifInf(x))
    {
        if(fabs(acos(x)) > epsi) return acos(x);
        else return 0;
    }
    else return infinit;
}

float Arctangenta(float x)
{
    if (DifInf(x))
    {
        if(fabs(atan(x)) > epsi) return atan(x);
        else return 0;
    }
    else return p/2;
}

float Arccotangenta(float x)
{
    if (DifInf(x))
    {
        if(fabs(atan(1/x)) > epsi) return atan(1/x);
        else return 0;
    }
    else return 0;
}

float SinusHiper(float x)
{
    if (DifInf(x))
    {
        if(fabs(sinh(x)) > epsi) return sinh(x);
        else return 0;
    }
    else return infinit;
}

float CosinusHiper(float x)
{
    if (DifInf(x))
    {
        if(fabs(cosh(x)) > epsi) return sinh(x);
        else return 0;
    }
    else return infinit;
}

float TangentaHiper(float x)
{
    if (DifInf(x))
    {
        if(fabs(tanh(x)) > epsi) return tanh(x);
        return 0;
    }
    else return infinit;
}

float CotangentaHiper(float x)
{
    if (DifInf(x))
    {
        if(1/fabs(tanh(x)) > epsi) return 1/tanh(x);
        else return 0;
    }
    else return infinit;
}

// ------------ structuri ----------//

struct anod
{
    char val[100];
    anod *st;
    anod *dr;
};
typedef anod *arbore;

struct nodOpr
{
    char val[100];
    nodOpr * urm;
};

struct nodOpd
{
    anod * nod;
    nodOpd * urm;
};

struct stivaOpr
{
    nodOpr* varf;
    int nrElemente;
} Opr, tempOpr;

struct stivaOpd
{
    nodOpd* varf;
    int nrElemente = 0;
} Opd, tempOpd;

struct expr
{
    char token[N][100];
    int lungime = 0;
} E;

struct variabila
{
    char nume[100];
    float valoare;
};

struct listaVar
{
    variabila var[100];
    int nrElemente;
} L;
//lista liniara cu variabile

//-------------- functii stiva --------------//

void initOpr(stivaOpr &s)
{
    s.varf = NULL;
    s.nrElemente = 0;
}

char* topOpr(stivaOpr s)
{
    char *val;
    strcpy(val, s.varf -> val);
    return val;
}

void popOpr(stivaOpr &s)
{
    nodOpr* varf_nou = s.varf -> urm;
    delete s.varf;
    s.varf = varf_nou;
    s.nrElemente--;
}

void pushOpr(stivaOpr &s, char val[])
{

    if(s.nrElemente == 0)
    {

        s.nrElemente = 1;
        s.varf = new nodOpr;
        //s.varf -> val = elem;
        strcpy(s.varf->val, val);
        s.varf -> urm = NULL;
    }

    else
    {
        nodOpr* nod_nou;
        nod_nou = new nodOpr;

        s.nrElemente++;

        //nod_nou -> val = elem;
        strcpy(nod_nou -> val, val);
        nod_nou -> urm = s.varf;
        s.varf = nod_nou;
    }

}

void initOpd(stivaOpd &s)
{
    s.varf = NULL;
    s.nrElemente = 0;
}

anod* topOpd(stivaOpd s)
{
    anod *nod;
    nod = s.varf -> nod;
    return nod;
}

void popOpd(stivaOpd &s)
{
    nodOpd* varf_nou = s.varf -> urm;
    s.varf = varf_nou;
    s.nrElemente--;
}

void pushOpd(stivaOpd &s, anod* nod)
{
    if(s.nrElemente == 0)
    {
        s.nrElemente = 1;
        s.varf = new nodOpd;
        s.nrElemente++;

        s.varf -> nod = nod;
        s.varf -> urm = NULL;
    }

    else
    {
        nodOpd* nod_nou;
        nod_nou = new nodOpd;
        s.nrElemente++;

        nod_nou -> nod = nod;
        nod_nou -> urm = s.varf;
        s.varf = nod_nou;
    }
}

//-----------functii de verificare -----------//

void printOpr(stivaOpr Opr)
{
    while(Opr.varf)
    {
        cout << Opr.varf -> val << endl;
        Opr.varf = Opr.varf -> urm;
    }
    cout << endl;
}

void printOpd(stivaOpd Opd)
{
    nodOpd *nod_nou;
    nod_nou = Opd.varf;
    while(nod_nou)
    {
        cout << nod_nou -> nod -> val << endl;
        nod_nou = nod_nou ->urm;
    }
}

//--------------- alte functii ------------//

bool esteSeparator(char c)
{
    char separatori[20] = "()+-*/^=<>#";
    if(strchr(separatori, c))
        return true;
    return false;
}

int esteFunctie(char s[])
{
    char functii[30][20] = {"sin", "cos", "tan", "cot", "abs", "exp", "sqrt", "floor", "ceil", "round", "arcsin", "arccos", "arctan", "arccot", "sinh", "cosh", "tanh", "coth"};
    //mai trebuie adaugate
    for(int i=0; i<17; i++)
        if(strcmp(functii[i],s) == 0)
            return i+1;
    if(strstr(s, "log["))
        return 19;
    if(strstr(s, "root["))
        return 20;
    return 0;
}

bool esteNumar(char s[])
{
    if(strchr("0123456789",s[0]) && s[0] != '\0')
        return true;
    if(s[0] == '-' && strchr("0123456789", s[1]) && s[1] != '\0')
        return true;
    return false;
}

float esteConst(char s[])
{
    if(strcmp(s, "p") == 0)
        return p;
    if(strcmp(s, "e") == 0)
        return e;
    if(strcmp(s, "phi") == 0)
        return phi;
    return 0;
}

bool esteVar(char s[])
{
    if(!(esteFunctie(s)) && !(esteNumar(s)) && !(esteSeparator(s[0])) && !(esteConst(s)))
        return true;
    return false;
}

int aritate(char s[])
{
    if(esteFunctie(s))
        return 1;
    return 2;
}

void eliminareSpatii(char exp[])
{
    int len = strlen(exp);
    for(int j=0; j <= len; j++)
        if(exp[j] == ' ')
        {
            strcpy(exp+j, exp+j+1);
            len--;
            j--;
        }
}

void extragereCuv(char token[][100], char exp[])
{
    char cuv[N];
    eliminareSpatii(exp);
    int len = strlen(exp);
    //nu este foarte eficient sa iteram pe expresie de doua ori, trebuie imbunatatit
    for(int j=0, i=0; j <= len; j++)
    {
        if(esteSeparator(exp[j]))
        {
            int n=0;
            for(int p=i; p<j; p++)
            {
                cuv[n++] = exp[p];
                int aux = esteFunctie(cuv);
                if(aux && exp[p+1] != 'h')
                {
                    if(aux == 19 || aux == 20)
                    {
                        do
                        {
                            p++;
                            cuv[n++] = exp[p];
                        } while(exp[p] != ']');
                    }
                j = p+1;
                break;
                }
            }
            cuv[n] = '\0';

            if(i != j)
                strcpy(token[E.lungime++], cuv);

            i = j+1;

            token[E.lungime][0] = exp[j];
            if(exp[j] == '>' && exp[j+1] == '=')
            {
                token[E.lungime][1] = exp[j+1];
                token[E.lungime][2] = '\0';
                i++;
                j++;
            }
            else if(exp[j] == '<' && exp[j+1] == '=')
            {
                token[E.lungime][1] = exp[j+1];
                token[E.lungime][2] = '\0';
                i++;
                j++;
            }
            else
            {
                token[E.lungime][1] = '\0';
            }
            E.lungime++;
        }
    }
    E.lungime--;
    strcpy(token[E.lungime], ")");
    E.lungime++;
}

int prioritate(char s[])  // prioritate operatorilor
{
    if(esteSeparator(s[0]))
    {
        if(s[0]=='(' || s[0]==')')
            return 0;
        if(s[0]=='+' || s[0]=='-')
            return 1;
        if(s[0]=='*' || s[0]=='/')
            return 2;
        if(s[0]=='^')
            return 3;
        if(s[0]=='=' || s[0]=='#' || s[0]=='<' || s[0]=='>')
            return 4;
    }
    return 5;
}

//-------------- functie pt corectitudine ------------//

int tipToken(char s[])
{
    if(s[0] == '(')
        return 1;
    if(s[0] == ')')
        return 2;
    if(strchr("+-", s[0]))
        return 3;
    if(strchr("*/^><=#", s[0]))
        return 4;
    if(esteFunctie(s))
        return 5;
    if(esteNumar(s) || esteConst(s) || esteVar(s))
        return 6;
    return 0;
    //daca functia returneaza 0, inseamna ca am intalnit un caracter ilegal
}

bool verifCorect(expr E)
{
    bool ok; //pt a verifica daca am gasit greseala
    bool corect = true; //pt a verifica corectitudinea expresiei in sine, va fi returnat
    int i = 0;
    int len = 0; //vom avea nevoie de un "contor" aditional, intrucat lungimea sirului de token-uri nu coincide cu lungimea expresiei
    while(i < E.lungime-1)
    {
        ok = true;
        len += strlen(E.token[i]);
        switch(tipToken(E.token[i]))
        {
        case 0:
        {
            ok = false;
            break;
        }
        case 1:
        {
            if(tipToken(E.token[i+1]) == 2 || tipToken(E.token[i+1]) == 4)
                ok = false;
            break;
        }
        case 2:
        {
            if(tipToken(E.token[i+1]) == 1 || tipToken(E.token[i+1]) == 5 || tipToken(E.token[i+1]) == 6)
                ok = false;
            break;
        }
        case 3:
        {
            if(tipToken(E.token[i+1]) == 2 || tipToken(E.token[i+1]) == 3 || tipToken(E.token[i+1]) == 4)
                ok = false;
            break;
        }
        case 4:
        {
            if(tipToken(E.token[i+1]) == 2 || tipToken(E.token[i+1]) == 3 || tipToken(E.token[i+1]) == 4)
                ok = false;
            break;
        }
        case 5:
        {
            if(tipToken(E.token[i+1]) != 1)
                ok = false;
            break;
        }
        case 6:
        {
            if(tipToken(E.token[i+1]) == 1 || tipToken(E.token[i+1]) == 5 || tipToken(E.token[i+1]) == 6)
                ok = false;
            break;
        }
        }
        if(ok == false)
        {
            if(corect == true)
            {
                cout << "Expresia este incorecta, avand urmatoarele greseli sintactice: " << endl;
                corect = false;
            }
            if(tipToken(E.token[i]) == 0)
                cout << "-Eroare pe pozitia " << len+1 << ": caracter ilegal" << endl;
            else cout << "-Eroare pe pozitia " << len+1 << ": dupa '" << E.token[i] << "' nu poate urma '" << E.token[i+1] << "'" << endl;
        }
        i++;
    }
    return corect;
}

//-------------- functii pt variabile ------------//

int dejaExista(char s[], listaVar L)
{
    //verifica daca deja am dat valoarea variabilei cu numele salvat in s
    //variabile sunt salvate ca o lista liniara practic, iar aceasta functie va returna indicele variabilei cu numele salvat in s in lista L
    for(int i = 0; i < L.nrElemente; i++)
        if(strcmp(s, L.var[i].nume) == 0)
            return i+1;
    return 0;
}

float valoareVar(char s[], listaVar L)
{
    //returneaza valoarea variabilei cu numele salvat in s
    return L.var[dejaExista(s,L) - 1].valoare;
}

void inserareVar(char s[], char numar[], listaVar &L)
{
    strcpy(L.var[L.nrElemente].nume, s);
    L.nrElemente++;
    if(!strcmp(numar, "p"))
    {
        L.var[L.nrElemente-1].valoare = p;
        return;
    }
    if(!strcmp(numar, "e"))
    {
        L.var[L.nrElemente-1].valoare = e;
        return;
    }
    if(!strcmp(numar, "phi"))
    {
        L.var[L.nrElemente-1].valoare = phi;
        return;
    }
    L.var[L.nrElemente-1].valoare = atof(numar);
}

void cautaVar(expr E, listaVar &L)
{
    //cauta si defineste variabilele din expresia E
    L.nrElemente = 0;
    char s[100];
    char numar[100];
    for(int i = 0; i < E.lungime; i++)
    {
        strcpy(s, E.token[i]);
        if(esteVar(s) && !(dejaExista(s, L)))
        {
            cout << "Introduceti valoarea variabilei " << s << ": ";
            cin >> numar;
            while(!esteConst(numar) && !esteNumar(numar))
            {
                cout << "Valoarea introdusa nu este un numar, introduceti din nou: ";
                cin >> numar;
            }
            inserareVar(s, numar, L);
        }
    }
}

void afisareVar(listaVar L)
{
    //functie pt testare
    for(int i = 0; i < L.nrElemente; i++)
        cout << "Variabila " << L.var[i].nume << " are valoarea " << L.var[i].valoare << "." << endl;
}

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
    if(aritate(val) == 2)
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
        }
    }
    else switch(esteFunctie(val))
        {
        //"sin", "cos", "tan", "cotan", "abs", "exp", "sqrt", "floor", "ceil", "round", "arcsin", "arccos", "arctan", "arccot", "sinh", "cosh", "tanh", "cotanh", "log", "root"
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
            char baza[100];
            int i, j;
            float b;
            i = 4;
            j = 0;
            while(val[i] != ']')
            {
                //log[x]
                baza[j] = val[i];
                j++;
                i++;
            }
            if(esteConst(baza))
            {
                b = esteConst(baza);
            }
            else b = atof(baza);
            return Impartit(Logaritm(valoareExpresie(A -> dr, L)), Logaritm(b));
            break;
        }
        case 20:
        {
            char baza[100];
            int i, j;
            float b;
            i = 5;
            j = 0;
            while(val[i] != ']')
            {
                //root[x]
                baza[j] = val[i];
                j++;
                i++;
            }
            if(esteConst(baza))
            {
                b = esteConst(baza);
            }
            else b = atof(baza);
            return Putere(valoareExpresie(A -> dr, L), 1/b);
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

//-------------- main --------------//

int main()
{
    char exp[N];
    cin.getline(exp, N-1);
    extragereCuv(E.token, exp);
    //-------- Test extragereCuv -------//

    /*
    for(int i=0; i < E.lungime; i++)
    {
        cout << endl << E.token[i];
    }
    cout << endl;
    */

    if(verifCorect(E))
    {
        formareArbore(E);
        cautaVar(E, L);
        arbore A;
        A = topOpd(Opd);
        float rezultat;
        rezultat = valoareExpresie(A, L);
        cout << rezultat;
    }

    return 0;
}
