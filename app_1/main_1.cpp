#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
using namespace std;

/*
 * Purpose; displays a menu with options
 */

// oOoOoOoOoOo READ MEEEEEEE, this was done really late and I have no clue what half of this does, so REVIEEEEW MEEEEE
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. init " << endl;
    cout << " 2. add " << endl;
    cout << " 3. rm " << endl;
    cout << " 4. commit " << endl;
    cout << " 5. checkout" << endl;
    cout << " 6. search" << endl;
    cout << " 7. quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
int main(int argc, char* argv[]) {
    MiniGit minigit;
    while(true) {
        displayMenu();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                minigit.init(5);
                break;
            }case 2: {
                cout << "File you want to add: ";
                string fileName;
                cin >> fileName;
                minigit.add(fileName);
                break;
            }case 3:{
                cout << "File you want to remove: ";
                string fileName;
                cin >> fileName;
                minigit.rm(fileName);
                break;
            }case 4:{
                string commitMessage;
                cout << "Commit message: ";
                ws(cin);
                getline(cin, commitMessage);
                stringstream ss(commitMessage);
                vector<string> messages;
                string word = "";
                for (int i = 0; getline(ss, word, ' '); i++) {
                    messages.push_back(word);
                }
                cout << minigit.commit(messages, commitMessage) << endl;
                break;
            }case 5:{
                cout << "<:::> You are attempting to overwrite all files! YOU HAVE BEEN WARNED!!! <:::>" << endl;
                cout << "Enter a commit number: ";
                string commitNumber;
                cin >> commitNumber;
                minigit.checkout(commitNumber);
                break;
            }case 6:{
                cout << "Enter key: ";
                string key;
                cin >> key;
                minigit.search(key);
                break;
            }case 7:{
                cout << "Goodbye!" << endl;
                return 0;
                break;
            }default:
                break;
        }
    }
}