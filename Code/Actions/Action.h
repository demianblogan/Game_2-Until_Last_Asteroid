#pragma once
#include <SFML/Window/Event.hpp>

// Class Action contains information about any game action that is trigged by
// specific button/key pressing/releasing.
class Action
{
public:
	enum class Type
	{
		RealTime = 1,
		Pressed = 1 << 1,
		Released = 1 << 2,
		RealTime_Pressed = RealTime | Pressed
	};

	Action(const sf::Keyboard::Key& key, Type type = Type::RealTime_Pressed);
	Action(const sf::Mouse::Button& button, Type type = Type::RealTime_Pressed);

	bool IsTriggeredByPress() const;
	const sf::Event& GetEvent() const;
	Type GetType() const;

	bool operator==(const sf::Event& event) const;
	bool operator==(const Action& other) const;

private:
	sf::Event event;
	Type type;
};

inline int operator|(Action::Type a, Action::Type b);
inline int operator&(Action::Type a, Action::Type b);