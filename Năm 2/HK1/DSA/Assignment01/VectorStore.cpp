// NOTE: Per assignment rules, only this single include is allowed here.
#include "VectorStore.h"

// =====================================
// Helper functions
// =====================================

// Helper function to print n spaces for tree visualization
void printNSpace(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << " ";
    }
}

// =====================================
// AVLTree<K, T> implementation
// =====================================

template <class K, class T>
void AVLTree<K, T>::printTreeStructure() const
{
    int height = this->getHeight();
    if (this->root == NULL)
    {
        cout << "NULL\n";
        return;
    }
    queue<AVLNode *> q;
    q.push(root);
    AVLNode *temp;
    int count = 0;
    int maxNode = 1;
    int level = 0;
    int space = pow(2, height);
    printNSpace(space / 2);
    while (!q.empty())
    {
        temp = q.front();
        q.pop();
        if (temp == NULL)
        {
            cout << " ";
            q.push(NULL);
            q.push(NULL);
        }
        else
        {
            cout << temp->data;
            q.push(temp->pLeft);
            q.push(temp->pRight);
        }
        printNSpace(space);
        count++;
        if (count == maxNode)
        {
            cout << endl;
            count = 0;
            maxNode *= 2;
            level++;
            space /= 2;
            printNSpace(space / 2);
        }
        if (level == height)
            return;
    }
}

// TODO: Implement all AVLTree<K, T> methods here

template <class K, class T>
AVLTree<K, T>::AVLTree() : root(nullptr) {}

template <class K, class T>
AVLTree<K, T>::~AVLTree() { clear(); }

template<class K,class T>
void AVLTree<K,T>::clearHelper(AVLNode* node){
    if (!node) return;
    clearHelper(node->pLeft);
    clearHelper(node->pRight);
    delete node;
}

template<class K,class T>
void AVLTree<K,T>::clear() {
    clearHelper(root);
    root = nullptr;
}

template<class K,class T>
typename AVLTree<K,T>::AVLNode* AVLTree<K,T>::rotateLeft(AVLNode* &node){
    if (!node || !node->pRight) return node;
    AVLNode* p = node->pRight;
    node->pRight = p->pLeft;
    p->pLeft = node;
    return p;
}

template<class K,class T>
typename AVLTree<K,T>::AVLNode* AVLTree<K,T>::rotateRight(AVLNode* &node){
    if (!node || !node->pLeft) return node;
    AVLNode* p = node->pLeft;
    node->pLeft = p->pRight;
    p->pRight = node;
    return p;
}

// ==============================
// Balance functions
// ==============================
template<class K,class T>
void AVLTree<K,T>::BalanceLeft(AVLNode*& node, bool& taller) {
    if (!node) return;
    AVLNode* left = node->pLeft;
    if (!left) return;
    // Case 1 : Left left Rotation 
    if (left->balance == LH) {
        node->balance = EH;
        left->balance = EH;
        node = rotateRight(node);
        taller = false;
                return;
    }
    else if (left->balance == RH) { // LR
        AVLNode* right = left->pRight;
        if (!right) return;
        switch (right->balance) {
            case LH: node->balance = RH; left->balance = EH; break;
            case EH: node->balance = EH; left->balance = EH; break;
            case RH: node->balance = EH; left->balance = LH; break;
        }
        right->balance = EH;
        node->pLeft = rotateLeft(left);
        node = rotateRight(node);
        taller = false;
        return;
    }
    // impossible case........................
    if (left->balance==EH){
        node ->balance=LH;
        left->balance=RH;
        node = rotateRight(node);
        taller =false;
        return;
    }
}

template<class K,class T>
void AVLTree<K,T>::BalanceRight(AVLNode*& node, bool& taller) {
    if(!node) return;
    AVLNode* right = node->pRight;
    if (!right) return;
    // Case 1: Right Right rotation 
    if (right->balance == RH) {
        node->balance = EH;
        right->balance = EH;
        node = rotateLeft(node);
        taller = false;
        return;
    }
    else if (right->balance == LH) { // RL
        AVLNode* left = right->pLeft;
        if (!left) return;
        switch(left->balance){
            case LH: node->balance = EH; right->balance = RH; break;
            case EH: node->balance = EH; right->balance = EH; break;
            case RH: node->balance = LH; right->balance = EH; break;
        }
        left->balance = EH;
        node->pRight = rotateRight(right);
        node = rotateLeft(node);
        taller = false;
        return;
    }
    //Defensive impossible case 
    if (right->balance==EH){
        node ->balance =RH;
        right ->balance =LH;
        node = rotateLeft(node);
        taller =false;
        return;
    }
}

// ==============================
// Insert
// ==============================
template<class K,class T>
typename AVLTree<K,T>::AVLNode* AVLTree<K,T>::insertHelper(AVLNode* node, AVLNode*& newNode, bool& taller){
    if (!node) {
        node = newNode;
        taller = true;
        return node;
    }

    if (newNode->key < node->key) {
        node->pLeft = insertHelper(node->pLeft, newNode, taller);
        if (taller) {
            switch(node->balance){
                case LH: BalanceLeft(node,taller); break;
                case EH: node->balance = LH; break;
                case RH: node->balance = EH; taller = false; break;
            }
        }
    } else if (newNode->key > node->key) {
        node->pRight = insertHelper(node->pRight, newNode, taller);
        if (taller) {
            switch(node->balance){
                case LH: node->balance = EH; taller=false; break;
                case EH: node->balance = RH; break;
                case RH: BalanceRight(node,taller); break;
            }
        }
    } else {
        delete newNode; // trùng key, xóa node mới
        taller = false;
    }

    return node;
}

template<class K,class T>
void AVLTree<K,T>::insert(const K& key, const T& value){
    AVLNode* newNode = new AVLNode(key,value);
    bool taller=false;
    root = insertHelper(root,newNode,taller);
}

// ==============================
// Remove (delete)
// ==============================
template<class K,class T>
typename AVLTree<K,T>::AVLNode* AVLTree<K,T>::findMinNode(AVLNode* node){
    while(node && node->pLeft) node = node->pLeft;
    return node;
}

template<class K,class T>
typename AVLTree<K,T>::AVLNode* AVLTree<K,T>::deLeftBalance(AVLNode*& node, bool &shorter){
    if (!node) {shorter = false;    return node ;            }
    AVLNode* left = node->pLeft;
    if (!left) {            // Xử lý trường nếu ko có cây con bên trái , chỉ cần cập nhập các chỉ số balance factor 
        if (node ->balance==RH){
            node -> balance = EH; // Độ cao của cây vẫn duy trì giảm    // Chưa đặt balnce hơi NHGHI VẤN 
        } else if (node ->balance ==EH){
            node ->balance=LH;
            shorter = false;
        }
        return node;
    }
    if (node->balance == RH) { node->balance = EH; return node; }    // rIGHT HEAVY
    if (node->balance == EH) { node->balance = LH; shorter=false; return node; }
// Left Subtreee was higher needdđ to rebalance factor 
    if (left->balance == LH) { 
        node->balance = EH; // Hệ số cân bằng của node mới (trước xoay:RH)
        left->balance = EH;         // Hệ số cân bằng của left(trước xoay: LH )
        node = rotateRight(node);           // Xoay phải nút 
                return node;
    }
    else if (left->balance == RH) {     // Left Right Rotation 
        AVLNode* right = left->pRight;
        if(right){
            switch(right->balance){
                case LH: node->balance = RH; left->balance = EH; break;
                case EH: node->balance = EH; left->balance = EH; break;
                case RH: node->balance = EH; left->balance = LH; break;
            }
            right->balance = EH;
        }
        node->pLeft = rotateLeft(left);
        node = rotateRight(node);
                return node;
    } else { // left->balnce ==EH
		node->balance = LH; 
		left->balance = RH;
	    node = rotateRight(node); 
		shorter=false;
            return node;
	}
   
}

template<class K,class T>
typename AVLTree<K,T>::AVLNode* AVLTree<K,T>::deRightBalance(AVLNode*& node, bool &shorter){
    if (!node){shorter = false;       return node ;  }
    AVLNode* right = node->pRight;
    if (!right){
        if (node ->balance ==LH) {
            node ->balance =EH;
        } else if (node ->balance ==EH){
            node ->balance =RH;
            shorter = false;
        }
        return node;
    } 
    if (node->balance == LH) { node->balance = EH; return node; }
    if (node->balance == EH) { node->balance = RH; shorter=false; return node; }
    // Right Subtreee was higher than left subtreee  Right rotation xử lý hơn nữa 
    if (right->balance == RH) { 
        node->balance = EH; 
        right->balance = EH; 
        node = rotateLeft(node);}
    else if (right->balance == LH) {
        AVLNode* left = right->pLeft;
        if(left){
            switch(left->balance){
                case LH: node->balance = EH; right->balance = RH; break;
                case EH: node->balance = EH; right->balance = EH; break;
                case RH: node->balance = LH; right->balance = EH; break;
            }
            left->balance = EH;
        }
        node->pRight = rotateRight(right);
        node = rotateLeft(node);
    } else {    // Right balance ==EH 
		node->balance = RH; 
		right->balance = LH; 
		node = rotateLeft(node); 
		shorter=false;
	}
    return node;
}

template<class K,class T>
typename AVLTree<K,T>::AVLNode* AVLTree<K,T>::removeHelper(AVLNode* node,const K& key,bool &shorter,bool &success){
    if (!node) { shorter=false; success=false; return nullptr; }
    if (key < node->key) {
        node->pLeft = removeHelper(node->pLeft,key,shorter,success);
        if(shorter) node = deRightBalance(node,shorter);
    } else if (key > node->key) {
        node->pRight = removeHelper(node->pRight,key,shorter,success);
        if(shorter) node = deLeftBalance(node,shorter);
    } else { // Found node
        success = true; shorter=true;
        if(!node->pLeft){ AVLNode* tmp=node->pRight; delete node; return tmp; }
        if(!node->pRight){ AVLNode* tmp=node->pLeft; delete node; return tmp; }

        AVLNode* pred = findMinNode(node->pRight);
        node->key = pred->key;
        node->data = pred->data;
        node->pRight = removeHelper(node->pRight,pred->key,shorter,success);
        if(shorter) node = deLeftBalance(node,shorter);
    }
    return node;
}

template<class K,class T>
void AVLTree<K,T>::remove(const K& key){
    bool shorter=false, success=false;
    root = removeHelper(root,key,shorter,success);
}

// ==============================
// Traversals & utilities
// ==============================
template<class K,class T>
bool AVLTree<K,T>::contains(const K& key) const {
    AVLNode* p=root;
    while(p){
        if(key==p->key) return true;
        else if(key<p->key) p=p->pLeft;
        else p=p->pRight;
    }
    return false;
}

template<class K,class T>
int AVLTree<K,T>::getHeight() const {
    if(!root) return 0;
    queue<AVLNode*> q; q.push(root);
    int height=0;
    while(!q.empty()){
        int sz = q.size();
        for(int i=0;i<sz;i++){
            AVLNode* n=q.front(); q.pop();
            if(n->pLeft) q.push(n->pLeft);
            if(n->pRight) q.push(n->pRight);
        }
        height++;
    }
    return height;
}

template<class K,class T>
int AVLTree<K,T>::getSize() const {
    if(!root) return 0;
    queue<AVLNode*> q; q.push(root);
    int count=0;
    while(!q.empty()){
        AVLNode* n=q.front(); q.pop();
        count++;
        if(n->pLeft) q.push(n->pLeft);
        if(n->pRight) q.push(n->pRight);
    }
    return count;
}

template<class K,class T>
bool AVLTree<K,T>::empty() const { return (root==nullptr); }

template<class K,class T>
void AVLTree<K,T>::inorderTraversalHelper(AVLNode* node, void (*action)(const T&data)) const {
    if(!node) return;
    inorderTraversalHelper(node->pLeft,action);
    action(node->data);
    inorderTraversalHelper(node->pRight,action);
}

template<class K,class T>
void AVLTree<K,T>::inorderTraversal(void (*action)(const T&)) const {
    inorderTraversalHelper(root,action);
}


// =====================================
// RedBlackTree<K, T> implementation
// =====================================

template <class K, class T>
void RedBlackTree<K, T>::printTreeStructure() const
{
    if (this->root == nullptr)
    {
        cout << "NULL\n";
        return;
    }

    queue<RBTNode *> q;
    q.push(root);
    RBTNode *temp;
    int count = 0;
    int maxNode = 1;
    int level = 0;

    // Calculate tree height for spacing
    int height = 0;
    queue<RBTNode *> heightQ;
    heightQ.push(root);
    while (!heightQ.empty())
    {
        int size = heightQ.size();
        height++;
        for (int i = 0; i < size; i++)
        {
            RBTNode *node = heightQ.front();
            heightQ.pop();
            if (node->left)
                heightQ.push(node->left);
            if (node->right)
                heightQ.push(node->right);
        }
    }

    int space = pow(2, height);
    printNSpace(space / 2);

    while (!q.empty())
    {
        temp = q.front();
        q.pop();

        if (temp == nullptr)
        {
            cout << "NULL";
            q.push(nullptr);
            q.push(nullptr);
        }
        else
        {
            // Print node data and color as tuple: (data, color)
            cout << "(" << temp->data << ",";
            if (temp->color == RED)
            {
                cout << "R)";
            }
            else
            {
                cout << "B)";
            }

            q.push(temp->left);
            q.push(temp->right);
        }

        printNSpace(space);
        count++;

        if (count == maxNode)
        {
            cout << endl;
            count = 0;
            maxNode *= 2;
            level++;
            space /= 2;
            printNSpace(space / 2);
        }

        if (level == height)
        {
            return;
        }
    }
}

// TODO: Implement all other RedBlackTree<K, T> methods here
template<class K,class T>
RedBlackTree<K,T>:: RBTNode ::RBTNode(const K &key, const T &value){
// Đang định nghĩa constructor chứ ko phải là kiểu dữ liệu nên ko dùng typename 
    this -> key = key;
    this -> data = value;
    this ->color = RED;
    this -> left = this -> right = this -> parent = nullptr;
}
template<class K,class T>
void RedBlackTree<K,T> :: RBTNode ::recolorToRed(){
    // Đổi màu của hiện tại sang RED 
    if (this -> color == RED){
        return ;
    }
    this -> color = RED;
}
template<class K,class T>
void  RedBlackTree<K,T> :: RBTNode ::recolorToBlack(){
    // Đổi màu của hiện tại sang BLACK
     if (this -> color == BLACK){
        return ;
    }
    this -> color = BLACK;
}
template<class K,class T>
void RedBlackTree<K,T> :: rotateLeft(typename RedBlackTree<K,T> ::RBTNode *node){
    // Thực hiện xoay trái cho RR và LR 
    if (!node && ! (node ->right)) return;
    RBTNode *p = node ->right;
    node ->right = p->left;
    if (p->left != nullptr){
        p->left ->parent = node;
    }
    p->parent = node ->parent ;
    if (node ->parent ==nullptr){
        root = p;
    } else if (node ==node ->parent ->left){
        node ->parent ->left =p;
    } else {
        node -> parent ->right = p;
    }
    p->left = node;
    node ->parent =p; // Mục đích chĩnh của nút này chỉ muốn thay đổi liên kết của các cây này thôi // ko muốn đổi nút này sang nút khác 
}
template<class K,class T>
void RedBlackTree<K,T> :: rotateRight(typename RedBlackTree<K,T> ::RBTNode *node){
    // Thực hiện xoay phải cho RL và LL  
    if (!node && ! (node ->left)) return;
    RBTNode*p = node ->left;
    node ->left = p->right;
    if (p->right != nullptr){
        p->right ->parent = node;
    }
    p->parent = node ->parent ;
    if (node ->parent ==nullptr){
        root = p;
    } else if (node ==node ->parent ->right){
        node ->parent ->right =p;
    } else {
        node -> parent ->left= p;
    }
    p->right = node;
    node ->parent =p;
}
template<class K,class T>
typename RedBlackTree<K,T> :: RBTNode* RedBlackTree<K,T> :: lowerBoundNode(const K &key) const{
    //Tìm nút đầu tiên có khóa >= key
    if (this->root ==nullptr) return nullptr;
    RBTNode* curr = this->root;
    RBTNode *res = nullptr;
    while(curr!=nullptr){
        if (curr->key==key){
            return curr;
        } else if (key<curr->key){
            res= curr;  // Tìm node có khả năng 
            curr= curr->left;
        } else {
            curr = curr ->right;// Dịch chuyển để tìm điều kiện thích hợp cho key thỏa mã node 
        }
    }
    return res;
}
template<class K,class T>
typename RedBlackTree<K,T> :: RBTNode* RedBlackTree<K,T> :: upperBoundNode(const K &key) const{
    // Tìm nút đầu tiên có khóa >key
    if (this ->root == nullptr){
        return nullptr;
    }
    RBTNode* res = nullptr;
    RBTNode* curr = root;
    while(curr != nullptr){
        if (key<curr->key){
            res= curr;  // Tìm node có khả năng 
            curr= curr->left;
        } else {
            curr = curr ->right;// Dịch chuyển để tìm điều kiện thích hợp cho key thỏa mã node 
        }
    }
    return res;
}
template<class K,class T>
RedBlackTree<K,T>:: RedBlackTree(){
    this -> root = nullptr; // Khởi tạo cây rỗng 
}
template<class K,class T> 
RedBlackTree<K,T>::~RedBlackTree(){
    // Giải phóng toàn bộ các nút đã được cấp phát theo cơ chế xóa theo mô hình postorder 
    // để tránh bị thất thoát dữ liệu 
    clear();
}

template<class K,class T> 
bool RedBlackTree<K,T>::empty() const {
    return (this -> root ==nullptr);
} 
template<class K,class T>
int RedBlackTree<K,T>::size() const {
    // Trả về số nút hiện có thực hiện đếm trong cây 
    if (empty()) return 0;
    queue<RBTNode*>q;
    q.push(root);
    int count =0;
    while (!q.empty()){
        RBTNode* curr = q.front();
        q.pop();
        if (curr->left){
            q.push(curr->left);
        }
        if (curr->right){
            q.push(curr->right);
        }
        count++;
    }
    return count;
}
template<class K,class T>
void RedBlackTree<K,T>::clearHelper(typename  RedBlackTree<K,T>::RBTNode* &node){
    if (node == nullptr) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}
template<class K,class T>
void RedBlackTree<K,T>::clear(){
    clearHelper(this->root);
    this -> root = nullptr;
}
template<class K,class  T>
void RedBlackTree<K,T>::insertRBHelper(typename RedBlackTree<K,T>::RBTNode* &node){
    if (node == nullptr) return;
    while(node ->parent !=nullptr && node ->parent ->color ==RED){
        RBTNode* parent = node ->parent ;
        RBTNode * grandpa  = parent ->parent ;
        if (grandpa==nullptr) break;     // Nếu parent chính là root
        if (parent ==grandpa->left){   // Case trái 
            RBTNode* uncle = grandpa ->right;
            // Case 1: UNCLE đỏ
            if (uncle !=nullptr && uncle->color ==RED){
                parent ->color =BLACK;
                uncle ->color =BLACK;
                grandpa->color = RED;
                node = grandpa;
            } else {
                // Case 2: node là con phải 
                if (node ==parent->right){
                    node = parent;
                    rotateLeft(node);
                    parent= node ->parent ;
                    if (parent) {
                        grandpa= parent -> parent; 
                    } else {
                        grandpa =nullptr;
                    }
                }
               if (parent != nullptr && grandpa != nullptr) { // Case 3
                    parent->color = BLACK;
                    grandpa->color = RED;
                    rotateRight(grandpa);
                }
            }
        } else {                 //mirror case 
             RBTNode* uncle = grandpa->left;

            if (uncle != nullptr && uncle->color == RED) { // Case 1 mirror
                parent->color = BLACK;
                uncle->color = BLACK;
                grandpa->color = RED;
                node = grandpa;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rotateRight(node);
                    parent = node->parent;
                    grandpa = parent ? parent->parent : nullptr;
                }
                if (parent != nullptr && grandpa != nullptr) { // Case 3 mirror
                    parent->color = BLACK;
                    grandpa->color = RED;
                    rotateLeft(grandpa);
                }
            }
        }
    }
    if (root !=nullptr){
        root ->color = BLACK;
    }
}
template<class K,class T>
void RedBlackTree<K,T>:: insert(const K&key,const T& value){
    // Nếu key đã tồn tại ko cần thực hiện gì nữa 
    if (this -> root == nullptr){
        root = new RBTNode(key,value);
        root->recolorToBlack(); // Thực hiện gán nút root thành BLACK
        return;
    } 
    // else if (contains(key)){     // Viết theo kiểu này dễ bị tốn dữ liệu vì duyệt qua cây tốn O(logN)
    //     return;
    // }
    // Chèn cặp (key,value) vào cây
    //2. Chèn như BST bình thường 
    RBTNode* parent = nullptr;
    RBTNode* curr = root;
    while (curr){
        parent = curr;
        if (key<curr->key){
            curr = curr ->left;
        } else if (key>curr->key){
            curr= curr->right;
        } else {
            return;        // Key tồn tại thoát 
        }
    }
    //3. Tạo node mới
    RBTNode*newNode = new RBTNode(key,value);
    newNode ->recolorToRed();
    newNode ->parent  = parent ;
    if (key<parent ->key){
        parent ->left = newNode;
    } else {
        parent ->right =newNode;
    }
    // Insert factor RB Tree
    insertRBHelper(newNode);
}
template<class K,class T>
typename RedBlackTree<K,T>:: RBTNode* RedBlackTree<K,T>::findMaxLeft(typename RedBlackTree<K,T>:: RBTNode*&node ){
    RBTNode* curr = node;
    while (curr->right){
        curr = curr->right; // giữ đc nút lớn nhất trong cây con bên trái
    }
    return curr;
}
template<class K,class T>
void RedBlackTree<K,T>::transParent (typename RedBlackTree<K,T>:: RBTNode*u, typename RedBlackTree<K,T>:: RBTNode*v){
    if(u->parent ==nullptr){
        this->root = v;
    } else if (u==u->parent ->left){
        u->parent->left = v;
    } else {
        u->parent ->right =v;
    }
    if (v != nullptr){
        v->parent = u->parent;
    }
}

template<class K,class T>
void RedBlackTree<K,T>::deleteHelper(typename RedBlackTree<K,T>::RBTNode* node, typename RedBlackTree<K,T>::RBTNode* parent) {
    while (node != root && (!node || node->color == BLACK)) {
        // Nếu node là nullptr, cần parent để xác định vị trí
        if (!parent) break;

        RBTNode* sibling = (node == parent->left) ? parent->right : parent->left;

        if (sibling && sibling->color == RED) {
            // Case 1: sibling đỏ
            sibling->color = BLACK;
            parent->color = RED;
            if (node == parent->left)
                rotateLeft(parent);
            else
                rotateRight(parent);
            sibling = (node == parent->left) ? parent->right : parent->left;
        }

        if (sibling) {
            // Case 2: sibling đen, 2 con đen
            bool leftBlack = !sibling->left || sibling->left->color == BLACK;
            bool rightBlack = !sibling->right || sibling->right->color == BLACK;

            if (leftBlack && rightBlack) {
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                // Case 3: Con gần đỏ, con xa đen
                if (node == parent->left && rightBlack) {
                    if (sibling->left) sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = parent->right;
                } else if (node == parent->right && leftBlack) {
                    if (sibling->right) sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = parent->left;
                }

                // Case 4: Con xa đỏ
                sibling->color = parent->color;
                parent->color = BLACK;
                
                if (node == parent->left) {
                    if (sibling->right) sibling->right->color = BLACK;
                    rotateLeft(parent);
                } else {
                    if (sibling->left) sibling->left->color = BLACK;
                    rotateRight(parent);
                }
                
                node = root; // Kết thúc
            }
        } else {
            // Không có sibling, lên parent
            node = parent;
            parent = node->parent;
        }
    }

    if (node) node->color = BLACK;
}

template<class K,class T>
void RedBlackTree<K,T>::remove(const K& key) {
    if (this->root == nullptr) return;
    
    // Tìm node cần xóa
    RBTNode* node = find(key);
    if (node == nullptr) return;
    
    RBTNode* p = node;           // Node sẽ bị xóa vật lý
    RBTNode* tmp = nullptr;      // Node thay thế
    RBTNode* tmpParent = nullptr; // Parent của tmp (quan trọng khi tmp là nullptr)
    Color pColor = p->color;
    
    if (node->left == nullptr) {
        // Chỉ có con phải hoặc không có con
        tmp = node->right;
        tmpParent = node->parent;
        transParent(node, node->right);
    } 
    else if (node->right == nullptr) {
        // Chỉ có con trái
        tmp = node->left;
        tmpParent = node->parent;
        transParent(node, node->left);
    } 
    else {
        // Có 2 con: tìm predecessor (max của cây con trái)
        RBTNode* predSucc = findMaxLeft(node->left);
        pColor = predSucc->color;
        tmp = predSucc->left;
        
        if (predSucc->parent == node) {
            // Predecessor là con trực tiếp của node
            tmpParent = predSucc;
        } else {
            // Predecessor không phải con trực tiếp
            tmpParent = predSucc->parent;
            transParent(predSucc, predSucc->left);
            predSucc->left = node->left;
            if (predSucc->left != nullptr) {
                predSucc->left->parent = predSucc;
            }
        }
        
        transParent(node, predSucc);
        predSucc->right = node->right;
        if (predSucc->right) {
            predSucc->right->parent = predSucc;
        }
        predSucc->color = node->color;
        
        // Cập nhật tmpParent nếu cần
        if (tmp) tmpParent = tmp->parent;
    }
    
    delete node;
    
    // Sửa cây nếu node bị xóa là đen
    if (pColor == BLACK) {
        deleteHelper(tmp, tmpParent);
    }
}
template<class K,class T>
typename RedBlackTree<K,T>::RBTNode* RedBlackTree<K,T>:: find (const K& key) const{
    // Tìm và trả về tới nút đầu tiên có khóa key
    if (root == nullptr) return root;
    RBTNode* curr = root;
    while (curr){
        if (curr->key==key) {
            return curr;
        } else if (curr->key>key){
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return nullptr;
}
template<class K,class T>
bool RedBlackTree<K,T>:: contains(const K& key) const{
    // Kiểm tra sự tồn tại của 1 khóa 
    if (this -> root == nullptr) return false;
    if (this->root->key ==key) return true;
    queue<RBTNode*> q;
    q.push(root);
    while (!q.empty())
    {
        RBTNode* curr = q.front();
        q.pop();
        if (!curr) continue; // bỏ qua nullptr
        if (curr->key==key){
            return true;
        } else if (key<curr->key){
            q.push(curr->left);
        } else {
            q.push(curr ->right);
        }
    }
    return false;
}
template<class K,class T>
typename RedBlackTree<K,T>:: RBTNode* RedBlackTree<K,T>::lowerBound(const K &key, bool &found) const{
    // Trả về địa chỉ có nút khóa nhỏ nhất lớn hơn bằng key 
    if (this->root == nullptr) {
        found =false;
        return nullptr;
    }
    RBTNode * curr = root,*res = nullptr;
    while(curr){
        if (curr->key==key){
            found = true;
            return curr;
        } else if (key<curr->key){
            res = curr;
            curr = curr -> left;
        } else {
            curr = curr -> right;
        }
    }
    if (res!=nullptr){
        found = true;
    } else {
        found = false;
    }
    return res; // Nếu nó ko là sự lựa chọn cuối cùng     
}
template<class K,class T>
typename RedBlackTree<K,T>:: RBTNode* RedBlackTree<K,T>::upperBound(const K &key, bool &found) const{
    // Trả về địa chỉ có nút khóa nhỏ nhất lớn hơn  key (khác biệt là ko có lấy giá trị bằng)
    // Tìm nút đầu tiên có khóa >key
    found = false;
    if (this -> root ==nullptr) {
        return nullptr;
    }
    RBTNode * curr = root,*res = nullptr;
    while (curr){
        if (key<curr->key){
            res= curr;        // Tìm ứng viên tốt hơn nhỏ hơn nhưng vẫn lớn hơn key
            curr = curr->left;
        } else {   // Đi sang phải để tìm node phù hợp với giá trị lớn hơn   // curr->key<=key ko thể là đáp án 
            curr = curr -> right;
        }
    }
    if (res!=nullptr){
        found = true;
    }
    return res;
}
//=================================================================
//  Hỗ trợ cho phương thức tìm topKNearrese trong vectorStore
//
//=================================================================
template<class K,class T>
 void RedBlackTree<K,T>::rangeQueryHelper(RBTNode*node,RBTNode* lowerNode, RBTNode* upperNode,std::vector<T*> &potentialRes) const{
    if (node == nullptr) return ;

    //Nếu node hiện tại nhỏ hơn lowerNode điều hướng 
    if (node ->key <lowerNode->key){
        rangeQueryHelper(node ->right,lowerNode,upperNode,potentialRes);
        return;
    }
    // Node hiện tại lớn hơn highNode
    if (node ->key > upperNode->key){
        rangeQueryHelper(node ->left,lowerNode,upperNode,potentialRes);
        return;
    }

    potentialRes.push_back(&(node->data));

    // Duyệt cả 2 nhánh 
    rangeQueryHelper(node->left,lowerNode,upperNode,potentialRes);
    rangeQueryHelper(node ->right,lowerNode,upperNode,potentialRes);
 }
// =====================================
// VectorRecord implementation
// =====================================
// VectorRecord::~VectorRecord(){
//     if (vector==nullptr) return;
//     delete vector;
//     vector = nullptr;
// }
//    VectorRecord(int _id,
//                  const std::string &_rawText,
//                  std::vector<float> *_vec,
//                  double _dist=0,
//                  double _norm = 0)
 std::vector<VectorRecord>VectorRecord:: shallowCopy(const std::vector<VectorRecord*>& allVecs){
    std::vector<VectorRecord> result;
    result.reserve(allVecs.size());

    for (auto* recPtr : allVecs) {
        result.emplace_back(recPtr->id,recPtr->rawText,recPtr->vector, recPtr->distanceFromReference,recPtr->norm); // copy pointer directly
    }
    return result;
}
std::vector<VectorRecord> VectorRecord::deepCopy(const std::vector<VectorRecord*>& allVecs) {
    std::vector<VectorRecord> result;
    result.reserve(allVecs.size());

    for (auto* recPtr : allVecs) {
        std::vector<float>* copiedVec = new std::vector<float>(*recPtr->vector);  //  tạo heap mới
        result.emplace_back(recPtr->id, recPtr->rawText, copiedVec, recPtr->distanceFromReference, recPtr->norm);
    }
    return result;
}
// std::vector<VectorRecord>VectorRecord::  deepCopy(const std::vector<VectorRecord*>& allVecs) {
//     std::vector<VectorRecord> result;
//     result.reserve(allVecs.size());

//     for (auto* recPtr : allVecs) {
//         // Tạo vector mới và copy nội dung
//         std::vector<float>* copiedVec = new std::vector<float>(*recPtr->vector);

//         // VectorRecord mới trỏ vào vùng nhớ mới
//         result.emplace_back(recPtr->id,recPtr->rawText,recPtr->vector, recPtr->distanceFromReference,recPtr->norm);
//     }
//     return result;
// }

// Overload operator << for VectorRecord - prints only the id
std::ostream &operator<<(std::ostream &os, const VectorRecord &record)
{
    os << record.id;        // Với mục đích in ra chỉ só id của các lớp VectorRecord == bản ghi của các vector
    return os;
}

// =====================================
// VectorStore implementation
// =====================================
VectorStore::VectorStore(int dimension,vector<float>*(*embeddingFunction)(const string&), const vector<float>& referenceVector){
    this -> dimension = dimension;
    this ->embeddingFunction = embeddingFunction;
        // Cần phải lưu lại reference vector này cần được tham chiếu trên này nè 
    this -> count =0;   // Ban đầu ko có bản ghi nào hết 
    // Sao chép reference vector của constructor vào member vector<float*>referencevector
    this -> referenceVector= new vector<float>(referenceVector);    
     // BỔ SUNG: khởi tạo AVL tree và normIndex
    this->vectorStore = new AVLTree<double, VectorRecord>();
    this->normIndex = new RedBlackTree<double, VectorRecord>(); // nếu bạn dùng AVLTree cho normIndex        // Cấp phát bộ nhớ mới cho referenceVector cần thiết 
}
VectorStore::~VectorStore(){
        // Giải phóng toàn bộ dữ liệu của cây AVL 
        if (referenceVector) delete referenceVector;
        referenceVector = nullptr;
        if (vectorStore) {
        delete vectorStore;   // AVLTree destructor xóa luôn VectorRecord*
        vectorStore = nullptr;
    }

    if (normIndex) {
        delete normIndex;     // RedBlackTree destructor xóa luôn VectorRecord*
        normIndex = nullptr;
    }
  
    count = 0;
}
int VectorStore::size(){
    return count;
}
bool VectorStore::empty(){
    return (count==0);
}
std::vector<float>* VectorStore::*embeddingFunction(const std::string& val){
        // Viết hàm ánh xạ để xử lý các rawTest trong dữ liệu RawTest 
        return embeddingFunction(val);
}
void VectorStore::clear(){
    // Xóa toàn bộ các vector và siêu dữ liệu khỏi cây AVL và red-back tree
    vectorStore->clear();           // Caay vectorStore nawmf trong caay AVL 
    normIndex->clear();
    // Vẫn giữ lại referenceVector 
    this ->rootVector = nullptr;
    this ->embeddingFunction = nullptr;
    this -> count =0;
    this ->averageDistance =0.0f;
}
// Tiền xử lý và quản lý dữ liệu 
vector<float>*VectorStore::preprocessing(string rawTest){
    // Gọi hàm của embedding fuction để chuyển hóa rawTest thành văn bản gốc 
    vector<float>* res= embeddingFunction(rawTest);
    int n =(int) res->size();
    if (n==dimension) return res;
    // Thực hiện chuẩn hóa chiều của vector embedding cho hợp lệ 
            // Nếu chiều của vector lớn hơn dimension cố định thì phải cắt bowit 
    if (n>dimension){
        while (n!=dimension){
            res->pop_back();
            n--;
        }
    }
            // Nếu chiều của vector nhỏ hơn dimension cố định thì phải thêm 0.0
    else if (n<dimension){
        for (int i=0;i<dimension-n;i++){
            res->push_back(0.0f);
        }
    }
    return res;
}
// void VectorStore::rebuildRootIfNeeded(){
//     // Tái thiết lập lại cây khi không thay đổi root hay average Distance ko bị dịch chuyển 
// }                                             // Xây dựng lại newTreeee nếu thật sự cần thiết 
// void VectorStore::rebuildTreeWithNewRoot(VectorRecord* newRoot){
//     // tái thiết lập cây xuấ hiện nút roor mới gần với averade distance hơn 
// }

double VectorStore :: getAverageDistance() const{
// Thực hiện tính khoảng cách trung bình của 
    return averageDistance;
}
typename AVLTree<double,VectorRecord> :: AVLNode *VectorStore :: buildNewAVL(const vector <VectorRecord>& record,int low, int high){
    if (low>high) return nullptr;
    int mid = low +(high-low)/2;   // Chọn điểm giữa để làm root tái cân bằng 

    AVLTree<double,VectorRecord> :: AVLNode* node = new AVLTree<double,VectorRecord>:: AVLNode(record[mid].distanceFromReference,record[mid]);

    // Xây dựng cây con trái 
    node ->pLeft = buildNewAVL(record,low,mid-1);

    // Xây dựng cây con bên phải 
    node ->pRight = buildNewAVL(record,mid +1,high);

    return node ;

}
vector<VectorRecord*>  VectorStore::  cloneAllRecord() const {
    vector<VectorRecord*> res;
   // ===================================================
    static vector<VectorRecord*> *desPtr = nullptr;
    struct Helper{
        static void collect (const VectorRecord& re){
            if (desPtr) desPtr->push_back(const_cast<VectorRecord*>(&re));
        }
    };
    desPtr = &res;
    vectorStore->inorderTraversal(&Helper::collect);
    desPtr = nullptr;
    // Static pointer tạm thời để truy cập từ hàm callback
 //   =======================================================
 
    return res;
}
std::vector<VectorRecord> VectorStore::cloneAllRecordSafe() const {
    std::vector<VectorRecord> res;
    if (!vectorStore) return res;

    // traversal trực tiếp, tạo bản copy an toàn
    vectorStore->inorderDeep([&res](const VectorRecord& rec){
        res.push_back(VectorRecord::deepCopySingle(&rec));
    });

    return res;
}

// Thêm hàm helper
VectorRecord* VectorStore::findRecordById(int id) {
    if (!vectorStore || !vectorStore->root) return nullptr;
    
    queue<AVLTree<double,VectorRecord>::AVLNode*> q;
    q.push(vectorStore->root);
    
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        
        if (node->data.id == id) {
            return &(node->data);
        }
        
        if (node->pLeft) q.push(node->pLeft);
        if (node->pRight) q.push(node->pRight);
    }
    
    return nullptr;
}


void VectorStore::addText(string rawTest){
    // Thêm một bản ghi mới vào kho từ chuỗi văn bản gốc 
    //1. Sử dụng preprocessing để chuyển hóa thành vector 
    int newId = getMaxId()+1;
    vector <float>*tmp = preprocessing(rawTest);
    // Mục đích dùng vector<mới> đề cập này tính toán lại reference vector trung bình để thiết lập lại rootVector trong cây AVL 
    // 2. Tính khoảng cách từ reference vector đến vector vừa tạo ra
    double disRefVector  = l2Distance(*tmp,*referenceVector);

    //4. Tính chuẩn Euclidean của vector 
    double newNorm = 0.0; // Dùng chuẩn này để xấy dựng cây redblack tree
    for (float x: *tmp){
        newNorm += x*x;
    }
    newNorm = std::sqrt(newNorm);
    // Khởi tạo 1 vector recorrd mới để thực hiện chèn vào 
    
    VectorRecord * res = new VectorRecord(newId,rawTest,tmp,disRefVector,newNorm);       // Tạo điều kiện chuẩn hóa các thông tin cần thiết để cung cấp dữ liệu cần thiết cho 1 cây AVL và RBT cây để chuyển hóa trực tiếp vào 
    
    //5. Nếu store rỗng, dặt vector này làm root
    if (empty()){
        // dặt vector record này làm root ạ 
        
        this ->rootVector = res;
        vectorStore->insert(res->distanceFromReference,*res);
        normIndex -> insert(res->norm,*res);
        this -> count = count +1;
        this -> averageDistance = disRefVector;
        return;
    } 
     // Chèn tạm vào xử lý trước đã 
    vectorStore->insert(res->distanceFromReference,*res);
    normIndex -> insert(res->norm,*res);
    // Lưu tất cả các VectorRecord* từ cây AVL 
    vector<VectorRecord*>  vectorAll= cloneAllRecord();
    vector<VectorRecord> clone = VectorRecord::deepCopy(vectorAll);
  // 3. Cập nhật khoảng cách trung bình mới sau khi chèn để xét nút 
    double total =0.0;

    for (VectorRecord* v : vectorAll){
         total += v->distanceFromReference;
    }
    averageDistance= total / vectorAll.size();

    // Tìm root mới nằm gần averageDistance nhất 
    VectorRecord * newRoot = vectorAll[0];

    double mini = std::fabs(newRoot -> distanceFromReference - averageDistance);
    for (VectorRecord* v: vectorAll){
        double diff = std::fabs(v->distanceFromReference- averageDistance);
        if (diff<mini){
            mini = diff;
            newRoot = v;
        }
    }
    
    // Chèn vector này vào cây AVL ==== BUILD LẠI CÂY CHO PHÙ HỢP 
    
    vectorStore->clear();   // Xóa cây trước 
    // Nếu ko thỏa cần tái cấu trúc của cây mà build lại  
    this -> rootVector = newRoot;
    vectorStore->insert(newRoot->distanceFromReference,*newRoot);
    vectorStore->root = buildNewAVL(clone,0,vectorAll.size()-1);
    // Thiết lập chỉ số id tiếp theo chính bằng maxId trong cây +1
    this -> count = vectorAll.size();
}

// ================================version 2.0===============================================

int VectorStore::idxTarget=0;
int VectorStore:: idxCount=0;
VectorRecord* VectorStore:: resRecord = nullptr;
void VectorStore::inorder_action(const VectorRecord& rec){
    if (resRecord !=nullptr) return;
    
    if(idxTarget == idxCount){
        resRecord= const_cast<VectorRecord*>(&rec);
        return;
    }
    idxCount++;
}
bool  VectorStore :: removeAt(int index){
    if (index <0 || index >= count){
        throw out_of_range("Index is invalid!");
    }
    // Xóa dữ liệu của nút tại vị trí index trong cây AVL 
    // vectorStore->remove()

    VectorRecord * tmp = this ->getVector(index);   // Tìm khóa để xóa tại vị trí indexx
    if (!tmp ) return false;
    // Thực hiện xóa trên cây AVL và cây RedBlack cho đồng bộ hóa 
    vectorStore->remove(tmp -> distanceFromReference);
    // Xóa dữ liệu của nút tạị vị trí index trong cây RedBlack Tree
    normIndex -> remove (tmp ->norm);
    // Thiết lập lại trật tự mới tìm lại vector trung bình mới để chọn root cho phù hợp 
    // Lưu tất cả các VectorRecord* từ cây AVL 
    vector<VectorRecord*>  vectorAll= cloneAllRecord();
    if (vectorAll.empty()) {
        this ->  rootVector = nullptr;
        this -> averageDistance = 0.0;
        this -> count = 0;
        return false;
    }
    // 3. Cập nhật khoảng cách trung bình mới sau khi xóađể xét nút 
    double total =0.0;

    for (VectorRecord* v : vectorAll){
        total += v->distanceFromReference;
    }
    averageDistance= total / vectorAll.size();

    // Tìm lại nút nằm gần với averageDistance nhất cho cây AVL 
     VectorRecord*  newRoot = vectorAll[0];

    double mini = std::fabs(newRoot ->distanceFromReference - averageDistance);
    for (VectorRecord *v: vectorAll){
        double diff = std::fabs(v->distanceFromReference- averageDistance);
        if (diff<mini){
            mini = diff;
            newRoot = v;
        }
    }
    // this -> rootVector = newRoot;
    // Chèn vector này vào cây AVL ==== BUILD LẠI CÂY CHO PHÙ HỢP 
    vector<VectorRecord> clone = VectorRecord::deepCopy(vectorAll);
    vectorStore->clear();   // Xóa cây trước 
    // Nếu ko thỏa cần tái cấu trúc của cây mà build lại  
    this -> rootVector = newRoot;
    vectorStore->insert(newRoot->distanceFromReference,*newRoot);
    vectorStore->root = buildNewAVL(clone,0,vectorAll.size()-1);
    // Thiết lập chỉ số id tiếp theo chính bằng maxId trong cây +1
    this -> count = vectorAll.size();
    
    return true;

}

//===================================================================
VectorRecord* VectorStore :: getVector(int index ){
    if (index<0 || index >= count){
        throw out_of_range("Index is invalid!");
    }
    // Duyệt cây AVL theo thứ inorder trả tại đúng vị trí chỉ số 
    idxTarget = index;
    idxCount =0;
    resRecord = nullptr;
    // Goi ham duyet theo nguyen tac ham avl 
    vectorStore->inorderTraversal(inorder_action);
    return resRecord;
}
string VectorStore::getRawText(int index){
    if (index<0 || index >= size()){
        throw out_of_range("Index is invalid!");
    }
    VectorRecord* tmp = getVector(index);
    return tmp -> rawText;
}
int VectorStore :: getId (int index){
    if (index <0 || index >= count){
        throw out_of_range("Index is invalid!");
    }
    VectorRecord* tmp = getVector(index);
    return tmp -> id;
}
int VectorStore :: getMaxId() {
    
    // int maxId = (int) -1e18;
    // vector<VectorRecord*> all = cloneAllRecord();
    // for (VectorRecord* rec : all) {
    //     if (rec->id > maxId) maxId = rec->id;
    // }

    // for (int i=0;i<count;i++){
    //     if (maxId <  getId(i)){
    //         maxId = getId(i);
    //     }
    // }
    // return maxId;
    int maxId = 0;
    auto all = cloneAllRecord();   // lấy toàn bộ VectorRecord*
    for (auto rec : all) {
        if (rec->id > maxId) maxId = rec->id;
    }
    return maxId;

}

//================================================
//              HÀM MERGE HỖ TRỢ BUILD NEWAVL
//================================================
void VectorStore::merge(vector<VectorRecord*>&arr, int low, int high, int mid){
    std::vector<VectorRecord*> left(arr.begin() + low, arr.begin() + mid + 1);
    std::vector<VectorRecord*> right(arr.begin() + mid + 1, arr.begin() + high + 1);
 
    int i=0, j=0, k = low;
    while (i<left.size() && j< right.size()){
        if (left[i]->distanceFromReference <= right[j]->distanceFromReference){
            arr[k++] = left [i++];
        } else {
            arr[k++] = right [j++];
        }
    }
    while (i<left.size()) arr[k++] = left[i++];
    while (j<right.size()) arr[k++] = right [j++];
}
void VectorStore::mergeSort(vector<VectorRecord*>&arr, int left, int right){
    if (left >= right) return;
    int mid = left + (right-left)/2;
    mergeSort(arr,left,mid);
    mergeSort(arr,mid +1,right);
    merge (arr,left,right,mid);

}
//================================================
// Thực hiện quản lý reference vector và hàm nhúng 
//================================================
void VectorStore:: setReferenceVector(const vector<float>& newReference){
    // Delete ref vector cũ để tránh leak memory 
    if (referenceVector){
        delete this ->referenceVector;
        this ->referenceVector = nullptr;
    }
    // Đỏi reference Vector sang vector mới 
    this -> referenceVector = new vector<float> (newReference);

    // Tính toán lại khoảng cách các reference vector
    vector<VectorRecord*> vectorAll = cloneAllRecord();
    // Trường hợp rỗng 
    if (vectorAll.empty()){
        this -> rootVector = nullptr;
        this -> averageDistance =0.0;
        this -> count =0;
        vectorStore-> clear();
        normIndex-> clear();
        return;
    }
    // Tự động tái cân bằng tính toán các khoảng cách từ reference vector đến tất cả vector có trong store hiện có 
    double total = 0.0;
    for (VectorRecord* v : vectorAll){
        v->distanceFromReference = l2Distance(*(v->vector),newReference); // Tính lại và cập nhật khoảng cách đến tham chiếu mới 
        total += v->distanceFromReference;
    }
    //Cập nhật lại và tìm đc khoảng cách trung bình để thiết lập lại root mới 
    this -> averageDistance= total / vectorAll.size();
    // Tìm lại nút nằm gần với averageDistance nhất cho cây AVL 
     VectorRecord*  newRoot = vectorAll[0];

    double mini = std::fabs(newRoot->distanceFromReference - averageDistance);
    for (VectorRecord* v: vectorAll){
        double diff = std::fabs(v->distanceFromReference- averageDistance);
        if (diff<mini){
            mini = diff;
            newRoot = v;
        }
    }
    
    // Sắp xếp toàn bộ các vectorAll theo thứ tự tăng dẫn của k/cách reference vector do thiết lập reference vector mới nên khoảng cách đến vector cũng thay đổi cần phải sort lại 
        // Thuận tiện cho việc xử lý tiền dữ liệu 
    mergeSort(vectorAll,0,vectorAll.size()-1);
    // tương ứng theo thứ tự của inorrder tree đã được tích hợp trong cloneRecord( duyệt theo trung thứ tự rồi )

    // Xây dựng lại cấu trúc cây AVL 
            // 1. Chia danh sách đã sắp xếp thành 2  nửa : nửa bên trái(nhỏ hơn rootVector) và nửa bên phải (lớn hơn rootvector) 
            //2. TRong một nửa của cây, chọn phần tử giữa làm gốc, sau đó đệ quy 2 phần còn lại của nhánh trái và nhánh phải 
            //3. Gắn cây con vừa xây dựng ở 2 nhánh trái và nhánh phải vào rootvector để tạo cây AVL hoàn chỉnh 
    // vector<VectorRecord> clone = VectorRecord::shallowCopy(vectorAll);
    vector<VectorRecord> clone = VectorRecord::deepCopy(vectorAll);
    vectorStore-> clear();
    this -> rootVector = newRoot;
    vectorStore -> insert(newRoot->distanceFromReference,*newRoot);
    vectorStore->root = buildNewAVL(clone,0,vectorAll.size()-1);
    this -> count = vectorAll.size();
}

vector<float>* VectorStore::getReferenceVector() const{
    return this ->referenceVector;
}

VectorRecord* VectorStore:: getRootVector() const {
    return this->rootVector;
}
void VectorStore::setEmbeddingFunction(std::vector<float>* (*newEmbeddingFunction)(const std::string&)){
    this ->embeddingFunction = newEmbeddingFunction;
}
void  VectorStore::inorderAction(AVLTree<double,VectorRecord>::AVLNode* root,void (*action)(std::vector<float> &, int, std::string &)){
    if (root ==nullptr) return;
    inorderAction(root->pLeft, action);
    action(*(root->data).vector,(root->data).id,(root->data).rawText);
    inorderAction(root->pRight, action);
}
// Thực hiệt duyệt và lặp

void VectorStore :: forEach(void(*action)(vector<float>&,int,string&)){
    // Duyệt toàn bộ bản ghi trong AVL tree theo thứ tự inorder (khoảng cách từ referenceVector)
    inorderAction(vectorStore->getRoot(),action);
    // Thực thi hàm action xuất hiện trên từng bản ghi 
}
vector<int> *VectorStore:: idListStore= nullptr;
void VectorStore::collectId(const VectorRecord& record ) {
    if (idListStore != nullptr) return;

    idListStore -> push_back(record.id);

}
vector<int> VectorStore::getAllIdsSortedByDistance() const {
    vector<int>idList;  // Thực hiện tạo lưu các mục id Vector theo thứ tự tăng dần
    // Thực hiện trả lại danh sách tất cả các id của bản ghi vector  sắp xếp theo khoảng cách tăng dẫn dến ref vector của cây AVL
    idListStore = &idList;
    vectorStore->inorderTraversal(&collectId);
    idListStore= nullptr;   // Đã dùng xong thì trả lại như ban đầu 
    // Lợi dụng tính chất của cây AVL đã dc cân bằng hợp lý duyệt inorder để lấy đc các thông số id tương ứng  
    return idList;
}

vector<VectorRecord*> VectorStore :: getAllVectorsSortedByDistance() const {
    vector<VectorRecord*> tmp;
    // Trả về danh sách các bản ghi vector đc sắp xếp theo khoảng cách tăng dần đến reference vector của cây AVL
    // vector<int> sortedID = getAllIdsSortedByDistance(); // Sắp theo kiểu inorder tăng dần trong cây AVL 
    // Đó chính là vector mà đc lưu trữ trong các bản ghi id có thể truy xuất các id này mà k cần lặp lại idea sinh 
    // Lý do: là hàm lấy getVector(int index) lấy chỉ số theo thứ tự inorder nên sẽ sinh ra đáp án tương ứng 
   
    if (vectorStore->getRoot()==nullptr) return tmp;
    static vector<VectorRecord*> *resVector= nullptr;
    struct Helper{
        static void sortedVector(const VectorRecord &record){
            resVector -> push_back(const_cast<VectorRecord*>(&record));
        }
    };
    resVector = &tmp;
    vectorStore->inorderTraversal(&Helper::sortedVector);
    resVector = nullptr;
    return tmp;
}
// Các chế độ đo khoảng cách 
double VectorStore :: cosineSimilarity(const vector<float>&v1,const vector<float>&v2)const {
    // Tính độ tương đồng cosine giữa 2 vector 
    // Đã xử lý ở bước tiền điều kiện nên rât yên tâm luôn 
    double multiple = 0.0, len1 =0.0, len2=0.0;
    for (int i =0 ;i<v1.size();i++){
        double A =v1[i], B= v2[i];
        multiple += A*B;
        len1 += A*A;
        len2+= B*B;
    }
    if(len1==0.0 || len2==0.0) return 0.0;
    return (multiple/ (std::sqrt(len1) * std :: sqrt(len2)));
}
double VectorStore :: l1Distance(const vector<float>&v1,const vector<float>&v2) const {
    // Tính khoảng cách Manhattan giữa 2 vector 
    // Đã xử lý tiền điều kiện phía trước nên đảm bảo các dimension sẽ bằng nhau 
    double tmp =0.0;
    for (int i=0;i<v1.size();i++){
        float A = v1[i];
        float B = v2[i];
        tmp += abs(A-B) ;
    }
    return tmp;
}
double VectorStore :: l2Distance(const vector<float>&v1,const vector<float>&v2) const {
     // Tính khoảng cách Euclidean của 2 vector ==> Thực hiện quy chuản cho norm cần thiết để xây dựng chuẩn cho cây RedBlack Trrreee
    double tmp =0.0;
    for (int i=0;i<v1.size();i++){
        float A = v1[i];
        float B = v2[i];
        tmp += (A-B) *(A-B);
    }
    return std::sqrt(tmp);
}
// Ưowcs lượng ngưỡng D từ k
double VectorStore::distanceByMetric(const std::vector<float>& a,const std::vector<float>& b,const std::string& metric) {
 // Tính khoảng cách tuyệt đội của 2 vector 
    if (metric != "cosine" && metric != "euclidean" && metric != "manhattan") {
        throw invalid_metric();
    }
    double res =0.0;
      // Thực hiện điều khiển các hàm metric Euclideam manhattan, cosine 
    if (metric=="cosine"){
        res = cosineSimilarity(a,b);
    } else if (metric =="manhattan"){
        res = l1Distance(a,b);
    } else {
        res = l2Distance(a,b);
    }
   return res;                               
}
// ước lượng ngưỡng D từ k 
double VectorStore::estimateD_Linear(const std::vector<float>& query, int k, double averageDistance, const std::vector<float>& reference, double c0_bias, double c1_slope){
    // Ước lượng bán kính D theo mô hình tuyến tính theo k dựa trên thống kê có sẵn của 1 vectorStore

    // dr = abs(abs(query-reference))   ,   D =| dr - averageDistance| +c1_slope*averageDistance*k + c0_bias
    // query : vector truy vấn , k: số láng giềng cần tìm    , averageDistance = mean||vector-r||
    
    // const vector<float>& refVector = *referenceVector;
    double Dr = l2Distance(query,reference);
    double D = std ::fabs(Dr-averageDistance) + c1_slope*averageDistance*k+c0_bias;
    if (D<=0) return 0.0;
    return D;
}
//Tìm kiếm láng giềng gần nhất  
int VectorStore::findNearest(const std::vector<float>& query, std::string metric){
    // Kiểm tra metric hợp lệ
    if (metric != "cosine" && metric != "euclidean" && metric != "manhattan") {
        throw invalid_metric();
    }
    if (count <= 0) return -1; 
    // Trả về id của vector Recorrd gần nhất với vector truy vấn 
    int bestIndex = -1;      
    double bestResult;

    // Khởi tạo giá trị ban đầu
    if (metric == "cosine") {
        bestResult = -1e9; // maximize
    } else {
        bestResult = 1e18; 
    }
    queue<AVLTree<double,VectorRecord>::AVLNode*> q;
    q.push(vectorStore->getRoot());
    double res=0;
    
    while (!q.empty()){
        AVLTree<double,VectorRecord>::AVLNode*curr = q.front();
        q.pop();
        VectorRecord *record = &(curr->data);
        if (metric == "cosine") {
            res = cosineSimilarity(query,*(record->vector));
            if (res > bestResult) {        // max cos
                bestResult = res;
                bestIndex = record->id;
                // cout<<bestResult<<" "<<bestIndex<<endl;
                if (bestResult==1) break;
            }
        } else if (metric == "euclidean") {
            res = l2Distance(query, *(record->vector));
            if (res < bestResult) {   // min distance     
                bestResult = res;
                bestIndex = record->id;
            }
        } else if (metric == "manhattan") {
            res = l1Distance(query, *(record->vector));
            if (res < bestResult) {        // min distance
                bestResult = res;
                bestIndex = record->id;
            }
        }
        // Duyệt tiếp cây để đi hết các node 

        if (curr->pLeft) {
            q.push(curr->pLeft);
        }
        if (curr->pRight){
            q.push(curr->pRight);
        }
    }
    // Bài toán yêu cầu trả về chỉ số id gần với referenceVector nhất 
    return bestIndex;
}
int *VectorStore::topKNearest(const std::vector<float> &query, int k, std::string metric){
    if (metric != "cosine" && metric != "euclidean" && metric != "manhattan") {
        throw invalid_metric();
    }
    if (k<=0 || k> vectorStore->getSize()){
        throw invalid_k_value();
    }

   
    // Tính chuẩn euclidean của truy vấn 
    double queryDistance = 0,tmp =0 ;
    for (float x : query){
        tmp += x*x;
    }
    queryDistance = std::sqrt(tmp);
    //Ước lượng bán kính D từ k bằng cách sử dụng phương thức estimateD_Linear
    double D = estimateD_Linear(query,k,this ->averageDistance,*referenceVector);
    // . Dùng lower_bound( nq − D )và upper_bound( nq + D ) trên red-black tree để thu dải ứng viên theo chuẩn,tạo tập ứng viên kích thước m.
    double lowerBound = queryDistance -D;
    double upperBound = queryDistance + D;
    vector <VectorRecord*> candidate;
    // std::vector<VectorRecord*>& refCandidate= candidate; 
    if (normIndex==nullptr || lowerBound > upperBound) return nullptr;
            // In ra giá trị m theo format: "Value m: <m>"
    bool found = false;
    normIndex->rangeQueryHelper(normIndex->getRoot(),normIndex->lowerBound(lowerBound,found),normIndex->upperBound(upperBound,found),candidate);
    cout<<"Value m: "<<candidate.size();
    //4. Tính khoảng cách thật theo các metric đã chọn  trên từng ứng cử 
        // Lưu các thông số của các candidat cần thiết đẻ tính dữ liệu cho chính xác nhất 
    struct CandiRecord {
        int id ; // nắm đc chỉ số id cất giữ 
        double distance;
    };
    vector<CandiRecord> disList; // Nắm đc các bản ghi record cho chính xác 
    for (auto x : candidate){
        double tmp =0;
        if (metric =="cosine"){
            tmp = cosineSimilarity(query,*(x->vector));

        } else if (metric=="euclidean"){
            tmp = l2Distance(query,*(x->vector));

        } else {
            //mahattan
            tmp = l1Distance(query,*(x->vector));
        }

        disList.push_back({x->id,tmp});
    }
    //5. Chọn top-k == sort theo phương thức lấy về những giá trị k gần nhất và trả về 1 mảng động int kích thước k theo thứ tự khoảng cách tăng dần 
    int n = disList.size();
    const double epsilon = 1e-9;
    // Thực hiện sort cho k phần tử để đáp ứng đúng yêu cầu đề bài 
    for (int i=0;i<std::min(k,n);i++){
        for (int j=i+1;j<n;j++){
            bool check = false;  // Ko cập nhật nuwac là dừng trả về kết quả 
            if(metric == "cosine"){         // Do tính chất của 1 maximixe để đánh đổi sự tương đồng 
                // Do có tính chất khác nên chia ra làm các trường hợp 
                if (disList[i].distance + epsilon < disList[j].distance){
                    check = false;
                } else if (disList[j].distance +epsilon <disList[i].distance){
                    check = true;
                } else check = (disList[i].id > disList[j].id);  // ràng buộc 
            } else {    // Do tính chất của 1 minimixe để đánh đổi 1 sự tương dồng 
                if (disList[i].distance > disList[j].distance+ epsilon){
                    check = true;
                } else if ( disList[i].distance +epsilon < disList[j].distance ){
                    check = false;
                } else {
                    check = (disList[i].id > disList[j].id);
                }

            }
            if (check) swap (disList[i],disList[j]);
        }
    }
    //6. Tạo kết quả lưu id 
    int * res = new int [k];
    for (int i=0;i<k;i++){
        res[i] = disList[i].id;
    }
    return res;

}
//==============================================================================
//
//                     HỖ TRỢ TRUY VẤN TÌM KIẾM 
//
//==============================================================================
void VectorStore:: preRangeQueryRoot(AVLTree<double,VectorRecord>::AVLNode* node,vector<int> &res,double &minDist, double &maxDist) const{
// Ý tưởng duyệt theo mô hình   AVL NODE =================

    if (node == nullptr) return;
    double d = l2Distance (*(node->data.vector),*referenceVector);
    if (d>=minDist && d<= maxDist) {
        res.push_back(node->data.id);
    }
    preRangeQueryRoot(node ->pLeft,res,minDist,maxDist);
    preRangeQueryRoot(node ->pRight,res,minDist,maxDist);
}

void VectorStore:: preRangeQuery(AVLTree<double,VectorRecord>::AVLNode* node,const vector<float>&query,vector<idDistance>&res, double &radius,string metric) const {
    if (!node) return;
    // Duyệt theo kiểu inorder để trả về kết quả 
    preRangeQuery(node->pLeft,query,res,radius,metric);
    VectorRecord &record = node ->data;
    double distance =0.0;
    if (metric =="cosine"){
        distance = cosineSimilarity(query,*(record.vector));
    } else if (metric == "euclidean"){
        distance = l2Distance(query,*(record.vector));
    } else if(metric == "manhattan") {
        distance = l1Distance(query,*(record.vector));

    } else throw invalid_metric();
    // Chỉ xét khoảng cách nằm trong bán kính theo comment của thầy 
    if (distance<radius){
        res.push_back({record.id,distance});
    }
    preRangeQuery(node->pRight,query,res,radius,metric);
}
void VectorStore:: preBoxQuery(AVLTree<double,VectorRecord>::AVLNode* node,const std::vector<float> &minBound, const std::vector<float> &maxBound,vector<int>&res) const{
    // tìm tất cả các vector đc định nghĩa dựa trên (minBound và maxBound)
    if (node==nullptr) return ;
    preBoxQuery(node->pLeft,minBound,maxBound,res);

    const vector<float> &tmp = *(node->data.vector);
    bool inBox = true;
    for (size_t i=0;i<tmp.size();i++){
        if (tmp[i] <= minBound[i] || tmp[i] >= maxBound[i]){
            inBox = false;
            break;
        }
    }
    if (inBox){
        res.push_back(node->data.id);
    }
    preBoxQuery(node->pRight,minBound,maxBound,res);
}

//===============================================================================
//
//                      TRUY VẤN PHẠM VI TÌM KIẾM
//
//================================================================================
int* VectorStore:: rangeQueryFromRoot(double minDist,double maxDist) const{
    if (vectorStore==nullptr|| vectorStore->getRoot()==nullptr) return nullptr;
    // Trả về tập tất cả các vector có khoảng cách từ refernce vector trên cây AVL nằm trong khoảng cách giới hạn cho phép
    vector<int> res;
    preRangeQueryRoot(vectorStore->getRoot(),res,minDist,maxDist);
    int * resId= new int [res.size()];
    for (size_t i=0;i<(int) res.size();i++){
        resId[i]= res[i];
    }
    // Trả về danh sách các id của vector thỏa mãn 
    return resId;
}
int* VectorStore:: rangeQuery(const std::vector<float> &query, double radius, std::string metric) const{
    if (metric != "cosine" && metric != "euclidean" && metric != "manhattan"){
        throw invalid_metric();
    }
    // Tìm tất cả các vector trên cây AVL có khoảng cách / độ tương đồng từ vector truy vấn nằm trong bán kính theo metric 
    vector<idDistance> tmpResult;
    // Thu đc Id và distance 1 cách trực tiếp luôn
    preRangeQuery(vectorStore->getRoot(),query,tmpResult,radius,metric);
    // Lưu giữ nhóm biến để tính toán sắp xếp lại dữ liệu tăng dần 
    for (size_t i=1;i< tmpResult.size();i++){
        idDistance key = tmpResult[i];
        int j = i-1;
        while (j>=0 && (tmpResult[j].distance >key.distance|| (tmpResult[j].distance == key.distance && tmpResult[j].id>key.id))){
            tmpResult[j+1] = tmpResult[j];
            j--;
        }
        tmpResult[j+1] =key;
    }
    // Đầu ra trả về danh sách các id thỏa mãn 
    int n = tmpResult.size();
    int *res = new int [n];
    for (int i=0;i<n;i++){
        res[i] = tmpResult[i].id;
    }
    return res;

}
int * VectorStore::boundingBoxQuery(const std::vector<float> &minBound, const std::vector<float> &maxBound) const{
    // Tìm tất cả các vector trên cây AVL nằm trong hộp giới hạn được định nghĩa  giới hạn bởi minBound và maxBound , tức là chỉ nằm trong (minBound,maxBound) ko nằm ở 2 đầu mút 
    vector<int>result;
    preBoxQuery(vectorStore->getRoot(),minBound,maxBound,result);
    // Trả về danh sách id các vectorStore thỏa mãn
    // Giair phóng ko hợp lệ đâu do chưa kịp trả về idList phù hợp thì đã xóa rồi 
    int * idList = new int [result.size()];
    for (size_t i=0;i< result.size();i++){
        idList[i] = result[i];
    }
    return idList;
}
//----------------------------------------------------------------------------------------------
//
// Các phương thức hỗ trợ nâng cao cho việc cây dựng cây AVL VÀ REDBLACK
//
//----------------------------------------------------------------------------------------------
 double VectorStore :: getMaxDistance()const {
    // Tìm khoảng cách lớn nhất từ reference vector dến bất kỳ vector nào trong vectorstore THỰC HIỆN DUYỆT TOÀN BỘ CÂY 
 
    // Thực hiện xét chạy ra tính từ khoảng cách reference vector tới bất kỳ vector nào trong record có thể 
    if (vectorStore == nullptr || vectorStore->empty()) return 0.0;
    // Thực hiện đi đến tận cùng của AVL tree bên nhánh phải  để tìm đc nút có gía trị là nút nhỏ nhất có khoảng cách đến reference vector 
   AVLTree<double,VectorRecord>::AVLNode * curr = vectorStore->getRoot();
   while (curr->pRight){
        curr = curr->pRight;
   }
   return curr ->key;               // Nắm lấy key distanceformRef trả về dữ liệu cần lấy 
}
double VectorStore::getMinDistance() const{
    // Tìm khoảng cách nhỏ nhất từ reference vector đến một vector trong vector store 
    if (vectorStore == nullptr || vectorStore->empty()) return 0.0;
    // Thực hiện đi đến tận cùng của AVL tree bên nhánh trái để tìm đc nút có gía trị là nút nhỏ nhất có khoảng cách đến reference vector 
    AVLTree<double,VectorRecord> :: AVLNode * curr = vectorStore->getRoot();
    while (curr->pLeft){
        curr = curr ->pLeft;
    }
    return curr->key;   // Trả về nút key giữ khoảng cách nhỏ nhất 
}
 VectorRecord VectorStore::computeCentroid(const std::vector<VectorRecord*>& records) const {
    // Tính centroid (tâm) của tập các vector theo công thức trung bình từng chiều O(mxd) với m là số vector , d là số chiều 
    if (records.empty()){
        throw invalid_argument("Non-exsiting centroid records.");
    }
    int m = (int) records.size();                       // Xác định kích thước của 1 vector 
    int d = (int) records[0]->vector->size();       // Xác định số chiều của 1 vector 
    // Giu vector ket quả trung tâm 
    vector<float>* centroid = new vector<float>(d,0.0f);

    for (const VectorRecord* reco :records){
        if ((int)reco->vector->size() != d){
            delete centroid;
            throw runtime_error("Vector dimension is error");
        }
        for (int i=0;i<d;i++){
            (*centroid)[i] += (*(reco->vector))[i];
        }
    }
    // Chia ra só kích thước reco ==> Lấy trung bình
    for (int i=0;i<d;i++){
        (*centroid)[i] /=m;
    }
    // // 4. Tính norm của centroid 
    // double normValue =0.0;
    // for (float x: *centroid){
    //     normValue +=x*x;
    // }
    // normValue = std::sqrt(normValue);
    /////////////////////
    string rawTmp = "centroid";
    VectorRecord res(-1,rawTmp,centroid);
    return res;
 }
 VectorRecord* VectorStore::findVectorNearestToDistance(double targetDistance) const{

    // Đánh giá vector trong store có khoảng cách từ reference vector gần nhất với giá trị targetDistance 
    if (vectorStore == nullptr || vectorStore->empty()) return nullptr;
    double minimum = 1e18;
    // tmp =abs(dis - targetDistance)==> min ==> VectorRecord 
    VectorRecord* record = nullptr ;
    queue <AVLTree<double,VectorRecord>::AVLNode*> q;
    q.push(vectorStore->getRoot());
    while (!q.empty()){
        AVLTree<double,VectorRecord>::AVLNode* curr = q.front();
        q.pop();
        double diff = std::fabs(curr->key - targetDistance);
        if (diff< minimum){
            minimum = diff;
            record = &(curr->data);
        }
        if(curr->pLeft) q.push(curr->pLeft);
        if (curr ->pRight) q.push(curr->pRight);
    }
    return record;
 }
// Explicit template instantiation for the type used by VectorStore
template class AVLTree<double, VectorRecord>;
template class AVLTree<double, double>;
template class AVLTree<int, double>;
template class AVLTree<int, int>;
template class AVLTree<double, string>;
template class AVLTree<int, string>;

template class RedBlackTree<double, VectorRecord>;
template class RedBlackTree<double, double>;
template class RedBlackTree<int, double>;
template class RedBlackTree<int, int>;
template class RedBlackTree<double, string>;
template class RedBlackTree<int, string>;
