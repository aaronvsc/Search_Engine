#define CATCH_CONFIG_MAIN
#include "AvlTree.h"
#include "catch2/catch.hpp"

TEST_CASE("Empty AVL Tree") {
    AvlTree<int> avlTree;

    SECTION("Is empty") {
        REQUIRE(avlTree.isEmpty());
    }

    SECTION("Containment check") {
        REQUIRE_FALSE(avlTree.contains(10));
    }
}

TEST_CASE("AVL Tree Insertion and Containment Check") {
    AvlTree<int> avlTree;

    avlTree.insert(10);
    avlTree.insert(5);
    avlTree.insert(15);
    avlTree.insert(3);
    avlTree.insert(7);
    avlTree.insert(12);

    SECTION("Containment check") {
        REQUIRE(avlTree.contains(10));
        REQUIRE(avlTree.contains(5));
        REQUIRE(avlTree.contains(15));
        REQUIRE(avlTree.contains(3));
        REQUIRE(avlTree.contains(7));
        REQUIRE(avlTree.contains(12));
        REQUIRE_FALSE(avlTree.contains(20));  // Not inserted
    }

    SECTION("Print tree structure") {
        avlTree.prettyPrintTree();
    }
}

TEST_CASE("AVL Tree Copy Constructor and Assignment Operator") {
    AvlTree<int> avlTree;

    avlTree.insert(10);
    avlTree.insert(5);
    avlTree.insert(15);
    avlTree.insert(3);
    avlTree.insert(7);
    avlTree.insert(12);

    SECTION("Copy constructor") {
        AvlTree<int> avlTreeCopy(avlTree);

        REQUIRE(avlTreeCopy.contains(10));
        REQUIRE(avlTreeCopy.contains(5));
        REQUIRE(avlTreeCopy.contains(15));
        REQUIRE(avlTreeCopy.contains(3));
        REQUIRE(avlTreeCopy.contains(7));
        REQUIRE(avlTreeCopy.contains(12));

        // Print the copied tree structure
        avlTreeCopy.prettyPrintTree();
    }

    SECTION("Assignment operator") {
        AvlTree<int> avlTreeAssigned;
        avlTreeAssigned = avlTree;

        REQUIRE(avlTreeAssigned.contains(10));
        REQUIRE(avlTreeAssigned.contains(5));
        REQUIRE(avlTreeAssigned.contains(15));
        REQUIRE(avlTreeAssigned.contains(3));
        REQUIRE(avlTreeAssigned.contains(7));
        REQUIRE(avlTreeAssigned.contains(12));

        // Print the assigned tree structure
        avlTreeAssigned.prettyPrintTree();
    }
}

TEST_CASE("AVL Tree Clearing") {
    AvlTree<int> avlTree;

    avlTree.insert(10);
    avlTree.insert(5);
    avlTree.insert(15);

    SECTION("Clearing the tree") {
        REQUIRE_FALSE(avlTree.isEmpty());

        avlTree.makeEmpty();

        REQUIRE(avlTree.isEmpty());
    }
}
