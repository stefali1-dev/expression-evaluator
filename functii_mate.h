// ----------------- functii matematice ----------------//

float Logaritm(float x)
{
    if(x < 0 || EsteNaN(x))
        return NAN;
    if (x>epsi && DifInf(x))
    {
        if(fabs(log(x)) > epsi)
            return log(x);
        else return 0;
    }
    if(x < epsi && x > 0) return infinit;
}

float LogaritmBazaB(float x, float b)
{
    return Impartit(Logaritm(x), Logaritm(b));
}

float Exponential(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(exp(x)) > epsi)
            return exp(x);
        else return 0;
    }
    else return infinit;
}

float Sinus(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(sin(x)) > epsi) return sin(x);
        else return 0;
    }
    else return infinit;
}

float Cosinus(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(cos(x)) > epsi) return cos(x);
        else return 0;
    }
    else return infinit;
}

float Tangenta(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(tan(x)) > epsi) return tan(x);
        else return 0;
    }
    else return infinit;
}

float Cotangenta(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(1/tan(x)) > epsi) return 1/tan(x);
        else return 0;
    }
    else return infinit;
}

float Modul(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(x) > epsi) return fabs(x);
        else return 0;
    }
    else return infinit;
}

float Radical(float x)
{
    if (x < 0 || EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(sqrt(x) > epsi) return sqrt(x);
        else return 0;
    }
    else return infinit;
}

float RadicalOrdinN(float x, float n)
{
    return Putere(x, 1/n);
}

float ParteIntreagaInf(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x)) return floor(x);
    else return infinit;
}

float ParteIntreagaSup(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x)) return ceil(x);
    else return infinit;
}

float Rotunjit(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(x - floor(x) < ceil(x) - x)
            return floor(x);
        else return ceil(x);
    }
    else return infinit;
}

float Arcsinus(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(asin(x)) > epsi) return asin(x);
        else return 0;
    }
    else return infinit;
}

float Arccosinus(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(acos(x)) > epsi) return acos(x);
        else return 0;
    }
    else return infinit;
}

float Arctangenta(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(atan(x)) > epsi) return atan(x);
        else return 0;
    }
    else return pi/2;
}

float Arccotangenta(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(atan(1/x)) > epsi) return atan(1/x);
        else return 0;
    }
    else return 0;
}

float SinusHiper(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(sinh(x)) > epsi) return sinh(x);
        else return 0;
    }
    else return infinit;
}

float CosinusHiper(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(cosh(x)) > epsi) return sinh(x);
        else return 0;
    }
    else return infinit;
}

float TangentaHiper(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(fabs(tanh(x)) > epsi) return tanh(x);
        return 0;
    }
    else return infinit;
}

float CotangentaHiper(float x)
{
    if (EsteNaN(x))
        return NAN;
    if (DifInf(x))
    {
        if(1/fabs(tanh(x)) > epsi) return 1/tanh(x);
        else return 0;
    }
    else return infinit;
}
