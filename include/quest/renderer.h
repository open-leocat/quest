#ifndef QUEST_RENDERER_H
#define QUEST_RENDERER_H

#include "quest/display.h"

#include <stdbool.h>
#include <stdint.h>



struct quest_sprite {
	/* Maximum sprite size: 16x16, 1 bit bitmap */
	const uint8_t width : 4;
	const uint8_t height : 4;
	const uint8_t* data;
};

struct quest_renderer {
	struct quest_display* display;

	int16_t camera_range_x_minimum;
	int16_t camera_range_x_maximum;
	int16_t camera_range_y_minimum;
	int16_t camera_range_y_maximum;
	int16_t camera_x;
	int16_t camera_y;
};

void quest_renderer_initialize(struct quest_renderer* renderer);
void quest_renderer_set_display(struct quest_renderer* renderer, struct quest_display* display);
void quest_renderer_set_camera_range_minimum(struct quest_renderer* renderer, int16_t camera_range_x_minimum, int16_t camera_range_y_minimum);
void quest_renderer_set_camera_range_maximum(struct quest_renderer* renderer, int16_t camera_range_x_maximum, int16_t camera_range_y_maximum);
void quest_renderer_set_camera_x(struct quest_renderer* renderer, int16_t camera_x);
void quest_renderer_set_camera_y(struct quest_renderer* renderer, int16_t camera_y);
void quest_renderer_center(struct quest_renderer* renderer, int16_t x, int16_t y, uint16_t width, uint16_t height);
bool quest_renderer_is_visible(struct quest_renderer* renderer, int16_t x, int16_t y, uint16_t width, uint16_t height);
void quest_renderer_draw_sprite(struct quest_renderer* renderer, int16_t x, int16_t y, const struct quest_sprite* sprite);
void quest_renderer_terminate(struct quest_renderer* renderer);



#endif
