//
// Created by seb on 12/05/19.
//

#include <EventAdmin.hpp>
#include <iostream>

int main(int ac, char**av) {
	EventAdmin manager;

	manager.addHandler<int>("", [](int i){std::cout << "JE SUIS UN TEST " << i << std::endl;});

	manager.fire("", 9);
	return (0);
}