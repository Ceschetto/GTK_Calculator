#include "../headers/gtk_interface.h"
#include "../headers/calculator_data.h"
#include <gtk/gtk.h>
void print_results(void)
{
  g_print("= %0.2lf\n", get_result());
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


  int* numbers = (int*)calloc( 10, sizeof(int));// quando dovrei liberarla?
  for(int i = 0, j = -1; i <= 9; i++)
  {
    if ( i%3 == 0) j++;

    numbers[i] = 9 - i;
    char stri[] = {numbers[i] + 48, '\0'}; //ascii table trick
    button = gtk_button_new_with_label(stri);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operand), (numbers + i)  ); //gpointer = void* --> quelli di gtk sono stupidi
    gtk_grid_attach(GTK_GRID( grid ), button, i%3, j, 1, 1);
    
  }


  char* operands = (char*)calloc(4, sizeof(char));//free??
  for(int i = 0; i<4; i++)
  {
    operands[i] =  (i<2)? i+42 : 2*i + 41 ; //ascii parkour
    char *operator = (char *) calloc(1, sizeof(char));
    button = gtk_button_new_with_label(operands + i);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operation), (operands + i) ); 
    gtk_grid_attach(GTK_GRID( grid ), button, 3, i, 1, 1);
  }

  button = gtk_button_new_with_label("=");
  g_signal_connect(button, "clicked", G_CALLBACK(print_results), NULL);
  gtk_grid_attach( GTK_GRID( grid ), button, 2, 3, 1, 1 );

  button = gtk_button_new_with_label(".");
  g_signal_connect(button, "clicked", G_CALLBACK(set_true_decimal_flag), NULL);
  gtk_grid_attach(GTK_GRID( grid ), button, 2, 4, 1, 1);


 

  gtk_widget_set_visible(window, true);



}

