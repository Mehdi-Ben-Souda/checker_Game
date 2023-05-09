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

