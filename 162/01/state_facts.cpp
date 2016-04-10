/******************************************************
** Program: state_facts.cpp
** Author: Tam Lu
** Date: 04/07/2016
** Description: Program that finds the information of a text file and orders it
** alphabetically, from largest to smallest population, etc.
** Input: Command line arguments (state # and file name)
** Output: Repeat program or exit program
******************************************************/ 

#include "state_facts.h"

bool is_valid_arguments(int argc, char* argv[]) {
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

/*********************************************************************
** Function: get_num
** Description: gets the number of states to see if it's a good number
** Parameters: argc, argv, i, compare
** Pre-Conditions: the user has entered something in the command line
** Post-Conditions: return num if it's a good number
*********************************************************************/ 
int get_num(int argc, char* argv[], int i, const char compare[]) {
	int num;
	if (strcmp(argv[i], compare) == 0) {
		if (is_valid_arguments((i+1), argv)) 
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

/*********************************************************************
** Function: create_states
** Description: create states array
** Parameters: state_size
** Pre-Conditions: user specified amount of states
** Post-Conditions: return created dynamic array
*********************************************************************/ 
state * create_states(int state_size) {
    state * state_array = new state[state_size];
    return state_array;
}

/*********************************************************************
** Function: create_counties
** Description: create states array
** Parameters: s, i
** Pre-Conditions: text file specifies amount of counties for state
** Post-Conditions: return created dynamic array
*********************************************************************/ 
county * create_counties(state *s, int i) {
    county * county_array = new county[s[i].counties];
    return county_array;
}

/*********************************************************************
** Function: start_program
** Description: starts the actual program
** Parameters: file, state_size
** Pre-Conditions: the user has inputted a state size and an opened file
** Post-Conditions: play again or exit
*********************************************************************/ 
void start_program(ifstream &file, int state_size) {
    state *s = create_states(state_size);
    get_state_data(s, file, state_size);
    file.close();
    largest_population(s, state_size);
    sorted_population(s, state_size);
    sorted_name(s, state_size);
    house (s, state_size);
    income(s, state_size);
    delete_info(s, state_size);
}

/*********************************************************************
** Function: income
** Description: finds the counties with user's minimum income 
** Parameters: s, state_size
** Pre-Conditions: the user has inputted a state size and an array is created
** Post-Conditions: counties with user's minimum income is printed
*********************************************************************/ 
void income(state * s, int state_size) {
    int income_thres;
    cout << "Enter in your minimum income for counties: ";
    cin >> income_thres;
    cout << "Counties with an average income above/equal to " << income_thres << ":\n";
    for (int i = 0; i < state_size; i++) {
        for (int j = 0; j < s[i].counties; j++) {
            if (s[i].c[j].avg_income >= income_thres) {
                cout << "\t" <<s[i].c[j].name << endl;
            }
        }
    }        
}

/*********************************************************************
** Function: house
** Description: find the average household cost of all counties
** Parameters: s, state_size
** Pre-Conditions: the user has inputted a state size and an array is created
** Post-Conditions: prints out household cost for all counties
*********************************************************************/ 
void house(state * s, int state_size) {
    cout << "Average household cost for all counties in each state:\n";
    for (int i = 0; i < state_size; i++) {
        int house = 0;
        cout << "\t" << s[i].name << ": ";
        for (int j = 0; j < s[i].counties; j++) {    
            house += s[i].c[j].avg_house;
        }
        house = (house)/(s[i].counties);
        cout << house << endl;
   }
}

/*********************************************************************
** Function: get_state_data
** Description: creates the state array
** Parameters: s, file, state_size
** Pre-Conditions: the user has inputted a state size and an array is created
** Post-Conditions: a state array is created
*********************************************************************/ 
void get_state_data(state * s, ifstream &file, int state_size) {
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
            s[i].c = create_counties(s, i);
            get_county_data(i, s, file, s[i].c, s[i].counties, pos);
        }
        i++; getline(file,text);
    }                
}

/*********************************************************************
** Function: get_county_data
** Description: creates the county array
** Parameters: s, file, c, county_size, pos
** Pre-Conditions: the user has inputted a state size and an array is created
** Post-Conditions: a county array is created
*********************************************************************/ 
void get_county_data(int i, state * s, ifstream &file, county * c, int county_size, int &pos) {
    string text; int j = 0;
    while (j < county_size) { 
        pos = file.tellg();
        getline(file, text); getline(file, text);
        int space_num = 0;
        for (int m = 0; m < text.length(); m++) {
            char cur_char = text[m];
            if (cur_char == ' ') space_num++;
        }
        if (space_num > 2) {
            file.seekg(pos);
            
            file >> s[i].c[j].name >> s[i].c[j].population >> s[i].c[j].avg_income >> s[i].c[j].avg_house >> s[i].c[j].cities; 
            cout << s[i].c[j].name << " " << s[i].c[j].population << " " << s[i].c[j].avg_income << " " <<s[i].c[j].avg_house << s[i].c[j].cities << endl; 
            s[i].c[j].city = new string[s[i].c[j].cities];
            for (int k = 0; k < s[i].c[j].cities; k++) {
                file >> s[i].c[j].city[k];
                cout << s[i].c[j].city[k] << endl;
            }
            j++;
        }
        else return;
    }
}

/*********************************************************************
** Function: largest_population
** Description: sort array from largest population to smallest
** Parameters: s, state_size
** Pre-Conditions: state array is filled 
** Post-Conditions: none
*********************************************************************/ 
void largest_population(state * s, int state_size) {
    cout << "Largest population: " << endl;
    int s_num, c_num; int s_pos = 0, sc_pos = 0, c_pos = 0; 
    s_num = s[0].population;
    c_num = s[0].c[0].population;
    for (int i = 0; i < state_size; i++) {
        if (s[i].population > s_num) {
            s_num = s[i].population;
            s_pos = i;
        }
        for (int j = 0; j < s[i].counties; j++) {
            if (s[i].c[j].population > c_num) {
                c_num = s[i].c[j].population;
                c_pos = j; sc_pos = i;
            }
        }
    }
    cout << "\t" <<s[s_pos].name << " has the largest state population.\n";
    cout << "\t" <<s[sc_pos].c[c_pos].name << " has the largest county population.\n";
}

/*********************************************************************
** Function: sorted_population
** Description: sort array from largest population to smallest (county and state)
** Parameters: s, state_size
** Pre-Conditions: state array is filled
** Post-Conditions: none
*********************************************************************/ 
void sorted_population(state * s, int state_size) {
    struct state s_temp; struct county c_temp;
    cout << "State and county population ordered from highest to lowest: \n";
    for (int i = 0; i < state_size; i++) { //sort states
        for (int j = i+1; j < state_size; j++) {
            if (s[j].population > s[i].population) {
                s_temp = s[i];
                s[i] = s[j];
                s[j] = s_temp;
            }
        }
        cout <<"\t" << s[i].name << endl;
        if (s[i].counties > 1) {
            for (int j = 0; j < s[i].counties; j++) {
                for (int k = j+1; k < s[i].counties; k++) {
                    if (s[i].c[k].population > s[i].c[j].population) {
                        c_temp = s[i].c[j];
                        s[i].c[j] = s[i].c[k];
                        s[i].c[k] = c_temp;
                    }
                }
                cout << "\t" <<s[i].c[j].name << endl;
            }
        }
        else {cout << "\t" <<s[i].c[0].name << endl;}
    }
}

/*********************************************************************
** Function: sorted_name
** Description: sort by name in alphabetical order (state and their counties)
** Parameters: s, state_size
** Pre-Conditions: state array is filled
** Post-Conditions: none
*********************************************************************/ 
void sorted_name(state * s, int state_size) {
    struct state s_temp; struct county c_temp;
    cout << "State and county name ordered in alphabetically: \n";
    for (int i = 0; i < state_size; i++) { //sort states
        for (int j = i+1; j < state_size; j++) {
            if (s[j].name[0] < s[i].name[0]) {
                s_temp = s[i];
                s[i] = s[j];
                s[j] = s_temp;
            }
        }
        cout << "\t" << s[i].name << endl;
        if (s[i].counties > 1) {
            for (int j = 0; j < s[i].counties; j++) {
                for (int k = j+1; k < s[i].counties; k++) {
                    if (s[i].c[k].name[0] < s[i].c[j].name[0]) {
                        c_temp = s[i].c[j];
                        s[i].c[j] = s[i].c[k];
                        s[i].c[k] = c_temp;
                    }
                }
                cout << "\t" <<s[i].c[j].name << endl;
            }
        }
        else {cout << "\t" <<s[i].c[0].name << endl;}
    }
}

/*********************************************************************
** Function: delete_info
** Description: deletes dynamic array to avoid leak
** Parameters: s, state_size
** Pre-Conditions: state array was created
** Post-Conditions: goes to again() to start over/exit
*********************************************************************/ 
void delete_info(state * s, int state_size) {
   for ( int i = 0; i < state_size; i++ ) {
       delete [] s[i].c;
   }
   delete [] s;
   again();
}

/*********************************************************************
** Function: again
** Description: if user wants to find different file, then find state # and file name, else exit
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 
void again() {
   int in; ifstream f;
   cout << "\nWould you like to find information for a different file? (1/0) ";
   cin >> in;
   if (in == 1) {
       int state_size; char * file_name = new char[256];
       cout << "What is the file name? ";
       cin.ignore();
       cin.getline(file_name, 256);
       cout << "How many states? ";
       cin >> state_size;
       f.open(file_name);
       if (f.is_open()) {
           start_program(f, state_size);
       }
       else {
           cout << "Error opening file." << endl;
       }
   }
}