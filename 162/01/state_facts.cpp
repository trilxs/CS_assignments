#include "header.h"

bool is_int(int argc, char* argv[]) {
	bool numOrNot;
	for (int i = 0; i < strlen(argv[argc]); i++) {
		if (isdigit(argv[argc][i])) {
			numOrNot = true;
			return numOrNot;
		}
		else {
			numOrNot = false;
			return numOrNot;
		}
	}
}

int get_num(int argc, char* argv[], int i, const char compare[]) {
	int num;
	if (strcmp(argv[i], compare) == 0) {
		if (is_int((i+1), argv)) 
			num = atoi(argv[i + 1]);
		else {
			cout << "Error: Invalid arguments.\nFormat: -s # -f \"filename.txt\"\n";
			exit(0);
		}
	}
	else {
		cout << "Error: Invalid arguments.\nFormat: -s # -f \"filename.txt\"\n";
		exit(0);
	}
	return num;
}

void start(ifstream * file, int state_size) {
    
}