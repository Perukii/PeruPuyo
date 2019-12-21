

class PPUF{
public:
     std::pair<std::pair<int,int>,int> table[PERUPUYO_TABLE_H][PERUPUYO_TABLE_W];  //parent/size
     //bool eraseable[PERUPUYO_TABLE_H][PERUPUYO_TABLE_W];

     PPUF(){};

     void setup(){
          
          for(int iy=0;iy<PERUPUYO_TABLE_H;iy++){
               for(int ix=0;ix<PERUPUYO_TABLE_W;ix++){
                    table[iy][ix]=std::make_pair(std::make_pair(ix,iy),1);
                    //eraseable[iy][ix]=false;
               }
          }
     }

     void debug(){
          std::cout<<"==================="<<std::endl;
          for(int iy=0;iy<PERUPUYO_TABLE_H;iy++){
               for(int ix=0;ix<PERUPUYO_TABLE_W;ix++){
                    
                    //std::cout<<eraseable[iy][ix]<<" ";
               }
               std::cout<<std::endl;
          }
     }

     std::pair<int,int> root(std::pair<int,int> _child){
          if(_child==table[_child.second][_child.first].first) return _child;
          else return root(table[_child.second][_child.first].first);
     }

     void unite(std::pair<int,int> _achild, std::pair<int,int> _bchild){
          std::pair<int,int> ra=root(_achild);
          std::pair<int,int> rb=root(_bchild);

          if(table[ra.second][ra.first].first==table[rb.second][rb.first].first)return;
          table[ra.second][ra.first].first  =  std::make_pair(_bchild.first, _bchild.second);
          table[rb.second][rb.first].second += table[ra.second][ra.first].second;
          //if(table[rb.second][rb.first].second>=PERUPUYO_ERASE_TERM)eraseable[rb.second][rb.first]=true;
     }
     
};

/*
struct UnionFind {
     std::vector<int> par; // par[i]:iの親の番号　(例) par[3] = 2 : 3の親が2

     UnionFind(int N) : par(N) { //最初は全てが根であるとして初期化
          for(int i = 0; i < N; i++) par[i] = i;
     }

     int root(int x) { // データxが属する木の根を再帰で得る：root(x) = {xの木の根}
          if (par[x] == x) return x;
          return par[x] = root(par[x]);
     }

     void unite(int x, int y) { // xとyの木を併合
          int rx = root(x); //xの根をrx
          int ry = root(y); //yの根をry
          if (rx == ry) return; //xとyの根が同じ(=同じ木にある)時はそのまま
          par[rx] = ry; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
     }

     bool same(int x, int y) { // 2つのデータx, yが属する木が同じならtrueを返す
          int rx = root(x);
          int ry = root(y);
          return rx == ry;
     }
};
*/