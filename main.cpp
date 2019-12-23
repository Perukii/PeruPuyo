
#include "PeruGTK/include.h"

peruHost mainHost;

#define PERUPUYO_TABLE_W 6
#define PERUPUYO_TABLE_H 13
#define PERUPUYO_NEXT    3
#define PERUPUYO_TYPE_NUM 4
#define PERUPUYO_KEY_UPDATE 10
#define PERUPUYO_ERASE_TERM 4
#define PERUPUYO_GRAVITY_SIZE 0.2

#define _X(X) mainHost.getPosFromCurrentSizeX(X)
#define _Y(Y) mainHost.getPosFromCurrentSizeY(Y)
#define PERUPUYO_MODE nazoperu

#include <random>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

std::random_device rd;

#include "uf.h"
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