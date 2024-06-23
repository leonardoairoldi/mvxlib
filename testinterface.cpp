#include "vx.h"
#include "mx.h"
#include <map>

namespace test {

	// Test the add operator+
	void add();




	std::map<std::string, void(*)()> examples =
	{
		{"operator+", add}

	};

	void add() {
		return;
	}


}