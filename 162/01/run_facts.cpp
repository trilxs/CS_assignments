#include "state_facts.h"

int main(int argc, char * argv[]) {
    const char * state_compare = "-s"; const char * file_compare = "-f";
    int state_size; char * file_name =  new char[256];
    ifstream f;
    if (argc == 5) {
        state_size = get_num(argc, argv, 1, state_compare);
       // if (argv[3] == "-f") {
            file_name = argv[4];
            f.open (file_name); //TEMPORARY
            if (f.is_open()) {
                start(f, state_size);
            }
            else {
                cout << "Failed to open file." << endl;
            }
      //  }
      //  else {
      //      cout << "Error: Invalid arguments.\nFormat: -s # -f \"filename.txt\"\n";
      //  }
    }
    else {
        cout << "Error: Invalid amount of arguments.\n";
    }
	return 0;
}