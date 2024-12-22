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
        KC_ESC,                                                                       KC_1,        EE_CLR,      QK_BOOT,     QK_REBOOT,
        KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,    KC_BSPC,
        KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_H,        KC_J,        KC_K,        KC_L,        KC_ENT,
        KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_N,        KC_M,        KC_DOT,      KC_LSFT,     MO(1),
        KC_LGUI,     KC_LGUI,     KC_LALT,                  KC_SPC,      KC_BSPC,                  KC_RGUI,     KC_RALT,     MO(1)
    ),
    [_NAV] = LAYOUT(
        KC_ESC,                                                                       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       MS_UP,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,   KC_NO,
        KC_NO,       MS_LEFT,     MS_DOWN,     MS_RGHT,     KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       KC_NO,                    KC_NO,       KC_NO,                    KC_NO,       KC_NO,       KC_NO
    ),
    [_PUN] = LAYOUT(
        KC_ESC,                                                                       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       MS_UP,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,   KC_NO,
        KC_NO,       MS_LEFT,     MS_DOWN,     MS_RGHT,     KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       KC_NO,                    KC_NO,       KC_NO,                    KC_NO,       KC_NO,       KC_NO
    ),
    [_NUM] = LAYOUT(
        KC_ESC,                                                                       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       MS_UP,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,   KC_NO,
        KC_NO,       MS_LEFT,     MS_DOWN,     MS_RGHT,     KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       KC_NO,                    KC_NO,       KC_NO,                    KC_NO,       KC_NO,       KC_NO
    ),
    [_FUN] = LAYOUT(
        KC_ESC,                                                                       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       MS_UP,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,   KC_NO,
        KC_NO,       MS_LEFT,     MS_DOWN,     MS_RGHT,     KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       KC_NO,                    KC_NO,       KC_NO,                    KC_NO,       KC_NO,       KC_NO
    ),
    [_MOUSE] = LAYOUT(
        KC_ESC,                                                                       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       MS_UP,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,   KC_NO,
        KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,       KC_NO,       KC_NO,                    KC_NO,       KC_NO,                    KC_NO,       KC_NO,       KC_NO
    ),
};


#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [_BASE]  =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
        [_NAV]   =  { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) },
        [_PUN]   =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
        [_NUM]   =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
        [_FUN]   =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
        [_MOUSE] =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) }
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
