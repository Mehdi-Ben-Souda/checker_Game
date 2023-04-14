
typedef struct img
{
    GtkWidget* img;
    char fichier[NB_Cara_chemin];
    Taille* taille;
    coordonne pos;
}image;

image *creer_image(char* fichier,int largeur ,int longueur, int X, int Y)
{
    printf("\n JJJJJJJJJJJJJJJJJ \n");
    image* img = (image*)malloc(sizeof(image));
    strcpy(img->fichier, fichier);
    img->pos.X = X;
    img->pos.Y = Y;
    img->taille->largeur;
    img->taille->longueur;
    printf("\n JJJJJJJJJJJJJJJJJ \n");
    GdkPixbuf* pixt = gdk_pixbuf_new_from_file_at_size(fichier, largeur, longueur,NULL);
    img->img = gtk_image_new_from_pixbuf(pixt);
    return((image*)img);
}
