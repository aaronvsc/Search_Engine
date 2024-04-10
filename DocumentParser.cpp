#include "Porter2/porter2Stemmer.cpp"
#include <iostream>
#include <set>
#include <fstream>

class DocumentParser {
public: 
    static std::string stemWord(const std::string& word) {
        std::string stemmedWord = word;
        Porter2Stemmer::stem(stemmedWord);
        return stemmedWord;
    }
    std::set<std::string> loadStopWords(const std::string& filePath) {
        std::set<std::string> stopWords;
        std::ifstream file(filePath);
        std::string word;

        if(!file.is_open()) {
            std::cerr << "Unable to open file: " << filePath << std::endl;
            return stopWords;
        }
        while (file >> word) {
            stopWords.insert(word);
        }

        file.close();
        return stopWords;
    }
    static bool removeStopWords(const std::string& text) {
        std::vector<std::string> tokens = 
    }

};
