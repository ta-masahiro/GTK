#include <gtk/gtk.h>
int main(int argc, char **argv) {

  /* 数値計算の内容の記述 */
  gint xxx = 3;
  gint fff = 5;
  gint zzz = xxx + fff; // 計算内容

  gchar buf[100]; // 単なるバッファ（仲介）の文字列 変数。
  g_sprintf(
      buf, "計算結果は%d です。",
      zzz); // 置き換え内容の書式の定義。bufに格納された段階であり、まだ置き換えは実行していない。

  gtk_init(&argc, &argv);
  GtkWidget *window, *fixed, *label;

  /* ウィンドウ、GtkFixedなど各種ウィジェットを作成 */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  fixed = gtk_fixed_new();
  label = gtk_label_new("Hello, world! kubetu");

  gtk_label_set_text(GTK_LABEL(label), buf); // ラベルを上書きしている。

  /* GtkFixedをウィンドウにパック */
  gtk_container_add(GTK_CONTAINER(window), fixed);

  /* GtkFixed内の(10,20)にラベルを配置 */
  gtk_fixed_put(GTK_FIXED(fixed), label, 10, 20);

  /*  表示することを設定 */
  gtk_widget_show_all(window);

  /*  メインループ */
  gtk_main();
  return 0;
}
