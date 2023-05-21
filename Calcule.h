int selectioner_cout(noeud *N,enum maxmin E)
{
    int Val;
    noeud *ptc;
    ptc = N;
    ptc = ptc->svt;
    Val = N->score;
    if (E == 1)
    {
        while (ptc)
        {
            if (ptc->score < Val)
                Val = ptc->score;
            ptc = ptc->svt;
        }
    }
    else
    {
        while (ptc)
        {
            if (ptc->score > Val)
                Val = ptc->score;
            ptc = ptc->svt;
        }
    }
    return ((int)Val);
}
noeud *calcuer_cout(noeud *N)
{
    mouvement *ptc;
    ptc=N->lejeu;
    N->score=0;
    while(ptc)
    {
        if(ptc->IDa >0)
            N->score++;
        ptc=ptc->svt;
    }
    return ((noeud*)N);
}