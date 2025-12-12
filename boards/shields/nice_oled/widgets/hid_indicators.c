// --- CORRECCIÓN LVGL 9: USAR LV_IMAGE_DECLARE ---
LV_IMAGE_DECLARE(dog_bark1_90);
LV_IMAGE_DECLARE(dog_bark2_90);

const lv_image_dsc_t *luna_imgs_bark_90[] = {&dog_bark1_90, &dog_bark2_90};
static lv_obj_t *hid_anim = NULL;

struct hid_indicators_state {
  uint8_t hid_indicators;
};

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

static void set_hid_indicators(lv_obj_t *label,
                               struct hid_indicators_state state) {

#if IS_ENABLED(CONFIG_NICE_OLED_WIDGET_HID_INDICATORS_LUNA_ONLY_CAPSLOCK)
  if (state.hid_indicators & LED_CLCK) {
#else
  if (state.hid_indicators & (LED_CLCK | LED_NLCK | LED_SLCK)) {
#endif
    lv_label_set_text(label, "");

    if (!hid_anim) {
      hid_anim = lv_animimg_create(label);
      lv_obj_center(hid_anim);

      // Casting correcto para LVGL 9
      lv_animimg_set_src(hid_anim, (const void **)luna_imgs_bark_90, 2);
      lv_animimg_set_duration(
          hid_anim, CONFIG_NICE_OLED_WIDGET_HID_INDICATORS_LUNA_ANIMATION_MS);
      lv_animimg_set_repeat_count(hid_anim, LV_ANIM_REPEAT_INFINITE);
      lv_animimg_start(hid_anim);
      lv_obj_align(hid_anim, LV_ALIGN_TOP_LEFT, 36, 0);
    }
  } else {
    if (hid_anim) {
      lv_obj_del(hid_anim);
      hid_anim = NULL;
    }
    lv_label_set_text(label, "");
  }
}

void hid_indicators_update_cb(struct hid_indicators_state state) {
  struct zmk_widget_hid_indicators *widget;
  SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) {
    set_hid_indicators(widget->obj, state);
  }
}

static struct hid_indicators_state
hid_indicators_get_state(const zmk_event_t *eh) {
  struct zmk_hid_indicators_changed *ev = as_zmk_hid_indicators_changed(eh);
  return (struct hid_indicators_state){
      .hid_indicators = ev->indicators,
  };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_hid_indicators, struct hid_indicators_state,
                            hid_indicators_update_cb, hid_indicators_get_state)

ZMK_SUBSCRIPTION(widget_hid_indicators, zmk_hid_indicators_changed);

int zmk_widget_hid_indicators_init(struct zmk_widget_hid_indicators *widget,
                                   lv_obj_t *parent) {
  widget->obj = lv_label_create(parent);

  sys_slist_append(&widgets, &widget->node);

  widget_hid_indicators_init();

  return 0;
}

lv_obj_t *
zmk_widget_hid_indicators_obj(struct zmk_widget_hid_indicators *widget) {
  return widget->obj;
}