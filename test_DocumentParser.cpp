#define CATCH_CONFIG_MAIN
#include "DocumentParser.h"
#include "catch2/catch.hpp"

TEST_CASE("Stop words are present", "[stopwords]") {
    DocumentParser::loadStopWords("../StopWords/stopWords.txt");
    std::string text = "This is the test of the stop word removal.";
    REQUIRE(DocumentParser::containsStopWords(text) == true);
}
TEST_CASE("Words stemmed correctly", "[stemming]") {
    std::string word = "running";
    std::string stemmedWord = DocumentParser::stemWord(word);
    std::cout << stemmedWord << std::endl;
    REQUIRE(stemmedWord == "run");
}

