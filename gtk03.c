#include <gtk/gtk.h>

int main (int argc, char **argv){
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "地図システム Ver 20.01");
    gtk_widget_set_size_request(window, 900, 500);

    GtkWidget *fixed  = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    GtkWidget *label     = gtk_label_new("bbb");
    GtkWidget *btnMenu   = gtk_button_new_with_label("メニュー");
    GtkWidget *btnZoomUp = gtk_button_new_with_label("＋");
    GtkWidget *btnZoomDn = gtk_button_new_with_label("－");
    GtkWidget *image = gtk_image_new_from_file("/media/sf_gis20/tile/osm_jit/17/116030/51818.png");

    gtk_fixed_put(GTK_FIXED(fixed), label,    200,200);
    gtk_fixed_put(GTK_FIXED(fixed), btnMenu,   10, 20);
    gtk_fixed_put(GTK_FIXED(fixed), btnZoomUp, 10, 60);
    gtk_fixed_put(GTK_FIXED(fixed), btnZoomDn, 10,100);
    gtk_fixed_put(GTK_FIXED(fixed), image,  250, 300);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
