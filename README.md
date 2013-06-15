# cswm

cswm is a minimalist tiling window manager that splits the screen into
a larger single-window master area and a smaller (by default)
window-stacking area; windows can be swapped between areas.  All window
manipulation is done via keyboard.

This project is a fork of 2wm, which was created by Anselm R. Garbe.

## Building

Modify the following preprocessor variables in config.h as appropriate
for your system configuration:
- CMD_TERMINAL (terminal program, defaults to 'st')
- CMD_BROWSER (web browser, defaults to 'firefox')
- CMD_LOCK (lock program, defaults to 'slock')

Then build/install from the Makefile as desired.

## Licensing

This project is distributed under the MIT/X Consortium License.
