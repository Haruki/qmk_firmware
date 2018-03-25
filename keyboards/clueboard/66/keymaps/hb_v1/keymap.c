#include "66.h"
#include "../../../../quantum/keymap_extras/keymap_german.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
#define _BL 0
#define _FL 1
#define _CL 2
#define LAYER1  3
#define LAYER2  4




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




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = LAYOUT(
  KC_GESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_NO, KC_BSPC,         KC_PGUP,
  KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_NO,                  KC_PGDN,
  TD(TD_CAPS),KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L, LT(LAYER2,KC_SCLN), TD(TD_END),KC_BSLASH, CTL_T(KC_ENT),
  KC_LSPO,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_NO, KC_RSPC,        KC_UP,
  KC_LCTL,KC_LGUI,KC_LALT, KC_INS, KC_DEL, KC_SPC, KC_SPC, KC_RALT,MO(_FL),KC_RCTL,                               KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = LAYOUT(
  KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_DEL,         KC_VOLU,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MPRV,KC_MPLY,KC_MNXT,_______,_______,                KC_VOLD,
  _______,_______,MO(_CL),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        KC_PGUP,
  _______,_______,_______, _______,_______,_______, _______,                               _______,MO(_FL),_______,KC_HOME,KC_PGDN,KC_END),

  /* Keymap _CL: Control layer
   */
[_CL] = LAYOUT(
  BL_STEP,RGB_M_P,RGB_M_B,RGB_M_R,RGB_M_SW,RGB_M_SN,RGB_M_K,RGB_M_X,RGB_M_G,_______,_______,_______,_______, _______,RGB_TOG,     RGB_VAI,
  _______,_______,_______,_______,RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______,                RGB_VAD,
  _______,_______,MO(_CL),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  MO(_FL),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        RGB_SAI,
  _______,_______,_______,_______,_______,                   RGB_MOD,_______,            _______,MO(_FL),_______,RGB_HUD,RGB_SAD,RGB_HUI),

[LAYER1] = LAYOUT(
  KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,_______,KC_DEL,          KC_VOLU,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MPRV,KC_MPLY,KC_MNXT,_______,_______,                KC_VOLD,
  _______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP, KC_RGHT ,KC_BSPC,DE_EQL ,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        KC_PGUP,
  _______,_______,_______,_______,_______,       _______,_______,                        _______,MO(_FL),_______,KC_HOME,KC_PGDN,KC_END),

[LAYER2] = LAYOUT(
  KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,_______,KC_DEL,          KC_VOLU,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_INS ,_______,_______,_______,_______,                KC_VOLD,
  _______,DE_LESS,DE_MORE,DE_LCBR,DE_RCBR,DE_LBRC,DE_RBRC,KC_HOME,KC_END,KC_DEL  ,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        KC_PGUP,
  _______,_______,_______,_______,_______,        _______,_______,                        _______,MO(_FL),_______,KC_HOME,KC_PGDN,KC_END),

};
