#include <bits/stdc++.h>
#include "classes.h"
using namespace std;

int cost(Plane plane, Stand stand)
{
	int total_cost = 0;
	total_cost = stand.Taxiing_Time * Taxes::Aircraft_Taxiing_Cost_per_Minute;

	int buses = plane.flight_PAX / 80;
	if (plane.flight_PAX % 80 != 0)
		buses++;

	int bus_cost = Taxes::Bus_Cost_per_Minute * stand.Time_To_Terminal[plane.flight_terminal] * buses;

	if (stand.Terminal != 0)
	{
		if (plane.flight_AD == 'A')
		{
			if (plane.flight_ID == stand.JetBridge_on_Arrival && stand.Terminal == plane.flight_terminal)
			{
				total_cost += plane.plane_type.JetBridge_Handling_Time * Taxes::JetBridge_Aircraft_Stand_Cost_per_Minute;
			}
			else
			{
				total_cost += plane.plane_type.Away_Handling_Time * Taxes::JetBridge_Aircraft_Stand_Cost_per_Minute;
				total_cost += bus_cost;
			}
		}
		else
		{
			if (plane.flight_ID == stand.JetBridge_on_Departure && stand.Terminal == plane.flight_terminal)
			{
				total_cost += plane.plane_type.JetBridge_Handling_Time * Taxes::JetBridge_Aircraft_Stand_Cost_per_Minute;
			}
			else
			{
				total_cost += plane.plane_type.Away_Handling_Time * Taxes::JetBridge_Aircraft_Stand_Cost_per_Minute;
				total_cost += bus_cost;
			}
		}
	}
	else
	{
		total_cost += plane.plane_type.Away_Handling_Time * Taxes::Aircraft_Taxiing_Cost_per_Minute;
		total_cost += bus_cost;
	}
	return total_cost;
}