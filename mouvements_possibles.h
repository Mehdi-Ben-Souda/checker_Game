
#define NB_PIONS 24
#define NB_CASES 8
typedef struct {
    int etat; //etat di pion . 0:capturé ,1:pion normal,2:pion dame
    int x;//coordoné horizontal
    int y;//coordoné vertical
}pion; //structure d'un pion
typedef struct {
    int damier[8][8];//la table du jeu
    int nbrpionJoueur; //nombre des pion joueur présent
    int nbrpionAdversaire;//nombre des pion adversaire présent
    int scoreJoueur;//score joueur
    int scoreMachine;//score machine
}match;//structure d'un match
typedef struct mvt
{
    int x; //coordonné horizontal du mouvement
    int y;//coordonné vertical du mouvement
    int IDj; //indice du pion qui va effectuer le mouvement
    int IDa; //indice du pion adversaire qui va etre capturé
    struct mvt *fils1;//pointeur sur mouvement complexe gauche
    struct mvt *fils2;//pointeur sur mouvement complexe droite
    struct mvt *fils3;//pointeur autres mouvement pour un pion dame
    struct mvt *pere; //pointeur sur le mouvement précédente
}mouvement;//structure d'un mouvement

typedef struct noeud
{
    mouvement* lejeu; // La suite du mouvement constituant un tour
    int score;        // Le score du jeu
    int copy_damier[NB_CASES][NB_CASES];//copie du damier
    pion copy_pions[NB_PIONS];//copie du tableau des pions
    struct noeud* svt;      // pointeur sur les mouvements frère
    struct noeud* sous_jeu; // pointeur sur les mouvements derivés
} noeud;//structure d'un noeud

/*
 * enumeration pour le type de mouvement
 */
typedef enum typeMouv
{
    SIMPLE,//aucun pion d'adversaire capturé
    COMPLEXE //il y a un pion d'adversaire capturé
} typeMouvement;

void Afficher_Damier(int damier[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d\t", damier[i][j]);
        }
        printf("\n");
    }
}
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
/*
 * fonction qui nous permet d'initialiser les positions des pions dans le damier
 *Entré:une matrice des entier
 *Sortie:matrice initialisée
 */

void Initialiser_Damier(int dameier[8][8])
{
    //déclaration des variables
    int a=0,k=0,j;
    while(k<8)//parcourir le damier
    {
        for (j = 0; j <8 ;j++)
        {
            //mettre les cases non jouable
            dameier[k][j++]=-2;
            if(k==4)
                dameier[k][j]=-1;  //mettre les cases vide
            else
                //mettre les pions du machine dans ses positions initiales
                dameier[k][j]=a++;
        }
        k++;
        for (j = 0; j <8 ;j++)
        {
            if(k==3)
                dameier[k][j++]=-1;//mettre les cases vide
            else
                //mettre les pions du machine dans ses positions initiales
                dameier[k][j++]=a++;
            dameier[k][j]=-2;//mettre les cases non jouable
        }
        k++;
    }
}
/*
 * fonction qui nous permet d'initialiser les information des pions
   dans la table des pions
 *Entré:un arbre de type mouvement
 *Sortie: un arbre de type mouvement
 */
void Initialiser_Tab_Pion(pion Tab[24])
{
    //déclartion des variables
    int j=1,k=0;
    for(int i=0;i<24;i++)
    {
        Tab[i].etat=1;//initialiser l'etat du pion
        Tab[i].y=k;//initialiser coordoné verticale
        Tab[i].x=j;//initialiser coordoné horizontal
        j+=2;//passer à la ligne suivante
        if(j>7)//si on a arriver à la fin du ligne horizontal
        {
            if(k==2)//si on a terminer les pions du machines
                //sautter les deux lignes vides(qui sépare le deux familles des pions
                k=5;
            else
                k++; //passer à a ligne suivante
            if((k%2 ==0))//si la ligne est paire
                j=1;
            else
                j=0;//si la ligne est impaire
        }
    }
}

/*
 * fonction qui nous permet de lier chaque noeud
    du l'arbre des mouvement à son père
 *Entré:un arbre de type mouvement
 *Sortie: un arbre de type mouvement
 */
mouvement* creer_antiarboraissance(mouvement* Arbre)
{
    if (Arbre) // Condition d'arret
    {
        if (Arbre->fils2)  //si le noeud a un fils droite
            Arbre->fils2->pere = Arbre;
        if (Arbre->fils1)//si le noeud a un fils gauche
            Arbre->fils1->pere = Arbre;
        //appelle récursive pour les deux fils
        Arbre->fils1 = creer_antiarboraissance(Arbre->fils1);
        Arbre->fils2 = creer_antiarboraissance(Arbre->fils2);
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
    //allocation de la mémoire
    noeud* NE = (noeud*)malloc(sizeof(noeud));
    if (!NE)//vérification de l'allocation mémoire
    {
        printf("\nErreur d'allocation de la structure noeud\n");
        return (noeud*)NE;
    }
    NE->lejeu = NULL;
    NE->score = 0;
    NE->svt = NE->sous_jeu = NULL;
    return (noeud*)NE;
}
/*
    Nom Fonction : creer_mouvement
    Entree : _ entiers x et y qui sont les coordonee
             _ entiers IDj et IDa qui sont les id des jetons
    Sortie : _ element de type mouvement
    Description : Cree et retourne un element de type mouvement
*/
mouvement* creer_mouvement(int x, int y, int IDj, int IDa)
{
    //allocation de la mémoire
    mouvement* NE = malloc(sizeof(mouvement));

    if (!NE)//vérification de l'allocation mémoire
    {
        printf("\n\t\t__________Erreur d'allocation de la "
               "structure mouvement__________\n\n");
        return (mouvement*)NE;
    }
    //initialisation des champs pour un mouvement
    NE->x = x;
    NE->y = y;
    NE->IDj = IDj;
    NE->IDa = IDa;
    NE->fils1 = NE->fils2 = NE->fils3 = NE->pere = NULL;
    return (mouvement*)NE;
}
/*
 * Fonction qui permet d'insérer un nouveau mouvement
    au début des autres mouvements dans un liste des noeud
 * Entré :un noeud (N) , le nouveau mouvement(M)
 * sortie:pointeur de type noeud
 */
noeud* inserer_debut_noeud(noeud* N, mouvement* M)
{
    noeud* NE2= creeNoeud();//creation d'une noeud
    NE2->lejeu = M;//affecter le nouveau mouvement
    // mettre le nouveau noeud en début
    NE2->svt = N;
    return ((noeud*)NE2);
}/*
 * Fonction qui permet d'insérer un nouveau mouvement
    au début des autres mouvements dans un liste des mouvements
 * Entré :un liste des mouvements (M) , le nouveau mouvement (M2)
 * sortie :pointeur de type mouvement
 */
mouvement* inserer_debut_mvt(mouvement* M, mouvement* M2)
{
    //creation d'une nouveau mouvement
    mouvement* NE = creer_mouvement(M2->x, M2->y, M2->IDj, M2->IDa);
    // mettre le nouveau noeud en début
    NE->fils1 = M;
    return ((mouvement*)NE);
}
/*
 *Fonction qui nous permet d'inverser l'ordre des mouvement dans la liste
  des mouvements dans un noeud
 * Entré :pointeur de type noeud
 * sortie :pointeur de type noeud
*/
noeud* inverser_lejeu(noeud* N)
{
    if (!N) //si le noeud n'existe pas
        return ( (noeud*)NULL);
    if (!N->lejeu)//si il n y a aucun mouvement
        return ((noeud*)N);
    mouvement* tmp;
    tmp = N->lejeu;
    N->lejeu = NULL;
    while (tmp) //parcourir la liste des mouvements
    {
        N->lejeu = inserer_debut_mvt(N->lejeu, tmp);
        tmp = tmp->pere;
    }
    return ((noeud*)N);
}
/*
 * fonction qui permet de transferer une cellule de type mouvement à
   un liste des noeud de type noeud
 * Entré :pointeur de type noeud,pointeur de type mouvement
 * sortie :pointeur de type noeud
 */
noeud* creer_sous_liste(noeud* N, mouvement* M)
{
    if (M)//si le mouvement exist
    {
        if (M->fils1)//s'il a un fils gauche
            N = creer_sous_liste(N, M->fils1);
        if (M->fils2)//s'il a un fils droite
            N = creer_sous_liste(N, M->fils2);
        if (!M->fils2 && !M->fils1) //si c'est une feuil
            N = inserer_debut_noeud(N, M);
        return ((noeud*)N);
    }
    return ((noeud*)N);
}
/*
 * fonction qui permet de transferer tout les arbres des mouvements en des
   liste des mouvement et les invérser
 * Entré :pointeur de type noeud
 * sortie :pointeur de type noeud
 */
noeud* creer_liste(noeud* N)
{
    //déclaration des variables
    noeud *NE = NULL, *tmp;
    mouvement* tmp2;
    tmp = N;
    while (tmp)//tant qu'il y a des noeuds
    {
        //on pointe sur la listes des mouvement dans le noeud
        tmp2 = tmp->lejeu;
        while (tmp2)//tant qu'il y des mouvements
        {
            //on li chaque mouvement avec son père
            tmp2 = creer_antiarboraissance(tmp2);
            //creer une liste a travers cette arbre de mouvements
            NE = creer_sous_liste(NE, tmp2);
            tmp2 = tmp2->fils3;//passer au mouvement suivante
        }
        tmp = tmp->svt;//passer au noeud suivant
    }
    tmp = NE;
    while (tmp)//on inverse tous les listes obtenues
    {
        tmp = inverser_lejeu(tmp);
        tmp = tmp->svt;
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
void copierLesJetons(pion tabDst[NB_PIONS],pion tabSrc[NB_CASES])
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
void MettreAjour_tab_pion(pion lespions[NB_PIONS],
                          int Damier[NB_CASES][NB_CASES])
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
        // On sauvegarde la position du jeton de l'adversaire
        Damier[lesjetons[lemvt->IDa].y][lesjetons[lemvt->IDa].x] = -1;
        // On reinitialise les donnee dans la table des jetons
    }
    // On enlève le jeton du joeur de sa position initiale
    Damier[lesjetons[lemvt->IDj].y][lesjetons[lemvt->IDj].x] = -1;
    // On le déplace vers la nouvelle position
    Damier[lemvt->y][lemvt->x] = lemvt->IDj;
    // On reinitialise les donnee dans la table des jetons
    lesjetons[lemvt->IDj].x = lemvt->x;
    lesjetons[lemvt->IDj].y = lemvt->y;

    if (lemvt->IDj < 12)//si le pion est du machine
    {
        //si le pion va etre un dame on change son état à 2
        if (lesjetons[lemvt->IDj].y == 7)
            lesjetons[lemvt->IDj].etat = 2;
    }
    else //si le pion est du joueur
    {
        //si le pion va etre un dame on change son état à 2
        if (lesjetons[lemvt->IDj].y == 0)
            lesjetons[lemvt->IDj].etat = 2;
    }
    //mise à ajour les changement dans le tableau des pions
    MettreAjour_tab_pion(lesjetons, Damier);
}

/*
 * Fonction qui determine les mouvements possibles pour un pion ordinaire
   dans une direction (gauche /droite)
 * Entré : - un id d'un pion
           - le damier
           - le tableau des pions
           - arbre mouvement
           - le sens de mouvement vertical (1 / -1 )
           - le sense de mouvement horizontal (1 / -1)
           - le type du mouvement (Simple /complexe)
* Sortie : pointeur de type mouvement contenant tous les mouvements
           possible dans une direction
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
    // s'il a une case libre pour boujer
    if (x + h < 8 && y + v < 8 && x + h >= 0 && y + v >= 0)
    {
        if (damier[y + v][x + h] == -1 && typemvt == SIMPLE)
            // s'il va faire une mouvement sans capturer un pion adversaire
            N = creer_mouvement(x + h, y + v, id, -1);
        else if (damier[y + v][x + h] == -1)
            return ((mouvement*)NULL);
        // s'il a un pion adversaire à coté
        else if ((damier[y + v][x + h] < 12 && damier[y][x] > 11)||
                 (damier[y + v][x + h] > 11 && damier[y][x] < 12))
        {
            // s'il peut capurer cette pion de l'adversaire
            if (x + (h * 2) < 8 && y + (v * 2) < 8 && x + (h * 2) >= 0 &&
                y + (v * 2) >= 0)
            {
                if (damier[y + (v * 2)][x + (h * 2)] == -1)
                {
                    // on garde cette mouvement
                    N = creer_mouvement(x + (h * 2), y + (v * 2), id,
                                        damier[y + v][x + h]);
                    // on fait une copie du damier
                    copierDamier(damier1, damier);
                    // on fait une copie du tableau des pions
                    copierLesJetons(pions1, pions);
                    //on applique cette mouvement
                    deplacerJeton(N, damier1, pions1);
                    // on cherche les mouvements complexes à droite et à gauche
                    N->fils1 = Mouvements(id, damier1, pions1, N->fils1, v,
                                          -1, COMPLEXE);
                    N->fils2 = Mouvements(id, damier1, pions1, N->fils2, v,
                                          1, COMPLEXE);
                }
            }
        }
    }
    // retourner le noeud des mouvements
    return ((mouvement*)N);
}
/*
 * Fonction qui determine  les mouvements possibles pour un pion dame
    dans une direction
    * Entré : - un id d'un pion
              - le damier
              - le tableau des pions
              - arbre mouvement
              - le sens de mouvement vertical (1 / -1 )
              - le sense de mouvement horizontal (1 / -1)
              - le type du mouvement (Simple /complexe)
* Sortie : pointeur de type mouvement contenant tous les mouvements
 *         possible dans une direction
 */
mouvement* Dame(int id, int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS],
                mouvement* N, int v, int h, int typemvt)
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
    /*  tant qu'il y'a des cases libres dans une direction et on a
        capturé aucun pion adversaire  (mouvement SIMPLE) */
    while (damier[b][a] == -1 && typemvt == SIMPLE)
    {
        if (a < 8 && b < 8 && a >= 0 && b >= 0) // si la indices sont valides
        {
            T = creer_mouvement(a, b, id, -1);//creer le mouvement
            //inserer le mouvement dans la liste des noeuds
            N = insererListeMouvement(N, T);
            //passer à la case suivante
            a = a + h;
            b = b + v;
        }
        else// si les indices sont invalides
            break;
    }
    /*  tant qu'il y'a des cases libres dans une direction et on a
        capturé aucun pion adversaire  (mouvement COMPLEXE) */
    while (damier[b][a] == -1 && typemvt == COMPLEXE)
    {
        if (a < 8 && b < 8 && a >= 0 && b >= 0)// si la indices sont valides
        {
            //ignorer cette case et passer à la case suivante
            a = a + h;
            b = b + v;
        }
    }
    //si on trouve un pion adversaire dans un diagonale
    if ((damier[b][a] < 12 && damier[b][a] >= 0 && damier[y][x] > 11) ||
        (damier[b][a] > 11 && damier[y][x] < 12 && damier[y][x] >= 0))
    {
        //garder l'ancien coordnées
        c = a;
        d = b;
        //passer à la case suivante
        c = c + h;
        d = d + v;
        //tant qu'il y a des cases libre dans ce diagonale
        while (damier[d][c] == -1)
        {
            // si la indices sont valides
            if (c < 8 && d < 8 && c >= 0 && d >= 0)
            {
                T = creer_mouvement(c, d, id, damier[b][a]);//creation du mouvement
                T2 = creer_mouvement(c, d, id, damier[b][a]);
                //faire une copie du damier
                copierDamier(damier1, damier);
                //faire une copie du tableau des pions
                copierLesJetons(pions1, pions);
                //appliquer cette mouvement sur la copie du damier
                deplacerJeton(T, damier1, pions1);
                //appellee récursive en arrière et  sense horizontal droite
                T2->fils1 = Dame(id, damier1, pions1, T2->fils1, v * (-1),
                                 h, COMPLEXE);
                //appellee récursive en avanceent et  sense horizontal droite
                T->fils1 = Dame(id, damier1, pions1, T->fils1, v,
                                1, COMPLEXE);
                //appellee récursive en avanceent et  sense horizontal gauche
                T->fils2 = Dame(id, damier1, pions1, T->fils2, v,
                                -1, COMPLEXE);
                if (T2->fils1)//s'il existe un mouvement complexe en arriére
                {
                    // T2->fils1->pere=T2;
                    //on insère le premier mouvement
                    N = insererListeMouvement(N, T2);
                    //s'il ya une mouvement complexe en avancent
                    //on insère cette mouvement
                    if (T->fils1 || T->fils2)
                        N = insererListeMouvement(N, T);
                }
                //s'il n ya pas une mouvement complexe en arrière
                //on insère les mouvement possible en avancent
                else
                    N = insererListeMouvement(N, T);

                /*if (T->fils1)
                    T->fils1->pere=T;
                if (T->fils2)
                    T->fils2->pere=T;*/

                //passer à la case suivante
                c = c + h;
                d = d + v;
            }
            else // si la indices sont invalides
                break;
        }
    }
    return ((mouvement*)N);
}

/*
 * Fonction qui determine tous les mouvements possibles pour
   un pion quelconque dans tous les directions
  * Entré : - un id d'un pion
              - le damier
              - le tableau des pions
 *Sortie : pointeur de type mouvement contenant tous les mouvements
 *         possible dans une direction
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
        // sense verticale = 1 et sens horizontale =-1
        tmp->lejeu = Dame(id, damier, pions, tmp->lejeu, 1, -1, SIMPLE);
        //s'il n ya pas de mouvement possible dan la direction précédente
        if (tmp->lejeu)
        {
            //creer une autre noeud
            tmp->svt = creeNoeud();
            tmp = tmp->svt;
        }
        // sense verticale = 1 et sens horizontale =1
        tmp->lejeu = Dame(id, damier, pions, tmp->lejeu, 1, 1, SIMPLE);
        //s'il n ya pas de mouvement possible dan la direction précédente
        if (tmp->lejeu)
        {
            //creer une autre noeud
            tmp->svt = creeNoeud();
            tmp = tmp->svt;
        }
        // sense verticale = -1 et sens horizontale =-1
        tmp->lejeu = Dame(id, damier, pions, tmp->lejeu, -1, -1, SIMPLE);
        //s'il n ya pas de mouvement possible dan la direction précédente
        if (tmp->lejeu)
        {
            //creer une autre noeud
            tmp->svt = creeNoeud();
            tmp = tmp->svt;
        }
        // sense verticale = -1 et sens horizontale =1
        tmp->lejeu = Dame(id, damier, pions, tmp->lejeu, -1, 1, SIMPLE);
    }
    else // si c'est un pion normal
    {
        // on determine le sens vertical du joueur
        if (id < 12)
            v = 1;
        else
            v = -1;
        // v :sens vertical pour un joueur, sens horizontale =1
        tmp->lejeu = Mouvements(id, damier, pions, tmp->lejeu, v, 1, SIMPLE);
        //s'il n ya pas de mouvement possible dan la direction précédente
        if (tmp->lejeu)
        {
            //creer une autre noeud
            tmp->svt = creeNoeud();
            tmp = tmp->svt;
        }
        // v :sense vertical pour un joueur, sens horizontale =-1
        tmp->lejeu = Mouvements(id, damier, pions, tmp->lejeu, v, -1, SIMPLE);
    }
    if (!tmp->lejeu) //s'il n' ya aucun mouvement dans la dernier noeud
        tmp = NULL;
    if (!A->lejeu)//s'il n' ya aucun mouvement dans tous les direction
    {
        free(A);
        A = NULL;
    }
    return ((noeud*)A);
}

/*
 *fonction qui retourne l 'id du pion qu a une possibilité de capturer un pion
  adversaire et ne l'avait pas fait (nfekh)
 * Entré :    - id joueur ( j )
              - le damier
              - le tableau des pions
 *Sortie : id du pion qu'il faut etre capturé
 */
int fct_nfikh(int j, int damier[NB_CASES][NB_CASES], pion pions[NB_PIONS])
{
    //déclaration des variables
    int i,a,b;
    noeud *N = NULL, *tmp;
    if (j < 12)//le cas du machine
    {
        //les indice entre 0 et 11
        a = 0;
        b = 12;
    }
    else //le cas du joueur
    {
        //les indices entre 12 et 23
        a = 12;
        b = 24;
    }
    for (i = a; i < b; i++)//parcourir tous les pions
    {
        if (pions[i].etat != 0)//si le pion encore présent sur le damier
        {
            //chercher les mouvements possible pour ce pion
            N = Mouvements_Possibles(i, damier, pions);
            N = creer_liste(N);
            tmp = N;
            while (tmp)//parcourir la liste des mouvements de ce pion
            {
                //s'il y a un pion possible à a capturer on retourne son indice
                if (tmp->lejeu->IDa >= 0)
                    return ((int)i);
                tmp = tmp->svt;
            }
        }
    }
    return ((int)-1);
}

/*
 * fonction qui permet de calculer le cout d'un mouvement
 * Entré : un noeud qui contient les détails d'un mouvement
 * Sortie : un noeud avec le score du mouvement calculé
 */
noeud *calculer_cout(noeud *N)
{
    //déclaration des variables
    int score =0;
    int nbJettonsJ1 = 0, nbJettonsJ2 = 0,ind;
    mouvement *ptc=N->lejeu;//un pointeur sur le mouvement dans ce noeud
    while (ptc->fils1)//tant qu'il y a des mouvements
    {
        if(ptc->IDa<0)//s'il n y a pas un pion adversaire a capturé
        {
            break;
        }

        else if(N->copy_pions[ptc->IDa].etat==2)//si un dame va etre capturé
            score+=6;
        else //si un pion normale va etre capturé
            score+=3;
        deplacerJeton(ptc,N->copy_damier,N->copy_pions);
        ptc=ptc->fils1;
    }
    if(ptc->IDa>=0 )//s'il n y a pas un pion adversaire a capturé
    {
        if( N->copy_pions[ptc->IDa].etat==2)//si un dame va etre capturé
            score+=6;
        else //si un pion normale va etre capturé
            score+=3;
    }
    //si le pion en mouvement n'est pas un dame
    if(N->copy_pions[ptc->IDj].etat==1)
    {
        //si après cette mouvement il va etre un dame
        if((ptc->y == 7 && ptc->IDj<12) || (ptc->y ==0 && ptc->IDj >11))
            score +=2;
        //si après cette mouvement il va etre proche d'etre un dame
        if((ptc->y == 6 && ptc->IDj<12) || (ptc->y ==1 && ptc->IDj >11))
            score ++;
    }

    //ici on compte les pions du machine présent dans le damier
    for (ind = 0; ind < 12; ind++)
    {
        //pour un pion normal on ajoute 1
        if (N->copy_pions[ind].etat == 1)
            nbJettonsJ2++;
            //pour un dame on ajoute 2
        else if (N->copy_pions[ind].etat == 2)
            nbJettonsJ2 += 2;
    }
    //ici on compte les pions du joueur présent dans le damier
    for (ind = 12; ind < 24; ind++)
    {
        //pour un pion normal on ajoute 1
        if (N->copy_pions[ind].etat == 1)
            nbJettonsJ1++;
            //pour un dame on ajoute 2
        else if (N->copy_pions[ind].etat == 2)
            nbJettonsJ1 += 4;
    }
    
    //si le pion qui bouge est celle du machine
    if (0 <= N->lejeu->IDj && N->lejeu->IDj < 12)
        score += nbJettonsJ2 - nbJettonsJ1;
    else //si le pion qui bouge est celle du joueur
        score += nbJettonsJ1 - nbJettonsJ2;
    N->score=score;
    return ((noeud*) N);
}