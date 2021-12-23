#include <gtk/gtk.h>

static void cb_button(GtkWidget *widget, gpointer user_data) {
    //ボタンのクリックで"Hello World"の文字列を受け取り、標準出力へ表示
    g_print("%s\n", (gchar*)user_data);
}

static void destroy_data(gpointer user_data, GClosure *closure) {
  //プログラムの終了でコールバック関数も終了
  g_print("Destroy the callback function data.\n");
  g_print("The value of the destroyed data = '%s'\n", (gchar*)user_data);
  //"Hello World"の文字列用に確保していた領域を解放
  g_free((gchar*)user_data);
}

int main (int argc, char **argv){
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "地図システム Ver 20.01");
    gtk_widget_set_size_request(window, 900, 500);

    GtkWidget *button = gtk_button_new_with_label("Click here");
    gtk_container_add(GTK_CONTAINER(window), button);

    //"Hello World"の文字列をボタンクリック用に格納（g_strdupで領域確保）
    g_signal_connect_data(G_OBJECT(button), "clicked", G_CALLBACK(cb_button), 
        (gpointer*)g_strdup("Hello World"), destroy_data, (GConnectFlags)0);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
