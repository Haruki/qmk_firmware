#include "lfk87.h"
#include "issi.h"
#include "lighting.h"
#include "action_layer.h"
#include "../../../../../quantum/keymap_extras/keymap_german.h"


//Define a shorter 'transparent' key code to make the keymaps more compact
#define _____ KC_TRNS

enum keymap_layout {
    VANILLA = 0,
    FUNC,         // 0x02
    SETTINGS,     // 0x04
};


#define LAYER1     5
#define LAYER2     6
#define LAYER3     7
#define GAMING     8

//Tap Dance Declarations
enum {
  TD_COMM_EQL = 0,
  TD_CAPS = 1,
  TD_END = 2
};



/*capslock tap dance */

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_HOLD = 4, 
  TRIPLE_HOLD = 6,
  QUAD_HOLD = 8
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || state->pressed==0) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return SINGLE_TAP;
  } 
  else if (state->count == 3) {
    if (state->pressed) return TRIPLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 4) {
    if (state->pressed) return QUAD_HOLD;
    else return SINGLE_TAP;
  }
  else return 10; //magic number. At some point this method will expand to work for more presses
}

/* instanz */
static tap xtap_state = { 
  .is_press_action = true,
  .state = 0
};


void dance_capslock_finished (qk_tap_dance_state_t *state, void *user_data) {
xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_ESC); break;
    case SINGLE_HOLD: layer_on(LAYER1); break;
    case DOUBLE_HOLD: layer_on(LAYER1); register_code(KC_LSFT); break;
    case TRIPLE_HOLD: layer_on(LAYER1); register_code(KC_LCTL); break;
    case QUAD_HOLD:   layer_on(LAYER1); register_code(KC_LSFT); register_code(KC_LCTL);
  }
}

void dance_capslock_reset (qk_tap_dance_state_t *state, void *user_data) {
switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_ESC); break;
    case SINGLE_HOLD: layer_off(LAYER1); break;
    case DOUBLE_HOLD: layer_off(LAYER1); unregister_code(KC_LSFT); break;
    case TRIPLE_HOLD: layer_off(LAYER1); unregister_code(KC_LCTL); break;
    case QUAD_HOLD: layer_off(LAYER1); unregister_code(KC_LSFT); unregister_code(KC_LCTL);
  }
  xtap_state.state = 0;
}




//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_COMM_EQL]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, DE_EQL),
  [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_capslock_finished, dance_capslock_reset),
  [TD_END] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_END)
// Other declarations would go here, separated by commas, if you have them
};





// Colors of the layer indicator LED
// This list needs to define layer 0xFFFFFFFF, it is the end of the list, and the unknown layer
const Layer_Info layer_info[] = {
  // Layer     Mask         Red   Green Blue
  {0x00000000, 0xFFFFFFFF, {0x00, 0x00, 0x00}}, // base layer - off
  {0x00000002, 0xFFFFFFFE, {0x00, 0x00, 0x7F}}, // function layer - blue
  {0x00000004, 0xFFFFFFFC, {0x7F, 0x00, 0x00}}, // settings layer - red
  {0xFFFFFFFF, 0xFFFFFFFF, {0x0F, 0x0F, 0x0F}}, // unknown layer - REQUIRED - white
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[VANILLA] = LAYOUT_iso(
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_LSCR, KC_PAUS, \
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, CTL_T(KC_ENT), KC_DELETE, KC_END, KC_PGDN, \
    TD(TD_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, LT(LAYER2,KC_SCLN),TD(TD_END), KC_NUHS,  \
    KC_LSPO, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_UP, \
    KC_LCTL, KC_LGUI, KC_LALT, LT(LAYER3,KC_INS), KC_DEL, KC_SPC, KC_RALT, TG(GAMING), MO(FUNC), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[FUNC] = LAYOUT_iso(
   _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,                        KC_PSCR, KC_SLCK, KC_PAUS, \
   _____,  _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,               KC_DEL,  _____, _____, _____, \
   KC_NO,KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO,   _____, _____, _____, \
   _____, KC_HOME, KC_PGDN, KC_END, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,            KC_NO, \
   _____,KC_NO, KC_NO,  KC_DEL,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   TG(SETTINGS),                 _____, \
   _____,  _____, _____,    _____,              KC_PGDN,   _____,                        _____, _____, _____,  _____,            _____,  _____, _____),

[SETTINGS] = LAYOUT_iso(
  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, BL_DEC,            KC_NO,   KC_NO,   KC_NO,
  KC_FN0,KC_FN3,KC_FN4,KC_FN5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, BL_DEC, BL_INC, BL_TOGG,  RGB_TOG, RGB_VAI, KC_NO,
  MU_MOD,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     RESET,  RGB_MOD, RGB_VAD, KC_NO,
  AU_TOG,  KC_FN3,KC_FN5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO,
  KC_FN7, KC_NO, KC_FN4, KC_FN6, KC_NO, KC_NO, KC_NO, KC_NO, MU_TOG, KC_NO, KC_NO, KC_NO,             KC_FN0,           RGB_HUI,
  KC_NO, KC_NO, KC_NO,     _____,             KC_NO,      _____,                     KC_NO, KC_NO, KC_NO, KC_FN0,     RGB_SAD, RGB_HUD, RGB_SAI),

[LAYER1] = LAYOUT_iso(
    _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______, \
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,_______,   _______,_______,_______, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______, \
    _______,KC_PSCR,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP, KC_RGHT ,KC_BSPC,DE_EQL ,        _______,                            \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,           _______,         \
    _______,_______,_______,        _______,       KC_DEL,      _______,          _______,_______,_______  ,_______,   _______,_______,_______),

[LAYER2] = LAYOUT_iso(
    _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______, \
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,_______,   _______,_______,_______, \
    _______,_______,_______,_______,_______,_______,_______,KC_PGUP,_______,_______,_______,_______,_______,_______,   _______,_______,_______, \
    _______,DE_LESS,DE_MORE,DE_LCBR,DE_RCBR,DE_LBRC,DE_RBRC,KC_HOME,KC_END,_______,_______,_______,        _______,                            \
    _______,_______,_______,_______,_______,_______,_______,KC_PGDN,_______,_______,_______,_______,        _______,           _______,         \
    _______,_______,_______,         _______,       KC_INS,      _______,          _______,_______,_______  ,_______,   _______,_______,_______),

[LAYER3] = LAYOUT_iso(
    _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______, \
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,_______,   _______,_______,_______, \
	_______,_______,_______,_______,_______,_______,_______,KC_7, KC_8, KC_9, KC_0,_______,_______,_______,   _______,_______,_______, \
	_______,_______,_______,_______,_______,_______,_______,KC_4, KC_5, KC_6,_______,_______,        _______,                            \
	_______,_______,_______,_______,_______,_______,_______,_______,KC_1, KC_2, KC_3,_______,        _______,           _______,         \
    _______,_______,_______,        _______,       KC_DEL,      KC_0,          _______,_______,_______  ,_______,   _______,_______,_______),

[GAMING] = LAYOUT_iso( \
		KC_ESC,             KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,   KC_PSCR,KC_SLCK,KC_PAUS, \
		KC_GRV,  KC_1,      KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,  KC_INS, KC_HOME,KC_PGUP, \
		KC_TAB,  KC_Q,      KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_ENT,  KC_DEL, KC_END, KC_PGDN, \
		KC_CAPSLOCK, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_BSLS,              \
		KC_LSPO, KC_NUBS,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM,KC_DOT, KC_SLSH,        KC_RSPC,          KC_UP,              \
		KC_LCTL, KC_LGUI,   KC_LALT,          KC_SPC,KC_SPC,KC_SPC,                     KC_RALT,_______,_______,_______,   KC_LEFT,KC_DOWN,KC_RGHT),
};

const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(LFK_CLEAR),                               // FN0 - reset layers
    ACTION_FUNCTION(LFK_ESC_TILDE),                           // FN1 - esc+shift = ~, else escape
    ACTION_FUNCTION(LFK_LED_TEST),                            // FN2 - cycle through LEDs for testing
    ACTION_FUNCTION(LFK_CLICK_FREQ_HIGHER),                   // FN3 - Increase Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_FREQ_LOWER),                    // FN4 - Decrease Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_LONGER),                   // FN5 - Increase length of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_SHORTER),                  // FN6 - Decrease length of audio click
    ACTION_FUNCTION(LFK_CLICK_TOGGLE),                        // FN7 - Toggle audio click
    ACTION_FUNCTION(LFK_LED_TEST),                            // FN8 - cycle through LEDs for testing
    ACTION_FUNCTION(LFK_DEBUG_SETTINGS),                      // FN9 - prints LED and click settings to HID
  };


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {
    // This keymap only has a single base layer, so reset the default if needed
    if(eeconfig_read_default_layer() > 1){
        eeconfig_update_default_layer(1);
        default_layer_set(1);
    }
}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
