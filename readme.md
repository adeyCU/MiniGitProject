# CSCI 2275 – Data Structures - Final Project
by sam d

##**DESCRIPTION**

This is a minigit integration. It enbles a user to create, edit, and save files. Using this tool you are able too save changes to a file and restore previous iterations of that file. This is done through commits. In which a user edits and creates files before adding them to this current iteration of a commit. The commit can then be initialized so that the added files to that designated commit are saved in a hidden folder and can be restored by means of checkout. Each commit comes with a message, this message can then be used to search for a certain commit by using the search function.

##**HASH TABLE**

This project's commits are stored on a hash table. The entirety of this hash table is abstracted away from the user so that they don't need to worry about interacting with it. But the hash table enables users to quickly find which commits are listed under certain key words as defined by each commit's message. This is done through the hash function desginating a generated integer to place the commit on an array. At times the generated integer may overlap, in the event of this collision the commit is simply "chained" on the end of that commit through linking.

##**MENU FUNCTIONS**

Here are the menu functions that a user can see once they run the program. This menu has 7 options and they as described as...

###**OPTION I ::: INIT**
