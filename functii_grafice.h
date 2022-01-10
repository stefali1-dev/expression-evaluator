void afiseazaFereastra(char s[]){

    if(Fereastra.paragraf >= 20)
        Fereastra.paragraf = 1;

    outtextxy(20 , Fereastra.paragraf * Fereastra.H/20, s);
    Fereastra.paragraf++;
}

char* citesteSiAfiseaza(){
    char c, c_arr[2];
    char* s = (char*) malloc (100);
    int len = 0;
    int leftSpace = 20;
    while((int)(c = (char)getch()) != ENTER){
        s[len] = c;
        len++;
        c_arr[0] = c;
        c_arr[1] = '\0';

        outtextxy(leftSpace, Fereastra.paragraf * Fereastra.H/20 - textheight(c_arr)/2, c_arr);
        leftSpace += textwidth(c_arr);
    }
    s[len] = '\0';
    Fereastra.paragraf++;
    return s;
}
