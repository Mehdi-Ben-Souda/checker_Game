#pragma once

typedef struct
{
    GtkWidget *monframe;
    char label[maxcarac];
    char name[maxcarac];
    int border_size;
    coordonne pos;
    coordonne Taille;
}frame;

void Modifier_Couleur_widget(GtkWidget *widget,char *color)
{
    GdkRGBA C;
    gdk_rgba_parse(&C,color);
    gtk_widget_override_background_color(widget,GTK_STATE_NORMAL,&C);
}

void Modifier_Style(GtkWidget*a,gchar* name)
{
    GtkStyleContext *context;
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    context = gtk_widget_get_style_context (a);

    gtk_css_provider_load_from_path (cssProvider,"D:\\ILISI\\ILISI 2022-----2023 1A\\GTK\\project\\gtk_css.css", NULL);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(cssProvider),
                                    GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,name);
}

/*    l'initialisation d'une frame    */
frame* Init_frame( char label[maxcarac],char name[maxcarac],int border_size,int X,int Y,int hauteur,int largeur)
{
    frame *F;
    // Allocation de mémoire pour la structure frame
    F = (frame *) malloc(sizeof(frame));
    if (!F) {
        printf("\nErreur d'allocation [frame]");
        exit(0);
    }
    strcpy(F->label,label);
    strcpy(F->name,name);
    F->border_size=border_size;
    F->pos.Y=Y;
    F->pos.X=X;
    F->Taille.X=hauteur;
    F->Taille.Y=largeur;
    return ((frame*)F);
}
    /*    La création d'une frame    */
    void Creation_frame(frame* F)
    {
        if (!F)
        {
            printf("\nErreur de pointeur nul [frame]");
            exit(0);
        }

        // Création d'un nouveau widget Gtk de type Gtkframe
        F->monframe = gtk_frame_new(F->label);
        // Set the border width of the frame
        gtk_container_set_border_width(GTK_CONTAINER(F->monframe), 10);
        // Configuration des attributs du cadre Gtk en utilisant les valeurs stockées dans la structure frame
      //  gtk_frame_set_label(GTK_FRAME(F->Fr), F->label);
      //  gtk_frame_set_label_align(GTK_FRAME(F->Fr), (gfloat)F->label_xalign,(gfloat)F->label_yalign);
      //  gtk_frame_set_shadow_type(GTK_FRAME(F->Fr), F->shadow_type);
       // if(F->Couleur[0] !='\0') Modifier_Couleur_widget(F->Fr,F->Couleur);
        gtk_widget_set_size_request(F->monframe,F->Taille.X,F->Taille.Y);
       // Modifier_Style(F->Fr,"frame");
    }
