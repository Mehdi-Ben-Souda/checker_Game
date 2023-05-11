typedef struct {
    int etat;
    int idjoueur;
    int x;
    int y;
}pion;

typedef struct {
    int damier[8][8];
    int nbrpionJoueur;
    int nbrpionMachine;
    int scoreJoueur;
    int scoreMachine;
}match;

typedef struct hsq {
    match  game;
    struct hsq *match_svt;
}historique;

typedef struct mvt
{
    int x;
    int y;
    int IDj;
    int IDa;
    struct mvt *svt;
}mouvement;

typedef struct A
{
    mouvement *listemvt;
    int cout ;
    struct A *FG;
    struct A *Frere;

}Noeud;
pion *creer_pion()
{
    pion *NE=(pion*)malloc(sizeof (pion));
    if(!NE)
    {
        printf("\nErreur d'allocation pion !!");
        exit(0);
    }
    return ((pion*)NE);
}
match *creer_match()
{
    match *NE=(match*)malloc(sizeof (match));
    if(!NE)
    {
        printf("\nErreur d'allocation pion !!");
        exit(0);
    }
    return ((match*)NE);
}
historique *creer_cellule_historique(match M)
{
    historique *NE=(historique *)malloc(sizeof (historique));
    if(!NE)
    {
        printf("\nErreur d'allocation pion !!");
        exit(0);
    }
    NE->game=M;
    NE->match_svt=NULL;
    return ((historique *)NE);
}

void Initialiser_Damier(int dameier[8][8])
{
    int a=0;
    int j,i;
        for (j = 0; j <8 ;j++)
        {
            dameier[0][j++]=-2;
            dameier[0][j]=a++;
        }
        for (j = 0; j <8 ;j++)
        {
            dameier[1][j++]=a++;
            dameier[1][j]=-2;
        }
        for (j = 0; j <8 ;j++)
        {
            dameier[2][j++]=-2;
            dameier[2][j]=a++;
        }
        for (j = 0; j <8 ; j++) {
            dameier[3][j++]=-1;
            dameier[3][j]=-2;
        }
        for (j = 0; j <8 ; j++) {
        dameier[4][j++]=-2;
        dameier[4][j]=-1;
        }
         for (i = 7; i >=0 ; i--) {
        dameier[7][i--]=-2;
        dameier[7][i]=a++;
    }
    for (i = 7; i >=0 ; i--) {
        dameier[6][i--]=a++;
        dameier[6][i]=-2;
    }
    for (i = 7; i >=0 ; i--) {
        dameier[5][i--]=-2;
        dameier[5][i]=a++;
    }

}
void Afficher_Damier(int damier[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d  ", damier[i][j]);
        }
        printf("\n");
    }
}

