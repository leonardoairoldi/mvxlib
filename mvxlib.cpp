// mvxlib.cpp : Defines the entry point for the application.
//

#include "mvxlib.h"



void Example() {
	mx m({ {1, 2, 3}, {4, 5, 6} });
	m.print();

	std::cout << m(1, 2) << std::endl;
	m(1, 2) = 10;

	m.print();

	double& v = m(1, 2);
	v = 20;
	m.print();

	mx div = m * m;
	div.print();
	div.cumsum(COL).print();

	vx a = m(0, ROW);


	vx diva = a;
	diva.print();
	vx a1 = m(1, COL);
	//vx sum = a + a1;

	a1.minimum_index();
	a1.print();
	vx cs = a1.cumsum();
	cs.print();

	vx csd = 2.0 - cs;
	csd.print();
}

int main()
{
	std::cout << "Hello CMake." << std::endl;

	Example();

	return 0;
}