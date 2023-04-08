typedef struct
{
    char username[maxcarac];
    char password[maxcarac];
    char image[maxcarac];
} infojoueur;
typedef struct cel
{
    infojoueur *info;  // champ d'information de type infoetud
    struct cel *svt; // pointeur sur le suivant
    int nbjoueur;
} cellulejoueur;

infojoueur *creer_etud()
{ // declaration des variables
    infojoueur *NE;
    // allocation de la memoire
    NE = (infojoueur *)malloc(sizeof(infojoueur));
    if (!NE) // vérification d'allocation
    {
        printf("\nerreur d'allocation !! ");
        exit(0);
    }
    NE->username[0]='\0';
    NE->password[0]='\0';
    NE->image[0]='\0';
    return ((infojoueur *)NE); // retourne l'étudiant crée
}
cellulejoueur *creer_cellule(infojoueur *etud)
{
    // declaration des variables
    cellulejoueur *NE;
    // allocation de la memoire
    NE = (cellulejoueur *)malloc(sizeof(cellulejoueur));
    if (!NE) // vérification d'allocation
    {
        printf("\nerreur d'allocation !! ");
        exit(0);
    }
    // initialisation de la cellule crée
    NE->info = etud;
    NE->svt = NULL;
    NE->nbjoueur=0;
    return ((cellulejoueur *)NE);
}
void lire_string(FILE *f, char mot[maxcarac])
{ // declaration des variables
    char c;
    int i = 0;
    do
    { // lire caractére par caractére tant que on n'a pas encore arrivé à un ;
        fscanf(f, "%c", &c);
        mot[i++] = c;
    } while (c != ';');
    mot[i - 1] = '\0';
    printf("\n%s",mot);
}
cellulejoueur *inserer_etudiant(cellulejoueur *base, infojoueur *etudiant)
{ // declaration des variables
    cellulejoueur *ptc;
    // création de la celluleetud avec un étudiant
    cellulejoueur *cell = creer_cellule(etudiant);
    if (!base) // vérifier si la classe existe
        // insertion de l'étudiant à la bonne place dans le tableau classe
        return ((cellulejoueur *)cell); // retourne la classe
    if(strcmp(base->info->username,cell->info->username)<0)
    {
        cell->svt=base;
        return ((cellulejoueur*)cell);
    }
    ptc = base;
    while(ptc->svt)
    {
        if(strcmp(ptc->svt->info->username,cell->info->username)<0)
        {
            cell->svt=ptc->svt;
            ptc->svt=cell;
            return ((cellulejoueur*)base);
        }
    }
    ptc->svt=cell;
    return ((cellulejoueur*)base);
}
infojoueur *Extraire_Info(FILE *f)
{
    // declaration des variables
    infojoueur *joueur = creer_etud();
    // vérification de l'existence du fichier
    if (f == NULL)
    {
        printf("\nfichier introuvable !!");
        exit(1);
    }
    //  appel de la fonction lire_string
    lire_string(f, joueur->username);
    lire_string(f, joueur->password);
    lire_string(f, joueur->image);
    return ((infojoueur *)joueur); // retourne l'étudiant
}
cellulejoueur *remplir_Base_Joueur()
{
    // declaration des variables
    char c;
    int eof;
    FILE *f = NULL;
    infojoueur *joueur;
    // creation de la classe
    cellulejoueur *base = NULL;
    f = fopen("BaseJoueurs.csv", "r");
    if(!f)
    {
        printf("erreur");
        exit(-1);
    }
    // lire le nombre des étudiants
    fscanf(f, "%d%c", &eof, &c);
    fscanf(f, "%c", &c); // ignorer le retour chariot
    for (int i = 0; i < eof; i++) // charger les étudiants
    {
        joueur = Extraire_Info(f);
        printf("\nt :%s",joueur->username);
        base = inserer_etudiant(base, joueur);
    }
    base->nbjoueur = eof;
    fclose(f);               // fermeture de fichier
    return ((cellulejoueur *)base); // retourne la classe
}