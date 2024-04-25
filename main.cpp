
#include <iostream>
#include "AvlTree.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"
using namespace std;

int main(int argc, char* argv[])
{
    /*

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
    return 0;
}