//--------------- alte functii ------------//

bool esteSeparator(char c)
{
    char separatori[25] = "()+-*/^=<>#%@~`':;|,?!$";
    if(strchr(separatori, c) || c == '"' || c == '\\')
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
    if(strchr("0123456789.",s[0]) && s[0] != '\0')
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

int esteConstLogica(char s[])
{
    if(strcmp(s, "TRUE") == 0 || strcmp(s, "true") == 0)
        return 1;
    if(strcmp(s, "FALSE") == 0 || strcmp(s, "false") == 0)
        return 2;
    return 0;
}

bool esteVar(char s[])
{
    if(s[0] == '_')
        return false;
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

int cazExceptieToken(char token[][DIMEN_MAXIMA_TOKEN], int i)
{
    if(E.sir[i] == '+' && ((E.lungime == 0) || token[E.lungime-1][0] == '('))
        return 1;
    if(E.sir[i] == '-' && ((E.lungime == 0) || token[E.lungime-1][0] == '('))
        return 2;
    if(strchr("<>", E.sir[i]) && E.sir[i+1] == '=')
        return 3;
    return 0;
}

void extragereCuv(char token[][DIMEN_MAXIMA_TOKEN])
{
    eliminareSpatii(E.sir);
    int len = strlen(E.sir);
    for(int j=0, i=0; j <= len; j++)
    {
        int OpL = esteOperatorLogic(E.sir+j).len;
        if(esteSeparator(E.sir[j]) || OpL)
        {
            int n=0;
            char cuv[N] = "";
            for(int p = i; p < j; p++)
            {
                //sinx
                cuv[n++] = E.sir[p];
                int auxf = esteFunctie(cuv);
                bool auxn = esteNumar(cuv);
                if(auxf)
                {
                    if((auxf == 1 || auxf == 2 || auxf == 3 || auxf == 4) && E.sir[p+1] == 'h')
                    {
                        p++;
                        cuv[n++] = E.sir[p];
                    }
                    else
                    {
                        //log[
                        if(auxf == 19 && E.sir[p+1] == '[')
                        {
                            p++;
                            cuv[n++] = E.sir[p];
                            auxf = 20;
                        }
                        if(auxf == 20 || auxf == 21)
                        {
                            int parPatrDeschise = 0;
                            int parPatrInchise = 1;
                            do
                            {
                                p++;
                                cuv[n++] = E.sir[p];
                                if(E.sir[p] == '[')
                                    parPatrInchise++;
                                if(E.sir[p] == ']')
                                    parPatrDeschise++;
                            }
                            while(parPatrDeschise != parPatrInchise);
                            //am folosit acesti contori pentru a asigura, de exemplu, ca log[log[x]](y) va fi gasit ca greseala
                            //intrucat, dupa conventie, baza unui logaritm poate fi numai nu numar pozitiv, o constanta sau o singura variabila
                        }
                    }
                    j = p+1;
                    break;
                }
                else if(auxn)
                {
                    if(!esteNumar(E.sir+p))
                    {
                        if(E.sir[p-1] == '.')
                        {
                            j = p-1;
                            n -= 2;
                        }
                        else
                        {
                            j = p;
                            n = n - 1;
                        }
                        break;
                    }
                }
            }
            cuv[n] = '\0';

            if(i != j)
                strcpy(token[E.lungime++], cuv);

            if(OpL)
            {
                strncpy(token[E.lungime++], E.sir+j, OpL);
                j += OpL - 1;
            }
            else
            {
                switch(cazExceptieToken(token, j))
                {
                case 0:
                {
                    //nici o exceptie, caz "default"
                    token[E.lungime][0] = E.sir[j];
                    token[E.lungime][1] = '\0';
                    break;
                }
                case 1:
                {
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
                    token[E.lungime][0] = E.sir[j];
                    token[E.lungime][1] = E.sir[j+1];
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

bool esteExpresieSimpla(char s[])
{
    //verifica daca o expresie este formata dintr-un singur numar, constanta sau variabila
    //"x", "2", "pi" sunt expresii simple
    //"2*x", "2+2", "2x", "sin", "sin(x)" nu sunt expresii simple si toate au mai multe token-uri
    //de aceea este folosit extragereCuv
    //folosit pt verificarea corectitudinii bazei/ordinului logaritmilor/radicalilor
    char token_aux[100][DIMEN_MAXIMA_TOKEN];
    int lungime_aux = E.lungime;
    char sir_aux[N];
    strcpy(sir_aux, E.sir);

    E.lungime = 0;
    strcpy(E.sir, s);
    extragereCuv(token_aux);
    if(E.lungime != 2)
    {
        strcpy(E.sir, sir_aux);
        E.lungime = lungime_aux;
        return false;
    }
    if(esteFunctie(token_aux[0]) || esteConstLogica(token_aux[0]))
    {
        strcpy(E.sir, sir_aux);
        E.lungime = lungime_aux;
        return false;
    }
    strcpy(E.sir, sir_aux);
    E.lungime = lungime_aux;
    return true;
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
    if((esteNumar(s) && s[0] != '.') || esteConst(s) || esteVar(s))
        return 6;
    if(!(strcmp(s, "NOT")))
        return 7;
    return 0;
    //daca functia returneaza 0, inseamna ca am intalnit un caracter ilegal
}

bool verifCorect()
{
    bool ok; //pt a verifica daca am gasit greseala
    int ok_baza = 0; //pt a verifica daca baza/ordinul unui logaritm/radical este corect
    int len_baza;
    bool corect = true; //pt a verifica corectitudinea expresiei in sine, va fi returnat
    int i = 0;
    int len = 0; //vom avea nevoie de un "contor" aditional, intrucat lungimea sirului de token-uri nu coincide cu lungimea expresiei
    int nrParanteze1 = 0;
    int nrParanteze2 = 0;

    char temp[100];
    int poz;
    char poz_arr[100];

    while(i < E.lungime-1)
    {
        ok = true;
        len += strlen(E.token[i]);
        if((E.token[i][0] == '@' && E.token[i][1] == '@') || (E.token[i][0] == '~' && E.token[i][1] == '~'))
            len--;
        switch(tipToken(E.token[i]))
        {
        //verificam, pentru fiecare token, daca token-ul urmator este valid
        //de exemplu, dupa "+" poate urma "x" dar dupa "(" nu poate urma ")"
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
            int auxf = esteFunctie(E.token[i]);
            if(auxf == 20 || auxf == 21)
            {
                char baza[20];
                int j;
                j = auxf-16;
                // daca auxf == 20 sau 21, atunci avem E.token[] este fie log[...] fie root[...]
                // in momentul de fata, vrem sa salvam baza/ordinul log./rad. in baza[] si incepem
                // sa salvam de la E.token[auxf-16], adica E.token[4] sau E.token[5], care coincide, intrucat:
                // "log[" -> 4 caractere, "root[" -> 5 caractere
                len_baza = 0;
                do
                {
                    baza[len_baza++] = E.token[i][j++];
                }
                while(E.token[i][j] != ']');
                baza[len_baza++] = '\0';
                if(!esteExpresieSimpla(baza))
                    ok_baza = auxf - 19;
                //verificam pentru ca sa nu avem expresii complexe (precum "2+2") ca baza/ordinul unui logaritm/radical
                //ce este numai o conventie, pur si simplu nu am adaugat optiunea din motiv de simplicitate
                //ok_baza == 1 cand baza unui logaritm nu este expresie simpla
                //ok_baza == 2 cand ordinul unui radical nu este expresie simpla
                //ok_baza == 0 cand nici nu intram in cazul asta (token-ul nu este "log[...]" sau "root[...]")
                //sau cand este dar baza/ordinul este un singur numar pozitiv, o constanta sau o singura variabila
            }
            if(tipToken(E.token[i+1]) != 1 && tipToken(E.token[i+1]) != 0)
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
            if(tipToken(E.token[i+1]) == 2 || tipToken(E.token[i+1]) == 3 || tipToken(E.token[i+1]) == 4)
                ok = false;
            break;
        }
        }

        if(ok_baza)
        {
            if(corect == true)
            {
                strcpy(temp, "Expresia este incorecta, avand urmatoarele greseli sintactice: ");
                afiseazaFereastra(temp);
                corect = false;
            }
            if(ok_baza == 1)
            {
                strcpy(temp, "-Eroare pe pozitia ");
                poz = len - len_baza + 1;

                sprintf(poz_arr, "%d", poz);
                strcat(temp, poz_arr);
                strcat(temp, ": baza unui logaritm poate fi numai un numar pozitiv, constanta sau o singura variabila");
                afiseazaFereastra(temp);
            }
            else
            {
                strcpy(temp, "-Eroare pe pozitia ");
                poz = len - len_baza + 1;

                sprintf(poz_arr, "%d", poz);
                strcat(temp, poz_arr);
                strcat(temp, ": ordinul unui radical poate fi numai un numar pozitiv, constanta sau o singura variabila");
                afiseazaFereastra(temp);
            }
        }
        ok_baza = 0;
        if(ok == false)
        {
            if(corect == true)
            {
                strcpy(temp, "Expresia este incorecta, avand urmatoarele greseli sintactice: ");
                afiseazaFereastra(temp);
                // cout << "Expresia este incorecta, avand urmatoarele greseli sintactice: " << endl;
                corect = false;
            }
            char token_nou[100];
            inlocuireUnar(E.token[i], token_nou);
            //@@ -> +
            //~~ -> -
            //restul ramane neschimbat
            if(tipToken(E.token[i]) == 0)
            {
                //orice token cu tip 0 este un caracter nedefinit, deci este considerat ilegal
                strcpy(temp, "-Eroare pe pozitia ");
                sprintf(poz_arr, "%d", len);
                strcat(temp, poz_arr);
                strcat(temp, ": caracter ilegal '");
                strcat(temp, E.token[i]);
                strcat(temp, "'");
                afiseazaFereastra(temp);
            }
            else
            {
                poz = len+1;
                sprintf(poz_arr, "%d", poz);
                strcpy(temp, "-Eroare pe pozitia ");
                strcat(temp, poz_arr);
                if(i != E.lungime-2)
                {
                    strcat(temp, ": dupa '");
                    strcat(temp, token_nou);
                    strcat(temp, "' nu poate urma '");
                    strcat(temp, E.token[i+1]);
                    strcat(temp, "'");
                }
                else if(tipToken(E.token[i]) == 5)
                {
                    strcat(temp, ": lipseste argumentul functiei '");
                    strcat(temp, E.token[i]);
                    strcat(temp, "'");
                }
                else if(!(strcmp(E.token[i], "NOT")))
                {
                    strcat(temp, ": lipseste argumentul operatiei 'NOT'");
                }
                else
                {
                    strcat(temp, ": lipseste un argument al operatiei '");
                    strcat(temp, E.token[i]);
                    strcat(temp, "'");
                }
                afiseazaFereastra(temp);
            }
        }
        i++;
    }
    int nr = nrParanteze1 - nrParanteze2;
    if(nr == 1)
    {
        strcpy(temp, "-Eroare: o paranteza nu a fost inchisa");
        afiseazaFereastra(temp);
        corect = false;
    }
    else if(nr > 1)
    {
        strcpy(temp, "-Eroare: ");
        sprintf(poz_arr, "%d", nr);
        strcat(temp, poz_arr);
        strcat(temp, " paranteze nu au fost inchise");
        afiseazaFereastra(temp);
        corect = false;
    }
    else if(nr < 0)
    {
        strcpy(temp, "-Eroare: sunt prea multe paranteze de tip ')'");
        afiseazaFereastra(temp);;
        corect = false;
    }
    return corect;
}

//-------------- functii pt variabile ------------//

int dejaExista(char s[])
{
    //verifica daca deja am dat valoarea variabilei cu numele salvat in s
    //variabile sunt salvate ca o lista liniara practic, iar aceasta functie va returna indicele variabilei cu numele salvat in s in lista L
    for(int i = 0; i < L.nrElemente; i++)
        if(strcmp(s, L.var[i].nume) == 0)
            return i+1;
    return 0;
}

float valoareVar(char s[])
{
    //returneaza valoarea variabilei cu numele salvat in s
    return L.var[dejaExista(s) - 1].valoare;
}

void inserareVar(char s[], char numar[])
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
    if(!strcmp(numar, "true") || !strcmp(numar, "TRUE"))
    {
        L.var[L.nrElemente-1].valoare = 1;
        return;
    }
    if(!strcmp(numar, "false") || !strcmp(numar, "FALSE"))
    {
        L.var[L.nrElemente-1].valoare = 0;
        return;
    }
    L.var[L.nrElemente-1].valoare = atof(numar);
}

void cautaVar()
{
    //cauta si defineste variabilele din expresia E
    char s[100];
    char numar[100];
    char temp[1000];
    for(int i = 0; i < E.lungime; i++)
    {
        strcpy(s, E.token[i]);
        if(esteConstLogica(s))
        {
            if(esteConstLogica(s) == 1)
                inserareVar(s, "1");
            else inserareVar(s, "0");
        }
        else if(esteVar(s) && !(dejaExista(s)))
        {
            strcpy(temp, "Introduceti valoarea");
            afiseazaFereastra(temp);

            strcpy(temp, "variabilei ");
            strcat(temp, s);
            strcat(temp, ":");
            afiseazaFereastra(temp);

            strcpy(numar, citesteSiAfiseaza());

            while(!esteConst(numar) && !esteNumar(numar))
            {
                strcpy(temp, "Valoarea introdusa");
                afiseazaFereastra(temp);

                strcpy(temp, "nu este un numar");
                afiseazaFereastra(temp);

                strcpy(temp, "Introduceti din nou:");
                afiseazaFereastra(temp);

                strcpy(numar, citesteSiAfiseaza());
            }
            inserareVar(s, numar);
        }

        //urmatoarele doua conditii sunt pentru cazul in care avem baza unui logaritm/ordinul unui radical ca variabila
        int auxf = esteFunctie(s);
        if(auxf == 20 || auxf == 21)
        {
            char baza[100];
            int j, n;
            j = auxf-16;
            // daca auxf == 20 sau 21, atunci avem E.token[] este fie log[...] fie root[...]
            // in momentul de fata, vrem sa salvam baza/ordinul log./rad. in baza[] si incepem
            // sa salvam de la E.token[auxf-16], adica E.token[4] sau E.token[5], care coincide, intrucat:
            // "log[" -> 4 caractere, "root[" -> 5 caractere
            n = 0;
            do
            {
                baza[n++] = s[j++];
            }
            while(s[j] != ']');
            baza[n++] = '\0';
            if(esteConstLogica(baza))
            {
                if(esteConstLogica(baza) == 1)
                    inserareVar(baza, "1");
                else inserareVar(baza, "0");
            }
            if(esteVar(baza) && !(dejaExista(baza)))
            {
                strcpy(temp, "Introduceti valoarea");
                afiseazaFereastra(temp);

                strcpy(temp, "variabilei ");
                strcat(temp, baza);
                strcat(temp, ":");
                afiseazaFereastra(temp);

                strcpy(numar, citesteSiAfiseaza());
                while(!esteConst(numar) && !esteNumar(numar))
                {
                    strcpy(temp, "Valoarea introdusa");
                    afiseazaFereastra(temp);

                    strcpy(temp, "nu este un numar");
                    afiseazaFereastra(temp);

                    strcpy(temp, "Introduceti din nou:");
                    afiseazaFereastra(temp);
                    strcpy(numar, citesteSiAfiseaza());
                }
                inserareVar(baza, numar);
            }
        }
    }
}
