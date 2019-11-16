
#include "PeruGTK/include.h"

peruHost mainHost;

#define _X(X) mainHost.getPosFromCurrentSizeX(X)
#define _Y(Y) mainHost.getPosFromCurrentSizeY(Y)

#include "perupuyo.h"
#include "nazoperu.h"
#include "signalDefinition.h"
#include <iostream>




static gboolean
loopEvent(GtkWidget * widget){
    gtk_widget_queue_draw(widget);
    return true;
}


int main(int _argc, char ** _argv){
    gtk_init(&_argc, &_argv);

    mainHost.setup("style.css");
    mainHost.setDefaultSize(800,800);
    mainHost.loop=3;
    
    mainHost.run();
}