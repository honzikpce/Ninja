//
//  Player.cpp
//  Ninja
//
//  Created by Honzik on 10.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "Player.hpp"
#include <JN/ResourceManager.hpp>

Player::Player(b2World *world, glm::vec2 position, glm::vec2 dimensions) :
_dimensions(dimensions), _color(JN::Color(255,255,255,255)), _world(world)
{
    _texture = JN::ResourceManager::getTexture("textures/ninja.png");

    _spriteSheet.init(_texture, _spriteSheetWidth, _spriteSheetHeight);

    _capsule = new Capsule(world, position, dimensions - glm::vec2(1.0f, 0.0f));
    _body = _capsule->getBody();

    // lock player's orientation
    _body->SetFixedRotation(true);
    
}

Player::~Player() {
    delete _capsule;
}

void Player::drawDebug(JN::DebugRenderer &debugRenderer) {
    _capsule->drawDebug(debugRenderer);
}

void Player::update(JN::ControlManager *controlManager) {

    if (controlManager->isKeyDown(SDLK_a)) {
        _body->ApplyForceToCenter(b2Vec2(-150.0f, 0.0f), true);
    }
    else if (_body->GetLinearVelocity().x < 0.1) _body->SetLinearVelocity(b2Vec2(_body->GetLinearVelocity().x * 0.8f, _body->GetLinearVelocity().y));

    if (controlManager->isKeyDown(SDLK_d)) {
        _body->ApplyForceToCenter(b2Vec2(150.0f, 0.0f), true);
    }
    else if (_body->GetLinearVelocity().x > 0.1) _body->SetLinearVelocity(b2Vec2(_body->GetLinearVelocity().x * 0.8f, _body->GetLinearVelocity().y));

    // jump

        _isOnGround = false;


        for (b2ContactEdge * ce = _body->GetContactList(); ce != nullptr; ce = ce->next) {
            b2Contact *c = ce->contact;
            if (!c->IsTouching()) continue;
            b2WorldManifold manifold;
            c->GetWorldManifold(&manifold);
            if ((manifold.points[0].y < _body->GetPosition().y -_dimensions.y / 2.0f + 0.5f)
                || (manifold.points[1].y < _body->GetPosition().y -_dimensions.y / 2.0f + 0.5f)) {
                _isOnGround = true;
            }
        }
    if (controlManager->isKeyPressed(SDLK_w)) {
        if (_isOnGround) {
            _body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 40.0f), true);
        }
    }

    // speed limitation
    if (_body->GetLinearVelocity().x > _MAX_SPEED)
        _body->SetLinearVelocity(b2Vec2(_MAX_SPEED, _body->GetLinearVelocity().y));
    if (_body->GetLinearVelocity().x < -_MAX_SPEED)
        _body->SetLinearVelocity(b2Vec2(-_MAX_SPEED, _body->GetLinearVelocity().y));
}


glm::vec2 Player::getPosition() const {
    return glm::vec2(_body->GetPosition().x, _body->GetPosition().y);
}

glm::vec2 Player::getDimensions() const {
    return _dimensions;
}


void Player::draw(JN::SpriteBatch &spriteBatch) {

    // calculate animation
    _animTime += _animSpeed;

    glm::vec2 vel(_body->GetLinearVelocity().x, _body->GetLinearVelocity().y);

    if (!_isOnGround > 0.0f) {
        // in air
        if (vel.y > 0.0f) {
            // rising
            _animFrames = 1;
            _animIndex = 16;
        }
        else {
            // falling
            _animFrames = 1;
            _animIndex = 17;
        }
    }
    else {
        // on ground
        if (fabs(vel.x) > 0.1f) {
            // running
            _animFrames = 6;
            _animIndex = 10;
        }
        else {
            // standing still
            _animFrames = 1;
            _animIndex = 0;
        }
    }


    if (vel.x > 0.3f) _isAnimInverted = false;
    if (vel.x < 0.3f) _isAnimInverted = true;


    int currentFrame = (int)_animTime % _animFrames + _animIndex;

    glm::vec4 uvs = _spriteSheet.getUVs(currentFrame);

    if (_isAnimInverted) {
        uvs.x = uvs.x + 1.0f / (float)_spriteSheetWidth;
        uvs.z = uvs.z * -1;
    }

    spriteBatch.draw(glm::vec4(_body->GetPosition().x - _dimensions.x / 2.0f,
                               _body->GetPosition().y - _dimensions.y / 2.0f,
                               _dimensions),
                     uvs, _texture.id, 1.0f, _color, _body->GetAngle());
}

