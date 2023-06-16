#pragma once
#include <unordered_map>
#include "Action.h"

// Class ActionMap is just a container for a std::unordered_map of elements:
// key - any keyboard key or mouse button.
// value - action that is linked to the key.
template <typename KeyType>
class ActionMap
{
public:
	void Map(const KeyType& key, const Action& action)
	{
		map.emplace(key, action);
	}

	const Action& Get(const KeyType& key) const
	{
		return map.at(key);
	}

private:
	std::unordered_map<KeyType, Action> map;
};