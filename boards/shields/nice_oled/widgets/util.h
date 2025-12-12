#pragma once

#include <lvgl.h>
#include <zmk/endpoints.h>
#undef CANVAS_WIDTH
#define CANVAS_WIDTH 32
#undef CANVAS_HEIGHT
#define CANVAS_HEIGHT 128

#ifndef LVGL_BACKGROUND
#define LVGL_BACKGROUND lv_color_black()
#endif

#ifndef LVGL_FOREGROUND
#define LVGL_FOREGROUND lv_color_white()
#endif

struct status_state {
  uint8_t battery;
  bool charging;
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  struct zmk_endpoint_instance selected_endpoint;
  int active_profile_index;
  bool active_profile_connected;
  bool active_profile_bonded;
  uint8_t layer_index;
  const char *layer_label;
  uint8_t wpm[10];
  uint8_t mod_state;
#else
  bool connected;
#endif
};

void to_uppercase(char *str);
void rotate_canvas(lv_obj_t *canvas, lv_color_t cbuf[]);
void draw_background(lv_obj_t *canvas);
void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color);
void init_line_dsc(lv_draw_line_dsc_t *line_dsc, lv_color_t color, uint8_t width);
void init_label_dsc(lv_draw_label_dsc_t *label_dsc, lv_color_t color, const lv_font_t *font, lv_text_align_t align);