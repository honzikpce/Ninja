//
//  Box.cpp
//  Ninja
//
//  Created by Honzik on 09.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "Box.hpp"


Box::Box(b2World *world, glm::vec2 position, glm::vec2 dimensions, GLuint texture) :
_dimensions(dimensions), _texture(texture), _color(JN::Color(255,255,255,255))
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x, position.y);
    _body = world->CreateBody(&bodyDef);
    _body->SetType(b2BodyType::b2_dynamicBody);
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);
    
    _fixture = _body->CreateFixture(&boxShape, 1.0f);
    _fixture->SetFriction(0.5f);
    

}


glm::vec2 Box::getPosition() const {
    return glm::vec2(_body->GetPosition().x, _body->GetPosition().y);
}

glm::vec2 Box::getDimensions() const {
    return _dimensions;
}


void Box::draw(JN::SpriteBatch &spriteBatch) {
    spriteBatch.draw(glm::vec4(_body->GetPosition().x - _dimensions.x / 2.0f,
                               _body->GetPosition().y - _dimensions.y / 2.0f,
                               _dimensions),
                     UV_DEFAULT, _texture, 1.0f, _color, _body->GetAngle());
}

void Box::drawDebug(JN::DebugRenderer &debugRenderer) {
    debugRenderer.drawRectangle(glm::vec4(getPosition() - getDimensions() / 2.0f, getDimensions()), _body->GetAngle(), _color);
}






