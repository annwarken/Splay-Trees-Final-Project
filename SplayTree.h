#include <iostream>

struct Node {
    int data;
    Node *left, *right, *parent;
};

class SplayTree {
    Node *root;

    Node* makeNode(int data) {
        Node* node = new Node();
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        node->parent - NULL;
        return node;
    }

    // single right rotation
    void zig(Node* node) {
        Node* p = node->parent; 
        Node* r = node->right;

        //set node's new values
        node->parent = NULL; //root has no parent
        node->right = p; //prev parent becomes right child

        //set prev parent's new values
        p->parent = node; //parent becomes node's right child
        p->left = r; //takes node's prev right child as its left child

        if(r != NULL) r->parent = p; 
    }

    // single left rotation
    void zag(Node* node) {
        Node* p = node->parent; 
        Node* l = node->left;

        //set node's new values
        node->parent = NULL; //root has no parent
        node->left = p; //prev parent becomes left child

        p->parent = node; //parent becomes node's left child
        p->right = l; //takes node's prev left child as its right child

        if(l != NULL) l->parent = p;
    }

    // double right rotation
    void zig_zig(Node* node) {
        Node* p = node->parent;
        Node* gp = p->parent;

        //store right children of node and parent 
        Node* A = node->right;
        Node* B = p->right;

        //set node's new values
        node->parent = gp->parent; //root has no parent
        node->right = p; 

        //set parent's new values
        p->parent = node;
        p->left = A;
        p->right = gp;

        //set grandparents's new values
        gp->parent = p;
        gp->left = B;

        //if "root" parent is not NULL (not yet root)
        if (node->parent != NULL)
        {
            if (node->parent->left == gp) 
                node->parent->left = node;
            else 
                node->parent->right = node;
        }
        
        //if the right children are not NULL set their parents 
        if (A != NULL) A->parent = p;
        if (B != NULL) B->parent = gp;
    }

    // double left rotation
    void zag_zag(Node* node) {
        Node* p = node->parent;
        Node* gp = p->parent;

        //store left children of node and parent
        Node* A = p->left;
        Node* B = node->left;

        //set node's new values
        node->parent = gp->parent; 
        node->left = p;

        //set parents's new values
        p->parent = node;
        p->left = gp;
        p->right = B;

        //set grandparents's new values
        gp->parent = p;
        gp->right = A;

        //if "root" parent is not NULL (not yet root)
        if (node->parent != NULL)
        {
            if (node->parent->left == gp) 
                node->parent->left = node;
            else 
                node->parent->right = node;
        }
        
        //if the left children are not NULL set their parents 
        if (A != NULL) A->parent = gp;
        if (B != NULL) B->parent = p;
    }
    
    // right then left rotation 
    void zig_zag(Node* node) {
        Node* p = node->parent;
        Node* gp = p->parent;

        Node* A = node->left;
        Node* B = node->right;

        node->parent = gp->parent;
        node->left = p;
        node->right = gp;

        p->parent = node;
        p->right = A;

        gp->parent = node;
        gp->left = B;
        
        if (node->parent != NULL)
        {
            if (node->parent->left == gp) 
                node->parent->left = node;
            else 
                node->parent->right = node;
        }
        
        if (A != NULL) A->parent = p;
        if (B != NULL) B->parent = gp;
    }

    //left then right rotation
    void zag_zig(Node* node) {
        Node* p = node->parent;
        Node* gp = p->parent;

        Node* A = node->left;
        Node* B = node->right;

        node->parent = gp->parent;
        node->left = gp;
        node->right = p;

        p->parent = node;
        p->left = B;

        gp->parent = node;
        gp->right = A;
        
        if (node->parent != NULL)
        {
            if (node->parent->left == gp) 
                node->parent->left = node;
            else 
                node->parent->right = node;
        }
        
        if (A != NULL) A->parent = gp;
        if (B != NULL) B->parent = p;
    }

    void splay(Node *node) {
        //keep making rotations until node is at the root of the tree
        while (node->parent != NULL) {
            Node *p = node->parent;
            Node *gp = p->parent;

            if(gp == NULL) { //if node one away from the root
                if(p->left == node) 
                    zig(node);
                else   
                    zag(node);
            } //otherwise two rotations have to be made 
            else if(gp->left == p && p->left == node) { 
                    zig_zig(node);
            } 
            else if (gp->right == p && p->right == node) {
                    zag_zag(node);
            }
            else {
                if(p->right == node)
                    zig_zag(node);
                else    
                    zag_zig(node);
            }
        }
        //update the root to be the desired node
        this->root = node;
    }

    Node* find(int data) {
        Node *ret = NULL;
        Node *tmp = this->root;

        //while there are still nodes to search
        while(tmp != NULL)
        {
            if(data < tmp->data) //data will be in left child tree
                tmp = tmp->left;
            else if(data > tmp->data) //data will be in right child tree
                tmp = tmp->right;
            else{ //data has been found
                ret = tmp;
                break;
            }
        }

        //splay the node to the root
        if (ret != NULL) 
            splay(ret);

        return ret;
    }

    Node* max(Node* root) {
        Node* tmp = root;
        while (tmp->right != NULL) {
            tmp = tmp->right;
        }
        return tmp;
    }

    Node* min(Node* root) {
        Node* tmp = root;
        while (tmp->left != NULL) {
            tmp = tmp->left;
        }
        return tmp;
    }

    void print(Node* root) {
        if (root == NULL) {
            std::cout << "x";
            return;
        }

        std::cout << "(" << root->data << " ";
        print(root->left);
        std::cout << " ";
        print(root->right);
        std::cout << ")";
    }

///////////////////////////////////////////////////////////////////////////////////

public:
    void insert(int data) {
        if(root == NULL) { //tree is empty
            root = makeNode(data);
            return;
        }

        Node* tmp = root;

        while(tmp != NULL) {
            if(data < tmp->data) { //node will be insert to the left
                if(tmp->left == NULL) { //if at the end of tree insert new node
                    Node* newNode = makeNode(data);
                    tmp->left = newNode;
                    newNode->parent = tmp;
                    splay(newNode);
                    return;
                }
                else
                    tmp = tmp->left; //if not travel further down
            }
            else if(data > tmp->data) { //node will be inserted to the right 
                if(tmp->right == NULL) { //if at the end of tree insert new node
                    Node* newNode = makeNode(data);
                    tmp->right = newNode;
                    newNode->parent = tmp;
                    splay(newNode);
                    return;
                }
                else 
                    tmp = tmp->right; //if not travel further down
            }
            else { //if data is already in the tree
                splay(tmp);
                return;
            }
        }
    }

    void remove(int data) {
        Node *del = find(data);

        if (del == NULL) return; //if the data is not in the tree do nothing

        //store left and right children
        Node *l = del->left;
        Node *r = del->right;

        //need to find new node to replace the root

        if (l == NULL && r == NULL) { //if was the only node in tree
            this->root = NULL;
        }
        else if (l == NULL) {
            Node *m = min(r);
            splay(m);
        }
        else if (r == NULL)
        {
            Node *m = max(l);
            splay(m);
        }
        else
        {
            Node *m = max(l);
            splay(m);
            m->right = r;
            r->parent = m;
        }
        delete del;
    }
   
    void splay(int data) {
        Node* node = find(data);
    }

    bool contains(int data) {
        if(find(data) != NULL) //if there is a node in the tree with this data
            return true;
        else
            return false;
    }

    void print() {
        std::cout << "Splay Tree:" << std::endl;
        print(root);
        std::cout << std::endl;
    }
};

