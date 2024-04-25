
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

   public:
    QueryProcessor(AvlTree<std::string>& person, AvlTree<std::string>& org, AvlTree<std::string>& word) : PersonTree(person), OrganizationTree(org), WordsTree(word) {}

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

    void outputTopDocuments(const std::map<std::string, int>& documentFrequencyMap) {
        // Create a vector of pairs to hold the documents and their frequencies
        std::vector<std::pair<std::string, int>> documentFrequencyPairs;

        // Copy the content of the map to the vector of pairs
        for (const auto& pair : documentFrequencyMap) {
            documentFrequencyPairs.push_back(pair);
        }

        // Sort the vector of pairs based on the frequency counts in descending order
        std::sort(documentFrequencyPairs.begin(), documentFrequencyPairs.end(),
                  [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                      return a.second > b.second;  // Sort in descending order of frequency counts
                  });

        // Output the first 15 documents along with their frequency counts
        int count = 0;
        for (const auto& pair : documentFrequencyPairs) {
            if (count >= 15) {
                break;  // Exit the loop after outputting the first 15 documents
            }
            // NOTE instead of DOCUMENT ID AND FREQUENCY. WE NEED A FUNCTION TO RETRIEVE ARTICLE NAME, PUBLICATION, and DATE
            std::cout << count + 1 << ". ";
            DocumentParser::printDocument(pair.first);
            std::cout << std::endl;
            ++count;
        }
    }

    void SeperateString(std::string search) {
        std::string tempWord = "";
        std::vector<std::string> wordsToSearch = DocumentParser::tokenizer(search);

        for (int i = 0; i < wordsToSearch.size(); i++) {
            wordsToSearch[i] = removePunctuationExcept(wordsToSearch[i]);
        }

        // for (const std::string& word : wordsToSearch) {
        //     std::cout << word << std::endl;
        // }

        for (int i = 0; i < wordsToSearch.size(); i++) {
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
        for (int i = 0; i < word.length(); ++i) {
            if (ispunct(word.at(i)) && word.at(i) != ':' && word.at(i) != '-') {
                word.erase(i, 1);
                --i;
            }
        }
        return word;
    }
};
#endif
