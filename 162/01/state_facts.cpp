#include "state_facts.h"

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

void start(ifstream &file, int state_size) {
    state *s = new state[state_size];
    string text; int i = 0, pos = 0;
    while (i < state_size) {
        pos = file.tellg();
        getline(file,text);
        int space_num = 0;
        for (int m = 0; m < text.length(); m++) {
            char cur_char = text[m];
            if (cur_char == ' ') space_num++;
        }
        if (space_num == 2) {
            file.seekg(pos);
            file >> s[i].name >> s[i].population >> s[i].counties;
            cout << s[i].name << " " << s[i].population << " "<< s[i].counties << endl;
            s[i].c = new county[s[i].counties];
            create_counties(i, s, file, s[i].c, s[i].counties, pos);
        }
        i++;
        getline(file,text);
    }            
}
    //states' pop is in ascending order
    //for (int i = 0; i < state_size; i++)
      //  t[i].pop = i;
    
    //sort pop in descending order
    //for (int i = 0; i < state_size; i++)
      //  for (int j = 0; j < state_size - 1 - i; j++)
        //    if (t[j].pop <t[j+1].pop) {
          //      temp = t[j];
            //}

void create_counties(int i, state * s, ifstream &file, county * c, int county_size, int &pos) {
    string text; int j = 0;
    while (j < county_size) { 
        pos = file.tellg();
        getline(file, text);
        getline(file, text);
        int space_num = 0;
        for (int m = 0; m < text.length(); m++) {
            char cur_char = text[m];
            if (cur_char == ' ') space_num++;
        }
    
        if (space_num > 2) {
            file.seekg(pos);
            file >> s[i].c[j].name >> 
                    s[i].c[j].population >> 
                    s[i].c[j].avg_income >> 
                    s[i].c[j].avg_house >>
                    s[i].c[j].cities; 
            s[i].c[j].city = new string[s[i].c[j].cities];
            cout << s[i].c[j].name << " " <<
                    s[i].c[j].population << " " <<
                    s[i].c[j].avg_income << " " <<
                    s[i].c[j].avg_house << " " <<
                    s[i].c[j].cities << " ";
            for (int k = 0; k < s[i].c[j].cities; k++) {
                file >> s[i].c[j].city[k];
                cout << s[i].c[j].city[k] << " ";
            }
            cout << endl;
            j++;
        }
        else {
            return;
        }
    }
}
/*
state * create_states(int) {
    
}

void get_state_data(state *) {
    
}

void get_county_data(county *) {
    
}

void delete_info(state *) {
    
}

void largest_population(int) {

}

void sorted_name(int) {
    
}

void sorted_population(int) {
    
}
*/