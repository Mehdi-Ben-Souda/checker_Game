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


noeud* tousLesmouvements(int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS],int joueur)
{
	noeud * lesmouvements=NULL,*ptr=NULL;
    int damierCPY[NB_CASES][NB_CASES];
    pion pionsCPY[NB_PIONS];

	int deb, fin,ind;

	if (joueur == 1)
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
            copierDamier(damierCPY, damier);
            copierLesJetons(pionsCPY, pions);

            ptr=lesmouvements;
            if (ptr!=NULL)
            {
                while (ptr->svt)
                    ptr = ptr->svt;

                ptr->svt = Mouvements_Possibles(ind, damierCPY, pionsCPY);
            }
            else
            {
                lesmouvements = Mouvements_Possibles(ind, damierCPY, pionsCPY);
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





