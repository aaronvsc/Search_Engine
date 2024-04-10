#include "porter2Stemmer.h"
#include <iostream>
#include <unordered_set>
#include <fstream>

class DocumentParser {
public: 
    static std::string stemWord(const std::string& word) {
        std::string stemmedWord = word;
        Porter2Stemmer::stem(stemmedWord);
        return stemmedWord;
    }
    std::unordered_set<std::string> loadStopWords(const std::string& filePath) {
        std::unordered_set<std::string> stopWords;
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
};
