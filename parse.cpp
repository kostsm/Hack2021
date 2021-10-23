#include <bits/stdc++.h>
#include "classes.h"
using namespace std;

void static_input(string file, void (*parse)(string row))
{	
	ifstream in_file(file);
	string str;
	getline(in_file, str);
	while(getline(in_file, str))	
		if ((int)str.size() != 0)
			parse(str);
	in_file.close();	
}

void Stand::parse(string row)
{
	if (row[0] == 'A')
		return;
	string buf = "";
	int num = 0;
	for (int i = 0; i < (int)row.size(); i++)
	{
		if(row[i] == ',')
		{
			if (num == 0)
				Aircraft_Stand = atoi(buf.c_str());
			else if (num == 1)
				JetBridge_on_Arrival = buf[0];
			else if (num == 2)
				JetBridge_on_Departure = buf[0];
			else if (num < 8)				
				Time_To_Terminal[num - 2] = atoi(buf.c_str());
			else if (num == 8)
				Terminal = atoi(buf.c_str());
			buf = "";	
			num++;
		}
		else
		{
			buf += row[i];
		}
	}
	Taxiing_Time = atoi(buf.c_str());
}
int T = 0;
void Plane::parse(string row)
{
	if (row[0] == 'f')
		return;
	id = T++;
	string buf = "";
	int num = -1;
	for (int i = 0; i < (int)row.size(); i++)
	{
		if (row[i] == ',')
		{
			if (num == 0)
				flight_AD = buf[0];
			else if (num == 1)
			{
				flight_datatime.parse(buf);										 
			}
			else if (num == 2)
				flight_AL_Synchron_code = buf;
			else if (num == 3)
				flight_number = atoi(buf.c_str());
			else if (num == 4)
				flight_ID = buf[0];
			else if (num == 5)
				flight_terminal = atoi(buf.c_str());
			else if (num == 6)
				flight_AP = buf;
			else if (num == 7)
				flight_AC_Synchron_code = buf;
			else if (num == 8)
				flight_AC_PAX_capacity_total = atoi(buf.c_str());
			else if (num == 9)
				flight_PAX = atoi(buf.c_str());

			buf = "";
			num++;
		}
		else
			buf += row[i];
	}

	if (flight_AC_PAX_capacity_total <= Aircraft_Classes::regional)
	{
		plane_type.name = "regional";
		plane_type.JetBridge_Handling_Time = Handling_Time::regional_jet;
		plane_type.Away_Handling_Time = Handling_Time::regional_away;
	}
	else if (flight_AC_PAX_capacity_total <= Aircraft_Classes::narrow)
	{
		plane_type.name = "narrow";
		plane_type.JetBridge_Handling_Time = Handling_Time::narrow_jet;
		plane_type.Away_Handling_Time = Handling_Time::narrow_away;
	}
	else if (flight_AC_PAX_capacity_total <= Aircraft_Classes::wide)
	{
		plane_type.name = "wide";
		plane_type.JetBridge_Handling_Time = Handling_Time::wide_jet;
		plane_type.Away_Handling_Time = Handling_Time::wide_away;
	}
}

void Datatime::parse(string row)
{
	string buf = "";
	for (int i = 0; i < (int)row.size(); i++)
	{
		if (i == 2)
		{
			day = atoi(buf.c_str());
			buf = "";
		}
		else if (i == 5)
		{
			month = atoi(buf.c_str());
			buf = "";
		}
		else if (i == 10)
		{
			year = atoi(buf.c_str());
			buf = "";
		}
		else if (row[i] == ':')
		{
			hour = atoi(buf.c_str());
			buf = "";
		}
		else 
			buf = buf + row[i];
	}
	minute = atoi(buf.c_str());
	minute += hour*60;
	second = 0;
}


void Handling_Time::parse(string row)
{
	if(row[0] == 'A')
		return;
	int id = 0;
	string name = "";
	string jet = "";
	string away = "";
	for (int i = 0; i < (int)row.size(); i++)
	{
		if (row[i] == ',')
			id ++;
		else if (id == 0)
		{
			name += row[i];	
		}
		else if(id == 1)
		{
			jet += row[i];
		}
		else
			away += row[i];
	}	
	if(name == "Regional")
	{
		regional_jet = atoi(jet.c_str());
		regional_away = atoi(away.c_str());
	}
	else if(name == "Narrow_Body")
	{
		narrow_jet = atoi(jet.c_str());
		narrow_away = atoi(away.c_str());
	}
	else
	{
		wide_jet = atoi(jet.c_str());
		wide_away = atoi(away.c_str());
	}
}

void Taxes::parse(string row)
{
	if(row[0] == 'N')
		return;
	bool id = 0;
	string name = "";
	string buf = "";
	for (int i = 0; i < (int)row.size(); i++)
	{
		if (row[i] == ',')
			id = 1;
		else if (id == 0)
		{
			name += row[i];	
		}
		else
		{
			buf += row[i];
		}
	}	
	if(name == "Bus_Cost_per_Minute") Bus_Cost_per_Minute = atoi(buf.c_str());
	else if(name == "Away_Aircraft_Stand_Cost_per_Minute") 
		Away_Aircraft_Stand_Cost_per_Minute = atoi(buf.c_str());
	else if(name == "JetBridge_Aircraft_Stand_Cost_per_Minute")
		JetBridge_Aircraft_Stand_Cost_per_Minute = atoi(buf.c_str());
	else Aircraft_Taxiing_Cost_per_Minute = atoi(buf.c_str());
}

int Aircraft_Classes::regional;
int Aircraft_Classes::narrow;
int Aircraft_Classes::wide;
int Handling_Time::regional_jet;
int Handling_Time::regional_away;
int Handling_Time::narrow_jet;
int Handling_Time::narrow_away;
int Handling_Time::wide_jet;
int Handling_Time::wide_away;
int Taxes::Bus_Cost_per_Minute;
int Taxes::Away_Aircraft_Stand_Cost_per_Minute;
int Taxes::JetBridge_Aircraft_Stand_Cost_per_Minute;
int Taxes::Aircraft_Taxiing_Cost_per_Minute;

void Aircraft_Classes::parse(string row)
{
	if (row[0] == 'A')
		return;
	bool id = 0;
	string name = "";
	string buf = "";
	for (int i = 0; i < (int)row.size(); i++)
	{
		if (row[i] == ',')
			id = 1;
		else if (id == 0)
		{
			name += row[i];	
		}
		else
		{
			buf += row[i];
		}
	}		
	if(name == "Regional") regional = atoi(buf.c_str());
	else if(name == "Narrow_Body") narrow = atoi(buf.c_str());
	else wide = atoi(buf.c_str());
}

bool operator<(Plane& p1, Plane& p2)
{	
/*	long long num1 = p1.flight_datatime.year*366*24*3600ll + p1.flight_datatime.month*31*24*3600ll + p1.flight_datatime.day*24*3600ll
		+ p1.flight_datatime.hour*3600ll + p1.flight_datatime.minute*60ll + p1.flight_datatime.second;
	long long num2 = p2.flight_datatime.year*366*24*3600ll + p2.flight_datatime.month*31*24*3600ll + p2.flight_datatime.day*24*3600ll
		+ p2.flight_datatime.hour*3600ll + p2.flight_datatime.minute*60ll + p2.flight_datatime.second;
	return num1 < num2;
	
	if(p1.flight_datatime.year < p2.flight_datatime.year) return true;
	if(p1.flight_datatime.year > p2.flight_datatime.year) return 0;
	if(p1.flight_datatime.month < p2.flight_datatime.month) return true;
	if(p1.flight_datatime.month > p2.flight_datatime.month) return 0;
	if(p1.flight_datatime.day < p2.flight_datatime.day) return true;
	if(p1.flight_datatime.day > p2.flight_datatime.day) return 0;
	if(p1.flight_datatime.hour < p2.flight_datatime.hour) return true;
	if(p1.flight_datatime.hour > p2.flight_datatime.hour) return 0;
	if(p1.flight_datatime.minute < p2.flight_datatime.minute) return true;
	if(p1.flight_datatime.minute > p2.flight_datatime.minute) return 0;*/
	return p1.flight_datatime.minute < p2.flight_datatime.minute;
}

void output(string file, vector <int> position)
{
  ifstream in_file(file);
  ofstream out_file("data_set/answer.csv");
  string str;
  getline(in_file, str);
  out_file << str << endl;
  int num = 0;
  while(getline(in_file, str))
  {
    if ((int)str.size() != 0)
    {
        string out = "";
        for (int i = 0; i < (int)str.size(); i++)          
            out += str[i];
        out_file << out  << position[num] << endl;
        num++;    
    }
  }
}