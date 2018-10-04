//
// Created by seb on 02/05/18.
//

#ifndef EVENT_EVENT_HPP
#define EVENT_EVENT_HPP


#include <functional>

template<typename ...Args>
class Event {
public:
	Event(std::function<void(Args...)> f): _function(f){}

	void fire(Args... f) {
		_function(f...);
	}

private:
	std::function<void(Args...)>	_function;
};


#endif //EVENT_EVENT_HPP
