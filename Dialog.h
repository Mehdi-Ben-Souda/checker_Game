#pragma once
//GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
//GtkWidget* iii = gtk_label_new("helooooooooo");
//GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(F->window), flags, 2, GTK_BUTTONS_OK_CANCEL, "%s", "plese select ok");
//gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), iii);
//gtk_dialog_run(GTK_DIALOG(dialog));
//gtk_widget_destroy (dialog);


typedef struct
{
	GtkWidget* mon_dialog;
	char texte[maxcarac];
	char name[maxcarac];
    char image[maxcarac];
}Dialog;

Dialog* Init_Dialog(char name[maxcarac],char text[maxcarac],char image[maxcarac])
{
	Dialog* NE = NULL;
	NE = (Dialog*)malloc(sizeof(Dialog));

    if(!NE)
    {
        printf("\nerreur d'allocation dialogue !!");
        exit(-1);
    }
	strcpy(NE->texte, text);
    strcpy(NE->image, image);

	return (Dialog*)NE;
}

Dialog* Creer_Dialog(Dialog* ledialog)
{
        GtkWidget *dialog;
        GtkWidget *label;
        GtkWidget *image;
        GtkWidget *content_area;
        GtkWidget *hbox;

        ledialog->mon_dialog = gtk_dialog_new_with_buttons("Ma boîte de dialogue",
                                             NULL,
                                             GTK_DIALOG_MODAL,
                                             "oui",
                                             GTK_RESPONSE_ACCEPT,
                                             "non",
                                             GTK_RESPONSE_REJECT,
                                             "Annuler",
                                             GTK_RESPONSE_REJECT,NULL);

        content_area = gtk_dialog_get_content_area(GTK_DIALOG(ledialog->mon_dialog));

        hbox = gtk_box_new(0, 5);
        image = gtk_image_new_from_file(ledialog->image);
        label = gtk_label_new(ledialog->texte);

        gtk_box_pack_start(GTK_BOX(hbox), image, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);

        gtk_container_add(GTK_CONTAINER(content_area), hbox);


	return (Dialog*)ledialog;
}

void Afficher_dialogue(Dialog *mondialogue)
{
    if(!mondialogue)
    {
        printf("\nDialogue dosen't exist !!");
        exit(-1);
    }
    gtk_widget_show_all(mondialogue->mon_dialog );
    gtk_dialog_run(GTK_DIALOG(mondialogue->mon_dialog ));
    gtk_widget_destroy(mondialogue->mon_dialog );
}