#ifndef QUEST_STATE_H
#define QUEST_STATE_H

#include <stdbool.h>
#include <stdint.h>



struct quest_state_manager {
	const struct quest_state* current_state;

	bool is_running;

	uint32_t next_action_time;
	uint32_t target_interval;
	uint32_t previous_time;
};

struct quest_state {
	void (*initialize)();
	void (*update)(uint32_t delta_time);
	void (*render)();
	void (*terminate)();
};



void quest_state_manager_initialize(struct quest_state_manager* manager);
void quest_state_manager_set_current_state(struct quest_state_manager* manager, const struct quest_state* state);
void quest_state_manager_set_ups(struct quest_state_manager* manager, uint32_t ups);
void quest_state_manager_start(struct quest_state_manager* manager);
void quest_state_manager_stop(struct quest_state_manager* manager);
void quest_state_manager_update(struct quest_state_manager* manager);
bool quest_state_manager_is_running(struct quest_state_manager* manager);
void quest_state_manager_terminate(struct quest_state_manager* manager);



#endif
