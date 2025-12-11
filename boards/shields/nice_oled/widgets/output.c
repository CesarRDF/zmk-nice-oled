#include "output.h"
#include "../assets/custom_fonts.h"
#include <zephyr/kernel.h>
#include <lvgl.h>

LV_IMG_DECLARE(bt_no_signal);
LV_IMG_DECLARE(bt_unbonded);
LV_IMG_DECLARE(bt);
LV_IMG_DECLARE(usb);

// #if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
// static void draw_usb_connected(lv_obj_t *canvas) {
//   lv_draw_img_dsc_t img_dsc;
//   lv_draw_img_dsc_init(&img_dsc);

//   lv_canvas_draw_img(canvas, 0, 34, &usb, &img_dsc);
//   // lv_canvas_draw_img(canvas, 45, 2, &usb, &img_dsc);
// }

// static void draw_ble_unbonded(lv_obj_t *canvas) {
//   lv_draw_img_dsc_t img_dsc;
//   lv_draw_img_dsc_init(&img_dsc);

//   // 36 - 39
//   lv_canvas_draw_img(canvas, -1, 32, &bt_unbonded, &img_dsc);
//   // lv_canvas_draw_img(canvas, 44, 0, &bt_unbonded, &img_dsc);
// }
// #endif

// static void draw_ble_disconnected(lv_obj_t *canvas) {
//   lv_draw_img_dsc_t img_dsc;
//   lv_draw_img_dsc_init(&img_dsc);

//   lv_canvas_draw_img(canvas, 4, 32, &bt_no_signal, &img_dsc);
//   // lv_canvas_draw_img(canvas, 49, 0, &bt_no_signal, &img_dsc);
// }

// static void draw_ble_connected(lv_obj_t *canvas) {
//   lv_draw_img_dsc_t img_dsc;
//   lv_draw_img_dsc_init(&img_dsc);

//   lv_canvas_draw_img(canvas, 4, 32, &bt, &img_dsc);
//   // lv_canvas_draw_img(canvas, 49, 0, &bt, &img_dsc);
// }

// void draw_output_status(lv_obj_t *canvas, const struct status_state *state) {
//   /*
//    * WHITOUT BACKGROUND
//   lv_draw_rect_dsc_t rect_white_dsc;
//   init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);
//   lv_canvas_draw_rect(canvas, -3, 32, 24, 15, &rect_white_dsc);
//   */

// #if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
//   switch (state->selected_endpoint.transport) {
//   case ZMK_TRANSPORT_USB:
//     draw_usb_connected(canvas);
//     break;

//   case ZMK_TRANSPORT_BLE:
//     if (state->active_profile_bonded) {
//       if (state->active_profile_connected) {
//         draw_ble_connected(canvas);
//       } else {
//         draw_ble_disconnected(canvas);
//       }
//     } else {
//       draw_ble_unbonded(canvas);
//     }
//     break;
//   }
// #else
//   if (state->connected) {
//     draw_ble_connected(canvas);
//   } else {
//     draw_ble_disconnected(canvas);
//   }
// #endif
// }

static void draw_icon(lv_obj_t *canvas, const lv_image_dsc_t *img_src, int x, int y) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);
    
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = img_src;

    // Definir el área exacta donde se pintará el icono
    lv_area_t coords;
    coords.x1 = x;
    coords.y1 = y;
    // Calculamos el punto final sumando el ancho/alto de la imagen (-1 porque empieza en 0)
    coords.x2 = x + img_src->header.w - 1;
    coords.y2 = y + img_src->header.h - 1;

    lv_draw_image(&layer, &img_dsc, &coords);
}

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
static void draw_usb_connected(lv_obj_t *canvas) {
    // Coordenadas originales: 0, 34
    draw_icon(canvas, &usb, 0, 34);
}

static void draw_ble_unbonded(lv_obj_t *canvas) {
    // Coordenadas originales: -1, 32
    draw_icon(canvas, &bt_unbonded, -1, 32);
}
#endif

static void draw_ble_disconnected(lv_obj_t *canvas) {
    // Coordenadas originales: 4, 32
    draw_icon(canvas, &bt_no_signal, 4, 32);
}

static void draw_ble_connected(lv_obj_t *canvas) {
    // Coordenadas originales: 4, 32
    draw_icon(canvas, &bt, 4, 32);
}

void draw_output_status(lv_obj_t *canvas, const struct status_state *state) {
  
  // Lógica de selección de icono (idéntica a tu código original)

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  switch (state->selected_endpoint.transport) {
  case ZMK_TRANSPORT_USB:
    draw_usb_connected(canvas);
    break;

  case ZMK_TRANSPORT_BLE:
    if (state->active_profile_bonded) {
      if (state->active_profile_connected) {
        draw_ble_connected(canvas);
      } else {
        draw_ble_disconnected(canvas);
      }
    } else {
      draw_ble_unbonded(canvas);
    }
    break;
  }
#else
  // Lógica para periféricos (lado derecho)
  if (state->connected) {
    draw_ble_connected(canvas);
  } else {
    draw_ble_disconnected(canvas);
  }
#endif
}