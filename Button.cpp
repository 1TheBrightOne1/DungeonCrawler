#include "Button.h"


Button::Button(InterfaceMetadata metadata, const sf::Vector2f& position) : StaticEntity(metadata.fileName, metadata.textureLocation, position, false, "interface"), metadata(metadata)
{
	sf::IntRect stuff = this->position;
	observer = EventManager::Subscribe(Click, [=](const sf::Event& event) {
		if (event.mouseButton.x >= stuff.left && event.mouseButton.x <= stuff.left + stuff.width &&
			event.mouseButton.y >= stuff.top && event.mouseButton.y <= stuff.top + stuff.height)
			metadata.callback(event);
	});
}

Button::~Button()
{
	EventManager::Unsubscribe(observer);
}

InterfaceMetadata::InterfaceMetadata(const std::string & fileName, const sf::IntRect & textureLocation, const std::string & name, const std::string & tooltip, const std::function<void(const sf::Event&)> callback) :
	fileName(fileName),
	textureLocation(textureLocation),
	name(name),
	tooltip(tooltip),
	callback(callback)
{
}
