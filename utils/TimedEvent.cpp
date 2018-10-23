//
// Created by seb on 10/10/18.
//

#include "TimedEvent.hpp"
#include <thread>
#include <iostream>

TimedEvent::TimedEvent(): _threadAlive(true),
	_thread([&](){
		long time;
		std::vector<TimedFuntion, std::allocator<TimedFuntion>>::iterator func;
		_mutexAlive.lock();
		while (_threadAlive) {
			_mutexAlive.unlock();
			time = getTime();
			_mutexFunctions.lock();
			func = _timedFunctions.begin();
			if (_timedFunctions.empty() != 1) {
				while (func != _timedFunctions.end()) {
					if (func->time > _initialTime && func->time < time) {
						func->func();
						_timedFunctions.erase(func);
						break;
					}
					func++;
				}
			}
			_mutexFunctions.unlock();
			_mutexAlive.lock();
		}
		_mutexAlive.unlock();
	})
{
	_initialTime = getTime();
}

TimedEvent::~TimedEvent() {
	_threadAlive = false;
	_thread.join();
}

TimedEvent& TimedEvent::get() {
	static TimedEvent event;

	return event;
}

long TimedEvent::getTime() {
	return (std::chrono::duration_cast<std::chrono::nanoseconds>(
		_clock.now().time_since_epoch()).count());
}

void TimedEvent::addEvent(long time, Time unit, std::function<void()> function) {
	long _time;

	if (unit == Time::Hours)
		_time = time * 3600000000000;
	else if (unit == Time::Minutes)
		_time = time * 60000000000;
	else if (unit == Time::Seconds)
		_time = time * 1000000000;
	else if (unit == Time::MilliSeconds)
		_time = time * 1000000;
	else if (unit == Time::MicroSeconds)
		_time = time * 1000;
	else
		_time = time;

	_mutexFunctions.lock();
	_timedFunctions.emplace_back(TimedFuntion(getTime() + _time, function));
	_mutexFunctions.unlock();
}