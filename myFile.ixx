export module myFile;

//#include <string>
import <string>;
/*informacje dzielone w aplikacji*/
export class AirportStats
{
public:
	int runway;
	int maxRunway;
	int limitRunway;
	int landing;
	int maxLanding;
	int limitLanding;
	int hangar;
	int maxHangar;
	int limitHangar;
};