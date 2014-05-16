#include "ccc_win.h"
#include <string>
#include <array>
#include <cmath>
#include "equation.h"

int ccc_win_main();
int equation_solver();
void zoom();
void makReady(int min, int max, int miny, int maxy, int minx, int maxx);
void makeReady(int min, int max, int miny, int maxy, int minx, int maxx) {
	//drawing a Grid
	cwin.coord(min, max, max, min);
	for (int i = miny; i <= maxy; i++) {
		cwin << Line(Point(minx, i), Point(maxx, i));
	}
	for (int i = minx; i <= maxx; i++){
		cwin << Line(Point(i,miny), Point(i,maxy));
	}
	//Marking X-Axis and Y-Axis
	for (double dy = -0.03; dy <= 0.03; dy = dy + 0.01) {
		cwin << Line(Point(miny, dy), Point(maxx, dy));
	}
	for (double dx = -0.03; dx <= 0.03; dx = dx + 0.01) {
		cwin << Line(Point(dx, miny), Point(dx, maxx));
	}
	//numbering grid 
	//X-axis numbering
	for (int num = minx; num <= maxx; num++) {
		cwin << Message(Point(num, -0.02), num);
	}
	// -ve Y-axis
	for (int num = miny; num < 0; num++) {
		if (num == 0) continue;
		cwin << Message(Point(-0.7, num), num);
	}
	// +ve Y-axis
	for (int num = 0; num <= maxy; num++) {
		if (num == 0) continue;
		cwin << Message(Point(-0.4, num), num);
	}
	draw();
	zoom();
}
 void zoom() {
	 cwin << Line(Point(-10, -2), Point(-10, 2));
	 cwin << Line(Point(-10, -2), Point(-8.3, -2));
	 cwin << Line(Point(-10, 2), Point(-8.3, 2));
	 cwin << Line(Point(-8.3, -2), Point(-8.3, 2));
	 cwin << Message(Point(-9.8, 1.5), "Press");
	 cwin << Message(Point(-9.8, 0.5), "Here");
	 cwin << Message(Point(-9.8, -0.5), "to");
	 cwin << Message(Point(-9.9, -1), "re-run");
	 Point k(0, 0);
	Point z = cwin.get_mouse("Press on upper screen to zoom in, and lower one to zoom out");
	double x = z.get_x(); double y = z.get_y();
	if (y >=0) {
		//zoom in
		cwin.clear();
		makeReady(-4, 4, -4, 4, -4, 4);
	}
	else if (y < 0) {
		cwin.clear();
		makeReady(-10, 10, -8, 8, -8, 8);
	}
}

 
int ccc_win_main() {
	cwin.clear();
	equation_solver();
	makeReady(-10, 10, -8, 8, -8, 8);
	return 0;
}
