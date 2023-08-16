#ifndef QUEST_INPUT_H
#define QUEST_INPUT_H

#include <stdbool.h>



enum quest_input {
	QUEST_INPUT_UP_LEFT,
	QUEST_INPUT_UP_RIGHT,
	QUEST_INPUT_UP_CENTER,
	QUEST_INPUT_DOWN_LEFT,
	QUEST_INPUT_DOWN_RIGHT,
	QUEST_INPUT_DOWN_CENTER
};



void quest_input_initialize();
bool quest_input_is_pressed(enum quest_input input);



#endif
