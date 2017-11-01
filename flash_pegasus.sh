#!/bin/sh
#make planck:hb_v1
dfu-programmer atmega32u2 erase
dfu-programmer atmega32u2 flash ./.build/pegasushoof_hb_v1.hex
dfu-programmer atmega32u2 start
