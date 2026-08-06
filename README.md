# QMx2040 ZMK Module

A Zephyr module containing the ZMK firmware for the [QMx2040].

[QMx2040]; https://onedeadkey.github.io/qmx2040/

Contrary to most other ergonomic keyboards, this firmware is built to be
entirely layout-agnostic. This means it’s fully compatible out-of-the-box with
any European keyboard layout, without any adaptations necessary.

## Features

### DIP-Switches

Parts of the keymap can be toggled on / off by sliding one of the dip-switches.
Going from left to right, those switches can:

- enable thumb taps
- enable home row mods
- disable sticky keys
- enable Mac support
- toggle your custom layer

### Mod-Holds

The navigation layer makes use of a custom zmk behavior called a `mod-hold`.
Any active modifier when pressing the nav key will be held for as long as the
nav key is held. This allows you to easily combine modifiers with this layer,
even if they are on the same hand (like ctrl and shift).

### Numpad Keys

This keymap uses a numpad, but doesn’t include a `num-lock` key, as the state
of this flag is handled by the keyboard. When pressing a numpad key, `num-lock`
will be automatically forced on if it wasn’t already.
