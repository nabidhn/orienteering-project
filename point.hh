// point.hh

/* Orienteering
 *
 *

 * point.hh (Header file for the Point class)
 * Declares the Point class, representing a location on the map with coordinates, height, and marker.
 *
 * */

#ifndef POINT_HH
#define POINT_HH

#include <string>
#include <set>


// Structure representing a point on the orienteering map.
// Stores the point's name, coordinates (x, y), height, marker character, and the routes it belongs to.
struct Point {
    std::string name;
    int x;
    int y;
    int height;
    char marker;
    std::set<std::string> routes;

    // Constructor for the Point structure.
    // initializes the point with the given name, coordinates, height, and marker.
    Point(std::string n, int px, int py, int h, char m) :
        name(n), x(px), y(py), height(h), marker(m) {}
};

#endif // POINT_HH
