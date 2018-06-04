#pragma once
#include <Texture.h>
#include <glm/glm.hpp>
namespace aie
{
	class Renderer2D;
}
class Tile
{
public:
	Tile() = delete;
	Tile(glm::vec2 a_position, aie::Texture* a_texture, bool a_hasFood = true, bool a_isTeleport = false);
	~Tile();
	//1: Up Connection
	//2: Down Connection
	//3: Left Connection
	//4: Right Connection
	void LinkConnection(int a_num, Tile* a_tile);
	void draw(aie::Renderer2D* a_renderer);
	void debug(aie::Renderer2D* a_renderer);
	void Eaten();
	glm::vec2 GetPosition();
	aie::Texture* GetTexture();
	bool IsTeleporter();

	Tile* Up();
	Tile* Down();
	Tile* Left();
	Tile* Right();

	Tile* GetConnections(int a_num);

	void SetGScore(float a_value);
	void SetHScore(float a_value);
	void SetFScore(float a_value);

	float GetFScore();
	float GetHScore();
	float GetGScore();

	void SetParent(Tile* a_parent);

	Tile* GetParent();


private:
	aie::Texture* m_texture;

	/*Tile* m_upConnection = nullptr;
	Tile* m_leftConnection = nullptr;
	Tile* m_rightConnection = nullptr;
	Tile* m_downConnection = nullptr;*/

	//1: Up
	//2: Down
	//3: Left
	//4: Right
	Tile* m_connections[4];
	Tile* m_aiParent = nullptr;

	glm::vec2 m_position;

	bool m_hasBeenEaten = false;
	bool m_hasFood;
	bool m_isTeleport;

	float m_gScore;
	float m_hScore;
	float m_fScore;
};

