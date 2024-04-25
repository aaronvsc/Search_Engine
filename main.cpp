#include <iostream>
#include "AvlTree.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"
using namespace std;

int main(int argc, char* argv[])
{

    AvlTree<std::string> PersonTree;
    AvlTree<std::string> OrganizationTree;
    AvlTree<std::string> WordsTree;
    DocumentParser documentparser(PersonTree,OrganizationTree,WordsTree);
    documentparser.runDocument();

    QueryProcessor q(PersonTree,OrganizationTree,WordsTree);
    q.query("Search term")
    cout << "Usage:\n"
         << "\tIndex all files in <directory> and store the index in one or several files:\n"
         << "\tsupersearch index <directory>\n\n"
         << "\tLoad the existing index and perform the following query:\n"
         << "\tsupersearch query \"social network PERSON:cramer\"\n\n"
         << "\tStart a simple text-based user interface that lets the user create an index,\n\tsave/load the index and perform multiple queries:\n"
         << "\tsupersearch ui\n\n";

    cout << "supersearch not implemented yet." << endl; 

    std::string command = argv[1];
    if (command == "index" && argc == 3) {
        std::string directory = argv[2];
        indexFiles(directory);
    }
    else if (command == "query" && argc == 3) {
        std::string query = argv[2];
        processQuery(query);
    } 
    else if (command == "ui" && argc == 2) {
        startUI();
    } else {
        std::cerr << "Invalid usage. Correct usage:\n" 
        << argv[0] << " index <directory>\n" << argv[0] << 
        " query <query-string>\n" << argv[0] << " ui\n";
        exit(1);
    }
    char userChoice;
    std::string input;

    while(true) {
        std::cout<< "\nSuperSearch Menu\n";
        std::cout<< "Press i to index a directory.\n";
        std::cout<< "Press s to save the index.\n";
        std::cout<< "Press l to load the index.\n";
        std::cout<< "Press q to perform query.\n";
        std::cout<< "Press e to exit.\n";
        std::cout<< "Enter the choice: ";
        std::cin >> userChoice;

        switch(userChoice) {
            case 'i':
            
            case 's':

            case 'l':

            case 'q':

            case 'e':

            default: 

        }





        

    }



    return 0;
}