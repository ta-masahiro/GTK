#include <gtk/gtk.h>

int main (int argc, char *argv[]) {
  GtkWidget *wnd; // ウィジェットを格納するためのポインタ変数を宣言。
  
  gtk_init(&argc, &argv); // GTKの初期化

  /* ウィンドウを作成 */
  wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL); // ここでウィンドウを作成
  gtk_window_set_title(GTK_WINDOW(wnd), "ウィンドウ"); // ウィンドウのタイトル名として「ウィンドウ」と命名

  /*  表示することを設定 */
  gtk_widget_show_all(wnd);

  /*  メインループ */
  gtk_main ();
  return 0;
}
