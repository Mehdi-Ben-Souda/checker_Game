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
void calculer_cout_mvt(mouvement *cel ,int *cout)
{
    if(cel)
    {
        if(cel->IDa)
            *cout++;
        calculer_cout_mvt(cel->gch,cout);
        calculer_cout_mvt(cel->drt,cout);
    }
}
noeud *calcuer_cout_nd(noeud *N)
{
    int cout;
    calculer_cout_mvt(N->lejeu,&cout);
    N->score=cout;
    return ((noeud*)N);
}
/*
void Afficher_arbre(noeud *a)
{
    if(a)
    {
        noeud *tmp;

        while (a->svt)
    }

}

noeud *construire_niveau(noeud *N,int idj,pion Tab[24],int damier[NB_CASES][NB_CASES],int *i,int *niveau)
{
   if( *niveau <=2)
   {
       noeud *tmp,*tmp2;
       mouvement * m,*ptc;
       int k=0;
       int copy_damier[NB_CASES][NB_CASES];
       pion copy_lesjetons[NB_PIONS];
       if((*i)>=0 && (*i)<24 )
       {
           if((idj ==1 && *i >11) || (idj ==-1 && *i<12))  return ((noeud*)N);

           if(!N)
           {
               N=creeNoeud();
               N=tousLesMouvementsJetton((*i),damier,Tab,0);
               tmp=N;
           }
           else
           {
               tmp=N;
               while (tmp->svt)
                   tmp=tmp->svt;
               tmp->svt=creeNoeud();
               tmp->svt=tousLesMouvementsJetton((*i),damier,Tab,0);
               tmp=tmp->svt;
           }
           tmp2=tmp;

           while(tmp2)
           {
               ptc=tmp2->lejeu;
               copierLesJetons(copy_lesjetons, Tab);
               copierDamier(copy_damier, damier);
               while (ptc)
               {
                   m=creer_mouvement(ptc->x,ptc->y,ptc->IDj, ptc->IDa);
                   deplacerJeton(m, copy_damier, copy_lesjetons);
                  // ptc=ptc->svt;
               }
               (*niveau)++;
               tmp2->sous_jeu=construire_niveau(tmp2->sous_jeu,(idj*(-1)),copy_lesjetons,copy_damier,&k,niveau);
               tmp=tmp2;
               tmp2=tmp2->svt;
           }
           (*i)++;
           construire_niveau(tmp,idj,Tab,damier,i,niveau);
       }
   }
    (*niveau)--;
    return ((noeud*)N);
}
 */