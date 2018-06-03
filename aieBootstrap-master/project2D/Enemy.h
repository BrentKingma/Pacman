#pragma once
#include <glm/glm.hpp>
#include <Texture.h>
#include <vector>
#include "Tile.h"
class Enemy
{
public:
	Enemy() = delete;
	Enemy(glm::vec2 a_pos, aie::Texture* a_texture);
	~Enemy();

	void Translate(glm::vec2 a_move);
	void SetPath(std::vector<Tile*> a_path);

private:
	glm::vec2 m_position;
	aie::Texture* m_texture;
	std::vector<Tile*> m_path;
};

