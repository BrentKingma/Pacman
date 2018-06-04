#include "Enemy.h"
#include <Renderer2D.h>
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

void Enemy::SetPath(std::vector<Tile> a_path)
{
	m_path = a_path;
}

void Enemy::draw(aie::Renderer2D* a_renderer)
{
	a_renderer->drawSprite(m_texture, m_position.x, m_position.y);
}

void Enemy::update(float deltaTime)
{
	
	for (int i = 0; i < m_path.size(); i++)
	{
		if (glm::distance(m_position, m_path[i].GetPosition()) < 2.0f)
		{
			directionMove = glm::normalize(m_path[i + 1].GetPosition() - m_position);
			break;
		}
	}
	Translate(directionMove * 100.0f * deltaTime);
}

glm::vec2 Enemy::GetPosition()
{
	return m_position;
}
