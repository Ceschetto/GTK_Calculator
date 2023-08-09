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

  
  button = gtk_button_new_with_label("1");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operand), 1 );
  gtk_grid_attach(GTK_GRID( grid ), button, 0, 0, 1, 1);



  button = gtk_button_new_with_label("2");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operand), 2 );
  gtk_grid_attach(GTK_GRID( grid ), button, 1, 0 , 1, 1 );



  button = gtk_button_new_with_label("3");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operand), 3);
  gtk_grid_attach(GTK_GRID( grid ), button, 2, 0 , 1, 1 );



  button = gtk_button_new_with_label("+");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operation), '+');
  gtk_grid_attach(GTK_GRID( grid ), button, 3, 0 , 1, 1 );


  button = gtk_button_new_with_label("=");
  g_signal_connect(button, "clicked", G_CALLBACK(print_results), NULL);
  gtk_grid_attach(GTK_GRID( grid ), button, 0, 1 , 1, 1 );



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