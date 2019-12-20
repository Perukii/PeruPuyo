


pRGB pallete[]={
     pRGB(1.0,1.0,1.0,0.0),
     pRGB(0.0,0.0,0.0,0.2),
     pRGB(1.0,0.0,0.0),
     pRGB(0.0,1.0,0.0),
     pRGB(0.0,0.0,1.0),
     pRGB(0.0,0.0,0.0)
};

#define PERUPUYO_TABLE_W 6
#define PERUPUYO_TABLE_H 13
#define PERUPUYO_NEXT    3
#define PERUPUYO_TYPE_NUM 3
#define PERUPUYO_KEY_UPDATE 10

class puyoSet{
private:
     int anglx[4]={0,1,0,-1};
     int angly[4]={1,0,-1,0};
public:
     int table[PERUPUYO_TABLE_H][PERUPUYO_TABLE_W];
     int readyPuyo[PERUPUYO_NEXT*2],cPuyo[2];
     int phase,lptime;
     double sx,sy,w,h,blockSize;
     double cpx,cpy;
     int cangl;

     puyoSet(){}

     void setup(double _sx, double _sy, double _h){
          sx = _sx;
          sy = _sy;
          h  = _h ;
          blockSize = h/(double)PERUPUYO_TABLE_H;
          w         = blockSize*(double)PERUPUYO_TABLE_W;
          for(int y=0;y<PERUPUYO_TABLE_H;y++){
               for(int x=0;x<PERUPUYO_TABLE_W;x++){
                    table[y][x]=y==0;
               }
          }
          phase     = 0;
          lptime    = 0;
          for(int i=0;i<PERUPUYO_NEXT*2;i++){
               readyPuyo[i]=rd()%PERUPUYO_TYPE_NUM+2;
          }
          nextPhase(true);
     }

     void drawPuyoSet(cairo_t * cr){
          // background
          peruDrawRect(cr,sx,sy,w,h,pRGB(0,0,0,0.1));

          // stayed puyo
          for(int y=0;y<PERUPUYO_TABLE_H;y++){
               for(int x=0;x<PERUPUYO_TABLE_W;x++){
                    peruDrawRect(cr,sx+blockSize*x,sy+blockSize*y,blockSize,blockSize,pallete[table[y][x]]);
               }
          }

          // reserved puyo
          for(int i=0;i<PERUPUYO_NEXT;i++){
               for(int j=0;j<2;j++){
                    peruDrawRect(cr,
                         sx+blockSize*(PERUPUYO_TABLE_W+1),
                         sy+blockSize*(i*2.1+j),
                         blockSize,blockSize,pallete[readyPuyo[i*2+j]]);
               }
          }

          // controling puyos
          for(int i=0;i<2;i++){
               peruDrawRect(cr,
                    sx+blockSize*(cpx+i*anglx[cangl]),
                    sy+blockSize*(cpy+i*angly[cangl]),
                    blockSize,blockSize,pallete[cPuyo[i]]);
          }

     }

     void nextPhase(bool first=false){


          // put controled puyos
          
          for(int i=0;i<2;i++){
               if(phase)table[int(cpy)+i*int(angly[cangl])][int(cpx)+i*int(anglx[cangl]) ]=cPuyo[i];
               cPuyo[i]=readyPuyo[i];
          }

          phase++;
          cpx=2;
          cpy=0;
          cangl=0;
          
          //cPuyo[1]=readyPuyo[1];
          if(!first){
               for(int i=0;i<PERUPUYO_NEXT;i++){
                    for(int j=0;j<2;j++){
                         readyPuyo[i*2+j]= i==PERUPUYO_NEXT-1 ?
                              rd()%PERUPUYO_TYPE_NUM+2:
                              readyPuyo[(i+1)*2+j];
                    }
               }
          }

     }


     bool checkFloor(){
          return    cpy<PERUPUYO_TABLE_H-1
                and angly[cangl]+cpy<PERUPUYO_TABLE_H-1;
     }

     bool checkWall(){ 
          return    cpx>=0 
                and cpx<PERUPUYO_TABLE_W
                and anglx[cangl]+cpx>=0 
                and anglx[cangl]+cpx<PERUPUYO_TABLE_W;
     }


     void process(){
          cpy+=0.03;
          if(!checkFloor())nextPhase();
     }

     void varyAngl(short _ap){
          int bcangl=cangl;
          cangl=(cangl+_ap+4)%4;
          if(!checkWall())cangl=bcangl;
     }

     void varyPos(short _pp){
          cpx+=_pp;
          if(!checkWall())cpx-=_pp;
     }

};


