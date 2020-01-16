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


using namespace state;
using namespace engine;
using namespace render;
using namespace std;
using namespace client;
using namespace ai;

NetworkClient::NetworkClient (std::string& url, int port, sf::RenderWindow& window): url(url), port(port),window(window){

}

void NetworkClient::run (){
    cout<<"---- SERVER TEST ----"<<endl;
    string name;
    cout<<"Enter your username : ";
    cin>>name;

    sf::Http http("http://localhost/", 8080);
                
    sf::Http::Request request1;
    request1.setMethod(sf::Http::Request::Post);
    request1.setUri("/player");
    request1.setHttpVersion(1, 0);
    request1.setField("name","free");
    string body="{\"req\" : \"POST\", \"name\":\"" + name + "\", \"free\":true}"; 
    request1.setBody(body);
                
    sf::Http::Response response1 = http.sendRequest(request1);

    Json::Reader jsonReader;
    Json::Value rep1;
    if(jsonReader.parse(response1.getBody(),rep1)){
        int playerId=rep1["id"].asInt();
        cout<<"You joined the game successfully."<<endl;
        cout<<"Your ID is : "<<playerId<<endl << "\n";

        cout<< "List of players in the game : "<<endl;
        for(int j=1; j<=playerId; j++){
            sf::Http::Request request2;
            request2.setMethod(sf::Http::Request::Get);
            string uri="/player/"+ to_string(j);
                            
            request2.setUri(uri);
            request2.setHttpVersion(1, 0);
            request2.setField("name","free");

            sf::Http::Response response2 = http.sendRequest(request2);
            Json::Reader jsonReader2;
            Json::Value rep2;
                        
            if (jsonReader.parse(response2.getBody(), rep2)){	
                string name=rep2["name"].asString();
                cout<<"	-"<<name<<endl;
            }
        }		

        cout<<"\nPress d and then enter to disconnect the last player from the server."<<endl;

        while(getchar()!='d'){}
        sf::Http::Request request3;
        request3.setMethod(sf::Http::Request::Post);
        string uri2="/player/"+ to_string(playerId);
        request3.setUri(uri2);
        request3.setHttpVersion(1, 0);
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
            request4.setHttpVersion(1, 0);
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
    else{
        cout<<"There is no server or there are already 2 players which is the maximum."<<endl;
    }
}

