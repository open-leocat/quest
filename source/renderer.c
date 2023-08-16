#include "quest/renderer.h"

#include <limits.h>



void quest_renderer_initialize(struct quest_renderer* renderer) {
	renderer->display = 0;
	renderer->camera_x = 0;
	renderer->camera_y = 0;
	renderer->camera_range_x_minimum = INT16_MIN;
	renderer->camera_range_x_maximum = INT16_MAX;
	renderer->camera_range_y_minimum = INT16_MIN;
	renderer->camera_range_y_maximum = INT16_MAX;
}

void quest_renderer_set_display(struct quest_renderer* renderer, struct quest_display* display) {
	renderer->display = display;
}

void quest_renderer_set_camera_range_minimum(struct quest_renderer* renderer, int16_t camera_range_x_minimum, int16_t camera_range_y_minimum) {
	renderer->camera_range_x_minimum = camera_range_x_minimum;
	renderer->camera_range_y_minimum = camera_range_y_minimum;
}

void quest_renderer_set_camera_range_maximum(struct quest_renderer* renderer, int16_t camera_range_x_maximum, int16_t camera_range_y_maximum) {
	renderer->camera_range_x_maximum = camera_range_x_maximum;
	renderer->camera_range_y_maximum = camera_range_y_maximum;
}

void quest_renderer_set_camera_x(struct quest_renderer* renderer, int16_t camera_x) {
	renderer->camera_x = camera_x;
}

void quest_renderer_set_camera_y(struct quest_renderer* renderer, int16_t camera_y) {
	renderer->camera_y = camera_y;
}

void quest_renderer_center(struct quest_renderer* renderer, int16_t x, int16_t y, uint16_t width, uint16_t height) {
	int16_t new_camera_x = (int16_t) x - (((int16_t) quest_display_width - (int16_t) width) / 2);
	int16_t new_camera_y = (int16_t) y - (((int16_t) quest_display_height - (int16_t) height) / 2);

	quest_renderer_set_camera_x(renderer, new_camera_x);
	quest_renderer_set_camera_y(renderer, new_camera_y);
}

/* TODO: Optimize */
bool quest_renderer_is_visible(struct quest_renderer* renderer, int16_t x, int16_t y, uint16_t width, uint16_t height) {
	int16_t ranged_camera_x = (renderer->camera_x < renderer->camera_range_x_minimum) ? renderer->camera_range_x_minimum : (renderer->camera_x > renderer->camera_range_x_maximum) ? renderer->camera_range_x_maximum : renderer->camera_x;
	int16_t ranged_camera_y = (renderer->camera_y < renderer->camera_range_y_minimum) ? renderer->camera_range_y_minimum : (renderer->camera_y > renderer->camera_range_y_maximum) ? renderer->camera_range_y_maximum : renderer->camera_y;

	int16_t visible_left = ranged_camera_x;
	int16_t visible_right = ranged_camera_x + quest_display_width;
	int16_t visible_top = ranged_camera_y;
	int16_t visible_bottom = ranged_camera_y + quest_display_height;

	if (x + width >= visible_left && x <= visible_right && y + height >= visible_top && y <= visible_bottom) {
		return true;
	}
 
	return false;
}

void quest_renderer_draw_sprite(struct quest_renderer* renderer, int16_t x, int16_t y, const struct quest_sprite* sprite) {
	int16_t ranged_camera_x = (renderer->camera_x < renderer->camera_range_x_minimum) ? renderer->camera_range_x_minimum : (renderer->camera_x > renderer->camera_range_x_maximum) ? renderer->camera_range_x_maximum : renderer->camera_x;
	int16_t ranged_camera_y = (renderer->camera_y < renderer->camera_range_y_minimum) ? renderer->camera_range_y_minimum : (renderer->camera_y > renderer->camera_range_y_maximum) ? renderer->camera_range_y_maximum : renderer->camera_y;

	if(renderer->display && quest_renderer_is_visible(renderer, x, y, sprite->width, sprite->height)) {
		quest_display_set_bitmap(renderer->display, x - ranged_camera_x, y - ranged_camera_y, sprite->width, sprite->height, sprite->data);
	}
}

void quest_renderer_terminate(struct quest_renderer* renderer) {
	(void) renderer;
}
