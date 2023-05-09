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
