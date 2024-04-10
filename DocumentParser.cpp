#include "Porter2/porter2Stemmer.cpp"
#include <iostream>
#include <set>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

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
    std::string toLower(const std::string& text) {
        std::string result;
        result.reserve(text.size());
        for (char ch : text) {
            result += std::tolower(ch);
        }
        return result;
    }
    bool removeStopWords(const std::string& text) {
        std::set<std::string> stopWords;
        std::vector<std::string> tokens = tokenizer(text);
        for (std::string& token : tokens) {
            std::string lowerToken = toLower(token);
            if (stopWords.find(lowerToken) != stopWords.end()) {
                return true;
            }
        }
        return false;
    }
    std::vector<std::string> tokenizer(const std::string textLine) {
        std::string word = "";
        std::vector<std::string> tokens;
        int startingLetter = 0;
        for (int i = 0; i < textLine.length(); i++) {
            if (textLine.at(i) == ' ') {
                word = textLine.substr(startingLetter, i);
                startingLetter = i + 1;
                tokens.push_back(word);
            }
        }
        return tokens;
    }

    static std::string removePunctuation(std::string) {
        
    }
};
