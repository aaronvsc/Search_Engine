#define CATCH_CONFIG_MAIN
#include "DocumentParser.h"
#include "QueryProcessor.h"
#include "catch2/catch.hpp"
#include "AvlTree.h"
#include <fstream>

TEST_CASE("Stop words are present", "[stopwords]") {
    DocumentParser::loadStopWords("../StopWords/stopWords.txt");
    std::string text1 = "This";
    REQUIRE(DocumentParser::containsStopWords(text1) == true);
    std::string text2 = "Able";
    REQUIRE(DocumentParser::containsStopWords(text2) == true);
}
TEST_CASE("Words stemmed correctly", "[stemming]") {
    std::string word = "running";
    std::string stemmedWord = DocumentParser::stemWord(word);
    REQUIRE(stemmedWord == "run");
}

TEST_CASE("Test DocumentParser integration with AVL Tree") {
    // Initialize AVL trees
    AvlTree<std::string> personTree;
    AvlTree<std::string> organizationTree;
    AvlTree<std::string> wordTree;

    // Initialize DocumentParser
    DocumentParser documentParser(personTree, organizationTree, wordTree);

    documentParser.runDocument("/home/aaronvsc/projects/assignment-4-search-engine-let-us-cook/sample_data/coll_1/news_0064567.json");

    SECTION("Test AVL Tree Population") {

        // Test AVL tree population for words
        // wordTree.prettyPrintTree();
        //personTree.prettyPrintTree();
        //organizationTree.prettyPrintTree();

    }
}

// TEST_CASE("Test SeperateStirng function") {
//     std::string search = "sample search string";
//     auto result = SeperateString(search);

//     SECTION("Check if the result is correct") {
//         // Add your assertions here to validate the result
//         REQUIRE(result.size() == 4);
//         REQUIRE(result["Facebook"] == std::vector<std::string>{"document1", "document2"});
//         REQUIRE(result["John"] == std::vector<std::string>{"document3", "document4"});
//         REQUIRE(result["profit"] == std::vector<std::string>{"document7", "document8"});
//         REQUIRE(result["apple"] == std::vector<std::string>{"document5", "document6"});
//     }
// }

TEST_CASE("Process query", "[processQuery]") {
    // Create AvlTree instances (you need to define them according to your implementation)
    AvlTree<std::string> personTree, orgTree, wordTree;

    DocumentParser documentParser(personTree, orgTree, wordTree);

    // Specify the folder path
    std::string folderPath = "/home/aaronvsc/projects/assignment-4-search-engine-let-us-cook/sample_data/coll_1";

    // Iterate over all files in the specified folder
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            documentParser.runDocument(entry.path().string());
        }
    }


    // Create QueryProcessor instance
    QueryProcessor queryProcessor(personTree, orgTree, wordTree);

    // Process query
    std::map<std::string, int> result = queryProcessor.processQuery("Pessimistic PERSON:lang");

    queryProcessor.outputTopDocuments(result);


}






