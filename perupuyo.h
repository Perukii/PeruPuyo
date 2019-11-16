


pRGB pallete[]={
     pRGB(1.0,1.0,1.0),
     pRGB(0.0,0.0,0.0,0.2),
     pRGB(1.0,0.0,0.0),
     pRGB(0.0,1.0,0.0),
     pRGB(0.0,0.0,1.0),
     pRGB(0.0,0.0,0.0)
};

class puyoSet{
public:
     int table[14][8];

     puyoSet(){
          for(int y=0;y<14;y++){
               for(int x=0;x<8;x++){
                    table[y][x]=!(y%13 and x%7);
               }
          }
     }

     void drawPuyoSet(cairo_t * cr, double tableSizeY ,double _x=0, double _y=0){
          double blockSize = tableSizeY/14.0;
          for(int y=0;y<14;y++){
               for(int x=0;x<8;x++){
                    //table[y][x];
                    peruDrawRect(cr,_x+blockSize*x,_y+blockSize*y,blockSize*0.95,blockSize*0.95,pallete[table[y][x]]);
               }
          }
     }



};


