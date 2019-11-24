#include "../render.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string> 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <array> 
#include "../../shared/state.h"
#include "../../shared/engine.h"

using namespace std;
using namespace render;
using namespace state;
using namespace engine;


StateLayer::StateLayer (state::State& myState, sf::RenderWindow& window):window(window){
    std::unique_ptr<TileSet> ptrMapTileSet(new TileSet(MAP_TILESET));
    tilesets.push_back(std::move(ptrMapTileSet));
    std::unique_ptr<TileSet> ptrEffectTileSet(new TileSet(MAP_TILESET));
    tilesets.push_back(std::move(ptrEffectTileSet));
    std::unique_ptr<TileSet> ptrPawnTileSet(new TileSet(PAWN_TILESET));
    tilesets.push_back(std::move(ptrPawnTileSet));
    std::unique_ptr<TileSet> ptrCommandTileSet(new TileSet(COMMAND_TILESET));
    tilesets.push_back(std::move(ptrCommandTileSet));
    std::unique_ptr<TileSet> ptrSlotTileSet(new TileSet(COMMAND_TILESET));
    tilesets.push_back(std::move(ptrSlotTileSet));
}

void StateLayer::initSurface (state::State& stateLayer){
    Display surfaceMap;
    Display surfaceEffects;
    Display surfacePlayers;
    Display surfaceCommand;
    Display surfaceSlot;

    int inTiles[] = {8, 1, 9, 0, 5, 7, 6, 0, 0, 2, 0, 0};
    int inSlot[] = {0, 0, 0, 0, 0, 0};

    std::vector<int> efftTab(stateLayer.getMapHeight(), 37);
    this->effectsTab.clear();
    for (int i = 0; i < stateLayer.getMapWidth(); ++i) {
        this->effectsTab.push_back(efftTab);
    }

    buttonReadyToClick = 0;
    
    for (int i = 0 ; i < 12 ; i++) {
        commandTab[i] = inTiles[i];
    }
    for (int i = 0 ; i < 6 ; i++) {
        slotTab[i] = inSlot[i];
    }


    surfaceMap.loadMap(stateLayer, tilesets[0]->getTexture(), sf::Vector2u(tilesets[0]->getCellWidth(), tilesets[0]->getCellHeight()));
    surfaceEffects.loadEffects(stateLayer, tilesets[1]->getTexture(), sf::Vector2u(tilesets[1]->getCellWidth(), tilesets[1]->getCellHeight()), effectsTab);
    surfacePlayers.loadPlayers(stateLayer, tilesets[2]->getTexture(), sf::Vector2u(tilesets[2]->getCellWidth(), tilesets[2]->getCellHeight()));
    surfaceCommand.loadCommand(tilesets[3]->getTexture(), sf::Vector2u(tilesets[3]->getCellWidth(), tilesets[3]->getCellHeight()), inTiles);
    surfaceSlot.loadSlot(tilesets[4]->getTexture(), sf::Vector2u(tilesets[4]->getCellWidth(), tilesets[4]->getCellHeight()), inSlot);


    std::unique_ptr<Display> ptrMapDisplay (new Display(surfaceMap));
    std::unique_ptr<Display> ptrEffectsDisplay (new Display(surfaceEffects));
    std::unique_ptr<Display> ptrPlayersDisplay (new Display(surfacePlayers));
    std::unique_ptr<Display> ptrCommandDisplay (new Display(surfaceCommand));
    std::unique_ptr<Display> ptrSlotDisplay (new Display(surfaceSlot));

    /* On nettoie/supprime les surfaces avant d'afficher les nouvelles */
    if (surfaces.size()!=0){
        while (surfaces.size()!=0){
            surfaces.pop_back();
        }
    }

    surfaces.push_back(move(ptrMapDisplay));
    surfaces.push_back(move(ptrEffectsDisplay));
    surfaces.push_back(move(ptrPlayersDisplay));
    surfaces.push_back(move(ptrCommandDisplay));
    surfaces.push_back(move(ptrSlotDisplay));
}

void StateLayer::refreshCommand () {
    Display surfaceCommand;

    int inTiles[12];
    for (int i = 0 ; i < 12 ; i++) {
        inTiles[i] = commandTab[i];
    }
   
    surfaceCommand.loadCommand(tilesets[3]->getTexture(), sf::Vector2u(tilesets[3]->getCellWidth(), tilesets[3]->getCellHeight()), inTiles);
    
    std::unique_ptr<Display> ptrCommandDisplay (new Display(surfaceCommand));

    /* Attention ! il faut appeler l'initialisation de la map avant refreshCommand sinon "surfaces" n'existe pas"*/
    surfaces.at(3) = move(ptrCommandDisplay);
}

void StateLayer::refreshSlot () {
    Display surfaceSlot;

    int inSlots[6];
    for (int i = 0 ; i < 6 ; i++) {
        inSlots[i] = slotTab[i];
    }
   
    surfaceSlot.loadSlot(tilesets[4]->getTexture(), sf::Vector2u(tilesets[4]->getCellWidth(), tilesets[4]->getCellHeight()), inSlots);
    
    std::unique_ptr<Display> ptrSlotDisplay (new Display(surfaceSlot));

    /* Attention ! il faut appeler l'initialisation de la map avant refreshCommand sinon "surfaces" n'existe pas"*/
    surfaces.at(4) = move(ptrSlotDisplay);
}

void StateLayer::refreshPlayers (state::State& stateLayer) {
    Display surfacePlayers;

    int inSlots[6];
    for (int i = 0 ; i < 6 ; i++) {
        inSlots[i] = slotTab[i];
    }
   
    surfacePlayers.loadPlayers(stateLayer, tilesets[2]->getTexture(), sf::Vector2u(tilesets[2]->getCellWidth(), tilesets[2]->getCellHeight()));
    
    std::unique_ptr<Display> ptrPlayersDisplay (new Display(surfacePlayers));

    /* Attention ! il faut appeler l'initialisation de la map avant refreshCommand sinon "surfaces" n'existe pas"*/
    surfaces.at(2) = move(ptrPlayersDisplay);

}

void StateLayer::refreshEffects (state::State& stateLayer, int actionsInRound, int idMyClient) {
    Display surfaceEffects;

    /* Display visited cp of the client player with the good color */
    std::vector<int> visitedCp = stateLayer.getPlayers()[idMyClient]->getVisitedCheckpoints();

    for (unsigned int k = 0; k < visitedCp.size() ; k++) {
        for (int i = 0 ; i < stateLayer.getMapWidth() ; i++) {
            for (int j = 0 ; j < stateLayer.getMapHeight() ; j++) {
                int isCp = stateLayer.getMap()[i][j]->getTileCode();
                if ((isCp >= 3) && (isCp <= 7) && (isCp-2) == visitedCp[k]) {
                    this->effectsTab[i][j] = isCp + 5;
                    cout<<"CP detected : "<<isCp<<endl;
                }
            }
        }
    }

    /* Display blast or attack */
    //stateLayer.getPlayers()[idMyClient]->getRobotActions()[actionsInRound];


    surfaceEffects.loadEffects(stateLayer, tilesets[1]->getTexture(), sf::Vector2u(tilesets[1]->getCellWidth(), tilesets[1]->getCellHeight()), effectsTab);
    std::unique_ptr<Display> ptrEffectsDisplay (new Display(surfaceEffects));

    surfaces.at(1) = move(ptrEffectsDisplay);
}

void StateLayer::setCommandTab(const std::array<int,12>& commandTab) {
    this->commandTab = commandTab;
}

const std::array<int,12>& StateLayer::getCommandTab() const {
     return commandTab;
}

void StateLayer::setSlotTab(const std::array<int,6>& slotTab) {
    this->slotTab = slotTab;
}

const std::array<int,6>& StateLayer::getSlotTab() const {
     return slotTab;
}

void StateLayer::setEffectsTab(const std::vector<std::vector<int>>& effectsTab) {
    this->effectsTab = effectsTab;
}

const std::vector<std::vector<int>>& StateLayer::getEffectsTab() const {
     return effectsTab;
}

bool StateLayer::getButtonReadyToClick() const {
    return buttonReadyToClick;
}
void StateLayer::setButtonReadyToClick(bool buttonReadyToClick){
    this->buttonReadyToClick = buttonReadyToClick;
}

void StateLayer::writeStatistics (state::State& stateLayer, sf::RenderWindow& window) {
    
    sf::Font font;
	if(!font.loadFromFile("../res/Roboto/Roboto-Regular.ttf")) {
        cerr << "Can't load font file" <<  endl;
    }
	for (unsigned int i = 0 ; i < stateLayer.players.size() ; i++ ) {  
        // Convert to string
        int idColor = stateLayer.getPlayers()[i]->getTileCode();
        std::string robotColor = "null";
        if (idColor == 0) {
            robotColor = "(pink)";
        } else if (idColor == 1) {
             robotColor = "(blue)";
        } else if (idColor == 2) {
             robotColor = "(yellow)";
        } else if (idColor == 3) {
             robotColor = "(orange)";
        } else if (idColor == 4) {
             robotColor = "(red)";
        }
        std::string robotNumber = std::to_string(i+1);
        std::string robotLifes = std::to_string(stateLayer.getPlayers()[i]->getLifeNumber());     
        std::string robotHP = std::to_string(stateLayer.getPlayers()[i]->getLifePoints()); 

        sf::Text text("Robot" + robotNumber + " " + robotColor + " | L : " + robotLifes + "/3 | HP : " + robotHP + "/5", font);
        text.setCharacterSize(13);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        text.setPosition(650, 320 + (20 * i));
        window.draw(text);
    }
}

void StateLayer::writeEndGame (state::State& stateLayer, sf::RenderWindow& windows) {
    
    sf::Font font;
	if(!font.loadFromFile("../res/Roboto/Roboto-Regular.ttf")) {
        cerr << "Can't load font file" <<  endl;
    }
    if (stateLayer.getEndGame() == true) {
            sf::Text text("end of THE GAME ;)", font);
            text.setCharacterSize(30);
            text.setStyle(sf::Text::Bold);
            text.setFillColor(sf::Color::Red);
            text.setPosition(180, 280);
            window.draw(text);
    }
}

void StateLayer::writeButton (sf::RenderWindow& window) {
    sf::Font font;
	if(!font.loadFromFile("../res/Roboto/Roboto-Regular.ttf")) {
        cerr << "Can't load font file" <<  endl;
    }
    sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(80, 40));
	rectangle.setPosition(730, 250);
    if (buttonReadyToClick == 1) {
        rectangle.setFillColor(sf::Color::Green);
		window.draw(rectangle);

    } else if (buttonReadyToClick == 0) {
        rectangle.setFillColor(sf::Color::Red);
		window.draw(rectangle);
    }

    /* Display the text of the send button */
    sf::Text text("Validate", font);
    text.setCharacterSize(17);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition(735, 260);
    window.draw(text);
}

void StateLayer::eventManager (const std::shared_ptr<state::State> ptrMyState, sf::RenderWindow& myWindow, StateLayer& myStateLayer) {
    /* Click management in loop */
	sf::Event event;
	while (myWindow.pollEvent(event)){
		if (event.type == sf::Event::Closed)
			window.close();
		myStateLayer.clickManager(*ptrMyState, event);
	}
	window.clear();
	myStateLayer.draw(*ptrMyState, myWindow);
}


void StateLayer::clickManager (state::State& state, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            int idCommandClicked = -1;
            int slotPosition; 
            std::array<int, 6> mySlot = getSlotTab();

            for (int i = 0 ; i < 6 ; i++) {
                if (mySlot[i] == 0) {
                    slotPosition = i;
                    break;
                } else {
                    slotPosition = 6;
                }
            }
            cout<<"Slot position deb : "<<slotPosition<<endl;
            
            /* Tab with coordiantes will be generated to accept multiple sizes of maps */
            /* Clic in the command zone */
            if ((event.mouseButton.x > 690) && (event.mouseButton.x < 730)
            && (event.mouseButton.y > 100) && (event.mouseButton.y < 140)) {
                idCommandClicked = 0;
            } else if ((event.mouseButton.x > 730) && (event.mouseButton.x < 770)
            && (event.mouseButton.y > 100) && (event.mouseButton.y < 140)) {
                idCommandClicked = 1;
            } else if ((event.mouseButton.x > 770) && (event.mouseButton.x < 810)
            && (event.mouseButton.y > 100) && (event.mouseButton.y < 140)) {
                idCommandClicked = 2;
            } else if ((event.mouseButton.x > 810) && (event.mouseButton.x < 850)
            && (event.mouseButton.y > 100) && (event.mouseButton.y < 140)) {
                idCommandClicked = 3;
            } else if ((event.mouseButton.x > 690) && (event.mouseButton.x < 730)
            && (event.mouseButton.y > 140) && (event.mouseButton.y < 180)) {
                idCommandClicked = 4;
            } else if ((event.mouseButton.x > 730) && (event.mouseButton.x < 770)
            && (event.mouseButton.y > 140) && (event.mouseButton.y < 180)) {
                idCommandClicked = 5;
            } else if ((event.mouseButton.x > 770) && (event.mouseButton.x < 810)
            && (event.mouseButton.y > 140) && (event.mouseButton.y < 180)) {
                idCommandClicked = 6;
            } else if ((event.mouseButton.x > 810) && (event.mouseButton.x < 850)
            && (event.mouseButton.y > 140) && (event.mouseButton.y < 180)) {
                idCommandClicked = 7;
            } else if ((event.mouseButton.x > 690) && (event.mouseButton.x < 730)
            && (event.mouseButton.y > 180) && (event.mouseButton.y < 220)) {
                idCommandClicked = 8;
            } else if ((event.mouseButton.x > 730) && (event.mouseButton.x < 770)
            && (event.mouseButton.y > 180) && (event.mouseButton.y < 220)) {
                idCommandClicked = 9;
            } else if ((event.mouseButton.x > 770) && (event.mouseButton.x < 810)
            && (event.mouseButton.y > 180) && (event.mouseButton.y < 220)) {
                idCommandClicked = 10;
            } else if ((event.mouseButton.x > 810) && (event.mouseButton.x < 850)
            && (event.mouseButton.y > 180) && (event.mouseButton.y < 220)) {
                idCommandClicked = 11;
            }
            /* Clic in the slot bar */
            else if ((event.mouseButton.x > 645) && (event.mouseButton.x < 685)
            && (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
                idCommandClicked = 20;
            } else if ((event.mouseButton.x > 685) && (event.mouseButton.x < 725)
            && (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
                idCommandClicked = 21;
            } else if ((event.mouseButton.x > 725) && (event.mouseButton.x < 765)
            && (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
                idCommandClicked = 22;
            } else if ((event.mouseButton.x > 765) && (event.mouseButton.x < 805)
            && (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
                idCommandClicked = 23;
            } else if ((event.mouseButton.x > 805) && (event.mouseButton.x < 845)
            && (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
                idCommandClicked = 24;
            } else if ((event.mouseButton.x > 845) && (event.mouseButton.x < 885)
            && (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
                idCommandClicked = 25;
            }
            /* Click on the button */
            else if ((event.mouseButton.x > 730) && (event.mouseButton.x < 810)
            && (event.mouseButton.y > 250) && (event.mouseButton.y < 290)) {
                idCommandClicked = 30;
            }
            
            /* A command has been clicked */
            if (idCommandClicked >= 0 && idCommandClicked <= 11) {
                /* Get command's disposition on the interface */
                std::array<int, 12> myCommand = getCommandTab();
                if (slotPosition <= 5 ) {
                    slotPosition ++;
                }
                if (myCommand[idCommandClicked] != 0) {
                    /* Put command in the last free space */              
                    for (int i = 0 ; i < 6 ; i++) {
                        if(mySlot[i] == 0){
                            mySlot[i] = myCommand[idCommandClicked];
                            setSlotTab(mySlot);
                            break; 
                        }
                    }
                }					
            }
            /* Clean slot bar after click */
            else if (idCommandClicked >= 20 && idCommandClicked <= 25) {
                slotPosition = idCommandClicked - 20;
                for (int i = 5 ; i >= 0 ; i--) {
                    /* On supprime les actions derrière l'action cliquée */
                    if (i >= slotPosition) {
                        mySlot[i] = 0;
                    }
                }					
                setSlotTab(mySlot);
            }
            /* Click on validate button */
            else if (idCommandClicked == 30) {
                /* Cast int to Actoion before sending them */
                if (slotPosition == 6) {
                    std::array<Action, 6> actionSlotTab;
                    std::unique_ptr<Robot>& ptrRobot = state.getPlayers()[0];
                    for (int i = 0; i < 6 ; i++) {
                        actionSlotTab[i] = static_cast<Action>(mySlot[i]);
                    }
                    ptrRobot->setRobotActions(actionSlotTab);
                    cout<<"commandes envoyées"<<endl;
                    
                    /* Player has choosen his actions, it sends a notification to Engine */
                    notifyObservators(0, 1);



                    StateEvent stateEvent(ALL_CHANGED);
                    state.notifyObservers(stateEvent, state);
                }                
            }

            /* Refreshing of the command pannel */
            if (slotPosition == 6) {
                /* Slot is full no need to display commands */
                setCommandTab({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            } else if (slotPosition == 5) {
                if (mySlot[slotPosition - 1] == 7) {
                    /* Basic cross arrow */
                    setCommandTab({0, 1, 0, 0, 3, 0, 4, 0, 0, 2, 0, 0});
                } else {
                    /* Classical command without boost */
                    setCommandTab({8, 1, 9, 0, 5, 0, 6, 0, 0, 2, 0, 0});
                }   
            } else if (slotPosition == 0) {
                /* Classical display */ 
                setCommandTab({8, 1, 9, 0, 5, 7, 6, 0, 0, 2, 0, 0});
            } else {
                if (mySlot[slotPosition - 1] == 7) {
                    /* Basic cross arrow with boost */
                    setCommandTab({0, 1, 0, 0, 3, 7, 4, 0, 0, 2, 0, 0});
                } else {
                    /* Classical display */ 
                    setCommandTab({8, 1, 9, 0, 5, 7, 6, 0, 0, 2, 0, 0});
                }
            }
            /* Refresh validate button */
            if (mySlot[5] != 0) {
                setButtonReadyToClick(1);						
            } else {
                setButtonReadyToClick(0);
            }		
            cout<<"Slot position fin : "<<slotPosition<<endl;
            refreshCommand();
            refreshSlot();
   		}
	}
}

void StateLayer::draw (state::State& stateLayer, sf::RenderWindow& window){
    window.clear();
    window.draw(*surfaces[0]);
    window.draw(*surfaces[1]);
    window.draw(*surfaces[2]);
    window.draw(*surfaces[3]);
    window.draw(*surfaces[4]);
    writeButton(window);
    writeStatistics(stateLayer, window);
    writeEndGame(stateLayer, window);
    window.display();
}
