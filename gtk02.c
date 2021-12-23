#include <gtk/gtk.h>

int main (int argc, char **argv){
   gtk_init(&argc, &argv); // GTKの初期化

   /* ウィンドウ、GtkFixedなど各種ウィジェットを作成 */
   GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   GtkWidget *fixed  = gtk_fixed_new();
   GtkWidget *button = gtk_button_new_with_label("aaa");
   GtkWidget *label  = gtk_label_new("bbb");

   /* GtkFixedをウィンドウにパック */
   gtk_container_add(GTK_CONTAINER(window), fixed);

   /* GtkFixed内の(100,100)にボタンを置き、(200,200)にラベルを配置 */
   gtk_fixed_put(GTK_FIXED(fixed), button, 100,100);
   gtk_fixed_put(GTK_FIXED(fixed), label, 200,200);

   gtk_widget_show_all(window);
   gtk_main();
   return 0;
}
