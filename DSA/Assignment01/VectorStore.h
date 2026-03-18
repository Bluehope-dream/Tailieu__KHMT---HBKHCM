#ifndef VECTORSTORE_H
#define VECTORSTORE_H

#pragma once
// NOTE: Per assignment rules, only this single include is allowed here.
#include "main.h"

// ------------------------------
// AVL balance enum
// ------------------------------
enum BalanceValue
{
    LH = -1, // Left Higher
    EH = 0,  // Equal Height
    RH = 1   // Right Higher
};

// ------------------------------
// Generic AVL Tree (template)
// ------------------------------
template <class K, class T>
class AVLTree
{
    friend class VectorStore; // Allow VectorStore to access protected/private members

public:
    class AVLNode
    {
    public:
        K key;
        T data;
        AVLNode *pLeft;
        AVLNode *pRight;
        BalanceValue balance;

        AVLNode(const K &key, const T &value)
            : key(key), data(value), pLeft(nullptr), pRight(nullptr), balance(EH) {}

        friend class VectorStore; // Allow VectorStore to access AVLNode members
    };

protected:
    AVLNode *root;

    AVLNode *rotateRight(AVLNode *&node);
    AVLNode *rotateLeft(AVLNode *&node);
    void clearHelper(AVLNode *node);

public:
    AVLTree();
    ~AVLTree();

    void BalanceLeft(AVLNode*&node,bool &taller);
    void BalanceRight(AVLNode*&node,bool &taller);
    AVLNode* insertHelper(AVLNode*node,AVLNode* &newNode,bool &taller);
    void insert(const K& key, const T& value);

    AVLNode* findMinNode(AVLNode* node);
    AVLNode* deRightBalance(AVLNode*&node,bool &shorter);
    AVLNode* deLeftBalance(AVLNode*&node,bool &shorter);
    AVLNode* removeHelper(AVLNode*node,const K&key,bool &shorter,bool &success);
    void remove(const K& key);

    bool contains(const K& key) const;
    int getHeight() const;
    int getSize() const;
    bool empty() const;
    void clear();
    void printTreeStructure() const;

    void inorderTraversalHelper(AVLNode* node,void (*action)(const T& data)) const;

    void inorderTraversal(void (*action)(const T&)) const;
    AVLNode* getRoot() const { return root; }
    // Trong class AVLTree
    template<typename Func>
    void inorderDeepHelper(AVLNode* node, Func& func) const {
        if (!node) return;
        inorderDeepHelper(node->pLeft, func);
        func(node->data);   // node->data là VectorRecord
        inorderDeepHelper(node->pRight, func);
    }
    template<typename Func>
    void inorderDeep(Func func) const {
        inorderDeepHelper(root, func);
    }
};

enum Color
{
    RED,
    BLACK
};

// RedBlackTree class
template <class K, class T>
class RedBlackTree
{
    friend class VectorStore; // Allow VectorStore to access protected/private members

public:
    // RBTNode class

    class RBTNode
    {
    public:
        K key;
        T data;
        Color color;
        RBTNode *parent;
        RBTNode *left;
        RBTNode *right;

        // Constructor
        RBTNode(const K &key, const T &value);

        void recolorToRed();
        void recolorToBlack();

        friend class VectorStore; // Allow VectorStore to access RBTNode members
    };

private:
    RBTNode *root;

protected:
    void rotateLeft(RBTNode *node);
    void rotateRight(RBTNode *node);

    RBTNode *lowerBoundNode(const K &key) const;
    RBTNode *upperBoundNode(const K &key) const;

public:
    RedBlackTree();
    ~RedBlackTree();

    bool empty() const;
    int size() const;
    void clearHelper(RBTNode* &node);
    void clear();
    void insertRBHelper(RBTNode* &node);
    void insert(const K &key, const T &value);
    RBTNode* findMaxLeft(RBTNode*&node) ;
    void transParent (RBTNode*u, RBTNode*v);
    void deleteHelper(RBTNode*node,RBTNode* parent);
    void remove(const K &key);
    RBTNode *find(const K &key) const;
    bool contains(const K &key) const;

    RBTNode *lowerBound(const K &key, bool &found) const;
    RBTNode *upperBound(const K &key, bool &found) const;

    // Hỗ trợ tìm k phần tử gần nhất  trong topKNearest.
    void rangeQueryHelper(RBTNode*node,RBTNode* lowerNode, RBTNode * upperNode,std::vector<T*> &) const;

    // In cây kiểm tra cấu trúc của cây 
    void printTreeStructure() const;
    RBTNode* getRoot (){ return root; }
};

// ------------------------------
// VectorRecord
// ------------------------------
class VectorRecord
{
public:
    int id;
    std::string rawText;
    int rawLength;
    std::vector<float> *vector;
    double distanceFromReference;
    double norm;

    VectorRecord()
        : id(-1), rawLength(0), vector(nullptr), distanceFromReference(0.0), norm(0.0) {}

    VectorRecord(int _id,
                 const std::string &_rawText,
                 std::vector<float> *_vec,
                 double _dist=0,
                 double _norm = 0)
        : id(_id),
          rawText(_rawText),
          rawLength(static_cast<int>(_rawText.size())),
          vector(_vec),
          distanceFromReference(_dist),
          norm(_norm) {}
    // Phương thức sao hỗ trợ sao chép các thông số vector để hỗ trợ buid lại cây 
    static     std::vector<VectorRecord> shallowCopy(const std::vector<VectorRecord*>& allVecs);
    static     std::vector<VectorRecord> deepCopy(const std::vector<VectorRecord*>& allVecs) ;

    static VectorRecord deepCopySingle(const VectorRecord* rec) {
        std::vector<float>* newVec = new std::vector<float>(*rec->vector);
        return VectorRecord(rec->id, rec->rawText, newVec,
                            rec->distanceFromReference, rec->norm);
    }
    // Overload operator << to print only the id
    friend std::ostream &operator<<(std::ostream &os, const VectorRecord &record);

            // ko hiện thực destructor luôn 

  
};

// ------------------------------
// VectorStore
// ------------------------------

class VectorStore
{
private:
    static int idxTarget;
    static int idxCount;
    static VectorRecord* resRecord;
    static void inorder_action(const VectorRecord& rec);
    //Static để lưu biến id cho các vectorStore theo thứ tự tăng dần 
    static vector<int> *idListStore;
    static void collectId(const VectorRecord& record) ;
   
    AVLTree<double, VectorRecord> *vectorStore;
    RedBlackTree<double, VectorRecord> *normIndex;

    std::vector<float> *referenceVector;
    VectorRecord *rootVector;

    int dimension;
    int count;
    double averageDistance;

    std::vector<float> *(*embeddingFunction)(const std::string &);
    // Các biến static hỗ trợ cho việc lấy ID cần thiết
    
    double distanceByMetric(const std::vector<float> &a,
                            const std::vector<float> &b,
                            const std::string &metric) ;

    // void rebuildRootIfNeeded();
    // void rebuildTreeWithNewRoot(VectorRecord *newRoot);
    AVLTree<double,VectorRecord> :: AVLNode * buildNewAVL(const vector <VectorRecord>&,int low, int high);
    VectorRecord *findVectorNearestToDistance(double targetDistance) const;

public:
    VectorStore(int dimension,
                std::vector<float> *(*embeddingFunction)(const std::string &),
                const std::vector<float> &referenceVector);
    ~VectorStore();

    int size();
    bool empty();
    void clear();

    std::vector<float> *preprocessing(std::string rawText);

    vector<VectorRecord*> cloneAllRecord() const ;

    vector<VectorRecord> cloneAllRecordSafe() const ;
    // vector<VectorRecord> cloneAllRecordCopy() const ;
    void addText(std::string rawText);          //xxxxxxxxxx
    VectorRecord *getVector(int index);
 
    std::string getRawText(int index);
    int getMaxId()  ;
    int getId(int index);

    bool removeAt(int index);         //Xxxxxxxxxxxxxxxxxxxxxxx

    void merge(vector<VectorRecord*>&arr, int low , int high , int mid);
    void mergeSort(vector<VectorRecord*>&arr, int low, int high);
    void setReferenceVector(const std::vector<float> &newReference); //xxxxxxxxxxxxxxxxx

    std::vector<float> *getReferenceVector() const;
    VectorRecord *getRootVector() const;
    double getAverageDistance() const;        
    void setEmbeddingFunction(std::vector<float> *(*newEmbeddingFunction)(const std::string &));

    void inorderAction(AVLTree<double,VectorRecord>::AVLNode* root,void (*action)(std::vector<float> &, int, std::string &));
    void forEach(void (*action)(std::vector<float> &, int, std::string &));

    std::vector<int> getAllIdsSortedByDistance() const;
    std::vector<VectorRecord *> getAllVectorsSortedByDistance() const;

    double cosineSimilarity(const std::vector<float> &v1, const std::vector<float> &v2) const;
    double l1Distance(const std::vector<float> &v1, const std::vector<float> &v2) const;
    double l2Distance(const std::vector<float> &v1, const std::vector<float> &v2) const ;   // chuẩn euclidean 

    double estimateD_Linear(const std::vector<float> &query, int k, double averageDistance, const std::vector<float> &reference, double c0_bias = 1e-9, double c1_slope = 0.05);

    int findNearest(const std::vector<float> &query, std::string metric = "cosine") ;
    int *topKNearest(const std::vector<float> &query, int k, std::string metric = "cosine");      //Xong
    //Các hàm hỗ trợ cho phương thức tìm kiếm 
    struct idDistance {
        int id;
        double distance;
    };
    void preRangeQueryRoot(AVLTree<double,VectorRecord>::AVLNode* node,vector<int> &res,double &minDist, double &maxDist) const;
    void preRangeQuery(AVLTree<double,VectorRecord>::AVLNode* node,const vector<float> &query,vector<idDistance>&res, double &radius,string metric = "cosine") const ;   /////////////////////////////////////////////
    void preBoxQuery(AVLTree<double,VectorRecord>::AVLNode* node,const std::vector<float> &minBound, const std::vector<float> &maxBound,vector<int>&res) const;/////////////////////////

    int *rangeQueryFromRoot(double minDist, double maxDist) const;    //Xong
    int *rangeQuery(const std::vector<float> &query, double radius, std::string metric = "cosine") const;     //Xong
    int *boundingBoxQuery(const std::vector<float> &minBound, const std::vector<float> &maxBound) const;     //Xpng

        //Lấy truy vấn nâng cao để tìm khoảng cách truy vấn trong phạm vi
    double getMaxDistance() const;
    double getMinDistance() const;
    VectorRecord computeCentroid(const std::vector<VectorRecord *> &records) const  ;  

    VectorRecord* findRecordById(int id);
};

#endif // VECTORSTOR_H
