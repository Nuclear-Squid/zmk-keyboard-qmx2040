#define DT_DRV_COMPAT zmk_behavior_numpad

#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <drivers/behavior.h>
#include <dt-bindings/zmk/modifiers.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/hid.h>
#include <zmk/hid_indicators.h>
#include <dt-bindings/zmk/keys.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/behavior.h>

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int on_numpad_binding_pressed(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    struct zmk_behavior_binding kp_binding = {
        .behavior_dev = "key_press",
        .param1 = KP_NUM,
    };

    if (!zmk_hid_indicators_get_current_profile() & 1) {
        zmk_behavior_invoke_binding(&kp_binding, event, true);
        zmk_behavior_invoke_binding(&kp_binding, event, false);
    }

    kp_binding.param1 = binding->param1;
    zmk_behavior_invoke_binding(&kp_binding, event, true);
    return ZMK_BEHAVIOR_OPAQUE;
}


static int on_numpad_binding_released(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    struct zmk_behavior_binding kp_binding = {
        .behavior_dev = "key_press",
        .param1 = binding->param1,
    };

    zmk_behavior_invoke_binding(&kp_binding, event, false);
    return ZMK_BEHAVIOR_OPAQUE;
}


static const struct behavior_driver_api numpad_driver_api = {
    .binding_pressed  = on_numpad_binding_pressed,
    .binding_released = on_numpad_binding_released,
};


#define NUMPAD_INST(n)                                                        \
    BEHAVIOR_DT_INST_DEFINE(                                                  \
        n,     /* Instance Number (Automatically populated by macro) */       \
        NULL,  /* Initialization Function */                                  \
        NULL,  /* Power Management Device Pointer */                          \
        NULL,  /* Behavior Data Pointer */                                    \
        NULL,  /* Behavior Configuration Pointer */                           \
        POST_KERNEL,  /* Initialization Level */                              \
        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,  /* Device Priority */           \
        &numpad_driver_api);  // API struct

DT_INST_FOREACH_STATUS_OKAY(NUMPAD_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
