#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Texture.h>
class Player
{
public:
	Player() = delete;
	Player(glm::vec2 a_pos, aie::Texture* a_texture);
	~Player();

	void Translate(glm::vec2 a_move);
	glm::vec2 GetPosition();
	void SetPosition(glm::vec2 a_pos);
private:
	glm::vec2 m_position;
	aie::Texture* m_texture;
};

