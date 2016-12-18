//
//  GamePlayScreen.hpp
//  Ninja
//
//  Created by Honzik on 08.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef GamePlayScreen_hpp
#define GamePlayScreen_hpp


#include <JN/IGameScreen.hpp>
#include <JN/SpriteBatch.hpp>
#include <JN/GLSLProgram.hpp>
#include <JN/Camera2d.hpp>
#include <JN/DebugRenderer.hpp>

#include <vector>

#include "Box.hpp"
#include "Player.hpp"

#include <Box2D/Box2D.h>


class GamePlayScreen : public JN::IGameScreen {
public:
    GamePlayScreen();
    virtual ~GamePlayScreen() override;
    
    virtual int getNextScreenIndex() const override;
    virtual int getPrevScreenIndex() const override;
    
    
    // creating and destroying screens
    virtual void build() override;
    virtual void destroy() override;
    
    // switch to and from screen;
    virtual void onEntry() override;
    virtual void onExit() override;
    
    // called from mainGame
    virtual void update() override;
    virtual void draw() override;
    
private:
    JN::SpriteBatch _spriteBatch;
    JN::DebugRenderer _debugRenderer;
    JN::GLSLProgram _textureProgram;
    JN::ControlManager* _controls = nullptr;
    JN::Camera2D _camera;
    b2World *_world = nullptr;
    void handleEvents();
    
    std::vector<Box> _boxes;
    Player * _player;
    bool _isDebugActive = false;

};

#endif /* GamePlayScreen_hpp */
