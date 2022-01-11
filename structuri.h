#define DIMEN_MAXIMA_TOKEN 20
#define N 485
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
    char token[100][DIMEN_MAXIMA_TOKEN], sir[N];
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

struct operatorLogic
{
    int id;
    /*
    id not = 0
    id and = 1
    id or = 2
    id nand = 3
    id nor = 4
    id xor = 5
    */
    int len;
};

struct cel{
    int inaltime, latime;
}Celula;

struct{
    int left, top, right, bottom;
}CasetaText;

struct {
    int W, H, paragraf = 1;
}Fereastra;
