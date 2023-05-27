typedef struct {
    int etat;
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
    struct mvt *gch;
    struct mvt *drt;
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
    int a=0,k=0;
    int j;
    while(k<8)
    {
        for (j = 0; j <8 ;j++)
        {

            dameier[k][j++]=-2;
            if(k==4)
                dameier[k][j]=-1;
            else
                dameier[k][j]=a++;
        }
        k++;
        for (j = 0; j <8 ;j++)
        {
            if(k==3)
                dameier[k][j++]=-1;
            else
                dameier[k][j++]=a++;

            dameier[k][j]=-2;
        }
        k++;
    }
}
void Afficher_Damier(int damier[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d\t", damier[i][j]);
        }
        printf("\n");
    }
}

void Initialiser_Tab_Pion(pion Tab[24])
{
    int j=1,k=0;
    for(int i=0;i<24;i++)
    {
        Tab[i].etat=1;
        Tab[i].y=k;
        Tab[i].x=j;
        j+=2;
        if(j>7)
        {
            if(k==2)
                k=5;
            else
                k++;
            if((k%2 ==0))
                j=1;
            else
                j=0;
        }
    }
}
void Afficher_pion(pion P)
{
    printf("\tx :%d\ty:%d",P.x,P.y);
}
void Afficher_Tab_Pion(pion Tab[24])
{
    for (int i = 0; i < 24; i++)
    {
        printf("\nPion %d:", i);
        Afficher_pion(Tab[i]);
        
    }
        
}



