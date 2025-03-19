/*
#############################################################################
# 
 *
 * orienteeringmap.hh (Header file for the OrienteeringMap class)
 * Declares the OrienteeringMap class, which manages the map data, points, routes, and other related operations
 *
\
 *
 *
 *
 * */


#ifndef ORIENTEERINGMAP_HH
#define ORIENTEERINGMAP_HH

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <point.hh>
#include <route.hh>

class OrienteeringMap
{
public:
    // Constructor and destructor
    OrienteeringMap();
    ~OrienteeringMap();

    // Sets the width and height for the map.
    void set_map_size(int width, int height);

    // Adds a new point in the map, with the given name, position (x and y
    // coordinates), height and marker.
    void add_point(std::string name, int x, int y, int height, char marker);

    // Connects two existing points such that the point 'to' will be
    // immediately after the point 'from' in the route 'route_name'.
    // The given route can be either a new or an existing one,
    // if it already exists, the connection between points will be
    // updated in the aforementioned way.
    // Returns true, if connection was successful, i.e. if both the points
    // exist, otherwise returns false.
    bool connect_route(std::string from,
                       std::string to,
                       std::string route_name);

    // Prints the map.
    void print_map() const;

    // Prints all routes' names, ordered alphabetically.
    void print_routes() const;

    // Prints all points' names and their markers on the map.
    void print_points() const;

    // Prints points belonging to the given route in the order they are
    // in the route.
    void print_route(const std::string& name) const;

    // Prints the given route's combined length,
    // the length is counted as a sum of the distances of adjacent points.
    void route_length(const std::string& name) const;

    // Finds and prints the highest rise in any of the routes after the given
    // point.
    void greatest_rise(const std::string& point_name) const;

private:
    // Add here attributes and private methods.
    // At least you need a datastructure for points or routes or for both,
    // containing Point* or Route* objects (use smart pointers).
    // Good candidates for such structures are STL maps or vectors.
    int width_;
    int height_;
    std::map<std::string, std::shared_ptr<Point>> points_; // Use Point from point.hh
    std::map<std::string, std::vector<std::string>> routes_; // Or std::map<std::string, std::shared_ptr<Route>> if using Route class
};

#endif // ORIENTEERINGMAP_HH
