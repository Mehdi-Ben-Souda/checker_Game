#pragma once

//typedef struct souslst
//{
//    int x;
//    int y;
//    int IDj;
//    int IDa;
//    struct souslst* svt;
//}sousListeMouvement;
//
//typedef struct lst
//{
//    sousListeMouvement* lejeu;
//
//    struct lst* svt;
//}listeMouvement;
//
///*
//    Nom Fonction : creer_sousListeMouvement
//
//    Entree : _entiers x et y qui sont les coordonee
//             _entiers IDj et IDa qui sont les id des jetons
//
//    Sortie : _element de type sousListeMouvement
//
//    Description : Cree et retourne un element de type sousListeMouvement
//*/
//
//sousListeMouvement* creer_sousListeMouvement(int x, int y, int IDj, int IDa)
//{
//    sousListeMouvement* NE = malloc(sizeof(sousListeMouvement));
//
//    if (!NE)
//    {
//        printf("\n\t\t__________Erreur d'allocation de la "
//               "structure sousListeMouvement__________\n\n");
//        return (sousListeMouvement*)NE;
//    }
//
//    NE->x = x;
//    NE->y = y;
//    NE->IDj = IDj;
//    NE->IDa = IDa;
//    NE->svt = NULL;
//    return (sousListeMouvement*)NE;
//}
//
//
///*
//    Nom Fonction : creer_sousListeMouvement
//
//    Entree : _entiers x et y qui sont les coordonee
//             _entiers IDj et IDa qui sont les id des jetons
//
//    Sortie : _element de type sousListeMouvement
//
//    Description : Cree et retourne un element de type sousListeMouvement
//*/
//
//listeMouvement* creer_sousListeMouvement(void)
//{
//    listeMouvement* NE = (listeMouvement*)malloc(sizeof(listeMouvement));
//
//    if (!NE)
//    {
//        printf("\n\t\t__________Erreur d'allocation de la "
//               "structure ListeMouvement__________\n\n");
//        return (listeMouvement*)NE;
//    }
//
//    
//    NE->svt = NE->lejeu= NULL;
//    return (listeMouvement*)NE;
//}
//
//
//
//listeMouvement* transfert_mouvement_TO_listeMouvement(mouvement* arb, listeMouvement*liste )
//{
//    sousListeMouvement* NE = creer_sousListeMouvement(arb->x, arb->y, arb->IDj, arb->IDa);
//    //Si il s'agit d'une feuille
//    if (!arb->fils1 && !arb->fils2 && !arb->fils3)
//    {
//
//    }
//
//
//
//}

typedef enum maxmin
{
    MAXIMUM,
    MINIMUM
} maxmin;

noeud* tousLesmouvements(int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS],int joueur)
{
	noeud * lesmouvements=NULL,*ptr=NULL;
    /*int damierCPY[NB_CASES][NB_CASES];
    pion pionsCPY[NB_PIONS];*/

	int deb, fin,ind;

	if (joueur == 2)
	{
        deb = 0;
        fin = 11;
	}
    else
    {
        deb = 12;
        fin = 23;
    }

    for (ind = deb; ind <= fin; ind++)
    {
        if (pions[ind].etat != 0)
        {
            /* copierDamier(damierCPY, damier);
            copierLesJetons(pionsCPY, pions);*/

            ptr=lesmouvements;
            if (ptr!=NULL)
            {
                while (ptr->svt)
                    ptr = ptr->svt;

                ptr->svt = Mouvements_Possibles(ind, damier, pions);
            }
            else
            {
                lesmouvements = Mouvements_Possibles(ind, damier, pions);
            }
            

        }
    }

    return (noeud*)lesmouvements;
	

}




noeud* listeDesMouvements(int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS], int joueur)
{
    noeud* ptr1=NULL,*resultat=NULL;
    ptr1=tousLesmouvements(damier, pions, joueur);

    if (ptr1)
       resultat=creer_liste(ptr1);

    return (noeud*)resultat;

}

void setCoutNoeud(noeud* nd)
{
    int nb1=0, nb2=0,i;
    if (nd)
    {
        for (i = 0; i < 12; i++)
            if (nd->copy_pions[i].etat != 0)
                nb1++;
        for (i = 12; i < 24; i++)
            if (nd->copy_pions[i].etat != 0)
                nb2++;
        
        nd->score = nb1 - nb2;
        printf("le cout %d\n",nd->score);
    }
}

int selectioner_cout(noeud* N, maxmin E,noeud * racine)
{
    int Val;
    noeud* ptc;

    if (N)
    {
        ptc = N;
        ptc = ptc->svt;
        Val = N->score;

        if (racine!=NULL)
            racine->lejeu = N->lejeu;

        if (E == MINIMUM)
        {
            while (ptc)
            {
                if (ptc->score < Val)
                {
                    Val = ptc->score;
                    if (racine != NULL)
                    {
                        racine->lejeu = ptc->lejeu;
                    }
                }
                else if (ptc->score == Val && rand() % 2 == 0)
                {
                    Val = ptc->score;
                    if (racine != NULL)
                    {
                        racine->lejeu = ptc->lejeu;
                    }
                }
                
                ptc = ptc->svt;
            }
        }
        else
        {
            while (ptc)
            {

                if (ptc->score > Val)
                {
                    Val = ptc->score;
                    if (racine != NULL)
                    {
                        racine->lejeu = ptc->lejeu;
                    }
                }
                else if (ptc->score == Val && rand() % 2 == 0)
                {
                    Val = ptc->score;
                    if (racine != NULL)
                    {
                        racine->lejeu = ptc->lejeu;
                    }
                }

                
                ptc = ptc->svt;
            }
        }
        return ((int)Val);
    }

    return (int)-32000;
}


noeud* creerArbre_MiniMax(int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS], int joueur)
{

    noeud* nd = creeNoeud(),*tmp=NULL,*tmp2=NULL;
   
    mouvement * ptr;

    nd->sous_jeu = listeDesMouvements(damier,pions,joueur);

    tmp = nd->sous_jeu;

    while (tmp)
    {
       copierDamier(tmp->copy_damier, damier);
       copierLesJetons(tmp->copy_pions, pions);

       ptr = tmp->lejeu;


       while (ptr)
       {
            deplacerJeton(ptr,tmp->copy_damier,tmp->copy_pions);
            ptr = ptr->fils1;
       }

       //setCoutNoeud(tmp);//On applique un score 

       tmp->sous_jeu = listeDesMouvements(tmp->copy_damier, tmp->copy_pions,(-1 * joueur));


       //On veut calculer les score pouer ce sous jeu
       tmp2 = tmp->sous_jeu;
       while (tmp2)
       {
            copierDamier(tmp2->copy_damier, tmp->copy_damier);
            copierLesJetons(tmp2->copy_pions,tmp->copy_pions);

            ptr = tmp2->lejeu;
            while (ptr)
            {
                deplacerJeton(ptr, tmp2->copy_damier, tmp2->copy_pions);
                ptr = ptr->fils1;
            }
            
            calculer_cout(tmp2);
            
            
           tmp2 = tmp2->svt;
       }
       tmp->score = selectioner_cout(tmp->sous_jeu, MINIMUM,NULL);


       tmp = tmp->svt;
    }

    selectioner_cout(nd->sous_jeu, MAXIMUM,nd);

    
    return (noeud*)nd;

}




void affciherArbre_MiniMax(noeud * arb)
{
    mouvement* ptc=NULL;
    if (arb)
    {
        noeud* tmp = arb;
        printf("\n\n-\n\n");
        while (tmp)
        {
            ptc = tmp->lejeu;
            /*while (ptc)
            {
                printf("x :%d\t", ptc->x);
                ptc = ptc->fils1;
            }*/
            printf("x :%d  y :%d idj :%d cout: %d\n", tmp->lejeu->x, tmp->lejeu->y, tmp->lejeu->IDj, tmp->score);
            affciherArbre_MiniMax(tmp->sous_jeu);

            tmp = tmp->svt;

        }
    }

}














