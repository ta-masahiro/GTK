#include <gtk/gtk.h>
 
int main(int argc, char*argv[]){
  GtkBuilder *builder;
  GObject *window1;
 
  gtk_init(&argc,&argv);
 
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "myapp.glade", NULL);
  gtk_builder_connect_signals(builder, NULL);
  window1 = gtk_builder_get_object(builder, "window1");
  gtk_widget_show_all(GTK_WIDGET(window1));
  g_signal_connect(window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_main();
 
  return 0;
}
