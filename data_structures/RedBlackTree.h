#ifndef SDIZO_P1_REDBLACKTREE_H
#define SDIZO_P1_REDBLACKTREE_H

#include <climits>
#include <string>
#include <iostream>


// Node representation of Red-black tree
class RBTNode {
public:
    // Parent node's pointer
    RBTNode *parent;

    // Left child node's pointer
    RBTNode *left;

    // Right child node's pointer
    RBTNode *right;

    // Node's color
    char color;

    // Key is also the data
    int key;

    // Constructor used for sentry node creation
    RBTNode() : parent(this), left(this), right(this), color('B'), key(INT_MAX) {}

    // Constructor used for creation of new nodes
    explicit RBTNode(int key) : parent(nullptr), left(nullptr), right(nullptr), color('R'), key(key) {}
};


class RedBlackTree {
public:
    // Constructor
    RedBlackTree();

    // Destructor
    ~RedBlackTree();

    // Searches for searchedKey value in Nodes end return pointer to found node
    // nullptr is returned if the key does not exist
    RBTNode *search(int searchedKey) const;

    // Left rotation of tree branch relative to relNode
    void rotateLeft(RBTNode *relNode);

    // Right rotation of tree branch relative to relNode
    void rotateRight(RBTNode *relNode);

    // Inserts into tree new node with key of value: key
    void insert(int key);

    // Removes node from tree pointed by rmNode
    void remove(RBTNode *rmNode);

private:
    // Sentry node
    RBTNode sentry;

    // Root of the tree
    RBTNode *root;

    std::string cr, cl, cp;

    // Recursive algorithm clearing up nodes starting from currNode
    void recursiveTreeRemoval(RBTNode *currNode);

    // Searches for the lowest node in subtree with root stRoot
    RBTNode *min(RBTNode *stRoot);

    // Gets in-order successor of currNode and returns its address
    // nullptr is returned if node has no successor
    RBTNode *successor(RBTNode *currNode);

    // Prints red-black tree
    void printTree(std::string sp, std::string sn, RBTNode *currNode, std::ostream &ostr) const;

    friend std::ostream &operator<<(std::ostream &ostr, const RedBlackTree &rbt);
};

// Declared for convenient printing
std::ostream &operator<<(std::ostream &ostr, const RedBlackTree &rbt);


#endif //SDIZO_P1_REDBLACKTREE_H
