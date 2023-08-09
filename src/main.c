#include "../headers/gtk_interface.h"






int main(int argc, char **argv)
{

  GtkApplication * TestApp;

  TestApp = gtk_application_new("id.TestApp.test", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(TestApp, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(TestApp), argc, argv);

  g_object_unref(TestApp);
  
  return status;

} 