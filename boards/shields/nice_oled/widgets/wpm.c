// #include "wpm.h"
// #include "../assets/custom_fonts.h"
// #include <math.h>
// #include <zephyr/kernel.h>

// LV_IMG_DECLARE(gauge);
// LV_IMG_DECLARE(grid);

// static void draw_gauge(lv_obj_t *canvas, const struct status_state *state) {
//     lv_draw_img_dsc_t img_dsc;
//     lv_draw_img_dsc_init(&img_dsc);

//     lv_canvas_draw_img(canvas, 0, 70, &gauge, &img_dsc);
// }

// static void draw_needle(lv_obj_t *canvas, const struct status_state *state) {
//     lv_draw_line_dsc_t line_dsc;
//     init_line_dsc(&line_dsc, LVGL_FOREGROUND, 1);

//     int centerX = 12; // 16 default
//     int centerY = 90; // 100 gut, 66 default
//     int offset = 5;   // 5 def, largo de la aguja
//     int value = state->wpm[9];

// #if IS_ENABLED(CONFIG_NICE_OLED_GEM_ANIMATION_WPM_FIXED_RANGE)
//     float max = CONFIG_NICE_OLED_GEM_ANIMATION_WPM_FIXED_RANGE_MAX;
// #else
//     float max = 0;
//     for (int i = 0; i < 10; i++) {
//         if (state->wpm[i] > max) {
//             max = state->wpm[i];
//         }
//     }
// #endif
//     if (max == 0)
//         max = 100;
//     if (value < 0)
//         value = 0;
//     if (value > max)
//         value = max;

//     float radius = 25.45585;
//     float angleDeg = 225 + ((float)value / max) * 90;
//     float angleRad = angleDeg * (3.14159 / 180.0f);

//     /* int needleStartX = 33 + (int)(13 * cos(4.71239)); // 33 + (int)(13 * 0) =
//     33
//     * int needleStartY = 66 + (int)(13 * sin(4.71239)); // 66 + (int)(13 * -1) =
//     53
//     * int needleEndX = 33 + (int)(25.45585 * cos(4.71239)); // 33 +
//     (int)(25.45585 * 0) = 33
//     * int needleEndY = 66 + (int)(25.45585 * sin(4.71239)); 66 + (int)(25.45585 *
//     -1) = 40 */
//     int needleStartX = centerX + (int)(offset * cos(angleRad));
//     int needleStartY = centerY + (int)(offset * sin(angleRad));
//     int needleEndX = centerX + (int)(radius * cos(angleRad));
//     int needleEndY = centerY + (int)(radius * sin(angleRad));

//     lv_point_t points[2] = {{needleStartX, needleStartY}, {needleEndX, needleEndY}};
//     // canvas, points, number of points, line_dsc
//     lv_canvas_draw_line(canvas, points, 2, &line_dsc);
//     // lv_canvas_draw_line(canvas, points, 2, &line_dsc);
// }

// #if IS_ENABLED(CONFIG_NICE_OLED_WIDGET_WPM_LUNA)
// #else
// static void draw_grid(lv_obj_t *canvas) {
//     lv_draw_img_dsc_t img_dsc;
//     lv_draw_img_dsc_init(&img_dsc);

//     lv_canvas_draw_img(canvas, -1, 95, &grid, &img_dsc);
// }

// static void draw_graph(lv_obj_t *canvas, const struct status_state *state) {
//     lv_draw_line_dsc_t line_dsc;
//     init_line_dsc(&line_dsc, LVGL_FOREGROUND, 2);
//     lv_point_t points[10];

// #if IS_ENABLED(CONFIG_NICE_OLED_GEM_ANIMATION_WPM_FIXED_RANGE)
//     int max = CONFIG_NICE_OLED_GEM_ANIMATION_WPM_FIXED_RANGE_MAX;
//     if (max == 0) {
//         max = 100;
//     }

//     int value = 0;
//     for (int i = 0; i < 10; i++) {
//         value = state->wpm[i];
//         if (value > max) {
//             value = max;
//         }

//         // modificar aqui par la posicion de la grafica
//         points[i].x = -36 + i * 7.4;
//         points[i].y = 127 - (value * 32 / max);
//         // points[i].y = 132 - (value * 32 / max);
//     }
// #else
//     int max = 0;
//     int min = 256;

//     for (int i = 0; i < 10; i++) {
//         if (state->wpm[i] > max) {
//             max = state->wpm[i];
//         }
//         if (state->wpm[i] < min) {
//             min = state->wpm[i];
//         }
//     }

//     int range = max - min;
//     if (range == 0) {
//         range = 1;
//     }

//     for (int i = 0; i < 10; i++) {
//         points[i].x = 0 + i * 7.4;
//         points[i].y = 97 - (state->wpm[i] - min) * 32 / range;
//     }
// #endif

//     lv_canvas_draw_line(canvas, points, 10, &line_dsc);
// }
// #endif

// static void draw_label(lv_obj_t *canvas, const struct status_state *state) {
//     lv_draw_label_dsc_t label_dsc_wpm;
//     init_label_dsc(&label_dsc_wpm, LVGL_FOREGROUND, &pixel_operator_mono_12, LV_TEXT_ALIGN_LEFT);
//     // init_label_dsc(&label_dsc_wpm, LVGL_FOREGROUND, &pixel_operator_mono,
//     // LV_TEXT_ALIGN_LEFT);

//     char wpm_text[10] = {};

//     snprintf(wpm_text, sizeof(wpm_text), "%d", state->wpm[9]);
//     // if wpm < 10, elsse if wpm => 10 and wpm < 100, else wpm >= 100
//     if (state->wpm[9] < 10) {
//         lv_canvas_draw_text(canvas, 12, 75, 50, &label_dsc_wpm, wpm_text);
//         // lv_canvas_draw_text(canvas, 12, 75, 50, &label_dsc_wpm, wpm_text); //
//         // with global font
//     } else if (state->wpm[9] >= 10 && state->wpm[9] < 100) {
//         lv_canvas_draw_text(canvas, 9, 75, 50, &label_dsc_wpm, wpm_text);
//         // lv_canvas_draw_text(canvas, 8, 75, 50, &label_dsc_wpm, wpm_text); // with
//         // global font
//     } else {
//         lv_canvas_draw_text(canvas, 7, 75, 50, &label_dsc_wpm, wpm_text);
//         // lv_canvas_draw_text(canvas, 5, 75, 50, &label_dsc_wpm, wpm_text); // with
//         // global font
//     }
// }

// void draw_wpm_status(lv_obj_t *canvas, const struct status_state *state) {
//     draw_gauge(canvas, state);
//     draw_needle(canvas, state);
// #if IS_ENABLED(CONFIG_NICE_OLED_WIDGET_WPM_LUNA)
// #else
//     draw_grid(canvas);
//     draw_graph(canvas, state);
// #endif
//     draw_label(canvas, state);
// }


#include "wpm.h"
#include "../assets/custom_fonts.h"
#include <math.h>
#include <stdio.h> // Necesario para snprintf
#include <zephyr/kernel.h>
#include <lvgl.h>

// LVGL 9 prefiere LV_IMAGE_DECLARE, pero mantenemos compatibilidad si es posible
LV_IMG_DECLARE(gauge);
LV_IMG_DECLARE(grid);

/* -------------------------------------------------------------------------
 * HELPER: Dibujar imagen en LVGL 9
 * ------------------------------------------------------------------------- */
static void draw_image_on_canvas(lv_obj_t *canvas, const lv_image_dsc_t *img_src, int x, int y) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);
    
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = img_src;

    // Definir el área donde se pintará la imagen
    lv_area_t coords;
    coords.x1 = x;
    coords.y1 = y;
    coords.x2 = x + img_src->header.w - 1;
    coords.y2 = y + img_src->header.h - 1;

    lv_draw_image(&layer, &img_dsc, &coords);
}

/* -------------------------------------------------------------------------
 * WIDGETS
 * ------------------------------------------------------------------------- */

static void draw_gauge(lv_obj_t *canvas, const struct status_state *state) {
    // Reemplaza lv_canvas_draw_img
    draw_image_on_canvas(&canvas, &gauge, 0, 70);
}

static void draw_needle(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    // Configurar estilo de línea
    lv_draw_line_dsc_t line_dsc;
    lv_draw_line_dsc_init(&line_dsc);
    line_dsc.width = 1; // Grosor
    line_dsc.color = lv_color_white(); // O lv_color_black() según tu tema (LVGL_FOREGROUND)
    line_dsc.round_start = 1;
    line_dsc.round_end = 1;

    // Lógica matemática (intacta)
    int centerX = 12; 
    int centerY = 90; 
    int offset = 5;   
    int value = state->wpm[9];

#if IS_ENABLED(CONFIG_NICE_OLED_GEM_ANIMATION_WPM_FIXED_RANGE)
    float max = CONFIG_NICE_OLED_GEM_ANIMATION_WPM_FIXED_RANGE_MAX;
#else
    float max = 0;
    for (int i = 0; i < 10; i++) {
        if (state->wpm[i] > max) max = state->wpm[i];
    }
#endif
    if (max == 0) max = 100;
    if (value < 0) value = 0;
    if (value > max) value = max;

    float radius = 25.45585;
    float angleDeg = 225 + ((float)value / max) * 90;
    float angleRad = angleDeg * (3.14159 / 180.0f);

    // Calcular puntos
    line_dsc.p1.x = centerX + (int)(offset * cos(angleRad));
    line_dsc.p1.y = centerY + (int)(offset * sin(angleRad));
    line_dsc.p2.x = centerX + (int)(radius * cos(angleRad));
    line_dsc.p2.y = centerY + (int)(radius * sin(angleRad));

    // Dibujar línea única
    lv_draw_line(&layer, &line_dsc);
}

#if IS_ENABLED(CONFIG_NICE_OLED_WIDGET_WPM_LUNA)
#else
static void draw_grid(lv_obj_t *canvas) {
    // Reemplaza lv_canvas_draw_img
    draw_image_on_canvas(canvas, &grid, -1, 95);
}

static void draw_graph(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_line_dsc_t line_dsc;
    lv_draw_line_dsc_init(&line_dsc);
    line_dsc.width = 2;
    line_dsc.color = lv_color_white(); // Ajustar color si es necesario

    lv_point_t points[10];

    // --- LÓGICA MATEMÁTICA (Mantenida igual) ---
#if IS_ENABLED(CONFIG_NICE_OLED_GEM_ANIMATION_WPM_FIXED_RANGE)
    int max = CONFIG_NICE_OLED_GEM_ANIMATION_WPM_FIXED_RANGE_MAX;
    if (max == 0) max = 100;

    int value = 0;
    for (int i = 0; i < 10; i++) {
        value = state->wpm[i];
        if (value > max) value = max;
        points[i].x = -36 + i * 7.4;
        points[i].y = 127 - (value * 32 / max);
    }
#else
    int max = 0;
    int min = 256;
    for (int i = 0; i < 10; i++) {
        if (state->wpm[i] > max) max = state->wpm[i];
        if (state->wpm[i] < min) min = state->wpm[i];
    }
    int range = max - min;
    if (range == 0) range = 1;

    for (int i = 0; i < 10; i++) {
        points[i].x = 0 + i * 7.4;
        points[i].y = 97 - (state->wpm[i] - min) * 32 / range;
    }
#endif
    // -------------------------------------------

    // DIBUJAR LA GRÁFICA (Adaptación LVGL 9)
    // Como lv_draw_line solo dibuja un segmento, iteramos del punto 0 al 8
    for (int i = 0; i < 9; i++) {
        line_dsc.p1 = points[i];
        line_dsc.p2 = points[i+1];
        lv_draw_line(&layer, &line_dsc);
    }
}
#endif

static void draw_label(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    // Configurar etiqueta
    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.color = lv_color_white();
    label_dsc.font = &pixel_operator_mono_12; // Asegúrate que esta fuente existe en custom_fonts.h
    label_dsc.align = LV_TEXT_ALIGN_LEFT;

    char wpm_text[10] = {};
    snprintf(wpm_text, sizeof(wpm_text), "%d", state->wpm[9]);
    
    label_dsc.text = wpm_text;
    label_dsc.text_local = 1; // Importante para buffers locales

    // Definir posición X basada en la lógica original
    int x_pos = 0;
    if (state->wpm[9] < 10) {
        x_pos = 12;
    } else if (state->wpm[9] >= 10 && state->wpm[9] < 100) {
        x_pos = 9;
    } else {
        x_pos = 7;
    }

    // Definir área (LVGL 9 necesita un área, no solo un punto XY)
    lv_area_t coords;
    coords.x1 = x_pos;
    coords.y1 = 75;
    coords.x2 = x_pos + 50; // Ancho estimado suficiente
    coords.y2 = 75 + 20;    // Alto estimado

    lv_draw_label(&layer, &label_dsc, &coords);
}

void draw_wpm_status(lv_obj_t *canvas, const struct status_state *state) {
    draw_gauge(canvas, state);
    draw_needle(canvas, state);
#if IS_ENABLED(CONFIG_NICE_OLED_WIDGET_WPM_LUNA)
#else
    draw_grid(canvas);
    draw_graph(canvas, state);
#endif
    draw_label(canvas, state);
}