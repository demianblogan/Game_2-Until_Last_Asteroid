#pragma once
#include <functional>
#include <list>
#include <SFML/Window.hpp>
#include "ActionMap.h"

// Class TargetForActions is a manager that links "Action" objects to specific
// functions that should been invoked when these actions are triggered.
// That's why this class process all action events.
template <typename ActionID>
class TargetForActions
{
public:
	using FuncType = std::function<void(const sf::Event&)>;

	TargetForActions() = default;
	TargetForActions(const ActionMap<ActionID>& map);

	bool ProcessNotRealTimeEvent(const sf::Event& event) const;
	void ProcessRealTimeEvents() const;

	void Bind(const ActionID& action, const FuncType& callback);
	void Unbind(const ActionID& action);

private:
	std::list<std::pair<ActionID, FuncType>> realTimeEvents;    // events that should been processed first
	std::list<std::pair<ActionID, FuncType>> notRealTimeEvents; // events that should been processed second

	const ActionMap<ActionID>& actionMap;
};

template <typename ActionID>
TargetForActions<ActionID>::TargetForActions(const ActionMap<ActionID>& map)
	: actionMap(map)
{ }

template <typename ActionID>
bool TargetForActions<ActionID>::ProcessNotRealTimeEvent(const sf::Event& event) const
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

template <typename ActionID>
void TargetForActions<ActionID>::ProcessRealTimeEvents() const
{
	for (auto& [key, function] : realTimeEvents)
	{
		const Action& action = actionMap.Get(key);
		if (action.IsTriggeredByPress())
			function(action.GetEvent());
	}
}

template <typename ActionID>
void TargetForActions<ActionID>::Bind(const ActionID& key, const FuncType& callback)
{
	const Action& action = actionMap.Get(key);

	if (action.GetType() & Action::Type::RealTime)
		realTimeEvents.emplace_back(key, callback);
	else
		notRealTimeEvents.emplace_back(key, callback);
}

template <typename ActionID>
void TargetForActions<ActionID>::Unbind(const ActionID& key)
{
	auto removeFunction = [&key](const std::pair<ActionID, FuncType>& pair)
	{
		return pair.first == key;
	};

	const Action& action = actionMap.Get(key);

	if (static_cast<int>(action.type) & static_cast<int>(Action::Type::RealTime))
		realTimeEvents.remove_if(removeFunction);
	else
		notRealTimeEvents.remove_if(removeFunction);
}