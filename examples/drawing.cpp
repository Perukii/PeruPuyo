
#include "../PeruGTK/include.h"


peruHost mainHost;
peruText ptext("sample", pRGB(0.5,0.5,1,0.5));

static gboolean
keyEvent(GtkWidget * widget, GdkEventKey * event, gpointer user_data){
     //std::cout<<event->keyval<<std::endl;
}

static gboolean
drawEvent(GtkWidget * widget, cairo_t * cr, gpointer data){
     ptext.draw(cr,40,40,100);
     peruSetColor(cr,pRGB(1.0,0.5,0.5,1));
     peruDrawImage(cr, "/home/tlllune/ピクチャ/langton.png");
     cairo_rectangle(cr, 100, 100, 100, 100);
     cairo_fill(cr);
}

double t=0;

static gboolean
loopEvent(GtkWidget * widget){
     gtk_widget_queue_draw(widget);
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