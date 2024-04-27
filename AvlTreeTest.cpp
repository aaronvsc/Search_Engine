#define CATCH_CONFIG_MAIN
#include "AvlTree.h"
#include "catch2/catch.hpp"

TEST_CASE("Empty AVL Tree") {
    AvlTree<std::string> avlTree;

    SECTION("Is empty") {
        REQUIRE(avlTree.isEmpty());
    }

    SECTION("Containment check") {
        REQUIRE_FALSE(avlTree.contains("example"));
    }
}

TEST_CASE("AVL Tree Insertion and Containment Check") {
    AvlTree<std::string> avlTree;

    avlTree.insert("example", "doc1", 5);
    avlTree.insert("example", "doc2", 3);
    avlTree.insert("test", "doc1", 7);
    avlTree.insert("test", "doc3", 2);
    avlTree.insert("data", "doc1", 10);
    avlTree.insert("Aaron", "doc4", 69);

    SECTION("Containment check") {
        REQUIRE(avlTree.contains("example"));
        REQUIRE(avlTree.contains("test"));
        REQUIRE(avlTree.contains("data"));
        REQUIRE(avlTree.contains("Aaron"));

        REQUIRE_FALSE(avlTree.contains("unknown"));  // Not inserted
    }

    SECTION("Document ID and frequency check") {
        // Check that the correct document IDs and frequencies are stored in the AVL tree
        // `find` allows you to check the map and its contents in the AvlNode
        auto exampleNode = avlTree.findNode("example");
        auto exampleMap = exampleNode->wordMap;
        REQUIRE(exampleMap.find("doc1") != exampleMap.end());
        REQUIRE(exampleMap.find("doc2") != exampleMap.end());
        REQUIRE(exampleMap["doc1"] == 5);
        REQUIRE(exampleMap["doc2"] == 3);

        auto testNode = avlTree.findNode("test");
        auto testMap = testNode->wordMap;
        REQUIRE(testMap.find("doc1") != testMap.end());
        REQUIRE(testMap.find("doc3") != testMap.end());
        REQUIRE(testMap["doc1"] == 7);
        REQUIRE(testMap["doc3"] == 2);

        auto aaronNode = avlTree.findNode("Aaron");
        auto aaronMap = aaronNode->wordMap;
        REQUIRE(aaronMap.find("doc4") != aaronMap.end());
        REQUIRE(aaronMap["doc4"] == 69);
    }

    SECTION("Print tree structure") {
        avlTree.prettyPrintTree();
    }
}

TEST_CASE("AVL Tree Copy Constructor and Assignment Operator") {
    AvlTree<std::string> avlTree;

    avlTree.insert("example", "doc1", 5);
    avlTree.insert("example", "doc2", 3);
    avlTree.insert("test", "doc1", 7);
    avlTree.insert("test", "doc3", 2);
    avlTree.insert("data", "doc1", 10);

    SECTION("Copy constructor") {
        AvlTree<std::string> avlTreeCopy(avlTree);

        REQUIRE(avlTreeCopy.contains("example"));
        REQUIRE(avlTreeCopy.contains("test"));
        REQUIRE(avlTreeCopy.contains("data"));

        // Print the copied tree structure
        avlTreeCopy.prettyPrintTree();
    }

    SECTION("Assignment operator") {
        AvlTree<std::string> avlTreeAssigned;
        avlTreeAssigned = avlTree;

        REQUIRE(avlTreeAssigned.contains("example"));
        REQUIRE(avlTreeAssigned.contains("test"));
        REQUIRE(avlTreeAssigned.contains("data"));

        // Print the assigned tree structure
        avlTreeAssigned.prettyPrintTree();
    }
}

TEST_CASE("AVL Tree Clearing") {
    AvlTree<std::string> avlTree;

    avlTree.insert("example", "doc1", 5);
    avlTree.insert("test", "doc2", 7);
    avlTree.insert("data", "doc1", 10);

    SECTION("Clearing the tree") {
        REQUIRE_FALSE(avlTree.isEmpty());

        avlTree.makeEmpty();

        REQUIRE(avlTree.isEmpty());
    }
}

TEST_CASE("AVL Tree Persistence") {
    AvlTree<std::string> test1;
    AvlTree<std::string> test2;

    test1.insert("example", "doc1", 5);
    test1.insert("example", "doc5", 9);
    test1.insert("test", "doc2", 7);
    test1.insert("data", "doc3", 10);

    test1.writeToTextFile("testPersistence.txt");
    test2.readFromTextFile("testPersistence.txt");
    // Making sure the contents of test 2 are the same as the contents of test 1.
    REQUIRE(test2.contains("example"));
    REQUIRE(test2.contains("test"));
    REQUIRE(test2.contains("data"));
    // Making sure the frequencies are still lined up with the docs
    auto aaronNode = test2.findNode("example");
    auto aaronMap = aaronNode->wordMap;
    REQUIRE(aaronMap["doc1"] == 5);
    REQUIRE(aaronMap["doc5"] == 9);
}
