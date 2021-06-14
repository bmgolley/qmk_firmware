/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define RGB_M_S rgb_matrix_mode(RGB_MATRIX_CUSTOM_SIDES_ONLY)

enum layer_names {
        _BASE,
        _HOMETOG,
        _WINLK,
        _SCRLTOG,
        _NUM,
        _FN,
        _RGB,
        _RESET
};

enum custom_keycodes {
    STEAM = KC_F15,
    DISCORD = KC_F16,
    SSE = KC_F17,
    HWM = KC_F18,
};

// Tap Dance declarations
enum {
    D_H,
    P_I,
    NL,
};

bool num_on;

void dance_layer_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (!num_on) {
        if (state->count == 1) {
            layer_on(_FN);
        } else {
            layer_on(_NUM);
            register_mods(MOD_BIT(KC_LALT));
        }
    }
}

void dance_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (!IS_LAYER_ON(_NUM)) {
        layer_off(_FN);
    } else if (num_on) {
        layer_off(_NUM);
        unregister_mods(MOD_BIT(KC_LALT));
        num_on = false;
    } else {
        num_on = true;
    }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Delete, twice for Home toggle
    [D_H] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_HOME),
    // Tap once for Print Screen, twice for Insert
    [P_I] = ACTION_TAP_DANCE_DOUBLE(KC_PSCR, KC_INS),
    [NL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_layer_finished,dance_layer_reset),
    
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(D_H):
            return 160;
            break;
        default:
            return TAPPING_TERM;
            break;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  TD(P_I),          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          TD(D_H),
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, TD(NL),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_HOMETOG] = LAYOUT( //Toggle Del/Home
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    
    [_WINLK] = LAYOUT( //Toggle Win on/off
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, XXXXXXX, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [_SCRLTOG] = LAYOUT( //Toggle Encoder Volume/Scroll
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

/*     [3] = LAYOUT(
        RESET, KC_MYCM, KC_WHOM, KC_CALC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, XXXXXXX, XXXXXXX, KC_NO, KC_PAUS,           KC_NO,
        KC_NO, KC_P1,   KC_P2,   KC_P3,   KC_P4, KC_P5, KC_P6, KC_P7, KC_P8, KC_P9, KC_P0,   XXXXXXX, KC_NO, KC_INS,            TG(1),
        KC_NO, RGB_HUI, RGB_VAI, RGB_SAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, XXXXXXX, XXXXXXX, KC_NO, RGB_TOG,           KC_NO,
        KC_NO, RGB_HUD, RGB_VAD, RGB_SAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, XXXXXXX, XXXXXXX,        XXXXXXX,           KC_NO,
        XXXXXXX,        XXXXXXX, XXXXXXX, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, XXXXXXX, XXXXXXX,        XXXXXXX, RGB_MOD,  KC_NO,
        KC_NO, TG(2),   KC_LALT,                        XXXXXXX,                    KC_RALT, _______, KC_NO, RGB_SPD, RGB_RMOD, RGB_SPI
    ) */
    
    [_NUM] = LAYOUT( //Numpad for unicode. Also sets encoder to Alt-tab through windows
        XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, KC_P1,    KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,
        XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    
    [_FN] = LAYOUT( //Primary Function layer.
        XXXXXXX, KC_MYCM,  KC_WHOM, KC_CALC, XXXXXXX, STEAM,   DISCORD, SSE,     HWM,     KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_PAUS,       TG(_SCRLTOG),
        XXXXXXX, KC_P1,    KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   XXXXXXX, KC_SLCK, KC_INS,        TG(_HOMETOG),
        XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,
        XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(_RGB),         XXXXXXX, KC_MSTP, XXXXXXX,
        _______,TG(_WINLK),KC_LALT,                            MO(_RESET),                         KC_RALT, _______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT
    ),
     
    [_RGB] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX,
        XXXXXXX, RGB_HUI, RGB_VAI, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,           XXXXXXX,
        XXXXXXX, RGB_HUD, RGB_VAD, RGB_SAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,           XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          XXXXXXX, RGB_MOD,  XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            _______,                            XXXXXXX, _______, XXXXXXX, RGB_SPD, RGB_RMOD, RGB_SPI
    ),
     
    [_RESET] = LAYOUT( //Reset
        EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,   NK_ON,   NK_OFF,  NK_TOGG, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            _______,                            XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        if (IS_LAYER_ON(_NUM)) {
            tap_code(KC_TAB);
        } else if (IS_LAYER_ON(_SCRLTOG)) {
            tap_code(KC_MS_WH_DOWN);
        } else { 
            tap_code(KC_VOLU);
        }
    } else {
        if (IS_LAYER_ON(_NUM)) {
            register_mods(MOD_BIT(KC_LSFT));
            tap_code(KC_TAB);
            unregister_mods(MOD_BIT(KC_LSFT));
        } else if (IS_LAYER_ON(_SCRLTOG)) {
            tap_code(KC_MS_WH_UP);
        } else { 
            tap_code(KC_VOLD);
        }
    };
    return true;
}

void rgb_matrix_indicators_user(void) {
    uint8_t this_led = host_keyboard_leds();
    if (this_led & (1<<USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(15, RGB_RED);
    }
}

void keyboard_post_init_user(void) {
    //Setup initial RGB stuff here
    rgb_matrix_set_color_all(RGB_PURPLE);
    RGB_M_S;
}

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}