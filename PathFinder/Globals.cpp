#include "Globals.h"

std::queue<std::vector<Coordinate>> WorkerQueue;

bool found_shortest_path;

// Path cycle speed in milliseconds. As in 1 every path_cycle_speed ms
int path_cycle_speed = 10;

sf::Mutex mutex;

std::vector<Coordinate> final_path;
