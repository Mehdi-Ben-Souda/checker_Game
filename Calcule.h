+int Min_Pliste(noeud *Maliste)
{
    int min;
    noeud *ptc;
    ptc = Maliste;
    ptc = ptc->svt;
    min = Maliste->cout;
    while (ptc)
    {
        if (ptc->cout < min)
            min = ptc->cout;
        ptc = ptc->svt;
    }
    return ((int)min);
}
int Max_Pliste(noeud *Maliste)
{
    int max;
    noeud *ptc;
    ptc = Maliste;
    ptc = ptc->svt;
    max = Maliste->cout;
    while (ptc)
    {
        if (ptc->cout > max)
            max = ptc->cout;
        ptc = ptc->svt;
    }
    return ((int)max);
}
int selectioner_cout(noeud *N)
{

}
noeud *calcuer_cout(noeud *N)
{
    mouvement *ptc;
    ptc=N->lejeu;
    N->cout=0;
    while(ptc)
    {
        if(ptc->IDa >0)
            N->cout++;
        ptc=ptc->svt;
    }
    return ((noeud*)N);
}