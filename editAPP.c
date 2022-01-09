#include <gtk/gtk.h>

void        new_file        ();
void        open_file       ();
void        save_file       ();
void        change_buffer   ();
void        closin_buffer   ();
void        comfirm_save    ();
GObject     *window;
gint        edited = FALSE;
char        *filename       =   "";
 
    /*  New file        */
void new_file(GtkWidget *widget, gpointer buffer)
{
    if (edited) comfirm_save(buffer);
    
    filename    =   "Untitled";
    gtk_text_buffer_set_text        (buffer, "", -1);
    gtk_window_set_title            (GTK_WINDOW(window), filename    );
    edited      =   FALSE;
}
 
    /*  Open file       */      // GTK_FILE_CHOOSER_ACTION_OPEN    0
                                // GTK_FILE_CHOOSER_ACTION_SAVE    1
                                // GTK_RESPONSE_ACCEPT            -3
                                // GTK_RESPONSE_CANCEL            -6
void open_file(GtkWidget *widget, gpointer buffer)
{
    if (edited) comfirm_save(buffer);
    
    GtkWidget   *dialog;
    gint        result;
    dialog  = gtk_file_chooser_dialog_new
                                    ("Open File", GTK_WINDOW(window),
                                     GTK_FILE_CHOOSER_ACTION_OPEN, 
                                     "Cancel", GTK_RESPONSE_CANCEL,
                                     "Open", GTK_RESPONSE_ACCEPT,
                                     NULL);
    result  = gtk_dialog_run        (GTK_DIALOG(dialog)              );
    if (result == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser  *chooser;
        FILE            *fp;
        char            str[256];
        GtkTextIter     iter;
        chooser     = GTK_FILE_CHOOSER(dialog);
        filename    = gtk_file_chooser_get_filename(chooser);
        gtk_text_buffer_set_text(buffer, "", -1);
        
        fp          = fopen(filename, "r");
        if (fp != NULL)
        {
            while ((fgets(str, 256, fp)) != NULL)
            {
                gtk_text_buffer_get_end_iter(buffer, &iter);
                gtk_text_buffer_insert(buffer,&iter,str,-1);
                edited  =   FALSE;
            }
        } else {
            gtk_text_buffer_set_text(buffer, "error", -1);
        }
        fclose(fp);
        gtk_window_set_title        (GTK_WINDOW(window), filename    );
    }
    gtk_widget_destroy(dialog);
}

    /*  Save file       */
void save_file(GtkWidget *widget, gpointer buffer)
{
    gchar       *text;
    GtkTextIter startiter;
    GtkTextIter enditer;
    FILE        *fp;
    if (edited && strcmp("Untitled", filename))
    {
        fp  =   fopen(filename, "w");
        if (fp != NULL)
        {
            gtk_text_buffer_get_start_iter  (buffer, &startiter );
            gtk_text_buffer_get_end_iter    (buffer, &enditer   );
            text    =   gtk_text_buffer_get_text
                                            (buffer, &startiter,
                                             &enditer, FALSE    );
            fprintf(fp, "%s", text);
            edited  =   FALSE;
        gtk_window_set_title        (GTK_WINDOW(window), filename    );
        } else {
            gtk_text_buffer_set_text        (buffer, "error", -1);
        }
        fclose(fp);
        g_free(text);
    } else if (edited) {
        GtkWidget       *dialog;
        GtkFileChooser  *chooser;
        gint            result;
        dialog  =   gtk_file_chooser_dialog_new
                                    ("Save File", GTK_WINDOW(window),
                                     GTK_FILE_CHOOSER_ACTION_SAVE,
                                     "Cancel", GTK_RESPONSE_CANCEL,
                                     "Save", GTK_RESPONSE_ACCEPT,
                                     NULL);
        chooser =   GTK_FILE_CHOOSER(dialog);
        gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE );
        gtk_file_chooser_set_current_name(chooser, "Untitled"        );
           
        result  =   gtk_dialog_run(GTK_DIALOG(dialog));
        if (result == GTK_RESPONSE_ACCEPT)
        {
            GtkFileChooser  *chooser;
            chooser     =   GTK_FILE_CHOOSER(dialog);
            filename    =   gtk_file_chooser_get_filename(chooser);
            fp          =   fopen(filename, "w");
            if (fp != NULL)
            {
                gtk_text_buffer_get_start_iter  (buffer, &startiter );
                gtk_text_buffer_get_end_iter    (buffer, &enditer   );
                text    =   gtk_text_buffer_get_text
                                                (buffer, &startiter,
                                                 &enditer, FALSE    );
                fprintf(fp, "%s", text);
                edited  =   FALSE;
                gtk_window_set_title    (GTK_WINDOW(window), filename);
            } else {
                gtk_text_buffer_set_text        (buffer, "error", -1);
            }
            fclose(fp);
            g_free(text);
        }
        gtk_widget_destroy(dialog);
    }
}

    /*  Change buffer   */
void change_buffer(GtkTextBuffer *buffer)
{
    if (!edited)
    {
        if (!(strcmp(filename, "")))
        {
            filename    =   "Untitled";
        }
        char   title[256];
        sprintf(title, "%s - edited", filename);
        gtk_window_set_title    (GTK_WINDOW(window), title);
        edited  =   TRUE;
    }
}

    /*  Closing buffer  */
void closin_buffer(GtkWidget *widget, gpointer buffer)
{
    if (edited) comfirm_save(buffer);
    gtk_main_quit();
}

void comfirm_save(gpointer buffer)
{
    gint    result;
    GtkWidget   *dialog;
    dialog  =   gtk_message_dialog_new
                                    (GTK_WINDOW(window),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_QUESTION,
                                     GTK_BUTTONS_YES_NO,
                        "This file has changed. Do you want to save?"
                                    );
    gtk_window_set_title            (GTK_WINDOW(dialog),
                                     filename);
    result  =   gtk_dialog_run      (GTK_DIALOG(dialog));
    gtk_widget_destroy              (dialog);
    if (result == GTK_RESPONSE_YES) save_file(GTK_WINDOW(window), buffer);
}
int main(int argc, char*argv[]){
  GtkBuilder *builder;
// GObject *window;
 
GtkTextBuffer   *buffer;
  gtk_init(&argc,&argv);
 
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "editAPP.glade", NULL);
  gtk_builder_connect_signals(builder, NULL);
  window = gtk_builder_get_object(builder, "windows");
  gtk_widget_show_all(GTK_WIDGET(window));
    /*  Events          */
    g_signal_connect                (window,   "on_newitem_activate",
                                     G_CALLBACK(new_file),     buffer);
    g_signal_connect                (window,  "on_openitem_activate",
                                     G_CALLBACK(open_file),    buffer);
    g_signal_connect                (window,  "on_saveitem_activate",
                                     G_CALLBACK(save_file),    buffer);
    g_signal_connect                (window,    "on_saveasitem_activiate",
                                     G_CALLBACK(change_buffer), NULL );
    g_signal_connect                (window,  "on_quititem_activate",
                                     G_CALLBACK(closin_buffer),buffer);
    g_signal_connect                (window,    "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL );
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_main();
 
  return 0;
}
