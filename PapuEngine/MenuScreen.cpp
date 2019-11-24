#include "MenuScreen.h"
#include "MyScreens.h"
#include "Game.h"
#include <iostream>

MenuScreen::MenuScreen(Window* window):
	_window(window), btnGameClicked(false), btnMembersClicked(false),isClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void MenuScreen::initGUI() {
}

void MenuScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
							"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void MenuScreen::destroy() {
	delete buttom;
	delete buttom2;
	delete background;
	delete spriteFont;
}

void MenuScreen::onExit() {}

void MenuScreen::onEntry() {
	initSystem();
	initGUI();
	camera.init(_window->getScreenWidth(), _window->getScreenHeight());
	camera.setPosition(
		glm::vec2(
			_window->getScreenWidth() / 2.0f,
			_window->getScreenHeight() / 2.0f)
	);
	isClicked = false;
	_spriteBatch.init();
	background = new Background("Textures/menu1.png");
	spriteFont = new SpriteFont("Fonts/ShakaPowHollow.ttf",64);
	spriteFont1 = new SpriteFont("Fonts/ShakaPowHollow.ttf", 64);
	buttom = new Buttom("Textures/menu_button.png", glm::vec2(280, 100));
	buttom2 = new Buttom("Textures/menu_button.png", glm::vec2(280, 50));
	
}

void MenuScreen::update(){
	camera.update();
	checkInput();
}

void MenuScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{		
		std::cout << isClicked << endl;
		glm::vec2 coordenadas = _game->_inputManager.getMouseCoords();
		//glm::vec2 coord = glm::vec2(coordenadas.x, int(coordenadas.y)%100 );
		if (!isClicked && buttom->cliked(coordenadas, glm::vec2(_window->getScreenWidth(), _window->getScreenHeight()))) {
			isClicked = true;
			std::cout << "Cambio de pantalla Tutorial"<<endl;
			_currentState = ScreenState::CHANGE_NEXT;
			//destroy();
		}
		else if (!isClicked && buttom2->cliked(coordenadas, glm::vec2(_window->getScreenWidth(), _window->getScreenHeight()))) {
			isClicked = true;
			std::cout << "Cambio de pantalla Miembros" << endl;
			_currentState = ScreenState::CHANGE_PREVIOUS;
			//destroy();
		}
	}
}

void MenuScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();

	buttom->draw(_spriteBatch);
	buttom2->draw(_spriteBatch);
	background->draw(_spriteBatch);
	
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	//Titulo Juego
	char buffer[256];
	_spriteBatch.begin();
	sprintf(
		buffer, "Foggie"
	);
		
	spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(320, 400), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 0, 0, 255)
		);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	// Button Jugar
	char buffer1[256];
	_spriteBatch.begin();
	sprintf(
		buffer1, "Jugar"
	);


	spriteFont1->draw(_spriteBatch, buffer1,
		glm::vec2(320, 110), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 0, 0, 255)
	);



	_spriteBatch.end();
	_spriteBatch.renderBatch();

	// Button Miembros
	char buffer2[256];
	_spriteBatch.begin();
	sprintf(
		buffer2, "Miembros"
	);

	spriteFont1->draw(_spriteBatch, buffer2,
		glm::vec2(300, 60), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 0, 0, 255)
	);

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	//

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void MenuScreen::build() {}

int MenuScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MEMBERS;
}

int MenuScreen::getNextScreen() const {
	return SCREEN_INDEX_TUTORIAL;
}

MenuScreen::~MenuScreen()
{
}
