//
//  App.hpp
//  Ninja
//
//  Created by Honzik on 06.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef App_hpp
#define App_hpp


#include <JN/IMainGame.hpp>
#include <JN/Window.hpp>


#include "GamePlayScreen.hpp"

class App : public JN::IMainGame {
public:
    App();
    ~App();
    
    virtual void onInit() override;
    virtual void addScreens() override;
    virtual void onExit() override;
    
    
private:
    JN::Window _window;
    JN::IGameScreen* gameScreen = nullptr;
    
    
};

#endif /* App_hpp */
