#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H
#include <map>
#include <cmath>

#include "AvlTree.h"
#include "DocumentParser.h"

// SeperateString()
// findWord()
// findPerson()
// find Person()
class QueryProcessor {
    private :
    AvlTree<std::string>& PersonTree;
    AvlTree<std::string> &OrganizationTree;
    AvlTree<std::string>& WordsTree;
   public:

   QueryProcessor(AvlTree<std::string> &person, AvlTree<std::string> &org, AvlTree<std::string> &word):PersonTree(person),OrganizationTree(org),WordsTree(word){
        // PersonTree = person;
        // OrganizationTree = org;
        // WordsTree = word;
   }

    std::map<std::string, std::vector<std::string>> documents;
    std::string tempWord = "";

    std::map<std::string, std::vector<std::string>> SeperateStirng(std::string search) {
        std::vector<std::string> wordsToSearch = tokenizer(search);
        for (int i = 0; i < wordsToSearch.size(); i++) {
            if (wordsToSearch[i].substr(0, 4) == "ORG:") {
                tempWord = wordsToSearch[i].substr(4);
                documents.insert({tempWord, findOrganization(tempWord)});
            } else if (wordsToSearch[i].substr(0, 7) == "PERSON:") {
                tempWord = wordsToSearch[i].substr(7);
                documents.insert({tempWord, findPerson(tempWord)});
            } else if (wordsToSearch[i].substr(0, 1) == "-") {
                tempWord = wordsToSearch[i].substr(1);
                documents.insert({tempWord, notFind(tempWord)});
            } else {
                documents.insert({wordsToSearch[i], findWord(wordsToSearch[i])});
            }
        }
        return documents;
    }

    std::vector<std::string> findWord(std::string wordToFind) {
        // search through the AVL tree to find the word and put all the documents related to the word into a vector
        std::vector<std::string> documents;
        AvlNode* node = findNode(wordToFind, root);
        if (node != nullptr) {
            for (const auto& entry : node->wordMap) {
                documents.push_back(entry.first);
            }
        }
        return documents;
    }

    std::vector<std::string> findPerson(std::string personToFind) {
        // search through the AVL tree to find the person and put all the documents related to the person into a vector
        std::vector<std::string> personDocs;
        personDocs.push_back(PersonTree.findNode(personToFind))

    }

    std::vector<std::string> findOrganization(std::string orgToFind) {
        // search through the AVL tree to find the organization and put all the documents related to the organization into a vector
    }

    std::vector<std::string> notFind(std::string wordToNotFind) {
        // find the total number of documents
        // search through the AVL tree to find the word and put all the documents related to the organization into a vector
        // compare the two lists and return a vector of the documents that are not in both lists
    }

    std::vector<std::string> rankRelevancy(std::vector<std::string> docsToRank) {
        // givens a vector of documents, find rank to relevancy of the documents
    }

    std::map<std::string, int> calculateTermFrequency(std::string document) {
        std::vector<std::string> words = tokenizer(document);
        std::map<std::string, int> freq;
        for (const auto& word : words) {
            freq[word]++;
        }
        return freq;
    }
    std::map<std::string, double> calculateIDF(std::vector<std::string> documents) {
        std::map<std::string, int> docCount;
        for (const auto& doc : documents) {
            std::vector<std::string> words = tokenizer(doc);
            std::set<std::string> seen;
            for (const auto& word : words) {
                if (seen.insert(word).second) {
                    docCount[word]++;
                }
            }
        }
        int totalDocs = documents.size();
        std::map<std::string, double> idf;
        for (const auto& [word, count] : docCount) {
            idf[word] = log(static_cast<double>(totalDocs) / count);
        }
        return idf;
    }
    std::map<std::string, double> calculateTFIDF(const std::string& document, const std::map<std::string, double>& idf) {
        std::map<std::string, int> tf = calculateTermFrequency(document);
        std::map<std::string, double> tfidf;
        for (const auto& [word, freq] : tf) {
            if (idf.find(word) != idf.end()) {
                tfidf[word] = freq * idf.at(word);
            }
        }
        return tfidf;
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
}

#endif
