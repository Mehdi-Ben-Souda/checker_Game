#define maxcarac 50
#include "common.h"
//La structure de données du switch
typedef struct sw
{
    //un widget qui a deux états: activé ou désactivé
    GtkWidget *my_switch;
    int etat;//activé ou désactivé
}Switch;
/*
La fonction Creer_Switch
-Entrees :etat1:un entier indique l'état du boutton.
-Sortie :Objet de type Switch.
-Description: Cette fonction permet de créer un switch boutton 
        on prenons on concidération l'état qu'on veut
*/
Switch*Creer_Switch(int etat1)
{
    //allocation de la mémoire 
    Switch*my_switch1=(Switch*)malloc(sizeof(Switch));
    //si l'allocation a échoué
    if(!my_switch1)
    {
        printf("Erreur d'allocation"); exit(-1);
    }
    //Crée un widget GtkSwitch
    my_switch1->my_switch=gtk_switch_new();
    //initialisation de l'état du switch
    my_switch1->etat=etat1;
    switch(etat1)
    {
        //si on veut choisir l'état activé pour le switch
        case 0:gtk_switch_set_state(GTK_SWITCH(my_switch1->my_switch), TRUE);break;
        //si on veut choisir l'état désactivé pour le switch
        case 1: gtk_switch_set_state(GTK_SWITCH(my_switch1->my_switch), FALSE);break;
        //activé par défaut 
        default: gtk_switch_set_active(GTK_SWITCH(my_switch1->my_switch), TRUE);
    }
    return((Switch*)my_switch1);
}

//La structure de données de l'entrée de recherche
typedef struct
{
    //un widget de la sous classe des GtkEntry
    GtkWidget *search;
    GtkWidget *conteneur;//le conteneur du widget
}Search;
/*
La fonction Creer_Search
-Entrees :conteneur1:de type GtkWidget.
-Sortie : une zone de recherche.
-Description: Cette fonction permet de créer une zone de 
            recherche 
*/
Search*Creer_Search(GtkWidget *conteneur1)
{
    //allocation de la mémoire 
    Search*sea=(Search*)malloc(sizeof(Search));
    //si l'allocation a échoué
    if(!sea)
    {
        printf("Erreur d'allocation"); exit(-1);
    }
    //Initialisation du conteneur
     sea->conteneur =conteneur1;
     //créer un nouveau Gtk widget de recherche
    sea->search=gtk_search_entry_new ();
    return ((Search*)sea);
}
/*
La fonction Entry_init
-Entrees :text1:une chaine de caractere pour le text saisi 
          par défaut dans la zone.
    cache1:caractère indique le caractère choisi pour 
           cacher le text saisi
    cont:de type GtkWidget le conteneur qui va contenir
         la zone de text
    mon_icon:une chaine de caractère indique le nom
            de l'icon à ajouter dans la zone.
-Sortie :Objet de type Entree.
-Description: Cette fonction permet d'allouer de l'espace pour
la structure de type Entree et d'initialiser
ses champs et de la retourner .
*/
Entree* Entry_init(gchar text1[maxcarac],gchar cache1,
gchar *mon_icon)
{
    Entree* mon_entre=(Entree*)malloc(sizeof(Entree));
    if(!mon_entre)
    {
        printf("Erreur d'allocation"); exit(-1);
    }
    //Initialisation de caractère de remplacement
    if(cache1)
        mon_entre->cache=cache1;
    else mon_entre->cache='\0';
    //initilisation de text par défaut 
    if (text1)
    {
        strcpy (mon_entre->text, text1);
    }
    else
        strcpy (mon_entre->text, "vide");
    //initilisation pour l'icon
    if (mon_icon)
    {
        mon_entre->icon = (gchar*) malloc (150*sizeof (gchar));
        strcpy (mon_entre->icon, mon_icon);
    }
    else mon_entre->icon =NULL;
    //on retourne la structure initialisé
    return((Entree*)mon_entre);
}
/*
La fonction Creer_Entree
-Entrees :L'objet Entree initialisé.
-Sortie :Objet de type Entree.
-Description: Cette fonction permet de créer un objet entree 
    en fonction des paramétres récupéres de la fonction 
    Entree_init
*/
Entree*Creer_Entree(Entree*mon_entre)
{
    //Création d'une nouvelle entrée
    mon_entre->entry = gtk_entry_new ();
    //si on veut que le texte saisi soit visible
 if ( mon_entre->cache=='\0')
  gtk_entry_set_visibility (GTK_ENTRY( mon_entre->entry),TRUE);

 else   //si on veut un mot de passe
 {
     //avec choix de caractère de cache

    gtk_entry_set_invisible_char(GTK_ENTRY( mon_entre->entry),
                                 mon_entre->cache);
}
 //si on veut un texte saisi par défaut dans la zone de texte
 if(!strcmp(mon_entre->text,"vide"))
  {
 gtk_entry_set_text (GTK_ENTRY(mon_entre->entry),mon_entre->text);
  }
 //si on veut ajouter un icon
 if(mon_entre->icon)
 {
     gtk_entry_set_icon_from_icon_name(GTK_ENTRY(mon_entre->entry),
                                                 GTK_ENTRY_ICON_SECONDARY,mon_entre->icon);
 }
    return ((Entree*)mon_entre);
}
