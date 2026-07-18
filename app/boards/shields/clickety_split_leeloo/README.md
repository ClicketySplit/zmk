# Clickety Split | Leeloo

![Leeloo v2](https://github.com/ClicketySplit/build-guides/blob/main/leeloo/images/gallery/Leeloo-v2-ZMK.jpg)

Keyboard Designer: [clicketysplit.ca](https://clicketysplit.ca)<br>
GitHub: [ClicketySplit](https://github.com/ClicketySplit)<br>
Hardware Supported: Pro Micro, Elite-C, and nice!nano v2

Leeloo is a 4×6+5 split keyboard with a column-staggered, low-profile
layout. Depending on the revision, it supports Choc or MX-compatible
switches, rotary encoders, displays, batteries, and per-key RGB lighting.

This shield family contains support for three Leeloo hardware revisions.

## Hardware Revisions and ZMK Targets

| Hardware revision | Left target | Right target | Default keymap |
|---|---|---|---|
| Leeloo v1 | `clickety_split_leeloo_left` | `clickety_split_leeloo_right` | `clickety_split_leeloo_rev1_keymap.dtsi` |
| Leeloo v2 | `clickety_split_leeloo_rev2_left` | `clickety_split_leeloo_rev2_right` | `clickety_split_leeloo_rev2.keymap` |
| Leeloo v2.1 / rev3 | `clickety_split_leeloo_rev3_left` | `clickety_split_leeloo_rev3_right` | `clickety_split_leeloo_rev3.keymap` |

The ZMK target names use firmware revision identifiers where necessary.
Leeloo v2.1 is represented by the `rev3` targets.

## Leeloo v2 and v2.1

Leeloo v2 was redesigned from the wiring schematic through to the case.
It retains the column stagger and low-profile design associated with
Leeloo while adding socketed components and expanded display, battery,
and lighting support.

### Features

- Support for Kailh Low Profile Choc switches with 18 mm × 18 mm spacing.
  - A Kailh Box/MX version with 19.05 mm × 19.05 mm spacing may be
    supported separately.
- Socketed switch locations.
- Socketed rotary-encoder locations.
  - One of two locations on each side may be used for a rotary encoder.
- Native support for OLED and nice!view displays.
- Support for per-switch RGB lighting.
- Support for 110 mAh and 700 mAh batteries.
- Dedicated battery-lead soldering locations.
- Support for Alps Alpine micro on/off switches.

### Leeloo v2.1 / rev3 Changes

The rev3 ZMK target adds controller-specific support for the nice!nano v2:

- Direct Sharp Memory LCD support without the `nice_view_adapter` shield.
- Independent display and RGB power control.
- MOSFET-controlled RGB power.
- RGB settings persistence across resets and complete power removal.
- Revision-specific default keymap selection.

The rev3 firmware implementation is isolated to the rev3 nice!nano v2
targets. It does not alter the controller configuration for Leeloo v1,
Leeloo v2, or other controller boards.

# Leeloo v1

![Leeloo](https://github.com/ClicketySplit/build-guides/blob/main/leeloo/images/gallery/Leeloo-v1.jpg)

## Features

- 4×6+5 split-keyboard layout.
- Support for Low Profile Choc and Box/MX switches using
  19.05 mm × 19.05 mm spacing.
- Approximately 90 percent of switch positions are socketed, excluding
  the rotary-encoder positions.
- Support for Alps Alpine EC11 rotary encoders.
  - One encoder may be installed on each half in one of three locations.
- Support for OLED or nice!view displays.
  - A nice!view display requires a CS connection to P0.22, also identified
    as D4 on the nice!nano.
- Support for 110 mAh and 700 mAh batteries.
- Battery-lead solder pads.
- Support for Alps Alpine micro on/off switches.

# Building Leeloo ZMK Firmware

- ZMK Firmware: [Introduction to ZMK](https://zmk.dev/docs/)
- Installation: [Installing ZMK](https://zmk.dev/docs/user-setup)
- Customization: [Customizing ZMK](https://zmk.dev/docs/customization)
- Development Environment: [Basic Setup](https://zmk.dev/docs/development/setup)

The examples below assume they are run from a ZMK workspace and use the
nice!nano v2 board target:

```text
nice_nano//zmk
```

## Default Leeloo v1 Firmware

```bash
west build -p always -s app -d build/leeloo_rev1_left \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_left

west build -p always -s app -d build/leeloo_rev1_right \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_right
```

## Default Leeloo v2 Firmware

```bash
west build -p always -s app -d build/leeloo_rev2_left \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_rev2_left

west build -p always -s app -d build/leeloo_rev2_right \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_rev2_right
```

## Default Leeloo v2.1 / rev3 Firmware

The rev3 target includes its direct Memory LCD and RGB power-control
configuration automatically. Do not add `nice_view_adapter` or
`nice_view` to these build commands.

```bash
west build -p always -s app -d build/leeloo_rev3_left \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_rev3_left

west build -p always -s app -d build/leeloo_rev3_right \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_rev3_right
```

## Building with a Custom ZMK Configuration

Replace `/absolute/path/to/zmk-config/config` with the path to the
directory containing the custom `.keymap` and `.conf` files.

### Leeloo v1

```bash
west build -p always -s app -d build/leeloo_rev1_left_custom \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_left \
  -DZMK_CONFIG="/absolute/path/to/zmk-config/config"

west build -p always -s app -d build/leeloo_rev1_right_custom \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_right \
  -DZMK_CONFIG="/absolute/path/to/zmk-config/config"
```

### Leeloo v2

```bash
west build -p always -s app -d build/leeloo_rev2_left_custom \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_rev2_left \
  -DZMK_CONFIG="/absolute/path/to/zmk-config/config"

west build -p always -s app -d build/leeloo_rev2_right_custom \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_rev2_right \
  -DZMK_CONFIG="/absolute/path/to/zmk-config/config"
```

### Leeloo v2.1 / rev3

```bash
west build -p always -s app -d build/leeloo_rev3_left_custom \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_rev3_left \
  -DZMK_CONFIG="/absolute/path/to/zmk-config/config"

west build -p always -s app -d build/leeloo_rev3_right_custom \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_rev3_right \
  -DZMK_CONFIG="/absolute/path/to/zmk-config/config"
```

# Display Support

## Leeloo v1 and v2 nice!view Displays

Leeloo v1 and v2 use the ZMK `nice_view_adapter` and `nice_view`
shields.

For the default shield keymaps, the display CS override is located in:

- Leeloo v1:
  `clickety_split_leeloo_rev1_keymap.dtsi`
- Leeloo v2:
  `clickety_split_leeloo_rev2.keymap`

Locate the commented display-CS block:

```dts
// nice_view_spi: &spi0 {
//     cs-gpios = <&pro_micro 4 GPIO_ACTIVE_HIGH>;
// };
```

Remove the comment markers:

```dts
nice_view_spi: &spi0 {
    cs-gpios = <&pro_micro 4 GPIO_ACTIVE_HIGH>;
};
```

For a custom ZMK configuration, place this block in the custom keymap
instead of modifying the shield's default keymap.

### Leeloo v1 with nice!view

```bash
west build -p always -s app -d build/leeloo_rev1_left_display \
  -b nice_nano//zmk -- \
  -DSHIELD="clickety_split_leeloo_left nice_view_adapter nice_view"

west build -p always -s app -d build/leeloo_rev1_right_display \
  -b nice_nano//zmk -- \
  -DSHIELD="clickety_split_leeloo_right nice_view_adapter nice_view"
```

### Leeloo v2 with nice!view

```bash
west build -p always -s app -d build/leeloo_rev2_left_display \
  -b nice_nano//zmk -- \
  -DSHIELD="clickety_split_leeloo_rev2_left nice_view_adapter nice_view"

west build -p always -s app -d build/leeloo_rev2_right_display \
  -b nice_nano//zmk -- \
  -DSHIELD="clickety_split_leeloo_rev2_right nice_view_adapter nice_view"
```

## Leeloo v2.1 / rev3 Direct Memory LCD Support

Leeloo rev3 directly defines the Sharp Memory LCD used by the
nice!view display. The display is part of the Leeloo shield
configuration and does not require the generic `nice_view_adapter` or
`nice_view` shields.

The controller-specific implementation:

- uses SPI0;
- uses P0.20 for SCK;
- uses P0.17 for MOSI;
- uses Pro Micro physical pin 4 for display CS;
- disables the inherited OLED node and Pro Micro I2C bus;
- enables the Zephyr `sharp,ls0xx` display driver;
- configures a 160 × 68 pixel display;
- keeps the display supply enabled independently of RGB power.

The direct display configuration is included only for:

```text
clickety_split_leeloo_rev3_left + nice!nano v2
clickety_split_leeloo_rev3_right + nice!nano v2
```

This prevents the rev3 hardware configuration from affecting Leeloo v1,
Leeloo v2, nice!nano v1, or unrelated controller boards.

# Leeloo rev3 RGB Power Control

## Hardware Design

Leeloo rev3 separates the display supply from the RGB LED supply.

- nice!nano v2 P0.13 enables the controller VCC output.
- VCC powers the display and the source side of the RGB MOSFET.
- P1.01 controls the RGB MOSFET gate.
- The RGB MOSFET is active-low.
- The MOSFET drain supplies power to the RGB LEDs.
- P0.06 carries the WS2812 data signal.
- Each half contains a chain of 29 GRB LEDs.

The display must remain powered while RGB lighting is disabled.
Therefore, P0.13 is configured as an output-high GPIO hog and remains
enabled during normal operation.

P1.01 is assigned to ZMK's generic external-power device and is used to
switch the RGB MOSFET:

```text
RGB ON  -> P1.01 low  -> MOSFET enabled  -> RGB rail powered
RGB OFF -> P1.01 high -> MOSFET disabled -> RGB rail unpowered
```

## ZMK Configuration

The rev3 nice!nano v2 configuration enables:

```conf
CONFIG_ZMK_RGB_UNDERGLOW=y
CONFIG_ZMK_RGB_UNDERGLOW_EXT_POWER=y
CONFIG_ZMK_RGB_UNDERGLOW_ON_START=n
CONFIG_ZMK_RGB_UNDERGLOW_BRT_MAX=10
CONFIG_ZMK_RGB_UNDERGLOW_BRT_START=10
```

The configuration is contained in the controller-specific rev3 board
configuration so that rev1, rev2, and other controllers remain
unaffected.

## Default RGB Controls

The rev3 default keymap provides the following controls on the Raise
layer:

| Key position while Raise is active | Action |
|---|---|
| Caps Lock | RGB on |
| A | RGB toggle |
| Left Shift | RGB off |
| Z | Change RGB effect |
| S / X | Hue up / down |
| D / C | Saturation up / down |
| F / V | Brightness up / down |

The default thumb key used to access Raise is the Minus key.

## Settings Persistence

RGB state is stored through ZMK settings.

Hardware testing has confirmed that the following values are restored
after a complete power-down:

- RGB enabled or disabled state;
- selected colour;
- brightness;
- effect state.

Testing was performed after a ZMK settings reset, followed by repeated
complete power removals and cold starts.

No visible startup flash was observed during repeated cold-boot tests.
The display remained powered and operational while RGB lighting was
switched on and off.

# Compatibility Status and Limitations

The Leeloo rev3 RGB implementation uses ZMK's generic external-power
support as a compatibility mechanism for the active-low RGB MOSFET.

This is intentionally isolated to the Leeloo rev3 nice!nano v2 board
configuration.

The implementation has been validated for:

- left and right keyboard matrices;
- wired USB HID;
- wireless split operation;
- direct Sharp Memory LCD operation;
- Lower and Raise layer status;
- RGB on, toggle, and off controls;
- RGB colour and brightness changes;
- settings restoration;
- complete power-down and cold-start recovery;
- repeated operation without a visible RGB startup flash;
- extended normal keyboard use.

Longer-term use and battery testing remain ongoing.

This compatibility implementation is not a replacement for a dedicated
RGB power-sequencing or power-domain subsystem. A future upstream
solution may replace it while retaining the same hardware behaviour.

An oscilloscope or logic analyser has not been used to prove the
complete absence of a very short electrical transition during startup.
The current validation establishes that no visible LED flash occurs
during normal reset, power-cycle, and cold-start testing.

# Keymap Resolution

The Leeloo shield directory does not contain a generic
`clickety_split_leeloo.keymap`.

A folder-level keymap with that name would be selected before the
revision-specific keymaps and would unintentionally shadow the rev2 and
rev3 layouts.

The default keymaps are therefore organized as follows:

```text
clickety_split_leeloo_left.keymap
  -> includes clickety_split_leeloo_rev1_keymap.dtsi

clickety_split_leeloo_right.keymap
  -> includes clickety_split_leeloo_rev1_keymap.dtsi

clickety_split_leeloo_rev2_left/right
  -> use clickety_split_leeloo_rev2.keymap

clickety_split_leeloo_rev3_left/right
  -> use clickety_split_leeloo_rev3.keymap
```

This structure ensures that each hardware revision receives its intended
default keymap while allowing both halves of a revision to share a
single layout definition.

# Support

For questions about Leeloo, please
[contact Clickety Split](https://clicketysplit.ca/pages/contact-us).

Clickety Split<br>
For the love of split keyboards.