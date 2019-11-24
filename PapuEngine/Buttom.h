#pragma once
#include "SpriteBacth.h"
#include "GLTexture.h"
#include <string>
#include <glm/glm.hpp>


class Buttom
{
private:
	std::string texture;
	int textureID;
	glm::vec2 position;

public:

	Buttom(std::string texture, glm::vec2 pos);
	void draw(SpriteBacth& spriteBatch);
	void setColor(ColorRGBA color);

	bool cliked(glm::vec2 position, glm::vec2 windowSize);
	void setPosition(glm::vec2 position);
	glm::vec2 getPosition()const {
		return position;
	}

	~Buttom();
};

