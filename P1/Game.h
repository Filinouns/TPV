#pragma once
#include "checkML.h"
#include "Texture.h"
#include "Paddle.h"
#include "Wall.h"
#include "Block.h"
#include "Ball.h"
#include "BlockMap.h"

const uint NUM_TEXTURES = 6;
const uint NUM_MAPS = 3;
const uint FRAME_RATE = 10;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint PADDLE_MOVE = 5;
const uint BALL_SIZE = 25;
const string IMAGES_PATH = "../images/";


enum Textures_T {TDog, TBrick, TPaddle, TBall, TSide, TTopSide};
enum Maps_T {Lv1, Lv2, Lv3};

struct TextureAtributtes {
	string nombre;
	int row;
	int col;
};

const TextureAtributtes TEXT_ATT[NUM_TEXTURES] = {
	{"dog.png", 1, 6}, {"bricks.png", 2, 3}, 
	{"paddle.png", 1, 1}, {"ball.png", 1, 1}, 
	{"side.png", 1, 1}, {"topside.png", 1, 1} 
};

const string maps[NUM_MAPS] = {
	{ "../images/level01.ark" },
	{ "../images/level02.ark" },
	{ "../images/level03.ark" }
};

class Game {
public:
	Game();
	~Game();

	void initSDL();
	void run();
	void handleEvents();
	void update();
	void render() const;
	
	void initTextures();
	void initObjects();
	void deleteTextures();
	bool collides(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector);

	void pierdeVida();
	void nextLevel();
protected:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//Aqui punteros a las clases de objetos
	bool exit = false, win = false;
	int vidas = 3;
	int level = 1;
	Texture* nTexturas[NUM_TEXTURES];

private:
	Paddle* paddle = nullptr;
	Wall* wallL = nullptr;
	Wall* wallR = nullptr;
	Wall* roof = nullptr;
	Block* block = nullptr;
	Ball* ball = nullptr;
	BlockMap* mapita = nullptr;
};