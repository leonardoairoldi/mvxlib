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
	csd.to_csv("csd.csv");

	vx m1 = vx::from_csv("csd.csv");
	m1.print();
	clrscr();

	mx af({ {1, 2, 3}, {4, 5, 6} });
	mx bf({ {1, 2, 3}, {7, 5, 8} });
	
	af.append_to_csv("a.csv", ";");
	bf.append_to_csv("a.csv", ";");	

	std::list<mx> mlist = mx::from_csv("a.csv", ";");

	std::cout << "List size: " << mlist.size() << std::endl;
	
	auto it = mlist.begin();
	(*it).print();
}

int main()
{
	std::cout << "Hello CMake." << std::endl;

	Example();

	return 0;
}