#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

using namespace std;

int main(int argc,char* argv[])
{
    /* Test le nombre d'argument dan sle terminal */
    if ( argc != 2 )
		cout<<"usage: "<< argv[0] <<" <command>\n";
	
	//arg = std::cout << argv[1] << std::endl;
	string entry = argv[1];
	if (entry == "Hello") {
		cout << "Hello world" << endl;
	} else if (entry == "state") {
		system("make code-coverage");
	} else {
		cout << "Fonction doesn't exist" << endl;
	}
	return 0;
}
