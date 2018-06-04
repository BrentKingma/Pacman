#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	
	aie::Texture* m_rightTopCorner;
	aie::Texture* m_leftTopCorner;
	aie::Texture* m_rightBottomCorner;
	aie::Texture* m_leftBottomCorner;
	aie::Texture* m_fourWay;
	aie::Texture* m_horizontal;
	aie::Texture* m_vertical;
	aie::Texture* m_straightDown;
	aie::Texture* m_straightLeft;
	aie::Texture* m_straightRight;
	aie::Texture* m_straightUp;
	aie::Texture* m_grass;
	aie::Texture* m_sand;
	aie::Texture* m_playerTexture;
	aie::Texture* m_enemyTexture;

	aie::Font*			m_font;

	Tile* m_tiles[24][23];

	Player* m_player;
	Enemy* m_enemy;

	glm::vec2 m_left;
	glm::vec2 m_right;
	glm::vec2 m_up;
	glm::vec2 m_down;

	float m_cameraX, m_cameraY;
	float m_timer;
	float m_speed;

	bool m_movingLeft = false;
	bool m_movingRight = false;
	bool m_movingUp = false;
	bool m_movingDown = false;
	//1: Up
	//2: Down
	//3: Left
	//4: Right
	int m_moveQue[2];

	int startPointX;
	int startPointY;
	int pictureWidth;
	int pictureHeight;
	bool test = true;

	void SetupMap();
	void ConnectTiles();
	void AStar(Tile* a_starting, Tile* a_target, Enemy* a_enemy);
	float GetChebyshevDistance(Tile a, Tile b);
	std::vector<Tile> RetracePath(Tile* start, Tile* end);
	bool Contains(std::vector<Tile*> a_list, Tile* a_tile);
	Tile* GetTileAtEnemyPosition(Enemy* a_enemy);
	Tile* GetTileAtPlayerPosition(Player* a_player);
};