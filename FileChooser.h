typedef struct
{
    GtkNativeDialog *chooser;
    char filename[maxcarac];
}FileChooser;

FileChooser *Initialiser_FileChooser()
{
    FileChooser *NE=(FileChooser*) malloc(sizeof (FileChooser));
    if(!NE)//vérification d'allocation
    {
        printf("\nerrur d'allocation !!!!");
        exit(0);
    }
//    strcpy(file)
}
FileChooser reteourner_filename(FileChooser *chooser,char filename[maxcarac])
{
    strcpy(filename,gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser)));

}

void reponse_a_overture_fichier(GtkNativeDialog *native,int id_reponse,char filename[maxcarac])
{
    if (id_reponse == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (native);
        g_autoptr (GFile) file = gtk_file_chooser_get_file (chooser);
        strcpy(filename,gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(native)));
    }
    g_object_unref (native);
}
void Action_FileChooser(GtkWidget *widget,char filename[maxcarac])
{
    GtkFileChooserNative *native =gtk_file_chooser_native_new ("Open File",
                                                               filename,
                                                               GTK_FILE_CHOOSER_ACTION_OPEN,
                                                               "_Open",
                                                               "_Cancel");
    g_signal_connect (native, "response",G_CALLBACK (reponse_a_overture_fichier),filename);
    gtk_native_dialog_show (GTK_NATIVE_DIALOG (native));
}
void ajouter_filechooser(GtkWidget *widget,Fenetre* fenetre_parent,char filename[maxcarac])
{
    if(!widget || !fenetre_parent)
    {
        printf("filechooser ne peut pas etre ajouté");
        exit(-1);
    }
    g_signal_connect(widget,"activate",G_CALLBACK(Action_FileChooser),fenetre_parent->ma_fenetre);
}