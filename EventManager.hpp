//
// Created by seb on 02/05/18.
//

#ifndef EVENT_EVENTMANAGER_HPP
#define EVENT_EVENTMANAGER_HPP

#include <unordered_map>
#include <iostream>
#include <list>
#include <thread>
#include <mutex>
#include <any>
#include "Event.hpp"

class EventManager {
public:
	template<typename T>
	struct fcn {
		using type  = T;
		static const char* Get()
		{
			return typeid(T).name();
		}
	};

	struct trash {
		std::string			first;
		std::string			second;
		void				*third;
	};

	EventManager();

	~EventManager();

	static EventManager &get();

	template<typename ...Args, typename T = void>
	struct trash addHandler(std::string name, T func) {
		struct trash ret;
		ret.third = new Event<Args...>(std::function<void(Args...)>(func));
		_map[name][std::string(fcn<std::function<void(Args...)>>::Get())].push_back(ret.third);
		ret.first = name;
		ret.second = std::string(fcn<std::function<void(Args...)>>::Get());
		return (ret);
	}

	/*struct trash addHandler(std::string name, std::any func) {
		struct trash ret;
		std::cout << func.type().name() << std::endl;
		ret.third = new Event<>(std::any_cast<std::function<void()>>(func));
		_map[name][std::string(func.type().name())].push_back(ret.third);
		ret.first = name;
		ret.second = std::string(func.type().name());
		return (ret);
	}*/

	template<typename ...Args>
	void fire(std::string name , Args... argc) {
		auto aMap = _map.find(name);
		if (aMap == _map.end())
			return;
		auto bMap = aMap->second.find(std::string(fcn<std::function<void(Args...)>>::Get()));
		if (bMap == aMap->second.end())
			return;
		for (void *func : bMap->second)
			static_cast<Event<Args...>*>(func)->fire(argc...);
	}

	void fire(std::string name) {
		auto aMap = _map.find(name);
		if (aMap == _map.end())
			return;
		auto bMap = aMap->second.find(std::string(fcn<std::function<void()>>::Get()));
		if (bMap == aMap->second.end())
			return;
		for (void *func : bMap->second)
			static_cast<Event<>*>(func)->fire();
	}

	void _erase(struct trash);

private:
	std::unordered_map<std::string, std::unordered_map<std::string, std::list<void*>>>	_map;

	std::mutex	_mutexAlive;
	bool		_isAlive;
	std::thread	_readThread;
};

#endif //EVENT_EVENTMANAGER_HPP
