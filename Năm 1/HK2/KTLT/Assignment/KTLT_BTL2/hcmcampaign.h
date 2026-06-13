    // The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_HCM_CAMPAIGN_H_
#define _H_HCM_CAMPAIGN_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class Unit;
class UnitList;
class Army;
class TerrainElement;

class Vehicle;
class Infantry;

class LiberationArmy;
class ARVN;

class Position;

class Road;
class Mountain;
class River;
class Urban;
class Fortification;
class SpecialZone;

class BattleField;

class HCMCampaign;
class Configuration;

enum VehicleType
{
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};
enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};
//////////////////////////////////////////////////////////////////////////////////////
////                CLASS POSITION 
////
////////////////////////////////////////////////////////////////////////////////////////
class Position
{
private:
    int r, c;

public:
    Position(int r = 0, int c = 0);
    Position(const string &str_pos);
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const;
};
/////////////////////////////////////////////////////////////
//             CLASS UNIT         
//
////////////////////////////////////////////////////////////
class Unit
{
protected:
    int quantity, weight;
    Position pos;
    int attackScore ; // thực hiện lấy chỉ số chiến đấu 
    int unitBelong;
public:
   
    Unit(int quantity, int weight, Position pos);
    virtual ~Unit();
    virtual int getAttackScore() = 0;
    Position getCurrentPosition() const;
    virtual string str() const = 0;
    // Dùng bộ đôi getter và setter để thay đổi dữ liệu đóng gói enscuplation  của chương trình 
    void setquantity(int );
    int getquantity();
    int getWeight();
    void setWeight(int weight);
    // virtual int getScore() const = 0;
    // Lập hàm setPosition và getPosition Bộ getPosition này đã được biểu diễn tương đương với bộ Position getCurrentPosition   
    void setPos(Position pos);
    // Position getPos();
    int  getAttackScoreDuringFight() { return attackScore; }
    void setAttackScore (int num){ this -> attackScore = num; }
    virtual int checkValue()=0;// Thực hàm hàm kiểu dữ liệu kiểm tra xem kiểu dữ liệu đầu vào là Infantry hay là Vehicle 
    void setUnitBelong(int & val) { unitBelong = val;}
    int getUnitBelong (){ return unitBelong; }
};
////////////////////////////////////////////////////////////////////////////////
////                    CLASS VEHICLE 
////
////////////////////////////////////////////////////////////////////////////////

class Vehicle : public Unit
{
    // TODO: implement
    private:
        VehicleType vehicleType;
    public:
    Vehicle (int quantity, int weight, const Position pos,VehicleType vehicleType);
    static string vehicleReflexion(const VehicleType &vehicleName);
    int getAttackScore() override ;
    string str() const override ;
    // int getScore() const override ;
    int checkValue() override ;  // Hàm kiểm tra đầu vào cho dữ liệu có phải là Vehicle hay ko ? 
};
////////////////////////////////////////////////////////////////////////////////////////////////
////                            INFANTRY CLASS 
///
////////////////////////////////////////////////////////////////////////////////////////////////

class Infantry : public Unit
{
    // TODO: implement
    private:
        InfantryType infantryType;
    public:
        Infantry(int quantity, int weight, const Position pos, InfantryType infantryType);
        int getAttackScore() override ;
        string str() const override ;
        bool checkCommando (InfantryType &value, int &weight);  // Hàm kiểm tra hàm điệp viên xét lấy score trong trường hợp đặc biệt 
        int getPersonalIndex(int &score);
        string InfantryName (const InfantryType& value) const  ;
        // int getScore ()const  override;
        int checkValue() override ;  // Hàm kiểm tra đầu vào  của dữ liệu
        int safeCeil(double val) ;
        bool isPerfect(int val);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
////
////                    CLASS UNITLIST 
////
//////////////////////////////////////////////////////////////////////////////////////////////////////
class UnitList
{
public:
struct Node {
        Unit*unit;
        Node * next;
        Node (Unit*m):  unit(m),next(nullptr){}  // Khởi tạo cho các Node ban đầu 
    };
    UnitList(int capa);     // Hàm constructor khởi tạo các giá trị 
    ~UnitList ();               // Hàm này dùng để xóa các danh sách trong linked LIST
    bool insert(Unit *unit);     // Hàm này chèn infantry và vehicle cho phù hợp
    // Hàm hỗ trợ chèn vào cuối danh sách cho Vehicle 
    void insertAtEnd (Unit * unit);
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
    void Print() {
        Node* curr = head;
        while (curr) {
            cout << curr->unit->str() << endl;
            curr = curr->next;
        }
    }
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
//////////////////////////////////////////////////////////////////////////////////////////
////            ARMY CLASS
////
//////////////////////////////////////////////////////////////////////////////////////////
class Army {
    protected:
    int LF;        // * Tổng điểm từ các phương tiện (Vehicle)
    int EXP;       // * Tổng điểm từ các lực lượng bộ binh (Infantry)
    bool fighting = false ;
    string name;

    BattleField* battleField;                 //Ơ mục này task 3.7  sẽ thêm hàm trận địa tham chiến 
    
    // Gọi danh sách Unitlist để kiểm tra từng đơn vị unit 
    // Lưu ý cần giải phóng linked List này khi gọi 
    vector<Unit*> SubMinScore(vector<Unit*> units, int max);  // Hàm tìm ra tổ hợp trả về gía trị nhỏ nhất lớn hơn chỉ số sức LF hoặc EXP tương ứng 
    // Tìm ra tổ hợp tối ưu nhỏ nhất 
public:
    bool liberChampion= false; // Mặc định Quân Giai Phóng là quân ĐỘI THUA trong cuộc chiến 
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
    void setFighting (){ this -> fighting = true;}
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
    bool checkSpecialNumber(int val);
    bool isSpecialNum(int val, int n);
    void printAfterWar ();
};
////////////////////////////////////////////////////////////////////////////////////////////////
////
////                        LIBERATION ARMY CLASS 
////
/////////////////////////////////////////////////////////////////////////////////////////////////
class LiberationArmy : public Army
{
private:
    Unit **unitArray;       // For temporary
    //int size_V = 0;         // For temporary: vehicle count
    // int size_I = 0;         // For temporary: infantry count
    int findNearestFibonacci(int value);
    // Dùng phương thức kế thừa protected cho một tổ hợp 
   
    vector <Unit*> setOfInfantry, setOfVehicle,A,B;
public:
    LiberationArmy(Unit **unitArray, int size, string name,BattleField* battleField);
    void fight(Army *enemy, bool defense) override;
    string str() const override;
    ~LiberationArmy();

    // Phương thức xóa tổ hợp khỏi danh sách 
    // Ý tưởng sẽ trả về các tổ hợp infantry và vehicle của quân ta và kẻ thù trả về tổ hợp phù hợp 
    void upload (UnitList*) override;  // Cập nhật lại các chỉ số cho kịp thời cho Quân Giair phóng 
    void eraseInvalidCombo(vector<Unit*>&);
    void clearVector(vector<Unit*>&); // Hàm hỗ trợ cho việc xóa các vector cho lệnh xóa các tổ hợp trên 
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
////                ARVN ARMY CLASS 
////
///////////////////////////////////////////////////////////////////////////////////////////////////////
class ARVN : public Army
{
    // TODO: implement
public:

    ARVN(Unit** unitArray, int size, string name,BattleField *battleField);
    void fight(Army* enemy, bool defense=false) override;
    string str() const;

    // * Additional functions if possible
    ~ARVN(); // GiẢI PHÓNG tài nguyên cho Quân đội Cộng Hòa 
    void upload (UnitList*) override;
};
//-----------------------------------------------------
// CLASS TerrainElement và các lớp dẫn xuất
//-----------------------------------------------------
class TerrainElement {
protected:
    Position pos; // Vị trí của yếu tố địa hình
    // Phương thức tính khoảng cách giữa hai vị trí
    double calDistance(const Position& pos1, const Position& pos2) {
        int rowLine = pos1.getRow() - pos2.getRow();
        int colLine = pos1.getCol() - pos2.getCol();
        return (sqrt(double(rowLine * rowLine + colLine * colLine)));
    }
    // Phương thức làm tròn 1 cách an toàn 
    int safeCeil(double value) {
        double dis = abs(value - round(value));
        return (dis < 1e-9) ? round(value) : ceil(value);
    }
public:
    TerrainElement(Position);
    virtual ~TerrainElement();
    // Phương thức thuần ảo: áp dụng hiệu ứng của yếu tố địa hình lên các quân đội.
    // (Chú ý: dùng tham số kiểu Army** theo đề bài.)
    virtual void getEffect(Army *army) = 0;
};

class Road : public TerrainElement {  // Lớp Road ĐƯỜNG MÒN
public:
    Road(Position pos) : TerrainElement(pos) {}
    // Đường mòn không có hiệu ứng
    ~Road() override;
    void getEffect(Army *army) override;
};

class Mountain : public TerrainElement { // Lớp rừng núi
public:
    Mountain(Position pos) : TerrainElement(pos) {}
    // Rừng núi: hiệu ứng áp dụng (stub) – áp dụng tác động đối với cả các đơn vị bộ binh và phương tiện
    void getEffect(Army *army) override;
    ~Mountain() override;
    void MountainEffect(double &addSum, double &minusSum,double &addIndex, double &minusIndex,UnitList *list,double &r);
};

class River : public TerrainElement {   // Lơp sống sâu 
public:
    River(Position pos) : TerrainElement(pos) {}
    // Sông: hiệu ứng giảm EXP 10% cho lực lượng bộ binh nếu nằm trong bán kính 2 đơn vị (stub)
    void getEffect(Army *army) override;
    ~River () override;
};

class Urban : public TerrainElement {   // Lớp khu dân cư 
public:
    Urban(Position pos) : TerrainElement(pos) {}
    // Khu dân cư: hiệu ứng (stub) – áp dụng theo mô tả đề bài
    void getEffect(Army *army) override;
    ~Urban() override;
};

class Fortification : public TerrainElement {     // Lớp chiến hào 
public:
    Fortification(Position pos) : TerrainElement(pos) {}
    // Chiến hào: hiệu ứng (stub) – áp dụng theo mô tả đề bài
    void getEffect(Army *army) override;
    ~Fortification () override;
};

class SpecialZone : public TerrainElement {   // Lớp khu vực phi quân sự 
public:
    SpecialZone(Position pos) : TerrainElement(pos) {}
    // Khu vực phi quân sự: hiệu ứng (stub) – đặt attackScore của các đơn vị xung quanh về 0
    void getEffect(Army *army) override;
    ~SpecialZone() override; // Hủy để tránh thất thoát tài nguyên
};

//!-----------------------------------------------------
//! CLASS BattleField
//!-----------------------------------------------------
class BattleField {  // Lớp trận địa chiến đấu 
private:
    int n_rows, n_cols;
    // 2D mảng chứa con trỏ đến các đối tượng TerrainElement
    TerrainElement ***terrain;
    enum Location{
        forest, river,fortification,urban, SpecialArea
    };
    bool isInsideMap(int row, int col) const;
    void attachTerrainEffect (const vector <Position*> & positions,Location type);
   
public:
    // Constructor nhận các vector vị trí của các yếu tố địa hình
    BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone);
    ~BattleField();
    
    // Trả về đối tượng TerrainElement tại vị trí (r,c)
    TerrainElement* getElement(int row, int col) const;
    
    // Hàm str để biểu diễn thông tin của BattleField
    string str() const;
};
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
     vector<string> splitUnits(const string &block) ;
  
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
     // Đọc cái chuỗi thông tin về các đơn vị Unit của các đơn vị tham chiến  
    string printUnitArr(vector<Unit*>) const; 
    void releaseVector(vector<Position*>);
    void releaseVector (vector<Unit*> );
    void mergeLine (string line,string &arrName,string key,bool &flag);
    
    void readPositionVector(vector<Position*>&, string &);  // Hàm đọc các mảng vector Position cho các đơn vị Position
    void readUnitVector(vector<Unit*>&, vector<Unit*>&, const string &);          // Hàm đọc các mảng vector cho 2 đơn vị quân sự Unit Vector
    bool isInfantry (const string &name );
    bool isVehicle  (const string & name );
    
};
///////////////////////////////////////////////////////////////////
/////                   HCM CAMPAIGN
/////
////////////////////////////////////////////////////////////////////
class HCMCampaign{
    private:
        Configuration* config;
        BattleField* battleField;
        LiberationArmy * liberationArmy;
        ARVN* ARVNArmy;
        Unit** LibertyUnitArray;
        Unit** ARVNUnitArray;
    public: 
    // Tạo một constructor nhận đường dẫn đến tập tin cấu hình cho chương trình 
        HCMCampaign ( const string & config_file_path );
        ~HCMCampaign();
        void run();  // Các yếu tố quan sự bị ảnh hưởng bởi các yếu tố ĐỊA HÌNH trước rồi mới GIAO TRANH 
        string printResult(); // In ra các chỉ số chiến đấu của 2 quân dôi cộng hòa và quân giải phóng 
    // LIBERATIONARMY[LF=<LF>,EXP=<EXP>]-ARVN[LF=<LF>,EXP=<EXP>]
        void getBattleEffect(Army *);
        void initialArmy (Army*& ,vector<Unit*> & unit , Unit**& unitArray, bool isARVN);
};
#endif