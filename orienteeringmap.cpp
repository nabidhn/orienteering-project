/* Orienteering
 *
 *
 * orienteeringmap.cpp (Source file for the OrienteeringMap class)
 * Implements the methods of the OrienteeringMap class, providing the functionality for managing the map, points, routes, and calculations.
 *

 *
 *
 * */



#include "orienteeringmap.hh"
#include <point.hh>
#include <route.hh>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

// Constructor for the OrienteeringMap class
OrienteeringMap::OrienteeringMap() : width_(0), height_(0) {}

// Destructor for the OrienteeringMap class
OrienteeringMap::~OrienteeringMap() {}

// Sets the dimensions (width and height) of the orienteering map
void OrienteeringMap::set_map_size(int width, int height) {
    width_ = width;
    height_ = height;
}

// Adds a new point in the map
void OrienteeringMap::add_point(std::string name, int x, int y, int height, char marker) {
    if (x >= 1 && x <= width_ && y >= 1 && y <= height_) {
        if (points_.find(name) == points_.end()) {
            points_[name] = std::make_shared<Point>(name, x, y, height, marker); // Corrected
        }
    }
}


// Connects two points in a Route
// Check if both points exiSt.  If route doesn't exist, it creates it
// Ensure points are added to the route in the correct sequence
bool OrienteeringMap::connect_route(std::string from, std::string to, std::string route_name) {
    if (points_.find(from) == points_.end() || points_.find(to) == points_.end()) {
        return false;
    }


    if (routes_.find(route_name) == routes_.end()) {
        routes_[route_name].push_back(from);
    }


    if (routes_[route_name].back() == from) {
        routes_[route_name].push_back(to);
        points_[from]->routes.insert(route_name);
        points_[to]->routes.insert(route_name);
        return true;
    } else {

        std::cerr << "Warning: Attempt to connect " << from << " to " << to
                  << " in route " << route_name << " out of sequence." << std::endl;
        return false;
    }
}

// Prints the orienteering map
void OrienteeringMap::print_map() const {
    std::cout << " ";
    for (int i = 1; i <= width_; ++i) {
        std::cout << std::setw(3) << i;
    }
    std::cout << std::endl;

    for (int y = 1; y <= height_; ++y) {
        std::cout << std::setw(2) << y << "";
        for (int x = 1; x <= width_; ++x) {
            bool point_found = false;
            for (const auto& pair : points_) {
                if (pair.second->x == x && pair.second->y == y) {
                    std::cout << std::setw(3) << pair.second->marker;
                    point_found = true;
                    break;
                }
            }
            if (!point_found) {
                std::cout << std::setw(3) << ".";
            }
        }
        std::cout << std::endl;
    }
}

// Prints the names of all defined routes (Sorted alphabetically)
void OrienteeringMap::print_routes() const {
    std::cout << "Routes:" << std::endl;
    std::vector<std::string> route_names;
    for (const auto& pair : routes_) {
        route_names.push_back(pair.first);
    }
    std::sort(route_names.begin(), route_names.end());

    for (const auto& name : route_names) {
        std::cout << " - " << name << std::endl;
    }
}

// Prints the names and markers of all points
void OrienteeringMap::print_points() const {
    std::cout << "Points:" << std::endl;
    std::vector<std::string> point_names;
    for (const auto& pair : points_) {
        point_names.push_back(pair.first);
    }
    std::sort(point_names.begin(), point_names.end());

    for (const auto& name : point_names) {
        std::cout << " - " << name << " : " << points_.at(name)->marker << std::endl;
    }
}

// Prints the points in a specific route
void OrienteeringMap::print_route(const std::string& name) const {
    if (routes_.find(name) != routes_.end()) {
        const auto& route = routes_.at(name);

        if (route.empty()) {
            return;
        }

        if (route.size() == 1) {
            std::cout << route[0] << std::endl;
            return;
        }

        std::cout << route[0] << std::endl;

        for (size_t i = 1; i < route.size(); ++i) {
            std::cout << std::setw(route[0].length()) << " -> " << route[i] << std::endl;
        }
    } else {
        std::cout << "Error: Route named " << name << " can't be found" << std::endl;
    }
}


// Calculate and prints the Length of a specific route
void OrienteeringMap::route_length(const std::string& name) const {
    if (routes_.find(name) == routes_.end()) {
        std::cout << "Error: Route named " << name << " can't be found" << std::endl;
        return;
    }

    const auto& route = routes_.at(name);
    double total_length = 0.0;

    if (route.size() < 2) {
        std::cout << "Route " << name << " must have at least two points to calculate length." << std::endl;
        return;
    }

    for (size_t i = 0; i < route.size() - 1; ++i) {
        const auto& p1 = points_.at(route[i]);
        const auto& p2 = points_.at(route[i + 1]);

        // Applying the distance formula
        double dx = p2->x - p1->x;
        double dy = p2->y - p1->y;
        double distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));

        total_length += distance;
    }


    total_length = std::round(total_length * 10.0) / 10.0;


    std::cout << "Route " << name << " length was ";

    std::cout << std::setprecision(2) << total_length << std::endl;
}

// finds and print the greatest rise after a given point in any route.
void OrienteeringMap::greatest_rise(const std::string& point_name) const {
    if (points_.find(point_name) == points_.end()) {
        std::cout << "Error: Point named " << point_name << " can't be found" << std::endl;
        return;
    }

    const auto& start_point = points_.at(point_name);
    int max_rise = 0;
    std::set<std::string> rising_routes;

    for (const auto& route_name : start_point->routes) {
        const auto& route = routes_.at(route_name);
        bool found_start = false;
        int current_rise = 0;
        for (const auto& point_name_in_route : route) {
            if (point_name_in_route == point_name) {
                found_start = true;
            }
            if (found_start) {
                int rise = points_.at(point_name_in_route)->height - start_point->height;
                if (rise >= current_rise) {
                    current_rise = rise;
                    if (rise > max_rise) {
                        max_rise = rise;
                        rising_routes.clear();
                        rising_routes.insert(route_name);
                    } else if (rise == max_rise) {
                        rising_routes.insert(route_name);
                    }
                } else {
                    break;
                }
            }
        }
    }

    if (max_rise > 0) {
        std::cout << "Greatest rise after point " << point_name << ", " << max_rise << " meters, is on route(s):" << std::endl;
        for (const auto& route_name : rising_routes) {
            std::cout << " - " << route_name << std::endl;
        }
    } else {
        std::cout << "No route rises after point " << point_name << std::endl;
    }
}
