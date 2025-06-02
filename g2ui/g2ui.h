/*
 * MIT License
 *
 * Copyright (c) 2025 Grzegorz Grzęda
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following c onditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef G2UI_H
#define G2UI_H
#include <stddef.h>
#include <stdint.h>

typedef enum g2ui_event_type {
    G2UI_EVENT_TYPE_PRESS,
} g2ui_event_type_t;

typedef struct g2ui_event {
    g2ui_event_type_t type;
    union {
        struct {
            int x;  // X coordinate of the event
            int y;  // Y coordinate of the event
        } press;    // Data for press events
    } data;
} g2ui_event_t;

typedef enum g2ui_display_color_mode {
    G2UI_DISPLAY_COLOR_MODE_MONO_1BPP,
} g2ui_display_color_mode_t;

typedef struct g2ui_display g2ui_display_t;

typedef void (*g2ui_hal_display_update_cb_t)(g2ui_display_t* display,
                                             const uint8_t* buffer,
                                             size_t size,
                                             void* user_data);

typedef uint32_t (*g2ui_hal_timer_get_ticks_cb_t)(void);

typedef struct g2ui_display_configuration {
    uint16_t width;
    uint16_t height;
    uint8_t* ping_buffer;
    uint8_t* pong_buffer;
    size_t buffer_size;
    g2ui_display_color_mode_t color_mode;
    g2ui_hal_display_update_cb_t update_callback;
} g2ui_display_configuration_t;

typedef struct g2ui_obj g2ui_obj_t;

typedef void (*g2ui_obj_event_callback_t)(g2ui_obj_t* obj, g2ui_event_t event, void* user_data);

void g2ui_init(void);

void g2ui_hal_timer_init(g2ui_hal_timer_get_ticks_cb_t get_ticks_callback);
void g2ui_hal_timer_increment_ms(uint32_t ms);

void g2ui_hal_display_update_complete(g2ui_display_t* display);

g2ui_display_t* g2ui_display_create(g2ui_display_configuration_t* config, void* user_data);
void g2ui_display_set_active(g2ui_display_t* display);

g2ui_obj_t* g2ui_screen_create(g2ui_display_t* display);
void g2ui_screen_set_active(g2ui_obj_t* screen);

void g2ui_obj_set_name(g2ui_obj_t* obj, const char* name);
void g2ui_obj_set_position(g2ui_obj_t* obj, int x, int y);
void g2ui_obj_set_size(g2ui_obj_t* obj, int width, int height);
void g2ui_obj_set_visible(g2ui_obj_t* obj, int visible);
void g2ui_obj_set_index(g2ui_obj_t* obj, uint16_t index);
void g2ui_obj_set_select_index(g2ui_obj_t* obj, uint16_t select_index);
void g2ui_obj_set_on_event(g2ui_obj_t* obj, g2ui_obj_event_callback_t on_event, void* user_data);

g2ui_obj_t* g2ui_sprite_create(g2ui_obj_t* parent);
void g2ui_sprite_set_image(g2ui_obj_t* sprite,
                           const uint8_t* image_data,
                           size_t image_size,
                           uint16_t width,
                           uint16_t height,
                           uint8_t bpp);
void g2ui_sprite_set_position(g2ui_obj_t* sprite, int x, int y);
void g2ui_sprite_set_frame(g2ui_obj_t* sprite, uint16_t frame);
void g2ui_sprite_set_visible(g2ui_obj_t* sprite, int visible);

g2ui_obj_t* g2ui_label_create(g2ui_obj_t* parent);
void g2ui_label_set_text(g2ui_obj_t* label, const char* text);
void g2ui_label_set_text_color(g2ui_obj_t* label, uint32_t color);
void g2ui_label_set_background_color(g2ui_obj_t* label, uint32_t color);
void g2ui_label_set_font(g2ui_obj_t* label, const char* font_name);
void g2ui_label_set_alignment(g2ui_obj_t* label, int alignment);

g2ui_obj_t* g2ui_button_create(g2ui_obj_t* parent);
void g2ui_button_set_background_color(g2ui_obj_t* button, uint32_t color);
void g2ui_button_set_font(g2ui_obj_t* button, const char* font_name);
void g2ui_button_set_alignment(g2ui_obj_t* button, int alignment);
void g2ui_button_set_on_click(g2ui_obj_t* button,
                              void (*on_click)(g2ui_obj_t* button, void* user_data),
                              void* user_data);
void g2ui_button_set_selected(g2ui_obj_t* button, int selected);

g2ui_obj_t* g2ui_checkbox_create(g2ui_obj_t* parent);
void g2ui_checkbox_set_selected(g2ui_obj_t* checkbox, int selected);

#endif  // G2UI_H