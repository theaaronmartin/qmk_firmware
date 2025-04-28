// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum piantor_layers {
  _QWERTY,
  _SYM,
  _NAV,
  _NUM
};

enum piantor_keycodes {
  QWERTY = SAFE_RANGE,
  SYM,
  NAV,
  NUM,
};

// #define NAV TT(_NAV)
#define NAV MO(_NAV)
#define SYM MO(_SYM)
#define NUM MO(_NUM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
      * │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ' │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ : │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
      *           ┌───┐                   ┌───┐
      *           │Ctl├───┐           ┌───┤Ctl│
      *           └───┤Nav├───┐   ┌───┤Sym├───┘
      *               └───┤Sft│   │Spc├───┘
      *                   └───┘   └───┘
      */
    [_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,  KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                        KC_H,  KC_J,    KC_K,    KC_L,    KC_QUOT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                        KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SCLN,
                                   QK_LEAD, NAV, KC_LSFT,                       KC_SPC,  SYM,   KC_LCTL
    ),

    [_SYM] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,    KC_HASH,    KC_DLR,    KC_PERC,                     KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_TILD,    KC_GRV,
        KC_ESC,  KC_LCBR,  KC_LBRC,    KC_LPRN,   KC_MINS,                     KC_UNDS,    KC_RPRN,    KC_RBRC,    KC_RCBR,    KC_QUES,
        KC_NO,   KC_NO,    KC_PIPE,    KC_SLSH,   KC_EQL,                      KC_PLUS,    KC_BSLS,    KC_NO,      KC_NO,      KC_SCLN,
                                       KC_TRNS,   NUM,    KC_LSFT,     KC_SPC, KC_TRNS,    KC_LCTL
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        KC_TAB,  KC_LGUI, KC_LALT, LGUI(KC_LEFT), LGUI(KC_RGHT),                 KC_NO,   KC_NO,   KC_UP,   KC_NO,   KC_DEL,
        KC_LCTL, KC_LSFT, KC_ESC,  LALT(KC_TAB),  LGUI(KC_TAB),                  KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        KC_ENT,  KC_NO,   KC_NO,   CW_TOGG,       KC_CAPS,                       KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_ENT,
                                   KC_TRNS,       KC_TRNS, KC_LSFT,      KC_SPC, NUM,     KC_LCTL
    ),

    [_NUM] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,   KC_7,    KC_8,    KC_9,    KC_0,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                             KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_F11,                            KC_F12, KC_NUM,  KC_MINS, KC_PSCR, KC_INS,
                          KC_TRNS, KC_TRNS, KC_LSFT,                           KC_SPC, KC_TRNS, KC_TRNS
    )
};

void leader_start_user(void) {};

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_E)) {
        // Win + E (My PC)
        SEND_STRING(SS_LGUI("e"));
    } else if (leader_sequence_one_key(KC_R)) {
        // Win + R (Run)
        SEND_STRING(SS_LGUI("r"));
    } else if (leader_sequence_one_key(KC_Q)) {
        // Alt + F4
        SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    } else if (leader_sequence_one_key(KC_S)) {
        // Win + Shift + S (Screenshot)
        SEND_STRING(SS_LGUI(SS_LSFT("s")));
    } else if (leader_sequence_one_key(KC_C)) {
        // Calculator
        SEND_STRING(SS_LALT(SS_TAP(X_CALC)));
    } else if (leader_sequence_one_key(KC_X)) {
        // Repeat
        SEND_STRING(SS_DOWN(X_X));
    } else if (leader_sequence_one_key(KC_M)) {
        // Re-detect Monitor via KVM switch
        SEND_STRING(SS_DOWN(X_NUM));
        SEND_STRING((SS_TAP(X_MINS)));
        SEND_STRING(SS_UP(X_NUM));
        SEND_STRING(SS_DELAY(500));
        SEND_STRING(SS_TAP(X_Q));
        SEND_STRING(SS_TAP(X_2));
        SEND_STRING(SS_DELAY(500));
        SEND_STRING(SS_TAP(X_ENT));
    }
}
