#include "quest/input.h"

#include "pico/stdlib.h"



enum quest_input_pin {
	QUEST_INPUT_UP_LEFT_PIN = 7,
	QUEST_INPUT_UP_RIGHT_PIN = 8,
	QUEST_INPUT_UP_CENTER_PIN,
	QUEST_INPUT_DOWN_LEFT_PIN = 9,
	QUEST_INPUT_DOWN_RIGHT_PIN = 10,
	QUEST_INPUT_DOWN_CENTER_PIN
};

void quest_input_initialize() {
	gpio_init(QUEST_INPUT_UP_LEFT_PIN);
	gpio_set_dir(QUEST_INPUT_UP_LEFT_PIN, GPIO_IN);
	gpio_pull_up(QUEST_INPUT_UP_LEFT_PIN);

	gpio_init(QUEST_INPUT_UP_RIGHT_PIN);
	gpio_set_dir(QUEST_INPUT_UP_RIGHT_PIN, GPIO_IN);
	gpio_pull_up(QUEST_INPUT_UP_RIGHT_PIN);

	gpio_init(QUEST_INPUT_DOWN_LEFT_PIN);
	gpio_set_dir(QUEST_INPUT_DOWN_LEFT_PIN, GPIO_IN);
	gpio_pull_up(QUEST_INPUT_DOWN_LEFT_PIN);

	gpio_init(QUEST_INPUT_DOWN_RIGHT_PIN);
	gpio_set_dir(QUEST_INPUT_DOWN_RIGHT_PIN, GPIO_IN);
	gpio_pull_up(QUEST_INPUT_DOWN_RIGHT_PIN);
}

bool quest_input_is_pressed(enum quest_input input) {
	enum quest_input_pin pin;

	switch(input) {
		case QUEST_INPUT_UP_LEFT:
			pin = QUEST_INPUT_UP_LEFT_PIN;
			break;
		case QUEST_INPUT_UP_RIGHT:
			pin = QUEST_INPUT_UP_RIGHT_PIN;
			break;
		case QUEST_INPUT_UP_CENTER:
			pin = QUEST_INPUT_UP_CENTER_PIN;
			break;
		case QUEST_INPUT_DOWN_LEFT:
			pin = QUEST_INPUT_DOWN_LEFT_PIN;
			break;
		case QUEST_INPUT_DOWN_RIGHT:
			pin = QUEST_INPUT_DOWN_RIGHT_PIN;
			break;
		case QUEST_INPUT_DOWN_CENTER:
			pin = QUEST_INPUT_DOWN_CENTER_PIN;
			break;
		default:
			return false;
			break;
	}

	return !gpio_get(pin);
}
