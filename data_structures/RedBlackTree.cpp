#include "RedBlackTree.h"


RedBlackTree::RedBlackTree() : sentry() {
    // Root points to sentry at the beginning
    root = &sentry;

    rightRamification = "  ";
    rightRamification[0] = 218;
    rightRamification[1] = 196;

    leftRamification = "  ";
    leftRamification[0] = 192;
    leftRamification[1] = 196;

    verticalPipe = "  ";
    verticalPipe[0] = 179;
}

RedBlackTree::~RedBlackTree() {
    recursiveTreeRemoval(root);
}

void RedBlackTree::recursiveTreeRemoval(RBTNode *currNode) {
    if (currNode != &sentry) {
        // Remove left subtree
        recursiveTreeRemoval(currNode->left);
        // Remove right subtree
        recursiveTreeRemoval(currNode->right);
        // Remove current node
        delete currNode;
    }
}

std::ostream &operator<<(std::ostream &ostr, const RedBlackTree &rbt) {
    ostr << std::string(40, '-') << std::endl;
    //    rbt.printTree(ostr, rbt.root);
    rbt.printTree("", "", rbt.root, ostr);
    ostr << std::string(40, '#') << std::endl;
    return ostr;
}

void RedBlackTree::printTree(std::ostream &ostr, RBTNode *startNode, int space) const {
    // Gap between levels
    static const int COUNT = 10;

    // Base case
    if (startNode == &sentry)
        return;

    // Space for new heap's level
    space += COUNT;

    // Process right subtree first
    printTree(ostr, startNode->right, space);

    // Process current node
    std::cout << std::endl << std::endl << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << startNode->color << ":" << startNode->key << std::endl;

    // Process left subtree
    printTree(ostr, startNode->left, space);
}

void RedBlackTree::printTree(std::string currPipes, std::string currRamification, RBTNode *currNode,
                             std::ostream &ostr) const {
    std::string pipes;

    // Check if we are still on tree
    if (currNode != &sentry) {
        pipes = currPipes;
        // If we are going deeper, remove unnecessary pipe
        if (currRamification == rightRamification) {
            pipes[pipes.length() - 2] = ' ';
        }
        // Process right subtree first
        printTree(pipes + verticalPipe, rightRamification, currNode->right, ostr);

        // Print current element
        pipes = pipes.substr(0, currPipes.length() - 2);
        ostr << pipes << currRamification << currNode->color << ":" << currNode->key << std::endl;

        pipes = currPipes;
        // If we are going deeper, remove unnecessary pipe
        if (currRamification == leftRamification) {
            pipes[pipes.length() - 2] = ' ';
        }
        // Process left element
        printTree(pipes + verticalPipe, leftRamification, currNode->left, ostr);
    }
}

RBTNode *RedBlackTree::search(int searchedKey) const {
    RBTNode *currNode = root;
    while ((currNode != &sentry) && (currNode->key != searchedKey))
        if (searchedKey < currNode->key) {
            // Look at left subtree
            currNode = currNode->left;
        } else {
            // Look at right subtree
            currNode = currNode->right;
        }
    if (currNode == &sentry) {
        // Reached leaf or tree is empty
        return nullptr;
    }
    return currNode;
}

RBTNode *RedBlackTree::min(RBTNode *stRoot) {
    if (stRoot != &sentry)
        while (stRoot->left != &sentry) {
            stRoot = stRoot->left;
        }
    return stRoot;
}

RBTNode *RedBlackTree::successor(RBTNode *currNode) {
    RBTNode *upNode;
    if (currNode != &sentry) {
        if (currNode->right != &sentry) {
            // Look in right subtree
            return min(currNode->right);
        } else {
            // Look up in the tree
            upNode = currNode->parent;
            while ((upNode != &sentry) && (currNode == upNode->right)) {
                currNode = upNode;
                upNode = upNode->parent;
            }
            return upNode;
        }
    }
    return &sentry;
}

void RedBlackTree::rotateLeft(RBTNode *relNode) {
    RBTNode *rightOfRelNode, *upOfRelNode;

    rightOfRelNode = relNode->right;
    if (rightOfRelNode != &sentry) {
        upOfRelNode = relNode->parent;
        relNode->right = rightOfRelNode->left;
        if (relNode->right != &sentry) {
            relNode->right->parent = relNode;
        }

        rightOfRelNode->left = relNode;
        rightOfRelNode->parent = upOfRelNode;
        relNode->parent = rightOfRelNode;

        if (upOfRelNode != &sentry) {
            if (upOfRelNode->left == relNode) {
                upOfRelNode->left = rightOfRelNode;
            } else {
                upOfRelNode->right = rightOfRelNode;
            }
        } else {
            root = rightOfRelNode;
        }
    }
}

void RedBlackTree::rotateRight(RBTNode *relNode) {
    RBTNode *leftOfRelNode, *upOfRelNode;

    leftOfRelNode = relNode->left;
    if (leftOfRelNode != &sentry) {
        upOfRelNode = relNode->parent;
        relNode->left = leftOfRelNode->right;
        if (relNode->left != &sentry) {
            relNode->left->parent = relNode;
        }

        leftOfRelNode->right = relNode;
        leftOfRelNode->parent = upOfRelNode;
        relNode->parent = leftOfRelNode;

        if (upOfRelNode != &sentry) {
            if (upOfRelNode->left == relNode) {
                upOfRelNode->left = leftOfRelNode;
            } else {
                upOfRelNode->right = leftOfRelNode;
            }
        } else {
            root = leftOfRelNode;
        }
    }
}

void RedBlackTree::insert(int key) {
    auto *newNode = new RBTNode(key);
    RBTNode *uncleNode = nullptr;

    // Initialize fields of newNode
    newNode->left = &sentry;
    newNode->right = &sentry;
    newNode->parent = root;

    if (newNode->parent == &sentry) {
        // First element in tree
        root = newNode;
    } else {
        // Find proper place for the newNode
        while (true) {
            if (key < newNode->parent->key) {
                if (newNode->parent->left == &sentry) {
                    // Place found
                    newNode->parent->left = newNode;
                    break;
                }
                // Continue lookup
                newNode->parent = newNode->parent->left;
            } else {
                if (newNode->parent->right == &sentry) {
                    // Place found
                    newNode->parent->right = newNode;
                    break;
                }
                // Continue lookup
                newNode->parent = newNode->parent->right;
            }
        }
    }

    // Restore red-black tree conditions
    while (newNode != root && newNode->parent->color == 'R') {
        if (newNode->parent == newNode->parent->parent->left) {
            uncleNode = newNode->parent->parent->right;

            // Case 1
            if (uncleNode->color == 'R') {
                newNode->parent->color = 'B';
                uncleNode->color = 'B';
                newNode->parent->parent->color = 'R';
                newNode = newNode->parent->parent;
                continue;
            }

            // Case 2
            if (newNode == newNode->parent->right) {
                newNode = newNode->parent;
                rotateLeft(newNode);
            }

            // Case 3
            newNode->parent->color = 'B';
            newNode->parent->parent->color = 'R';
            rotateRight(newNode->parent->parent);

            // End restoration
            break;
        } else {
            uncleNode = newNode->parent->parent->left;

            // Mirror case 1
            if (uncleNode->color == 'R') {
                newNode->parent->color = 'B';
                uncleNode->color = 'B';
                newNode->parent->parent->color = 'R';
                newNode = newNode->parent->parent;
                continue;
            }

            // Mirror case 2
            if (newNode == newNode->parent->left) {
                newNode = newNode->parent;
                rotateRight(newNode);
            }

            // Mirror case 3
            newNode->parent->color = 'B';
            newNode->parent->parent->color = 'R';
            rotateLeft(newNode->parent->parent);

            // End restoration
            break;
        }
    }
    // Paint root to black
    root->color = 'B';
}

void RedBlackTree::remove(RBTNode *rmNode) {
    RBTNode *node1 = nullptr;
    RBTNode *node2 = nullptr;
    RBTNode *node3 = nullptr;

    if (rmNode->left == &sentry || rmNode->right == &sentry) {
        node2 = rmNode;
    } else {
        node2 = successor(rmNode);
    }

    if (node2->left != &sentry) {
        node3 = node2->left;
    } else {
        node3 = node2->right;
    }

    node3->parent = node2->parent;

    if (node2->parent == &sentry) {
        root = node3;
    } else if (node2 == node2->parent->left) {
        node2->parent->left = node3;
    } else {
        node2->parent->right = node3;
    }

    if (node2 != rmNode) {
        rmNode->key = node2->key;
    }

    // Restore red-black tree conditions
    if (node2->color == 'B') {
        while ((node3 != root) && (node3->color == 'B')) {
            if (node3 == node3->parent->left) {
                node1 = node3->parent->right;

                // Case 1
                if (node1->color == 'R') {
                    node1->color = 'B';
                    node3->parent->color = 'R';
                    rotateLeft(node3->parent);
                    node1 = node3->parent->right;
                }

                // Case 2
                if ((node1->left->color == 'B') && (node1->right->color == 'B')) {
                    node1->color = 'R';
                    node3 = node3->parent;
                    continue;
                }

                // Case 3
                if (node1->right->color == 'B') {
                    node1->left->color = 'B';
                    node1->color = 'R';
                    rotateRight(node1);
                    node1 = node3->parent->right;
                }

                // Case 4
                node1->color = node3->parent->color;
                node3->parent->color = 'B';
                node1->right->color = 'B';
                rotateLeft(node3->parent);

                // End of loop here
                node3 = root;
            } else {
                node1 = node3->parent->left;

                // Mirror case 1
                if (node1->color == 'R') {
                    node1->color = 'B';
                    node3->parent->color = 'R';
                    rotateRight(node3->parent);
                    node1 = node3->parent->left;
                }

                // Mirror case 2
                if ((node1->left->color == 'B') && (node1->right->color == 'B')) {
                    node1->color = 'R';
                    node3 = node3->parent;
                    continue;
                }

                // Mirror case 3
                if (node1->left->color == 'B') {
                    node1->right->color = 'B';
                    node1->color = 'R';
                    rotateLeft(node1);
                    node1 = node3->parent->left;
                }

                // Mirror case 4
                node1->color = node3->parent->color;
                node3->parent->color = 'B';
                node1->left->color = 'B';
                rotateRight(node3->parent);

                // End of loop here
                node3 = root;
            }
        }
    }
    // Paint root
    node3->color = 'B';

    delete node2;
}

void RedBlackTree::removeKey(int key) {
    auto *rmNode = this->search(key);
    if (rmNode != nullptr) {
        this->remove(rmNode);
    }
}
