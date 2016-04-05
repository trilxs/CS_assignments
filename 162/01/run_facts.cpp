#include "state_facts.h"

int main(int argc, int * argv[]) {
    const char * state_compare = "-s"; const char * file_compare = "-f";
    int state_pos = 1; int file_pos = 3;
    int state_size; string file_name;
    ifstream f;
    if (argc == 5) {
        state_size = get_num(argc, argv, state_pos, state_num);
        if (argv[file_pos] = "-f") {
            string file_name = argv[file_pos + 1];
            f.open (file_name);
            if (f.is_open()) {
                start(&f, state_size);
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