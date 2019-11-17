#pragma once
#include "Agent.h"
#include <string>
#include <glm/glm.hpp>
#include "InputManager.h"
class Food
{
private:
	float speed;
	std::string texture;
	int textureID;
	glm::vec2 position;

public:
	Food(float _speed, std::string texture);
	void draw(SpriteBacth& spriteBatch);
	void setColor(ColorRGBA color);
	glm::vec2 getPosition()const {
		return position;
	}
	void update();
	~Food();

};

