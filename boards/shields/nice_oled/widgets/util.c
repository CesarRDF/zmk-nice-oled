#include "util.h"
#include <ctype.h>
#include <zephyr/kernel.h>
#include <string.h>
#include <lvgl.h>
#include <stdlib.h>

void to_uppercase(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    str[i] = toupper(str[i]);
  }
}

void rotate_canvas(lv_obj_t *canvas, lv_color_t cbuf[]) {
  //static lv_color_t cbuf_tmp[CANVAS_HEIGHT * CANVAS_HEIGHT];
  static uint8_t cbuf_tmp[CANVAS_HEIGHT * CANVAS_HEIGHT / 8];
  //memcpy(cbuf_tmp, cbuf, sizeof(cbuf_tmp));
  memset(cbuf_tmp, 0, sizeof(cbuf_tmp));

  size_t src_size = (CANVAS_WIDTH * CANVAS_HEIGHT) / 8;
    if (src_size > sizeof(cbuf_tmp)) {
        src_size = sizeof(cbuf_tmp);
    }

  memcpy(cbuf_tmp, cbuf, src_size);

  lv_image_dsc_t img;
  img.header.magic = LV_IMAGE_HEADER_MAGIC;
  img.header.cf = LV_COLOR_FORMAT_I1;

  img.header.flags = 0;

  img.header.w = CANVAS_WIDTH;
  img.header.h = CANVAS_HEIGHT;
  img.header.stride = (CANVAS_HEIGHT + 7) / 8; // Stride en bytes para 1 bit
  //img.header.stride = CANVAS_HEIGHT * sizeof(lv_color_t); 
  img.header.reserved_2 = 0;

  // lv_canvas_fill_bg(canvas, LVGL_BACKGROUND, LV_OPA_COVER);
  // lv_canvas_transform(canvas, &img, 900, LV_IMG_ZOOM_NONE, -1, 0,
  //                     CANVAS_HEIGHT / 2, CANVAS_HEIGHT / 2, false);

  img.data = (const uint8_t *)cbuf_tmp;
  img.data_size = sizeof(cbuf_tmp);

  // 3. Limpiar el canvas actual
  lv_canvas_fill_bg(canvas, lv_color_hex(0x000000), LV_OPA_COVER);

  // 4. Obtener la capa del canvas para dibujar (LVGL 9 way)
  lv_layer_t layer;
  lv_canvas_init_layer(canvas, &layer);

  // 5. Configurar el dibujado con rotación
  lv_draw_image_dsc_t draw_dsc;
  lv_draw_image_dsc_init(&draw_dsc);
  draw_dsc.src = &img;
  draw_dsc.rotation = 900; // 90.0 grados
    
  // Punto de pivote (centro)
  draw_dsc.pivot.x = CANVAS_HEIGHT / 2;
  draw_dsc.pivot.y = CANVAS_HEIGHT / 2;

  // 6. Definir área y dibujar
  lv_area_t coords;
  coords.x1 = 0;
  coords.y1 = 0;
  coords.x2 = CANVAS_HEIGHT - 1;
  coords.y2 = CANVAS_HEIGHT - 1;

  lv_draw_image(&layer, &draw_dsc, &coords);
}

void draw_background(lv_obj_t *canvas) {
  // lv_draw_rect_dsc_t rect_black_dsc;
  // init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);

  // lv_canvas_draw_rect(canvas, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT,
  //                     &rect_black_dsc);

  // LVGL 9: No usamos lv_canvas_draw_rect, usamos lv_draw_rect sobre la capa
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_rect_dsc_t rect_black_dsc;
    init_rect_dsc(&rect_black_dsc, lv_color_black()); // Usar helper de color

    lv_area_t coords;
    coords.x1 = 0;
    coords.y1 = 0;
    coords.x2 = CANVAS_WIDTH - 1;  // Importante restar 1
    coords.y2 = CANVAS_HEIGHT - 1;

    lv_draw_rect(&layer, &rect_black_dsc, &coords);
}

void init_label_dsc(lv_draw_label_dsc_t *label_dsc, lv_color_t color,
                    const lv_font_t *font, lv_text_align_t align) {
  lv_draw_label_dsc_init(label_dsc);
  label_dsc->color = color;
  label_dsc->font = font;
  label_dsc->align = align;
}

void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color) {
  lv_draw_rect_dsc_init(rect_dsc);
  rect_dsc->bg_color = bg_color;
}

void init_line_dsc(lv_draw_line_dsc_t *line_dsc, lv_color_t color,
                   uint8_t width) {
  lv_draw_line_dsc_init(line_dsc);
  line_dsc->color = color;
  line_dsc->width = width;
}
