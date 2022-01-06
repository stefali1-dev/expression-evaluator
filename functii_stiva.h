using namespace std;
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
