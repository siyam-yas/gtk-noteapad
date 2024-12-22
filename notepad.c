#include <gtk/gtk.h>
#include <pango/pango.h>

GtkWidget *textview;

void on_new_file(GtkWidget *widget, gpointer data) {
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview)), "", -1);
}

void on_open_file(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(data), GTK_FILE_CHOOSER_ACTION_OPEN,
                                                   "_Cancel", GTK_RESPONSE_CANCEL,
                                                   "_Open", GTK_RESPONSE_ACCEPT, NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        GError *error = NULL;
        gchar *content = NULL;
        g_file_get_contents(filename, &content, NULL, &error);
        
        if (content) {
            gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview)), content, -1);
            g_free(content);
        }
        g_free(filename);
    }
    
    gtk_widget_destroy(dialog);
}

void on_save_file(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(data), GTK_FILE_CHOOSER_ACTION_SAVE,
                                                   "_Cancel", GTK_RESPONSE_CANCEL,
                                                   "_Save", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        GError *error = NULL;
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
        GtkTextIter start, end;
        gtk_text_buffer_get_start_iter(buffer, &start);
        gtk_text_buffer_get_end_iter(buffer, &end);
        gchar *content = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        
        g_file_set_contents(filename, content, -1, &error);
        
        if (error) {
            g_warning("Error saving file: %s", error->message);
            g_error_free(error);
        }

        g_free(content);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void on_font_change(GtkWidget *widget, gpointer data) {
    GtkTextView *textview = GTK_TEXT_VIEW(data);

    GtkFontChooser *font_chooser = GTK_FONT_CHOOSER(widget);
    const gchar *font_name = gtk_font_chooser_get_font(font_chooser);
    PangoFontDescription *font_desc = pango_font_description_from_string(font_name);

    gtk_widget_override_font(GTK_WIDGET(textview), font_desc);
    pango_font_description_free(font_desc);
}

GtkWidget* create_main_window() {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *scrolled_window;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Notepad");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, 
        "window {"
        "  background-color: #f4f4f4;"
        "  border-radius: 12px;"
        "  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);"
        "}"
        "GtkButton {"
        "  border-radius: 8px;"
        "  padding: 8px 12px;"
        "  background-color: #4CAF50;"
        "  color: white;"
        "}"
        "GtkButton:hover {"
        "  background-color: #45a049;"
        "}"
        "GtkTextView {"
        "  background-color: #ffffff;"
        "  font-family: 'Poppins';"
        "  font-size: 14px;"
        "  border-radius: 8px;"
        "}"
        , -1, NULL);
    
    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *menu_bar = gtk_menu_bar_new();
    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *file_item = gtk_menu_item_new_with_label("File");
    GtkWidget *open_item = gtk_menu_item_new_with_label("Open");
    GtkWidget *save_item = gtk_menu_item_new_with_label("Save");
    GtkWidget *new_item = gtk_menu_item_new_with_label("New");
    
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);
    
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_item);
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 0);

    g_signal_connect(new_item, "activate", G_CALLBACK(on_new_file), window);
    g_signal_connect(open_item, "activate", G_CALLBACK(on_open_file), window);
    g_signal_connect(save_item, "activate", G_CALLBACK(on_save_file), window);

    textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), textview);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);
    
    GtkWidget *font_button = gtk_font_button_new();
    gtk_box_pack_start(GTK_BOX(vbox), font_button, FALSE, FALSE, 0);
    
    g_signal_connect(font_button, "font-set", G_CALLBACK(on_font_change), textview);

    gtk_widget_show_all(window);

    return window;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = create_main_window();

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return 0;
}
