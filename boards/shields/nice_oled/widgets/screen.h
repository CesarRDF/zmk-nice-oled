#pragma once
#ifndef SCREEN_H_
#define SCREEN_H_

#include "util.h"
#include <lvgl.h>
#include <stdint.h>
#include <zephyr/kernel.h>

struct zmk_widget_screen {
  sys_snode_t node;
  lv_obj_t *obj;
  /* LVGL v9 I1 format requires 8 bytes for palette (2 * 4 bytes) */
  uint8_t cbuf[(CANVAS_WIDTH * CANVAS_HEIGHT) / 8 + 8];
  struct status_state state;
};

int zmk_widget_screen_init(struct zmk_widget_screen *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_screen_obj(struct zmk_widget_screen *widget);
#endif
