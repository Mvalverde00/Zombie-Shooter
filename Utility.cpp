#ifndef UTILITY_GUARD
#define UTILITY_GUARD

#include <SDL.h>
#include <math.h>
#include<vector>

class UTILITY{
public:

	static int distanceSquared(int x0, int y0, int x1, int y1) {
		return (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0);
	}
	static int distance(int x0, int y0, int x1, int y1) {
		return std::sqrt( (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
	}	


};


#endif // UTILITY_GUARD