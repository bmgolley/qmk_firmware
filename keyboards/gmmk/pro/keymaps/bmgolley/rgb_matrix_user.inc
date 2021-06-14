RGB_MATRIX_EFFECT(SIDES_ONLY)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool SIDES_ONLY(effect_params_t* params) {
	RGB_MATRIX_USE_LIMITS(led_min, led_max);
	
	RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(i, RGB_OFF);
        }
    }
	return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS