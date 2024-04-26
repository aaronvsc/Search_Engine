#include <chrono>
#include <iostream>

#include "AvlTree.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"

// static void startUI() {
//     char userChoice;
//     std::string input;
//     while (true) {
//         std::cout << "\nSuperSearch Menu\n";
//         std::cout << "Press i to index a directory.\n";
//         std::cout << "Press s to save the index.\n";
//         std::cout << "Press l to load the index.\n";
//         std::cout << "Press q to perform query.\n";
//         std::cout << "Press e to exit.\n";
//         std::cout << "Enter the choice: ";
//         std::cin >> userChoice;

//         switch (userChoice) {
//             case 'i':
//             case 's':
//             case 'l':
//             case 'q':
//             case 'e':
//                 break; // Added break statement
//         }
//     }
// }

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
        documentParser.toFile("Trees/person_tree.txt","Trees/organization_tree.txt","Trees/words_tree.txt");

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Index took " << duration.count() << " seconds" << std::endl;

    } else if (command == "query") {
        std::string query = argv[2];
        auto start = std::chrono::high_resolution_clock::now();
        queryProcessor.getTreesfromFile("Trees/person_tree.txt","Trees/organization_tree.txt","Trees/words_tree.txt");
        std::map<std::string, int> result = queryProcessor.processQuery(query);
        queryProcessor.outputTopDocuments(result);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Query took " << duration.count() << " seconds" << std::endl;
    } else if (command == "ui" && argc == 2) {
        // startUI();
    } else {
        std::cerr << "Invalid usage. Correct usage:\n"
                  << argv[0] << " index <directory>\n"
                  << argv[0] << " query <query-string>\n"
                  << argv[0] << " ui\n";
        exit(1);
    }
    return 0;
}