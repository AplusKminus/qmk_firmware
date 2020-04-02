#include QMK_KEYBOARD_H
#include "quantum/keymap_extras/keymap_german.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _FUNC 3

#define ESC_ALT MT(MOD_LALT, KC_ESC)
#define Y_ALT MT(MOD_LALT, DE_Y)
#define BSP_ALT MT(MOD_LALT, KC_BSPC)
#define SPC_LOW LT(_LOWER, KC_SPC)
#define UE_ALT MT(MOD_LALT, DE_UDIA)
#define AE_SFT MT(MOD_RSFT, DE_ADIA)
#define SZ_RCTL MT(MOD_RCTL, DE_SS)
#define MIN_RIS LT(_RAISE, DE_MINS)
#define ENT_ALT MT(MOD_LALT, KC_ENT)
#define ENT_FNC LT(_FUNC, KC_ENT)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                        DE_Z,    KC_U,    KC_I,    KC_O,    KC_P,  KC_ESC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,    KC_K,    KC_L, DE_ODIA,  AE_SFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    DE_Y,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_N,    KC_M, KC_COMM,  KC_DOT, DE_UDIA, SZ_RCTL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_BSPC, SPC_LOW, ENT_ALT,    ENT_FNC,  MIN_RIS,  KC_DEL \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_LGUI, KC_PGUP,   KC_UP, KC_PGDN,  KC_INS,                     XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,                     XXXXXXX,    KC_4,    KC_5,    KC_6, KC_COMM, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                     XXXXXXX,    KC_1,    KC_2,    KC_3,  KC_DOT, KC_RCTL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,   LOWER, _______,   ENT_ALT, _______,    KC_0 \
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      DE_CIRC,  DE_DEG, DE_DQUO, DE_QUOT,  DE_GRV, DE_ACUT,                     DE_MICR, DE_LABK, DE_SLSH, DE_EXLM, DE_RABK, DE_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, DE_PERC,   DE_AT, KC_PAST,  DE_EQL,  DE_DLR,                     XXXXXXX, DE_LCBR, DE_LPRN, DE_RPRN, DE_RCBR, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, DE_EURO, DE_TILD, DE_AMPR, DE_HASH, DE_PIPE,                     DE_SECT, KC_PPLS, DE_LBRC, DE_RBRC, KC_PMNS, DE_QUES,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,   LOWER, _______,   _______,   RAISE, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNC] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_ESC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, RGB_HUI, RGB_SAI, RGB_VAI, RGBRST,  RGB_TOG,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F11, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, RGB_MOD,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F12, KC_RCTL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER, _______,   _______,   RAISE, _______ \
                                      //`--------------------------'  `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _FUNC);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _FUNC);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _FUNC);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _FUNC);
      }
      return false;
    /*case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;*/
  }
  return true;
}
