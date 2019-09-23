#include "Move.h"


Move::Move(int entityID, int movesAllowed) : Action(entityID)
{
	this->movesAllowed = movesAllowed;
	observers.push_back(EventManager::Subscribe(Click, [this](const sf::Event& event) {
		this->destination = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
	}));
}

Move::~Move()
{
}

bool Move::Show(const sf::Time& elapsedTime)
{
	if (this->destination != sf::Vector2f())
	{
		this->moves = GetPath(this->parentEntity, SpriteManager::GetSprite(this->parentEntity)->sprite->getPosition(), this->destination, true);
		this->pointsNeeded = this->moves.size();
		return true;
	}
	//sf::Vector2f destination = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	//auto moves = GetPath(parentEntity, SpriteManager::GetSprite(parentEntity)->sprite->getPosition(), destination, true);
	return false;
}

bool Move::Do(const sf::Time& elapsedTime)
{
	auto kinematics = KinematicsManager::GetKinematics(parentEntity);
	sf::Vector2f velocity = kinematics->GetVelocity();
	sf::Vector2f position = kinematics->GetPosition();
	sf::Vector2f oldPosition = position;

	//Not in new location yet
	size_t next = moves.size() - 1;
	if (velocity != sf::Vector2f() && (position.y > moves[next].y + 2 ||
		position.y < moves[next].y ||
		position.x > moves[next].x + 2 ||
		position.x < moves[next].x))
	{
		return false;
	}

	//Snap to destination tile if within tile
	else if (velocity != sf::Vector2f())
	{
		std::cout << "Snap " << moves[next].y << " " << moves[next].x << '\n';
		kinematics->SetPosition(sf::Vector2f(moves[next].x, moves[next].y));
		kinematics->SetVelocity(sf::Vector2f());
		moves.pop_back();
		return false;
	}

	else if (moves.size() > 0)
	{
		std::cout << moves.size() << "\n";
		std::cout << "Moving from (" << position.x << ", " << position.y << ") to (" << moves[moves.size() - 1].x << ", " << moves[moves.size() - 1].y << "\n";
		sf::Vector2f velocity = CalcVelocity(kinematics->GetPosition(), moves[moves.size() - 1]);
		velocity.x *= kinematics->GetBaseSpeed();
		velocity.y *= kinematics->GetBaseSpeed();

		kinematics->SetVelocity(velocity);

		return false;
	}
	else
	{
		kinematics->SetVelocity(sf::Vector2f());
		return true;
	}
}

sf::Vector2f Move::CalcVelocity(const sf::Vector2f & oldPosition, sf::Vector2f newPosition)
{
	sf::Vector2f velocity;

	float yChange = newPosition.y - oldPosition.y;
	float xChange = newPosition.x - oldPosition.x;
	float angle = atan(abs(yChange) / abs(xChange));

	velocity.y = sin(angle) / .1 * .1;
	velocity.x = cos(angle) / .1 * .1;

	if (yChange < 0)
	{
		velocity.y *= -1;
	}
	if (xChange < 0)
	{
		velocity.x *= -1;
	}

	return velocity;
}
