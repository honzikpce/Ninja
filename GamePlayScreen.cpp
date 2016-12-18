//
//  GamePlayScreen.cpp
//  Ninja
//
//  Created by Honzik on 08.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//


#include "GamePlayScreen.hpp"
#include <OpenGL/gl3.h>
#include "ConstsAndTypes.hpp"
#include <glm/glm.hpp>
#include <random>
#include <JN/ResourceManager.hpp>
#include <JN/IMainGame.hpp>


GamePlayScreen::GamePlayScreen() {
    
}

GamePlayScreen::~GamePlayScreen() {
    destroy();
}

int GamePlayScreen::getNextScreenIndex() const{
    return SCREEN_INDEX_NO_SCREEN;
}

int GamePlayScreen::getPrevScreenIndex() const{
    return SCREEN_INDEX_NO_SCREEN;
}


// creating and destroying screens
void GamePlayScreen::build() {
    
    // init shaders
    _textureProgram.compileShaders("shaders/simple.vert", "shaders/simple.frag");
    _textureProgram.addAttribute("vertexPosition");
    _textureProgram.addAttribute("vertexColor");
    _textureProgram.addAttribute("vertexUV");
    
    //init spriteBatch
    _spriteBatch.init();
    _debugRenderer.init();
    _camera.init(SCREEN_W, SCREEN_H);

    // init camera
    _camera.setScale(25.0f);
    _camera.setPosition(glm::vec2(0.0f, 0.0f));
    
    // get control manager
    _controls = _mainGame->getControlManager();
    
    // create the physics world with gravity
    b2Vec2 gravity = b2Vec2(0.0f, -25.0f);
    _world = new b2World(gravity);
    
    // create a ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -15.0);
    
    b2Body * groundBody = _world->CreateBody(&groundBodyDef);
    b2PolygonShape groundShape;
    
    groundShape.SetAsBox(50.0f, 5.0f);
    b2Fixture * groundFixture = groundBody->CreateFixture(&groundShape, 0.0f);

}

void GamePlayScreen::destroy() {
    delete _world;
    _world = nullptr;
    delete _player;
    _player = nullptr;
}

// switch to and from screen;
void GamePlayScreen::onEntry() {
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    
    // generate boxes
    std::random_device rndDev;
    std::mt19937 rndEngine(rndDev());
    std::uniform_real_distribution<float> rndPosition(0.0f, 40.0f);
    
    for (int i = 0; i < 5; i++) {
        _boxes.emplace_back(_world,
                            glm::vec2(rndPosition(rndEngine) - 20.0f, rndPosition(rndEngine) / 2.0f),
                            //glm::vec2(0.0f, -5.0f),
                            glm::vec2(1.5f),
                            JN::ResourceManager::getTexture("textures/Tiles/boxAlt.png").id);
        _boxes.back().setColor(JN::Color(6 * (GLubyte)rndPosition(rndEngine),
                                            6 * (GLubyte)rndPosition(rndEngine),
                                            6 * (GLubyte)rndPosition(rndEngine), 255));
    }

    // spawn player
    _player = new Player(_world, glm::vec2(-10.0f, 25.0f), glm::vec2(2.0f, 3.0f));
    //CEGUI::OpenGL3Renderer &guiRenderer = CEGUI::OpenGL3Renderer::bootstrapSystem();

}

void GamePlayScreen::onExit() {
    
}

// called from mainGame
void GamePlayScreen::update() {
    handleEvents(); ///< can start exiting game!!!
    _world->Step(1/60.0f, 8, 3);
    _player->update(_controls);
    _camera.update();

}

void GamePlayScreen::handleEvents() {
    // handle control events
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt))
        _mainGame->onSDLEvent(evnt);

    if (_controls->isKeyPressed(SDLK_F1)) {
        _isDebugActive = !_isDebugActive;
    }

    if (_controls->isKeyDown(SDLK_o)) {
        _camera.setScale(_camera.getScale() + 0.1f);
    }

    if (_controls->isKeyDown(SDLK_p)) {
        _camera.setScale(_camera.getScale() - 0.1f);
    }
    if (_controls->isKeyDown(SDLK_i)) {
        _camera.setPosition(glm::vec2(_camera.getPosition().x, _camera.getPosition().y + 1.0f));
    }

    if (_controls->isKeyDown(SDLK_k)) {
        _camera.setPosition(glm::vec2(_camera.getPosition().x, _camera.getPosition().y - 1.0f));
    }
    if (_controls->isKeyDown(SDLK_j)) {
        _camera.setPosition(glm::vec2(_camera.getPosition().x - 1.0f, _camera.getPosition().y));
    }

    if (_controls->isKeyDown(SDLK_l)) {
        _camera.setPosition(glm::vec2(_camera.getPosition().x + 1.0f, _camera.getPosition().y));
    }
}

void GamePlayScreen::draw() {
    
    // clear to bg color
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // activating shaders!
    _textureProgram.use();
    glActiveTexture(GL_TEXTURE0);
    
    //upload uniforms to shaders
    GLuint camLoc = _textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(camLoc, 1, GL_FALSE, &(_camera.getCameraMatrix())[0][0]);

    GLuint textureLocation = _textureProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    // batch drawing
    _spriteBatch.begin();

    // draw boxes
    for (int i = 0; i < _boxes.size(); i++) {
        _boxes[i].draw(_spriteBatch);
        if (_isDebugActive) _boxes[i].drawDebug(_debugRenderer);
    }
    // draw player
    _player->draw(_spriteBatch);
    if (_isDebugActive) _player->drawDebug(_debugRenderer);

    // render textured draws
    _spriteBatch.end();
    _spriteBatch.renderBatch();
    _textureProgram.unUse();


    // debug renderer
    if (_isDebugActive)
    {
        // draw ground box
        _debugRenderer.drawRectangle(glm::vec4(-50.0f, -20.0f, 100.0f, 10.0f), 0.0f, JN::Color(255,255,255,255));

        // render debug draws
        _debugRenderer.end();
        _debugRenderer.render(_camera.getCameraMatrix(), 1.0f);
    }
}
