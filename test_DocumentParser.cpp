#define CATCH_CONFIG_MAIN
#include "DocumentParser.h"
#include "catch2/catch.hpp"

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
    std::cout << stemmedWord << std::endl;
    REQUIRE(stemmedWord == "run");
}

