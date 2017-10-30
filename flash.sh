#!/bin/sh
#make planck:hb_v1
dfu-programmer atmega32u4 erase
dfu-programmer atmega32u4 flash ./.build/planck_rev4_hb_v1.hex
dfu-programmer atmega32u4 start
