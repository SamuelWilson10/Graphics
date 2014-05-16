#include "ccc_win.h"
#include <string>
#include <array>
#include <cmath>
#include <stdlib.h>
#include <vector>
using namespace std;

void draw();
void check();
void zoom();
int ccc_win_main();
int val = 0; int c = 1, d =1;
float* x_vals = new float[162 * d];
float* y_vals = new float[162 * d];
float* x_point = new float[162 * d];
float* y_point = new float[162 * d];
int equation_solver() {
	cwin.clear();
	val = 0;
	string equation;
	string to = "";
	double y = 0;
	int j = 0, k = 0, temp;
	equation = cwin.get_string("Please enter your equation");

	//converting to lowercase letters and eliminiate white space
	for (int i = 0; i < equation.length(); i++){
		equation[i] = tolower(equation[i]);
		int white_sp = equation.find(" ");
		if (white_sp != -1) equation.erase(white_sp, 1);
	}
	int value = 0;
	int* ops = new int[10];
	//to determine length of dynamic arrays (c = no. of terms)
	for (int i = 1; i < equation.length(); i++) {
		if (equation[i] == '+' || equation[i] == '-') {
			if (equation[i - 1] == ')') {
				d++;
				ops[value++] = i;
			}
			else if (equation.substr(i - 1, 1) != "^" && equation.substr(i - 1, 1) != "=") {
				d++;
				ops[value++] = i;
			}
		}
	}
	cwin << Message(Point(-10, 8), "Equation to be solved: "); 
	cwin << Message(Point(-10, 7), equation);

	//cout << "final value of c equals: " << c << endl;

	//creating dynamic/static arrays
	vector<string> elements(d);
	cwin << Message(Point(-10, 5), "Number of elements: ");
	cwin << Message(Point(-10, 4), elements.size());


	//handling first term
	temp = equation.find("=");
	if (temp >= 0) {
		elements[0] = equation.substr(temp + 1, ops[0] - 2);
	}
	else {
		elements[0] = equation.substr(0, ops[0]);
	}

	//appending rest of terms to elements[]
	for (int p = 0, q = 1; p < value, q <= value; p++, q++) {
		elements[q] = equation.substr(ops[p], ops[p + 1] - (ops[p]));
	}
	for (int i = 0; i < d; i++) {
		cwin << Message(Point(-10, 2), "Elements are: ");
		cwin << Message(Point(-10, 1-i), elements[i]);
	}

	//Iterating through elements[] and obtaining values of x,y
	for (int i = 0; i < d; i++) {
		int left_br = elements[i].find("(");
		int right_br = elements[i].find(")");
		int x_pos = elements[i].find("x");
		int pwr_pos = elements[i].find("^");
		char first = elements[i][0];

		//Terms: Brackets, Power, and Coeff exists [eg: 4(x^2) ] DONE
		if (left_br != -1 && right_br != -1 && x_pos>0 && pwr_pos > 0) {
			if (left_br == 0) {
				//cout << "to be solved: " << elements[i] << endl;
				//cout << "Same as [(x^n)]" << endl;
				for (double x = -8; x <= 8; x += 0.1) {
					x_vals[val] = x;
					x_point[val] = x;
					to.insert(0, to_string(x));
					elements[i].insert(left_br + 1, to);
					auto left_br = elements[i].find("(");
					auto right_br = elements[i].find(")");
					auto x_pos = elements[i].find("x");
					auto pwr_pos = elements[i].find("^");
					y_vals[val] = pow(atof(elements[i].substr(left_br + 1, pwr_pos).c_str()), atof(elements[i].substr(pwr_pos + 1, right_br).c_str()));
					elements[i].erase(left_br + 1, to.length());
					to.erase();
					val++;
				}
			}
			else if (left_br == 1 && first == '+') {
				//cout << "to be solved: " << elements[i] << endl;
				//cout << "Same as [+(x^n)]" << endl;
				for (double x = -8; x <= 8; x += 0.1) {
					x_vals[val] = x;
					x_point[val] = x;
					to.insert(0, to_string(x));
					elements[i].insert(left_br + 1, to);
					auto left_br = elements[i].find("(");
					auto right_br = elements[i].find(")");
					auto x_pos = elements[i].find("x");
					auto pwr_pos = elements[i].find("^");
					y_vals[val] = pow(atof(elements[i].substr(left_br + 1, pwr_pos).c_str()), atof(elements[i].substr(pwr_pos + 1, right_br).c_str()));
					elements[i].erase(left_br + 1, to.length());
					to.erase();
					val++;
				}
			}
			else if (left_br == 1 && first == '-') {
				//cout << "to be solved: " << elements[i] << endl;
				//cout << "Same as [-(x^n)]" << endl;
				for (double x = -8; x <= 8; x += 0.1) {
					x_vals[val] = x;
					x_point[val] = x;
					to.insert(0, to_string(x));
					elements[i].insert(left_br + 1, to);
					auto left_br = elements[i].find("(");
					auto right_br = elements[i].find(")");
					auto x_pos = elements[i].find("x");
					auto pwr_pos = elements[i].find("^");
					y_vals[val] = -pow(atof(elements[i].substr(left_br + 1, pwr_pos).c_str()), atof(elements[i].substr(pwr_pos + 1, right_br).c_str()));
					elements[i].erase(left_br + 1, to.length());
					to.erase();
					val++;
				}
			}
			else if (left_br > 0) {
				//cout << "to be solved: " << elements[i] << endl;
				//cout << "Same as [-m(x^n) or +m(x^n) or m(x^n)]" << endl;
				elements[i].erase(x_pos, 1);
				for (double x = -8; x <= 8; x += 0.1) {
					x_vals[val] = x;
					x_point[val] = x;
					to.insert(0, to_string(x));
					elements[i].insert(left_br + 1, to);
					auto left_br = elements[i].find("(");
					auto right_br = elements[i].find(")");
					auto x_pos = elements[i].find("x");
					auto pwr_pos = elements[i].find("^");
					y_vals[val] = atof(elements[i].substr(0, left_br).c_str()) * pow(atof(elements[i].substr(left_br + 1, pwr_pos).c_str()), atof(elements[i].substr(pwr_pos + 1, right_br).c_str()));
					elements[i].erase(left_br + 1, to.length());
					to.erase();
					val++;
				}
			}
		} //Terms: No Brackets exists but Power and coeff does
		else if (left_br == -1 && right_br == -1 && x_pos >= 0 && pwr_pos > 0) {
			if (x_pos == 1 && first == '+') {
				//cout << "to be solved: " << elements[i] << endl;
				//cout << "Same as [+x^n]" << endl;
				auto x_pos = elements[i].find("x");
				auto pwr_pos = elements[i].find("^");
				elements[i].erase(x_pos, 1);
				for (double x = -8; x <= 8; x += 0.1) {
					x_vals[val] = x;
					x_point[val] = x;
					to.insert(0, to_string(x));
					elements[i].insert(0, to);
					pwr_pos = elements[i].find("^");
					y_vals[val] = pow(atof(elements[i].substr(0, pwr_pos).c_str()), atof(elements[i].substr(pwr_pos + 1).c_str()));
					elements[i].erase(0, to.length());
					to.erase();
					val++;
				}
			}
			else if (x_pos == 1 && first == '-') {
				//cout << "to be solved: " << elements[i] << endl;
				//cout << "Same as [-x^n]" << endl;
				auto x_pos = elements[i].find("x");
				auto pwr_pos = elements[i].find("^");
				elements[i].erase(x_pos, 1);
				for (double x = -8; x <= 8; x += 0.1) {
					x_vals[val] = x;
					x_point[val] = x;
					to.insert(0, to_string(x));
					elements[i].insert(0, to);
					pwr_pos = elements[i].find("^");
					y_vals[val] = -pow(atof(elements[i].substr(0, pwr_pos).c_str()), atof(elements[i].substr(pwr_pos + 1).c_str()));
					elements[i].erase(0, to.length());
					to.erase();
					val++;
				}
			}
			else if (x_pos == 0) {
				//cout << "to be solved: " << elements[i] << endl;
				//cout << "Same as [x^n]" << endl;
				auto x_pos = elements[i].find("x");
				auto pwr_pos = elements[i].find("^");
				elements[i].erase(x_pos, 1);
				for (double x = -8; x <= 8; x += 0.1) {
					x_vals[val] = x;
					x_point[val] = x;
					to.insert(0, to_string(x));
					elements[i].insert(0, to);
					pwr_pos = elements[i].find("^");
					y_vals[val] = pow(atof(elements[i].substr(0, pwr_pos).c_str()), atof(elements[i].substr(pwr_pos + 1).c_str()));
					elements[i].erase(0, to.length());
					to.erase();
					val++;
				}
			}
			else if (x_pos >= 1) {
				auto x_pos = elements[i].find("x");
				auto coeff = elements[i].substr(0, x_pos);
				//cout << "to be solved: " << elements[i] << endl;
				//cout << "Same as [mx^n or +mx^2 or -mx^n]" << endl;
				elements[i].erase(x_pos, 1);
				for (double x = -8; x <= 8; x += 0.1) {
					x_vals[val] = x;
					x_point[val] = x;
					to.insert(0, to_string(x));
					elements[i].insert(coeff.length(), to);
					pwr_pos = elements[i].find("^");
					y_vals[val] = atof(elements[i].substr(0, coeff.length()).c_str()) * pow(atof(elements[i].substr(coeff.length(), pwr_pos).c_str()), atof(elements[i].substr(pwr_pos + 1).c_str()));
					elements[i].erase(coeff.length(), to.length());
					to.erase();
					val++;
				}
			}
		}
		else if (x_pos == -1) {
			//cout << "to be solved: " << elements[i] << endl;
			for (double x = -8; x <= 8; x += 0.1) {
				x_vals[val] = x;
				y_vals[val] = atof(elements[i].substr(0).c_str());
				val++;
			}
		}
	}
	/*for (int i = 1; i <= val; i++) {
		cwin << Message(Point(0, 8), "X values");
		cwin << Message(Point(0, 8-i), x_vals[i-1]);
		cwin << Message(Point(5, 8), "Y values");
		cwin << Message(Point(5, 8-i), y_vals[i-1]);
	}*/

	for (int i = 0; i < 162 * d; i++) {
		y_point[i] = 0;
	}

	//final (X,Y) Points
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < 161; j++) {
			y_point[j] += y_vals[(i * 161) + j];
		}
	}
	for (int i = 0; i < 161; i++) {
	cwin << Message(Point(0, 8), "X values");
	cwin << Message(Point(0, 7-i), x_vals[i]);
	cwin << Message(Point(5, 8), "Y values");
	cwin << Message(Point(5, 7-i), y_point[i]);
	}

	string ans;
	cwin << Message(Point(-10, -8), "enter n to retry anything else to continue");
	ans = cwin.get_string(" ");
	if (ans == "n" || ans == "N") {
		cwin << Message(Point(-7, 1), "retrying..");
		cwin.clear();
		equation_solver();
	}
	else {
		cwin.clear();
	}
	return 0;
	draw();
}
void draw() {
	for (int i = 0; i < 161; i++) {
		for (double d = -0.03; d <= 0.03; d+=0.01) {
			cwin << Line(Point(x_vals[i] + d, y_point[i]), Point(x_vals[i + 1] + d, y_point[i + 1]));
			cwin << Line(Point(x_vals[i], y_point[i] + d), Point(x_vals[i + 1], y_point[i + 1] + d));
		}
	}
	zoom();
}
