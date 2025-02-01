/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

enum custom_keycodes {
     DRAG_SCROLL = SAFE_RANGE,
     CC_LBRK,
     CC_RBRK,
     CC_LPAREN,
     CC_RPAREN,
     CC_LCBRACE,
     CC_RCBRACE,
     CC_PIPE,
     CC_FSLSH,
     CC_BSLSH,
};

/// This is not actually for umlaut, its how we do left bracket and all the other keys remapped by intl layouts
enum {
    TD_A_UMLAUT,
    TD_O_UMLAUT,
    TD_U_UMLAUT,
    TD_E_UMLAUT,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // The keycodes below don't correlate the same way with the Swiss-German keyboard map selected (operating system level)
    [TD_A_UMLAUT] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_QUOT), // KC_QUOT => ä
    [TD_O_UMLAUT] = ACTION_TAP_DANCE_DOUBLE(KC_O, KC_SEMICOLON), // KC_QUOT => ö
    [TD_U_UMLAUT] = ACTION_TAP_DANCE_DOUBLE(KC_U, KC_LBRC), // KC_QUOT => ü
};

// Software mouse scroll
bool set_scrolling = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     switch (keycode) {
          case CC_LBRK:
               // ALT-5 => [
               if (record->event.pressed) { SEND_STRING(SS_LALT("5")); }
               return false;
          case CC_RBRK:
               // ALT-6 => ]
               if (record->event.pressed) { SEND_STRING(SS_LALT("6")); }
               return false;
          case CC_PIPE:
               // ALT-7 => |
               if (record->event.pressed) { SEND_STRING(SS_LALT("7")); }
               return false;
          case CC_LCBRACE:
               // ALT-8 => {
               if (record->event.pressed) { SEND_STRING(SS_LALT("8")); }
               return false;
          case CC_RCBRACE:
               // ALT-9 => }
               if (record->event.pressed) { SEND_STRING(SS_LALT("9")); }
               return false;
          case CC_LPAREN:
               if (record->event.pressed) { SEND_STRING(SS_LSFT("8")); }
               return false;
          case CC_RPAREN:
               if (record->event.pressed) { SEND_STRING(SS_LSFT("9")); }
               return false;
          case CC_FSLSH:
               if (record->event.pressed) { SEND_STRING(SS_LSFT("7")); }
               return false;
          case CC_BSLSH:
               if (record->event.pressed) { SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LALT) SS_TAP(X_7) SS_UP(X_LALT) SS_UP(X_LSFT)); } //  SS_LSFT("7")
               return false;
    }
    return true;
}

enum charybdis_keymap_layers {
     LAYER_BASE = 0,
     _L1,
     _L2,
     _L3,
     LAYER_COLEMAK = 5,
     _AW_MOUSE = 6,

};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     // Basil base layer
     [LAYER_BASE] = LAYOUT_charybdis_4x6(
     // Querty, with tapdance for intl chars
     // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          KC_CAPS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0, QK_BOOT,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          KC_ESC,    KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,     KC_Y, TD(TD_U_UMLAUT), KC_I, TD(TD_O_UMLAUT),  KC_P, KC_MINUS, KC_AT,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          KC_TAB,    TD(TD_A_UMLAUT),    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L, KC_SLASH,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,   KC_M,   KC_COMMA,  KC_DOT,  KC_LALT, KC_LCTL,
     // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_ENT, KC_LSFT,   KC_LGUI,      KC_SPC,  KC_BSPC,
                                           KC_LCTL,   TO(_L1),        TO(_L2)
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     ),

     [_L1] = LAYOUT_charybdis_4x6(
     // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        XXXXXXX, KC_ESC,KC_EQUAL,LSFT(KC_3),LSFT(KC_5),KC_SLASH,  LALT(KC_7), LALT(KC_5),LALT(KC_6),LALT(KC_7),LSFT(KC_2), KC_MINUS,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
XXXXXXX,KC_AT,LALT(KC_G),LSFT(KC_RBRACKET),LSFT(KC_MINUS),LSFT(KC_SLASH),   KC_GRAVE,LSFT(KC_8),LSFT(KC_9),LSFT(KC_GRAVE),LSFT(KC_EQUAL),XXXXXXX,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         XXXXXXX,KC_MSTP, KC_BRID, KC_BRIU, KC_PSCREEN, KC_MPLY,  XXXXXXX,KC_VOLD,KC_VOLU, XXXXXXX, KC_LALT, KC_LCTL,
     // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_ENT, KC_LSFT,   KC_LGUI,      KC_SPC,  KC_BSPC,
                                            KC_LCTL, TO(0),         TO(0)
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     ),

     [_L2] = LAYOUT_charybdis_4x6(
     // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          KC_F12, KC_F1,  KC_F2,  KC_F3,    KC_F4,    KC_F5,      KC_F6,  KC_F7,   KC_F8,    KC_F9,    KC_F10, KC_F11,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_ESC, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4, KC_KP_5,      KC_KP_6, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_0, XXXXXXX,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_AT, KC_LT, KC_GT, CC_LCBRACE, CC_RCBRACE, KC_BSLS,     KC_KP_EQUAL_AS400, KC_COLON, KC_SCLN, KC_QUES, KC_EXLM, XXXXXXX,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
   XXXXXXX, LSFT_T(KC_2), LSFT_T(KC_3), CC_LBRK, CC_RBRK, XXXXXXX, XXXXXXX, KC_HASH, KC_CIRC, KC_AMPR, KC_LALT, KC_LCTL,
     // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    KC_ENT, KC_LSFT,   KC_LGUI,     KC_SPC,  KC_BSPC,
                                            KC_LCTL, TO(0),         TO(0)
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     ),
     [_L3] = LAYOUT_charybdis_4x6(
//      // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
           KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//      // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
           KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, LCTL(KC_LEFT), KC_UP, LCTL(KC_RIGHT), XXXXXXX, XXXXXXX,
//      // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
           XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,    XXXXXXX,  KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,
//      // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
           XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_U, KC_WH_D, XXXXXXX,    XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, KC_LALT, KC_LCTL,
//      // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                KC_ENT, KC_LSFT,   KC_LGUI,         KC_SPC,  KC_BSPC,
                                            KC_LCTL, TO(0),         TO(0)
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     ),

// clang-format on
     //[LAYER_COLEMAK] = LAYOUT_charybdis_4x6(
     // Colemak-dh(m?)
     // ignore top row to start with, aiming for a minimal usable layout to build on
     // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
     //     KC_ESC,    KC_NO,    KC_NO,    KC_VOLD,    KC_VOLU,    KC_MPLY,       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
    //      KC_NO,    MT(MOD_LSFT,KC_Q),    MT(MOD_LALT,KC_W),    MT(MOD_LCTL,KC_F),    MT(MOD_LGUI,KC_P),    KC_B, KC_J,       MT(MOD_LGUI,KC_L),    MT(MOD_LCTL,KC_U),    MT(MOD_LALT,KC_Y),    KC_NO, KC_NO,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
     //     KC_ESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,       KC_M,    KC_N,    KC_E,    KC_I, KC_O, KC_NO,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
    //      KC_TAB,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_NO,
     // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
     //                              KC_ENT, KC_LSFT,   KC_LGUI,     KC_SPC,  KC_BSPC,
     //                                       KC_LCTL, TO(0),         TO(0)
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     //),


// // Transparent template
//      // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
//           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//      // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
//           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//      // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
//           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//      // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
//           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//      // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
//                                    XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
//                                              XXXXXXX, XXXXXXX,      XXXXXXX
//      //                            ╰───────────────────────────╯ ╰──────────────────╯
};
// clang-format on
