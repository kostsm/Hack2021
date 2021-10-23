#include "classes.h"
using namespace std;

vector<int> solve(vector<Stand>& Stands, vector<Plane>& Planes)
{
	Plane tmp;
	tmp.flight_datatime.year = 0;
	tmp.flight_datatime.month = 0;
	tmp.flight_datatime.day = 0;
	tmp.flight_datatime.hour = 0;
	tmp.flight_datatime.minute = -1000000000;
	tmp.flight_datatime.second = 0;
	tmp.plane_type.name = "regional";
	vector<Plane> was(Stands.size() + 2, tmp);
	vector<int> ans(Planes.size() + 1);
	for (int i = 0; i < (int)Planes.size(); i++)
	{
		Plane plane = Planes[i];
		//cout << plane.plane_type.name << endl;
		int mn = 1000000000;
		int poz = 0;
		int bestm;
		for (int j = 0; j < (int)Stands.size(); j++)
		{
			Stand stand = Stands[j];
			int minute = stand.Taxiing_Time;
			if (stand.Terminal == 0 && plane.plane_type.name == "regional") minute += Handling_Time::regional_away;
			if (stand.Terminal != 0 && plane.plane_type.name == "regional") minute += Handling_Time::regional_jet;
			if (stand.Terminal == 0 && plane.plane_type.name == "narrow") minute += Handling_Time::narrow_away;
			if (stand.Terminal != 0 && plane.plane_type.name == "narrow") minute += Handling_Time::narrow_jet;
			if (stand.Terminal == 0 && plane.plane_type.name == "wide") minute += Handling_Time::wide_away;
			if (stand.Terminal != 0 && plane.plane_type.name == "wide") minute += Handling_Time::wide_jet;
			if (plane.flight_AD == 'D') plane.flight_datatime.minute -= minute;
			else plane.flight_datatime.minute += stand.Taxiing_Time;
			if (was[stand.Aircraft_Stand] < plane && cost(plane, stand) < mn
				&& !(plane.plane_type.name == "wide" && stand.Terminal != 0 && stand.Aircraft_Stand != 1 &&
					was[stand.Aircraft_Stand - 1].plane_type.name == "wide" &&
					Stands[stand.Aircraft_Stand - 2].Terminal != 0/* &&
					plane < was[stand.Aircraft_Stand - 1]*/) &&
				!(plane.plane_type.name == "wide" && stand.Terminal != 0 &&
					was[stand.Aircraft_Stand + 1].plane_type.name == "wide" &&
					Stands[stand.Aircraft_Stand].Terminal != 0/* &&
					plane < was[stand.Aircraft_Stand + 1]*/))
			{
				bestm = minute;
				mn = cost(plane, stand);
				poz = stand.Aircraft_Stand;
			}

			if (plane.flight_AD == 'D') plane.flight_datatime.minute += minute;
			else plane.flight_datatime.minute -= stand.Taxiing_Time;


		}

		plane.flight_datatime.minute += 47;
		if (plane.flight_AD == 'A') plane.flight_datatime.minute += bestm;
		else plane.flight_datatime.minute -= Stands[poz - 1].Taxiing_Time;
		cerr << plane.flight_datatime.minute << endl;
		was[poz] = plane;
		ans[plane.id] = poz;
	}
	cerr << '.';
	return ans;
}
