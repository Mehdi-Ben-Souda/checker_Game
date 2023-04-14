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
                                             "OK",
                                             GTK_RESPONSE_ACCEPT,
                                             "Annuler",
                                             GTK_RESPONSE_REJECT,
                                             NULL);

        content_area = gtk_dialog_get_content_area(GTK_DIALOG(ledialog->mon_dialog));

        hbox = gtk_hbox_new(FALSE, 5);
        image = gtk_image_new_from_file(ledialog->image);
        label = gtk_label_new(ledialog->texte);

        gtk_box_pack_start(GTK_BOX(hbox), image, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);

        gtk_container_add(GTK_CONTAINER(content_area), hbox);

        gtk_widget_show_all(ledialog->mon_dialog );

        gtk_dialog_run(GTK_DIALOG(ledialog->mon_dialog ));

        gtk_widget_destroy(ledialog->mon_dialog );
	return (Dialog*)ledialog;
}