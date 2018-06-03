#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <vector>
#include <algorithm>

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_fourWay = new aie::Texture("./textures/fourWay.png");
	m_straightDown = new aie::Texture("./textures/straightDown.png");
	m_straightLeft = new aie::Texture("./textures/straightLeft.png");
	m_straightRight = new aie::Texture("./textures/straightRight.png");
	m_straightUp = new aie::Texture("./textures/straightUp.png");
	m_rightTopCorner = new aie::Texture("./textures/topRightCorner.png");
	m_leftTopCorner = new aie::Texture("./textures/topLeftCorner.png");
	m_rightBottomCorner = new aie::Texture("./textures/bottomRightCorner.png");
	m_leftBottomCorner = new aie::Texture("./textures/bottomLeftCorner.png");
	m_horizontal = new aie::Texture("./textures/horizontalPath.png");
	m_vertical = new aie::Texture("./textures/verticlePath.png");
	m_grass = new aie::Texture("./textures/grass.png");
	m_sand = new aie::Texture("./textures/sand.png");
	m_playerTexture = new aie::Texture("./textures/player.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_speed = 100.0f;
	m_left = { -1, 0 };
	m_right = { 1, 0 };
	m_up = { 0, 1 };
	m_down = { 0, -1 };

	/*for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			m_tiles[i][j] = nullptr;
		}
	}*/

	startPointX = 90;
	startPointY = getWindowHeight() - 15;
	pictureWidth = 50;
	pictureHeight = 30;

	SetupMap();
	ConnectTiles();
	m_player = new Player({ startPointX, startPointY }, m_playerTexture);
	
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	m_moveQue[0] = 0;
	m_moveQue[1] = 0;

	return true;
}

void Application2D::shutdown() {
	
	
	/*for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			delete m_tiles[i][j];
		}
	}*/
	delete m_font;
	delete m_2dRenderer;
	delete m_rightTopCorner;
	delete m_leftTopCorner;
	delete m_rightBottomCorner;
	delete m_leftBottomCorner;
	delete m_fourWay;
	delete m_horizontal;
	delete m_vertical;
	delete m_straightDown;
	delete m_straightLeft;
	delete m_straightRight;
	delete m_straightUp;
	delete m_grass;
	delete m_sand;
	delete m_playerTexture;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (m_moveQue[0] == 1)
	{
		m_player->Translate(m_up * m_speed * deltaTime);
	}
	if (m_moveQue[0] == 2)
	{
		m_player->Translate(m_down * m_speed * deltaTime);
	}
	if (m_moveQue[0] == 3)
	{
		m_player->Translate(m_left * m_speed * deltaTime);
	}
	if (m_moveQue[0] == 4)
	{
		m_player->Translate(m_right * m_speed * deltaTime);
	}
	//Checks for eating pellates and resolves players movements
	for (int y = 0; y < 24; y++)
	{
		for (int x = 0; x < 23; x++)
		{
			
			if (glm::distance(m_player->GetPosition(), m_tiles[y][x]->GetPosition()) <= 5.0f)
			{
				m_tiles[y][x]->Eaten();
				if (m_moveQue[0] == 2 && m_tiles[y][x]->Down() == 0)
				{
					m_player->SetPosition(m_tiles[y][x]->GetPosition());
					m_moveQue[0] = m_moveQue[1];
					m_moveQue[1] = 0;
					break;
				}
				if (m_moveQue[0] == 1 && m_tiles[y][x]->Up() == 0)
				{
					m_player->SetPosition(m_tiles[y][x]->GetPosition());
					m_moveQue[0] = m_moveQue[1];
					m_moveQue[1] = 0;
					break;
				}
				if (m_moveQue[0] == 3 && m_tiles[y][x]->Left() == 0)
				{
					m_player->SetPosition(m_tiles[y][x]->GetPosition());
					m_moveQue[0] = m_moveQue[1];
					m_moveQue[1] = 0;
					break;
				}
				if (m_moveQue[0] == 4 && m_tiles[y][x]->Right() == 0)
				{
					m_player->SetPosition(m_tiles[y][x]->GetPosition());
					m_moveQue[0] = m_moveQue[1];
					m_moveQue[1] = 0;
					break;
				}

				if (m_moveQue[1] == 1 && m_tiles[y][x]->Up() != 0)
				{
					m_player->SetPosition(m_tiles[y][x]->GetPosition());
					m_moveQue[0] = m_moveQue[1];
					m_moveQue[1] = 0;
					break;
				}
				if (m_moveQue[1] == 2 && m_tiles[y][x]->Down() != 0)
				{
					m_player->SetPosition(m_tiles[y][x]->GetPosition());
					m_moveQue[0] = m_moveQue[1];
					m_moveQue[1] = 0;
					break;
				}
				if (m_moveQue[1] == 3 && m_tiles[y][x]->Left() != 0)
				{
					m_player->SetPosition(m_tiles[y][x]->GetPosition());
					m_moveQue[0] = m_moveQue[1];
					m_moveQue[1] = 0;
					break;
				}
				if (m_moveQue[1] == 4 && m_tiles[y][x]->Right() != 0)
				{
					m_player->SetPosition(m_tiles[y][x]->GetPosition());
					m_moveQue[0] = m_moveQue[1];
					m_moveQue[1] = 0;
					break;
				}

				if (m_moveQue[0] == 3 && m_tiles[y][x] == m_tiles[12][0])
				{
					m_player->SetPosition(m_tiles[12][22]->GetPosition());
					break;
				}
				if (m_moveQue[0] == 4 && m_tiles[y][x] == m_tiles[12][22])
				{
					m_player->SetPosition(m_tiles[12][0]->GetPosition());
					break;
				}
			}			
		}
	}

	//Adds movements to the move que
	if (input->wasKeyPressed(aie::INPUT_KEY_UP))
	{
		if (m_moveQue[0] == 0)
		{
			m_moveQue[0] = 1;
		}
		else if (m_moveQue[1] == 0)
		{
			m_moveQue[1] = 1;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
	{
		if (m_moveQue[0] == 0)
		{
			m_moveQue[0] = 2;
		}
		else if (m_moveQue[1] == 0)
		{
			m_moveQue[1] = 2;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT))
	{
		if (m_moveQue[0] == 0)
		{
			m_moveQue[0] = 3;
		}
		else if (m_moveQue[1] == 0)
		{
			m_moveQue[1] = 3;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT))
	{
		if (m_moveQue[0] == 0)
		{
			m_moveQue[0] = 4;
		}
		else if (m_moveQue[1] == 0)
		{
			m_moveQue[1] = 4;
		}
	}
	// use arrow keys to move camera
	

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw()
{
	// wipe the screen to the background colour
	clearScreen();
	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	for (int y = 0; y < 24; y++)
	{
		for (int x = 0; x < 23; x++)
		{
			if (m_tiles[y][x] != nullptr)
			{
				m_tiles[y][x]->draw(m_2dRenderer);
				m_tiles[y][x]->debug(m_2dRenderer);
			}
		}
	}

	m_2dRenderer->drawSprite(m_playerTexture, m_player->GetPosition().x, m_player->GetPosition().y);
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}

void Application2D::SetupMap()
{
	//Row 1
	m_tiles[0][0] = new Tile({ startPointX, startPointY }, m_leftTopCorner);
	m_tiles[0][1] = new Tile({ startPointX + pictureWidth, startPointY }, m_horizontal);
	m_tiles[0][2] = new Tile({ startPointX + pictureWidth * 2, startPointY }, m_horizontal);
	m_tiles[0][3] = new Tile({ startPointX + pictureWidth * 3, startPointY }, m_horizontal);
	m_tiles[0][4] = new Tile({ startPointX + pictureWidth * 4, startPointY }, m_horizontal);
	m_tiles[0][5] = new Tile({ startPointX + pictureWidth * 5, startPointY }, m_straightDown);
	m_tiles[0][6] = new Tile({ startPointX + pictureWidth * 6, startPointY }, m_horizontal);
	m_tiles[0][7] = new Tile({ startPointX + pictureWidth * 7, startPointY }, m_horizontal);
	m_tiles[0][8] = new Tile({ startPointX + pictureWidth * 8, startPointY }, m_horizontal);
	m_tiles[0][9] = new Tile({ startPointX + pictureWidth * 9, startPointY }, m_horizontal);
	m_tiles[0][10] = new Tile({ startPointX + pictureWidth * 10, startPointY }, m_rightTopCorner);
	m_tiles[0][11] = new Tile({ startPointX + pictureWidth * 11, startPointY }, m_grass, false);
	m_tiles[0][12] = new Tile({ startPointX + pictureWidth * 12, startPointY }, m_leftTopCorner);
	m_tiles[0][13] = new Tile({ startPointX + pictureWidth * 13, startPointY }, m_horizontal);
	m_tiles[0][14] = new Tile({ startPointX + pictureWidth * 14, startPointY }, m_horizontal);
	m_tiles[0][15] = new Tile({ startPointX + pictureWidth * 15, startPointY }, m_horizontal);
	m_tiles[0][16] = new Tile({ startPointX + pictureWidth * 16, startPointY }, m_horizontal);
	m_tiles[0][17] = new Tile({ startPointX + pictureWidth * 17, startPointY }, m_straightDown);
	m_tiles[0][18] = new Tile({ startPointX + pictureWidth * 18, startPointY }, m_horizontal);
	m_tiles[0][19] = new Tile({ startPointX + pictureWidth * 19, startPointY }, m_horizontal);
	m_tiles[0][20] = new Tile({ startPointX + pictureWidth * 20, startPointY }, m_horizontal);
	m_tiles[0][21] = new Tile({ startPointX + pictureWidth * 21, startPointY }, m_horizontal);
	m_tiles[0][22] = new Tile({ startPointX + pictureWidth * 22, startPointY }, m_rightTopCorner);
	//Row 2
	m_tiles[1][0] = new Tile({ startPointX, startPointY - pictureHeight }, m_vertical);
	m_tiles[1][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight }, m_vertical);
	m_tiles[1][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight }, m_vertical);
	m_tiles[1][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight }, m_vertical);
	m_tiles[1][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight }, m_vertical);
	m_tiles[1][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight }, m_grass, false);
	m_tiles[1][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight }, m_vertical);
	//Row 3
	m_tiles[2][0] = new Tile({ startPointX, startPointY - pictureHeight * 2 }, m_vertical);
	m_tiles[2][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 2 }, m_vertical);
	m_tiles[2][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 2 }, m_vertical);
	m_tiles[2][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 2 }, m_vertical);
	m_tiles[2][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 2 }, m_vertical);
	m_tiles[2][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 2 }, m_grass, false);
	m_tiles[2][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 2 }, m_vertical);
	//Row 4
	m_tiles[3][0] = new Tile({ startPointX, startPointY - pictureHeight * 3 }, m_vertical);
	m_tiles[3][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 3 }, m_vertical);
	m_tiles[3][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 3 }, m_vertical);
	m_tiles[3][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 3 }, m_vertical);
	m_tiles[3][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 3 }, m_vertical);
	m_tiles[3][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 3 }, m_grass, false);
	m_tiles[3][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 3 }, m_vertical);
	//Row 5
	m_tiles[4][0] = new Tile({ startPointX, startPointY - pictureHeight * 4 }, m_straightRight);
	m_tiles[4][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 4 }, m_fourWay);
	m_tiles[4][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 4 }, m_straightDown);
	m_tiles[4][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 4 }, m_straightUp);
	m_tiles[4][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 4 }, m_straightUp);
	m_tiles[4][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 4 }, m_straightDown);
	m_tiles[4][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 4 }, m_fourWay);
	m_tiles[4][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 4 }, m_horizontal);
	m_tiles[4][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 4 }, m_straightLeft);
	//Row 6
	m_tiles[5][0] = new Tile({ startPointX, startPointY - pictureHeight * 5 }, m_vertical);
	m_tiles[5][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 5 }, m_vertical);
	m_tiles[5][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 5 }, m_vertical);
	m_tiles[5][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 5 }, m_vertical);
	m_tiles[5][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 5 }, m_vertical);
	m_tiles[5][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 5 }, m_grass, false);
	m_tiles[5][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 5 }, m_vertical);
	//Row 7
	m_tiles[6][0] = new Tile({ startPointX, startPointY - pictureHeight * 6 }, m_vertical);
	m_tiles[6][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 6 }, m_vertical);
	m_tiles[6][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 6 }, m_vertical);
	m_tiles[6][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 6 }, m_vertical);
	m_tiles[6][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 6 }, m_vertical);
	m_tiles[6][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 6 }, m_grass, false);
	m_tiles[6][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 6 }, m_vertical);
	//Row 8
	m_tiles[7][0] = new Tile({ startPointX, startPointY - pictureHeight * 7 }, m_leftBottomCorner);
	m_tiles[7][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 7 }, m_straightLeft);
	m_tiles[7][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 7 }, m_grass, false);
	m_tiles[7][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 7 }, m_leftBottomCorner);
	m_tiles[7][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 7 }, m_rightTopCorner);
	m_tiles[7][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 7 }, m_grass, false);
	m_tiles[7][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 7 }, m_leftTopCorner);
	m_tiles[7][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 7 }, m_rightBottomCorner);
	m_tiles[7][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 7 }, m_grass, false);
	m_tiles[7][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 7 }, m_straightRight);
	m_tiles[7][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 7 }, m_horizontal);
	m_tiles[7][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 7 }, m_rightBottomCorner);
	//Row 9
	m_tiles[8][0] = new Tile({ startPointX, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 8 }, m_vertical);
	m_tiles[8][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 8 }, m_vertical, false);
	m_tiles[8][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 8 }, m_vertical, false);
	m_tiles[8][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 8 }, m_vertical);
	m_tiles[8][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 8 }, m_grass, false);
	m_tiles[8][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 8 }, m_grass, false);
	//Row 10
	m_tiles[9][0] = new Tile({ startPointX, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 9 }, m_vertical);
	m_tiles[9][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 9 }, m_leftTopCorner, false);
	m_tiles[9][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 9 }, m_horizontal, false);
	m_tiles[9][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 9 }, m_horizontal, false);
	m_tiles[9][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 9 }, m_straightUp, false);
	m_tiles[9][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 9 }, m_straightDown, false);
	m_tiles[9][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 9 }, m_straightUp, false);
	m_tiles[9][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 9 }, m_horizontal, false);
	m_tiles[9][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 9 }, m_horizontal, false);
	m_tiles[9][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 9 }, m_rightTopCorner, false);
	m_tiles[9][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 9 }, m_vertical);
	m_tiles[9][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 9 }, m_grass, false);
	m_tiles[9][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 9 }, m_grass, false);
	//Row 11
	m_tiles[10][0] = new Tile({ startPointX, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 10 }, m_vertical);
	m_tiles[10][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 10 }, m_vertical, false);
	m_tiles[10][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 10 }, m_sand, false);
	m_tiles[10][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 10 }, m_sand, false);
	m_tiles[10][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 10 }, m_sand, false);
	m_tiles[10][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 10 }, m_vertical, false);
	m_tiles[10][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 10 }, m_sand, false);
	m_tiles[10][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 10 }, m_sand, false);
	m_tiles[10][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 10 }, m_sand, false);
	m_tiles[10][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 10 }, m_vertical, false);
	m_tiles[10][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 10 }, m_vertical);
	m_tiles[10][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 10 }, m_grass, false);
	m_tiles[10][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 10 }, m_grass, false);
	//Row 12
	m_tiles[11][0] = new Tile({ startPointX, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 11 }, m_vertical);
	m_tiles[11][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 11 }, m_vertical, false);
	m_tiles[11][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 11 }, m_sand, false);
	m_tiles[11][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 11 }, m_leftTopCorner, false);
	m_tiles[11][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 11 }, m_horizontal, false);
	m_tiles[11][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 11 }, m_fourWay, false);
	m_tiles[11][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 11 }, m_horizontal, false);
	m_tiles[11][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 11 }, m_rightTopCorner, false);
	m_tiles[11][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 11 }, m_sand, false);
	m_tiles[11][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 11 }, m_vertical, false);
	m_tiles[11][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 11 }, m_vertical);
	m_tiles[11][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 11 }, m_grass, false);
	m_tiles[11][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 11 }, m_grass, false);
	//Row 13
	m_tiles[12][0] = new Tile({ startPointX, startPointY - pictureHeight * 12 }, m_horizontal, true, true);
	m_tiles[12][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 12 }, m_horizontal);
	m_tiles[12][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 12 }, m_horizontal);
	m_tiles[12][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 12 }, m_horizontal);
	m_tiles[12][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 12 }, m_horizontal);
	m_tiles[12][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 12 }, m_fourWay);
	m_tiles[12][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 12 }, m_horizontal, false);
	m_tiles[12][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 12 }, m_straightLeft, false);
	m_tiles[12][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 12 }, m_sand, false);
	m_tiles[12][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 12 }, m_vertical, false);
	m_tiles[12][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 12 }, m_grass, false);
	m_tiles[12][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 12 }, m_vertical, false);
	m_tiles[12][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 12 }, m_grass, false);
	m_tiles[12][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 12 }, m_vertical, false);
	m_tiles[12][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 12 }, m_sand, false);
	m_tiles[12][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 12 }, m_straightRight, false);
	m_tiles[12][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 12 }, m_horizontal, false);
	m_tiles[12][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 12 }, m_fourWay);
	m_tiles[12][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 12 }, m_horizontal);
	m_tiles[12][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 12 }, m_horizontal);
	m_tiles[12][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 12 }, m_horizontal);
	m_tiles[12][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 12 }, m_horizontal);
	m_tiles[12][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 12 }, m_horizontal, true, true);
	//Row 14
	m_tiles[13][0] = new Tile({ startPointX, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 13 }, m_vertical);
	m_tiles[13][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 13 }, m_vertical, false);
	m_tiles[13][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 13 }, m_sand, false);
	m_tiles[13][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 13 }, m_leftBottomCorner, false);
	m_tiles[13][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 13 }, m_horizontal, false);
	m_tiles[13][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 13 }, m_straightUp, false);
	m_tiles[13][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 13 }, m_horizontal, false);
	m_tiles[13][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 13 }, m_rightBottomCorner, false);
	m_tiles[13][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 13 }, m_sand, false);
	m_tiles[13][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 13 }, m_vertical, false);
	m_tiles[13][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 13 }, m_vertical);
	m_tiles[13][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 13 }, m_grass, false);
	m_tiles[13][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 13 }, m_grass, false);
	//Row 15
	m_tiles[14][0] = new Tile({ startPointX, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 14 }, m_vertical);
	m_tiles[14][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 14 }, m_vertical, false);
	m_tiles[14][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 14 }, m_sand, false);
	m_tiles[14][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 14 }, m_sand, false);
	m_tiles[14][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 14 }, m_sand, false);
	m_tiles[14][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 14 }, m_sand, false);
	m_tiles[14][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 14 }, m_sand, false);
	m_tiles[14][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 14 }, m_sand, false);
	m_tiles[14][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 14 }, m_sand, false);
	m_tiles[14][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 14 }, m_vertical, false);
	m_tiles[14][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 14 }, m_vertical);
	m_tiles[14][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 14 }, m_grass, false);
	m_tiles[14][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 14 }, m_grass, false);
	//Row 16
	m_tiles[15][0] = new Tile({ startPointX, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 15 }, m_vertical);
	m_tiles[15][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 15 }, m_straightRight, false);
	m_tiles[15][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 15 }, m_horizontal, false);
	m_tiles[15][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 15 }, m_horizontal, false);
	m_tiles[15][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 15 }, m_horizontal, false);
	m_tiles[15][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 15 }, m_horizontal, false);
	m_tiles[15][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 15 }, m_horizontal, false);
	m_tiles[15][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 15 }, m_horizontal, false);
	m_tiles[15][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 15 }, m_horizontal, false);
	m_tiles[15][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 15 }, m_straightLeft, false);
	m_tiles[15][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 15 }, m_vertical);
	m_tiles[15][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 15 }, m_grass, false);
	m_tiles[15][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 15 }, m_grass, false);
	//Row 17
	m_tiles[16][0] = new Tile({ startPointX, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 16 }, m_vertical);
	m_tiles[16][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 16 }, m_vertical, false);
	m_tiles[16][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 16 }, m_vertical, false);
	m_tiles[16][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 16 }, m_vertical);
	m_tiles[16][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 16 }, m_grass, false);
	m_tiles[16][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 16 }, m_grass, false);
	//Row 18
	m_tiles[17][0] = new Tile({ startPointX, startPointY - pictureHeight * 17 }, m_leftTopCorner);
	m_tiles[17][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 17 }, m_fourWay);
	m_tiles[17][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 17 }, m_straightUp);
	m_tiles[17][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 17 }, m_rightTopCorner);
	m_tiles[17][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 17 }, m_grass, false);
	m_tiles[17][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 17 }, m_leftTopCorner);
	m_tiles[17][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 17 }, m_straightUp);
	m_tiles[17][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 17 }, m_fourWay);
	m_tiles[17][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 17 }, m_horizontal);
	m_tiles[17][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 17 }, m_rightTopCorner);
	//Row 19
	m_tiles[18][0] = new Tile({ startPointX, startPointY - pictureHeight * 18 }, m_vertical);
	m_tiles[18][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 18 }, m_vertical);
	m_tiles[18][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 18 }, m_vertical);
	m_tiles[18][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 18 }, m_vertical);
	m_tiles[18][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 18 }, m_vertical);
	m_tiles[18][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 18 }, m_grass, false);
	m_tiles[18][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 18 }, m_vertical);
	//Row 20
	m_tiles[19][0] = new Tile({ startPointX, startPointY - pictureHeight * 19 }, m_vertical);
	m_tiles[19][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 19 }, m_vertical);
	m_tiles[19][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 19 }, m_vertical);
	m_tiles[19][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 19 }, m_vertical);
	m_tiles[19][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 19 }, m_vertical);
	m_tiles[19][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 19 }, m_grass, false);
	m_tiles[19][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 19 }, m_vertical);
	//Row 21
	m_tiles[20][0] = new Tile({ startPointX, startPointY - pictureHeight * 20 }, m_leftBottomCorner);
	m_tiles[20][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 20 }, m_horizontal);
	m_tiles[20][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 20 }, m_rightTopCorner);
	m_tiles[20][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 20 }, m_grass, false);
	m_tiles[20][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 20 }, m_grass, false);
	m_tiles[20][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 20 }, m_straightRight);
	m_tiles[20][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 20 }, m_horizontal);
	m_tiles[20][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 20 }, m_straightDown);
	m_tiles[20][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 20 }, m_horizontal);
	m_tiles[20][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 20 }, m_horizontal);
	m_tiles[20][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 20 }, m_straightUp);
	m_tiles[20][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 20 }, m_horizontal);
	m_tiles[20][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 20 }, m_straightUp);
	m_tiles[20][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 20 }, m_horizontal);
	m_tiles[20][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 20 }, m_horizontal);
	m_tiles[20][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 20 }, m_straightDown);
	m_tiles[20][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 20 }, m_horizontal);
	m_tiles[20][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 20 }, m_straightLeft);
	m_tiles[20][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 20 }, m_grass, false);
	m_tiles[20][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 20 }, m_grass, false);
	m_tiles[20][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 20 }, m_leftTopCorner);
	m_tiles[20][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 20 }, m_horizontal);
	m_tiles[20][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 20 }, m_rightBottomCorner);
	//Row 22
	m_tiles[21][0] = new Tile({ startPointX, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 21 }, m_vertical);
	m_tiles[21][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 21 }, m_vertical);
	m_tiles[21][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 21 }, m_vertical);
	m_tiles[21][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 21 }, m_vertical);
	m_tiles[21][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 21 }, m_vertical);
	m_tiles[21][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 21 }, m_vertical);
	m_tiles[21][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 21 }, m_grass, false);
	m_tiles[21][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 21 }, m_grass, false);
	//Row 23
	m_tiles[22][0] = new Tile({ startPointX, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 22 }, m_vertical);
	m_tiles[22][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 22 }, m_vertical);
	m_tiles[22][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 22 }, m_vertical);
	m_tiles[22][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 22 }, m_vertical);
	m_tiles[22][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 22 }, m_vertical);
	m_tiles[22][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 22 }, m_vertical);
	m_tiles[22][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 22 }, m_grass, false);
	m_tiles[22][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 22 }, m_grass, false);
	//Row 24
	m_tiles[23][0] = new Tile({ startPointX, startPointY - pictureHeight * 23 }, m_grass, false);
	m_tiles[23][1] = new Tile({ startPointX + pictureWidth, startPointY - pictureHeight * 23 }, m_grass, false);
	m_tiles[23][2] = new Tile({ startPointX + pictureWidth * 2, startPointY - pictureHeight * 23 }, m_leftBottomCorner);
	m_tiles[23][3] = new Tile({ startPointX + pictureWidth * 3, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][4] = new Tile({ startPointX + pictureWidth * 4, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][5] = new Tile({ startPointX + pictureWidth * 5, startPointY - pictureHeight * 23 }, m_straightUp);
	m_tiles[23][6] = new Tile({ startPointX + pictureWidth * 6, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][7] = new Tile({ startPointX + pictureWidth * 7, startPointY - pictureHeight * 23 }, m_straightUp);
	m_tiles[23][8] = new Tile({ startPointX + pictureWidth * 8, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][9] = new Tile({ startPointX + pictureWidth * 9, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][10] = new Tile({ startPointX + pictureWidth * 10, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][11] = new Tile({ startPointX + pictureWidth * 11, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][12] = new Tile({ startPointX + pictureWidth * 12, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][13] = new Tile({ startPointX + pictureWidth * 13, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][14] = new Tile({ startPointX + pictureWidth * 14, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][15] = new Tile({ startPointX + pictureWidth * 15, startPointY - pictureHeight * 23 }, m_straightUp);
	m_tiles[23][16] = new Tile({ startPointX + pictureWidth * 16, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][17] = new Tile({ startPointX + pictureWidth * 17, startPointY - pictureHeight * 23 }, m_straightUp);
	m_tiles[23][18] = new Tile({ startPointX + pictureWidth * 18, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][19] = new Tile({ startPointX + pictureWidth * 19, startPointY - pictureHeight * 23 }, m_horizontal);
	m_tiles[23][20] = new Tile({ startPointX + pictureWidth * 20, startPointY - pictureHeight * 23 }, m_rightBottomCorner);
	m_tiles[23][21] = new Tile({ startPointX + pictureWidth * 21, startPointY - pictureHeight * 23 }, m_grass, false);
	m_tiles[23][22] = new Tile({ startPointX + pictureWidth * 22, startPointY - pictureHeight * 23 }, m_grass, false);
}

void Application2D::ConnectTiles()
{
	for (int y = 0; y < 24; y++)
	{
		for (int x = 0; x < 23; x++)
		{
			//The four corners connections
			if (m_tiles[y][x]->GetTexture()->getFilename() == m_leftTopCorner->getFilename())
			{
				m_tiles[y][x]->LinkConnection(4, m_tiles[y][x + 1]);
				m_tiles[y][x]->LinkConnection(2, m_tiles[y + 1][x]);
			}
			else if (m_tiles[y][x]->GetTexture()->getFilename() == m_leftBottomCorner->getFilename())
			{
				m_tiles[y][x]->LinkConnection(4, m_tiles[y][x + 1]);
				m_tiles[y][x]->LinkConnection(1, m_tiles[y - 1][x]);
			}
			else if (m_tiles[y][x]->GetTexture()->getFilename() == m_rightTopCorner->getFilename())
			{
				m_tiles[y][x]->LinkConnection(3, m_tiles[y][x - 1]);
				m_tiles[y][x]->LinkConnection(2, m_tiles[y + 1][x]);
			}
			else if (m_tiles[y][x]->GetTexture()->getFilename() == m_rightBottomCorner->getFilename())
			{
				m_tiles[y][x]->LinkConnection(3, m_tiles[y][x - 1]);
				m_tiles[y][x]->LinkConnection(1, m_tiles[y - 1][x]);
			}
			//Vertical and Horizontal
			else if (m_tiles[y][x]->GetTexture()->getFilename() == m_vertical->getFilename())
			{
				m_tiles[y][x]->LinkConnection(1, m_tiles[y - 1][x]);
				m_tiles[y][x]->LinkConnection(2, m_tiles[y + 1][x]);
			}
			else if (m_tiles[y][x]->GetTexture()->getFilename() == m_horizontal->getFilename() && !m_tiles[y][x]->IsTeleporter())
			{
				m_tiles[y][x]->LinkConnection(4, m_tiles[y][x + 1]);
				m_tiles[y][x]->LinkConnection(3, m_tiles[y][x - 1]);
			}
			//Fourway
			else if (m_tiles[y][x]->GetTexture()->getFilename() == m_fourWay->getFilename())
			{
				m_tiles[y][x]->LinkConnection(1, m_tiles[y - 1][x]);
				m_tiles[y][x]->LinkConnection(3, m_tiles[y][x - 1]);
				m_tiles[y][x]->LinkConnection(4, m_tiles[y][x + 1]);
				m_tiles[y][x]->LinkConnection(2, m_tiles[y + 1][x]);
			}
			//Straights
			else if (m_tiles[y][x]->GetTexture()->getFilename() == m_straightDown->getFilename())
			{
				m_tiles[y][x]->LinkConnection(3, m_tiles[y][x - 1]);
				m_tiles[y][x]->LinkConnection(4, m_tiles[y][x + 1]);
				m_tiles[y][x]->LinkConnection(2, m_tiles[y + 1][x]);
			}
			else if (m_tiles[y][x]->GetTexture()->getFilename() == m_straightLeft->getFilename())
			{
				m_tiles[y][x]->LinkConnection(1, m_tiles[y - 1][x]);
				m_tiles[y][x]->LinkConnection(3, m_tiles[y][x - 1]);
				m_tiles[y][x]->LinkConnection(2, m_tiles[y + 1][x]);
			}
			else if (m_tiles[y][x]->GetTexture()->getFilename() == m_straightRight->getFilename())
			{
				m_tiles[y][x]->LinkConnection(1, m_tiles[y - 1][x]);
				m_tiles[y][x]->LinkConnection(4, m_tiles[y][x + 1]);
				m_tiles[y][x]->LinkConnection(2, m_tiles[y + 1][x]);
			}
			else if (m_tiles[y][x]->GetTexture()->getFilename() == m_straightUp->getFilename())
			{
				m_tiles[y][x]->LinkConnection(3, m_tiles[y][x - 1]);
				m_tiles[y][x]->LinkConnection(4, m_tiles[y][x + 1]);
				m_tiles[y][x]->LinkConnection(1, m_tiles[y - 1][x]);
			}
		}
	}
	m_tiles[12][0]->LinkConnection(3, m_tiles[12][22]);
	m_tiles[12][0]->LinkConnection(4, m_tiles[12][1]);
	m_tiles[12][22]->LinkConnection(3, m_tiles[12][21]);
	m_tiles[12][22]->LinkConnection(4, m_tiles[12][0]);
}

void Application2D::AStar(Tile* a_starting, Tile* a_target, Enemy* a_enemy)
{
	std::vector<Tile> tempList;
	std::vector<Tile> closedList;

	tempList.push_back(*a_starting);

	while (tempList.size() > 0)
	{
		Tile currentTile = tempList[0];
		currentTile.SetHScore(GetChebyshevDistance(currentTile, *a_target));
		for (int i = 0; i < tempList.size(); i++)
		{
			if (tempList[i].GetFScore() < currentTile.GetFScore() || (tempList[i].GetFScore() == currentTile.GetFScore() && tempList[i].GetFScore() < currentTile.GetFScore()))
			{
				currentTile = tempList[i];
			}
		}

		closedList.push_back(currentTile);
		tempList.pop_back();

		if (&currentTile == a_target)
		{

		}
	}
}

float Application2D::GetChebyshevDistance(Tile a, Tile b)
{
	float dx = glm::abs(a.GetPosition().x - b.GetPosition().x);
	float dy = glm::abs(a.GetPosition().y - b.GetPosition().y);

	return 10 * (dx + dy) + (14 - 2 * 10) * std::min(dx, dy);
}

void Application2D::RetracePath(Tile start, Tile end)
{
	std::vector<Tile> path;
	Tile current = end;

	while (&current != &start)
	{
		path.push_back(current);
		current = *current.GetParent();
	}

	path.
}


