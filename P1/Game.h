#pragma once
#include "checkML.h"
#include "Texture.h"
#include "GameObject.h"
#include <list>
#include <SDL_ttf.h>	//Para textos

#include "BlockMap.h"
#include "Wall.h"
#include "Paddle.h"
#include "Ball.h"
#include "RewardX4.h"
#include "RewardX3.h"
#include "RewardX2.h"
#include "RewardX1.h"

const uint NUM_TEXTURES = 6;
const uint NUM_OBJECTS = 6;
const uint NUM_MAPS = 3;
const uint FRAME_RATE = 10;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const string IMAGES_PATH = "../images/";
const string FONT = "";
const string SAVEFILE = "../images/save.ark";

const uint WALL_WIDTH = 40;
const uint PADDLE_MOVE = 5;
const uint BALL_SIZE = 25;
const uint REWARD_W = 30;
const uint REWARD_H = 20;
const uint REWARD_CHANCE = 5;

//Constantes de posiciones de los objetos
const Vector2D POS_WALL_L_ROOF = Vector2D(0, 0);
const Vector2D POS_WALL_R = Vector2D(WIN_WIDTH - WALL_WIDTH, 0);

enum Textures_T {TBrick, TPaddle, TBall, TSide, TTopSide, TReward};
enum Maps_T {Lv1, Lv2, Lv3};

struct TextureAtributtes {
	string nombre;
	int row;
	int col;
};

const TextureAtributtes TEXT_ATT[NUM_TEXTURES] = {
	{"bricks.png", 2, 3}, {"paddle.png", 1, 1}, 
	{"ball.png", 1, 1}, {"side.png", 1, 1}, 
	{"topside.png", 1, 1}, {"rewards.png", 10, 8}
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
	
	//Constructoras
	void initTextures();
	void initObjects();
	void initObjectsFromFile(const ifstream& f);
	void initMap();

	//Destructoras
	void deleteTextures();
	void deleteObjects();

	//Colisiones
	bool collidesBall(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector);
	bool collidesReward(const SDL_Rect& rect);
	//Variados
	void createReward(const SDL_Rect& rect);
	void powerUp(int type);
	void addLife() { vidas++; }
	void pierdeVida();
	void nextLevel();
	void setLevel(bool b) { nivel = b; }
	//Guardar y cargar
	void save(const string& filename);
	void load();

protected:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect scoreRect;

	bool exit = false, win = false;
	int vidas = 3;
	int level = 0;
	int puntuacion = 0;

	Texture* nTexturas[NUM_TEXTURES];
	list<ArkanoidObject*> objects, killObjects;

private:
	BlockMap* blockMap;
	list<ArkanoidObject*>::iterator mapIt, paddleIt, ballIt, lastIt;
	bool nivel = false, saveState = false;
	Texture* tScore;
	SDL_Color red = { 255, 0, 0 }; //The color of the font
	TTF_Font* font;

	int numCodes = 0, code = 0;
};