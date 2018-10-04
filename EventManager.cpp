//
// Created by seb on 02/05/18.
//

#include <algorithm>

#include "EventManager.hpp"

EventManager &EventManager::get()
{
	static EventManager manager;
	return (manager);
}

EventManager::~EventManager()
{
}

void EventManager::_erase(struct trash toErase) {
	auto it = std::find(_map[toErase.first][toErase.second].begin(), _map[toErase.first][toErase.second].end(), toErase.third);
	if (it == _map[toErase.first][toErase.second].end())
		return;
	delete(reinterpret_cast<Event<void*>*>(toErase.third));
	_map[toErase.first][toErase.second].erase(it);

}