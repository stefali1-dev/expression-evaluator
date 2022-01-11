#define infinit LONG_LONG_MAX
#define epsi 0.0001

// ------------ constante matematice ------------ //

const float pi = 3.1415926536;
const float e = 2.7182818284;
const float phi = 1.6180339887;

// ------------ operatii logice --------------//

float Not(float x)
{
    return !x;
}

float And(float x, float y)
{
    return x && y;
}

float Or(float x, float y)
{
    return x || y;
}

float Nand(float x, float y)
{
    return !(x && y);
}

float Nor(float x, float y)
{
    return !(x || y);
}

float Xor(float x, float y)
{
    return ((x && !y) || (!x && y));
}

// ------------ operatii matematice simple ------------//

bool EsteNaN(float x)
{
    return x != x;
}

bool DifInf(float x)
{
    return fabs(x) < infinit;
}

float Inmultit(float x, float y)
{
    if (EsteNaN(x) || EsteNaN(y))
        return NAN;
    if (fabs(x) < epsi || fabs(y) < epsi) return 0;
    else if (DifInf(x) && DifInf(y)) return x*y;
    else return infinit;
}

float Putere(float x, float y)
{
    if (EsteNaN(x) || EsteNaN(y))
        return NAN;
    if (x == 0) return 0;
    else if (y == 0) return 1;
    else if (x == infinit || y == infinit) return infinit;
    else if (fabs(pow(x,y)) > epsi) return pow(x,y);
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
    if (EsteNaN(x) || EsteNaN(y))
        return NAN;
    if (DifInf(x) && DifInf(y))
    {
        if(fabs(x+y) > epsi) return x+y;
        else return 0;
    }
    else return infinit;
}

float Minus(float x, float y)
{
    if (EsteNaN(x) || EsteNaN(y))
        return NAN;
    if (DifInf(x) && DifInf(y))
    {
        if(fabs(x-y) > epsi) return x-y;
        else return 0;
    }
    else return infinit;
}

float Impartit(float x, float y)
{
    if (EsteNaN(x) || EsteNaN(y))
        return NAN;
    if (fabs(y) > epsi) return x/y;
    else return infinit;
}

float Rest(float x, float y)
{
    if (EsteNaN(x) || EsteNaN(y))
        return NAN;
    if (DifInf(x) && fabs(y) > epsi) return fmod(x, y);
    else return infinit;
}

