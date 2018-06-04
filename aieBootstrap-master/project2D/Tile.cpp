#include "Tile.h"
#include <Renderer2D.h>
#include <Gizmos.h>


Tile::Tile(glm::vec2 a_position, aie::Texture* a_texture, bool a_hasFood, bool a_isTeleport)
{
	m_position = a_position;
	m_texture = a_texture;
	m_hasFood = a_hasFood;
	m_isTeleport = a_isTeleport;

	m_gScore = 0;
	m_hScore = 0;

	m_connections[0] = nullptr;
	m_connections[1] = nullptr;
	m_connections[2] = nullptr;
	m_connections[3] = nullptr;
}


Tile::~Tile()
{
}

void Tile::LinkConnection(int a_num, Tile * a_tile)
{
	switch (a_num)
	{
	case 1:
		m_connections[0] = a_tile;
		break;
	case 2:
		m_connections[1] = a_tile;
		break;
	case 3:
		m_connections[2] = a_tile;
		break;
	case 4:
		m_connections[3] = a_tile;
		break;
	default:
		break;
	}
}

void Tile::draw(aie::Renderer2D * a_renderer)
{
	a_renderer->drawSprite(m_texture, m_position.x, m_position.y, 50, 30);
	if (!m_hasBeenEaten && m_hasFood == true)
	{
		a_renderer->drawCircle(m_position.x, m_position.y, 5);
	}
}

void Tile::debug(aie::Renderer2D* a_renderer)
{
	if (m_connections[0] != nullptr)
	{
		a_renderer->drawLine(m_position.x, m_position.y, m_connections[0]->GetPosition().x, m_connections[0]->GetPosition().y);
	}
	if (m_connections[1] != nullptr)
	{
		a_renderer->drawLine(m_position.x, m_position.y, m_connections[1]->GetPosition().x, m_connections[1]->GetPosition().y);
	}
	if (m_connections[2] != nullptr)
	{
		a_renderer->drawLine(m_position.x, m_position.y, m_connections[2]->GetPosition().x, m_connections[2]->GetPosition().y);
	}
	if (m_connections[3] != nullptr)
	{
		a_renderer->drawLine(m_position.x, m_position.y, m_connections[3]->GetPosition().x, m_connections[3]->GetPosition().y);
	}
}

void Tile::Eaten()
{
	m_hasBeenEaten = true;
}

glm::vec2 Tile::GetPosition()
{
	return m_position;
}

aie::Texture * Tile::GetTexture()
{
	return m_texture;
}

bool Tile::IsTeleporter()
{
	return m_isTeleport;
}

Tile * Tile::Up()
{
	if (m_connections[0] != nullptr)
	{
		return m_connections[0];
	}
	return 0;
}

Tile * Tile::Down()
{
	if (m_connections[1] != nullptr)
	{
		return m_connections[1];
	}
	return 0;
}

Tile * Tile::Left()
{
	if (m_connections[2] != nullptr)
	{
		return m_connections[2];
	}
	return 0;
}

Tile * Tile::Right()
{
	if (m_connections[3] != nullptr)
	{
		return m_connections[3];
	}
	return 0;
}

Tile* Tile::GetConnections(int a_num)
{
	return m_connections[a_num];
}

void Tile::SetGScore(float a_value)
{
	m_gScore = a_value;
}

void Tile::SetHScore(float a_value)
{
	m_hScore = a_value;
}

void Tile::SetFScore(float a_value)
{
	m_fScore = a_value;
}

float Tile::GetFScore()
{
	return m_fScore;
}

float Tile::GetHScore()
{
	return m_hScore;
}

float Tile::GetGScore()
{
	return m_gScore;
}

void Tile::SetParent(Tile * a_parent)
{
	m_aiParent = a_parent;
}

Tile * Tile::GetParent()
{
	return m_aiParent;
}
