#include "engine.h"
#include "../render.h"
#include "state.h"
#include "../client.h"
#include "ai.h"
#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include "../../../extern/jsoncpp-1.8.0/jsoncpp.cpp"

#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"
#include "../client.h"
#include "../render.h"

#define MAP_FILE "../res/map.txt"

using namespace state;
using namespace engine;
using namespace render;
using namespace std;
using namespace client;
using namespace ai;

void thread_moteur(void* ptr, int i){
	Engine* ptr_moteur=(Engine*)ptr;
	usleep(1000);
	//ptr_moteur->update();
	ptr_moteur->executeAction(i);
	ptr_moteur->getMyState()->checkEndGame();
}

NetworkClient::NetworkClient (std::string& url, int port, sf::RenderWindow& window): url(url), port(port),window(window){
	myEngine.initEngine(MAP_FILE);
	ptrClientState = myEngine.getMyState();

	StateLayer statelay(*ptrClientState, window);
	statelay.initSurface(*ptrClientState);
}

void NetworkClient::run (){
    cout<<"Client is running"<<endl;
    string name;
    cout<<"Enter your username : ";
    cin>>name;

    sf::Http http(url, port);
                
    sf::Http::Request request1;
    request1.setMethod(sf::Http::Request::Post);
    request1.setUri("/player");
    request1.setHttpVersion(5, 0);
    request1.setField("name","free");
    string body="{\"req\" : \"POST\", \"name\":\"" + name + "\", \"free\":true}"; 
    request1.setBody(body);
                
    sf::Http::Response response1 = http.sendRequest(request1);

    Json::Reader jsonReader;
    Json::Value rep1;
    if(jsonReader.parse(response1.getBody(),rep1)){
        int playerId=rep1["id"].asInt();
        cout<<"You joined the game successfully."<<endl;
        cout<<"Your robot number is : "<<playerId<<endl << "\n";
        this->networkId=playerId;
        cout<< "List of robots on the server : "<<endl;
        for(int j=1; j<=playerId; j++){
            sf::Http::Request request2;
            request2.setMethod(sf::Http::Request::Get);
            string uri="/player/"+ to_string(j);
                            
            request2.setUri(uri);
            request2.setHttpVersion(5, 0);
            request2.setField("name","free");

            sf::Http::Response response2 = http.sendRequest(request2);
            Json::Reader jsonReader2;
            Json::Value rep2;
                        
            if (jsonReader.parse(response2.getBody(), rep2)){	
                string name=rep2["name"].asString();
                cout<<"	-"<<name<<endl;
            }
        }		

        cout<<"\nPress 'r' to Run or 'e' to Exit"<<endl;

        char entry;
        while(entry=getchar()) {
            if (entry=='e') {
                /* exit */
                sf::Http::Request request3;
                request3.setMethod(sf::Http::Request::Post);
                string uri2="/player/"+ to_string(playerId);
                request3.setUri(uri2);
                request3.setHttpVersion(5, 0);
                request3.setField("name","free");
                string body3="D"; 
                request3.setBody(body3);
                http.sendRequest(request3);
                cout<<""<<endl;
                cout<<"Player "<< playerId << " has been deleted."<<endl;
                cout<<""<<endl;
                                    
                cout<< "List of remaining players : "<<endl;
                for(int k=1; k<=15; k++){	
                    sf::Http::Request request4;
                    request4.setMethod(sf::Http::Request::Get);
                        string uri="/player/"+ to_string(k);
                    request4.setUri(uri);
                    request4.setHttpVersion(5, 0);
                    request4.setField("name","free");
                                        
                    sf::Http::Response response4 = http.sendRequest(request4);
                                        
                    Json::Reader jsonReader4;
                    Json::Value rep4;
                                                
                    if (jsonReader.parse(response4.getBody(), rep4)){
                        string nom4=rep4["name"].asString();
                        cout<<"	-"<<nom4<<endl;
                    }
                }
            }
           
            else if (entry =='r') {
                /* run */
                myEngine.initEngine(MAP_FILE);
                ptrClientState = myEngine.getMyState();

                StateLayer statelay(*ptrClientState, window);
                statelay.initSurface(*ptrClientState);
                
                StateLayer* ptr_stateLayer = &statelay;
	            myEngine.getMyState()->registerObserver(ptr_stateLayer);
                
                ai::HeuristicAI aiRobot(1);
                ptrClientState->initRobot(ORANGE);
                while (window.isOpen()){
                    statelay.eventManager(ptrClientState, window, statelay);

                    /* Actions processed when all players have selected their actions */
                    if (myEngine.checkRobotsActions()) {

                        aiRobot.run(myEngine);
                        for (int i = 0 ; i < 6 ; i++) {
                            if (!myEngine.getMyState()->getEndGame()) {
                                std::thread th(thread_moteur,&myEngine,i);
                                cout<<"Thread created!"<<endl;
                                th.join();
                                
                                /* Refresh and display what needs to be */			
                                StateEvent majDisponibilite(ALL_CHANGED);
                                myEngine.getMyState()->notifyObservers(majDisponibilite, *myEngine.getMyState());
                                    
                                sf::sleep(sf::seconds(0.5));
                            }
                        }
                        myEngine.endOfRound();		
                    }
                }
            }
        }
    }
    else{
        cout<<"There is no server or there are already 2 players which is the maximum."<<endl;
    }
}

void NetworkClient::sendCommands (std::array<state::Action, 6> actions){
    sf::Http::Request requestCommand;
    requestCommand.setMethod(sf::Http::Request::Post);
    requestCommand.setUri("/player");
    requestCommand.setHttpVersion(5, 0);
    requestCommand.setField("name","free");
    //string body="{\"req\" : \"POST\", \"name\":\"" + name + "\", \"free\":true}";
    //"name\":\"" + name + "\",
    string body=
        string("{\"req\" : \"POST\", ") +
        string("\"networkID\": \"" + std::to_string(networkId) +"\", ") +
        string("\"action0\": \"" + std::to_string(actions[0]) +"\", ") +
        string("\"action1\": \"" + std::to_string(actions[1]) +"\", ") +
        string("\"action2\": \"" + std::to_string(actions[2]) +"\", ") +
        string("\"action3\": \"" + std::to_string(actions[3]) +"\", ") +
        string("\"action4\": \"" + std::to_string(actions[4]) +"\", ") +
        string("\"action5\": \"" + std::to_string(actions[5]) +"\", ") +
        string("\"free\":true}");
    requestCommand.setBody(body);
}
