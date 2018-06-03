#include "Enemy.h"

Enemy::Enemy(glm::vec2 a_pos, aie::Texture * a_texture)
{
	m_position = a_pos;
	m_texture = a_texture;
}


Enemy::~Enemy()
{
}

void Enemy::Translate(glm::vec2 a_move)
{
	m_position += a_move;
}

void Enemy::SetPath(std::vector<Tile*> a_path)
{
	m_path = a_path;
}
