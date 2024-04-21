#ifndef DOCUMENT_PARSER_H
#define DOCUMENT_PARSER_H
#include "Porter2/porter2Stemmer.cpp"
#include "AvlTree.h"
#include <iostream>
#include <set>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
#include <filesystem>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
using namespace rapidjson;

class DocumentParser {
private:
    AvlTree<std::string> PersonTree;
    AvlTree<std::string> OrganizationTree;
    AvlTree<std::string> WordsTree;

public: 
    static std::set<std::string> stopWords;

    static std::string stemWord(const std::string& word) {
        std::string stemmedWord = word;
        Porter2Stemmer::stem(stemmedWord);
        return stemmedWord;
    }
    static void loadStopWords(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string word;

        if(!file.is_open()) {
            std::cerr << "Unable to open file: " << filePath << std::endl;
        }
        while (file >> word) {
            stopWords.insert(word);
        }

        file.close();
    }

    static std::string toLower(const std::string& text) {
        std::string result;
        result.reserve(text.size());
        for (char ch : text) {
            result += std::tolower(ch);
        }
        return result;
    }
    static bool containsStopWords(const std::string& word) {
        std::string lowerToken = toLower(word);
        if (stopWords.find(lowerToken) != stopWords.end()) {
            return true;
        }
        return false;
    }

    static std::vector<std::string> tokenizer(const std::string textLine) {
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

    static std::string removePunctuation(std::string word) {
        for (int i = 0; i < word.length(); i++) {
            if (ispunct(word.at(i))) {
                word = word.erase(i,1);
                i--;
            }
        }
        return word;
    }

    void runDocument(std::string documentName) {
        //remember to do persons and organizations later

        std::ifstream input(documentName);
        if (!input.is_open())
        {
            std::cerr << "cannot open file: " << documentName << std::endl;
            return;
        }

        IStreamWrapper isw(input);
        Document d;
        d.ParseStream(isw);

        std::string docText = d["text"].GetString();
        std::cout << docText << std::endl;

        std::vector<std::string> tokens = tokenizer(docText);
        std::map<std::string, double> frequencies;

        for (int i = 0; i < tokens.size(); i++) {
            tokens[i] = removePunctuation(tokens[i]);
            tokens[i] = toLower(tokens[i]);
            tokens[i] = stemWord(tokens[i]);
            if (!containsStopWords(tokens[i])) {
                frequencies[tokens[i]]++;
            }
        }

        for (int i = 0; i < tokens.size(); i++) {
            if (!containsStopWords(tokens[i])) {
                pushToTreeWord(tokens[i], documentName, relevancy(tokens[i], tokens));
            }
        }


        // Person
        auto docPersons = d["persons"].GetArray();
        for(const auto& person: docPersons){
            std::string pers = person["name"].GetString();
            std::vector<std::string> names = tokenizer(pers);
            for (int i = 0; i < names.size(); i++) {
                pushToTreePerson(names[i], documentName, 1);
            }
        }

        // Org
        auto docOrgs = d["organizations"].GetArray();
        for (const auto& organization: docOrgs) {
            std::string orgs = organization["organizations"].GetString();
            std::vector<std::string> orgWords = tokenizer(orgs);
            for (int i = 0; i < orgWords.size(); i++) {
                pushToTreeOrg(orgWords[i], documentName, 1);
            }
        }

        input.close();
    }


    // person AVL Tree
    void pushToTreePerson(std::string token, std::string docName, double frequency) {
        PersonTree.insert(token, docName, frequency);
        //insert(token, docName, frequency)

    }
    // organization AVL Tree
    void pushToTreeOrg(std::string token, std::string docName, double frequency) {
        OrganizationTree.insert(token, docName, frequency);
        //insert(token, docName, frequency)

    }
    // word AVL Tree
    void pushToTreeWord(std::string token, std::string docName, double frequency) {
        WordsTree.insert(token, docName, frequency);
        //insert(token, docName, frequency)

    }

    double relevancy(std::string word, std::vector<std::string> tokens) {
        int counter, appearanceNum = 0;
        for (int i = 0; i < tokens.size(); i++) {
            if (word == tokens.at(i)) {
                appearanceNum++;
            }
            counter++;
        }
        double appearancePercent = static_cast<double>(appearanceNum) / static_cast<double>(counter);
        return appearancePercent;
    }

};
std::set<std::string> DocumentParser::stopWords;
#endif