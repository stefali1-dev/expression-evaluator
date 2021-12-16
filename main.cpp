#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <winbgim.h>
#include <graphics.h>
#define N 10000
#define infinit INT_MAX
#define epsi 0.0001
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
    if (fabs(x < epsi) || fabs(y) < epsi) return 0;
        else if (DifInf(x) && DifInf(y)) return x*y;
            else return infinit;
}

float Putere(float x, float y)
{
    // float p;
    if (x==0) return 0;
    else if (y==0) return 1;
    else if (x==infinit || y==infinit) return infinit;
    else
        return pow(x,y);
}

float Egal(float x, float y)
{
    return x==y;
}

float Diferit(float x, float y)
{
    return x!=y;
}

float MaiMic(float x, float y)
{
    return x < y;
}

bool MaiMare(float x, float y)
{
    return x > y;
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
    if (fabs(y)>epsi) return x/y;
    else return infinit;
}

float Sinus(float x)
{
    if (DifInf(x))  return sin(x);
    else return infinit;
}

float Cosinus(float x)
{
    if (DifInf(x))  return cos(x);
    else return infinit;
}

float Modul(float x)
{
    if (DifInf(x)) return fabs(x);
    else return infinit;
}

float Radical(float x)
{
    if (DifInf(x) && (x>epsi)) return sqrt(x);
    else return infinit;
}

// ------------ structuri ----------//

struct anod
{

    char val[100];
    anod *st;
    anod *dr;
};

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
    char tokenArr[N][100];
    int ArrLen = 0;

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
    delete s.varf;
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
    char functii[30][7] = {"sin", "cos", "abs", "exp", "ln", "sqrt"};
    //mai trebuie adaugate
    for(int i=0; i<6; i++)
        if(strcmp(functii[i],s) == 0)
            return i+1;
    return 0;
}

bool esteNumar(char s[])
{
    if(strchr("0123456789",s[0]) && s[0] != '\0')
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

void extragereCuv(char tokenArr[][100], char exp[])
{
    char cuv[N];
    int len = strlen(exp);
    strcpy(tokenArr[E.ArrLen], "(");
    E.ArrLen++;
    for(int j=0,i=0; j<=len; j++)
    {
        if(esteSeparator(exp[j]))
        {
            int n=0;
            for(int p=i; p<j; p++)
            {
                cuv[n++] = exp[p];
            }
            cuv[n] = '\0';

            if(i != j)
                strcpy(tokenArr[E.ArrLen++], cuv);

            i = j+1;

            tokenArr[E.ArrLen][0] = exp[j];
            tokenArr[E.ArrLen][1] = '\0';
            E.ArrLen++;
        }
    }
    E.ArrLen--;
    strcpy(tokenArr[E.ArrLen], ")");
    E.ArrLen++;
}

int prioritate(char s[])  // prioritate operatorilor
{
    if(esteSeparator(s[0])) {
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

void vechi_formareStive(expr E)
{
    initOpr(Opr); initOpd(Opd);
    //pushOpr(Opr, "(");
    int i=0;
    while (i < E.ArrLen)
    {
        if(esteSeparator(E.tokenArr[i][0]) || esteFunctie(E.tokenArr[i]))
        {
            pushOpr(Opr,E.tokenArr[i]);
        }
        else
        {
            anod *nod_nou;
            nod_nou = new anod;
            strcpy(nod_nou ->val, E.tokenArr[i]);
            pushOpd(Opd, nod_nou);
        }
        i++;
    }
    //pushOpr(Opr, ")");
}

void formareStive(expr E)
{
    initOpr(Opr); initOpd(Opd);
    pushOpr(Opr, "(");
    int i = 0;
    while (i<E.ArrLen && Opr.varf != NULL)
    {
        if (esteNumar(E.tokenArr[i]) || esteVar(E.tokenArr[i]) || esteConst(E.tokenArr[i]))
        {
            anod *nod_nou;
            nod_nou = new anod;
            strcpy(nod_nou -> val, E.tokenArr[i]);
            pushOpd(Opd, nod_nou);
        }
        else
            switch (E.tokenArr[i][0]) {
            case '(': /* inceput de bloc */ pushOpr(Opr, "("); break;
            default: {
                char val[100];
                strcpy(val, Opr.varf -> val);
                /* operatii binare si unare */
               while ((Opr.varf != NULL) && !(strchr("()",val[0])) && prioritate(val) >= prioritate(E.tokenArr[i]))
                {
                    anod *nodst, *noddr, *nod;
                    noddr = Opd.varf -> nod;
                    nodst = Opd.varf -> urm -> nod;
                    nod = new anod;
                    strcpy(nod -> val, val);
                    nod -> st = nodst;
                    nod -> dr = noddr;
                    if(aritate(val) == 2) popOpd(Opd);
                    if(esteSeparator(val[0]) || esteFunctie(val)) {
                        popOpd(Opd);
                        pushOpd(Opd,nod);
                    }
                    popOpr(Opr);
                }
            }
            // depanare();
            if (Opr.varf != NULL)
                if((strcmp(Opr.varf -> val, "(") != 0) || (strcmp(E.tokenArr[i],")") != 0))
                    {
                        pushOpr(Opr, E.tokenArr[i]);
                    }
                else popOpr(Opr);
            }
        i++;
    }
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

void inserareVar(char s[], float numar, listaVar &L)
{
    //insereaza o noua variabila
    strcpy(L.var[L.nrElemente].nume, s);
    L.var[L.nrElemente].valoare = numar;
    L.nrElemente++;
}

void cautaVar(expr E, listaVar &L)
{
    //cauta si defineste variabilele din expresia E
    L.nrElemente = 0;
    char s[100];
    float numar;
    for(int i = 0; i < E.ArrLen; i++) {
        strcpy(s, E.tokenArr[i]);
        //nu cred ca e necesar acest s intermediar dar verific altadata
        if(esteVar(s) && !(dejaExista(s, L))) {
            cout << "Introduceti valoarea variabilei " << s << ": ";
            cin >> numar;
            inserareVar(s, numar, L);
        }
    }
}
//functie pt testare
void afisareVar(listaVar L)
{
    for(int i = 0; i < L.nrElemente; i++)
        cout << "Variabila " << L.var[i].nume << " are valoarea " << L.var[i].valoare << "." << endl;
}
//-------------- functii pt formare arbore ------------//

void creareArbore()
{
    while(Opr.varf) {
        if(strcmp(Opr.varf -> val, "(") == 0 || strcmp(Opr.varf -> val, ")") == 0)
            popOpr(Opr);
        else{
            char val[20];
            strcpy(val, Opr.varf -> val);
            switch(aritate(val)) {
                case 1: {
                    anod* nodTemp;
                    nodTemp = new anod;
                    nodTemp -> dr = topOpd(Opd);
                    nodTemp -> st = NULL;
                    popOpd(Opd);
                    strcpy(nodTemp -> val, Opr.varf -> val);
                    //nou bloc
                    pushOpd(Opd, nodTemp);
                    break;
                }
                case 2: {
                    anod* nodTemp;
                    nodTemp = new anod;
                    nodTemp -> dr = topOpd(Opd);
                    popOpd(Opd);
                    nodTemp -> st = topOpd(Opd);
                    popOpd(Opd);
                    strcpy(nodTemp -> val, Opr.varf -> val);
                    //nou bloc
                    pushOpd(Opd, nodTemp);
                    break;
                }
            }
        Opr.varf = Opr.varf -> urm;
        }
    }
}

float valoareExpresie(anod* nod, listaVar L)
{
    char val[20];
    strcpy(val, nod -> val);
    if(esteNumar(val)) {
        return atof(val);
    }
    if(esteConst(val)) {
        return esteConst(val);
    }
    if(esteVar(val)) {
        return valoareVar(val, L);
    }
    if(aritate(val) == 2) {
           switch(val[0]) {
            case '+': {
                return Plus(valoareExpresie(nod -> st, L), valoareExpresie(nod -> dr, L));
                break;
            }
            case '-': {
                return Minus(valoareExpresie(nod -> st, L), valoareExpresie(nod -> dr, L));
                break;
            }
            case '*': {
                return Inmultit(valoareExpresie(nod -> st, L), valoareExpresie(nod -> dr, L));
                break;
            }
            case '^': {
                return Putere(valoareExpresie(nod -> st, L), valoareExpresie(nod -> dr, L));
                break;
            }
            case '/': {
                return Impartit(valoareExpresie(nod -> st, L), valoareExpresie(nod -> dr, L));
                break;
            }
            case '=': {
                return Egal(valoareExpresie(nod -> st, L), valoareExpresie(nod -> dr, L));
                break;
            }
            case '>': {
                return MaiMare(valoareExpresie(nod -> st, L), valoareExpresie(nod -> dr, L));
                break;
            }
            case '<': {
                return MaiMic(valoareExpresie(nod -> st, L), valoareExpresie(nod -> dr, L));
                break;
            }
            case '#': {
                return Diferit(valoareExpresie(nod -> st, L), valoareExpresie(nod -> dr, L));
                break;
            }
        }
    }
    else switch(esteFunctie(val)) {
        //"sin", "cos", "abs", "exp", "ln", "sqrt"
        case 1: {
            return Sinus(valoareExpresie(nod -> dr, L));
            break;
        }
        case 2: {
            return Cosinus(valoareExpresie(nod -> dr, L));
            break;
        }
        case 3: {
            return Modul(valoareExpresie(nod -> dr, L));
            break;
        }
        case 4: {
            return Exponential(valoareExpresie(nod -> dr, L));
            break;
        }
        case 5: {
            return Logaritm(valoareExpresie(nod -> dr, L));
            break;
        }
        case 6: {
            return Radical(valoareExpresie(nod -> dr, L));
            break;
        }
    }
}

//-------------- functii pt desenare arbore -----------//

//-------------- main --------------//

int main()
{

    char exp[N];
    cin.getline(exp, N-1);
    extragereCuv(E.tokenArr, exp);
    cautaVar(E, L);
    vechi_formareStive(E);
    creareArbore();
    //formareStive(E);
    //-------- Test extragereCuv -------//
    /*
    for(int i=0; i < E.ArrLen; i++){
        cout << endl << E.tokenArr[i];
    }
    cout << endl;
    */

    //------- Test stive -------//
    /*
    cout << "Operatorii:\n";
    printOpr(Opr);

    cout << "\nOperanzii:\n";
    printOpd(Opd);
    */

    //------- Test variabile ------//
    /*
    afisareVar(L);
    */

    //------- Test valoare (foarte simplu) -------//

    anod* nod;
    nod = topOpd(Opd);
    float rez;
    rez = valoareExpresie(nod, L);
    cout<< endl << rez;
    return 0;
}
