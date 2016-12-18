//
// Created by Honzik on 13.12.16.
// Copyright (c) 2016 Jan Novak. All rights reserved.
//

#include "Capsule.h"

Capsule::Capsule(b2World *world, glm::vec2 position, glm::vec2 dimensions)
:_dimensions(dimensions), _color(JN::Color(255,255,255,255))
{
    _dimensions = dimensions;
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x, position.y);
    _body = world->CreateBody(&bodyDef);
    _body->SetType(b2BodyType::b2_dynamicBody);

    // rectangle
    b2PolygonShape boxShape;
    boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f - dimensions.x / 4.0f);
    b2FixtureDef rectDef;
    rectDef.shape = &boxShape;
    rectDef.friction = 0.1f;
    rectDef.density = 1.0f;
    _fixture[0] = _body->CreateFixture(&rectDef);

    b2CircleShape topShape;
    b2CircleShape bottomShape;

    // top circle
    b2FixtureDef topCircle;
    topCircle.shape = &topShape;
    topShape.m_p = b2Vec2(0.0f, _dimensions.y / 2.0f - dimensions.x / 2.0f);
    topShape.m_radius = _dimensions.x / 2.0f;
    topCircle.density = 1.0f;
    topCircle.friction = 0.1;
    _fixture[1] = _body->CreateFixture(&topCircle);


    // bottom circle
    b2FixtureDef bottomCircle;
    bottomCircle.shape = &bottomShape;
    bottomShape.m_p = b2Vec2(0.0f, -_dimensions.y / 2.0f + dimensions.x / 2.0f);
    bottomShape.m_radius = _dimensions.x / 2.0f;
    bottomCircle.density = 1.0f;
    bottomCircle.friction = 0.1f;
    _fixture[2] = _body->CreateFixture(&bottomCircle);


}

void Capsule::drawDebug(JN::DebugRenderer &debugRenderer) {
    // draw box
    debugRenderer.drawRectangle(
            glm::vec4(
        _body->GetPosition().x - _dimensions.x / 2.0f,
        _body->GetPosition().y - _dimensions.y / 2.0f + _dimensions.x / 2.0f,
        _dimensions.x, _dimensions.y - _dimensions.x),
        _body->GetAngle(), _color);

    // draw top circle
    debugRenderer.drawCircle(
            glm::vec2(
                    _body->GetPosition().x,
                    _body->GetPosition().y + _dimensions.y / 2.0f - _dimensions.x / 2.0f),
            _dimensions.x / 2.0f, _color);

    // draw bottom circle
    debugRenderer.drawCircle(
            glm::vec2(
                    _body->GetPosition().x,
                    _body->GetPosition().y - _dimensions.y / 2.0f + _dimensions.x / 2.0f),
            _dimensions.x / 2.0f, _color);
}
