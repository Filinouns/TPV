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
	//textures.resize(NUM_TEXTURES);
	for (int i = 0; i < NUM_TEXTURES; i++) {
		nTexturas[i] = new Texture(renderer);
		nTexturas[i]->load(IMAGES_PATH + TEXT_ATT[i].nombre, TEXT_ATT[i].row, TEXT_ATT[i].col);
		if (nTexturas[i] == nullptr) cout << "Error cargando la textura numero " + i << endl;
	}
}

void Game::initObjects() { //Aqui los objetos del juego 
	blockMap = new BlockMap(renderer, nTexturas[TBrick]);
	blockMap->load(maps[Lv1]);
	objects.push_back(blockMap);
	mapIt = --(objects.end());

	objects.push_back(new Ball(renderer, nTexturas[TBall], this));
	ballIt = --(objects.end());
	objects.push_back(new Paddle(renderer, nTexturas[TPaddle]));
	paddleIt = --(objects.end());
	objects.push_back(new Wall(renderer, nTexturas[TSide], POS_WALL_L_ROOF, false));
	objects.push_back(new Wall(renderer, nTexturas[TSide], POS_WALL_R, false));
	objects.push_back(new Wall(renderer, nTexturas[TTopSide], POS_WALL_L_ROOF, true));
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
	for (auto it = objects.begin(); it != objects.end(); it++) {
		if (static_cast<ArkanoidObject*>(*it)->getActive()) static_cast<ArkanoidObject*>(*it)->update();
		else {	//Aqui hacer la igualacion de iteradores para mas adelante en el 
				//update ir eliminando los premios que sobran de la lista de objetos
			//delete it;
			//destroy = it;
		}
	}

	//Comprobacion de victoria
	if (static_cast<BlockMap*>(*mapIt)->getNumBlocks() == 0) {
		nextLevel();
		if (level > 3) win = true;
	}
}

void Game::nextLevel() {
	level++;

	if (level > NUM_MAPS) level = 1;

	switch (level) {
	case 1:
		static_cast<BlockMap*>(*mapIt)->load(maps[Lv1]);
		break;
	case 2:
		static_cast<BlockMap*>(*mapIt)->load(maps[Lv2]);
		break;
	case 3:
		static_cast<BlockMap*>(*mapIt)->load(maps[Lv3]);
		break;
	default:
		static_cast<BlockMap*>(*mapIt)->load(maps[Lv1]);
		break;
	}

	static_cast<Ball*>(*ballIt)->respawn();
}

void Game::render() const {
	SDL_RenderClear(renderer); //Eliminamos lo que hay en pantalla
	//Render de cada objeto
	for (auto it = objects.begin(); it != objects.end(); it++) {
		static_cast<ArkanoidObject*>(*it)->render();
	}
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
			case SDLK_c:
				nextLevel();
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		//Eventos de cada obejeto
		static_cast<Paddle*>(*paddleIt)->handleEvents(event);
	}
}

void Game::pierdeVida() {
	vidas--;
	static_cast<Ball*>(*ballIt)->respawn();
	if (vidas == 0) {
		exit = true;
	}
}

bool Game::collidesBall(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector) {
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
	else if ((rect.x + rect.w) - (WIN_WIDTH - WALL_WIDTH) < 5) { //Parte der
		c = true;
		collVector = { -1, 0 };
	}
	else if (rect.x - WALL_WIDTH < 5) { //Parte izq
		c = true;
		collVector = { 1, 0 };
	}

	//Colisiones con Bloques
	Block* block = nullptr;
	block = static_cast<BlockMap*>(*mapIt)->collides(rect, vel, collVector);
	if (block != nullptr) {
		if (block->getActive()) {
			static_cast<BlockMap*>(*mapIt)->ballHitsBlock(block);
			c = true;
			puntuacion++;
			createReward(block->getRect());
		}
	}
	//---------------

	//Colisiones con paddle
	if (static_cast<Paddle*>(*paddleIt)->collidesBall(rect, collVector)) c = true;

	return c;
}

bool Game::collidesReward(const SDL_Rect &rect) {
	bool b = static_cast<Paddle*>(*paddleIt)->collidesReward(rect);
	return b;
}

void Game::createReward(const SDL_Rect &rect) {
	int aux = rand() % REWARD_CHANCE;
	if (aux == 0) {
		int r = rand() % 8;
		objects.push_back(new Reward(renderer, nTexturas[TReward], rect.x, rect.y, r, this));
		static_cast<Reward*>(objects.back())->setIt(--(objects.end()));
	}
}

Game::~Game() {
	deleteTextures();	//Eliminar las texturas del array de texturas
	deleteObjects();

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

void Game::deleteObjects() {
	for (auto i : objects) {
		delete i;
		i = nullptr;
	}
}