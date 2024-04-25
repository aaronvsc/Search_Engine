#include <iostream>
#include "AvlTree.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"
using namespace std;

static void startIU() {
    char userChoice;
    std::string input;
    while (true) {
        std::cout << "\nSuperSearch Menu\n";
        std::cout << "Press i to index a directory.\n";
        std::cout << "Press s to save the index.\n";
        std::cout << "Press l to load the index.\n";
        std::cout << "Press q to perform query.\n";
        std::cout << "Press e to exit.\n";
        std::cout << "Enter the choice: ";
        std::cin >> userChoice;

        switch (userChoice) {
            case 'i':
            case 's':

            case 'l':

            case 'q':

            case 'e':

            default:
        }
    }
}

int main(int argc, char* argv[]) {
    AvlTree<std::string> PersonTree;
    AvlTree<std::string> OrganizationTree;
    AvlTree<std::string> WordsTree;


    DocumentParser documentParser(PersonTree, OrganizationTree, WordsTree);

    QueryProcessor queryProcessor(PersonTree, OrganizationTree, WordsTree);
    
    std::string command = argv[1];
    if (command == "index" && argc == 3) {
        std::string directory = argv[2];
        documentParser.runDocument(directory);
    } else if (command == "query" && argc == 3) {
        std::string query = argv[2];
        std::map<std::string, int> result = queryProcessor.processQuery(query);
        queryProcessor.outputTopDocuments(result);


    } else if (command == "ui" && argc == 2) {
        startUI();
    } else {
        std::cerr << "Invalid usage. Correct usage:\n"
                  << argv[0] << " index <directory>\n"
                  << argv[0] << " query <query-string>\n"
                  << argv[0] << " ui\n";
        exit(1);
    }
    return 0;
}