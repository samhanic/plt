#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

using namespace std;

int main(int argc,char* argv[])
{
    /* Gestion de la commande en entrée */
	if ( argc != 2 ) {
		cout<<"usage: "<< argv[0] <<" <command>\n";
	}
	string entry = argv[1];
	if (entry == "Hello") {
		cout << "Hello world" << endl;
	} else if (entry == "state") {
		system("make code-coverage");
	} else if (entry == "render") {

		/* TESTS DE RENDU */
		sf::RenderWindow renderWindow(sf::VideoMode(800, 550), "RobotIS");
		sf::Event event;
		sf::Texture texture;
		texture.loadFromFile("../res/map.png");

		sf::Sprite sprite(texture);

		while (renderWindow.isOpen()){
			while (renderWindow.pollEvent(event)){
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
			}

			renderWindow.clear();
			renderWindow.draw(sprite);
			renderWindow.display();
		}








	} else {
		cout << "Fonction doesn't exist" << endl;
	}
	return 0;
}
