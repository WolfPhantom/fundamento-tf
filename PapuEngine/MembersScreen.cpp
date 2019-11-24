#include "MembersScreen.h"
#include "MyScreens.h"
#include "Game.h"
#include <iostream>

MembersScreen::MembersScreen(Window* window) :
	_window(window), btnbackClicked(false),isClicked(false)
{
	_screenIndex = SCREEN_INDEX_MEMBERS;
}

void MembersScreen::initGUI() {
}

void MembersScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void MembersScreen::destroy() {
	delete buttom;
	delete background;
	delete spriteFont;
}

void MembersScreen::onExit() {}

void MembersScreen::onEntry() {
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
	spriteFont = new SpriteFont("Fonts/ShakaPowHollow.ttf", 64);
	spriteFont1 = new SpriteFont("Fonts/ShakaPowHollow.ttf", 35);
	buttom = new Buttom("Textures/btn_back.png", glm::vec2(280, 100));


}

void MembersScreen::update() {
	camera.update();
	checkInput();
}

void MembersScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{

		std::cout << isClicked << endl;
		glm::vec2 coordenadas = _game->_inputManager.getMouseCoords();
		glm::vec2 coord = glm::vec2(coordenadas.x, int(coordenadas.y) % 100);
		if (!isClicked && buttom->cliked(_game->_inputManager.getMouseCoords(), glm::vec2(_window->getScreenWidth(), _window->getScreenHeight()))) {
			isClicked = true;
			std::cout << "Cambio de pantalla menu" << endl;
			_currentState = ScreenState::CHANGE_PREVIOUS;
			//destroy();
		}
	}
}

void MembersScreen::draw() {
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
	background->draw(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	char buffer[256];
	_spriteBatch.begin();
	sprintf(
		buffer, "Diego Miranda \n Diego Johnson \n Alexander Trujillano \n Oscar Fernandez"
	);

	spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(250, 320), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 0, 0, 255)
	);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	//
	char buffer1[256];
	_spriteBatch.begin();
	sprintf(
		buffer1, "Regresar"
	);


	spriteFont1->draw(_spriteBatch, buffer1,
		glm::vec2(330, 115), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 0, 0, 255)
	);

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	//

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void MembersScreen::build() {}

int MembersScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int MembersScreen::getNextScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

MembersScreen::~MembersScreen()
{
}