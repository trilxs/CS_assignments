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
state * create_states(int);
void get_state_data(state *);
void get_county_data(county *);
void delete_info(state *);
void largest_population(int);
void sorted_name(int);
void sorted_population(int);
*/
bool is_int(int, char**);
int get_num(int, char**, int, const char*);
void start(ifstream&, int);
int main(int, char**);
void create_counties(int, struct state*, ifstream&, struct county*, int, int&);