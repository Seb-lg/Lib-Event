//
// Created by seb on 10/10/18.
//

#pragma once

#include <functional>
#include <vector>
#include <mutex>
#include <thread>


enum class Time {
	Hours,
	Minutes,
	Seconds,
	MilliSeconds,
	MicroSeconds,
	NanoSeconds
};

struct TimedFuntion {
	TimedFuntion() {
		time = 0;
		func = nullptr;
	}

	TimedFuntion(long time, std::function<void()> &function) {
		this->time = time;
		this->func = function;
	}

	long 			time;
	std::function<void()>	func;
};

class TimedEvent {
public:
	TimedEvent();
	~TimedEvent();

	void addEvent(long time, Time unit, std::function<void()> function);
	long getTime();
	static TimedEvent &get();

private:
	std::vector<TimedFuntion>		_timedFunctions;
 	std::chrono::high_resolution_clock	_clock;
 	std::thread				_thread;
 	long 					_initialTime;
 	bool 					_threadAlive;
	std::mutex 				_mutexAlive;
	std::mutex 				_mutexFunctions;
};
