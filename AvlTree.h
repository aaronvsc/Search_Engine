#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

using namespace std;

/*
 * @class AvlTree
 * @brief This implementation is based on the unbalanced binary search tree and adds hight information
 * to the nodes and a balance function to perform the needed rotations.
 */
template <typename Comparable>
class AvlTree {
   private:
    struct AvlNode {
        Comparable key;
        AvlNode *left;
        AvlNode *right;
        int height;                          // Height of the node used for balancing
        std::map<std::string, int> wordMap;  // Map to hold <documentID, frequency>

        AvlNode(const Comparable &theKey, AvlNode *lt = nullptr, AvlNode *rt = nullptr, int h = 0)
            : key{theKey}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;

    // Allowed imbalance in the AVL tree. A higher value will make balancing cheaper
    // but the search less efficient.
    static const int ALLOWED_IMBALANCE = 1;

   public:
    // Default constructor
    AvlTree() : root{nullptr} {
    }

    // Rule-of-3 Part 1: Copy constructor
    AvlTree(const AvlTree &rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    // Rule-of-3 Part 2: Destructor
    ~AvlTree() {
        makeEmpty();
    }

    // Rule-of-3 Part 3: Copy assignment operator
    AvlTree &operator=(const AvlTree &rhs) {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }

        return *this;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    // Method to find a node with a given key in the AVL tree
    AvlNode *findNode(const Comparable &x) const {
        return findNode(x, root);
    }

    std::map<std::string, int> getWordMapAtKey(const Comparable &key) const {
        AvlNode *node = findNode(key);
        if (node != nullptr) {
            return node->wordMap;
        } else {
            // Key not found, return an empty map
            return std::map<std::string, int>();
        }
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const {
        prettyPrintTree("", root, false);
    }

    /**
     * Make the tree empty.
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x, const std::string &documentID, int frequency) {
        insert(x, documentID, frequency, root);
    }

    // Calls writer helper and checks file stream
    void writeToTextFile(const std::string &filename) const {
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
            return;
        }
        writeHelper(root, outFile);
        outFile.close();
    }

    // Add this method to your AvlTree class
    void readFromTextFile(const std::string &filename) {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "Error: Unable to open file " << filename << " for reading." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::string key;
            std::string docID;
            int frequency;

            // Parse the line
            size_t colonPos = line.find(':');
            if (colonPos == std::string::npos) {
                std::cerr << "Error: Invalid file format. Colon not found." << std::endl;
                continue;
            }
            key = line.substr(0, colonPos);

            size_t openParenPos = line.find('(', colonPos);
            size_t commaPos = line.find(',', openParenPos);
            size_t closeParenPos = line.find(')', commaPos);
            if (openParenPos == std::string::npos || commaPos == std::string::npos || closeParenPos == std::string::npos) {
                std::cerr << "Error: Invalid file format. Parentheses or comma not found." << std::endl;
                continue;
            }
            docID = line.substr(openParenPos + 1, commaPos - openParenPos - 1);
            frequency = std::stoi(line.substr(commaPos + 1, closeParenPos - commaPos - 1));

            // Insert key and associated data into AVL tree
            insert(key, docID, frequency);
        }

        inFile.close();
    }

#ifdef DEBUG
    /**
     * Check if the tree is balanced and that the height of the nodes is correct.
     * Throws an exception if the tree is not balanced or the height is wrong.
     * This function is not necessary in production code since the tree is always balanced.
     * It is only compiled when DEBUG is defined.
     */

    int check_balance() {
        return check_balance(root);
    }
#endif

   private:
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */

    // Helper method to recursively write tree nodes to file
    void writeHelper(AvlNode *node, std::ofstream &outFile) const {
        if (node == nullptr) {
            return;
        }
        // Write current node's key and associated data to file
        outFile << node->key << ": ";
        for (const auto &item : node->wordMap) {
            outFile << "(" << item.first << ", " << item.second << ") ";
        }
        outFile << std::endl;
        // Recursively write left and right subtrees
        writeHelper(node->left, outFile);
        writeHelper(node->right, outFile);
    }

    void insert(const Comparable &x, const std::string &documentID, int frequency, AvlNode *&t) {
        if (t == nullptr) {
            t = new AvlNode{x};
            t->wordMap[documentID] = frequency;
            return;
        }

        if (x < t->key) {
            insert(x, documentID, frequency, t->left);
        } else if (t->key < x) {
            insert(x, documentID, frequency, t->right);
        } else {
            // Key already exists, update the map for the document ID and frequency
            if (t->wordMap.find(documentID) != t->wordMap.end()) {
                // Document ID exists, update the frequency
                t->wordMap[documentID] += frequency;
            } else {
                // Document ID does not exist, add a new entry
                t->wordMap[documentID] = frequency;
            }
        }

        // Rebalance the subtree rooted at the current node
        balance(t);
    }

    /**
     * Internal method to check if x is found in a subtree rooted at t.
     */
    bool contains(const Comparable &x, AvlNode *t) const {
        if (t == nullptr)
            return false;

        if (x == t->key)
            return true;  // Element found.
        else if (x < t->key)
            return contains(x, t->left);
        else
            return contains(x, t->right);
    }

    // Internal method to find a node with a given key in a subtree rooted at t
    AvlNode *findNode(const Comparable &x, AvlNode *t) const {
        if (t == nullptr) {
            return nullptr;  // Key not found
        }
        if (x == t->key) {
            return t;  // Key found, return the node
        } else if (x < t->key) {
            return findNode(x, t->left);  // Search in left subtree
        } else {
            return findNode(x, t->right);  // Search in right subtree
        }
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t) {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }

        AvlNode *newNode = new AvlNode(t->key, clone(t->left), clone(t->right), t->height);
        newNode->wordMap = t->wordMap;
        return newNode;
    }

    /**
     * Pretty print the tree structure
     * Uses preorder traversal with R and L swapped (NRL)
     *
     * Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
     */
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const {
        if (node == nullptr) {
            return;
        }

        std::cout << prefix;
        std::cout << (isRight ? "├──" : "└──") << node->key;

        // Print the word map inside the node
        for (const auto &item : node->wordMap) {
            std::cout << " (" << item.first << ": " << item.second << ")";
        }

        std::cout << std::endl;

        // Enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }

    // Balancing: AVL Rotations

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const {
        return t == nullptr ? -1 : t->height;
    }

    /**
     * 1. Performs rotations if the the the difference of the height stored in t's two child nodes
     *    more than ALLOWED_IMBALANCE.
     * 2. Updates the height information of the note t.
     *
     * Assumes that the high information in the child nodes is correct. This is guaranteed by calling
     * balance() recursively from the inserted node up to the tree node (see insert()). Rotations will
     * only be performed for node alpha (parent of the parent of the inserted node). For all other nodes,
     * only the height will be updated.
     */
    void balance(AvlNode *&t) {
        // special case: empty tree
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)  // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);  // case 1 (outside)
            else
                doubleWithLeftChild(t);                                     // case 2 (inside)
        } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)  // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);  // case 4 (outside)
            else
                doubleWithRightChild(t);  // case 3 (inside)
        }
        // else ... no imbalance was created

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2) {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1) {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1) {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

#ifdef DEBUG
    /**
     * Check if the tree is balanced and that the height of the nodes is correct.
     * Throws an exception if the tree is not balanced or the height is wrong.
     * This function is not necessary in production code since the tree is always balanced.
     * It is only compiled when DEBUG is defined.
     */

    int check_balance(AvlNode *node) {
        if (node == nullptr) {
            return -1;
        }

        // use LRN traversal to check the balance of the tree
        int lHeight = check_balance(node->left) + 1;
        int rHeight = check_balance(node->right) + 1;

        if (std::abs(lHeight - rHeight) > ALLOWED_IMBALANCE) {
            throw std::runtime_error("tree is not balanced in node with key " + std::to_string(node->key) + ".");
        }

        int trueNodeHeight = std::max(lHeight, rHeight);

        if (trueNodeHeight != node->height) {
            throw std::runtime_error("node does not have correct height value in node with key " + std::to_string(node->key) + ".");
        }

        return trueNodeHeight;
    }
#endif
};
#endif
