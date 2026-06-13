#ifndef _H_ARMY_H_
#define _H_ARMY_H_
#include "BattleField.h"
#include "UnitList.h"
using namespace std;
class BattleField;
class Army {
    protected:
    int LF;        // * Tổng điểm từ các phương tiện (Vehicle)
    int EXP;       // * Tổng điểm từ các lực lượng bộ binh (Infantry)
   
    string name;

    BattleField* battleField;                 //Ơ mục này task 3.7  sẽ thêm hàm trận địa tham chiến 
    
    // Gọi danh sách Unitlist để kiểm tra từng đơn vị unit 
    // Lưu ý cần giải phóng linked List này khi gọi 
    vector<Unit*> SubMinScore(vector<Unit*> units, int max);  // Hàm tìm ra tổ hợp trả về gía trị nhỏ nhất lớn hơn chỉ số sức LF hoặc EXP tương ứng 
    // Tìm ra tổ hợp tối ưu nhỏ nhất 
public:
    // Phần khởi tạo thiếu trận điạ BattleField trận địa chiến đấu 
    // Phần khởi tạo này với mục đích tính LF và EXP thêm vào danh sách Yb
    Army(Unit **unitArray, int size, string name,BattleField * battleField);  // Dùng LF tính bằng tổng điểm getScore của các phương tiện Vehicle 
    // Dùng EXP tính bằng tổng điểm  các score của các phương tiện Infantry
    virtual void fight(Army *enemy, bool defense = false) = 0;  // Hàm này dùng để ghi đè chỉ ra tính đa hình phương thức giao tranh của từng loai
    virtual string str() const = 0;
    virtual ~Army();  // Gợi ý giải phóng thủ công trong hàm hủy 
    UnitList *unitList;     // Thêm vào phần danh sách unitList 
    // * Additional functions if possible
    void checkLFrange(int &);
    void checkEXPrange(int &);
    int safeCeil(double value);
    int getLF ()  { return LF;}
    int getEXP ()  { return EXP; }
    void setLF(int val) { this -> LF = val;}
    void setEXP (int val){ this -> EXP = val; }
    UnitList * getUnitList (){ return unitList;  }
    // Hàm xử lý danh sách Unit  và UnitList 
    Unit* deepCopyUnit(Unit* unit); // Tương đương với hàm cloneUnit hàm unit ảo 
    UnitList* deepCopyUnitList(UnitList* );
    // Phương thức loại bỏ Unit ra khỏi danh sách 
    void eliminateUnit(UnitList *list,Unit* unit);
    // Gán toàn bộ Score cho toàn bộ danh sách 
    void setAttackScore ();    // Thiết lập chỉ số giao tranh cho toàn bộ danh sách 
    // Hàm tính toán cho LF và EXP cập nhật các thông số LF và EXP cho chính xác trong lúc giao tranh 
    void findLFEXP();  // Mục đích của hàm này là cập nhật  chỉ số  LF và EXP đúng với tình trạng đang chiến đấu 
    virtual void upload(UnitList*)= 0;   // Cập nhật lại các chỉ số cho phù hợp 
    void findMinestGreaterLiberArmy(vector<Unit*>&, vector<Unit*>&,vector<Unit*>&,
                                 vector<Unit*>&,UnitList*,int , int );// Truyền 4 thông tin đối số đầu vào để tìm số nhỏ nhất mà lớn hơn
    
};

#endif
