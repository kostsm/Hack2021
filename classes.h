#ifndef CLASSES_H
#define CLASSES_H
#include <bits/stdc++.h>
using namespace std;

template<class T>
void input(string file, vector<T>& data)
{
	ifstream in_file(file);
	int sz = 0;
	string str;
	getline(in_file, str);
	while(getline(in_file, str))
	{
//		cout << (int)str.size() << endl;
		if ((int)str.size() == 0)
			continue;
		data.push_back(T());
		data[sz++].parse(str);
	}	
	in_file.close();	
}

void static_input(string file, void (*parse)(string row));

struct Aircraft_Classes
{	
	static int regional;
	static int narrow;
	static int wide;

	static void parse(string row);
};

struct Handling_Time
{
	static int regional_jet;
	static int regional_away;
	static int narrow_jet;
	static int narrow_away;
	static int wide_jet;
	static int wide_away;
	                                                          
	static void parse(string row);
};

struct Taxes
{
	static int Bus_Cost_per_Minute;
	static int Away_Aircraft_Stand_Cost_per_Minute;
	static int JetBridge_Aircraft_Stand_Cost_per_Minute;
	static int Aircraft_Taxiing_Cost_per_Minute;

	static void parse(string row);
};

struct Plane_Type
{
	string name;
	int JetBridge_Handling_Time;
	int Away_Handling_Time;
};

struct Datatime
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	void parse(string row);
};

struct Plane
{
	int id;
	char flight_AD;
	Datatime flight_datatime;
	Datatime spawn_datatime;
	string flight_AL_Synchron_code;
	int flight_number;
	char flight_ID;
	int flight_terminal;
	string flight_AP;
	string flight_AC_Synchron_code;
	int flight_AC_PAX_capacity_total;
	int flight_PAX;
	int Aircraft_Stand;
	Plane_Type plane_type;
	
	void parse(string row);
};
bool operator<(Plane& p1, Plane& p2);

struct Stand
{
	int Aircraft_Stand;
	char JetBridge_on_Arrival;
	char JetBridge_on_Departure;
	int Time_To_Terminal[6];
	int Terminal;
	int Taxiing_Time;

	void parse(string row); 
};
int cost(Plane plane, Stand stand);
vector<int> solve(vector<Stand>& Stands, vector<Plane>& Planes);
void output(string file, vector <int> position);
#endif