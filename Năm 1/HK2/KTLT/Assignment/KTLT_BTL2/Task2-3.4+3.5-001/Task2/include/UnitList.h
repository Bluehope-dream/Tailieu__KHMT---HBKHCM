#ifndef _H_UNITLIST_H_
#define _H_UNITLIST_H_

#include "Infantry.h"
#include "Vehicle.h"

class UnitList
{
public:
struct Node {
        Unit*unit;
        Node * next;
        Node (Unit*m):  unit(m),next(nullptr){}  // Khởi tạo cho các Node ban đầu 
    };
    UnitList(int capacity);     // Hàm constructor khởi tạo các giá trị 
    ~UnitList ();               // Hàm này dùng để xóa các danh sách trong linked LIST
    bool insert(Unit *unit);     // Hàm này chèn infantry và vehicle cho phù hợp
    // Hàm hỗ trợ chèn vào cuối danh sách cho Vehicle 
    void insertAtEnd (Unit * unit);
            void insertAtEndRaw(Unit* unit);
    // Sử dụng function overloading gọi hàm isContain
    vector<Unit *> getUnits() const;
    // Thực hiện đảm bảo xử lý danh sách trung gian tạo danh sách can thiệp sâu 
    Unit* deepCopyUnit(Unit* unit);
    string str() const;
     // Hàm kiểm tra xem nó thuộc trong sanh sách Vehicle hay là Infantry 
    bool isContain (VehicleType vehicleType);
    bool isContain (InfantryType infantryType);
    // * Additional functions if possible
    void remove(Unit *unit);
    Node* getHead() const { return head; }
    int getCapacity() const {return capacity ;}
    void setCapacity (int capacity){
        this -> capacity = capacity;
    }
    int getcountVehicle(){return countVehicle ;}
    void setcountVehicle (int countVehicle){
        this -> countVehicle = countVehicle;
    }
     int getcountInfantry(){return countInfantry ;}
    void setcountInfantry (int countInfantry){
        this -> countInfantry = countInfantry;
    }
    void setCurrSize (int currSize){ this -> currSize = currSize;}
    bool isSpecialNum(int val, int n);
    bool checkSpecialNumber(int val);
    // Hàm kiểm tra xem nó đã nằm trong Unit hay chưa 
    bool isContain(Unit *unit );
    // Hàm kiểm tra kiểu dữ liệu của Unit đưa vào 
    bool  isVehicleType(Unit *unit);
    bool  isInfantryType(Unit *unit);
    // Hàm tìm unit theo đơn vị Vehicle hoặc Infantry và Unit
    Unit* identifyUnit (Unit * unit);
    Unit* identifyUnit (InfantryType type);         // hàm tìm đơn vị unit theo infantry hỗ trợ hàm isContain trong Infantry
    Unit* identifyUnit (VehicleType type);          // Hàm tìm đơn vị unit theo vehicle hỗ trợ hàm isContain trong Vehicle 
    // Phương thức xử lý danh sách đảo ngược 
    void reverseList ();
    void updateQuantity(Unit*, Unit*);
    // Thêm hàm Copy Constructor và tìm Assignment Operator =
    UnitList(const UnitList& other);  // Khởi tạo cho hàm Constructor Copy tạo bản sao mới từ bản gốc
    UnitList& operator=(const UnitList& other); // Tạo operator toán tử = gán cho 2 unit list bằng nhau 
    void clear (); // Giải phóng tài nguyên cho các node 
private:
// Thêm đơn vị danh sách liên kết vào 
    
    int capacity;
    // vector<Unit *> units; 
    // Đối với bài toán ở bài tập này mảng Vector phải đc sử dụng bằng Linked List
    int countVehicle=0, countInfantry=0;
    int currSize;               // Cập nhật sức chứa hiện có 
    Node *head;                 // Con trỏ trỏ đến đầu danh sách 
    Node *tail;                 // Con trỏ trỏ đến cuối danh sách 
    int numCount =1;
};

#endif
