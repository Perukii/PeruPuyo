


class puyoAnim{
public:
      int loopTime;
      double disy,gv=0;

      puyoAnim(double _disy=0):disy(_disy){
            loopTime=0;
      }

      void process(){
            loopTime++;
            if(disy){
                  gv+=PERUPUYO_GRAVITY_SIZE;
                  disy+=gv;
                  if(disy>0){
                        disy=0;
                  }
                  
            }
            else{
                  gv=0;
            }
      }
      
};