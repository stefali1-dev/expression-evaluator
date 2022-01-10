//--------------- alte functii ------------//

bool esteSeparator(char c)
{
    char separatori[30] = "()+-*/^=<>#%@~`':;|\,.?!$";
    if(strchr(separatori, c) || c == '"')
        return true;
    return false;
}

operatorLogic esteOperatorLogic(char s[])
{
    operatorLogic op;
    //returneaza id-ul si lungimea operatorului logic, folositor in extragereCuv
    /*
    id not = 1
    id and = 2
    id or = 3
    id nand = 4
    id nor = 5
    id xor = 6
    */
    if(s[0] == 'N' && s[1] == 'O' && s[2] == 'T')
    {
        op.id = 1;
        op.len = 3;
        return op;
    }
    if(s[0] == 'A' && s[1] == 'N' && s[2] == 'D')
    {
        op.id = 2;
        op.len = 3;
        return op;
    }
    if(s[0] == 'O' && s[1] == 'R')
    {
        op.id = 3;
        op.len = 2;
        return op;
    }
    if(s[0] == 'N' && s[1] == 'A' && s[2] == 'N' && s[3] == 'D')
    {
        op.id = 4;
        op.len = 4;
        return op;
    }
    if(s[0] == 'N' && s[1] == 'O' && s[2] == 'R')
    {
        op.id = 5;
        op.len = 3;
        return op;
    }
    if(s[0] == 'X' && s[1] == 'O' && s[2] == 'R')
    {
        op.id = 6;
        op.len = 3;
        return op;
    }
    op.id = 0;
    op.len = 0;
    return op;
}

int esteFunctie(char s[])
{
    char functii[30][20] = {"sin", "cos", "tan", "cot", "abs", "exp", "sqrt", "floor", "ceil", "round", "arcsin", "arccos", "arctan", "arccot", "sinh", "cosh", "tanh", "coth", "log"};
    //mai trebuie adaugate
    for(int i=0; i<19; i++)
        if(strcmp(functii[i],s) == 0)
            return i+1;
    if(strstr(s, "log["))
        return 20;
    if(strstr(s, "root["))
        return 21;
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
    //returneaza constanta in sine
    if(strcmp(s, "pi") == 0)
        return pi;
    if(strcmp(s, "e") == 0)
        return e;
    if(strcmp(s, "phi") == 0)
        return phi;
    return 0;
}

bool esteVar(char s[])
{
    if(!(esteFunctie(s)) && !(esteNumar(s)) && !(esteSeparator(s[0])) && !(esteConst(s)) && !(esteOperatorLogic(s).id))
        return true;
    return false;
}

int aritate(char s[])
{
    if(esteFunctie(s) || !(strcmp(s, "NOT")) || s[0] == '@' || s[0] == '~')
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

int cazExceptieToken(char token[][100], char exp[], int i)
{
    if(exp[i] == '+' && ((E.lungime == 0) || token[E.lungime-1][0] == '('))
        return 1;
    if(exp[i] == '-' && ((E.lungime == 0) || token[E.lungime-1][0] == '('))
        return 2;
    if(strchr("<>", exp[i]) && exp[i+1] == '=')
        return 3;
    return 0;
}

void extragereCuv(char token[][100], char exp[])
{
    eliminareSpatii(exp);
    int len = strlen(exp);
    //nu este foarte eficient sa iteram pe expresie de doua ori, trebuie imbunatatit
    for(int j=0, i=0; j <= len; j++)
    {
        int OpL = esteOperatorLogic(exp+j).len;
        if(esteSeparator(exp[j]) || OpL)
        {
            int n=0;
            char cuv[N] = "";
            for(int p = i; p < j; p++)
            {
                cuv[n++] = exp[p];
                int auxf = esteFunctie(cuv);
                bool auxn = esteNumar(cuv);
                if(auxf)
                {
                    if((auxf == 1 || auxf == 2 || auxf == 3 || auxf == 4) && exp[p+1] == 'h')
                    {
                        p++;
                        cuv[n++] = exp[p];
                    }
                    else
                    {
                        if(auxf == 19 && exp[p+1] == '[')
                        {
                            p++;
                            cuv[n++] = exp[p];
                            auxf = 20;
                        }
                        if(auxf == 20 || auxf == 21)
                        {
                            do
                            {
                                p++;
                                cuv[n++] = exp[p];
                            }
                            while(exp[p] != ']');
                        }
                    }
                    j = p+1;
                    break;
                }
                else if(auxn)
                {
                    if(!esteNumar(exp+p))
                    {
                        j = p;
                        break;
                    }
                }
            }
            cuv[n] = '\0';

            if(i != j)
                strcpy(token[E.lungime++], cuv);

            if(OpL)
            {
                strncpy(token[E.lungime++], exp+j, OpL);
                j += OpL - 1;
            }
            else
            {
                switch(cazExceptieToken(token, exp, j))
                {
                case 0:
                {
                    //nici o exceptie, caz "default"
                    token[E.lungime][0] = exp[j];
                    token[E.lungime][1] = '\0';
                    break;
                }
                case 1:
                {
                    //plus unar
                    token[E.lungime][0] = '@';
                    token[E.lungime][1] = '@';
                    token[E.lungime][2] = '\0';
                    break;
                }
                case 2:
                {
                    //minus unar
                    token[E.lungime][0] = '~';
                    token[E.lungime][1] = '~';
                    token[E.lungime][2] = '\0';
                    break;
                }
                case 3:
                {
                    //mai mare/mic sau egal
                    token[E.lungime][0] = exp[j];
                    token[E.lungime][1] = exp[j+1];
                    token[E.lungime][2] = '\0';
                    j++;
                    break;
                }
                }
                E.lungime++;
            }
            i = j + 1;
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
        if(s[0]=='+' || s[0]=='-' || s[0]=='@' || s[0]=='~')
            return 1;
        if(s[0]=='*' || s[0]=='/' || s[0]=='%')
            return 2;
        if(s[0]=='^')
            return 3;
        if(s[0]=='=' || s[0]=='#' || s[0]=='<' || s[0]=='>')
            return 4;
    }
    if(esteOperatorLogic(s).id && strcmp(s, "NOT"))
        return 4;
    return 5;
}

void inlocuireUnar(char token[], char token_nou[])
{
    //inlocuieste '@@' (plusul unar) cu '+'
    //inlocuieste '~~' (minusul unar) cu '-'
    if(token[0] == '@')
    {
        strcpy(token_nou, "+");
        return;
    }
    if(token[0] == '~')
    {
        strcpy(token_nou, "-");
        return;
    }
    strcpy(token_nou, token);
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
    if(s[0] == '@' && s[1] == '@')
        return 3;
    if(s[0] == '~' && s[1] == '~')
        return 3;
    if(strchr("*/^><=#%", s[0]) || (esteOperatorLogic(s).id && strcmp(s, "NOT")))
        return 4;
    if(esteFunctie(s))
        return 5;
    if(esteNumar(s) || esteConst(s) || esteVar(s))
        return 6;
    if(!(strcmp(s, "NOT")))
        return 7;
    return 0;
    //daca functia returneaza 0, inseamna ca am intalnit un caracter ilegal
}

bool verifCorect(expr E)
{
    bool ok; //pt a verifica daca am gasit greseala
    bool corect = true; //pt a verifica corectitudinea expresiei in sine, va fi returnat
    int i = 0;
    int len = 0; //vom avea nevoie de un "contor" aditional, intrucat lungimea sirului de token-uri nu coincide cu lungimea expresiei
    int nrParanteze1 = 0;
    int nrParanteze2 = 0;
    while(i < E.lungime-1)
    {
        ok = true;
        len += strlen(E.token[i]);
        if((E.token[i][0] == '@' && E.token[i][1] == '@') || (E.token[i][0] == '~' && E.token[i][1] == '~'))
            len--;
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
            nrParanteze1++;
            break;
        }
        case 2:
        {
            if(tipToken(E.token[i+1]) == 1 || tipToken(E.token[i+1]) == 5 || tipToken(E.token[i+1]) == 6 || tipToken(E.token[i+1]) == 7)
                ok = false;
            nrParanteze2++;
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
            if(tipToken(E.token[i+1]) != 1 || tipToken(E.token[i+1]) == 7)
                ok = false;
            break;
        }
        case 6:
        {
            if(tipToken(E.token[i+1]) == 1 || tipToken(E.token[i+1]) == 5 || tipToken(E.token[i+1]) == 6 || tipToken(E.token[i+1]) == 7)
                ok = false;
            break;
        }
        case 7:
        {
            if(tipToken(E.token[i+1]) == 2 || tipToken(E.token[i+1]) == 4)
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
            char token_aux[100];
            inlocuireUnar(E.token[i], token_aux);
            if(tipToken(E.token[i]) == 0)
                cout << "-Eroare pe pozitia " << len << ": caracter ilegal '" << E.token[i][0] << "'" << endl;
            else
            {
                if(i != E.lungime-2) cout << "-Eroare pe pozitia " << len+1 << ": dupa '" << token_aux << "' nu poate urma '" << E.token[i+1] << "'" << endl;
                else if(tipToken(E.token[i]) == 5) cout << "-Eroare pe pozitia " << len+1 << ": lipseste argumentul functie '" << E.token[i] << "'" << endl;
                else if(!(strcmp(E.token[i], "NOT"))) cout << "-Eroare pe pozitia " << len+1 << ": lipseste argumentul operatiei 'NOT'";
                else cout << "-Eroare pe pozitia " << len+1 << ": lipseste un argument al operatiei '" << E.token[i] << "'" << endl;
            }
        }
        i++;
    }
    int nr = nrParanteze1 - nrParanteze2;
    if(nr == 1)
    {
        cout << "-Eroare: o paranteza nu a fost inchisa" << endl;
        corect = false;
    }
    else if(nr > 1)
    {
        cout << "-Eroare: " << nr << " paranteze nu au fost inchise" << endl;
        corect = false;
    }
    else if(nr < 0)
    {
        cout << "-Eroare: sunt prea multe paranteze de tip ')'";
        corect = false;
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
    return L.var[dejaExista(s, L) - 1].valoare;
}

void inserareVar(char s[], char numar[], listaVar &L)
{
    strcpy(L.var[L.nrElemente].nume, s);
    L.nrElemente++;
    if(!strcmp(numar, "pi"))
    {
        L.var[L.nrElemente-1].valoare = pi;
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

        //urmatoarele doua conditii sunt pentru cazul in care avem baza unui logaritm/ordinul unui radical ca variabila
        int auxf = esteFunctie(s);
        if(auxf == 20 || auxf == 21)
        {
            char baza[100];
            int j, n;
            j = auxf-16;
            n = 0;
            do
            {
                baza[n++] = s[j++];
            }
            while(s[j] != ']');
            baza[n++] = '\0';
            if(esteVar(baza) && !(dejaExista(baza, L)))
            {
                cout << "Introduceti valoarea variabilei " << baza << ": ";
                cin >> numar;
                while(!esteConst(numar) && !esteNumar(numar))
                {
                    cout << "Valoarea introdusa nu este un numar, introduceti din nou: ";
                    cin >> numar;
                }
                inserareVar(baza, numar, L);
            }
        }
    }
}

void afisareVar(listaVar L)
{
    //functie pt testare
    for(int i = 0; i < L.nrElemente; i++)
        cout << "Variabila " << L.var[i].nume << " are valoarea " << L.var[i].valoare << "." << endl;
}