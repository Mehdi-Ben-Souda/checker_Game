#pragma once

typedef struct
{
    GtkWidget* monframe;
    char label[maxcarac];
    char name[maxcarac];
    int border_size;
    coordonne pos;
    coordonne Taille;
} frame;

/*    l'initialisation d'une frame    */
frame* Init_frame(char label[maxcarac], char name[maxcarac], int border_size, int X, int Y, int hauteur, int largeur)
{
    frame* F;
    // Allocation de mémoire pour la structure frame
    F = (frame*)malloc(sizeof(frame));
    if (!F)
    {
        printf("\nErreur d'allocation [frame]");
        exit(0);
    }
    strcpy(F->label, label);
    strcpy(F->name, name);
    F->border_size = border_size;
    F->pos.Y = Y;
    F->pos.X = X;
    F->Taille.X = hauteur;
    F->Taille.Y = largeur;
    return ((frame*)F);
}
/*    La création d'une frame    */
void Creation_frame(frame* F)
{
    if (!F)
    {
        printf("\nErreur d'allocation frame !!");
        exit(0);
    }
    // Création d'un nouveau widget Gtk de type Gtkframe
    F->monframe = gtk_frame_new(F->label);
    // Set the border width of the frame
    if (F->border_size)
        gtk_container_set_border_width(GTK_CONTAINER(F->monframe), F->border_size);
    gtk_widget_set_size_request(F->monframe, F->Taille.X, F->Taille.Y);
    gtk_widget_set_name(F->monframe, F->name);
}
void Ajouter_Frame(frame* frame, GtkWidget* fils)
{
    if (!frame)
    {
        printf("\nframe dosen't exist !!!");
        exit(-1);
    }
    gtk_container_add(GTK_CONTAINER(frame->monframe), fils);
}
