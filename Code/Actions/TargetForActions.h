#pragma once
#include <functional>
#include <list>
#include <SFML/Window.hpp>
#include "ActionMap.h"

// Class TargetForActions is a manager that links "Action" objects to specific
// functions that should been invoked when these actions are triggered.
// That's why this class process all action events.
template <typename KeyType>
class TargetForActions
{
public:
	using FuncType = std::function<void(const sf::Event&)>;

	TargetForActions() = default;
	TargetForActions(const ActionMap<KeyType>& map);

	bool ProcessNotRealTimeEvent(const sf::Event& event) const;
	void ProcessRealTimeEvents() const;

	void Bind(const KeyType& action, const FuncType& callback);
	void Unbind(const KeyType& action);

private:
	std::list<std::pair<KeyType, FuncType>> realTimeEvents;    // events that should been processed first
	std::list<std::pair<KeyType, FuncType>> notRealTimeEvents; // events that should been processed second

	const ActionMap<KeyType>& actionMap;
};

template <typename KeyType>
TargetForActions<KeyType>::TargetForActions(const ActionMap<KeyType>& map)
	: actionMap(map)
{ }

template <typename KeyType>
bool TargetForActions<KeyType>::ProcessNotRealTimeEvent(const sf::Event& event) const
{
	for (auto& [key, function] : notRealTimeEvents)
	{
		if (actionMap.Get(key) == event)
		{
			function(event);
			return true;
		}
	}

	return false;
}

template <typename KeyType>
void TargetForActions<KeyType>::ProcessRealTimeEvents() const
{
	for (auto& [key, function] : realTimeEvents)
	{
		const Action& action = actionMap.Get(key);
		if (action.IsTriggeredByPress())
			function(action.event);
	}
}

template <typename KeyType>
void TargetForActions<KeyType>::Bind(const KeyType& key, const FuncType& callback)
{
	const Action& action = actionMap.Get(key);

	if (static_cast<int>(action.type) & static_cast<int>(Action::Type::RealTime))
		realTimeEvents.emplace_back(key, callback);
	else
		notRealTimeEvents.emplace_back(key, callback);
}

template <typename KeyType>
void TargetForActions<KeyType>::Unbind(const KeyType& key)
{
	auto removeFunction = [&key](const std::pair<KeyType, FuncType>& pair)
	{
		return pair.first == key;
	};

	const Action& action = actionMap.Get(key);

	if (static_cast<int>(action.type) & static_cast<int>(Action::Type::RealTime))
		realTimeEvents.remove_if(removeFunction);
	else
		notRealTimeEvents.remove_if(removeFunction);
}