#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"
#include <Windows.h>

using namespace std;

using uint = unsigned int;
uint startTime = SDL_GetTicks();
uint frameTime;

Game::Game() {
	initSDL();
	initTextures(); //Iniciar texturas
	initObjects();
}

void Game::initSDL() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SDL ARKANOID", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) cout << "Error cargando SDL" << endl;
	//Las excepciones se deben lanzar con un throw, creando su clase respectiva para excepciones
}

void Game::initTextures() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		nTexturas[i] = new Texture(renderer);
		nTexturas[i]->load(IMAGES_PATH + TEXT_ATT[i].nombre, TEXT_ATT[i].row, TEXT_ATT[i].col);
		if (nTexturas[i] == nullptr) cout << "Error cargando la textura numero " + i << endl;
	}
}

void Game::initObjects() {
	//Aqui los objetos del juego
	paddle = new Paddle(renderer, nTexturas[TPaddle]);
	wallL = new Wall(renderer, nTexturas[TSide], Vector2D(0, 0), false);
	wallR = new Wall(renderer, nTexturas[TSide], Vector2D(WIN_WIDTH - WALL_WIDTH, 0), false);
	roof = new Wall(renderer, nTexturas[TTopSide], Vector2D(0, 0), true);
	ball = new Ball(renderer, nTexturas[TBall], this);
	mapita = new BlockMap(renderer, nTexturas[TBrick]);
	mapita->load(maps[Lv1]);
}

void Game::run() {
	while (!exit && !win) {
		handleEvents();
		update();
		render();
		Sleep(FRAME_RATE);
	}
}

void Game::update() {
	//Update de los objetos 
	paddle->update();
	ball->update();

	//Comprobacion de victoria
	if (mapita->getNumBlocks() == 0) {
		nextLevel();
		if (level > 3) win = true;
	}
}

void Game::nextLevel() {
	level++;
	switch (level)	{
	case 1:
		mapita->load(maps[Lv1]);
		break;
	case 2:
		mapita->load(maps[Lv2]);
		break;
	case 3:
		mapita->load(maps[Lv3]);
		break;
	default:
		mapita->load(maps[Lv1]);
		break;
	}
	ball->respawn();
}

void Game::render() const {
	SDL_RenderClear(renderer); //Eliminamos lo que hay en pantalla
	//Render de cada objeto
	paddle->render();
	wallL->render();
	wallR->render();
	roof->render();
	mapita->render();
	ball->render();

	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		//Mas eventos de teclado
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: //Para salir con esc
				exit = true;
				break;
			default:
				break;
			}
		}
		//Eventos de cada obejeto
		paddle->handleEvents(event);
	}
}

void Game::pierdeVida() {
	vidas--;
	ball->respawn();
	if (vidas == 0) {
		exit = true;
	}
}

bool Game::collides(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector) {
	bool c = false;

	//Caso especial en caso de bug y que se salga de la pantalla, para poder seguir jugando(no se deberia llamar nunca)
	if (rect.x < 0 || rect.y < 0) {
		c = true;
		pierdeVida();
	}

	//Colisiones con muros
	if (rect.y - WALL_WIDTH < 5) {//Muro de arriba
		c = true;
		collVector = { 0, -1 };
	}
	else if (rect.y > WIN_HEIGHT - 20) { //game over (Parte inferior)
		c = true;
		pierdeVida();
	}
	else if ((rect.x + rect.w) - (WIN_WIDTH - WALL_WIDTH) < 5) { 
		c = true;
		collVector = { -1, 0 };
	}
	else if (rect.x - WALL_WIDTH < 5) {
		c = true;
		collVector = { 1, 0 };
	}

	//Colisiones con Bloques
	Block* block = nullptr;
	block = mapita->collides(rect, vel, collVector);
	if (block != nullptr) {
		if (block->getActive()) {
			mapita->ballHitsBlock(block);
			c = true;
		}
	}
	//---------------

	//Colisiones con paddle
	if (paddle->collides(rect, collVector)) {
		c = true;
	}

	return c;
}

Game::~Game() {
	deleteTextures();	//Eliminar las texturas del array de texturas

	delete paddle;    paddle = nullptr;
	delete wallL;    wallL = nullptr;
	delete wallR;    wallR = nullptr;
	delete roof;    roof = nullptr;
	delete ball;    ball = nullptr;
	delete mapita;    mapita = nullptr;
	//delete block;    block = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

void Game::deleteTextures() {
	for (auto i : nTexturas) {
		delete i;
		i = nullptr;
	}
}