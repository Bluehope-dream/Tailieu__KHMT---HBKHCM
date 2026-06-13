#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "main.h"
#include "Position.h"
#include "Unit.h"
#include "Vehicle.h"
#include "Infantry.h"
//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------
 
class Configuration {
private:
    enum class InforInput{
        NUM_ROWS, NUM_COLS, ARRAY_FOREST,ARRAY_RIVER,ARRAY_FORTIFICATION,ARRAY_URBAN,ARRAY_SPECIAL_ZONE,UNIT_LIST,EVENT_CODE
    };
    int num_rows;
    int num_cols;
    vector<Position*> arrayForest;
    vector<Position*> arrayRiver;
    vector<Position*> arrayFortification;
    vector<Position*> arrayUrban;
    vector<Position*> arraySpecialZone;
    // Các mảng đơn vị quân được để trống (stub) trong phần hiện thực mẫu
    vector<Unit*> liberationUnits;  // Đối với vector thì tự đọng khai báo cho nó đã là rỗng rồi 

    vector<Unit*> ARVNUnits;
    int eventCode;
    int LibertyUnitNum ;
    int ARVNUnitNum ;
        // Lưu ý đối với switch thì expression chỉ có kiểu dữ liệu là int hoặc enum mà thôi !!!!!!!!!!!!
    //  InforInput mapkey(const string &infor);
  
public:
   
    Configuration(const string & filepath);  // Constructor nhận vào đường dẫn truy cập file path để đọc lấy thông tin nưaz chứ
    ~Configuration();  // Loại bỏ các tài nguyên cần thiết 
    string str() const;
   
  
    // Hint: You can add more or other methods to access the private members if needed.
    int getNumRows() const { return num_rows; }
    int getNumCols() const { return num_cols; }
    const vector<Position*>& getForestPositions() const { return arrayForest; }
    const vector<Position*>& getRiverPositions() const { return arrayRiver; }
    const vector<Position*>& getFortificationPositions() const { return arrayFortification; }
    const vector<Position*>& getUrbanPositions() const { return arrayUrban; }
    const vector<Position*>& getSpecialZonePositions() const { return arraySpecialZone; }
    int getEventCode() const { return eventCode; }
    int getLibertyUnitNum(){  return LibertyUnitNum; }
    int getARVNUnitNum(){    return ARVNUnitNum; }
    vector<Unit*>& getLiberationUnits() { return liberationUnits; }
    vector<Unit*>& getARVNUnits() { return ARVNUnits; }
    static string trim(const string &s) ;  // Hàm để cắt chuỗi đầu để lấy thông tin xử lý thông tin
    string  deleteSpace(const string &s); // Hàm xóa khoảng trắng trong chuỗi 
    // Hàm lấy vị trí của đối tượng trong trận địa 
    string printPositionArray (vector<Position*> arrayPosition) const;
    string printUnitArr(vector<Unit*>, int ) const; // Đọc cái chuỗi thông tin về các đơn vị Unit của các đơn vị tham chiến  
    void releaseVector(vector<Position*>);
    void releaseVector (vector<Unit*> );
    void mergeLine (string line,string &arrName,string key,bool &flag);
    int getUnitType(string name); // ĐỌC DỮ LIỆU LẤY TÊN CỦA ĐƠN VỊ UNIT 
    // Phương thức đọc các chỉ số vị trí (x,y) của Position
    void readPositionVector(vector<Position*>&, string &);  // Hàm đọc các mảng vector Position cho các đơn vị Position
    void readUnitVector(vector<Unit*>&, vector<Unit*>&, const string &);          // Hàm đọc các mảng vector cho 2 đơn vị quân sự Unit Vector
    bool isInfantry (const string &name );
    bool isVehicle  (const string & name );
};

#endif