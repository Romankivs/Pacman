#pragma once

#include <utility>

int findDirection(std::pair<int, int> from, std::pair<int, int> to) {
	int dx = from.first - to.first;
	int dy = from.second - to.second;

	if (dx == 0) {
		if (dy > 0) {
			return 3;
		}
		else if (dy < 0) {
			return 4;
		}
	}
	else if (dy == 0) {
		if (dx > 0) {
			return 1;
		}
		else if (dx < 0) {
			return 2;
		}
	}

	return -1;
}