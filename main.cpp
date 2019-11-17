
#include "PeruGTK/include.h"

peruHost mainHost;

#define _X(X) mainHost.getPosFromCurrentSizeX(X)
#define _Y(Y) mainHost.getPosFromCurrentSizeY(Y)
#define PERUPUYO_MODE nazoperu

#include <random>
#include <iostream>
#include <set>

std::random_device rd;

#include "perupuyo.h"
#include "nazoperu.h"
#include "signalDefinition.h"




int main(int _argc, char ** _argv){
    gtk_init(&_argc, &_argv);

    mainHost.setup("style.css");
    mainHost.setDefaultSize(800,800);
    PERUPUYO_MODE::puyoMain.setup(0,0,_Y(1));
    mainHost.loop=5;
    
    mainHost.run();
}