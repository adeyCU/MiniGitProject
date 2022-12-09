#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>

#include <cstring>

MiniGit::MiniGit() {
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
    fs::remove_all("FilesGoHere");
    fs::create_directory("FilesGoHere");
}

MiniGit::~MiniGit() {   
    // Any postprocessing that may be required
    BranchNode* prev = NULL;
    BranchNode* temp = commitHead;
    while(!(temp == NULL)) {
        FileNode* prevFile = NULL;
        FileNode* tempFile = temp->fileHead;
        while(!(tempFile == NULL)) {
            prevFile = tempFile;
            tempFile = tempFile->next;
            delete prevFile;
            prevFile = NULL;
        }
        prev = temp;
        temp = temp->next;
        delete prev;
        prev = NULL;
    }
}

void MiniGit::init(int hashtablesize) {
    ht = new HashTable(hashtablesize);
    BranchNode* nBranch = new BranchNode;
    commitHead = nBranch;
    nBranch->commitMessage = "";
    nBranch->commitID = 0;
    nBranch->next = NULL;
    nBranch->previous = NULL;
    nBranch->fileHead = NULL;
    commits = 0;
}

void MiniGit::add(string fileName) {
   if(recentCommit){
       if(fs::exists("FilesGoHere/"+fileName)){
           BranchNode* latest = commitHead;
           while(latest->next != NULL)
               latest = latest->next;
           if(latest->fileHead != NULL) {
               FileNode* temp = latest->fileHead;
               FileNode* prev = NULL;
               while(temp != NULL && temp->name != fileName){
                   prev = temp;
                   temp = temp->next;
               }
               if(temp == NULL) {
                   FileNode* newNode = new FileNode;
                   newNode->name = fileName;
                   newNode->version = 0;
                   newNode->next = NULL;
                   prev->next = newNode;
                   while(fs::exists(".minigit/"+newNode->name+"_"+to_string(newNode->version))) {
                       fstream file1("FilesGoHere/"+fileName);
                       fstream file2(".minigit/"+newNode->name+"_"+to_string(newNode->version));
                       char string1[256], string2[256];
                       while(!file1.eof()) {
                           file1.getline(string1,256);
                           file2.getline(string2,256);
                           if(strcmp(string1,string2) != 0){
                               newNode->version++;
                               cout << "File added." << endl;
                               return;
                           }
                       }
                       break;
               }
                   cout << "File added." << endl;
           } else {
                   if(fs::exists(".minigit/"+fileName+"_"+to_string(temp->version))) {
                       fstream file1("FilesGoHere/"+fileName);
                       fstream file2(".minigit/"+fileName+"_"+to_string(temp->version));
                       char string1[256], string2[256];
                       while(!file1.eof()) {
                           file1.getline(string1,256);
                           file2.getline(string2,256);
                           if(strcmp(string1,string2) != 0) {
                               temp->version++;
                               cout << "File added." << endl;
                               return;
                           }
                       }
                       cout << "File added already." << endl;
                   } else {
                       cout << "File added already." << endl;
                   }
               }
       } else {
               FileNode* newNode = new FileNode;
               newNode->name = fileName;
               newNode->version = 0;
               newNode->next = NULL;
               latest->fileHead = newNode;
               while(fs::exists(".minigit/"+newNode->name+"_"+to_string(newNode->version))) {
                   fstream file1("FilesGoHere/"+fileName);
                   fstream file2(".minigit/"+newNode->name+"_"+to_string(newNode->version));
                   char string1[256], string2[256];
                   while(!file1.eof()) {
                       file1.getline(string1,256);
                       file2.getline(string2,256);
                       if(strcmp(string1,string2) != 0) {
                           newNode->version++;
                           cout << "File added." << endl;
                           return;
                       }
                   }
                   break;
               }
               cout << "File added." << endl;
           }
   } else {
           cout << "Enter a file that exists." << endl;
       }
   } else {
       cout << "Switch to the latest commit" << endl;
   }
}

void MiniGit::rm(string fileName) {
    if(recentCommit) {
        BranchNode* latest = commitHead;
        while(latest->next != NULL)
            latest = latest->next;
        FileNode* prev = NULL;
        FileNode* temp = latest->fileHead;
        while(temp != NULL && temp->name != fileName) {
            prev = temp;
            temp = temp->next;
        } if(temp == NULL) {
            cout << "File does not exist." << endl;
        } else if(prev == NULL) {
            latest->fileHead = temp->next;
            delete temp;
            temp = NULL;
        } else {
            prev->next = temp->next;
            delete temp;
            temp = NULL;
        }
    } else {
        cout << "Switch to the latest commit" << endl;
    }
}



void MiniGit::printSearchTable() {
     ht->printTable();
}

//REVIEW ME!!!
void MiniGit::search(string key) {
    HashNode * temp = ht->searchItem(key);
    if (temp != NULL) {
        cout << "Commit(s) with key (" << key << ") are: ";
        for(int i = 0; i < temp->commitNums.size(); i++) {
            cout << temp->commitNums.at(i) << " ";
        }
        cout << endl;
    } else {
        cout << "There is no commit with this key." << endl;
    }
}


string MiniGit::commit(vector<string> messages,string msg) {
    if(recentCommit){
        BranchNode* prev = NULL;
        BranchNode* temp = commitHead;
        while(temp->commitMessage != "" && temp->commitMessage != msg) {
            prev = temp;
            temp = temp->next;
        }
        if(temp->commitMessage == ""){
            temp->commitMessage = msg;
            temp->previous = prev;
            FileNode* tempFile = temp->fileHead;
            while(tempFile != NULL){
                if(!fs::exists(".minigit/"+tempFile->name+"_"+to_string(tempFile->version))) {
                    string line;
                    ifstream readFile("FilesGoHere/"+tempFile->name);
                    ofstream writeFile(".minigit/"+tempFile->name+"_"+to_string(tempFile->version));
                    if(readFile && writeFile){
                        while(getline(readFile,line))
                            writeFile << line << "\n";
                    } else {
                        cout << "error in opening files" << endl;
                    }
                }
                tempFile = tempFile->next;
            }
            for(int i = 0; i < messages.size(); i++)
                ht->insertItem(messages.at(i),temp->commitID);
            BranchNode* nBranch = new BranchNode;
            FileNode* fileCopy = temp->fileHead;
            FileNode* prevCopy = NULL;
            while(fileCopy != NULL) {
                if(nBranch->fileHead == NULL) {
                    FileNode* newNode = new FileNode;
                    nBranch->fileHead = newNode;
                    newNode->name = fileCopy->name;
                    newNode->version = fileCopy->version;
                    prevCopy = newNode;
                    fileCopy = fileCopy->next;
                } else {
                    FileNode* newNode = new FileNode;
                    prevCopy->next = newNode;
                    newNode->name = fileCopy->name;
                    newNode->version = fileCopy->version;
                    prevCopy = newNode;
                    fileCopy = fileCopy->next;
                }
            }
            temp->next = nBranch;
            nBranch->commitMessage = "";
            commits++;
            nBranch->commitID = commits;
            nBranch->next = NULL;
            nBranch->previous = temp;
            return "CommitID: " + to_string(temp->commitID);
        }
        return "This commit message already exists.";
    }
    return "Please switch to the latest commit.";
    //should return the commitID of the commited DLL node
}

//REVIEW ME TOOOOOOO!
void MiniGit::checkout(string commitID) {
    BranchNode * temp = commitHead;
    while(temp != NULL && temp->commitID != stoi(commitID)) {
        temp = temp->next;
    }
    BranchNode * latestCommit = commitHead;
    while(latestCommit->next != NULL) {
        latestCommit = latestCommit->next;
    }
    if (latestCommit != temp) {
        recentCommit = false;
    } else {
        recentCommit = true;
    }
    if (temp != NULL) {
        for (const auto & entry : fs::directory_iterator(fs::current_path())) {
            if (string(fs::current_path())+"/.minigit" != entry.path() && string(fs::current_path())+"/.ipynb_checkpoints" != entry.path()) {
                fs::remove_all("FilesGoHere");
                fs::create_directory("FilesGoHere");
            }
        }
        FileNode* tempFile = temp->fileHead;
        while(tempFile != NULL) {
            string line;
            ifstream readFile(".minigit/"+tempFile->name+"_"+to_string(tempFile->version));
            ofstream writeFile("FilesGoHere/"+tempFile->name);
            cout << tempFile->name << endl;
            //Leave me here for now.
            if (readFile && writeFile) {
                while(getline(readFile,line)){
                    writeFile << line << "\n";
                }
            } else {
                cout << "error in opening files" << endl;
            }
            tempFile = tempFile->next;
        }
    } else {
        cout << "This commit does not exist." << endl;
    }
}
