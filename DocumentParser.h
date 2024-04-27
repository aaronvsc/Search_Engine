#ifndef DOCUMENT_PARSER_H
#define DOCUMENT_PARSER_H
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "AvlTree.h"
#include "Porter2/porter2Stemmer.cpp"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
using namespace rapidjson;

class DocumentParser {
   private:
    AvlTree<std::string>& PersonTree;
    AvlTree<std::string>& OrganizationTree;
    AvlTree<std::string>& WordsTree;
    int filesIndexed = 0;

   public:
    DocumentParser(AvlTree<std::string>& person, AvlTree<std::string>& org, AvlTree<std::string>& word) : PersonTree(person), OrganizationTree(org), WordsTree(word) {}
    static std::set<std::string> stopWords;

    static std::string stemWord(const std::string& word) {
        std::string stemmedWord = word;
        Porter2Stemmer::trim(stemmedWord);
        Porter2Stemmer::stem(stemmedWord);
        return stemmedWord;
    }
    static void loadStopWords(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string word;

        if (!file.is_open()) {
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
        for (std::string::size_type i = 0; i < textLine.length(); i++) {
            if (textLine.at(i) == ' ') {
                word = textLine.substr(startingLetter, i - startingLetter);
                startingLetter = i + 1;
                tokens.push_back(word);
            }
        }

        word = textLine.substr(startingLetter);
        tokens.push_back(word);

        return tokens;
    }

    static std::string removePunctuation(std::string word) {
        for (std::string::size_type i = 0; i < word.length(); i++) {
            if (ispunct(word.at(i)) || !isalpha(word.at(i))) {
                word = word.erase(i, 1);
                i--;
            }
        }
        return word;
    }

    void runDocument(std::string documentName) {
        filesIndexed++;
        std::ifstream input(documentName);
        if (!input.is_open()) {
            std::cerr << "cannot open file: " << documentName << std::endl;
            return;
        }

        if (stopWords.size() == 0) {
            loadStopWords("stopWords.txt");
        }

        IStreamWrapper isw(input);
        Document d;
        d.ParseStream(isw);

        std::string docText = d["text"].GetString();

        std::vector<std::string> tokens = tokenizer(docText);

        for (std::string::size_type i = 0; i < tokens.size(); i++) {
            tokens[i] = removePunctuation(tokens[i]);
            tokens[i] = toLower(tokens[i]);
            tokens[i] = stemWord(tokens[i]);
        }

        for (std::string::size_type i = 0; i < tokens.size(); i++) {
            if (!containsStopWords(tokens[i]) && tokens[i] != "") {
                pushToTreeWord(tokens[i], documentName, 1);
            }
        }

        // Person
        auto docPersons = d["entities"]["persons"].GetArray();
        for (const auto& person : docPersons) {
            std::string pers = person["name"].GetString();
            std::vector<std::string> names = tokenizer(pers);
            for (const auto& name : names) {
                pushToTreePerson(name, documentName, 1);
            }
        }

        // Org
        auto docOrgs = d["entities"]["organizations"].GetArray();
        for (const auto& organization : docOrgs) {
            std::string orgName = organization["name"].GetString();
            pushToTreeOrg(orgName, documentName, 1);
        }
        
        input.close();
    }

    // person AVL Tree
    void pushToTreePerson(std::string token, std::string docName, double frequency) {
        PersonTree.insert(token, docName, frequency);
    }
    // organization AVL Tree
    void pushToTreeOrg(std::string token, std::string docName, double frequency) {
        OrganizationTree.insert(token, docName, frequency);
    }
    // word AVL Tree
    void pushToTreeWord(std::string token, std::string docName, double frequency) {
        WordsTree.insert(token, docName, frequency);
    }

    static void printDocument(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file: " << filename << std::endl;
            return;
        }

        IStreamWrapper isw(file);
        Document doc;
        doc.ParseStream(isw);

        // Extract article title and publication date from the parsed JSON
        std::string articleName = doc["title"].GetString();
        std::string publicationDate = doc["published"].GetString();

        // Output the article name and publication date
        std::cout << "Article Name: " << articleName;
        std::cout << " Publication Date: " << publicationDate << std::endl;

        file.close();
    }

    void printDocumentText(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return;
        }
        IStreamWrapper isw(file);
        Document document;
        document.ParseStream(isw);

        if (!document.HasMember("text") || !document["text"].IsString()) {
            std::cerr << "Text not found in JSON file: " << filename << std::endl;
            return;
        }

        std::cout << document["text"].GetString() << std::endl;

        file.close();
    }

    // Function to write trees into corresponding files
    void toFile(const std::string& personFile, const std::string& orgFile, const std::string& wordFile) {
        // Serialize PersonTree to personFile
        PersonTree.writeToTextFile(personFile);

        // Serialize and write OrganizationTree
        OrganizationTree.writeToTextFile(orgFile);

        // Serialize and write WordsTree
        WordsTree.writeToTextFile(wordFile);
    }

    int getFilesIndexed() {
        return filesIndexed;
    }
};
std::set<std::string> DocumentParser::stopWords;
#endif