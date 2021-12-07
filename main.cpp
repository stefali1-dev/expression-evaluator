#include <iostream>
#include <string.h>
#include <stdio.h>
#define N 10000
using namespace std;

// ------------ structuri ----------//

struct anod{

    char val[100];
    struct nod *st;
    struct nod *dr;
};

struct nodOpr {
    char val[100];
    nodOpr * urm;
};

struct nodOpd {
    anod * nod;
    nodOpd * urm;
};

struct stivaOpr{
    nodOpr* varf;
    int nrElemente;
}Opr;

struct stivaOpd{
    nodOpd* varf;
    int nrElemente = 0;
}Opd;

struct expr{

    char tokenArr[N][100];
    int ArrLen = 0;

}E;

//-------------- functii stiva --------------//

void initOpr(stivaOpr &s) {
    s.varf = NULL;
    s.nrElemente = 0;
}
    
char* popOpr(stivaOpr &s) {
    char *val;
    strcpy(val, s.varf->val);

    nodOpr* varf_nou = s.varf -> urm;

    delete s.varf;

    s.varf = varf_nou;
    s.nrElemente--;
    return val;
}


void pushOpr(stivaOpr &s, char* val) {

    if(s.nrElemente == 0) {

        s.nrElemente = 1;
        s.varf = new nodOpr;
        //s.varf -> val = elem;
        strcpy(s.varf->val, val);
        s.varf -> urm = NULL;
    }

    else {
        nodOpr* nod_nou;
        nod_nou = new nodOpr;

        s.nrElemente++;

        //nod_nou -> val = elem;
        strcpy(nod_nou->val, val);
        nod_nou -> urm = s.varf;
        s.varf = nod_nou;
    }

}

void initOpd(stivaOpd &s) {
    s.varf = NULL;
    s.nrElemente = 0;
}

anod* popOpd(stivaOpd &s) {
    anod * nod = s.varf -> nod;

    nodOpd* varf_nou = s.varf -> urm;

    delete s.varf;

    s.varf = varf_nou;
    s.nrElemente--;
    return nod;
}

void pushOpd(stivaOpd &s, anod* nod) {

    if(s.nrElemente == 0) {

        s.nrElemente = 1;
        s.varf = new nodOpd;

        s.varf -> nod = nod;
        s.varf -> urm = NULL;
    }

    else {
        nodOpd* nod_nou;
        nod_nou = new nodOpd;

        s.nrElemente++;

        //nod_nou -> val = elem;
        nod_nou -> nod = nod;
        nod_nou -> urm = s.varf;
        s.varf = nod_nou;
    }

}

//--------------- alte functii ------------//

bool isSeparator(char c){

    char separatori[20] = "()+-*/^=<>#";
    if(strchr(separatori, c))
        return true;
    return false;
}

void extragereCuv(char tokenArr[][100], char exp[]){
    char cuv[N];
    int len = strlen(exp);

    for(int j=0,i=0; j<len; j++){

        if(isSeparator(exp[j])){

            int n=0;
            for(int p=i; p<j; p++){
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
}

int main()
{
    /*
    char exp[N];
    cin.getline(exp, N-1);

    extragereCuv(E.tokenArr, exp);

    for(int i=0; i<E.ArrLen; i++){
        cout << endl << E.tokenArr[i];
    }
    */
    
    return 0;
}

