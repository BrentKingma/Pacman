#include "Player.h"

Player::Player(glm::vec2 a_pos, aie::Texture * a_texture)
{
	m_position = a_pos;
	m_texture = a_texture;
}


Player::~Player()
{
}

void Player::Translate(glm::vec2 a_move)
{
	m_position += a_move;
}

glm::vec2 Player::GetPosition()
{
	return m_position;
}

void Player::SetPosition(glm::vec2 a_pos)
{
	m_position = a_pos;
}
