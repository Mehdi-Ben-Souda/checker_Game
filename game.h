#pragma once

#define NB_PIONS 24


typedef struct noeud
{
	mouvement* lejeu;//La suite du mouvement constituant un jeu
	int score;//Le score du jeu 
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
	NE->svt = NULL;
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
	, int IDj, int IDa)
{

	mouvement* NE = creer_mouvement(x, y, IDj, IDa);
	mouvement* ptr = NULL;
	if (!liste)

		return (mouvement*)NE;


	ptr = liste;

	while (ptr->svt)
		ptr = ptr->svt;

	ptr->svt = NE;

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
		//On sauvgarde les id des jettons
	int idJetonJoueur = lemvt.IDj;
	int idJetonAdversaire = lemvt.IDa;

		//On sauvgarde la position du jeton du joueur
	int x_init_joueur = lesjetons[idJetonJoueur].x;
	int y_init_joueur = lesjetons[idJetonJoueur].y;
		
		//On sauvgarde la position du jeton de l'adversaire
	int x_adversaire = lesjetons[idJetonAdversaire].x;
	int y_adversaire = lesjetons[idJetonAdversaire].y;


		//On enleve le jeton du joeur de sa position initiale
	Damier[y_init_joueur][x_init_joueur] = -1;
		//On le deplace vers la nouvelle position
	Damier[lemvt.y][lemvt.x] = idJetonJoueur;

		//On capture le jeton adverse
	Damier[y_adversaire][x_adversaire] = -1;

		//On reinitialise les donnee dans la table des jettons 
	lesjetons[idJetonAdversaire].etat = 0;
	lesjetons[idJetonJoueur].x = lemvt.x;
	lesjetons[idJetonJoueur].y = lemvt.y;

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
	case -2:
			//Si case non jouable
		return (etatCase)NONJOUABLE;
		break;

	case -1:
			//Si case vide
		return (etatCase)VIDE;
		break;

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
	else if(numeroJoueur==2)
	{
		if (0 <= idJeton && idJeton <= 11)
		
			return (typeJeton)ADVERSAIRE;
		else if(12 <= idJeton && idJeton <= 23)
			return (typeJeton)ALLIER;
	}

	printf("\n!!!!Erreur , paramatre invalid dans la fonction"
		"determiner_typeJeton!!!!\n");
}
/*____________________________________________________________*/


void MettreAjour_tab_pion(pion lespions[NB_PIONS], match lematch)
{
	int i, j, id;

	//On suppose que tous les pions sont capture
	for (i = 0; i < NB_PIONS; lespions[i++].etat = -1);


	/*On change l'etat de capture a pas encore capture
	* pour tous les pions que nous allons trouver encore sur
	* le damier
	*/
	for (i = 0; i < NB_CASES; i++)
	{
		for (j = 0; j < NB_CASES; j++)
		{
			//On recupere le pion qui est a la position acctuel
			id = lematch.damier[i][j];

			//Si un pion existe sur la position actuel
			if (id == 1 || id == 2)
			{
				//Alors on change sont etat
				lespions[id].etat = 1;
				//On change aussi sa position
				lespions[id].x = i;
				lespions[id].y = j;
			}
		}
	}

}

/*
	Nom Fonction : mouvementsPossibleSelonSens

	Entree : _entier x et y qui sont les coordonee de la case
			 _une matrice de type entier

	Sortie : _enumeration de type etatCase

	Description : permet de determiner le type de la case passe
			en parametre
*/
noeud* Mouvements_possible(int id,
		int damier[NB_CASES][NB_CASES], pion lespions[NB_PIONS])
{

	noeud* mouvements = NULL;
	int x = lespions[id].x;
	int y = lespions[id].y;
	int nature;
	int joueur;
	int sens_mouvement_vertical;

	mouvements = creeNoeud();

	//TODO verifier d'abord est ce que je peut chke7

	if (lespions[id].etat == 1)//Si c'est un pion
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
		if ( ( 0 < y && y < NB_CASES - 1) && x < NB_CASES - 1)
		{


			nature = damier[y + sens_mouvement_vertical][x + 1];


			if (nature == -1)//Case libre
			{
				mouvements->lejeu = insererListeMouvement(
						mouvements->lejeu, x + 1, 
						y + sens_mouvement_vertical, id, -1);
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
				
				if (x < NB_CASES - 2 
						&& ( 1 < y && y < NB_CASES - 2 ))
				{
					//Si la 2 eme case sur la diagonale est vide 
					if (determiner_etatCase(x + 2, 
						y + sens_mouvement_vertical*2, damier)
														== VIDE)
					{
						/*
						Alors on insere le mouvement dans la
						liste des mouvements et on fait un appel
						recursive pour voir si il y a un 
						enchainement d'autres mouvements
						*/

						/*On recupere l'id du pion adversaire que
							nous allons capturer
						*/
						int pionAdversaire = 
							damier[y + sens_mouvement_vertical]
													[x + 1];

						//On insere le mouvement
						mouvements->lejeu = 
							insererListeMouvement(
								mouvements->lejeu, x + 2, 
								y + sens_mouvement_vertical * 2,
								id, pionAdversaire);

						//On verifie si nous pouvons pas faire un autre mouvement

					}
				}

			}


		}
		/*if (x > 0 && y < 7)//Traitement du mouvement gauche
			sens_mouvement_horizontal = -1;*/


		



	}
	/*else if (lespions[id].etat == 2)//Si c'est une damme
	{

	}*/

	return (noeud*)mouvements;

}









