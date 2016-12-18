//
// Created by Honzik on 13.12.16.
// Copyright (c) 2016 Jan Novak. All rights reserved.
//

#ifndef NINJA_CAPSULE_H
#define NINJA_CAPSULE_H

#include <glm/glm.hpp>
#include <JN/SpriteBatch.hpp>
#include "ConstsAndTypes.hpp"
#include <Box2D/Box2D.h>
#include <JN/DebugRenderer.hpp>
#include <OpenGL/OpenGL.h>

class Capsule {

public:

    Capsule(b2World *world, glm::vec2 position, glm::vec2 dimensions);
    void drawDebug(JN::DebugRenderer &debugRenderer);


    //setters

    void setColor(JN::Color color) { _color = color; }

    //getters
    b2Body * getBody() { return _body; }

private:
    glm::vec2 _dimensions;
    JN::Color _color;
    b2Body *_body = nullptr;

    // rect, top circle, bottom circle
    b2Fixture * _fixture[3];
};


#endif //NINJA_CAPSULE_H
