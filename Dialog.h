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

}Dialog;

Dialog* Init_Dialog(char name[maxcarac],char text[maxcarac])
{
	Dialog* NE = NULL;
	NE = (Dialog*)malloc(sizeof(Dialog));

	/*if (!name)
	{
		strcpy(NE->name, name);
		gtk_widget_set_name(NE->mon_dialog, name);
	}*/
	strcpy(NE->texte, text);

	return (Dialog*)NE;
}

Dialog* Creer_Dialog(Dialog* ledialog,GtkWindow *Fenetre_parent)
{
	

	ledialog->mon_dialog = gtk_dialog_new();/*GTK_WINDOW(Fenetre_parent),
		GTK_DIALOG_DESTROY_WITH_PARENT, 2, GTK_BUTTONS_OK_CANCEL, "%s", ledialog->texte);*/
	GtkWidget* iii = gtk_label_new("helooooooooo");
	gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(ledialog->mon_dialog))), iii);
	gtk_dialog_run(GTK_DIALOG(ledialog->mon_dialog));
	//gtk_widget_destroy(ledialog->mon_dialog);

	return (Dialog*)ledialog;
}