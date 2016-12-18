//
//  App.cpp
//  Ninja
//
//  Created by Honzik on 06.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//



#include "App.hpp"
#include <JN/JNgine.hpp>
#include <JN/Window.hpp>


App::App() {
    // empty
}

App::~App() {
    delete gameScreen;
}


void App::onInit() {
    
    
}


void App::addScreens() {
    gameScreen = new GamePlayScreen();
    _screenList->addScreen(gameScreen);
    _screenList->setScreen(gameScreen->getScreenIndex());
}


void App::onExit() {
    
}
