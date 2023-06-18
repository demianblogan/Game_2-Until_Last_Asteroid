#include "Action.h"

Action::Action(const sf::Keyboard::Key& key, Type type)
	: type(type)
{
	event.type = sf::Event::KeyPressed;
	event.key.code = key;
}

Action::Action(const sf::Mouse::Button& button, Type type)
	: type(type)
{
	event.type = sf::Event::MouseButtonPressed;
	event.mouseButton.button = button;
}

bool Action::IsTriggeredByPress() const
{
	if (event.type == sf::Event::KeyPressed)
		return sf::Keyboard::isKeyPressed(event.key.code);
	else if (event.type == sf::Event::MouseButtonPressed)
		return sf::Mouse::isButtonPressed(event.mouseButton.button);
	else
		return false;
}

 const sf::Event& Action::GetEvent() const
{
	return event;
}

Action::Type Action::GetType() const
{
	return type;
}

bool Action::operator==(const sf::Event& other) const
{
	switch (other.type)
	{
	case sf::Event::KeyPressed:
		if (type & Type::Pressed && event.type == sf::Event::KeyPressed)
			return event.key.code == other.key.code;
		break;

	case sf::Event::KeyReleased:
		if (type & Type::Released && event.type == sf::Event::KeyPressed)
			return event.key.code == other.key.code;
		break;

	case sf::Event::MouseButtonPressed:
		if (type & Type::Pressed && event.type == sf::Event::MouseButtonPressed)
			return event.mouseButton.button == other.mouseButton.button;
		break;

	case sf::Event::MouseButtonReleased:
		if (type & Type::Released && event.type == sf::Event::MouseButtonPressed)
			return event.mouseButton.button == other.mouseButton.button;
		break;
	}

	return false;
}

bool Action::operator==(const Action& other) const
{
	return type == other.type && event == other;
}

inline int operator|(Action::Type a, Action::Type b)
{
	return int(a) | int(b);
}

inline int operator&(Action::Type a, Action::Type b)
{
	return int(a) & int(b);
}