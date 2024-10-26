# Did it Make the News? - Financial News Search Engine

### Authors: Aaron Santa Cruz, Spencer Neil, Hunter Ryan

## Project Overview
This project is a custom-built search engine designed to search and rank financial news articles from January to May 2018, using a dataset of over 300,000 articles. Users can perform complex searches on this dataset, filtering results by keywords, people, or organizations. Each article is stored in JSON format, enabling efficient processing and querying using metadata fields.

The system includes a structured index architecture, relevancy ranking based on term frequency-inverse document frequency (tf-idf), and entity-specific search functionality, creating a comprehensive financial news search engine.

## Objectives
- **Document Parsing**: Efficiently process news articles, clean data by removing stopwords and stemming keywords, and create searchable document entries.
- **Efficient Indexing**: Use AVL trees for inverted indexing of terms, organizations, and people, allowing rapid querying.
- **Relevance Ranking**: Implement tf-idf-based ranking for search results to ensure the most relevant articles appear first.
- **Entity-Specific Querying**: Allow filtering by people or organizations directly in search queries.
- **Data Persistence**: Implement custom serialization for AVL trees to retain index data between sessions, improving runtime efficiency.

## Learning Objectives
This project provides an opportunity to:
1. Work with complex data structures, such as AVL trees, and learn to manage their persistence.
2. Develop skills in data processing with JSON, including parsing and filtering large datasets.
3. Implement foundational search engine techniques, such as tf-idf, stop word removal, and stemming.
4. Gain experience in designing a command-line and optional UI interface for processing user queries and displaying search results.
5. Understand serialization for data structures, allowing for persistence across sessions.

## Used Data Structures
1. **AVL Tree**: Used for efficient indexing of keywords, people, and organizations with a time complexity of \(O(\log(n))\). This data structure allows us to maintain balanced trees for fast data retrieval.
2. **Set**: Employed in the `DocumentParser` to manage stopwords, offering sorted, efficient data handling for functions like `LoadStopWords`.
3. **Map**: Used in `QueryProcessor` to store and retrieve document IDs along with term frequencies, which aids in quick lookups during query processing.

## Features
- **User Interface**: 
  - Supports commands for indexing, querying, and viewing specific articles.
  - Supports entity-based search, allowing for queries such as `ORG:reuters` or `PERSON:strax` for precise results.
  - A UI interface provides dropdown options for indexing, saving/loading indexes, and running queries.
  
## How to Use the Software
The software operates via a command-line interface, where users can start with the `supersearch` command followed by specific actions, including indexing files, storing/loading an index, and performing searches. For an interactive experience, a user interface (`supersearch ui`) provides dropdown options for various actions. Here are examples of commands:

- **Indexing a Directory**:  
  To index all files in a specified directory, use:

  supersearch index <directory>

- **Loading and Querying an Existing Index**:
    To load an existing index and perform a search with:

    supersearch query "social network PERSON:cramer"

- **User Interface Mode**:
    Launch the UI with dropdown options by entering:

    supersearch ui

    **SuperSearch UI Capabilities:**

    The SuperSearch user interface (supersearch ui) provides the following options for managing the search engine and queries:

    1. Indexing: Allows users to specify a directory to index, creating an AVL tree for words, persons, and organizations found in the documents.
    2. Writing Index to File: Exports the current index to files, storing each tree in a separate file.
    3. Reading Index from File: Imports a saved index from files to continue searching previously indexed data.
    4. Querying: Users can enter search queries and receive ranked results based on relevance. Query options include:
        - Print the next 5 documents from the result set.
        - Start a new query.
        - Print the full text of a specific document that comes up in search
        - Exit the query menu and return to the main menu.


## Example Queries with Results

**Query 1.** 

hcryan@genuse60.smu.edu$ ./supersearch query "per"
1. Article Name: Eaton Vance Closed-End Funds Release Estimated Sources Of Distributions Publication Date: 2018-02-28T18:54:00.000+02:00

2. Article Name: BRIEF-Francesca’s Sees Q4 2017 GAAP Earnings Per Share $0.07 To $0.11 Publication Date: 2018-02-28T05:29:00.000+02:00

3. Article Name: BRIEF-Strax Ab Result For Period Jan 1 - Dec 31 2017 amounted to 0.03 Euros Per Share​ Publication Date: 2018-02-28T04:00:00.000+02:00

4. Article Name: BRIEF-Kewaunee Scientific Q3 Earnings Per Share $0.31 Publication Date: 2018-02-28T08:59:00.000+02:00

Query took 0.0268854 seconds

**Query 2.**

hcryan@genuse60.smu.edu$ ./supersearch query "ORG:reuters"
1. Article Name: BRIEF-Francesca’s Sees Q4 2017 GAAP Earnings Per Share $0.07 To $0.11 Publication Date: 2018-02-28T05:29:00.000+02:00

2. Article Name: German firms doing business in UK gloomy about Brexit - survey Publication Date: 2018-02-27T20:09:00.000+02:00

3. Article Name: BRIEF-Strax Ab Result For Period Jan 1 - Dec 31 2017 amounted to 0.03 Euros Per Share​ Publication Date: 2018-02-28T04:00:00.000+02:00

4. Article Name: BRIEF-Kewaunee Scientific Q3 Earnings Per Share $0.31 Publication Date: 2018-02-28T08:59:00.000+02:00

Query took 0.0206422 seconds

**Query 3.** 

hcryan@genuse60.smu.edu$ ./supersearch query "per ORG:reuters"
1. Article Name: BRIEF-Francesca’s Sees Q4 2017 GAAP Earnings Per Share $0.07 To $0.11 Publication Date: 2018-02-28T05:29:00.000+02:00

2. Article Name: BRIEF-Strax Ab Result For Period Jan 1 - Dec 31 2017 amounted to 0.03 Euros Per Share​ Publication Date: 2018-02-28T04:00:00.000+02:00

3. Article Name: BRIEF-Kewaunee Scientific Q3 Earnings Per Share $0.31 Publication Date: 2018-02-28T08:59:00.000+02:00

Query took 0.0290456 seconds

**Query 4.** 

hcryan@genuse60.smu.edu$ ./supersearch query "per ORG:reuters PERSON:strax"
1. Article Name: BRIEF-Strax Ab Result For Period Jan 1 - Dec 31 2017 amounted to 0.03 Euros Per Share​ Publication Date: 2018-02-28T04:00:00.000+02:00

Query took 0.017492 seconds


### Performance Statistic Example

Index took 0.090847 seconds
Unique names: 14
Unique orgs: 29
Unique words: 376
Files Indexed: 6
