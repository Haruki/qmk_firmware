#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    yasintahir/silentreader
#define PRODUCT         YAS62
#define DESCRIPTION     YAS62

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

//                        0   1   2   3   4   5   6   7   8   9   A
#define MATRIX_ROW_PINS { C3, C4, C5, C6, C7 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, B0, B1, B2, B3, B4, B5, B6, B7}
#define DIODE_DIRECTION COL2ROW

#define RGBLED_NUM 12
#define RGB_DI_PIN C1
#define RGBLIGHT_ANIMATIONS
