#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include <fstream>
#include "Game.h"
#include <Windows.h>
#include <sstream>
#include "SDLError.h"
#include "FileNotFoundError.h"

using namespace std;

using uint = unsigned int;
uint startTime = SDL_GetTicks();
uint frameTime;

Game::Game() {
	initSDL();
	initTextures(); //Iniciar texturas
	initObjects();

	scoreRect.x = (WIN_WIDTH / 2) + 50;
	scoreRect.y = -5;
	scoreRect.w = 300;
	scoreRect.h = 50;

	/*cout << "Introduce un '0' para cargar o un '1' para jugar una nueva partida." << endl;
	int klkpa;
	cin >> klkpa;
	if (klkpa == 0) load(SAVEFILE);
	else if (klkpa == 1) initObjects();
	else {
		cout << "Parece que no sabes leer :)";
		exit = true;
		system("pause");
	}*/
}

void Game::initSDL() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw SDLError(SDL_GetError());
		cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
	}
	else {
		window = SDL_CreateWindow("SDL ARKANOID", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			throw SDLError(SDL_GetError());
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) {
				throw SDLError(SDL_GetError());
				cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
			}
		}
	}
	if (TTF_Init() < 0)	throw SDLError("Error al cargar la librería TTF");
}

void Game::initTextures() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		nTexturas[i] = new Texture(renderer);
		nTexturas[i]->load(IMAGES_PATH + TEXT_ATT[i].nombre, TEXT_ATT[i].row, TEXT_ATT[i].col);
		if (nTexturas[i] == nullptr) {
			throw SDLError(SDL_GetError());
			cout << "Textures could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
		}
	}
	tScore = new Texture(renderer);
	font = TTF_OpenFont("../images/pixel.ttf", 20);
	if (font == nullptr) throw SDLError(TTF_GetError());
}

void Game::initObjects() { //Aqui los objetos del juego 
	initMap();
	objects.push_back(new Ball(renderer, nTexturas[TBall], this));
	ballIt = --(objects.end());
	objects.push_back(new Paddle(renderer, nTexturas[TPaddle], this));
	paddleIt = --(objects.end());
	objects.push_back(new Wall(renderer, nTexturas[TSide], POS_WALL_L_ROOF, false));
	objects.push_back(new Wall(renderer, nTexturas[TSide], POS_WALL_R, false));
	objects.push_back(new Wall(renderer, nTexturas[TTopSide], POS_WALL_L_ROOF, true));
	lastIt = --(objects.end());
}

void Game::initMap() {
	blockMap = new BlockMap(renderer, nTexturas[TBrick]);
	if (level < 3) blockMap->load(maps[level]);
	if (blockMap == nullptr) {
		throw FileNotFoundError(SDL_GetError());
		cout << "Map cannot be loaded! \nSDL_Error: " << SDL_GetError() << '\n';
	}
	objects.push_front(blockMap);
	mapIt = objects.begin();
}

void Game::run() {
	while (!exit && !win) {
		if (!saveState) {
			handleEvents();
			update();
			render();
			Sleep(FRAME_RATE);
		}
		else {
			save(SAVEFILE);
			exit = true;
		}
	}
}

void Game::update() {
	//Comprobacion de no mas bloques
	if (static_cast<BlockMap*>(*mapIt)->getNumBlocks() == 0) nextLevel();
	if (nivel) nextLevel();
	if (level > 2) win = true;

	auto it = objects.begin();
	while (it != objects.end()) {
		auto next = it;
		++next;
		if ((*it)->getActive()) (*it)->update();
		else {
			killObjects.push_back(*it);
			objects.remove(*it);
		}
		it = next;
	}
}

void Game::nextLevel() { //Siguiente nivel
	nivel = false;
	level++;

	//Eliminamos el mapa que sino se queda basura, no se como hacerlo mejor jeje
	delete *mapIt;
	objects.pop_front();
	initMap();

	// Reespauneamos la bola y el paddle
	static_cast<Ball*>(*ballIt)->respawn();
	static_cast<Paddle*>(*paddleIt)->respawn();

	// Eliminamos los premios sobrantes
	auto it = ++lastIt;
	while (it != objects.end()) {
		auto next = it;
		++next;
		killObjects.push_back(*it);
		objects.remove(*it);
		it = next;
	}

	// Actualizamos el ultimo iterador de nuevo para que apunte al ultimo objeto del juego que no sea un reward
	lastIt = --(objects.end());
}

void Game::render() const {
	SDL_RenderClear(renderer); //Eliminamos lo que hay en pantalla
	//Render de cada objeto
	for (auto it = objects.begin(); it != objects.end(); it++) {
		(*it)->render();
	}

	//Dibujado de la puntuacion
	stringstream strm;
	strm << "Score: " << puntuacion << "                " << "Vidas: " << vidas;
	tScore->loadFont(renderer, font, strm.str().c_str(), red);

	tScore->render(scoreRect);

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
			case SDLK_p:
				saveState = true;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		//Eventos de cada objeto
		static_cast<Paddle*>(*paddleIt)->handleEvents(event);
	}
}

void Game::pierdeVida() {
	vidas--;
	static_cast<Ball*>(*ballIt)->respawn();
	if (vidas == 0) exit = true;
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
	//int aux = 0;
	if (aux == 0) {
		int r = rand() % 4;
		switch (r) {
		case 0:
			objects.push_back(new RewardX1(renderer, nTexturas[TReward], rect.x, rect.y, this));
			static_cast<RewardX1*>(objects.back())->setIt(--(objects.end()));
			break;
		case 1:
			objects.push_back(new RewardX2(renderer, nTexturas[TReward], rect.x, rect.y, this));
			static_cast<RewardX2*>(objects.back())->setIt(--(objects.end()));
			break;
		case 2:
			objects.push_back(new RewardX3(renderer, nTexturas[TReward], rect.x, rect.y, this));
			static_cast<RewardX3*>(objects.back())->setIt(--(objects.end()));
			break;
		case 3:
			objects.push_back(new RewardX4(renderer, nTexturas[TReward], rect.x, rect.y, this));
			static_cast<RewardX4*>(objects.back())->setIt(--(objects.end()));
			break;
		default:
			break;
		}
	}
}

void Game::powerUp(int type) {
	static_cast<Paddle*>(*paddleIt)->powerUp(type);
}

void Game::load(const string& filename) {
	ifstream f;
	f.open(filename);

	int tempCode = 0;
	cout << "Introduce codigo de partida: ";
	cin >> tempCode;
	while (tempCode != code || f.end) {
		f >> code;
		//Salto
	}
	if (tempCode == code) {
		//Lectura
	}
}

void Game::save(const string& filename) {
	fstream f;
	f.open(filename, fstream::out | fstream::in | fstream::app);

	int nRow = static_cast<BlockMap*>(*mapIt)->numRow();
	nRow++;

	for (auto it = objects.begin(); it != objects.end(); it++) {
		nRow++;
	}

	cout << "Introduce codigo de partida: ";
	cin >> code;
	f << code << " " << nRow << endl;
	f << vidas << " " << puntuacion << endl;

	for (auto it = objects.begin(); it != objects.end(); it++) {
		(*it)->saveToFile(f); 
		nRow++;
	}

	f << endl;

	f.close();
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
	delete tScore;
	tScore = nullptr;
}

void Game::deleteObjects() {
	for (auto i : objects) {
		delete i;
		i = nullptr;
	}
	for (auto i : killObjects) {
		delete i;
		i = nullptr;
	}
}