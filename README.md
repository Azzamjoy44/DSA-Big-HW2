# Project Overview

This repository contains implementations for two distinct programs:

1. **Ancient Language Alphabet Order Finding Program**
2. **Quad Tree Image Representation Program**

Each program is described in detail below, with instructions on how to use them.

---

# Ancient Language Alphabet Order

This program is used to find the order of characters in an ancient language using a directed acyclic graph (DAG) with topological sorting. The ancient language's alphabet uses all the characters of the English language, but the order of the characters in the ancient language is different from the order of the characters in the English language.

## Features:
1. Creation of a directed graph using an adjacency matrix.
2. Depth-First Search (DFS) algorithm to explore the graph.
3. Topological sorting to determine the correct order of characters in the ancient language.
4. Reading words from an input file `index.in` and writing the correct order of the characters to an output file `index.out`.
5. The graph, topological sort, and the characters whose position in the order of characters could not be determined due to insufficient input data, are all printed onto the console as well.

## Files included:
- `Directed Graph.h`
- `Ancient Language.cpp`
- `index.in`
- `index.out`

## How to use:
1. Edit the `index.in` file to include the list of words in the ancient language. Each word should be on a separate line. Terminate the input with a period (.) on a new line.
2. Compile and run the code in the `Ancient Language.cpp` file.
3. The program will output to the console the graph, the topological sort result, and the characters whose order could not be determined due to insufficient input data.
4. The topological sort (correct order of characters) is also written to the `index.out` file.

---

# Quad Tree Image Representation

This program demonstrates how to represent a 1024x1024 pixel image using a quad tree data structure. Users can input two image quad trees, and merge them into a single quad tree. The program also calculates the number of black pixels in the images and displays the trees by levels.

## Features:
1. Create quadtree image representations from preorder traversals.
2. Display an image tree and the number of black pixels in the corresponding image.
3. Merge two inputted image trees and display the resulting merged image tree, including the number of black pixels in the merged image.

## Files included:
- `Quad Tree Image Representation.cpp`

## How to use:
1. **Begin program execution.**
2. Throughout the execution, the program will prompt you to:
   - Create an Image Quad Tree.
   - Display an image tree and the number of black pixels in the image.
   - Merge two inputted image trees and display the merged tree and the number of black pixels in the merged image.
   - Cease program execution.

   Input a number between `1` and `4` (both inclusive) to select an operation to perform.
   - Input `1` to order the program to create an Image Quad Tree.
   - Input `2` to order the program to display an image tree and the number of black pixels in the image.
   - Input `3` to order the program to merge two inputted image trees and display the merged tree and the number of black pixels in the merged image.
   - Input `4` to order the program to cease program execution.
   When you have completed execution of any operation (besides operation 4), you will be prompted again to select an operation from among those mentioned above to perform. 

   **Note:** Do not input integers outside the range or other data types, as this may cause the program to function improperly or crash.

3. **Creating an Image Quad Tree**:
   - Input `1` when given the prompt mentioned in step 2.
   - The program will ask you to input the preorder traversal of the tree (e.g., `pwpwbbwbpbbwb`).
   - Afterwards, you must provide an index position (`0` or `1`) in which you would like to store the created quad tree.
   - The program will create the image quad tree from the character sequence you inputted and the tree will be stored at the index position you specified.

   **Note:** Ensure the character sequence you input contains only `p`, `b`, or `w` characters, and that the sequence of characters is a valid preorder traversal of an image quad tree. When you are asked to input an index, please input either `0` or `1`. Invalid input may cause the program to crash.

4. **Displaying an Image Tree and Black Pixels**:
   - Input `2` when given the prompt mentioned in step 2.
   - If you have created at least one tree, provide the index position (`0` or `1`) of the tree to display. If you provide an index which contains a tree, the image tree and the number of black pixels it contains will be displayed.
   - If no tree is stored at the provided index or no tree has been created, the program will inform you.

5. **Merging Two Image Trees**:
   - Input `3` when given the prompt mentioned in step 2.
   - Ensure you have created two image trees (one stored at index `0` and another stored at index `1`) before ordering the program to merge two image tree.
   - If the merging is successful, the program will display the merged tree and the number of black pixels the merged tree contains. Otherwise, it will inform you that the merging process cannot happen because either index 0 or index 1 or both indices do not contain an image tree.

6. **Ceasing Program Execution**:
   - Input `4` when given the prompt mentioned in step 2, to stop the program.
