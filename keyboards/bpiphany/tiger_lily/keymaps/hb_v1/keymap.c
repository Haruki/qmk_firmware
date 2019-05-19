#include "tiger_lily.h"
#include "action_layer.h"
#include "../../../quantum/keymap_extras/keymap_german.h"

/*keys for space cadet: */


 


#define _______ KC_TRNS

#define KM_QWERTY  0
#define LAYER1     1
#define LAYER2     2
#define MISC       3

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
[KM_QWERTY] = LAYOUT( \
		KC_ESC,             KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,   KC_PSCR,KC_SLCK,KC_PAUS,                                    \
		KC_GRV,  KC_1,      KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,  KC_INS, KC_HOME,KC_PGUP,   KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS, \
		KC_TAB,  KC_Q,      KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,  KC_DEL, KC_END, KC_PGDN,     KC_P7,  KC_P8,  KC_P9,KC_PPLS, \
		LT(LAYER1,KC_ESC), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   LT(LAYER2,KC_SCLN), TD(TD_END), CTL_T(KC_ENT),                  KC_P4,  KC_P5,  KC_P6,         \
		KC_LSPO, KC_NUBS,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M, KC_COMM, KC_DOT, KC_SLSH,        KC_RSPC,          KC_UP,                  KC_P1,  KC_P2,  KC_P3,KC_PENT, \
		KC_LCTL, KC_LGUI,   KC_LALT,                       KC_SPC,                          KC_RALT,KC_RGUI,KC_MENU,KC_FN0,   KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0, KC_PDOT),


	/* Layer 1: Homerow ArrowKeys */
	[LAYER1] = LAYOUT( \
		_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,                                 \
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,_______,   _______,_______,_______,  _______,_______,_______,_______,\
		 _______,LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),LSFT(KC_0), LSFT(KC_MINS), LSFT(KC_EQL), LSFT(KC_NO),  _______,_______,_______,  _______,_______,_______,_______,\
		_______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP, KC_RGHT ,KC_BSPC,DE_EQL ,        _______,                             _______,_______,_______        ,\
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,           _______,          _______,_______,_______,_______,\
		_______,_______,_______,                        KC_DEL,                        _______,_______,_______  ,_______,  _______,_______,_______, _______,_______                ),

    /* Layer 2: Homerow ArrowKeys */
	[LAYER2] = LAYOUT( \
		_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,                                 \
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,_______,   _______,_______,_______,  _______,_______,_______,_______,\
		_______,LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_8),LSFT(KC_0), LSFT(KC_MINS), LSFT(KC_EQL), LSFT(KC_NO),   _______,_______,_______,  _______,_______,_______,_______,\
		_______,DE_LESS,DE_MORE,DE_LCBR,DE_RCBR,DE_LBRC,DE_RBRC,KC_HOME,KC_END,_______,_______,_______,        _______,                              _______,_______,_______        ,\
		 _______,_______,_______,_______,_______,_______,_______,DE_GRV,DE_QUOT,_______,_______,_______,_______,           _______,          _______,_______,_______,_______,\
		_______,_______,_______,                        _______,                        _______,_______,_______  ,_______,   _______,_______,_______, _______,_______                ),

	/* Misc Layer: Function layer */
	[MISC] = LAYOUT( \
		_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   KC_MUTE,KC_VOLD,KC_VOLU,                                 \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______,\
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______,\
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,                             _______,_______,_______        ,\
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,           KC_MPLY,          _______,_______,_______,_______,\
		_______,_______,_______,                        _______,                        _______,_______,RESET  ,_______,   KC_MPRV,KC_MSTP,KC_MNXT,  _______,_______                 )
};

const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_LAYER_MOMENTARY(MISC),
	[1] = ACTION_LAYER_MOMENTARY(LAYER1)
};

/*
void led_set_user(uint8_t usb_led) {
	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		ph_caps_led_on();
	} else {
		ph_caps_led_off();
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		ph_sclk_led_on();
	} else {
		ph_sclk_led_off();
	}
}
*/

