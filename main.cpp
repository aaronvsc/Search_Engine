#include <chrono>
#include <iostream>
#include "AvlTree.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"

static void startUI() {
    AvlTree<std::string> PersonTree;
    AvlTree<std::string> OrganizationTree;
    AvlTree<std::string> WordsTree;

    DocumentParser documentParser(PersonTree, OrganizationTree, WordsTree);
    QueryProcessor queryProcessor(PersonTree, OrganizationTree, WordsTree);

    char userChoice;
    std::string input;
    while (true) {
        std::cout << "\nSuperSearch Menu\n";
        std::cout << "Press i to index a directory.\n";
        std::cout << "Press q to perform a query.\n";
        std::cout << "Press e to exit.\n";
        std::cout << "Enter the choice: ";
        std::cin >> userChoice;

        switch (userChoice) {
            case 'i':
                std::cout << "Enter the path to directory to index: ";
                std::cin >> input;
                auto start = std::chrono::high_resolution_clock::now();
                // Iterate over all files in the specified folder
                for (const auto& entry : std::filesystem::directory_iterator(input)) {
                    if (entry.is_regular_file()) {
                        std::string filename = entry.path().filename().string();
                        documentParser.runDocument(entry.path().string());
                    }
                }
                documentParser.toFile("Trees/person_tree.txt", "Trees/organization_tree.txt", "Trees/words_tree.txt");
                std::cout << "Indexing completed.\n";
                break;
            case 'q':
                std::cout << "Enter the search query: ";
                std::cin.ignore();  // Clear the input buffer
                std::getline(std::cin, input);
                auto startQuery = std::chrono::high_resolution_clock::now();
                queryProcessor.getTreesfromFile("Trees/person_tree.txt", "Trees/organization_tree.txt", "Trees/words_tree.txt");
                queryProcessor.runQueryProcessor(input);
                std::cout << "\nOptions for query results:\n";
                std::cout << "Press n to print 5 more documents.\n";
                std::cout << "Press q to start a new query.\n";
                std::cout << "Press d and enter document number to print document text.\n";
                std::cout << "Press e to return to main menu.\n";
                std::cout << "Enter choice: ";
                std::cin >> userChoice;
                switch (userChoice) {
                    case 'm':
                        queryProcessor.outputDocuments(5);
                        break;
                    case 'n':
                        break; // Continue to outer loop and start a new query
                    case 'd':
                        std::cout << "Enter the document number to print: ";
                        std::cin >> input;
                        //convert input to integer
                        std::string name = queryProcessor.getDocumentName(input);
                        documentParser.printDocumentText(name);
                        break;
                    case 'e':
                        continue; // Continue to outer loop to display main menu
                    default:
                        std::cout << "Invalid choice. Returning to main menu.\n";
                        continue; // Continue to outer loop to display main menu
                }
                auto endQuery = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> queryDuration = endQuery - startQuery;
                std::cout << "Query took " << queryDuration.count() << " seconds" << std::endl;
                break;
            case 'e':
                std::cout << "Exiting program.\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
int main(int argc, char* argv[]) {
    AvlTree<std::string> PersonTree;
    AvlTree<std::string> OrganizationTree;
    AvlTree<std::string> WordsTree;
    DocumentParser documentParser(PersonTree, OrganizationTree, WordsTree);
    QueryProcessor queryProcessor(PersonTree, OrganizationTree, WordsTree);
    if (argc < 2) {
        std::cerr << "Invalid usage. Correct usage:\n"
                  << argv[0] << " index <directory>\n"
                  << argv[0] << " query <query-string>\n"
                  << argv[0] << " ui\n";
        exit(1);
    }
    std::string command = argv[1];
    if (command == "index") {
        std::string directory = argv[2];
        auto start = std::chrono::high_resolution_clock::now();
        // Iterate over all files in the specified folder
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                documentParser.runDocument(entry.path().string());
            }
        }
        documentParser.toFile("Trees/person_tree.txt", "Trees/organization_tree.txt", "Trees/words_tree.txt");
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Index took " << duration.count() << " seconds" << std::endl;
    } else if (command == "query") {
        std::string query = argv[2];
        auto start = std::chrono::high_resolution_clock::now();
        queryProcessor.getTreesfromFile("Trees/person_tree.txt", "Trees/organization_tree.txt", "Trees/words_tree.txt");
        queryProcessor.runQueryProcessor(query);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Query took " << duration.count() << " seconds" << std::endl;
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