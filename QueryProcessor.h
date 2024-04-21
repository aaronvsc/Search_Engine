#include "AvlTree.h"
#include "DocumentParser.h"
#include <map>


// SeperateString()
// findWord()
// findPerson()
// find Person()

std::map<std::string, std::vector<std::string>> documents;
std::string tempWord = "";

std::map<std::string, std::vector<std::string>> SeperateStirng(std::string search) {
    std::vector<std::string> wordsToSearch = tokenizer(search);
    for (int i = 0; i < wordsToSearch.size(); i++){
        if (wordsToSearch[i].substr(0, 4) == "ORG:") {
            tempWord = wordsToSearch[i].substr(4);
            documents.insert({tempWord, findOrganization(tempWord)});
        }
        else if(wordsToSearch[i].substr(0,7) == "PERSON:") {
            tempWord = wordsToSearch[i].substr(7);
            documents.insert({tempWord, findPerson(tempWord)});
        }
        else if (wordsToSearch[i].substr(0,1) == "-") {
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
}

std::vector<std::string> findPerson(std::string personToFind) {
// search through the AVL tree to find the person and put all the documents related to the person into a vector
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
