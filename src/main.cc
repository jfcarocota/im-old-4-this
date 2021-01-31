
#include "CommonHeaders.hh"

#include "Maze.hh"
#include "Inputs.hh"
#include "Character.hh"
#include "Tile.hh"
#include "GameObject.hh"
#include "ContactListener.hh"
#include "Score.hh"
#include "GUI/Button.hh"
#include "HiddenBox.hh"

#include "AssetsPath.hh"

int main()
{

    gameState = MENU;

    //esto es la ventana de tu grafico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), GAME_NAME, sf::Style::Titlebar | sf::Style::Close);
    sf::Image* iconTexture{new sf::Image()};
    iconTexture->loadFromFile(ICON);
    window->setIcon(32, 32, iconTexture->getPixelsPtr());

    sf::SoundBuffer* soundBuffer{new sf::SoundBuffer()};
    sf::Sound* sound{new sf::Sound()};
    soundBuffer->loadFromFile(BG_MUSIC);
    sound->setBuffer(*soundBuffer);
    sound->setLoop(true);
    sound->setVolume(10.f);
    sound->play();

    sf::SoundBuffer* soundBufferStepsSFX{new sf::SoundBuffer()};
    sf::Sound* stepsSfx{new sf::Sound()};
    soundBufferStepsSFX->loadFromFile(STEPS_SFX);
    stepsSfx->setBuffer(*soundBufferStepsSFX);
    stepsSfx->setVolume(4.f);
    float stepDelay{0.3f};
    float currentStepSFXTime {stepDelay};

    //sfx click
    sf::SoundBuffer* clickSFXBuffer{new sf::SoundBuffer()};
    sf::Sound* clickSfx{new sf::Sound()};
    clickSFXBuffer->loadFromFile(CLICK_SFX);
    clickSfx->setBuffer(*clickSFXBuffer);
    clickSfx->setVolume(4.f);

    Button* btnStart{new Button((WINDOW_WIDTH / 2) - 75, (WINDOW_HEIGHT / 2)  + 100, 150.f, 50.f, 0.5f, 
    new sf::Color(255, 255, 255), new sf::Color(255, 255, 255), window, "Start", FONT1, 35)};

    //aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    Score* score{new Score(FONT1, "Score ", 24, new sf::Vector2f(25, 5), new sf::Color(255, 255, 255), window)};
    

    //physics declaration
    b2Vec2* gravity{new b2Vec2(0.f, 0.f)};
    b2World* world{new b2World(*gravity)}; 

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};

    window->setFramerateLimit(FPS);
    //Game inputs
    Inputs* inputs{new Inputs()};

    //Menu Texture
    sf::Texture* bannerTexture{new sf::Texture()};
    bannerTexture->loadFromFile(BANNER);

    //Textures
    sf::Texture* texturePlayer{new sf::Texture()};
    texturePlayer->loadFromFile(SS_OLDGUY);
    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);
    sf::Texture* tilesTexture2{new sf::Texture()};
    tilesTexture2->loadFromFile(TILES2);
    sf::Texture* tilesTexture3{new sf::Texture()};
    tilesTexture3->loadFromFile(TILES3);
    sf::Texture* tilesTextureMain{new sf::Texture()};
    tilesTextureMain->loadFromFile(MAIN_TILES);

    const float tileBaseWidth{16 * SPRITE_SCALE};
    const float tileBaseHeight{16 * SPRITE_SCALE};

    sf::Sprite* bannerSprite{new sf::Sprite(*bannerTexture, *(new sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)))};

    //Main player
    Character* character1{new Character(texturePlayer, 0 * 1, 0 * 1, 78 / 6, 27 / 2, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(400, 300), b2BodyType::b2_dynamicBody, world, window)};
    character1->SetAnimations(
        new Animation*[2]
        {
            new Animation(0, 0, 5, character1->GetSprite(), 80.f),
            new Animation(1, 0, 5, character1->GetSprite(), 80.f)
        }
    );
    
    character1->SetTagName("player");
    //character1->SetDebug(true);

    unsigned int N{10}, M{13};
    Maze* maze1{new Maze(N, M, SPRITE_SCALE, 16, tilesTextureMain, MAZEROOM, world)};
    Maze* maze2{new Maze(N, M, SPRITE_SCALE, 16, tilesTextureMain, MAZE2, world)};
    Maze*& currentMaze{*&maze1};

   /* GameObject* treasure{new GameObject(tilesTexture3, 16 * 19, 16 * 19, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(400, 400), b2BodyType::b2_staticBody, world, window)}; 
    treasure->SetTagName("item");
    GameObject* treasure2{new GameObject(tilesTexture3, 16 * 19, 16 * 19, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(200, 400), b2BodyType::b2_staticBody, world, window)}; 
    treasure2->SetTagName("item");

    GameObject* stairs{new GameObject(tilesTexture3, 16 * 3, 16 * 6, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(510, 510), b2BodyType::b2_staticBody, world, window)};
    stairs->SetTagName("stairs");
    //stairs->SetDebug(true);*/

    HiddenBox* boxLeft {new HiddenBox(world, 0, 0, 1, WINDOW_HEIGHT, SPRITE_SCALE, window)};
    //boxLeft->SetDebugMode(true);
    HiddenBox* boxRight {new HiddenBox(world, 750, 0, 1, WINDOW_HEIGHT, SPRITE_SCALE, window)};
    HiddenBox* boxBottom {new HiddenBox(world, 0, WINDOW_HEIGHT - 40, WINDOW_WIDTH, 1, SPRITE_SCALE, window)};
    std::vector<HiddenBox*>* boxes{new std::vector<HiddenBox*>()};
    boxes->push_back(boxLeft);
    boxes->push_back(boxRight);
    boxes->push_back(boxBottom);

    std::vector<GameObject*>* items{new std::vector<GameObject*>()};
    /*items->push_back(treasure);
    items->push_back(treasure2);
    items->push_back(stairs);*/

    ContactListener* conctactListener{new ContactListener(score, items)};

    world->SetContactListener(conctactListener);

    //esto es el loop principal, mientras la ventana este abierta, esto se va ejecutar.
    while (window->isOpen())
    {
        //mientras se esten ejecutando eventos dentro de la ventana, esto se va repetir eje: teclado, joystick, mouse, etc
        while (window->pollEvent(event))
        {
            //si el evento fue la acción de cerrar la ventana, entonces termina la aplicación.
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        switch (conctactListener->GetSceneIndex())
        {
            case 0:
                currentMaze = maze1;
                break;
            case 1:
                currentMaze = maze2;
                break;
            default:
                currentMaze = maze1;
                break;
        }
        
        Vec2* keyboardAxis{inputs->GetKeyboardAxis()};
        Vec2* joystickAxis{inputs->GetJoystickAxis()};

        if(gameState == GAME)
        {
            if(sf::Joystick::isConnected(0))
            {
                character1->Move(new b2Vec2(joystickAxis->x * deltaTime * PLAYER_MOVESPEED, joystickAxis->y * deltaTime * PLAYER_MOVESPEED));
                character1->FlipSpriteX(joystickAxis->x);

                if(std::abs(joystickAxis->x) > 0 || std::abs(joystickAxis->y) > 0)
                {
                    //run
                    character1->GetAnimation(1)->Play(deltaTime);
                }
                else
                {
                    //idle
                    character1->GetAnimation(0)->Play(deltaTime);
                }
            }
            else
            {
                character1->Move(new b2Vec2(keyboardAxis->x * deltaTime * PLAYER_MOVESPEED, keyboardAxis->y * deltaTime * PLAYER_MOVESPEED));
                character1->FlipSpriteX(keyboardAxis->x);

                if(std::abs(keyboardAxis->x) > 0 || std::abs(keyboardAxis->y) > 0)
                {
                    //run
                    character1->GetAnimation(1)->Play(deltaTime);
                    if(currentStepSFXTime >= stepDelay)
                    {
                        stepsSfx->play();
                        currentStepSFXTime = 0.f;
                    }
                }
                else
                {
                    //idle
                    character1->GetAnimation(0)->Play(deltaTime);
                }
            }
        }

        window->clear(*(new sf::Color(150, 100, 0, 255)));//limpiar la pantalla

        if(gameState == MENU)
        {
            window->draw(*bannerSprite);
            btnStart->Update();
            if(btnStart->OnClick())
            {
                //click sfx
                clickSfx->play();
                gameState = GAME;
            }
        }

        if(gameState == GAME)
        {
            for(auto& mazeTile : *currentMaze->GetContainer())
            {
                window->draw(*mazeTile->GetSprite());
            }

            //stairs->Update();
            
            /*for(auto& item : *items)
            {
                item->Update();
            }*/

            for(auto& box : *boxes)
            {
                box->Update();
            }

            character1->Update();

            //button1->Update();

            //score->Update();
        }

        window->display(); //mostrar en pantalla lo que se va dibujar

        sf::Time timeElapsed {clock->getElapsedTime()};
        deltaTime = timeElapsed.asMilliseconds();

        if(gameState == GAME)
        {
            currentStepSFXTime += timeElapsed.asSeconds();
        }
        
        //std::cout << "Current step sfx time: " << currentStepSFXTime;
        world->ClearForces();
        world->Step(1.f / 100 * deltaTime, 8, 8);
        clock->restart();
        
        //std::cout << "delta time: " << deltaTime << std::endl;

        delete keyboardAxis;
        delete joystickAxis;
    }
    
    return 0;
}