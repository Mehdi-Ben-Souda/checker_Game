/*
 * Fonction qui determine tous les mouvements possibles pour un pion ordinaire
 */
mouvement *Mouvements(int id,int damier[NB_CASES][NB_CASES],
                      pion pions[NB_PIONS],mouvement *N,int v,
                      int h,int typemvt)
{
    //déclaration des variables
    int damier1[NB_CASES][NB_CASES];
    pion pions1[NB_PIONS];
    int x=pions[id].x;
    int y=pions[id].y;
        if(x+h<8 &&y+v<8 && x+h>=0 &&y+v>=0)//s'il a une case libre pour boujer
        {
            if(damier[y+v][x+h]==-1 &&typemvt ==0)
                //s'il va faire une mouvement sans capturer un pion adversaire
                N = creer_mouvement(x + h, y + v, id, -1);
            //s'il a un pion adversaire à coté
            else if((damier[y+v][x+h]<12 && damier[y][x]>11)
                    || (damier[y+v][x+h]>11 && damier[y][x]<12) )
            {
                //s'il peut capurer cette pion de l'adversaire
                if(damier[y+(v*2)][x+(h*2)]==-1)
                {
                    //on garde cette mouvement
                    N=creer_mouvement(x+(h*2),y+(v*2),id,damier[x+h][y+v]);
                    //on fait une copie du damier et on applique cette mouvement
                    copierDamier(damier1,damier);
                    copierLesJetons(pions1,pions);
                    deplacerJeton(N,damier1,pions1);
                    //on cherche les mouvements complexes à droite et à gauche
                    N->gch = Mouvements(id, damier1, pions1, N->gch, v,-1,1);
                    N->drt = Mouvements(id, damier1, pions1, N->drt, v,1,1);
                }
            }
        }
        //retourner le noeud des mouvements
    return ((mouvement*)N);
}
/*
* Fonction qui determine tous les mouvements possibles pour un pion dame
*/
mouvement *Dame(int id,int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS],mouvement *N,int v,int h,int typemvt)
{
    //déclaration des variabes
    int damier1[NB_CASES][NB_CASES];
    pion pions1[NB_PIONS];
    int a,b,c,d;
    int x=pions[id].x;
    int y=pions[id].y;
    mouvement *T,*T2;
    a=x+h;
    b=y+v;
    //tant qu'il y'a des cases dans le damier
    while(a<8 && b<8 && a>=0 && b>=0)
    {
        if(damier[b][a]==-1 &&typemvt ==0)//si la case est libre
        {
            T= creer_mouvement(a, b, id, -1);
            N= insererListeMouvement(N,T);
            a=a+h;
            b=b+v;
        }
        else
        {
            if((damier[b][a]<12 && damier[b][a]>=0 && damier[y][x]>11)
               || (damier[b][a]>11 && damier[y][x]<12 && damier[y][x]>=0) )
            {
                c=a;
                d=b;
                c=c+h;
                d=d+v;
                while(c<8 && d<8&& c>=0 && d>=0)
                {
                    if(damier[d][c] ==-1)
                    {
                        typemvt=1;
                        T= creer_mouvement(c,d,id,damier[b][a]);
                        T2=creer_mouvement(c,d,id,damier[b][a]);
                        copierDamier(damier1,damier);
                        copierLesJetons(pions1,pions);
                        deplacerJeton(T,damier1,pions1);
                        T->gch= Dame(id,damier1,pions1,T->gch,v,-1,1);
                        T->drt= Dame(id,damier1,pions1,T->drt,v,1,1);
                        T2->gch=Dame(id,damier1,pions1,T2->gch,v*(-1),h,1);
                        N= insererListeMouvement(N,T);
                        if(T2->gch)
                            N=insererListeMouvement(N,T2);
                        c=c+h;
                        d=d+v;
                    }
                    else break;
                }
            }
            a=a+h;
            b=b+v;
        }
    }
    return ((mouvement*)N);
}
/*
 * Fonction qui determine tous les mouvements possibles pour un pion quelconque
 */
noeud *Mouvements_Possibles(int id,int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS])
{
    int v;
    noeud *A=creeNoeud();
    noeud *tmp;
    tmp=A;
    if(pions[id].etat ==2)//s'il s'agit d'un dame
    {
        //on cherche les mouvements possibles dans les 4 directions
        tmp->lejeu= Dame(id,damier,pions,tmp->lejeu,1,-1,SIMPLE);// sense verticale = 1 et sens horizontale =-1

        tmp->svt=creeNoeud();
        tmp=tmp->svt;
        tmp->lejeu= Dame(id,damier,pions,tmp->lejeu,1,1,SIMPLE);// sense verticale = 1 et sens horizontale =1

        tmp->svt=creeNoeud();
        tmp=tmp->svt;
        tmp->lejeu= Dame(id,damier,pions,tmp->lejeu,-1,-1,SIMPLE);// sense verticale = -1 et sens horizontale =-1

        tmp->svt=creeNoeud();
        tmp=tmp->svt;
        tmp->lejeu= Dame(id,damier,pions,tmp->lejeu,-1,1,SIMPLE);// sense verticale = -1 et sens horizontale =1
    }
    else//sinon
    {
        //on determine le sens vertical du joueur
        if(id<12) v=1;
        else
            v=-1;
        //v :sens vertical pour un joueur, sens horizontale =1
        tmp->lejeu= Mouvements(id,damier,pions, tmp->lejeu,v,1,SIMPLE);
        //v :sense vertical pour un joueur, sens horizontale =-1
        tmp->svt=creeNoeud();
        tmp=tmp->svt;
        tmp->lejeu=Mouvements(id,damier,pions,tmp->lejeu,v,-1,SIMPLE);
    }
    return ((noeud *)A);
}
