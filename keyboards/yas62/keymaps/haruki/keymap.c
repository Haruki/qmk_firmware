/* Copyright 2019 MechMerlin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "action_layer.h"
#include "../../../quantum/keymap_extras/keymap_german.h"

#define _______ KC_TRNS

#define QWERTY  0
#define LAYER1     1
#define LAYER2     2
#define MISC1      3
#define MISC2      4

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERTY] = LAYOUT_all(
        KC_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_NO,   KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_NO,
        LT(LAYER1,KC_ESC), KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    LT(LAYER2,KC_SCLN), KC_QUOT, KC_BSLS,   CTL_T(KC_ENT),
        KC_LSPO, KC_NUBS,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSPC,
        KC_LCTL, KC_LGUI, KC_LALT,LT(MISC1,KC_INS), LT(MISC2,KC_DEL), KC_SPC, KC_SPC,               KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

[MISC1] = LAYOUT_all(
	KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, _______, 
	KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_7, KC_8, KC_9, KC_0, _______, _______, _______, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS, KC_TRNS, KC_TRNS,_______, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC, BL_TOGG, BL_INC, BL_STEP, KC_1, KC_2, KC_3, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_NO,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ),

[MISC2] = LAYOUT_all(
	RESET, M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), M(11), M(12), KC_TRNS, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_MNXT, KC_MPRV, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLU, KC_VOLD, KC_TRNS, KC_TRNS, KC_TRNS,_______, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ),

[LAYER1] = LAYOUT_all( \
	KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,_______,_______, \
	_______,LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),LSFT(KC_0), LSFT(KC_MINS), LSFT(KC_EQL), LSFT(KC_NO),   \
	_______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP, KC_RGHT ,KC_BSPC,DE_EQL ,        _______, _______,  \
	_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_UP,_______,   \
	_______,_______,_______,_______,_______,_______,KC_NO,_______,                        KC_LEFT,KC_DOWN  ,KC_RGHT  ),

/* Layer 2: Homerow ArrowKeys */
[LAYER2] = LAYOUT_all( \
	KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,_______,_______, \
	_______,LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_8),LSFT(KC_0), LSFT(KC_MINS), LSFT(KC_EQL), LSFT(KC_NO),   \
	_______,DE_LESS,DE_MORE,DE_LCBR,DE_RCBR,DE_LBRC,DE_RBRC,KC_HOME,KC_END,KC_DEL  ,_______,_______,        _______, _______,  \
	_______,_______,_______,_______,_______,_______,_______,DE_GRV,DE_QUOT,_______,_______,_______,_______,_______,   \
	_______,_______,_______,_______,_______,_______,KC_NO,_______,                        _______,_______  ,_______  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
