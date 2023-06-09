#define NB_PIONS 24
#define NB_CASES 8

typedef struct noeud
{
    mouvement* lejeu; // La suite du mouvement constituant un jeu
    int score;        // Le score du jeu
    int copy_damier[NB_CASES][NB_CASES];
    struct noeud* svt;      // pointeur sur les mouvements frere
    struct noeud* sous_jeu; // pointeur sur les mouvements derives
} noeud;

typedef enum typeMouv
{
    SIMPLE,
    COMPLEXE
} typeMouvement;

void Afficher_Arbre_horizotalement(mouvement* Arbre, int Niv)
{
    int esp;   // Pour l'affichage des espaces
    if (Arbre) // Condition d'arret
    {
        // Affichage des fils droits
        Afficher_Arbre_horizotalement(Arbre->fils2, Niv + 1);
        printf("\n");
        for (esp = 0; esp < Niv; esp++)
            printf("\t");
        printf("x :%d  y :%d ida :%d ", Arbre->x, Arbre->y, Arbre->IDa);
        // Affichage des fils gauches
        Afficher_Arbre_horizotalement(Arbre->fils1, Niv + 1);
    }
}
mouvement *creer_antiarboraissance(mouvement * Arbre)
{
    if (Arbre) // Condition d'arret
    {
        // Affichage des fils droits
        if(Arbre->fils2)    Arbre->fils2->pere=Arbre;
        if(Arbre->fils1)    Arbre->fils1->pere=Arbre;
        Arbre->fils1=creer_antiarboraissance(Arbre->fils1);
        Arbre->fils2=creer_antiarboraissance(Arbre->fils2);
    }
    return ((mouvement*)Arbre);
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
    NE->fils1 = NE->fils2 = NE->fils3 =NE->pere= NULL;
    return (mouvement*)NE;
}
noeud *inserer_debut_noeud(noeud *N,mouvement*M)
{
    mouvement *NE;
    noeud *NE2;
    NE2=creeNoeud();
    NE2->lejeu=M;
    if(!N)
        return ((noeud*)NE2);
    NE2->svt=N;
    return ((noeud*)NE2);
}
mouvement *inserer_debut_mvt(mouvement *M,mouvement *M2)
{
    mouvement *NE= creer_mouvement(M2->x,M2->y,M2->IDj,M2->IDa);
        NE->fils1=M;
    return ((mouvement*)NE);
}
noeud *inverser_lejeu(noeud *N)
{
    int i=0;
    if(!N)
        return NULL;
    if(!N->lejeu)
        return ((noeud*)N);
    mouvement *tmp;
    tmp=N->lejeu;
    N->lejeu=NULL;
    while (tmp)
    {

        N->lejeu= inserer_debut_mvt(N->lejeu,tmp);
        tmp=tmp->pere;
    }
    printf("\n");
    return ((noeud*)N);
}

noeud *creer_sous_liste(noeud *N,mouvement *M)
{
    if(M)
    {
        if(M->fils1)
            N= creer_sous_liste(N,M->fils1);
        if(M->fils2)
            N= creer_sous_liste(N,M->fils2);
        if(!M->fils2 && !M->fils1)
        {
            N= inserer_debut_noeud(N,M);
           // Afficher_Arbre_horizotalement(M,3);
        }

        return ((noeud*)N);
    }
    return ((noeud*)N);
}
noeud *creer_liste(noeud *N)
{
    int i=0 ;
    noeud *NE=NULL,*tmp;
    mouvement *tmp2;
    mouvement *tmp3;
    tmp=N;
    while (tmp)
    {
        tmp2=tmp->lejeu;
        while (tmp2)
        {
            tmp2= creer_antiarboraissance(tmp2);
            NE=creer_sous_liste(NE,tmp2);
            tmp2=tmp2->fils3;
        }
        tmp=tmp->svt;
    }
    tmp=NE;
    while (tmp)
    {
        tmp= inverser_lejeu(tmp);
        tmp=tmp->svt;
    }
    return ((noeud*)NE);
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

mouvement* insererListeMouvement(mouvement* liste, mouvement* NE)
{

    mouvement* ptr = NULL;
    if (!liste)
        return (mouvement*)NE;
    ptr = liste;
    while (ptr->fils3)
        ptr = ptr->fils3;
    ptr->fils3 = NE;
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
void MettreAjour_tab_pion(pion lespions[NB_PIONS], int Damier[NB_CASES][NB_CASES])
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
            // On recupere le pion qui est a la position acctuel
            id = Damier[i][j];
            // Si un pion existe sur la position actuel
            if (id >= 0)
            {
                // On change aussi sa position
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

void deplacerJeton(mouvement* lemvt,
                   int Damier[NB_CASES][NB_CASES], pion lesjetons[NB_PIONS])
{
    if (lemvt->IDa >= 0)
    {
        lesjetons[lemvt->IDa].etat = 0;
        // On sauvgarde la position du jeton de l'adversaire
        Damier[lesjetons[lemvt->IDa].y][lesjetons[lemvt->IDa].x] = -1;
        // On reinitialise les donnee dans la table des jettons
    }
    // On enleve le jeton du joeur de sa position initiale
    Damier[lesjetons[lemvt->IDj].y][lesjetons[lemvt->IDj].x] = -1;
    // On le deplace vers la nouvelle position
    Damier[lemvt->y][lemvt->x] = lemvt->IDj;
    // On reinitialise les donnee dans la table des jettons
    lesjetons[lemvt->IDj].x = lemvt->x;
    lesjetons[lemvt->IDj].y = lemvt->y;
    if (lemvt->IDj < 12)
    {
        if (lesjetons[lemvt->IDj].y == 7)
            lesjetons[lemvt->IDj].etat = 2;
    }
    else
    {
        if (lesjetons[lemvt->IDj].y == 0)
            lesjetons[lemvt->IDj].etat = 2;
    }
    MettreAjour_tab_pion(lesjetons, Damier);
}

/*
 * Fonction qui determine tous les mouvements possibles pour un pion ordinaire
 */
mouvement* Mouvements(int id, int damier[NB_CASES][NB_CASES],
                      pion pions[NB_PIONS], mouvement* N, int v,
                      int h, int typemvt)
{
    // déclaration des variables
    int damier1[NB_CASES][NB_CASES];
    pion pions1[NB_PIONS];
    int x = pions[id].x;
    int y = pions[id].y;
    if (x + h < 8 && y + v < 8 && x + h >= 0 && y + v >= 0) // s'il a une case libre pour boujer
    {
        if (damier[y + v][x + h] == -1 && typemvt == 0)
            // s'il va faire une mouvement sans capturer un pion adversaire
            N = creer_mouvement(x + h, y + v, id, -1);
        // s'il a un pion adversaire à coté
        else if ((damier[y + v][x + h] < 12 && damier[y][x] > 11) || (damier[y + v][x + h] > 11 && damier[y][x] < 12))
        {
            // s'il peut capurer cette pion de l'adversaire
            if (damier[y + (v * 2)][x + (h * 2)] == -1)
            {
                // on garde cette mouvement
                N = creer_mouvement(x + (h * 2), y + (v * 2), id, damier[y + v][x + h]);
                // on fait une copie du damier et on applique cette mouvement
                copierDamier(damier1, damier);
                copierLesJetons(pions1, pions);
                deplacerJeton(N, damier1, pions1);
                // on cherche les mouvements complexes à droite et à gauche
                N->fils1 = Mouvements(id, damier1, pions1, N->fils1, v, -1, COMPLEXE);
                N->fils2 = Mouvements(id, damier1, pions1, N->fils2, v, 1, COMPLEXE);
            }
        }
        else
            return ((mouvement*)NULL);
    }
    // retourner le noeud des mouvements
    return ((mouvement*)N);
}
/*
 * Fonction qui determine tous les mouvements possibles pour un pion dame
 */
mouvement* Dame(int id, int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS], mouvement* N, int v, int h, int typemvt)
{
    // déclaration des variabes
    int damier1[NB_CASES][NB_CASES];
    pion pions1[NB_PIONS];
    int a, b, c, d;
    int x = pions[id].x;
    int y = pions[id].y;
    mouvement *T, *T2;
    a = x + h;
    b = y + v;
    // tant qu'il y'a des cases dans le damier
    while (damier[b][a] == -1 && typemvt == SIMPLE)
    {
        if (a < 8 && b < 8 && a >= 0 && b >= 0) // si la case est libre
        {
            T = creer_mouvement(a, b, id, -1);
            N = insererListeMouvement(N, T);
            a = a + h;
            b = b + v;
        }
        else
            break;
    }
    while (damier[b][a] == -1 && typemvt == COMPLEXE)
    {
        if (a < 8 && b < 8 && a >= 0 && b >= 0)
        {
            a = a + h;
            b = b + v;
        }
    }
    if ((damier[b][a] < 12 && damier[b][a] >= 0 && damier[y][x] > 11) || (damier[b][a] > 11 && damier[y][x] < 12 && damier[y][x] >= 0))
    {
        c = a;
        d = b;
        c = c + h;
        d = d + v;
        while (damier[d][c] == -1)
        {
            if (c < 8 && d < 8 && c >= 0 && d >= 0)
            {
                typemvt = COMPLEXE;
                T = creer_mouvement(c, d, id, damier[b][a]);
                T2 = creer_mouvement(c, d, id, damier[b][a]);
                copierDamier(damier1, damier);
                copierLesJetons(pions1, pions);
                deplacerJeton(T, damier1, pions1);
                T2->fils1 = Dame(id, damier1, pions1, T2->fils1, v * (-1), h, COMPLEXE);
                T->fils1 = Dame(id, damier1, pions1, T->fils1, v, 1, COMPLEXE);
                T->fils2 = Dame(id, damier1, pions1, T->fils2, v, -1, COMPLEXE);
                if (T2->fils1)
                {
                    //T2->fils1->pere=T2;
                    N = insererListeMouvement(N, T2);
                    if(T->fils1 || T->fils2)
                        N = insererListeMouvement(N, T);
                }
                else
                    N = insererListeMouvement(N, T);
                /*if (T->fils1)
                    T->fils1->pere=T;
                if (T->fils2)
                    T->fils2->pere=T;*/
                c = c + h;
                d = d + v;
            }
            else
                break;
        }
    }
    return ((mouvement*)N);
}
/*
 * Fonction qui determine tous les mouvements possibles pour un pion quelconque
 */
noeud* Mouvements_Possibles(int id, int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS])
{
    int v;
    noeud* A = creeNoeud();
    noeud* tmp;
    tmp = A;
    if (pions[id].etat == 2) // s'il s'agit d'un dame
    {
        // on cherche les mouvements possibles dans les 4 directions
        tmp->lejeu = Dame(id, damier, pions, tmp->lejeu, 1, -1, SIMPLE); // sense verticale = 1 et sens horizontale =-1
        if(tmp->lejeu)
        {
            tmp->svt = creeNoeud();
            tmp = tmp->svt;
        }
        tmp->lejeu = Dame(id, damier, pions, tmp->lejeu, 1, 1, SIMPLE); // sense verticale = 1 et sens horizontale =1
        if(tmp->lejeu)
        {
            tmp->svt = creeNoeud();
            tmp = tmp->svt;
        }
        tmp->lejeu = Dame(id, damier, pions, tmp->lejeu, -1, -1, SIMPLE); // sense verticale = -1 et sens horizontale =-1
        if(tmp->lejeu)
        {
            tmp->svt = creeNoeud();
            tmp = tmp->svt;
        }
        tmp->lejeu = Dame(id, damier, pions, tmp->lejeu, -1, 1, SIMPLE); // sense verticale = -1 et sens horizontale =1
        if(!tmp->lejeu)
            tmp=NULL;
    }
    else // sinon
    {
        // on determine le sens vertical du joueur
        if (id < 12)
            v = 1;
        else
            v = -1;
        // v :sens vertical pour un joueur, sens horizontale =1
        tmp->lejeu = Mouvements(id, damier, pions, tmp->lejeu, v, 1, SIMPLE);
        // v :sense vertical pour un joueur, sens horizontale =-1
        if(tmp->lejeu)
        {
            tmp->svt = creeNoeud();
            tmp = tmp->svt;
        }
        tmp->lejeu = Mouvements(id, damier, pions, tmp->lejeu, v, -1, SIMPLE);
        if(!tmp->lejeu)
            tmp=NULL;
    }
    if(!A->lejeu)
    {
        free(A);
        A=NULL;
    }
    return ((noeud*)A);
}
/*

mouvement *nfikh(int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS])
{
    int i;
    if()

}
*/