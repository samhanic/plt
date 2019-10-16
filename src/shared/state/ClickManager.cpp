#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;

bool ClickManager::getAction(Action action) {
	
	/* Player decides to delete actions */
	if (action == DELETE_I) { 
		actionList [5] = NO_ACTION;
	} else if (action == DELETE_II) { 
		actionList [4] = NO_ACTION;
		actionList [5] = NO_ACTION;
	} else if (action == DELETE_III) { 
		actionList [3] = NO_ACTION;
		actionList [4] = NO_ACTION;
		actionList [5] = NO_ACTION;
	} else if (action == DELETE_IV) { 
		actionList [2] = NO_ACTION;
		actionList [3] = NO_ACTION;
		actionList [4] = NO_ACTION;
		actionList [5] = NO_ACTION;
	} else if (action == DELETE_V) { 
		actionList [1] = NO_ACTION;
		actionList [2] = NO_ACTION;
		actionList [3] = NO_ACTION;
		actionList [4] = NO_ACTION;
		actionList [5] = NO_ACTION;
	} else if (action == DELETE_VI) {
		actionList [0] = NO_ACTION; 
		actionList [1] = NO_ACTION;
		actionList [2] = NO_ACTION;
		actionList [3] = NO_ACTION;
		actionList [4] = NO_ACTION;
		actionList [5] = NO_ACTION;
	} /* If user click on a correct action and has remainig action slot */ 
	else if (action  <= 1 || action >=12 ) {
		for (int i = 0 ; i <=6 ; i++){
			if (actionList [i] == NO_ACTION) {
				actionList [i] = action;
				i = 6;
			}			
		}
		return false;	
	} else if (action == VALIDATE) {
		return true;	
	} else {
		return false;
	}
	
	/* Player validate action set */
	if (action == VALIDATE) {
		return true;	
	} else {
		return false;
	}
}
