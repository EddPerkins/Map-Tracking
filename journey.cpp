#include "journey.h"
/*  journey.cpp - created 06/09/20 by E. Perkins
 *  journey has only a blank constructor.
 *      It is assumed that data will be added to it in the program
 *  calculates distance between points and time taken between those points
 *  has console output
 *  Only allows for creation of journey - does not allow for updating an existing one
 */

journey::journey(){
    // constructor - blank
}

void journey::insertLat(float lat){
    // insert a latitude
    journey::_lats.push_back(lat);
}

void journey::insertLon(float lon){
    // insert a longitude
    journey::_lons.push_back(lon);
}

void journey::insertSpeed(float speed){
    // insert a speed
    journey::_speeds.push_back(speed);
}

void journey::calcDists(void){
    /* calculate all distances
     *  NOTE will be less accurate as you get closer to the poles
     *  ALSO Assumes perfectly flat land
     */

    unsigned int numLats = _lats.size();
    unsigned int numLons = _lons.size();
    // make sure there are as many longs as lats
    unsigned int numDists = MIN(numLats, numLons);

    // if there is no distances data, then resize vector
    if (_dists.size() == 0){
        float lonDiff, latDiff;
        _dists.resize(numDists);

        _dists.push_back(0);
        _dists[0] = 0; // no previous points means distance from previous points = 0
        for (int i = 1; i < numDists; ++i){
            //convert points to radians
            float cLat = _lats[i] / DEGTORAD;
            float pLat = _lats[i - 1] / DEGTORAD;
            float cLon = _lons[i] / DEGTORAD;
            float pLon = _lons[i - 1] / DEGTORAD;

            lonDiff = cLon - pLon;
            latDiff = cLat - pLat;
            // calculations
            float latArc = (sin(latDiff / 2));
            float lonArc = (sin(lonDiff / 2));

            float arc = ((latArc * latArc) + cos(pLat) * cos(cLat) * (lonArc * lonArc));
            float circ = 2 * atan2 (sqrt(arc), sqrt(1-arc));
            _dists[i] = EQEARTHRADMILE * circ;
        }
    }
}

void journey::calcTimes(void){
    /*  calculates time taken between two points
     *  stores times in seconds in times vector
     */
    unsigned int numDists = _dists.size();
    if (numDists != 0){
        float time = 0; // helper variable

        _times.push_back(time); //no time to move from this point to the next
        for (int i = 1; i < numDists - 1; ++i){
            time = _dists[i] / _speeds[i]; //assumes perfect matching
            time = time * SECSPERHOUR;
            _times.push_back(time);
        }
    }
}

bool journey::inputLatLonSpped(std::vector<float> input){
    // checks size of array being supplied and if not 3, outputs false
    // if vector is 3, will insert lat lon and speed to appropriate places
    bool added = false;
    if (input.size() == 3){
        insertLat(input[0]);
        insertLon(input[1]);
        insertSpeed(input[2]);
        added = true;
    }
    return added;
}

void journey::calculateJourney(void){
    // calculates Distances and Times between each point
    // uses relevant member functions
    journey::calcDists();
    journey::calcTimes();
}

void journey::outputJourney(void){
    // output all lats, lons, speeds, dists and times
    // assumes no missing values
    // could be replaced by overloading << operator to allow cleaner output.
    unsigned short precision = 6;
    std::cout << "Latitude\tLongitude\tspeed(mph)\tdistances(miles)\ttimes(seconds)\n";
    unsigned int latLen = _lats.size();

    for (unsigned int i = 0; i < latLen; ++i){
        std::cout << std::fixed << std::setprecision(precision);
        std::cout << _lats[i] << '\t' << _lons[i] << '\t' << '\t';
        std::cout << std::defaultfloat << _speeds[i] << '\t';
        std::cout << '\t' << _dists[i] << '\t' << '\t' << _times[i] << '\n';
    }
}

void journey::plotJourney(void){
    // plots the journey to a graph style format

    /* this is an interesting problem,
     * it appears that there is no simple library that plots graphs like matplotlib in python.
     * options include:
     *      using openCV - which can work, but will produce tiny images and is a non-standard library
     *      using a matplotlib wrapper - non-standard library that may not be present at other end
     *      creating a python program and use that - not in the spirit of the challenge
     *      creating a bitmap and modifying that - very time consuming to code, but uses only iomanip
     *  Favoured approach would be to use matplotlib-cpp (found here https://github.com/lava/matplotlib-cpp)
     *
     *  Would need to be a part of the journey object, as it will need to access lats and lons
     */
}
