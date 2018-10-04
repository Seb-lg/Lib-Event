//
// Created by seb on 04/05/18.
//

#ifndef EVENT_EVENTADMIN_HPP
#define EVENT_EVENTADMIN_HPP

#include <unordered_map>
#include <list>

#include "EventManager.hpp"

class EventAdmin {
public:
	template<typename T = void>
	struct fcn {
		using type  = T;
		static const char* Get()
		{
			return typeid(T).name();
		}
	};

	EventAdmin();
	~EventAdmin();

	template<typename ...Args>
	void addHandler(std::string name, typename fcn<std::function<void(Args...)>>::type func) {
		_trash.push_back(_manager.addHandler<Args...>(name, func));
	}

	void addHandler(std::string name, typename fcn<std::function<void()>>::type func) {
		_trash.push_back(_manager.addHandler(name, func));
	}

	template<typename ...Args>
	void fire(std::string name , Args... argc) {
		_manager.fire(name, argc...);
	}

	void fire(std::string name) {
		_manager.fire(name);
	}

	private:
	EventManager				&_manager;
	std::list<struct EventManager::trash>	_trash;
};


#endif //EVENT_EVENTADMIN_HPP
