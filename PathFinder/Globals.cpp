#include "Globals.h"

std::queue<std::vector<Coordinate>> WorkerQueue;

bool found_shortest_path;

sf::Mutex mutex;
