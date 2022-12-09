# CSCI 2275 – Data Structures - Final Project
by sam d

## **DESCRIPTION**

This is a minigit integration. It enbles a user to create, edit, and save files. Using this tool you are able too save changes to a file and restore previous iterations of that file. This is done through commits. In which a user edits and creates files before adding them to this current iteration of a commit. The commit can then be initialized so that the added files to that designated commit are saved in a hidden folder and can be restored by means of checkout. Each commit comes with a message, this message can then be used to search for a certain commit by using the search function. In order to get started simply run the ./run_app_1 executible in the build directory, then add your files to the FilesGoHere directory in order for the program to recognize any of the fiels you are inputting.

## **HASH TABLE**

This project's commits are stored on a hash table. The entirety of this hash table is abstracted away from the user so that they don't need to worry about interacting with it. But the hash table enables users to quickly find which commits are listed under certain key words as defined by each commit's message. This is done through the hash function desginating a generated integer to place the commit on an array. At times the generated integer may overlap, in the event of this collision the commit is simply "chained" on the end of that commit through linking.

## **MENU FUNCTIONS**

Here are the menu functions that a user can see once they run the program. This menu has 7 options and they as described as...

### **OPTION I ::: INIT**

The init method takes no input. The init creates a hidden directory called .minigit to store all your altered and committed files. The init function also initializes the hash table with a table size of 5. In addition, it creates the first commit node so that whenever you edit files you are free to add your files after running init. Speaking of adding files...

### **OPTION II ::: ADD**

The add method takes one input, the file name. The add method first goes through a checklist before doing anything. The add function determines if the file defined by the inputted file even exists, then it determines if that file is already added in the current commit, if it is then it will display a message informing the user of such, then it will check if the file is added in any previous commits, if the file exists in any previous commits, with will increment the file version that exists in the .minigit directory. Otherwise it will create an edition 0 of the file.

### **OPTION III ::: REMOVE**

The remove method takes one input, a file name that is currently added to the current commit. First, the method checks if the file is added to the current commit, if not the program will notify the user of such. Otherwise, the method will remove the file from the current commit, meaning that file while not be committed.

### **OPTION IV ::: COMMIT**

The commit method takes one input, the commit message. The commit message is a string. The files added to the current commit are added to the .minigit directory. Here the program will determine if there are any previous iterations of the file, if there are, the file will be designated the latest version of that file, if there aren't then the file is made the 0th version. The commit message is stored on the doubly-linked list. The commit message is broken up into it's individual words, each of these words are then put into the hash table with the associated commit number. Using the search, the user can find a commit number going off the commit message they added.

### **OPTION V ::: CHECKOUT**

The checkout method takes one input, the commit number. The checkout method will overwrite all of the files in the current FilesGoHere directory with the files of the defined commit version. All files in the FilesGoHere directory will be removed before being replaced by the designated commit numbers files. The program will first remove all the current files from the FilesGoHere directory, then the program will scour through the linked lists before finding all the files from the commit number and add them to the FilesGoHere directory.

### **OPTION VI ::: SEARCH**

The search method takes one input, a word. The word is then searched for in the hash table, if it is located then it will print the key used and the commit numbers associated with it. If there the word is not found then the program will tell the user such.

### **OPTION VII ::: QUIT**

Says goodbye and exits the program.

## **QUICKSTART GUIDE**

To quickly get using this version system, download all of the relevant files, go to the build directory, type ./run_app_1, choose option 1, create and alter your files in the FilesGoHere directory, add those files with option 2, remove any unwanted files from the commit with option 3, then commit them with option 4, repeat creating and altering your files in the FilesGoHere directory, if you ever want to restore a version then search for it using an associated keyword with option 6, then use the information gained from the previous step and proceed to option 5 and enter aforementioned information, your files will be restored, continue in this manner until you are done, then exit the program with option 7.
