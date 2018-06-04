#pragma once
#include <glm/glm.hpp>
#include <Texture.h>
#include <vector>
#include "Tile.h"

namespace aie
{
	class Renderer2D;
}
class Enemy
{
public:
	Enemy() = delete;
	Enemy(glm::vec2 a_pos, aie::Texture* a_texture);
	~Enemy();

	void Translate(glm::vec2 a_move);
	void SetPath(std::vector<Tile> a_path);
	void draw(aie::Renderer2D* a_renderer);
	void update(float deltaTime);

	glm::vec2 GetPosition();

private:
	glm::vec2 directionMove;
	glm::vec2 m_position;
	aie::Texture* m_texture;
	std::vector<Tile> m_path;
};

