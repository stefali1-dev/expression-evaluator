void afiseazaFereastra(char s[])
{
    if(textwidth(s) + 20 > Fereastra.W*0.2)
    {
        int k = 0;
        char s_nou[100];
        for(int i=strlen(s)-1; i>=0; i--)
        {
            if(s[i] == ' ')
                k++;
            if(k==2)
            {
                strcpy(s_nou, s+i+1);
                s[i] = '\0';
                afiseazaFereastra(s);
                afiseazaFereastra(s_nou);
                return;
            }
        }
    }
    if(Fereastra.paragraf >= 29)
    {
        Fereastra.paragraf = 1;
        cleardevice();
    }

    outtextxy(20, Fereastra.paragraf * Fereastra.H/30, s);
    Fereastra.paragraf++;
}

char* citesteSiAfiseaza()
{
    char c, c_arr[2];
    char* s = (char*) malloc (100);
    int len = 0;
    int leftSpace = 20;
    while((int)(c = (char)getch()) != ENTER)
    {
        s[len] = c;
        len++;
        c_arr[0] = c;
        c_arr[1] = '\0';

        outtextxy(leftSpace, Fereastra.paragraf * Fereastra.H/30 - textheight(c_arr)/2, c_arr);
        leftSpace += textwidth(c_arr);
    }
    s[len] = '\0';
    Fereastra.paragraf++;
    return s;
}
