/*
 * Copyright 2024 Nachie
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
#include "keycodes.h"
#include "rgb_matrix_types.h"
#include QMK_KEYBOARD_H

#include <stdio.h>
#include "os_detection.h"
#include "features/achordion.h"

enum layer_names {
    _BASE,
    _CANARY,
    _NAV,
    _PUN,
    _NUM,
    _FUN,
    _MEDIA,
    _MOUSE,
    _RGB,
    _KEY
};

const char *human_layer_names[] =  {
    "qwerty",
    "canary",
    "nav",
    "pun",
    "num",
    "fun",
    "media",
    "mouse",
    "rgb",
    "key"
};

#ifdef OLED_ENABLE
void render_oled_logo(void);
void render_key_status(void);
void render_current_layer(void);
void render_current_wpm(void);
#endif

os_variant_t current_platform;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,                                                                             TG(_MEDIA),   TG(_MOUSE),    TG(_RGB),      TG(_KEY),
        KC_Q,         KC_W,          KC_E,          KC_R,         KC_T,        KC_Y,        KC_U,         KC_I,          KC_O,          KC_P,    KC_QUOT,
        LGUI_T(KC_A), LALT_T(KC_S),  LSFT_T(KC_D),  LCTL_T(KC_F), KC_G,        KC_H,        RCTL_T(KC_J), RSFT_T(KC_K),  RALT_T(KC_L),  RGUI_T(KC_SCLN),
        KC_Z,         KC_X,          KC_C,          KC_V,         KC_B,        KC_N,        KC_M,         KC_COMMA,      KC_DOT,        KC_SLASH,
        MO(_NAV),     QK_LEAD,       MO(_NUM),                    KC_SPC,      KC_BSPC,                   MO(_PUN),      MO(_FUN),      KC_NO
    ),
    [_CANARY] = LAYOUT(
        KC_ESC,                                                                             TG(_MEDIA),   TG(_MOUSE),    TG(_RGB),      TG(_KEY),
        KC_W,         KC_L,          KC_Y,         KC_P,          KC_K,        KC_Z,        KC_X,         KC_O,          KC_U,          KC_SCLN, KC_QUOT,
        LGUI_T(KC_C), LALT_T(KC_R),  LSFT_T(KC_S), LCTL_T(KC_T),  KC_B,        KC_F,        RCTL_T(KC_N), RSFT_T(KC_E),  RALT_T(KC_I),  RGUI_T(KC_A),
        KC_J,         KC_V,          KC_D,         KC_G,          KC_Q,        KC_M,        KC_H,         KC_SLASH,      KC_COMM,       KC_DOT,
        MO(_NAV),     QK_LEAD,       MO(_NUM),                    KC_TRNS,     KC_TRNS,                   MO(_PUN),      MO(_FUN),      KC_NO
    ),
    [_NAV] = LAYOUT(
        KC_TRNS,                                                                            KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_NO,        MS_BTN1,       MS_UP,        MS_BTN2,       KC_NO,       LCTL(KC_Y),  KC_PGUP,      KC_NO,         KC_NO,         KC_NO,   KC_DEL,
        KC_NO,        MS_LEFT,       MS_DOWN,      MS_RGHT,       KC_HOME,     KC_LEFT,     KC_DOWN,      KC_UP,         KC_RIGHT,      KC_END,
        LCTL(KC_Z),   LCTL(KC_X),    LCTL(KC_C),   LCTL(KC_V),    KC_NO,       KC_NO,       KC_PGDN,      KC_NO,         KC_NO,         KC_NO,
        KC_NO,        KC_NO,         KC_NO,                       KC_TRNS,     KC_TRNS,                   KC_NO,         KC_NO,         KC_NO
    ),
    [_PUN] = LAYOUT(
        KC_TRNS,                                                                            KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_EXLM,      KC_AT,         KC_HASH,      KC_DLR,        KC_PERC,     KC_CIRC,     KC_AMPR,      KC_ASTR,       KC_NO,         KC_DQUO, KC_QUOT,
        KC_UNDS,      KC_MINS,       KC_PLUS,      KC_EQL,        KC_SLASH,    KC_SLASH,    KC_LCTL,      KC_LSFT,       KC_LALT,       KC_LGUI,
        KC_PIPE,      KC_BSLS,       KC_TILD,      KC_GRV,        KC_NO,       KC_NO,       KC_NO,        KC_LABK,       KC_RABK,       KC_QUES,
        KC_NO,        KC_NO,         KC_NO,                       KC_TRNS,     KC_TRNS,                   KC_NO,         KC_NO,         KC_NO
    ),
    [_NUM] = LAYOUT(
        KC_TRNS,                                                                            KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_NO,        KC_5,          KC_6,         KC_7,          KC_NO,       KC_UNDS,     KC_MINS,      KC_PLUS,       KC_ASTR,       KC_SLASH, KC_EQL,
        KC_1,         KC_2,          KC_3,         KC_4,          KC_5,        KC_6,        KC_7,         KC_8,          KC_9,          KC_0,
        KC_NO,        KC_8,          KC_9,         KC_0,          KC_NO,       KC_NO,       KC_NO,        KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_NO,        KC_NO,         KC_NO,                       KC_TRNS,     KC_TRNS,                   KC_NO,         KC_NO,         KC_NO
    ),
    [_FUN] = LAYOUT(
        KC_TRNS,                                                                            KC_CAPS,      KC_NUM,        KC_SCRL,       KC_PSCR,
        KC_NO,        KC_NO,         KC_NO,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,   KC_NO,
        KC_F1,        KC_F2,         KC_F3,        KC_F4,         KC_F5,       KC_F6,       KC_F7,        KC_F8,         KC_F9,         KC_F10,
        KC_F11,       KC_F12,        KC_NO,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,
        KC_NO,        KC_NO,         KC_NO,                       KC_TRNS,     KC_TRNS,                   KC_NO,         KC_NO,         KC_NO
    ),
    [_MEDIA] = LAYOUT(
        KC_MUTE,                                                                            KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_NO,        KC_NO,         MS_UP,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,   KC_NO,
        KC_MPRV,      KC_MPLY,       KC_MNXT,      KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,
        KC_NO,        KC_NO,         KC_NO,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,
        KC_NO,        KC_NO,         KC_NO,                       MS_BTN1,     MS_BTN2,                   MS_BTN3,       MS_BTN4,       KC_NO
    ),
    [_MOUSE] = LAYOUT(
        KC_ESC,                                                                             KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_NO,        KC_NO,         MS_UP,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,   KC_NO,
        KC_NO,        MS_LEFT,       MS_DOWN,      MS_RGHT,       KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,
        KC_NO,        KC_NO,         KC_NO,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,
        KC_NO,        KC_NO,         KC_NO,                       MS_BTN1,     MS_BTN2,                   MS_BTN3,       MS_BTN4,       KC_NO
    ),
    [_RGB] = LAYOUT(
        RM_TOGG,                                                                            RM_NEXT,      RM_HUED,       TG(_RGB),      RM_HUEU,
        KC_NO,        KC_NO,         MS_UP,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        RM_PREV,       RM_HUED,       RM_SATD, KC_NO,
        KC_NO,        MS_LEFT,       MS_DOWN,      MS_RGHT,       KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,
        KC_NO,        KC_NO,         KC_NO,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,
        KC_NO,        KC_NO,         KC_NO,                       KC_TRNS,     KC_TRNS,                   KC_NO,         KC_NO,         KC_NO
    ),
    [_KEY] = LAYOUT(
        KC_SLEP,                                                                            QK_BOOT,      QK_REBOOT,     EE_CLR,        KC_TRNS,
        KC_NO,        KC_NO,         KC_NO,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,   KC_NO,
        KC_NO,        KC_NO,         KC_NO,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,
        KC_NO,        KC_NO,         KC_NO,        KC_NO,         KC_NO,       KC_NO,       KC_NO,        KC_NO,         KC_NO,         KC_NO,
        KC_NO,        KC_NO,         KC_NO,                       DF(_BASE),   DF(_CANARY),               KC_NO,         KC_NO,         KC_NO
    )
};

// First 3 encoders are unused
#ifdef ENCODER_MAP_ENABLE
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [_BASE]   = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_UP, KC_DOWN)},
        [_CANARY] = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_UP, KC_DOWN)},
        [_NAV]    = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
        [_PUN]    = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_UP, KC_DOWN)},
        [_NUM]    = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_UP, KC_DOWN)},
        [_FUN]    = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_UP, KC_DOWN)},
        [_MEDIA]  = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [_MOUSE]  = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(MS_WHLU, MS_WHLD)},
        [_RGB]    = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(RM_VALD, RM_VALU)},
        [_KEY]    = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_BRID, KC_BRIU)}
    };
#endif

#ifdef ACHORDION_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_achordion(keycode, record)) {
        return false;
    }
    return true;
}
#endif

#ifdef ACHORDION_ENABLE
void matrix_scan_user(void) {
    achordion_task();
}
#endif

#ifdef ACHORDION_ENABLE
bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {

    switch (tap_hold_keycode) {
        case LCTL_T(KC_F):
        case RCTL_T(KC_J):
            return true;
    }

    if (tap_hold_record->event.key.col <= 2 && other_record->event.key.col >= 3) {
        return true;
    }
    if (tap_hold_record->event.key.col >= 3 && other_record->event.key.col <= 2) {
        return true;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}
#endif

#ifdef ACHORDION_ENABLE
uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    return 500;
}
#endif

#ifdef ACHORDION_STREAK
uint16_t achordion_streak_chord_timeout(
    uint16_t tap_hold_keycode, uint16_t next_keycode) {
    uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
    if ((mod & MOD_LSFT) != 0 || (mod & MOD_RSFT) != 0) {
       return 0;
   }

    return 200;
}
#endif

#ifdef COMBO_ENABLE
// Combos
const uint16_t PROGMEM q_w_esc[]        = { KC_Q, KC_W, COMBO_END };
const uint16_t PROGMEM a_s_tab[]        = { LGUI_T(KC_A), LALT_T(KC_S), COMBO_END };
const uint16_t PROGMEM z_x_cut[]        = { KC_Z, KC_X, COMBO_END };
const uint16_t PROGMEM z_c_copy[]       = { KC_Z, KC_C, COMBO_END };
const uint16_t PROGMEM z_v_paste[]      = { KC_Z, KC_V, COMBO_END };
const uint16_t PROGMEM spc_bspc_ent[]   = { KC_SPC, KC_BSPC, COMBO_END };
const uint16_t PROGMEM f_e_lprn[]       = { LCTL_T(KC_F), KC_E, COMBO_END };
const uint16_t PROGMEM j_i_rprn[]       = { RCTL_T(KC_J), KC_I, COMBO_END };
const uint16_t PROGMEM d_v_lbrc[]       = { LSFT_T(KC_D), KC_V, COMBO_END };
const uint16_t PROGMEM k_n_rbrc[]       = { RSFT_T(KC_K), KC_N, COMBO_END };
const uint16_t PROGMEM e_r_lcbr[]       = { KC_E, KC_R, COMBO_END };
const uint16_t PROGMEM u_i_rcbr[]       = { KC_U, KC_I, COMBO_END };
const uint16_t PROGMEM j_k_osm_sft[]    = { RCTL_T(KC_J), RSFT_T(KC_K), COMBO_END };
const uint16_t PROGMEM btn1_btn2_btn3[] = { MS_BTN1, MS_BTN2, COMBO_END };

enum combos {
    Q_W_ESC,
    A_S_TAB,
    Z_X_CUT,
    Z_C_COPY,
    Z_V_PASTE,
    SPC_BSPC_ENT,
    F_E_LPRN,
    J_I_RPRN,
    D_V_LBRC,
    K_N_RBRC,
    E_R_LCBR,
    U_I_RCBR,
    J_K_OSM_SFT,
    BTN1_BTN2_BTN3
};

combo_t key_combos[] = {
    [Q_W_ESC]        = COMBO(q_w_esc, KC_ESC),
    [A_S_TAB]        = COMBO(a_s_tab, KC_TAB),
    [Z_X_CUT]        = COMBO(z_x_cut, C(KC_X)),
    [Z_C_COPY]       = COMBO(z_c_copy, C(KC_C)),
    [Z_V_PASTE]      = COMBO(z_v_paste, C(KC_V)),
    [SPC_BSPC_ENT]   = COMBO(spc_bspc_ent, KC_ENTER),
    [F_E_LPRN]       = COMBO(f_e_lprn, KC_LPRN),
    [J_I_RPRN]       = COMBO(j_i_rprn, KC_RPRN),
    [D_V_LBRC]       = COMBO(d_v_lbrc, KC_LBRC),
    [K_N_RBRC]       = COMBO(k_n_rbrc, KC_RBRC),
    [E_R_LCBR]       = COMBO(e_r_lcbr, KC_LCBR),
    [U_I_RCBR]       = COMBO(u_i_rcbr, KC_RCBR),
    [J_K_OSM_SFT]    = COMBO(j_k_osm_sft, OSM(MOD_LSFT)),
    [BTN1_BTN2_BTN3] = COMBO(btn1_btn2_btn3, MS_BTN3)
};
#endif

#ifdef LEADER_ENABLE
    void leader_end_user(void) {
        if (leader_sequence_two_keys(KC_P, KC_A)) {
            SEND_STRING("()");
        } else if (leader_sequence_two_keys(KC_P, KC_I)) {
            SEND_STRING("()" SS_TAP(X_LEFT));
        } else if (leader_sequence_two_keys(KC_B, KC_A)) {
            SEND_STRING("{}");
        } else if (leader_sequence_two_keys(KC_B, KC_I)) {
            SEND_STRING("{}" SS_TAP(X_LEFT));
        } else if (leader_sequence_three_keys(KC_B, KC_B, KC_I)) {
            SEND_STRING("[]");
        } else if (leader_sequence_three_keys(KC_B, KC_B, KC_A)) {
            SEND_STRING("[]" SS_TAP(X_LEFT));
        }
    }
#endif

#ifdef TAPPING_TERM_PER_KEY
    // Tap term timings
    uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
        switch (keycode) {
            // Pinky keys
            case LGUI_T(KC_A):
            case LALT_T(KC_S):
            case RALT_T(KC_L):
            case RGUI_T(KC_SCLN):
            // Pinky keys for canary
            case LGUI_T(KC_C):
            case LALT_T(KC_R):
            case RGUI_T(KC_A):
            case RALT_T(KC_I):
            // Number layer
            case LGUI_T(KC_0):
            case LALT_T(KC_1):
            case RALT_T(KC_8):
            case RGUI_T(KC_9):
                return 180;
            // All other keys
            default:
                return TAPPING_TERM;
        };
    };
#endif

#ifdef COMBO_PER_TERM_COMBO
    uint8_t get_combo_term(uint16_t combo_index, combo_t *combo) {
        switch (combo_index) {
            case A_S_TAB:
                return 75;
        }
        return COMBO_TERM;
    }
#endif

#ifdef COMBO_MUST_TAP_PER_COMBO
    bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
        switch (combo_index) {
            case J_K_OSM_SFT:
                return true;
        }
        return false;
    }
#endif

#ifdef OLED_ENABLE
    #ifdef DYNAMIC_MACRO_ENABLE
        bool macro1;
        bool macro1rec;
        bool macro2;
        bool macro2rec;
        bool prevEnabled;
        uint8_t prevRGBmode;

        void render_dynamic_macro_status(int col, int line){
            oled_set_cursor(col,line);
            macro1rec ? oled_write(PSTR("DM1"), macro1) : oled_write(PSTR("      "),false);
            oled_set_cursor(col,line+1);
            macro2rec ? oled_write(PSTR("DM2"), macro2) : oled_write(PSTR("      "),false);
        }

        // Direction indicates which macro it is, with 1 being Macro 1, -1 being Macro 2, and 0 being no macro.
        bool dynamic_macro_record_start_user(int8_t direction){
            prevEnabled = rgb_matrix_is_enabled();
            if (!prevEnabled) { rgb_matrix_enable(); }
            prevRGBmode = rgb_matrix_get_mode();
            rgb_matrix_mode(RGB_MATRIX_BREATHING);
            switch(direction){
                case 1:
                    macro1 = false;
                    macro1rec = true;
                    break;
                case -1:
                    macro2 = false;
                    macro2rec = true;
                    break;
                default:
                    macro1 = false;
                    macro2 = false;
                    macro1rec = false;
                    macro2rec = false;
                    break;
            }
            return true;
        }

        bool dynamic_macro_record_end_user(int8_t direction){
            prevEnabled ? rgb_matrix_mode(prevRGBmode) : rgb_matrix_disable();
            switch(direction){
                case 1:
                    macro1 = true;
                    break;
                case -1:
                    macro2 = true;
                    break;
                default:
                    macro1 = false;
                    macro2 = false;
                    break;
            }
            return true;
        }
    #endif

    bool rerender_platform = false;
    bool render_logo = true;

    void render_keylock_status(led_t led_state) {
        bool caps_state = (led_state.caps_lock || is_caps_word_on());
        oled_write(PSTR("CAPS"), caps_state);
        oled_write(PSTR(" "), false);
        oled_write(PSTR("NUM"), led_state.num_lock);
        oled_write(PSTR(" "), false);
        oled_write(PSTR("SCRL"), led_state.scroll_lock);
        // oled_write_ln_P(PSTR(" "), false);
    }

    void render_mod_status(uint8_t modifiers) {
        oled_write(PSTR("SH"), (modifiers & MOD_MASK_SHIFT));
        oled_write(PSTR(" "), false);
        (current_platform == OS_MACOS || current_platform == OS_IOS)  ? oled_write(PSTR("CMD"), (modifiers & MOD_MASK_GUI)) : oled_write(PSTR("CT"), (modifiers & MOD_MASK_CTRL));
        oled_write(PSTR(" "), false);
        (current_platform == OS_MACOS || current_platform == OS_IOS) ? oled_write(PSTR("OPT"), (modifiers & MOD_MASK_ALT)) : oled_write(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
        oled_write(PSTR(" "), false);
        (current_platform == OS_MACOS || current_platform == OS_IOS) ? oled_write(PSTR("CT"), (modifiers & MOD_MASK_CTRL)) : oled_write(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
    }

    void render_key_status(){
        led_t led_state = host_keyboard_led_state();
        uint8_t mod_state = (get_mods()|get_oneshot_mods());
        oled_set_cursor(8,0);
        render_keylock_status(led_state);
        oled_set_cursor(8,1);
        render_mod_status(mod_state);
    }

    void render_current_layer(){
        char PROGMEM layer[18];
        snprintf(layer, sizeof(layer), "Layer %s", human_layer_names[get_highest_layer(layer_state)]);
        oled_write_ln_P(layer, false);
    }

    void render_current_wpm(){
        oled_write_P(PSTR("WPM "), false);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);
    }

    void render_oled_logo() {
        static const char PROGMEM raw_logo[] = {
            255,255,255,255,255,255,223,255,255,255,253,255,254,254,254,254,254,254,255,253,253,251,231,207,223,127, 95,223,223,127, 63,255,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
            0,255,255,223,199,251,133,255,255,  8,101,203,247,173,208,237,249,131,253,195,255,255,255,255, 31,255,127,255, 18,  3, 15, 31, 31,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
            0,255,255,255,255,253,226,240,199, 15, 16,  1,  3,103,255, 23, 63,255,219, 11, 41, 21, 15,  7,  0,  1,  4,  6,  6,  6,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
            0,255,255,255,255,255,255,255,  0,  0,  0,  0,  0,  0,  1,  0,  3,  1,  0,  0,  0,  0,  0,  0,192,248,248,252,254,254,255,255,255,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
            0,
        };
        oled_write_raw_P(raw_logo, sizeof(raw_logo));
    }

    bool oled_task_user(void) {
        if (render_logo) {
            render_oled_logo();
            render_logo = false;
        }
        render_key_status();
        oled_set_cursor(8,2);
        render_current_layer();
        #ifdef DYNAMIC_MACRO_ENABLE
            render_dynamic_macro_status(18,2);
        #endif
        oled_set_cursor(8,3);
        render_current_wpm();

        return false;
    }

#endif
