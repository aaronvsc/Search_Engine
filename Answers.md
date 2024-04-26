# Assignment 4: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Names of all team members: Aaron Santa Cruz, Spencer Neill, Hunter Ryan




Used free extension: [ ] 24 hrs or [ ] 48 hrs

[x] Early submission (48 hrs)

[x] Bonus work. Describe: We implemented a smart relevancy ranking.

Place [x] for what applies.


## Answers

### Project Management

Complete the tasks and planned completion columns **BEFORE** You start with 
coding!


Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Task        | Planned completion | Actual completion | Time spent in hrs by X | Time spent in hrs by Y |
| ----------- | :-----------------:| :---------------: | :--------------------: | :--------------------: |
| x           | Nov 3              | Nov 6             | 8.5                    | 0                      |
| Finish AVL tree           | April 15               | April 15             | 6                     | 6                      |
| Finish Document Parser    | April 22               | April 21             | 8                     | 8                      |
| Finish Query Processor    | April 24               | April 25             | 4                     | 8                      |
| Finish Project            | April 27               | April 26             | 5                     | 5                      |

### High-level Design of Solution

- Add a UML class diagram, etc.
- High-level pseudo code for each component.


### Used Data Structures
Explanation of what data structures are used where. For each, state
    - time and space complexity (Big-Oh),
    - why it is the appropriate data structure and what other data structure could have been used.

    In the AVL tree file, we used the AVL tree data structure. It's time and space complexity is O(log(n)) for the balance function to find the correct spot for an inserted item into the AVL Tree. There are no other data structures in this case that could substitute the AVL Tree.
    In the DocumentParser file, we used the set data structure. It's time and space complexity is O(log(n)) for the insert/find function that we used in the LoadStopWords function. We used this data structure because it is sorted meaning the time complexity is better. Other data structures that could have been used are an unordered set and a list.
    In the QueryProcessor file, we used the map data structure. It's time and space complexity is O(log(n)) for the find function that we used in the intersectMaps and exludeMaps functions. This is thet correct data structure because we needed to store a key value which is the document ID and it's respective value which is the frequencies. In this case, you could have implemented your own hashtable.

### User Documentation
- What are the features of your software?

Our software is able to create an index (AVL tree) if you give it a directory of json documents to sift through organizing three different AVL trees, a tree of words, a tree of people, and a tree of organizations all relating to the documents given to the program.
It is also able to write an index (AVL tree) to a file for storage once the program is turned off.
It is also able to read an index (AVL tree) from a file to pull from old data if the program is restarted.
The user is able to search for given words, names, or organizations using the query function which will return all relevant documents ranked from most relevant to least relevant.
From those returned documents, the user is able to choose one of the documents to have all the text from the document printed out for the user to read.

- Describe how to use the software.
The user will have a command line interface from which their first argument in the command line will be called "supersearch" followed by additional information the user wants, such as indexing files and storing the index, writing the index to a file and read an index from a file, creating an index from a directory with documents, or loading the existing index and performing a query. From here, the user can type in "supersearch ui" to pull up a user interface from which there will be dropdowns to choose what the user wants to do. For example, indexing all files in a directory the user will choose and storing the index in one or several files will look like this: "supersearch index <directory>". Loading the existing index and performing a query would look like this: supersearch query "social netwwork PERSON:cramer". For the search command: "supersearch ui", the user will be able to create an index, save/load index and perform multiple queries from a list of drop downs such as "Press q to start a new query". 


- Some example queries with the results.





### Performance
- Provide statistics (word counts, timing, etc) for indexing all documents (or as many as you can in a reasonable amount of time). 

### Bonus Work
Did you attempt any bonuses? If so, please give a brief description of what you did.

   > Yes, the implementation of a very smart revelancy ranking. 
