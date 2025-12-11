#include "layer.h"
#include "../assets/custom_fonts.h" 
#include "util.h" // Necesario para init_label_dsc y LVGL_FOREGROUND
#include <ctype.h> // Para toupper()
#include <stdio.h> // Necesario para snprintf
#include <zephyr/kernel.h>
#include <lvgl.h>

// // MC: better implementation
// void draw_layer_status(lv_obj_t *canvas, const struct status_state *state) {
//   lv_draw_label_dsc_t label_dsc;
//   init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono,
//                  LV_TEXT_ALIGN_LEFT);

//   char text[14] = {};
//   int result;

//   if (state->layer_label == NULL) {
//     result = snprintf(text, sizeof(text), "Layer %i", state->layer_index);
//   } else {
//     result = snprintf(text, sizeof(text), "%s", state->layer_label);
//     for (int i = 0; text[i] != '\0'; i++) {
//       // toupper( ... ): This function, found in the ctype.h library, takes a
//       // character as an argument and converts it to its uppercase equivalent.
//       // If the character is already uppercase or not a letter, the function
//       // returns it unchanged.
//       text[i] = toupper(text[i]);
//     }
//   }

//   if (result >= sizeof(text)) {
//     LV_LOG_WARN("truncated");
//   }

//   lv_canvas_draw_text(canvas, 0, 146, 68, &label_dsc, text);
// }

void draw_layer_status(lv_obj_t *canvas, const struct status_state *state) {
    // 1. Obtener la capa del canvas (LVGL 9)
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    // 2. Configurar el estilo del texto
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);

    // 3. Preparar el string de texto
    char text[14] = {};
    int result;

    if (state->layer_label == NULL) {
        result = snprintf(text, sizeof(text), "Layer %i", state->layer_index);
    } else {
        result = snprintf(text, sizeof(text), "%s", state->layer_label);
        for (int i = 0; text[i] != '\0'; i++) {
            text[i] = toupper(text[i]);
        }
    }

    if (result >= sizeof(text)) {
        // LV_LOG_WARN("truncated"); // Descomentar si quieres logs
    }

    // 4. Asignar el texto al descriptor (Novedad LVGL 9)
    label_dsc.text = text;
    label_dsc.text_local = 1; // Importante para buffers locales

    // 5. Definir el área de dibujo
    lv_area_t coords;
    coords.x1 = 0;
    coords.y1 = 146;
    coords.x2 = 0 + 68;  // Ancho máximo (originalmente era el 4to argumento)
    coords.y2 = 146 + 20; // Altura estimada de la fuente

    // 6. Dibujar
    lv_draw_label(&layer, &label_dsc, &coords);
}
