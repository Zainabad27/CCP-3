#include <algorithm>
#include <iostream>
#include <string>




#include "Tree.h"
// using namespace std;

AVLNode::AVLNode(registration reg)
    : data(reg), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::height(AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLTree::balanceFactor(AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

AVLNode *AVLTree::rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode *AVLTree::leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode *AVLTree::insert(AVLNode *node, registration reg)
{
    if (node == nullptr)
        return new AVLNode(reg);

    if (reg.regID < node->data.regID)
        node->left = insert(node->left, reg);
    else if (reg.regID > node->data.regID)
        node->right = insert(node->right, reg);
    else
        return node; // duplicate regID not allowed

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1)
    {
        if (balanceFactor(node->left) >= 0)
        {
            return rightRotate(node); // LL
        }
        else
        {
            node->left = leftRotate(node->left); // LR
            return rightRotate(node);
        }
    }

    if (balance < -1)
    {
        if (balanceFactor(node->right) <= 0)
        {
            return leftRotate(node); // RR
        }
        else
        {
            node->right = rightRotate(node->right); // RL
            return leftRotate(node);
        }
    }

    return node;
}

AVLNode *AVLTree::minValueNode(AVLNode *node)
{
    AVLNode *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

AVLNode *AVLTree::deleteNode(AVLNode *root, int regID)
{
    if (root == nullptr)
        return root;

    if (regID < root->data.regID)
        root->left = deleteNode(root->left, regID);
    else if (regID > root->data.regID)
        root->right = deleteNode(root->right, regID);
    else
    {
        if ((root->left == nullptr) || (root->right == nullptr))
        {
            AVLNode *temp = root->left ? root->left : root->right;

            if (temp == nullptr)
            {
                delete root;
                return nullptr;
            }
            else
            {
                AVLNode *old = root;
                root = temp;
                delete old;
            }
        }
        else
        {
            AVLNode *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data.regID);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + std::max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && balanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && balanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void AVLTree::inorder(AVLNode *root)
{
    if (root != nullptr)
    {
        inorder(root->left);
        std::cout << "RegID: " << root->data.regID
             << " | Customer: " << root->data.cusName
             << " | Workshop: " << root->data.workshopName
             << " | Date: " << root->data.WorkshopDate
             << " | Seats: " << root->data.seatsBooked
             << "\n\n";
        inorder(root->right);
    }
}

// Returns pointer to node if found, nullptr otherwise
AVLNode *AVLTree::search(AVLNode *root, int regID)
{
    if (root == nullptr || root->data.regID == regID)
        return root;
    if (regID < root->data.regID)
        return search(root->left, regID);
    return search(root->right, regID);
}

void AVLTree::insert(registration reg) { root = insert(root, reg); }

void AVLTree::remove(int regID) { root = deleteNode(root, regID); }

// Returns a pointer to the found registration, or nullptr
registration *AVLTree::search(int regID)
{
    AVLNode *result = search(root, regID);
    if (result)
        return &result->data;
    return nullptr;
}

void AVLTree::printInorder() { inorder(root); }
