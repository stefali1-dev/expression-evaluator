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

struct snod{

    char val[100];
    snod * urm;

};

struct stiva{

    snod* varf;
    int nrElemente;
}S;

struct expr{

    char tokenArr[N][100];
    int ArrLen;

}E;

//-------------- functii stiva --------------//

void init(stiva s) {

    s.varf = NULL;
    s.nrElemente = 0;
}

char* pop(stiva &s) {
    char *val;
    strcpy(val, s.varf->val);

    snod* varf_nou = s.varf -> urm;

    delete s.varf;

    s.varf = varf_nou;
    s.nrElemente--;
    return val;
}

void push(stiva &s, char* val) {

    if(s.nrElemente == 0) {

        s.nrElemente = 1;
        s.varf = new snod;
        //s.varf -> val = elem;
        strcpy(s.varf->val, val);
        s.varf -> urm = NULL;
    }

    else {
        snod* nod_nou;
        nod_nou = new snod;

        s.nrElemente++;

        //nod_nou -> val = elem;
        strcpy(nod_nou->val, val);
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

            i = j+1;

            strcpy(tokenArr[E.ArrLen++], cuv);

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

