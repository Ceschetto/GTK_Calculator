#include <gtk/gtk.h>
#include "../headers/calculator_data.h"
#include <string.h>

void print_results(void)
{
  g_print("%lf", get_result());
}



void activate(GtkApplication *appPtr, gpointer data)
{
  GtkWidget *window;
  GtkWidget *button;

  GtkWidget *grid;

  init_calculator();

  window = gtk_application_window_new(appPtr);
  gtk_window_set_title(GTK_WINDOW(window), "Titolone");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);


  for(int i = 9, j= 0; i >= 0; i--)
  {
    if(i != 9 && (i%3 == 0)) j++;
    char stri[] = {i+48}; //ascii table trick
    button = gtk_button_new_with_label(stri);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operand), i ); //da capire sta storia del gpointer data come parametro
    gtk_grid_attach(GTK_GRID( grid ), button, i%3, j, 1, 1);
    
  }

  for(int i = 0; i<4; i++)
  {
    char stri[] = { (i<2)? i+42 : 2*i + 41 }; //ascii table trick
    button = gtk_button_new_with_label(stri);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operation), i ); //char e int sono compatibili
    gtk_grid_attach(GTK_GRID( grid ), button, 3, i, 1, 1);
     
  }
 

  gtk_widget_set_visible(window, true);



}




int main(int argc, char **argv)
{

  GtkApplication * TestApp;

  TestApp = gtk_application_new("id.TestApp.test", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(TestApp, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(TestApp), argc, argv);

  g_object_unref(TestApp);
  
  return status;

} 