// route.hh

/* Orienteering
 *
 *
 * route.hh (Header file for the Route class)
 * Declares the Route class, representing a path on the map,
 *
 * Program author
 * Name: Nabid Hasan
 * Student number: 152754330
 * UserID: vmn388
 * E-Mail: nabid.hasan@tuni.fi
 *
 *
 *
 * */

#ifndef ROUTE_HH
#define ROUTE_HH

#include <string>
#include <vector>

// Class representing a route in the orienteering map.
// Stores the route's name and the sequence of point names that make up the route
class Route {
public:
    Route(const std::string& name);
    ~Route() = default;

    const std::string& getName() const;
    void addPoint(const std::string& pointName);
    const std::vector<std::string>& getPoints() const;

private:
    std::string name_;
    std::vector<std::string> points_;
};

#endif // ROUTE_HH
