// Ancient Language.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This program is used to find the order of characters in an ancient language using a directed acyclic graph (DAG) with topological sorting. 
// The ancient language's alphabet uses all the characters of the English language, but the order of the characters in the ancient language is different from the order of the characters in the English language.
//

#include <iostream>
#include "Directed Graph.h"
#include <vector>
#include <string>
#include <fstream>
#include <set>
using namespace std;

//Function for performing a Depth-First Search on a graph
template<typename T>
int dfs(Graph<T>& graph, int index1, char* visited, char* visitedNodes, int size) {
	int index2; //Will be used to check if the node at `index2` has an inward directed edge to it from the node at `index1` 
	visited[index1] = 1; //We mark the node as visited

	for (index2 = 0; index2 < graph.N; index2++) {

		//If the node at `index1` has a directed edge to the node at `index2` we will recursively call the dfs funtion
		//The dfs function will eventually store a character in `visitedNodes` and return the size of `visitedNodes` after storing the character
		if (graph.adjacencyMatrix[index1][index2] && !visited[index2]) {
			size = dfs(graph, index2, visited, visitedNodes, size);
		}
	}
	visitedNodes[size] = graph.getNodeInfo(index1); //If a node has no more directed edges to other nodes, then the node's data will be stored in `visitedNodes`
	return size + 1; //This is returned to indicate an increased size of `visitedNodes` and also to identify where to store the next character in `visitedNodes`
}

//Function for topologically sorting a graph
template<typename T>
string topologicalSort(Graph<T>& graph) {
	int N = graph.N; //Number of nodes in the graph
	char* visited = new char[N](); //This will track the nodes which have been visited throughout the topological sorting process, and will not be re-initialised for each path
	char* topSortOrdering = new char[N](); //This will store the topological sort 
	int orderingIndex = N - 1; //This index is used to insert characters in `topSortOrdering` in the correct order

	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			char* visitedNodes = new char[N](); //If we have not visited node `i`, we will (re)-initialise this array so that we can store the nodes on the path we will follow
			int size = 0; // This tracks the number of nodes we have visited and stored in `visitedNodes`
			size = dfs(graph, i, visited, visitedNodes, size); //We will perform a depth-first search on the graph, starting from node `i`. The dfs will return the size of `visitedNodes`

			//We will start storing the characters which are in `visitedNodes` in `topSortOrdering`. The character at index 0 of `visitedNodes` will be stored at index `N-1` of `topSortOrdering` and the character at index 1 of `visitedNodes` will be stored at index `N-2` and so on.
			for (int j = 0; j < size; j++) {
				topSortOrdering[orderingIndex] = visitedNodes[j];
				orderingIndex--;
			}
		}
	}

	string topSortString = "";

	for (int index = 0; index < N; index++) {
		topSortString += topSortOrdering[index];
	}

	return topSortString;

}

//Function to print a graph
template<typename T>
void printGraph(Graph<T>& graph) {
	int N = graph.N; //Number of nodes in the graph

	//If there is one node, we print the node and exit the function
	if (N == 1) {
		cout << graph.getNodeInfo(0) << "\n";
	}

	//Otherwise, we will enter this block of code
	//This block will print the connections between nodes
	else {
		for (int x = 0; x < N; x++) {
			for (int y = 0; y < N; y++) {

				//If there is a directed edge from node `x` to node `y`, we will display the connection
				if (graph.adjacencyMatrix[x][y]) {
					cout << graph.getNodeInfo(x) << " ---> " << graph.getNodeInfo(y) << "\n";
				}
			}
		}
	}
	cout << "\n";
}


int main()
{

	vector<string> list; //We make a vector `list` to store all the words from the file "index.in"
	fstream inputFile; //This variable represents the input file
	inputFile.open("index.in", ios::in); //We open the file

	/*If the file is open and while we have not reached the end of the file,
	we get the words from the file, check if the word is a '.'
	If the word is not a '.' we store the word in `list` and if we encounter a '.' we stop reading from the file*/
	if (inputFile.is_open()) {
		string word;
		int dotCheck = 1;
		while (getline(inputFile, word) && dotCheck != 0) {
			dotCheck = word.compare(".");
			if (dotCheck != 0) {
				list.push_back(word);
			}
		}
		inputFile.close(); //We close the file when we are done storing all the words
	}

	//We will check for the special case where there is only one word/letter in the list, or if there are multiple words/letters which are all equal to each other
	string firstWord = list.at(0);
	bool allWordsEqual = true;
	for (int index = 0; index < list.size(); index++) {
		if (firstWord != list.at(index)) {
			allWordsEqual = false;
		}
	}

	/*This if block handles the case when there is only one word in "index.in" or when 
	there are multiple words in the file and every word is equal to every other word*/
	if (allWordsEqual) {

		char result = list.at(0)[0]; //The result will be the first character of the first word, or if it's just a single character, the result will be just that character
		Graph<char> charGraph(1); //We initialize the graph which will only store one character
		charGraph.setNodeInfo(0, result); //We store the character in the `charGraph`

		//We print the graph
		cout << "The Graph:\n\n";
		printGraph(charGraph);
		cout << "Topological Sort: " << result << "\n\n"; //The topological sort algorithm is not run, because we can consider that the graph has already been topologically sorted as there is just a single character and there are no edges in the graph

		//We write the letter to the file "index.out" and cease program execution
		fstream outputFile;
		outputFile.open("index.out", ios::out);
		if (outputFile.is_open()) {
			outputFile << result << "\n";
			outputFile.close();
		}
	}

	//This block of code handles the general case
	else {

		vector<char> charsWithEdges; //This vector is used to store the unique characters which have edges between them. A unique character will only be stored once in this vector
		vector<char> charEdges; //This vector is used to "note down" the directed edges between characters. The character at index `i` will have a directed edge to the character at index `i+1` and the character at index `i+2` will have an edge to the character at index `i+3`. The character at index `i+1` will NOT have an edge to the character at index `i+2`.

		//We iterate through the words in `list` and compare all pairs of adjacent words in `list`
		for (int index1 = 0; index1 < list.size() - 1; index1++) {

			//These strings store a pair of adjacent words
			string word1 = list.at(index1);
			string word2 = list.at(index1 + 1);

			//These chars will store a character from `word1` and `word2` at the same indices
			//We will start by comparing the first character of both words
			char char1 = word1[0];
			char char2 = word2[0];

			//One of the conditions to stop comparing the words is when char1 != char2
			//We will initially assume that the characters are equal to each other
			bool charsEqual = true;

			int charIndex = 0; //This variable is used to assign the next characters in `word1` and `word2` to `char1` and `char2` respectively.

			//We iterate through the characters in the adjacent words until we find the first pair of mismatched characters or we reach the end of one of the words
			while ((charsEqual) && (char1 != '\0' && char2 != '\0')) {

				if (char1 != char2) {
					charsEqual = false; //If a pair of mismatched characters is found, charsEqual will be assigned "false"

					//We push the characters to the back of the `charEdges` vector, effectively "noting down" that `char1` has a directed edge to `char2`
					//First we push `char1` because this is the character which will have a directed edge to another character
					//Secondly, we push 'char2' because this is the character which has a directed edge coming towards it from `char1`
					charEdges.push_back(char1);
					charEdges.push_back(char2);

					//We will now check if `charWithEdges` contains the two characters.
					//The character not already in `charsWithEdges` will be stored in `charsWithEdges`
					//We will initially assume that both characters are not in `charsWithEdges`
					bool char1Present = false;
					bool char2Present = false;
					for (int i = 0; i < charsWithEdges.size(); i++) {
						if (char1 == charsWithEdges.at(i)) {
							char1Present = true;
						}
						else if (char2 == charsWithEdges.at(i)) {
							char2Present = true;
						}
					}

					//The chars not in `charsWithEdges` will be stored in `charsWithEdges`
					if (!char1Present) {
						charsWithEdges.push_back(char1);
					}
					if (!char2Present) {
						charsWithEdges.push_back(char2);
					}
				}
				//If the characters are equal to each other, we check the next pair of adjacent characters
				else {
					charIndex++;
					char1 = word1[charIndex];
					char2 = word2[charIndex];
				}
			}

		}

		//We create a graph and store the unique characters of `charsWithEdges` in the graph
		Graph<char> charGraph(charsWithEdges.size());
		int index = 0;
		for (char c : charsWithEdges) {
			charGraph.setNodeInfo(index, c);
			index++;
		}

		//We iterate through `charEdges` to identify the edges which need to be added in the `charGraph`
		for (int vectorIndex = 0; vectorIndex < charEdges.size() - 1; vectorIndex += 2) {
			char char1 = charEdges.at(vectorIndex);
			char char2 = charEdges.at(vectorIndex + 1);
			int char1Index = 0, char2Index = 1; //These variables are used to store the index position of `char1` and `char2` in the graph

			//We will try to find the index position of `char1` and `char2` in `charGraph` in order to create an edge from `char1` to `char2` in the `charGraph`

			//First we will try to find `char1` in the graph
			for (int graphIndex = 0; graphIndex < charGraph.N; graphIndex++) {

				//If we find the index of `char1` in the graph, we store the index in `char1Index` and stop checking further
				if (char1 == charGraph.getNodeInfo(graphIndex)) {
					char1Index = graphIndex;
					break;
				}
			}

			//Now we will try to find `char2` in the graph
			for (int graphIndex = 0; graphIndex < charGraph.N; graphIndex++) {

				//If we find the index of `char2` in the graph, we store the index in `char2Index` and stop checking further
				if (char2 == charGraph.getNodeInfo(graphIndex)) {
					char2Index = graphIndex;
					break;
				}
			}

			//We create the directed edge from `char1` to `char2` by passing their indexes in the graph, to the graph function `addEdge()`
			charGraph.addEdge(char1Index, char2Index);
		}

		//We print the graph
		cout << "The Graph:\n\n";
		printGraph(charGraph);

		//We call the topolgical sort function and store the `topSortString` in the `result`
		string result = topologicalSort(charGraph);
		cout << "Correct order of the letters in the ancient language's alphabet: ";
		for (char c : result) {
			cout << c << " ";
		}
		cout << "\n\n";

		//We write `result` to the file "index.out"
		fstream outputFile;
		outputFile.open("index.out", ios::out);
		if (outputFile.is_open()) {
			outputFile << result << "\n";
			outputFile.close();
		}

		//We will now check which letters were not added to the graph and topologically sorted because they were isolated characters

		set<char> uniqueChars; //This will store all the unique characters which exist in the input data
		for (string word : list) {
			for (char c : word) {
				uniqueChars.insert(c);
			}
		}

		vector<char> unusedChars; //This will store all the unused characters
		bool charUsed; //This variable is used to "note down" if a character was used to produce the final result or not

		//We iterate through the characters in `uniqueChars` and check if each character was used in the final output or not
		for (char c : uniqueChars) {
			charUsed = false; //We initially assume the character was not used in the final output

			//We iterate through the nodes in `charGraph` to check if the char `c` is stored in `charGraph` as a node
			for (int index = 0; index < charGraph.N; index++) {
				if (c == charGraph.getNodeInfo(index)) {
					charUsed = true; //If `c` is in the graph, then we mark the character as used
				}
			}

			//If the character was not used in the graph, then we push the unused character to the back of `unusedChars`
			if (!charUsed) {
				unusedChars.push_back(c);
			}
		}

		//If there are unused characters, we will print them to the screen and then we will cease program execution
		if (unusedChars.size() != 0) {
			cout << "The following letters are also in the ancient language's alphabet but their actual position cannot be determined;\n\n";
			for (char c : unusedChars) {
				cout << c << " ";
			}
			cout << "\n";
		}

	}
	
}