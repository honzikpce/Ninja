//
//  Player.hpp
//  Ninja
//
//  Created by Honzik on 10.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <glm/glm.hpp>
#include <JN/SpriteBatch.hpp>
#include <JN/DebugRenderer.hpp>
#include <JN/ControlManager.hpp>
#include "ConstsAndTypes.hpp"
#include "Capsule.h"
#include <Box2D/Box2D.h>
#include <JN/SpriteSheet.h>
#include <JN/glTexture.h>

class Player {
    
public:
    
    Player(b2World *world, glm::vec2 position, glm::vec2 dimensions);
    ~Player();

    void draw(JN::SpriteBatch &spriteBatch);
    void drawDebug(JN::DebugRenderer &debugRenderer);
    void update(JN::ControlManager *controlManager);
    
    //getters
    glm::vec2 getPosition() const;
    glm::vec2 getDimensions() const;
    JN::Color getColor() const { return _color; }
    b2Body * getBody() { return _body; }
    b2Fixture * getFixture() { return _fixture; }
    
    
private:
    glm::vec2 _dimensions;
    JN::Color _color;
    JN::GLTexture _texture;

    b2World * _world = nullptr;
    b2Body *_body = nullptr;
    b2Fixture * _fixture = nullptr;
    Capsule * _capsule;
    JN::SpriteSheet _spriteSheet;

    const float _MAX_SPEED = 10.0f;

    float _animTime = 0.0f;
    float _animSpeed = 0.2f;
    int _animFrames = 1;
    int _animIndex = 0;
    bool _isOnGround;
    bool _isAnimInverted = false;
    const int _spriteSheetWidth = 10;
    const int _spriteSheetHeight = 2;
};

#endif /* Player_hpp */
