#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

#include "EventBase.h"

using EventTypeID = unsigned int;

inline EventTypeID getEventTypeID() {
	static EventTypeID eventID = 0;
	return eventID++;
}

template <typename T> inline EventTypeID getEventTypeID() noexcept {
	static EventTypeID typeID = getEventTypeID();
	return typeID;
}



class HandlerFunctionBase {
public:
	virtual ~HandlerFunctionBase() {}
	void exec(EventBase* event) {
		call(event);
	}

private:
	virtual void call(EventBase* event) = 0;
};

template<typename T, typename EventType>
class MemberFunctionHandler : public HandlerFunctionBase {
private:
	// instance of system class
	T* m_instance;
	// member function of the above instance
	typedef void (T::* MemberFunction)(EventType*);
	MemberFunction m_memberFunction;

public:
	MemberFunctionHandler(T* instance, MemberFunction memberFunction)
		: m_instance{ instance }, m_memberFunction(memberFunction) {}

	void call(EventBase* event) {
		(m_instance->*m_memberFunction)(static_cast<EventType*>(event));
	}
};

using HandlerList = std::list<std::unique_ptr<HandlerFunctionBase>>;

class EventHandler {
private:
	std::unordered_map<EventTypeID, std::unique_ptr<HandlerList>> m_subscribers;

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
	void subscribe(T* instance, void (T::*memberFunction)(EventType*)) {
		if (m_subscribers[getEventTypeID<EventType>()] == nullptr) {
			m_subscribers[getEventTypeID<EventType>()] = std::make_unique<HandlerList>();
		}

		m_subscribers[getEventTypeID<EventType>()]->push_back(std::make_unique<MemberFunctionHandler<T, EventType>>(instance, memberFunction));
	}
};