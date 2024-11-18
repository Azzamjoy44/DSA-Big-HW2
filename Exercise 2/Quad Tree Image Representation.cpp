#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class QuadTree {
public:
    bool isLeaf; //Indicates if the node is a leaf or a parent
    bool color; //True for black, false for white
    QuadTree** children; //Four children

    QuadTree() { //Constructor
        isLeaf = false;
        color = false;
        children = new QuadTree*[4];

        for (int i = 0; i <= 3; i++) {
            children[i] = nullptr;
        }
    }

    int countBlackPixels(int depth) {
        if (this == nullptr) {
            return 0;
        }
        if (this->isLeaf) {
            if (this->color) { //Black node found
                return (1024 / pow(4, depth)); //We take into account the depth we are at when we calculate the number of black pixels represented by the node
            }
            else { //White node found
                return 0; //We are not intersted in the number of white pixels, so we do not add anything to the total count of black pixels
            }
        }
        else {
            int count = 0; //Total count of black pixels. Initially zero
            for (int i = 0; i <= 3; i++) {
                count += this->children[i]->countBlackPixels(depth + 1); //We explore the children and add the number of pixels returned to the total count
            }
            return count;
        }
    }

    int getNumOfNodesOnLongestPath() {
        if (this == nullptr) {
            return 0;
        }
        else { //We get the height of each child so we can compare the heights and identify the maximum height
            int child0Height = this->children[0]->getNumOfNodesOnLongestPath();
            int child1Height = this->children[1]->getNumOfNodesOnLongestPath();
            int child2Height = this->children[2]->getNumOfNodesOnLongestPath();
            int child3Height = this->children[3]->getNumOfNodesOnLongestPath();

            //The heights of the children are compared and the largest height + 1 is returned, taking into account the parent node
            //The final return value of this function will be the number of nodes on the longest path 

            if (child0Height >= child1Height && child0Height >= child2Height && child0Height >= child3Height) {
                return (child0Height + 1);
            }
            else if (child1Height >= child0Height && child1Height >= child2Height && child1Height >= child3Height) {
                return (child1Height + 1);
            }
            else if (child2Height >= child0Height && child2Height >= child1Height && child2Height >= child3Height) {
                return (child2Height + 1);
            }
            else {
                return (child3Height + 1);
            }

        }
    }

    void displayCurrentLevel(int level) {
        if (this == nullptr) {
            return;
        }
        if (level == 1) { //When we are at the desired level, we print the data.
            if (!this->isLeaf) {
                cout << "p   ";
            }
            else {
                if (this->color) {
                    cout << "b   ";
                }
                else {
                    cout << "w   ";
                }
            }
        }
        else if (level > 1) { //We will go to the next level and decrement 'level' until we reach the base case
            this->children[0]->displayCurrentLevel(level - 1);
            this->children[1]->displayCurrentLevel(level - 1);
            this->children[2]->displayCurrentLevel(level - 1);
            this->children[3]->displayCurrentLevel(level - 1);
        }
    }

    void displayByLevels() { //This function will use 'displayCurrentLevel' and 'getNumOfNodesOnLongestPath' to print the tree by levels
        int numOfNodesOnLongestPath = this->getNumOfNodesOnLongestPath();
        for (int i = 1; i <= numOfNodesOnLongestPath; i++) {
            this->displayCurrentLevel(i);
            cout << "\n\n"; //To seperate the levels from each other and identify which level is which
        }
    }

    void preorderTraversal() { //Performs a preorder traversal of the quad tree. This function is used to display the preorder traversal of the merged image
        if (!this->isLeaf) {
            cout << "p  ";
        }
        else {
            if (this->color) {
                cout << "b  ";
            }
            else {
                cout << "w  ";
            }
        }
        if (this->children[0] != nullptr) {
            for (int i = 0; i <= 3; i++) {
                this->children[i]->preorderTraversal();
            }
        }
    }
};

QuadTree* quadTreeCreation(string preorderTraversal, int& index) {
    char node = preorderTraversal[index]; //We check the character at the index we are currently at. This character will tell us how to manage the node.
    index++;
    if (node == 'p') { //If the character is a 'p', we make a parent node with four children and return the parent
        QuadTree* parentNode = new QuadTree();
        parentNode->isLeaf = false;
        for (int i = 0; i <= 3; i++) { //The parent node will have children so we will create the children of the parent node
            QuadTree* childNode = quadTreeCreation(preorderTraversal, index);
            parentNode->children[i] = childNode;
        }
        return parentNode;
    }
    else if (node == 'b') { //If the character is a 'b' we simply make a leaf with color black, and return it
        QuadTree* leafNode = new QuadTree();
        leafNode->isLeaf = true;
        leafNode->color = true;
        for (int j = 0; j <= 3; j++) { //The leaf node will have no children
            leafNode->children[j] = nullptr;
        }
        return leafNode;
    }
    else { //If the character is a 'w' we simply make a leaf with color white, and return it
        QuadTree* leafNode = new QuadTree();
        leafNode->isLeaf = true;
        leafNode->color = false;
        for (int k = 0; k <= 3; k++) { //The leaf node will have no children
            leafNode->children[k] = nullptr;
        }
        return leafNode;
    }
}

QuadTree* mergeTrees(QuadTree* tree1, QuadTree* tree2) {
    if (tree1 == nullptr) {
        return tree2;
    }
    if (tree2 == nullptr) {
        return tree1;
    }
    if (tree1->isLeaf && tree2->isLeaf) {
        if (tree1->color && !tree2->color) {
            return tree1; //Return 'tree1' because 'tree1' is black
        }
        else if (!tree1->color && tree2->color) {
            return tree2; //Return 'tree2' because 'tree2' is black
        }
        else {
            return tree1; //Return any of the two trees because they are both white
        }

    }
    else if (tree1->isLeaf && !tree2->isLeaf) {
        if (tree1->color) {
            return tree1; //Return 'tree1' because the whole merged quadrant will be black
        }
        else {
            return tree2; //Return 'tree2' because 'tree1' is white and 'tree2' may or may not be white
        }
    }
    else if (!tree1->isLeaf && tree2->isLeaf) {
        if (tree2->color) {
            return tree2; //Return 'tree2' because the whole merged quadrant will be black
        }
        else {
            return tree1; //Return 'tree1' because 'tree2' is white and 'tree1' may or may not be white
        }
    }
    else { //This block runs when both nodes are parents. The node made in this block may or may not be a parent. We assume the node is a parent at first. If the children of the merged node are all the same color, the node will be made a leaf which is the same color as it's children and it will be returned as a leaf. Otherwise, the node is returned as a parent.
        QuadTree* node = new QuadTree(); //This merged node may or may not be a parent by the end of this block of code
        node->isLeaf = false; //Initially we assume the node is a parent
        for (int i = 0; i <= 3; i++) { //We create the children of the merged parent by merging the children of 'tree1' and 'tree2'
            QuadTree* childNode = mergeTrees(tree1->children[i], tree2->children[i]);
            node->children[i] = childNode;
        }
        
        //We will now want to check if the children of the merged parent are all leaves which have the same color. If so, we will turn the merged parent node into a leaf node

        bool allLeafChildren = true;
        for (int j = 0; j <= 3; j++) {
            if (!node->children[j]->isLeaf) {
                allLeafChildren = false;
                break;
            }
        }

        bool sameColorLeafChildren = true;
        if (allLeafChildren) { //Only when all the children are leaves, we will check their colors, because parents themselves don't have a color.
            bool colorOfChild1 = node->children[0]->color;
            for (int k = 1; k <= 3; k++) {
                if (colorOfChild1 != node->children[k]->color) {
                    sameColorLeafChildren = false;
                    break;
                }
            }

            if (sameColorLeafChildren) { //If all the child leaves have the same color, the merged parent node will become a leaf, and it will be returned as a leaf. Otherwise it will be returned as a parent
                node->isLeaf = true; //The node is declared a leaf
                node->color = colorOfChild1; //The nde is given the color of it's children
                for (int l = 0; l <= 3; l++) { //Because the merged parent is becoming a leaf, we will make the children point to nullptr
                    node->children[l] = nullptr;
                }
            }

        }

        return node; //We return 'node' either as a merged parent or as a leaf
    }
}

int main() { 

    int userInput1; //This variable will help the program understand what the user wants the program to do

    string userInputTraversal; //This variable will store any preorder traversals the user inputs

    QuadTree** imageTrees = new QuadTree*[2]; //This is an array of pointers which will point to the quad trees the user creates

    QuadTree* mergedImageTree = nullptr; //This will point to the merged image tree when the user merges two images

    int startIndex; //This is always initialised to zero when it is used. It is used to create quad trees from preorder traversals. This variable will track the current character we are at in the preorder traversal string when we are creating the quad tree

    bool twoTreesExist; //This is used to ensure if two trees have been inputted by the user in separate indices (0 and 1) before the program attempts to merge two trees

    bool noTrees; //This variable checks if there are any trees have been inputted by the user so far. If at least one tree has been inputted by the user, the user can display an inputted tree's information

    for (int i = 0; i <= 1; i++) {
        imageTrees[i] = nullptr;
    }

    cout << "Program is running. . .\n\n";

    do {
        cout << "What would you like to do?:\n"; //The user is given options. They can pick any option from 1-4 and the program will execute the corresponding functions
        cout << "1. Create an Image Quad Tree;\n";
        cout << "2. Display an Image Tree and the number of black pixels in the image;\n";
        cout << "3. Merge inputted Image Trees and display the Merged Image Tree and the number of black pixels in the merged image;\n";
        cout << "4. Stop program execution;\n";
        cout << "Select an option (input a number from 1-4): ";
        cin >> userInput1;
        cout << "\n\n";

        switch (userInput1) {
        case 1:
            cout << "Input the preorder traversal of the quad tree: ";
            cin >> userInputTraversal;

            int userInputIndex;
            cout << "In which index position would you like to store the traversal? (input 0 or 1): ";
            cin >> userInputIndex;

            while (userInputIndex != 0 && userInputIndex != 1) { //We want the user to enter an index between 0 and 1 (inclusive) because we can only have a single pair of trees at a time, not more
                cout << "Please input a 0 or 1 for the index position: ";
                cin >> userInputIndex;
            }

            startIndex = 0;
            imageTrees[userInputIndex] = quadTreeCreation(userInputTraversal, startIndex);
            cout << "Image Tree has been successfully created.";
            cout << "\n";
            cout << "\n";

            break;

        case 2:

            noTrees = true;

            for (int i = 0; i <= 1; i++) {
                if (imageTrees[i] != nullptr) {
                    noTrees = false;
                }
            }

            if (!noTrees) { //If at least one tree exists, the user is asked which tree they would like to print
                cout << "Input the index position of the image tree you would like to display (input 0 or 1): ";
                cin >> userInputIndex;

                while (userInputIndex != 0 && userInputIndex != 1) {
                    cout << "Please input a 0 or 1 for the index position: ";
                    cin >> userInputIndex;
                }

                if (imageTrees[userInputIndex] != nullptr) {
                    cout << "Image Tree displayed by levels:\n\n";
                    imageTrees[userInputIndex]->displayByLevels();
                    cout << "\n\nThe number of black pixels in the image: " << imageTrees[userInputIndex]->countBlackPixels(0);
                }
                else { //If the user picks an index which has not yet been filled with a tree, the program informs them of the error
                    cout << "Error: Cannot display tree\n";
                    cout << "There is no image tree at this index";
                }
            }
            else { //If there are no trees at all the user is informed that they have not inputted any trees so far which can be displayed
                cout << "Error: Cannot display tree\n";
                cout << "You have not inputted any image trees yet\n";
                cout << "Try again after inputting an image tree";
            }

            cout << "\n";
            cout << "\n";

            break;

        case 3:
            twoTreesExist = true;
            for (int i = 0; i <= 1; i++) {
                if (imageTrees[i] == nullptr) {
                    twoTreesExist = false;
                }
            }

            if (twoTreesExist) { //If two trees have been stored we will begin the merging process
                mergedImageTree = mergeTrees(imageTrees[0], imageTrees[1]);
                cout << "Merged Image Tree:\n\nPre-order Traversal: ";
                mergedImageTree->preorderTraversal();
                cout << "\n\nDisplayed By Levels:\n\n";
                mergedImageTree->displayByLevels();
                cout << "\n\nThe number of black pixels in the merged image: " << mergedImageTree->countBlackPixels(0);
            }
            else { //Otherwise, we inform the user of the error.
                cout << "Error: Cannot merge trees\n";
                cout << "You have not inputted image trees in both index positions 0 and 1\n";
                cout << "Try again after inputting image trees in both index positions 0 and 1\n";
            }
            cout << "\n";
            cout << "\n";

            break;

        case 4: //If the user inputs 4, we stop program execution
            cout << "Stopping program execution...\n";

            break;

        default:
            cout << "You inputted an invalid option, try again\n\n";

            break;
        }

    } while (userInput1 != 4); //We loop until the user inputs 4
    
}
