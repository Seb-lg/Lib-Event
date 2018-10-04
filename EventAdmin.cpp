//
// Created by seb on 04/05/18.
//

#include "EventAdmin.hpp"

EventAdmin::EventAdmin() : _manager(EventManager::get())
{
}

EventAdmin::~EventAdmin() {
	for (EventManager::trash &it : _trash)
		_manager._erase(it);

}
