/*
 * Copyright (c) 2026 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_pm_gpio_rail

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/pm/device.h>

struct pm_gpio_rail_config {
    struct gpio_dt_spec enable;
    uint16_t init_delay_ms;
};

static int pm_gpio_rail_enable(const struct device *dev) {
    const struct pm_gpio_rail_config *config = dev->config;
    int ret = gpio_pin_set_dt(&config->enable, 1);

    if (ret < 0) {
        return ret;
    }

    if (config->init_delay_ms > 0) {
        k_msleep(config->init_delay_ms);
    }

    return 0;
}

static int pm_gpio_rail_disable(const struct device *dev) {
    const struct pm_gpio_rail_config *config = dev->config;
    return gpio_pin_set_dt(&config->enable, 0);
}

static int pm_gpio_rail_init(const struct device *dev) {
    const struct pm_gpio_rail_config *config = dev->config;

    if (!gpio_is_ready_dt(&config->enable)) {
        return -ENODEV;
    }

    int ret = gpio_pin_configure_dt(&config->enable, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return ret;
    }

    if (config->init_delay_ms > 0) {
        k_msleep(config->init_delay_ms);
    }

    return 0;
}

#ifdef CONFIG_PM_DEVICE
static int pm_gpio_rail_pm_action(const struct device *dev,
                                  enum pm_device_action action) {
    switch (action) {
    case PM_DEVICE_ACTION_SUSPEND:
        return pm_gpio_rail_disable(dev);
    case PM_DEVICE_ACTION_RESUME:
        return pm_gpio_rail_enable(dev);
    default:
        return -ENOTSUP;
    }
}
#endif

#define PM_GPIO_RAIL_DEFINE(inst)                                              \
    static const struct pm_gpio_rail_config pm_gpio_rail_config_##inst = {     \
        .enable = GPIO_DT_SPEC_INST_GET(inst, enable_gpios),                   \
        .init_delay_ms = DT_INST_PROP_OR(inst, init_delay_ms, 0),              \
    };                                                                          \
    PM_DEVICE_DT_INST_DEFINE(inst, pm_gpio_rail_pm_action);                    \
    DEVICE_DT_INST_DEFINE(inst, pm_gpio_rail_init,                             \
                          PM_DEVICE_DT_INST_GET(inst), NULL,                    \
                          &pm_gpio_rail_config_##inst, POST_KERNEL, 80, NULL);

DT_INST_FOREACH_STATUS_OKAY(PM_GPIO_RAIL_DEFINE)
