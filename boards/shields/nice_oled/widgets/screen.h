#pragma once
#ifndef SCREEN_H_
#define SCREEN_H_

#include "util.h"
#include <lvgl.h>
#include <zephyr/kernel.h>

  sys_snode_t node;
  lv_obj_t *obj;
  uint8_t cbuf[LV_CANVAS_BUF_SIZE(CANVAS_WIDTH, CANVAS_HEIGHT, 1, LV_COLOR_FORMAT_I1)];
  struct status_state state;
};

int zmk_widget_screen_init(struct zmk_widget_screen *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_screen_obj(struct zmk_widget_screen *widget);
#endif
