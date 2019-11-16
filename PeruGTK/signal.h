
static gboolean quitEvent     (GtkWidget * widget, GdkEventKey * event, gpointer user_data){
     gtk_main_quit();
}
static gboolean keyEvent      (GtkWidget * widget, GdkEventKey * event, gpointer user_data);
static gboolean drawEvent     (GtkWidget * widget, cairo_t * cr, gpointer data);
static gboolean mouseMoveEvent(GtkWidget *widget,GdkEvent *event, gpointer user_data);

static gboolean loopEvent(GtkWidget * widget);

