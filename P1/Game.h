#pragma once
#include "checkML.h"
#include "Texture.h"
#include "GameObject.h"

#include "BlockMap.h"
#include "Wall.h"
#include "Paddle.h"
#include "Ball.h"

const uint NUM_TEXTURES = 5;
const uint NUM_OBJECTS = 5;
const uint NUM_MAPS = 3;
const uint FRAME_RATE = 10;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const string IMAGES_PATH = "../images/";

const uint WALL_WIDTH = 40;
const uint PADDLE_MOVE = 5;
const uint BALL_SIZE = 25;

//Constantes de posiciones de los objetos
const Vector2D POS_WALL_L_ROOF = Vector2D(0, 0);
const Vector2D POS_WALL_R = Vector2D(WIN_WIDTH - WALL_WIDTH, 0);

enum Objects_T {WallL, WallR, Roof, Map, Player};
enum Textures_T {TBrick, TPaddle, TBall, TSide, TTopSide};
enum Maps_T {Lv1, Lv2, Lv3};

struct TextureAtributtes {
	string nombre;
	int row;
	int col;
};

const TextureAtributtes TEXT_ATT[NUM_TEXTURES] = {
	{"bricks.png", 2, 3}, {"paddle.png", 1, 1}, 
	{"ball.png", 1, 1}, {"side.png", 1, 1}, 
	{"topside.png", 1, 1} 
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
	GameObject* Objects[NUM_OBJECTS];

private:
	Paddle* paddle = nullptr;
	GameObject* wallL = nullptr;
	GameObject* wallR = nullptr;
	GameObject* roof = nullptr;
	Ball* ball = nullptr;
	GameObject* mapita = nullptr;
};