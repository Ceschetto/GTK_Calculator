#include "../headers/gtk_interface.h"
#include "../headers/calculator_data.h"
#include <gtk/gtk.h>

void print_results( GtkTextBuffer * text_buffer);
void set_operand_and_refresh(void * opPtr);
void set_operation_and_refresh(void * opPtr);

struct c_s_data
{
  int number;
  GtkTextBuffer * text_buffer;
};

struct c_s_data_operation
{
  char operation;
  GtkTextBuffer * text_buffer;

};

typedef struct c_s_data cs;
typedef struct c_s_data_operation cs_operation;


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

  cs *csPtr = (cs *) calloc(10, sizeof(cs)); 


  for(int i = 0, j = -1; i <= 9; i++)
  {
    if ( i%3 == 0) j++;
   (csPtr[i]).number = 9-i;

    char stri[] = {csPtr[i].number + 48, '\0'}; //ascii table trick
    button = gtk_button_new_with_label(stri);

    csPtr[i].text_buffer = text_buffer;

    g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operand_and_refresh),csPtr + i);//gpointer = void* --> quelli di gtk sono stupidi
    gtk_grid_attach(GTK_GRID( grid ), button, i%3, j, 1, 1);
    
  }

  cs_operation *cs_operatPtr = (cs_operation *)calloc(4, sizeof(cs_operation));
  for(int i = 0; i<4; i++)
  {
    cs_operatPtr[i].operation =  (i<2)? i+42 : 2*i + 41 ; //ascii parkour
    cs_operatPtr[i].text_buffer = text_buffer;
    char operatStr[] = {cs_operatPtr[i].operation, '\0'};
    button = gtk_button_new_with_label(operatStr);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(set_operation_and_refresh), (cs_operatPtr + i) ); 
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


void set_operand_and_refresh(void * opPtr)
{
  cs *  op = (cs *)opPtr;
  set_operand((double)((op->number)));

  char operandStr[100];
  memset(operandStr, 0, sizeof(char) * 100);
  sprintf(operandStr, "%lf",(!is_operator_selected())? get_operand1(): get_operand2());
  gtk_text_buffer_set_text(op->text_buffer, operandStr, -1 );
  fflush(stdout); // non so perchè ma senza lo schermo non mostra nulla.
}


void set_operation_and_refresh(void * opPtr)
{
  cs_operation *  op = (cs_operation *)opPtr;
  set_operation(op->operation);

  
  char operatStr[100];
  memset(operatStr, 0, sizeof(char) * 100);
  sprintf(operatStr, "%lf", get_operand1());
  gtk_text_buffer_set_text(op->text_buffer, operatStr, -1 );
  fflush(stdout);
}


void print_results( GtkTextBuffer * text_buffer)
{
  char res[100];
  sprintf(res, "%0.2lf", get_result());
  gtk_text_buffer_set_text(text_buffer, res, -1);
  fflush(stdout);
}

