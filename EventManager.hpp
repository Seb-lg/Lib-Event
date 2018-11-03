//
// Created by seb on 02/05/18.
//

#ifndef EVENT_EVENTMANAGER_HPP
#define EVENT_EVENTMANAGER_HPP

#include <unordered_map>
#include <list>
#include <thread>
#include <mutex>
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

	template<typename ...Args>
	struct trash addHandler(std::string name, typename fcn<std::function<void(Args...)>>::type func) {
		struct trash ret;
		ret.third = new Event<Args...>(func);
		_map[name][std::string(fcn<Args...>::Get())].push_back(ret.third);
		ret.first = name;
		ret.second = std::string(fcn<Args...>::Get());
		return (ret);
	}

	struct trash addHandler(std::string name, typename fcn<std::function<void()>>::type func) {
		struct trash ret;
		ret.third = new Event<>(func);
		_map[name][std::string(fcn<void>::Get())].push_back(ret.third);
		ret.first = name;
		ret.second = std::string(fcn<void>::Get());
		return (ret);
	}

	template<typename ...Args>
	void fire(std::string name , Args... argc) {
		auto aMap = _map.find(name);
		if (aMap == _map.end())
			return;
		auto bMap = aMap->second.find(std::string(fcn<Args...>::Get()));
		if (bMap == aMap->second.end())
			return;
		for (void *func : bMap->second)
			static_cast<Event<Args...>*>(func)->fire(argc...);
	}

	void fire(std::string name) {
		auto aMap = _map.find(name);
		if (aMap == _map.end())
			return;
		auto bMap = aMap->second.find(std::string(fcn<void>::Get()));
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
