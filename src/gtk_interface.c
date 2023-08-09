#include "../headers/gtk_interface.h"
#include "../headers/calculator_data.h"
#include <gtk/gtk.h>
void print_results(void)
{
  g_print("%0.2lf\n", get_result());
}



void activate(GtkApplication *appPtr, gpointer data)
{
  GtkWidget *window;
  GtkWidget *button;

  GtkWidget *grid;

  init_calculator();

  window = gtk_application_window_new(appPtr);
  gtk_window_set_title(GTK_WINDOW(window), "Calcolatrice");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);


  for(int i = 9, j= -1; i >= 0; i--)
  {
    if ( i%3 == 0) j++;
    char stri[] = {i+48, '\0'}; //ascii table trick
    button = gtk_button_new_with_label(stri);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operand), i ); //da capire sta storia del gpointer data come parametro
    gtk_grid_attach(GTK_GRID( grid ), button, i%3, j, 1, 1);
    
  }

  for(int i = 0; i<4; i++)
  {
    char operatorStr[] = { (i<2)? i+42 : 2*i + 41, '\0'  }; //ascii parkour
    button = gtk_button_new_with_label(operatorStr);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operation), operatorStr[0] ); //char e int sono compatibili
    gtk_grid_attach(GTK_GRID( grid ), button, 3, i, 1, 1);
  }

  button = gtk_button_new_with_label("=");
  g_signal_connect(button, "clicked", G_CALLBACK(print_results), NULL);
  gtk_grid_attach( GTK_GRID( grid ), button, 2, 3, 1, 1 );

 

  gtk_widget_set_visible(window, true);



}

