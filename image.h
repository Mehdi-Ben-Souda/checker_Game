
typedef struct img
{
    GtkWidget* img;
    char fichier[NB_Cara_chemin];
    coordonne taille;
    coordonne pos;
}image;

image *creer_image(char* fichier,int largeur ,int longueur, int X, int Y)
{
    image* img = (image*)malloc(sizeof(image));
    strcpy(img->fichier, fichier);
    img->pos.X = X;
    img->pos.Y = Y;
    img->taille.X=longueur;
    img->taille.Y=largeur;
    GdkPixbuf* pixt = gdk_pixbuf_new_from_file_at_size(img->fichier, img->taille.X, img->taille.Y,NULL);
    img->img = gtk_image_new_from_pixbuf(pixt);
    return((image*)img);
}
