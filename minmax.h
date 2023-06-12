#pragma once

    //Enumeration servant a dire si on veut le maximum
        //ou le minimum
typedef enum maxmin
{
    MAXIMUM,
    MINIMUM
} maxmin;//nom de l'enumeration


/*
    Nom Fonction : tousLesmouvements

    Entree : _matrice d'entiers
             _table des pions
             _entier

    Sortie : _pointeur de type noeud

    Description : la fonction retourne tous les mouvements 
        de tous les jettons d'un joueur donnée
*/

noeud* tousLesmouvements(int damier[NB_CASES][NB_CASES],
        pion pions[NB_PIONS], int joueur)
{
    noeud *lesmouvements = NULL, *ptr = NULL;
    

    int deb, fin, ind;

        //determiner les pions sur les quels je vais tester
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

        //Je boucle sur tous les jettons du joeurs
    for (ind = deb; ind <= fin; ind++)
    {
            //Si le pion n'est pas capture (exsiste encore sur le dammier)
        if (pions[ind].etat != 0)
        {

            ptr = lesmouvements;
            if (ptr != NULL)
            {
                    //je parcourt tous lesmouvements jusqu'a arriver
                        //au dernier
                while (ptr->svt)
                    ptr = ptr->svt;
                    //J'insere les mouvements retourner pour ce jettons
                        //a la fin de la liste
                ptr->svt = Mouvements_Possibles(ind, damier, pions);
            }
            else
            {
                    //Si la liste des mouvements est initialement vide
                        //J'insere les mouvements au debut
                lesmouvements = Mouvements_Possibles(ind, damier, pions);
            }
        }
    }

    return (noeud*)lesmouvements;
}

/*____________________________________________________________*/




/*
    Nom Fonction : listeDesMouvements

    Entree : _matrice d'entiers
             _table des pions
             _entier

    Sortie : _pointeur de type noeud

    Description : la fonction appel a tousLesmouvements qui elle retorune 
        une liste de type noeud et qui chaque un contient un arbre de 
        mouvement puis qui les convertis en une liste simple de type noeud
*/
noeud* listeDesMouvements(int damier[NB_CASES][NB_CASES],
            pion pions[NB_PIONS], int joueur)
{
    noeud *ptr1 = NULL, *resultat = NULL;

        //On apple la focntion qui retourne listes d'arbres
    ptr1 = tousLesmouvements(damier, pions, joueur);

    if (ptr1)
            //on converti cette liste d'arbres en une liste de liste de mouvement
        resultat = creer_liste(ptr1);

    return (noeud*)resultat;
}

/*____________________________________________________________*/



/*
    Nom Fonction : selectioner_cout

    Entree : _deux pointeurs de type noeud
             _Enumeration qui nous dis si on veut le minimum ou le 
                maximum 

    Sortie : RIEN

    Description : parcourt la liste de type noeud et retourne 
        le minimum (resp. le maximum) 
*/
int selectioner_cout(noeud* N, maxmin E, noeud* racine)
{
    int Val;
    noeud* ptc;

    if (N)
    {
            //On selectionne le premier element comme minimum (resp. maximum)
        ptc = N;
        ptc = ptc->svt;
        Val = N->score;

        if (racine != NULL)
            racine->lejeu = N->lejeu;
            //Si il s'agit de cas de recherche de minimum
        if (E == MINIMUM)
        {
                //Je parcourt la liste des mouvements
            while (ptc)
            {
                    //Si l'elemnent actuel est plus petit ,alors on change
                        //le minimum
                if (ptc->score < Val)
                {
                    Val = ptc->score;
                    if (racine != NULL)
                    {
                        racine->lejeu = ptc->lejeu;
                    }
                }

                    //Si les elements ont le meme cout , alors on choisi
                        //l'un des deux aleatoirement
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
                // Si l'elemnent actuel est plus grand ,alors on change
                // le maximum
                if (ptc->score > Val)
                {
                    Val = ptc->score;
                    if (racine != NULL)
                    {
                        racine->lejeu = ptc->lejeu;
                    }
                }
                // Si les elements ont le meme cout , alors on choisi
                // l'un des deux aleatoirement
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
        //Dans le cas ou le noued est vide
    return (int)-32000;
}


/*____________________________________________________________*/


/*
    Nom Fonction : creerArbre_MiniMax

    Entree : _matrice d'entiers
             _table des pions
             _entier

    Sortie : Arbre de decision (minmax) 

    Description : la fonction cree et calcul le mouvement le plus
        optimale
*/
noeud* creerArbre_MiniMax(int damier[NB_CASES][NB_CASES],
        pion pions[NB_PIONS], int joueur)
{
        //On cree le noeud racine
    noeud *nd = creeNoeud(), *tmp = NULL, *tmp2 = NULL, *tmp3=NULL,*tmp4=NULL;

    mouvement* ptr;
        //on cree le premier niveau
    nd->sous_jeu = listeDesMouvements(damier, pions, joueur);

    tmp = nd->sous_jeu;

    while (tmp)
    {
            //tant que j'ai des element dans le premier niveau
        copierDamier(tmp->copy_damier, damier);
        copierLesJetons(tmp->copy_pions, pions);

        ptr = tmp->lejeu;
            //J'applique l'entierté du mouvement
        while (ptr)
        {
            deplacerJeton(ptr, tmp->copy_damier, tmp->copy_pions);
            ptr = ptr->fils1;
        }

            //puis je lui attribut les sous jeu correspondants
        tmp->sous_jeu = listeDesMouvements(tmp->copy_damier, 
                tmp->copy_pions, (-1 * joueur)+3);

            // On veut calculer les score pouer ce sous jeu
        tmp2 = tmp->sous_jeu;
            //pour chaque sous jeu
        while (tmp2)
        {

            copierDamier(tmp2->copy_damier, tmp->copy_damier);
            copierLesJetons(tmp2->copy_pions, tmp->copy_pions);
                //j'applique l'entierté du sous jeu
            ptr = tmp2->lejeu;
            while (ptr)
            {
                deplacerJeton(ptr, tmp2->copy_damier, tmp2->copy_pions);
                ptr = ptr->fils1;
            }
                //puis je lui attribut les sous jeu correspondants
            tmp2->sous_jeu = listeDesMouvements(tmp2->copy_damier, 
                    tmp2->copy_pions, joueur);
                // On veut calculer les score pouer ce sous jeu
            tmp3 = tmp2->sous_jeu;
            while (tmp3)
            {
                copierDamier(tmp3->copy_damier, tmp2->copy_damier);
                copierLesJetons(tmp3->copy_pions, tmp2->copy_pions);

                ptr = tmp3->lejeu;
                while (ptr)
                {
                    deplacerJeton(ptr, tmp3->copy_damier, tmp3->copy_pions);
                    ptr = ptr->fils1;
                }

                tmp3->sous_jeu = listeDesMouvements(tmp3->copy_damier,
                        tmp3->copy_pions,  (-1 * joueur)+3);
                tmp4=tmp3->sous_jeu;
                while (tmp4)
                {
                    copierDamier(tmp4->copy_damier, tmp3->copy_damier);
                    copierLesJetons(tmp4->copy_pions, tmp3->copy_pions);

                    ptr=tmp4->lejeu;
                    while (ptr)
                    {
                        deplacerJeton(ptr, tmp4->copy_damier, tmp4->copy_pions);
                        ptr = ptr->fils1;
                    }

                    calculer_cout(tmp4);
                    tmp4=tmp4->svt;
                }

                tmp3->score = selectioner_cout(tmp3->sous_jeu, MAXIMUM, NULL);

                tmp3 = tmp3->svt;

            }
            tmp2->score = selectioner_cout(tmp2->sous_jeu, MINIMUM, NULL);

                //puis je lui calcul le cout correspondant
            
            tmp2 = tmp2->svt;
        }
        tmp->score = selectioner_cout(tmp->sous_jeu, MAXIMUM, NULL);

        tmp = tmp->svt;
    }

    selectioner_cout(nd->sous_jeu, MINIMUM, nd);

    return (noeud*)nd;
}

void affciherArbre_MiniMax(noeud* arb)
{
    mouvement* ptc = NULL;
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
