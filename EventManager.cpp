//
// Created by seb on 02/05/18.
//

#include <algorithm>
#include <iostream>

#include "EventManager.hpp"

EventManager &EventManager::get()
{
	static EventManager manager;
	return (manager);
}

EventManager::EventManager(): _isAlive(true),  _readThread([this](){
	std::string in;

	_mutexAlive.lock();
	while (this->_isAlive) {
		_mutexAlive.unlock();
		std::getline (std::cin, in);
		if (!in.empty()) {
			fire(in);
		}
		_mutexAlive.lock();
	}
	_mutexAlive.unlock();
})
{}

EventManager::~EventManager()
{
	_mutexAlive.lock();
	_isAlive = false;
	_mutexAlive.unlock();
	_readThread.join();
}

void EventManager::_erase(struct trash toErase) {
	auto it = std::find(_map[toErase.first][toErase.second].begin(), _map[toErase.first][toErase.second].end(), toErase.third);
	if (it == _map[toErase.first][toErase.second].end())
		return;
	delete(reinterpret_cast<Event<void*>*>(toErase.third));
	_map[toErase.first][toErase.second].erase(it);

}