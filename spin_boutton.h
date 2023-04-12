#pragma once
typedef struct spin
{
    GtkWidget *spinbutton;
    gint min ;
    gint max ;
    gint step ;
    GtkAdjustment *adjustment;
    char name [maxcarac];
    char exist;
}Spin_Bouton;
Spin_Bouton *Init_spin(gint max1,gint min1, gint step1,char exist1,char name1[maxcarac])
{
    Spin_Bouton *mon_spin=(Spin_Bouton*)malloc(sizeof(Spin_Bouton));
    if(!mon_spin)
    {
        printf("Erreur d'allocation"); exit(-1);
    }
    mon_spin->max=max1;
    mon_spin->min=min1;
    mon_spin->step=step1;
    mon_spin->exist=exist1;
    strcpy(mon_spin->name,name1);
    return ((Spin_Bouton*)mon_spin);
}
Spin_Bouton *Creer_Spin(Spin_Bouton*mon_spin,gint value)
{
    if(mon_spin->exist=='y'||mon_spin->exist=='Y')
    {
        mon_spin->adjustment=gtk_adjustment_new(value,mon_spin->min,mon_spin->max,mon_spin->step,1,1 );
        mon_spin->spinbutton = gtk_spin_button_new (mon_spin->adjustment, 1, 0);
    }
    else
    {
        mon_spin->spinbutton=gtk_spin_button_new_with_range (mon_spin->min,mon_spin->max,mon_spin->step);
    }
    //Recupere_Spin(mon_spin);
    gtk_widget_set_name(mon_spin->spinbutton,mon_spin->name);
    return ((Spin_Bouton*)mon_spin);
}