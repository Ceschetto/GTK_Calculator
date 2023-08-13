#include "../headers/gtk_interface.h"
#include "../headers/calculator_data.h"
#include <gtk/gtk.h>
void print_results( GtkTextBuffer * text_buffer);


void activate(GtkApplication *appPtr, gpointer data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box;

  GtkTextBuffer * text_buffer;
  GtkWidget * text_view;

  GtkWidget *grid;

  init_calculator();

  window = gtk_application_window_new(appPtr);
  gtk_window_set_title(GTK_WINDOW(window), "Calcolatrice");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);


  grid = gtk_grid_new();


  text_view = gtk_text_view_new();
  text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  gtk_text_buffer_set_text(text_buffer, "Wow", -1);


  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
  gtk_box_set_baseline_child(GTK_BOX(box), 2);
  gtk_box_append(GTK_BOX(box), text_view);
  gtk_box_append(GTK_BOX(box), grid);

  gtk_window_set_child(GTK_WINDOW(window), box);


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
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(print_results), text_buffer);
  gtk_grid_attach( GTK_GRID( grid ), button, 2, 3, 1, 1 );


  button = gtk_button_new_with_label(".");
  g_signal_connect(button, "clicked", G_CALLBACK(set_true_decimal_flag), NULL);
  gtk_grid_attach(GTK_GRID( grid ), button, 2, 4, 1, 1);


 

  gtk_widget_set_visible(window, true);



}




void print_results( GtkTextBuffer * text_buffer)
{
  char res[100];
  sprintf(res, "%0.2lf", get_result());
  gtk_text_buffer_set_text(text_buffer, res, -1);
}

