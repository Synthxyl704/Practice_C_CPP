#include <iostream>
#include <cstdlib> 
#include <cstdint>

struct Node {
    std::int32_t dataNum;
    Node *leftNode;
    Node *rightNode;

    Node(size_t valueNum) {
        dataNum = valueNum;
        leftNode = nullptr;
        rightNode = nullptr;
    }
};

#include <iomanip>

// print types by AI

void printTreeType1(Node* root, int space = 0, int indent = 6) {
    if (root == nullptr) return;

    space += indent;

    // Print right subtree first (so it appears on top)
    printTreeType1(root->rightNode, space, indent);

    // Print current node
    std::cout << std::setw(space) << root->dataNum << "\n";

    // Print left subtree
    printTreeType1(root->leftNode, space, indent);
}

void printTreeType2(Node* node, std::string prefix = "", bool isLast = true) {
    if (!node) return;

    // Print current node
    std::cout << prefix;
    std::cout << (isLast ? "└── " : "├── ");
    std::cout << node->dataNum << "\n";

    // Prepare prefix for children
    std::string newPrefix = prefix + (isLast ? "    " : "│   ");

    // Case: both children exist
    if (node->leftNode && node->rightNode) {
        printTreeType2(node->leftNode, newPrefix, false); // left is NOT last
        printTreeType2(node->rightNode, newPrefix, true); // right IS last
    }
    // Only left child
    else if (node->leftNode) {
        printTreeType2(node->leftNode, newPrefix, true);
    }
    // Only right child
    else if (node->rightNode) {
        printTreeType2(node->rightNode, newPrefix, true);
    }
}

auto BST(Node *(&root), std::int32_t valueToInsert) -> void { // this is new
    if (root == nullptr) {
        root = new Node(valueToInsert);
        return; std::cout << "added root value " << root->dataNum << " to tree\n";
    }

    (valueToInsert < root->dataNum) ? BST(root->leftNode, valueToInsert) 
                                    : BST(root->rightNode, valueToInsert);
} 

std::int32_t main(std::int32_t argc, char *argv[]) {
    std::cout << "\n";

    Node *root {new Node(1)};

    BST(root, 2); BST(root, 42); BST(root, 8);
    BST(root, 1); BST(root, 30); BST(root, 6);
    
    printTreeType1(root);

    std::cout << "\n";

    return static_cast<std::int32_t>(NULL);
}
