#ifndef JOURNEY_H
#define JOURNEY_H

// libraries used by class
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#define DEGLATTOMILE 69.048 // number of miles to a degree of latitude - not this simple

#define EQEARTHRADMILE 3958.8 // equatorial radius of earth in miles - earth is oblate, so not entirely accurate
#define SECSPERHOUR 3600 // number of seconds in an hour

#define MIN(a, b) ((a < b) ? a : b) // find minimum of two values
#define DEGTORAD 57.29577951 // conversion factor for Degrees to Radians = 180 / pi

class journey
{
    public:
        journey(); // constructor - no copy constructor so can't be passed to function by value

        bool inputLatLonSpped(std::vector<float>);
        void calculateJourney(void);
        void outputJourney(void);
        void plotJourney(void);

    private:
        void calcDists(void);
        void calcTimes(void);
        void insertLat(float);   // insert a latitude
        void insertLon(float);   // insert a longitude
        void insertSpeed(float); // insert a speed
        std::vector<float> _lats;
        std::vector<float> _lons;
        std::vector<float> _speeds;
        std::vector<float> _dists;
        std::vector<float> _times;
};

#endif // JOURNEY_H
