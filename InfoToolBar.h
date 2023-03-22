typedef struct
{
    GtkWidget *info_toolbar;//pointeur sur le toolbar d'information
    const gchar *message;//le message
    const gchar *boutton_Label;//le titre du boutton
    guint type_message;//le type de message
}InfoToolBar;//structure du toolbar d'information
/*
 * Fonction qui permet l'initialisation d'un toolbar d'information
 * entrées : -> le message
             -> le titre du boutton
             -> //le type de message
 * sorties : un pointeur sur un toolbar d'information
 */
InfoToolBar *Init_InfoToolBar(const gchar *message,const gchar *boutton_Label,guint type_message)
{
    InfoToolBar *NE;//déclaration d'un nouvel élément
    NE=(InfoToolBar*)malloc(sizeof (InfoToolBar));//l'allocation de la mémoire
    if(!NE)//vérification d'allocation
    {
        printf("\nerrur d'allocation !!!!");
        exit(0);
    }
    //Initialisation des champs de la structure
    NE->boutton_Label=boutton_Label;
    NE->message=message;
    NE->type_message=type_message;
    return ((InfoToolBar*)NE);
}
/*
 * Fonction qui permet creer un toolbar d'information
 * entrées : -> pointeur sur le toolbar d'information
 * sorties : un pointeur sur le toolbar d'information après création
 */
InfoToolBar *Creer_InfoToolBar(InfoToolBar *inftoolbar)
{
    GtkWidget *message_label, *content_area;//déclaration des variables
    if(!inftoolbar)//vérification d'initialisation
        return ((InfoToolBar*)NULL);
    //creer le toolbar d'information
    inftoolbar->info_toolbar = gtk_info_bar_new ();
    gtk_widget_set_no_show_all (inftoolbar->info_toolbar, FALSE);
    //creer le message
    message_label = gtk_label_new (inftoolbar->message);
    content_area = gtk_info_bar_get_content_area (GTK_INFO_BAR (inftoolbar->info_toolbar));
    //ajouter le message à l'espace du message dans le toolbar d'information
    gtk_container_add (GTK_CONTAINER (content_area),message_label);
    //ajouter un boutton dans le toolbar d'information
    gtk_info_bar_add_button (GTK_INFO_BAR (inftoolbar->info_toolbar),inftoolbar->boutton_Label,GTK_RESPONSE_OK);
    //mettre le type de message
    gtk_info_bar_set_message_type (GTK_INFO_BAR (inftoolbar->info_toolbar),inftoolbar->type_message);
    //cacher le toolbar d'information après cliquer sur le boutton
    g_signal_connect (inftoolbar->info_toolbar,"response",G_CALLBACK (gtk_widget_hide),NULL);
    return ((InfoToolBar*)inftoolbar);
}
/*
 * Fonction qui permet d'afficher un toolbar d'information
 * entrées : -> pointeur sur le toolbar d'information
 * sorties : le toolbar d'information affiché dans la fenetre
 */
void Afficher_InfoToolBar(InfoToolBar* inf)
{
    if(!inf)
        return;
    gtk_widget_show (inf->info_toolbar);
}