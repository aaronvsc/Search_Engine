#define CATCH_CONFIG_MAIN
#include "DocumentParser.cpp"
#include "catch2/catch.hpp"

TEST_CASE("Stop words are removed", "[stopwords]") {
    DocumentParser parser;
    std::string text = "This is the test of the stop word removal";
    //std::string processedText = parser.removeStopWords(text);
    //REQUIRE(processedTest == "This test stop word removal");
}
TEST_CASE("Words stemmed correctly", "[stemming]") {
    std::string word = "running";
    std::string stemmedWord = DocumentParser::stemWord(word);
    REQUIRE(stemmedWord == "run");
}

