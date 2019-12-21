

pRGB pallete[]={
     pRGB(1.0,1.0,1.0,0.0),
     pRGB(0.0,0.0,0.0,0.2),
     pRGB(1.0,0.0,0.0),
     pRGB(0.0,1.0,0.0),
     pRGB(0.0,0.0,1.0),
     pRGB(0.0,0.0,0.0)
};




class puyoSet{
private:
     int anglx[4]={0,1,0,-1};
     int angly[4]={1,0,-1,0};
public:
     int table[PERUPUYO_TABLE_H][PERUPUYO_TABLE_W]; // table size
     int readyPuyo[PERUPUYO_NEXT*2],cPuyo[2]; // color (readyPuyo: reserved puyos, cPuyo: controling puyos)
     int phase; // phase:phase
     double sx,sy,w,h,blockSize; // draw property
     double cpx,cpy; // controling puyo location
     bool boost; // puyospeed boost i/o
     double speed=0.005,bstspeed=0.2; // puyospeed (speed:default, bstspeed:boosted speed)
     int cangl; // angl of controling puyos
     int pushingTime, lpTime; //
     int pushingTimeLimit=100,lpTimeLimit=1500;
     PPUF uf;

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
          phase      = 0;
          pushingTime= 0;
          boost      = false;
          lpTime     = 0;
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

     void sortTable(){ //
          for(int ix=0;ix<PERUPUYO_TABLE_W;ix++){
               int voids=0;
               for(int iy=PERUPUYO_TABLE_H-1;iy>=0;iy--){
                    if(table[iy][ix]<2)voids++;
                    else{
                         table[iy+voids][ix]=table[iy][ix];
                         if(voids)table[iy][ix]=0;
                    }
               }
          }
     }

     void chainLoop(int _chain){
          sortTable();
          uf.setup();
          for(int iy=0;iy<PERUPUYO_TABLE_H;iy++){
               for(int ix=0;ix<PERUPUYO_TABLE_W;ix++){
                     
                    if(ix>0 and table[iy][ix]==table[iy][ix-1])uf.unite(
                          std::make_pair(ix,iy),std::make_pair(ix-1,iy));
                  
                    if(iy>0 and table[iy][ix]==table[iy-1][ix])uf.unite(
                          std::make_pair(ix,iy),std::make_pair(ix,iy-1));
                    
               }
          }

          int groups=0;
          std::cout<<"chain"<<_chain<<" : ";
          for(int iy=0;iy<PERUPUYO_TABLE_H;iy++){
               for(int ix=0;ix<PERUPUYO_TABLE_W;ix++){
                     std::pair<int,int> rt=uf.root(uf.table[iy][ix].first);
                     if(uf.table[rt.second][rt.first].second>=PERUPUYO_ERASE_TERM
                          and table[iy][ix]>=2){
                           table[iy][ix]=0;
                           if(iy==rt.second and ix==rt.first){
                                groups++;
                                std::cout<<ix<<":"<<iy<<"["<<uf.table[iy][ix].second<<"],";
                           }
                     }
                    
               }
          }
          if(groups==0)std::cout<<"none";
          std::cout<<std::endl;

          if(groups){
                chainLoop(++_chain);
          }
     }

     void nextPhase(bool first=false){ // 

          // put controled puyos
          for(int i=0;i<2;i++){
               if(!first)table[int(cpy)+i*int(angly[cangl])][int(cpx)+i*int(anglx[cangl]) ]=cPuyo[i];
               cPuyo[i]=readyPuyo[i];
          }

          phase++;
          lpTime = 0;
          cpx    = 2;
          cpy    = 0;
          cangl  = 0;

          
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

          chainLoop(1);



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

     bool checkPuyoCollision(){
          return    table[int(cpy)+1][int(cpx)]<2
                and table[int(cpy)+int(angly[cangl])+1][int(cpx)+int(anglx[cangl]) ]<2;
     }

     bool checkPuyoSideCollision(int _bcangl){ // onry cangl=0
          return    (_bcangl==3 and table[int(cpy)+int(angly[cangl])+1][int(cpx)+int(anglx[cangl]-1) ]<2)
                or  (_bcangl==1 and table[int(cpy)+int(angly[cangl])+1][int(cpx)+int(anglx[cangl]+1) ]<2);
     }


     void process(){
          cpy+=boost ? bstspeed : speed;
          lpTime++;
          //std::cout<<lpTime<<std::endl;
          if(!checkFloor() or !checkPuyoCollision()){
                pushingTime++;
                if(pushingTime>pushingTimeLimit  or lpTime>lpTimeLimit){
                      pushingTime=0;
                      nextPhase();
                }
                cpy=floor(cpy)-0.000001;
          }
          
     }

     void varyAngl(short _ap){
          int bcangl=cangl;
          cangl=(cangl+_ap+4)%4;
          if(cangl!=0 or lpTime>lpTimeLimit){
               if(!checkFloor() or !checkWall() or !checkPuyoCollision()){
                    cangl=bcangl;
               }
          }
          else{
                if(!checkFloor() or !checkWall() or !checkPuyoCollision() or !checkPuyoSideCollision(bcangl)){
                    cpy-=1;
                }
          }

     }

     void varyPos(short _pp){
          cpx+=_pp;
          if(!checkWall() or !checkPuyoCollision())cpx-=_pp;
     }

};


