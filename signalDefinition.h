
static gboolean
keyEvent(GtkWidget * widget, GdkEventKey * event, gpointer user_data){
     //std::cout<<event->keyval<<std::endl;
     //mainHost.setCurrentPos(100,100);
}

static gboolean
drawEvent(GtkWidget * widget, cairo_t * cr, gpointer data){
     nazoperu::draw(cr);
}        

static gboolean mouseMoveEvent(GtkWidget *widget,GdkEvent *event, gpointer user_data) {

}