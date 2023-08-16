#include "pico/stdlib.h"

#include "quest/state.h"



void quest_state_manager_initialize(struct quest_state_manager* manager) {
	manager->current_state = 0;

	manager->is_running = false;

	manager->next_action_time = 0;
	manager->target_interval = 0;
	manager->previous_time = 0;
}

void quest_state_manager_set_current_state(struct quest_state_manager* manager, const struct quest_state* state) {
	if(manager->is_running) {
		if(manager->current_state) {
			manager->current_state->terminate();
		}

		state->initialize();
	}

	manager->current_state = state;
}

void quest_state_manager_set_ups(struct quest_state_manager* manager, uint32_t ups) {
	manager->target_interval = 1000000 / ups;
}

void quest_state_manager_start(struct quest_state_manager* manager) {
	if(manager->is_running) {
		return;
	}

	manager->is_running = true;

	if(manager->current_state) {
		manager->current_state->initialize();
	}
}

void quest_state_manager_stop(struct quest_state_manager* manager) {
	if(!manager->is_running) {
		return;
	}

	if(manager->current_state) {
		manager->current_state->terminate();
	}

	manager->is_running = false;
}

void quest_state_manager_update(struct quest_state_manager* manager) {
	uint32_t current_time = time_us_32();

	if(current_time >= manager->next_action_time) {
		uint32_t delta_time = current_time - manager->previous_time;
		manager->previous_time = current_time;

		if(manager->current_state) {
			manager->current_state->update(delta_time);
			manager->current_state->render();
		}

		manager->next_action_time = current_time + manager->target_interval;
	}
}

bool quest_state_manager_is_running(struct quest_state_manager* manager) {
	return manager->is_running;
}

void quest_state_manager_terminate(struct quest_state_manager* manager) {
	(void) manager;
}
