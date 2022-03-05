#pragma once

#include <iostream>
#include <list>
#include <map>

#include "IdGenerator.h"

class Event {
public:
	virtual ~Event() {}
};

class HandlerFunctionBase {
public:
	virtual ~HandlerFunctionBase() {}
	void exec(Event* event) {
		call(event);
	}

private:
	virtual void call(Event* event) = 0;
};

template<typename T, typename EventType>
class MemberFunctionHandler : public HandlerFunctionBase {

	typedef void (T::* MemberFunction)(EventType*);

private:
	// instance of system class
	T* m_instance;
	// member function of the above instance
	MemberFunction m_memberFunction;

public:
	MemberFunctionHandler(T* instance, MemberFunction memberFunction)
		: m_instance{ instance }, m_memberFunction(memberFunction) {}

	void call(Event* event) {
		(m_instance->*m_memberFunction)(static_cast<EventType*>(event));
	}
};

using HandlerList = std::list<std::unique_ptr<HandlerFunctionBase>>;

class EventHandler {
private:
	std::map<EventTypeID, std::unique_ptr<HandlerList>> m_subscribers;

public:
	template<typename EventType>
	void publish(EventType* event) {
		if (m_subscribers[getEventTypeID<EventType>()] == nullptr) {
			return;
		}

		for (auto& handler : *m_subscribers[getEventTypeID<EventType>()]) {
			if (handler != nullptr)
				handler->exec(event);
		}
	}

	template<typename T, typename EventType>
	void subscribe(T* instance, void (T::* memberFunction)(EventType*)) {
		if (m_subscribers[getEventTypeID<EventType>()] == nullptr) {
			m_subscribers[getEventTypeID<EventType>()] = std::make_unique<HandlerList>();
		}

		m_subscribers[getEventTypeID<EventType>()]->push_back(std::make_unique<MemberFunctionHandler<T, EventType>>(instance, memberFunction));
	}
};