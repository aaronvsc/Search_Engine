#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H
#include <cmath>
#include <map>
#include "AvlTree.h"
#include "DocumentParser.h"

class QueryProcessor {
   private:

    AvlTree<std::string>& PersonTree;
    AvlTree<std::string>& OrganizationTree;
    AvlTree<std::string>& WordsTree;
    // vector of maps to compare
    std::vector<std::map<std::string, int>> vectorOfMaps;
    std::vector<std::map<std::string, int>> vectorOfBadMaps;
    // Create a vector of pairs to hold the documents and their frequencies
    std::vector<std::pair<std::string, int>> documentFrequencyPairs;
    size_t searchIndex = 0;

   public:

    QueryProcessor(AvlTree<std::string>& person, AvlTree<std::string>& org, AvlTree<std::string>& word) : PersonTree(person), OrganizationTree(org), WordsTree(word){    }

    //Function to run entire query outputting the first 15 docs
    void runQueryProcessor(const std::string& search) {
        documentFrequencyPairs.clear();
        vectorOfMaps.clear();
        vectorOfBadMaps.clear();
        searchIndex = 0;
        // Process the query
        std::map<std::string, int> result = processQuery(search);
        // Sort documents by frequency
        sortDocumentsByFrequency(result);
        // Output the top documents
        outputDocuments(15); // Change the number as needed
    }

    // Function to prcoess query, returns final map of desired search results
    std::map<std::string, int> processQuery(std::string search) {
        SeperateString(search);
        if (vectorOfMaps.empty()) {
            return {};  // Return an empty map if there are no input maps
        }
        std::map<std::string, int> result = vectorOfMaps[0];  // Start with the first map
        // Find the intersection of all maps
        for (size_t i = 1; i < vectorOfMaps.size(); ++i) {
            result = intersectMaps(result, vectorOfMaps[i]);
        }
        // Exclude documents specified in badMaps
        for (const auto& badMap : vectorOfBadMaps) {
            result = excludeMaps(result, badMap);
        }
        return result;
    }
    void sortDocumentsByFrequency(const std::map<std::string, int>& documentFrequencyMap) {
        // Copy the content of the map to the vector of pairs
        for (const auto& pair : documentFrequencyMap) {
            documentFrequencyPairs.push_back(pair);
        }
        // Sort the vector of pairs based on the frequency counts in descending order
        std::sort(documentFrequencyPairs.begin(), documentFrequencyPairs.end(),
                  [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                      return a.second > b.second;  // Sort in descending order of frequency counts
                  });
    }

    void outputDocuments(int numDocuments) {
        int count = 0;
        size_t startIndex = searchIndex;
        if (startIndex >= documentFrequencyPairs.size()) {
            std::cout << "No documents match the search criteria." << std::endl;
            return;
        }

        while (startIndex < documentFrequencyPairs.size() && count < numDocuments) {
            const auto& pair = documentFrequencyPairs[startIndex];
            std::cout << count + 1 << ". ";
            DocumentParser::printDocument(pair.first);
            std::cout << std::endl;
            ++count;
            ++startIndex;
        }
        searchIndex = startIndex;
    }

    void SeperateString(std::string search) {
        std::string tempWord = "";
        std::vector<std::string> wordsToSearch = DocumentParser::tokenizer(search);
        for (std::string::size_type i = 0; i < wordsToSearch.size(); i++) {
            wordsToSearch[i] = removePunctuationExcept(wordsToSearch[i]);
        }
        for (std::string::size_type i = 0; i < wordsToSearch.size(); i++) {
            if (wordsToSearch[i].substr(0, 4) == "ORG:") {
                tempWord = wordsToSearch[i].substr(4);
                vectorOfMaps.push_back(OrganizationTree.getWordMapAtKey(tempWord));
            } else if (wordsToSearch[i].substr(0, 7) == "PERSON:") {
                tempWord = wordsToSearch[i].substr(7);
                vectorOfMaps.push_back(PersonTree.getWordMapAtKey(tempWord));
            } else if (wordsToSearch[i].substr(0, 1) == "-") {
                tempWord = DocumentParser::stemWord(wordsToSearch[i].substr(1));
                vectorOfBadMaps.push_back(WordsTree.getWordMapAtKey(tempWord));
            } else if (!DocumentParser::containsStopWords(wordsToSearch[i]) && wordsToSearch[i] != "") {
                vectorOfMaps.push_back(WordsTree.getWordMapAtKey(DocumentParser::stemWord(wordsToSearch[i])));
            } else {
                continue;
            }
        }
    }
    std::map<std::string, int> intersectMaps(std::map<std::string, int>& map1, std::map<std::string, int>& map2) {
        std::map<std::string, int> intersectMap;
        for (auto it = map1.begin(); it != map1.end(); ++it) {
            auto findIter = map2.find(it->first);
            if (findIter != map2.end()) {
                // Key exists in both maps, add the frequencies together
                intersectMap[it->first] = it->second + findIter->second;
                map2.erase(findIter);  // Remove the key from map2
            }
        }
        return intersectMap;
    }
    std::map<std::string, int> excludeMaps(const std::map<std::string, int>& map, const std::map<std::string, int>& badMap) {
        std::map<std::string, int> excludeMap;
        for (const auto& pair : map) {
            if (badMap.find(pair.first) == badMap.end()) {
                // Document ID not found in badMap, include it in the result
                excludeMap.insert(pair);
            }
        }
        return excludeMap;
    }

    static std::string removePunctuationExcept(std::string word) {
        for (std::string::size_type i = 0; i < word.length(); ++i) {
            if (ispunct(word.at(i)) && word.at(i) != ':' && word.at(i) != '-') {
                word.erase(i, 1);
                --i;
            }
        }
        return word;
    }
    // Function to write trees into corresponding files
    void getTreesfromFile(const std::string& personFile, const std::string& orgFile, const std::string& wordFile) {
        // Serialize PersonTree to personFile
        PersonTree.readFromTextFile(personFile);
        // Serialize and write OrganizationTree
        OrganizationTree.readFromTextFile(orgFile);
        // Serialize and write WordsTree
        WordsTree.readFromTextFile(wordFile);
    }
    std::string getDocumentName(int index) {
    if (index >= documentFrequencyPairs.size()) {
        return ""; // Return an empty string if the index is out of range
    }
    return documentFrequencyPairs[index].first; // Return the document name at the specified index
}
};

#endif