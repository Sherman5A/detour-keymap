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
#include QMK_KEYBOARD_H

#include <stdio.h>
#include "os_detection.h"
#include "features/achordion.h"

enum layer_names {
    _BASE,
    _NAV,
    _PUN,
    _NUM,
    _FUN,
    _MOUSE
};

#ifdef OLED_ENABLE
void render_key_status_or_logo(void);
void render_current_layer(void);
void render_current_wpm(void);
#endif

os_variant_t current_platform;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,                                                                            KC_1,         EE_CLR,        QK_BOOT,        QK_REBOOT,
        KC_Q,         KC_W,          KC_E,         KC_R,         KC_T,        KC_Y,        KC_U,         KC_I,          KC_O,          KC_P,    KC_QUOT,
        LGUI_T(KC_A), LALT_T(KC_S),  LSFT_T(KC_D), LCTL_T(KC_F), KC_G,        KC_H,        RCTL_T(KC_J), RSFT_T(KC_K),  RALT_T(KC_L),  RGUI_T(KC_SCLN),
        KC_Z,         KC_X,          KC_C,         KC_V,         KC_B,        KC_N,        KC_M,         KC_COMMA,      KC_DOT,        KC_SLASH,
        MO(_NAV),     OSM(MOD_LSFT), MO(_NUM),                   KC_SPC,      KC_BSPC,                   MO(_PUN),      OSM(MOD_LSFT), MO(_NAV)
    ),
    [_NAV] = LAYOUT(
        KC_TRNS,                                                                          KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,   KC_NO,
        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,       KC_LEFT,     KC_DOWN,      KC_UP,        KC_RIGHT,     KC_NO,
        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        KC_NO,                      KC_TRNS,     KC_TRNS,                   KC_NO,        KC_NO,        KC_NO
    ),
    [_PUN] = LAYOUT(
        KC_ESC,                                                                           KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_EXLM,      KC_AT,        KC_HASH,      KC_AMPR,      KC_ASTR,     KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,   KC_NO,
        KC_UNDS,      KC_PERC,      KC_MINS,      KC_EQL,       KC_PLUS,     KC_CIRC,     KC_LCTL,      KC_LSFT,      KC_LALT,      KC_LGUI,
        KC_BSLS,      KC_GRV,       KC_TILD,      KC_PIPE,      KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        KC_NO,                      KC_TRNS,     KC_TRNS,                   KC_NO,        KC_NO,        KC_NO
    ),
    [_NUM] = LAYOUT(
        KC_ESC,                                                                           KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_5,         KC_6,         KC_7,         KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,   KC_NO,
        KC_1,         KC_2,         KC_3,         KC_4,         KC_5,        KC_6,        KC_7,         KC_8,         KC_9,         KC_0,
        KC_NO,        KC_8,         KC_9,         KC_0,         KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        KC_NO,                      KC_TRNS,     KC_TRNS,                   KC_NO,        KC_NO,        KC_NO
    ),
    [_FUN] = LAYOUT(
        KC_ESC,                                                                           KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        MS_UP,        KC_NO,        KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,   KC_NO,
        KC_NO,        MS_LEFT,      MS_DOWN,      MS_RGHT,      KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        KC_NO,                      KC_TRNS,     KC_TRNS,                   KC_NO,        KC_NO,        KC_NO
    ),
    [_MOUSE] = LAYOUT(
        KC_ESC,                                                                           KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        MS_UP,        KC_NO,        KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,   KC_NO,
        KC_NO,        MS_LEFT,      MS_DOWN,      MS_RGHT,      KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,       KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,
        KC_NO,        KC_NO,        KC_NO,                      KC_TRNS,     KC_TRNS,                   KC_NO,        KC_NO,        KC_NO
    ),
};

// First 3 encoders are unused
#ifdef ENCODER_MAP_ENABLE
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [_BASE]  = { ENCODER_CCW_CW(KC_UP,    KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN)},
        [_NAV]   = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN)},
        [_PUN]   = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN)},
        [_NUM]   = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN)},
        [_FUN]   = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN)},
        [_MOUSE] = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN)}
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
const uint16_t PROGMEM q_w_esc[]       = { KC_Q, KC_W, COMBO_END };
const uint16_t PROGMEM a_s_tab[]       = { LGUI_T(KC_A), LALT_T(KC_S), COMBO_END };
const uint16_t PROGMEM z_x_cut[]       = { KC_Z, KC_X, COMBO_END };
const uint16_t PROGMEM z_c_copy[]      = { KC_Z, KC_C, COMBO_END };
const uint16_t PROGMEM z_v_paste[]     = { KC_Z, KC_V, COMBO_END };
const uint16_t PROGMEM spc_bspc_ent[]  = { KC_SPC, KC_BSPC, COMBO_END };
const uint16_t PROGMEM i_o_lprn[]      = { KC_I, KC_O, COMBO_END };
const uint16_t PROGMEM o_p_rprn[]      = { KC_O, KC_P, COMBO_END };
const uint16_t PROGMEM m_comm_lbrc[]   = { KC_N, KC_M, COMBO_END };
const uint16_t PROGMEM comm_dot_rbrc[] = { KC_M, KC_COMM, COMBO_END };
const uint16_t PROGMEM j_k_osm_sft[]   = { RCTL_T(KC_J), RSFT_T(KC_K), COMBO_END };

enum combos {
    Q_W_ESC,
    A_S_TAB,
    Z_X_CUT,
    Z_C_COPY,
    Z_V_PASTE,
    SPC_BSPC_ENT,
    I_O_LPRN,
    O_P_RPRN,
    M_COMM_LBRC,
    COMM_DOT_RBRC,
    J_K_OSM_SFT
};

combo_t key_combos[] = {
    [Q_W_ESC]       = COMBO(q_w_esc, KC_ESC),
    [A_S_TAB]       = COMBO(a_s_tab, KC_TAB),
    [Z_X_CUT]       = COMBO(z_x_cut, C(KC_X)),
    [Z_C_COPY]      = COMBO(z_c_copy, C(KC_C)),
    [Z_V_PASTE]     = COMBO(z_v_paste, C(KC_V)),
    [SPC_BSPC_ENT]  = COMBO(spc_bspc_ent, KC_ENTER),
    [I_O_LPRN]      = COMBO(i_o_lprn, KC_LPRN),
    [O_P_RPRN]      = COMBO(o_p_rprn, KC_RPRN),
    [M_COMM_LBRC]   = COMBO(m_comm_lbrc, KC_LBRC),
    [COMM_DOT_RBRC] = COMBO(comm_dot_rbrc, KC_RBRC),
    [J_K_OSM_SFT]   = COMBO(j_k_osm_sft, OSM(MOD_LSFT))
};
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

        //direction indicates which macro it is, with 1 being Macro 1, -1 being Macro 2, and 0 being no macro.
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

    bool clear_screen = false;
    bool rerender_platform = false;

    static void render_logo(void) {
        static const char PROGMEM logo[] = {
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        };

        oled_write(logo, false);
    }

    void render_keylock_status(led_t led_state) {
        bool caps_state = (led_state.caps_lock || is_caps_word_on());
        oled_write(PSTR("CAPS"), caps_state);
        oled_write(PSTR(" "), false);
        oled_write(PSTR("NUM"), led_state.num_lock);
        oled_write(PSTR(" "), false);
        oled_write(PSTR("SCRL"), led_state.scroll_lock);
        //oled_write_ln_P(PSTR(" "), false);
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

    void render_key_status_or_logo(){
        led_t led_state = host_keyboard_led_state();
        uint8_t mod_state = (get_mods()|get_oneshot_mods());
        if ( !led_state.num_lock && !led_state.caps_lock && !led_state.scroll_lock
        && !(mod_state & MOD_MASK_SHIFT) && !(mod_state & MOD_MASK_ALT) && !(mod_state & MOD_MASK_CTRL) && !(mod_state & MOD_MASK_GUI)) {
            if(!clear_screen) {
                render_logo();
                rerender_platform = true;
            }
            clear_screen = true;
        } else {
            if (clear_screen == true) {
                oled_clear();
                oled_render();
                clear_screen = false;
            }
            oled_set_cursor(8,0);
            render_keylock_status(led_state);
            oled_set_cursor(8,1);
            render_mod_status(mod_state);
            rerender_platform = true;
        }

    }

    void render_current_layer(){
        switch (get_highest_layer(layer_state)) {
                case 0:
                    oled_write(PSTR("Layer 0"), false);
                    break;
                case 1:
                    oled_write(PSTR("Layer 1"), false);
                    break;
                case 2:
                    oled_write(PSTR("Layer 2"), false);
                    break;
                case 3:
                    oled_write(PSTR("Layer 3"), false);
                    break;
                default:
                    oled_write(PSTR("Layer ?"), false);    // Should never display, here as a catchall
        }
    }

    void render_current_wpm(){
        oled_write_P(PSTR("WPM: "), false);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);
    }

    void render_platform_status(int col, int line) {
        /* Show Ctrl-Gui Swap options */
        static const char PROGMEM logo[][5][3] = {
            {{0x9B, 0x9C, 0}, {0xbb, 0xbc, 0}}, //Android
            {{0x99, 0x9A, 0}, {0xb9, 0xba, 0}}, //Linux
            {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}}, //Windows
            {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}}, //Mac/iOS
            {{0x9D, 0x9E, 0}, {0xbd, 0xbe, 0}}, //Empty Placeholder
        };
        current_platform = detected_host_os();
        switch (current_platform) {
            /*case OS_ANDROID: //Android
                oled_set_cursor(col,line);
                oled_write(logo[0][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[0][1], false);
                break;*/
            case OS_LINUX: //Linux
                oled_set_cursor(col,line);
                oled_write(logo[1][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[1][1], false);
                keymap_config.swap_lctl_lgui = false;
                keymap_config.swap_rctl_rgui = false;
                break;
            case OS_WINDOWS: //Windows
                oled_set_cursor(col,line);
                oled_write(logo[2][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[2][1], false);
                keymap_config.swap_lctl_lgui = false;
                keymap_config.swap_rctl_rgui = false;
                break;
            case OS_MACOS: //Mac
                oled_set_cursor(col,line);
                oled_write(logo[3][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[3][1], false);
                keymap_config.swap_lctl_lgui = true;
                keymap_config.swap_rctl_rgui = true;
                break;
            case OS_IOS: //iOS
                oled_set_cursor(col,line);
                oled_write(logo[3][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[3][1], false);
                keymap_config.swap_lctl_lgui = true;
                keymap_config.swap_rctl_rgui = true;
                break;
            default: //OS_UNSURE or not configured
                oled_set_cursor(col,line);
                oled_write(logo[4][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[4][1], false);
                break;
        }
        rerender_platform = false;
    }

    bool oled_task_user(void) {
        render_key_status_or_logo();
        oled_set_cursor(8,2);
        render_current_layer();
        #ifdef DYNAMIC_MACRO_ENABLE
            render_dynamic_macro_status(18,2);
        #endif
        oled_set_cursor(8,3);
        render_current_wpm();
        #ifdef OS_DETECTION_ENABLE
            if(current_platform != detected_host_os() || rerender_platform) { render_platform_status(3,0); }
        #endif

        return false;
    }

#endif

