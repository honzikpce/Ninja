//
//  Box.hpp
//  Ninja
//
//  Created by Honzik on 09.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp

#include <glm/glm.hpp>
#include <JN/SpriteBatch.hpp>
#include "ConstsAndTypes.hpp"
#include <Box2D/Box2D.h>
#include <JN/DebugRenderer.hpp>
#include <OpenGL/OpenGL.h>

class Box {
    
public:
    
    Box(b2World *world, glm::vec2 position, glm::vec2 dimensions, GLuint texture);
    void draw(JN::SpriteBatch &spriteBatch);
    void drawDebug(JN::DebugRenderer &debugRenderer);
    
    
    //setters

    void setColor(JN::Color color) { _color = color; }

    //getters
    glm::vec2 getPosition() const;
    glm::vec2 getDimensions() const;
    JN::Color getColor() const { return _color; }
    b2Body * getBody() { return _body; }

private:
    glm::vec2 _dimensions;
    JN::Color _color;
    GLuint _texture;
    b2Body *_body = nullptr;
    b2Fixture * _fixture = nullptr;
};

#endif /* Box_hpp */
