/* Copyright 2019 cfbender
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
#include "../../../quantum/keymap_extras/keymap_german.h"

#define OPT_TAB LCTL_T(KC_TAB)
#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split(/* Base */
                 KC_HOME, OPT_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
                 KC_END, LT(1,KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, LT(2,KC_SCLN), KC_QUOTE, CTL_T(KC_ENTER),
                 KC_PGUP, KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLSH, KC_RSPC, MO(1),
                 KC_PGDN, KC_LGUI, KC_LALT, KC_LALT, KC_SPACE, KC_SPACE, KC_RGUI, KC_RCTL, MO(2)),

    [1] = LAYOUT_split(
        _______, _______, LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),LSFT(KC_0), LSFT(KC_MINS), LSFT(KC_EQL), LSFT(KC_NO),
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT,KC_DOWN,KC_UP, KC_RGHT ,KC_BSPC,DE_EQL, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______),

    [2] = LAYOUT_split(
        _______, _______, LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),LSFT(KC_0), LSFT(KC_MINS), LSFT(KC_EQL), LSFT(KC_NO),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_RIGHT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DOWN, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, RESET, _______)};

