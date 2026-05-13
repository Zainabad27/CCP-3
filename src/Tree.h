#pragma once  
#include <string>

struct registration {
    int regID;
    std::string cusName;
    std::string workshopName;
    std::string WorkshopDate;
    int seatsBooked;
};

class AVLNode {
public:
    registration data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(registration reg);  
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* node, registration reg);
    AVLNode* minValueNode(AVLNode* node);
    AVLNode* maxValueNode(AVLNode* node);
    AVLNode* deleteNode(AVLNode* root, int regID);
    void inorder(AVLNode* root);
    AVLNode* search(AVLNode* root, int regID);

public:
    AVLTree();
    AVLNode* rootNode() { return root; }
    int GetNodeCount(AVLNode* node);  
    int GetMaxNodeID(AVLNode* node);      
    void insert(registration reg);
    void remove(int regID);
    registration* search(int regID);
    void printInorder();
};