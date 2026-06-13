#include "BattleField.h"
//!-----------------------------------------------------
// CLASS BattleField
//!-----------------------------------------------------
BattleField::BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                         const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                         const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone)
    : n_rows(n_rows), n_cols(n_cols),terrain(nullptr)
{
    if (this->n_rows <=0 || this -> n_cols <=0){
        this -> n_rows =0;
        this -> n_cols =0;
        return;
    }
    terrain = new TerrainElement**[n_rows];
    for (int i=0; i< n_rows;i++){
        terrain[i] = new TerrainElement *[n_cols];
        // Khởi tạo giá trị ban đầu cho ma trạn 
        for (int j= 0;j<n_cols;j++){
            terrain[i][j] =  nullptr;
        }
    }
   attachTerrainEffect(arrayForest, Location:: forest);
   attachTerrainEffect(arrayRiver, Location:: river);
   attachTerrainEffect(arrayFortification, Location:: fortification);
   attachTerrainEffect(arrayUrban, Location:: urban);
   attachTerrainEffect(arraySpecialZone, Location:: SpecialArea);
   // Ngoài các yêu tố trong mảng trên đều lsf đường mòn
   for (int i=0;i<n_rows;i++){
        for (int j=0;j<n_cols;j++){
            if (terrain[i][j] == nullptr) terrain[i][j] = new Road(Position(i,j));
        }
   }
}

BattleField::~BattleField() {
    if (!terrain) return;
    // Nếu terrainđã là nullptr thì ko cần xóa 
    for (int i=0;i<n_rows;i++){
        for (int j=0;j<n_cols;j++){
            delete terrain [i][j];
        }
        delete [] terrain[i];
    }
    delete [] terrain; //Xóa các mục terrain 
}

TerrainElement* BattleField::getElement(int r, int c) const {
        // Kiểm tra nếu ko  nằm trong tiền tuyến chiến đấu
        if (! isInsideMap(r,c)) return nullptr;
        return terrain[r][c]; // Lây vị trí của r và c trỏ đễn con trỏ thích hợp

}
// Kiểm tra xem nhân tố có nằm trên bản đồ hay không 
bool BattleField:: isInsideMap(int row, int col) const{
        return (row>= 0 && col>=0 && row <n_rows && col < n_cols);
}

string BattleField::str() const {
    stringstream ss;
    ss<<"BattleField[n_rows="<<this-> n_rows <<",n_cols="<< this -> n_cols <<"]";
    return ss.str();
}
void BattleField::attachTerrainEffect (const vector <Position*> & positions,Location type){
    for (Position* pos : positions){
        int row = pos-> getRow();
        int col = pos -> getCol();
        if (!isInsideMap(row,col)   || terrain [row][col]  != nullptr) continue;
        switch (type){
            case Location :: forest : terrain [row][col] = new Mountain(*pos);
            break;
            case Location::river: terrain [row][col] = new River(*pos);
            break;
            case Location :: fortification: terrain [row][col] = new Fortification(*pos);
            break;
            case Location:: urban: terrain[row][col] = new Urban(*pos);
            break;
            case Location:: SpecialArea: terrain [row][col] = new SpecialZone(*pos);
            break;
            default: break;
        }
    }
}