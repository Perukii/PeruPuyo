
#include "../PeruGTK/include.h"


peruHost mainHost;

static gboolean
keyEvent(GtkWidget * widget, GdkEventKey * event, gpointer user_data){
     //std::cout<<event->keyval<<std::endl;
}

static gboolean
drawEvent(GtkWidget * widget, cairo_t * cr, gpointer data){

}


static gboolean
loopEvent(GtkWidget * widget){
     //gtk_widget_queue_draw(widget);
     return true;
}


int main(int _argc, char ** _argv){
     gtk_init(&_argc, &_argv);

     mainHost.setup("style.css");
     mainHost.setDefaultSize(300,300);
     g_signal_connect(mainHost.window, "key-press-event"    , G_CALLBACK(keyEvent) , NULL);
     g_signal_connect(mainHost.canvas, "draw"               , G_CALLBACK(drawEvent), NULL);
     g_timeout_add(1, (GSourceFunc)loopEvent, mainHost.canvas);

     mainHost.run();
}