#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <thread>
#include <pthread.h>


#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"
#include "../client.h"
#include "../render.h"

using namespace state;
using namespace engine;
using namespace render;
using namespace std;
using namespace ai;
using namespace client;


bool v1=false;
bool v2=true;

void thread_moteur(void* ptr){
	Engine* ptr_moteur=(Engine*)ptr;
	while(v2){
		usleep(1000);
		if(v1){
			ptr_moteur->update();
			v1=false;
		}
	}
	
}

Client::Client (sf::RenderWindow& window): window(window) {




	// unsigned int longueur_map_cases = 25, largeur_map_cases = 25;
	// std::string chemin_fichier_map_txt = "res/map1.txt";
	// Correspondances tab_corres = Correspondances();

	// moteur.getEtat().initGrille(chemin_fichier_map_txt, longueur_map_cases, largeur_map_cases, tab_corres);
	// moteur.getEtat().initPersonnages(tab_corres);
	// moteur.getEtat().initCurseur();
	
	// moteur.onThread = true;

	// armeeRouge=new HeuristicIA();
	// armeeBleue= new HeuristicIA();
	// armeeBleue->setCamp(true);
	// demarrage = true ;

	// moteur.registerObserver(this);
	
}


void Client::run (){


	// sf::Event event;
	// StateLayer stateLayer(moteur.getEtat(), window);
	// stateLayer.initSurfaces(moteur.getEtat());
										
	// StateLayer* ptr_stateLayer=&stateLayer;
	// moteur.getEtat().registerObserver(ptr_stateLayer);
	// Moteur* ptr_moteur=&moteur;
	// stateLayer.registerObserver(ptr_moteur);

	// std::thread th(thread_moteur, &moteur); //creation d'un thread qui va executer la fonction thread_moteur
	// while(!moteur.getEtat().getFin()){
	// 	if(!moteur.getEtat().getFin() && moteur.verificationFinDeTour()){
	// 		moteur.verificationDebutDeTour();
	// 		StateEvent majDisponibilite(ALLCHANGED);
	// 		moteur.getEtat().notifyObservers(majDisponibilite, moteur.getEtat());
	// 	}
	// 	if (demarrage){
	// 		stateLayer.draw(window);
								
	// 		cout << "\n\t\t--- Tour " << moteur.getEtat().getTour() << " ---\n" << endl;
			
	// 		demarrage = false;
	// 	}
		
	// 	armeeBleue->run(moteur);

	// 	armeeRouge->run(moteur);
	// 	while (window.pollEvent(event)){
	// 		// Fermeture de la fenetre
	// 		if (event.type == sf::Event::Closed){
	// 			window.close();
	// 			moteur.getEtat().setFin(true);
	// 			cout << "\tFENETRE FERMEE - PROCESSUS INTERROMPU" << endl;
	// 			break;
	// 		}
	// 	}
	// }
	// v2=false;
	// th.join();
}


