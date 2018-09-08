/*
* sjtuoj 1050:可合并堆裸题
* Status: RE (20/100)
左偏树写错了？？
*/
#include <cstddef>
#include <functional>
#include <iostream>
using namespace std;
const int MAXN = 300000 + 7;
template<typename T, class Compare = std::greater<T>>
class priority_queue {
private:
    Compare cmp = Compare();
    struct Node {
        T *key = (T *) ::operator new[](sizeof(T));
        int dist;
        Node *left;
        Node *right;

        Node() {}

        Node(T *lkey, int ldist, Node *ll, Node *lright) {
            new(key) T(lkey[0]);
            dist = ldist;
            left = ll;
            right = lright;

        }

        Node(T lkey, int ldist, Node *ll, Node *lright) {
            new(key) T(lkey);
            dist = ldist;
            left = ll;
            right = lright;

        }

        Node(T lkey) {
            key = lkey;
            left = nullptr;
            right = nullptr;
            dist = 0;
        }
    };

    Node *mRoot;


    template<typename U>
    inline void swap(U &a, U &b) {
        U tmp = a;
        a = b;
        b = tmp;
    }

    Node *MergeIn(Node *a, Node *b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (cmp(*(a->key), *(b->key))) swap<Node *>(a, b);
        a->right = MergeIn(b, a->right);
        if ((a->left != nullptr ? a->left->dist : -1) < (a->right != nullptr ? a->right->dist : -1))
            swap<Node *>(a->left, a->right);
        if (a->right == nullptr) a->dist = 0;
        else a->dist = a->right->dist + 1;
        return a;
    }

    void deleteup(Node *p) {
        if (p == nullptr) return;
        if (p->left != nullptr) deleteup(p->left);
        if (p->right != nullptr) deleteup(p->right);
        p->key->~T();
        ::operator delete[](p->key);
        delete p;
        p = nullptr;
    }

public:
    int len;
    /**
     * TODO constructors
     */
    priority_queue() {
        mRoot = nullptr;
        len = 0;
    }

    void DeepCopy(Node *Current, Node *&Copied) {
        if (Current == nullptr) return;
        if (Current->left != nullptr) DeepCopy(Current->left, Copied);
        if (Current->right != nullptr) DeepCopy(Current->right, Copied);
        Node *tmp2 = new Node(Current->key, 0, nullptr, nullptr);
        Copied = MergeIn(Copied, tmp2);
        return;
    }

    priority_queue(const priority_queue &other) {
        mRoot = nullptr;
        DeepCopy(other.mRoot, mRoot);
        len = other.len;
    }

    ~priority_queue() {
        if (len != 0)deleteup(mRoot); //这个是有析构函数的状态
    }

    priority_queue &operator=(const priority_queue &other) {
        if (other.mRoot != this->mRoot) {
            deleteup(mRoot);
            mRoot = nullptr;
            DeepCopy(other.mRoot, mRoot);
            len = other.len;
        }
        return *this;
    }

    const T &top() const {
        return mRoot->key[0];
    }

    void push(const T &e) {
        Node *p = new Node(e, 0, nullptr, nullptr);
        mRoot = MergeIn(p, mRoot);
        len++;
    }

    void pop() {
        Node* tmp = mRoot;
        mRoot = MergeIn(mRoot->left, mRoot->right);
        tmp->key->~T();
        ::operator delete[](tmp->key);
        delete tmp;
        tmp = nullptr;
        len--;
    }

    size_t size() const {
        return len;
    }

    bool empty() const {
        return len == 0;
    }

    void merge(priority_queue &other) {
        mRoot = MergeIn(mRoot, other.mRoot);
        len += other.len;
        other.len = 0;
        other.mRoot = nullptr;

    }
};

priority_queue<int> pqlist[MAXN];
bool avail[MAXN];
int n, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        int t;
        cin >> t;
        pqlist[i].push(t);
        avail[i] = true;
    }
    int opt, a, b;
    for(int i = 0;i < m; ++i){
        cin >> opt;
        if(opt == 0){
            cin >> a >> b;
            pqlist[a].merge(pqlist[b]);
            avail[b] = false;
        } else if(opt == 1){
            cin >> a;
            if(!avail[a]) cout << -1 << "\n";
            else {
                cout << pqlist[a].top() << "\n";
                pqlist[a].pop();
                //if(pqlist[a].empty()) avail[a] = false;
            }
        } else if(opt == 2){
            cin >> a >> b;
            pqlist[a].push(b);
        }
    }
    return 0;
}
