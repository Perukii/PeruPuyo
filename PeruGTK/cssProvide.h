
void peruCssProvide(const char * _cssfile){
     GtkCssProvider * provider = gtk_css_provider_new ();
     GdkDisplay *     display;
     GdkScreen *      screen;

     display = gdk_display_get_default ();
     screen = gdk_display_get_default_screen (display);
     gtk_style_context_add_provider_for_screen (screen,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

     gsize bytes_written, bytes_read;
     const gchar * home = _cssfile;
     GError * error = 0;

     gtk_css_provider_load_from_path (provider,g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error),NULL);

     g_object_unref (provider);
}