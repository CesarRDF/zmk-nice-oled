#include "profile.h"
// use custom_fonts.h only for the draw_active_profile_text function
#include "../assets/custom_fonts.h"
#include <stdio.h>
#include <zephyr/kernel.h>
#include "util.h"
#include <lvgl.h>

LV_IMG_DECLARE(profiles);

static void draw_inactive_profiles(lv_obj_t *canvas,
                                   const struct status_state *state) {
  // lv_draw_img_dsc_t img_dsc;
  // lv_draw_img_dsc_init(&img_dsc);

  // lv_canvas_draw_img(canvas, 0, 137, &profiles, &img_dsc);
  // // lv_canvas_draw_img(canvas, 18, 129, &profiles, &img_dsc);

  lv_layer_t *layer = lv_canvas_get_layer(canvas);

    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = &profiles;

    // Área donde se dibuja la imagen
    lv_area_t coords;
    coords.x1 = 0;
    coords.y1 = 137;
    // Calculamos el final sumando el ancho de la imagen
    coords.x2 = 0 + profiles.header.w - 1;
    coords.y2 = 137 + profiles.header.h - 1;

    lv_draw_image(layer, &img_dsc, &coords);
}

static void draw_active_profile(lv_obj_t *canvas,
                                const struct status_state *state) {
  // lv_draw_rect_dsc_t rect_white_dsc;
  // init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);

  // int offset = state->active_profile_index * 7;

  // lv_canvas_draw_rect(canvas, 0 + offset, 137, 3, 3, &rect_white_dsc);
  // // lv_canvas_draw_rect(canvas, 18 + offset, 129, 3, 3, &rect_white_dsc);

  lv_layer_t *layer = lv_canvas_get_layer(canvas);

    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_FOREGROUND);

    int offset = state->active_profile_index * 7;

    // Área del rectángulo pequeño (3x3 pixeles)
    lv_area_t coords;
    coords.x1 = 0 + offset;
    coords.y1 = 137;
    coords.x2 = coords.x1 + 3 - 1; // Ancho 3
    coords.y2 = coords.y1 + 3 - 1; // Alto 3

    lv_draw_rect(layer, &rect_dsc, &coords);
}

// MC: mejor implementación
static void draw_active_profile_text(lv_obj_t *canvas,
                                     const struct status_state *state) {
  // // new label_dsc
  // lv_draw_label_dsc_t label_dsc;
  // init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono_8,
  //                LV_TEXT_ALIGN_LEFT);

  // // buffer size should be enough for largest number + null character
  // char text[14] = {};
  // snprintf(text, sizeof(text), "%d", state->active_profile_index + 1);

  // lv_canvas_draw_text(canvas, 25, 32, 35, &label_dsc, text);

  lv_layer_t *layer = lv_canvas_get_layer(canvas);

    // Configurar estilo del texto
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono_8, LV_TEXT_ALIGN_LEFT);

    char text[14] = {};
    snprintf(text, sizeof(text), "%d", state->active_profile_index + 1);
    
    label_dsc.text = text;
    label_dsc.text_local = 1;

    // Área del texto
    lv_area_t coords;
    coords.x1 = 25;
    coords.y1 = 32;
    coords.x2 = 25 + 35; // Ancho límite original
    coords.y2 = 32 + 20; // Altura estimada

    lv_draw_label(layer, &label_dsc, &coords);
}

void draw_profile_status(lv_obj_t *canvas, const struct status_state *state) {
  draw_active_profile_text(canvas, state);
  draw_inactive_profiles(canvas, state);
  draw_active_profile(canvas, state);
}
