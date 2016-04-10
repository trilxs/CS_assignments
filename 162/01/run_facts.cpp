/******************************************************
** Program: state_facts.cpp
** Author: Tam Lu
** Date: 04/07/2016
** Description: start function to check command lines
** Input: command line argments
** Output: start program or exit
******************************************************/ 

#include "state_facts.h"

/*********************************************************************
** Function: main
** Description: reads command arguments 
** Parameters: argc, argv
** Pre-Conditions: user entered command line
** Post-Conditions: start game or exit because of error
*********************************************************************/ 
int main(int argc, char * argv[]) {
    const char * state_compare = "-s"; const char * file_compare = "-f";
    int state_size; char * file_name =  new char[256];
    ifstream f;
    if (argc == 5) {
        state_size = get_num(argc, argv, 1, state_compare);
       if (strcmp(argv[3], file_compare) == 0) {
            file_name = argv[4];
            f.open (file_name); //TEMPORARY
            if (f.is_open()) {
                start_program(f, state_size);
            }
            else {
                cout << "Failed to open file." << endl;
            }
      }
      else {
            cout << "Error: Invalid arguments.\nFormat: -s # -f \"filename.txt\"\n";
     }
    }
    else {
        cout << "Error: Invalid amount of arguments.\n";
    }
	return 0;
}