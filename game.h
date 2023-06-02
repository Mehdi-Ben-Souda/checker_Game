#pragma once

#define NB_PIONS 24
#define NB_CASES 8

typedef enum maxmin
{
	MAXIMUM,
	MINIMUM
};

typedef struct noeud
{
	mouvement* lejeu;//La suite du mouvement constituant un jeu
	int score;//Le score du jeu 
	int copy_damier[NB_CASES][NB_CASES];
	struct noeud* svt;//pointeur sur les mouvements frere
	struct noeud* sous_jeu;//pointeur sur les mouvements derives
}noeud;

typedef enum etCase
{
	NONJOUABLE,
	VIDE,
	JETON1,
	JETON2
}etatCase;

typedef enum typeJet
{
	ADVERSAIRE,
	ALLIER
}typeJeton;

typedef enum typeMouv
{
	SIMPLE,
	COMPLEXE
}typeMouvement;



/*
	Nom Fonction : creer_mouvement

	Entree : _entiers x et y qui sont les coordonee
			 _entiers IDj et IDa qui sont les id des jetons

	Sortie : _element de type mouvement

	Description : Cree et retourne un element de type mouvement
*/

mouvement* creer_mouvement(int x, int y, int IDj, int IDa)
{
	mouvement* NE = malloc(sizeof(mouvement));

	if (!NE)
	{
		printf("\n\t\t__________Erreur d'allocation de la "
			"structure mouvement__________\n\n");
		return (mouvement*)NE;
	}

	NE->x = x;
	NE->y = y;
	NE->IDj = IDj;
	NE->IDa = IDa;
	NE->gch=NE->drt = NULL;
	return (mouvement*)NE;

}
/*____________________________________________________________*/

/*
	Nom Fonction : insererListeMouvement

	Entree : _la liste de mouvements
			 _entiers x et y qui sont les coordonees
			 _entiers IDj et IDa qui sont les id des jetons

	Sortie : _element de type mouvement

	Description : Cree un element de type mouvement et l'ajoute
			a la fin de la liste passee en parametre
*/

mouvement* insererListeMouvement(mouvement* liste, int x, int y
	, int IDj, int IDa,int dir)
{

	mouvement* NE = creer_mouvement(x, y, IDj, IDa);
	mouvement* ptr = NULL;
	if (!liste)

		return (mouvement*)NE;


	ptr = liste;
    if(dir ==1) {
        while (ptr->drt)
            ptr = ptr->drt;
        ptr->drt = NE;
    }
    else

	return (mouvement*)liste;

}

/*____________________________________________________________*/



/*
	Nom Fonction : copierDamier

	Entree : _Deux marices de type entiers

	Sortie : _Rien

	Description : Copie une matrice d'entier dans un autre
*/
void copierDamier(int DamierDst[NB_CASES][NB_CASES],
	int DamierSrc[NB_CASES][NB_CASES])
{
	for (int i = 0; i < NB_CASES; i++)
		for (int j = 0; j < NB_CASES; j++)
			DamierDst[i][j] = DamierSrc[i][j];

}
/*____________________________________________________________*/


/*
	Nom Fonction : copierLesJetons

	Entree : _Deux marices de type pion

	Sortie : _Rien

	Description : Copie une matrice de pion dans un autre
*/
void copierLesJetons(pion tabDst[NB_PIONS],
	pion tabSrc[NB_CASES])
{
	for (int i = 0; i < NB_PIONS; i++)
	{
		tabDst[i].etat = tabSrc[i].etat;
		tabDst[i].x = tabSrc[i].x;
		tabDst[i].y = tabSrc[i].y;
	}

}
/*____________________________________________________________*/


/*
	Nom Fonction : MettreAjour_tab_pion

	Entree : _tableau de pions
			 _variable de type match

	Sortie : _rien

	Description : regarde le jeu qui est dans la
*/
void MettreAjour_tab_pion(pion lespions[NB_PIONS],int Damier[NB_CASES][NB_CASES])
{
    int i, j, id;
    /*On change l'etat de capture a pas encore capture
    * pour tous les pions que nous allons trouver encore sur
    * le damier
    */
    for (i = 0; i < NB_CASES; i++)
    {
        for (j = 0; j < NB_CASES; j++)
        {
            //On recupere le pion qui est a la position acctuel
            id = Damier[i][j];
            //Si un pion existe sur la position actuel
            if (id >= 0)
            {
                //On change aussi sa position
                lespions[id].x = j;
                lespions[id].y = i;
            }
        }
    }

}

/*____________________________________________________________*/

/*
	Nom Fonction : deplacerJeton

	Entree : _un mouvement de type mouvement
			 _une matrice de type entier
			 _

	Sortie : _Rien

	Description : L'utilite de cette fct c'est qu'elle applique
			un mouvement sur le damier en mettant a jour la
			table des jetons
*/

void deplacerJeton(mouvement lemvt,
	int Damier[NB_CASES][NB_CASES], pion lesjetons[NB_PIONS])
{
	if (lemvt.IDa >= 0)
	{
        lesjetons[lemvt.IDa].etat = 0;
		//On sauvgarde la position du jeton de l'adversaire
		Damier[lesjetons[lemvt.IDa].y][lesjetons[lemvt.IDa].x] = -1;
		//On reinitialise les donnee dans la table des jettons

	}
	//On enleve le jeton du joeur de sa position initiale
	Damier[lesjetons[lemvt.IDj].y][lesjetons[lemvt.IDj].x] = -1;
	//On le deplace vers la nouvelle position
	Damier[lemvt.y][lemvt.x] = lemvt.IDj;
	//On reinitialise les donnee dans la table des jettons 
	lesjetons[lemvt.IDj].x = lemvt.x;
	lesjetons[lemvt.IDj].y = lemvt.y;
    if(lemvt.IDj < 12)
    {
        if(lesjetons[lemvt.IDj].y == 7)
            lesjetons[lemvt.IDj].etat=2;
    }
    else
    {
        if(lesjetons[lemvt.IDj].y==0)
            lesjetons[lemvt.IDj].etat=2;
    }
    MettreAjour_tab_pion(lesjetons, Damier);
}
/*____________________________________________________________*/




/*
	Nom Fonction : creeNoeud

	Entree : _rien

	Sortie : _element de type noeud

	Description : cree un element de type noeud et le retourne
*/
noeud* creeNoeud(void)
{
	noeud* NE = (noeud*)malloc(sizeof(noeud));
	if (!NE)
	{
		printf("\n\t\t__________Erreur d'allocation de la "
			"structure noeud__________\n\n");
		return (noeud*)NE;
	}

	NE->lejeu = NULL;
	NE->score = 0;
	NE->svt = NE->sous_jeu = NULL;

	return (noeud*)NE;
}

/*____________________________________________________________*/



/*
	Nom Fonction : determiner_etatCase

	Entree : _entier x et y qui sont les coordonee de la case
			 _une matrice de type entier

	Sortie : _enumeration de type etatCase

	Description : permet de determiner le type de la case passe
			en parametre
*/
etatCase determiner_etatCase(int x, int y,
	int damier[NB_CASES][NB_CASES])
{
	switch (damier[y][x])
	{
	case -2:    return (etatCase)NONJOUABLE;//Si case non jouable
	case -1:    return (etatCase)VIDE;
	default:
		//Si il d'agit d'un jeton du joueur 1
		if (0 <= damier[y][x] && damier[y][x] <= 11)
            return (etatCase)JETON1;
		//Si il d'agit d'un jeton du joueur 2
		else if (12 <= damier[y][x] && damier[y][x] <= 23)
			return (etatCase)JETON2;

		printf("\nErreur: La case a determiner contient "
			"une valeur inconnu");
		break;
	}
}

/*____________________________________________________________*/


/*
	Nom Fonction : determiner_typeJeton

	Entree : _l'id du jeton
			 _une matrice de type entier

	Sortie : _enumeration de type etatCase

	Description : permet de determiner le type de la case passe
			en parametre
*/
typeJeton determiner_typeJeton(int idJeton, int numeroJoueur)
{
	if (numeroJoueur == 1)
	{
		if (0 <= idJeton && idJeton <= 11)
			return (typeJeton)ALLIER;
		else if (12 <= idJeton && idJeton <= 23)
			return (typeJeton)ADVERSAIRE;
	}
	else if (numeroJoueur == 2)
	{
		if (0 <= idJeton && idJeton <= 11)

			return (typeJeton)ADVERSAIRE;
		else if (12 <= idJeton && idJeton <= 23)
			return (typeJeton)ALLIER;
	}

	printf("\n!!!!Erreur , paramatre invalid dans la fonction"
		"determiner_typeJeton!!!! Joueur%d IDJett%d\n", numeroJoueur, idJeton);
}

/*
	Nom Fonction : Mouvements_possible

	Entree : _entier qui est l'id au quel nous devons determiner
				les mouvements
			 _une matrice de type entier
			 _un tableau de jetton

	Sortie : _la liste des mouvements possibles

	Description : la fonction permet de determiner tous
					les mouvements possible pour un jeton

*/
mouvement* Mouvements_possible(int id,
	int damier[NB_CASES][NB_CASES], pion lesJetons[NB_PIONS], mouvement* mouvements, int sens_mouvement_horizontal, typeMouvement typeMvt)
{

	int x = lesJetons[id].x;
	int y = lesJetons[id].y;
	int nature;
	int joueur;
	int sens_mouvement_vertical;



	if (lesJetons[id].etat == 1)//Si c'est un pion
	{
		if (id < 12)
		{
			//On va faire un mouvement vers le bas
			sens_mouvement_vertical = 1;
			joueur = 1;
		}
		else
		{
			//On va faire un mouvement vers le haut
			sens_mouvement_vertical = -1;
			joueur = 2;
		}




		//Traitement du mouvement droit

			/*
				Nous testons si la case sur la diagonale
				droite existe
			*/
		if ((0 <= (y + sens_mouvement_vertical) && (y + sens_mouvement_vertical) < NB_CASES)
			&& (0 <= (x + sens_mouvement_horizontal) && (x + sens_mouvement_horizontal) < NB_CASES))//A revoir
		{


			nature = damier[y + sens_mouvement_vertical][x + sens_mouvement_horizontal];

			/*
			* Case libre et que nous n'avaons pas fait un mouvement
			* avant
			*/
			if (nature == -1 && typeMvt == SIMPLE)
			{

			
				mouvements = creer_mouvement(x + sens_mouvement_horizontal,
					y + sens_mouvement_vertical, id, -1);
					
					/*insererListeMouvement(
					mouvements->lejeu, x + sens_mouvement_horizontal,
					y + sens_mouvement_vertical, id, -1);*/
			}

			/*Si la case contient un jetton Allier
			* Alors nous sommes blocke
			*/

			/*Si la case contient un jetton Adversaire
			* Alors nous pouvons le bouffer
			* a condition que la case d'apres ce jetton
			* sois vide
			*/
			else if (determiner_typeJeton(nature, joueur)
				== ADVERSAIRE)
			{

				/*
				* Il faut voir la case qui est juste apres
				* sur la diagonale si elle est vide ou pas
				*
				*	SI elle est vide il faut voir si il
				*	y a pas une autre serie de mouvements
				*	a faire dans les quels je mange
				*/


				/*Si la deuxieme case sur la diagonale
				*	droite existe
				*/

				if (0 <= (x + sens_mouvement_horizontal * 2) && (x + sens_mouvement_horizontal * 2) < NB_CASES
					&& 0 <= (y + sens_mouvement_vertical * 2) && (y + sens_mouvement_vertical * 2) < NB_CASES)
				{

					//Si la 2 eme case sur la diagonale est vide 
					if (determiner_etatCase(x + sens_mouvement_horizontal * 2,
						y + sens_mouvement_vertical * 2, damier)
						== VIDE)
					{

						/*
						Alors on insere le mouvement dans la
						liste des mouvements et on fait un appel
						recursive pour voir si il y a un
						enchainement d'autres mouvements
						*/

						/*	On recupere l'id du pion adversaire que
							nous allons capturer
						*/
						int pionAdversaire =
							damier[y + sens_mouvement_vertical]
							[x + sens_mouvement_horizontal];

						//On insere le mouvement
						if(!mouvements)
								mouvements = creer_mouvement(x + sens_mouvement_horizontal * 2,
									y + sens_mouvement_vertical * 2,
									id, pionAdversaire);
						/*mouvements->lejeu =
							insererListeMouvement(
								mouvements->lejeu, x + sens_mouvement_horizontal * 2,
								y + sens_mouvement_vertical * 2,
								id, pionAdversaire);*/

						/*
						On verifie si nous pouvons pas faire un autre mouvement
						*/

						int copy_damier[NB_CASES][NB_CASES], copy_damier2[NB_CASES][NB_CASES];
						pion copy_lesjetons[NB_PIONS], copy_lesjetons2[NB_PIONS];
						copierLesJetons(copy_lesjetons, lesJetons);
						copierDamier(copy_damier, damier);

						copierLesJetons(copy_lesjetons2, lesJetons);
						copierDamier(copy_damier2, damier);

						mouvement* tmp = creer_mouvement(x + sens_mouvement_horizontal * 2,
							y + sens_mouvement_vertical * 2,
							id, pionAdversaire);

						deplacerJeton(*tmp, copy_damier, copy_lesjetons);
						deplacerJeton(*tmp, copy_damier2, copy_lesjetons2);

						mouvements->drt = Mouvements_possible(id, copy_damier, copy_lesjetons, mouvements->drt, 1, COMPLEXE);
						mouvements->gch = Mouvements_possible(id, copy_damier, copy_lesjetons, mouvements->gch, -1, COMPLEXE);
						/*noeud* mouvementgauche = creeNoeud(), * mouvementdroit = creeNoeud(),*ptrnoeud=NULL, * ptrnoeud2 = NULL;
						mouvement* ptrmvt1 = NULL;
						
						ptrmvt1 = mouvements->lejeu;
						while (ptrmvt1)
						{
							mouvementgauche->lejeu = insererListeMouvement(mouvementgauche->lejeu, ptrmvt1->x,
															ptrmvt1->y, ptrmvt1->IDj, ptrmvt1->IDa);
						

							ptrmvt1 = ptrmvt1->gch;
							
						}*/

						

						
						//mouvements = Mouvements_possible(id, copy_damier2, copy_lesjetons2, mouvements,-1,COMPLEXE);
						
						/*mouvementgauche = Mouvements_possible(id, copy_damier2, copy_lesjetons2, mouvementgauche, -1, COMPLEXE);
						ptrnoeud = mouvements;
						while (ptrnoeud->svt)
							ptrnoeud = ptrnoeud->svt;
						if(mouvementgauche->lejeu)  ptrnoeud->svt = mouvementgauche;*/
					}
				}

			}
			else
				return (mouvement*)NULL;


		}


	}


	return (mouvement*)mouvements;

}



noeud* tousLesMouvementsJetton(int id,
	int damier[NB_CASES][NB_CASES], pion lesJetons[NB_PIONS], typeMouvement typeMvt)
{
	int copy_damier[NB_CASES][NB_CASES], copy_damier2[NB_CASES][NB_CASES];
	pion copy_lesjetons[NB_PIONS], copy_lesjetons2[NB_PIONS];
	copierLesJetons(copy_lesjetons, lesJetons);
	copierDamier(copy_damier, damier);

	copierLesJetons(copy_lesjetons2, lesJetons);
	copierDamier(copy_damier2, damier);

	noeud* tmp = creeNoeud();


	tmp->lejeu = Mouvements_possible(id, copy_damier, copy_lesjetons, tmp->lejeu, 1, typeMvt);

	tmp->svt = creeNoeud();

	tmp->svt->lejeu = Mouvements_possible(id, copy_damier2, copy_lesjetons2, tmp->svt->lejeu, -1, typeMvt);


	return (noeud*)tmp;


}
