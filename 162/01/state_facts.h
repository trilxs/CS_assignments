#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <limits>

using namespace std;

struct county {
    string name;
    string *city;
    int cities;
    int population;
    float avg_income;
    float avg_house;
};

struct state {
    string name;
    struct county *c;
    int counties;
    int population;
};
/*
void delete_info(state *);
void sorted_name(int);
*/
bool is_int(int, char**);
int get_num(int, char**, int, const char*);
void start_program(ifstream&, int);
int main(int, char**);
state * create_states(int);
county * create_counties(state *, int);
void get_state_data (state *, ifstream&, int);
void get_county_data(int, struct state*, ifstream&, struct county*, int, int&);
void largest_population(state *, int);
void sorted_population(state*, int);
void sorted_name(state*, int);
void income(state*, int);
void house(state*, int);