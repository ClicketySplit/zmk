# Clickety Split | Leeloo-Micro

- **Designed by:** [Clickety Split](https://clicketysplit.ca)
- **Website:** [clicketysplit.ca](https://clicketysplit.ca)
- **GitHub:** [ClicketySplit](https://github.com/ClicketySplit)

## Overview

Leeloo-Micro is a compact split ergonomic keyboard family designed by
Clickety Split. The current ZMK shield definitions support the original
Leeloo-Micro v1.0 hardware and Leeloo-Micro v1.1.

The source tree keeps revision-specific shield targets separate and provides
controller-specific display and RGB routing for Leeloo-Micro v1.1 / Rev2.
This preserves established Rev1 behavior while allowing Rev2 to support its
Sharp displays and switched RGB power rail correctly with either nice!nano v2
or Clickety Split Chiisai.

## Features

- Split central and peripheral operation
- Separate left and right shield targets
- Support for Leeloo-Micro v1.0 / Rev1 and v1.1 / Rev2
- OLED / SSD1306 support in the shared and Rev1 configuration
- Dual Sharp LS011B7DH03 160 × 68 Memory LCD support for Rev2
- RGB underglow support
- Controller-specific Rev2 RGB power handling
- nice!nano v2 and Clickety Split Chiisai Rev2 integrations
- User-configurable ZMK keymaps
- USB and Bluetooth Low Energy operation through the installed controller
- UF2 firmware output when supported by the selected controller board

## Hardware Revisions and ZMK Targets

| Hardware    | Metadata Name     | Left Target                             | Right Target                             | Current Documentation Boundary                         |
| ----------- | ----------------- | --------------------------------------- | ---------------------------------------- | ------------------------------------------------------ |
| v1.0 / Rev1 | Leeloo-Micro      | `clickety_split_leeloo_micro_left`      | `clickety_split_leeloo_micro_right`      | Shared legacy configuration retained                   |
| v1.1 / Rev2 | Leeloo-Micro v1.1 | `clickety_split_leeloo_micro_rev2_left` | `clickety_split_leeloo_micro_rev2_right` | Controller-specific Sharp display and RGB integrations |

The Rev1 targets remain available in the ZMK 4.1 source tree. This README does
not claim renewed physical validation for Rev1 unless the exact keyboard,
controller, and tested functions are identified.

Rev2 is the primary controller-specific integration in the current migration
workstream.

## Controller Support

### nice!nano v2

Leeloo-Micro Rev2 supports nice!nano v2 through controller-specific
configuration and overlay files for both halves.

The Rev2 compatibility configuration separates display power from the RGB
underglow rail:

- nice!nano P0.13 keeps controller VCC and display power available;
- nice!nano P1.01 controls the active-low RGB MOSFET gate;
- nice!nano P0.06 carries WS2812 data; and
- ZMK `EXT_POWER` controls the RGB MOSFET route.

This configuration has been physically validated, including dual-display
operation, RGB underglow, and RGB settings persistence across power cycles.

The compatibility implementation remains temporary until a suitable upstream
ZMK power-domain mechanism can replace it.

### Clickety Split Chiisai

Leeloo-Micro Rev2 also includes controller-specific display and RGB definitions
for Clickety Split Chiisai.

The current Chiisai routing uses:

- P0.06 to keep the Chiisai TPS79333-EP regulator and controller VCC active;
- rear P0.08 as the active-low RGB MOSFET control through the required bodge
  connection;
- P1.09 / D1 / TX0 for WS2812 data;
- P1.12 / D2 for Sharp display MOSI;
- P1.13 / D3 for Sharp display SCK; and
- P1.14 / D4 for active-high Sharp display chip select.

P1.01 / D18 must not be treated as the Chiisai RGB MOSFET route.

The Leeloo-Micro Rev2 Chiisai integration has been physically validated for
keyboard input, split communication, both Sharp displays, correctly resolved
status information, and RGB underglow.

### Shared and Legacy Controller Paths

Rev1 and the shared shield files retain the established Pro Micro-compatible
controller structure used by the original Leeloo-Micro implementation.

Pro Micro-compatible connector placement does not guarantee that display, RGB,
or power-control routing is interchangeable between controllers. Use the
controller-specific Rev2 files provided for the installed controller.

## Display Support

### OLED / SSD1306

The shared and Rev1 Leeloo-Micro definitions retain OLED / SSD1306 support for
the original hardware configuration.

The presence of inherited OLED definitions does not mean that the
controller-specific Rev2 integrations use OLED displays. The Rev2 controller
files disable the inherited OLED node and provide the appropriate Sharp
display route.

### Sharp Memory LCD

Leeloo-Micro Rev2 uses two Sharp LS011B7DH03 160 × 68 Memory LCD displays.

The nice!nano v2 and Chiisai integrations each provide the display routing
required by their controller. The Chiisai route uses P1.12 for MOSI, P1.13 for
SCK, and P1.14 for active-high chip select.

The controller-specific Rev2 display definitions are self-contained. Do not
add the supplemental `nice_view` or `nice_view_adapter` shields to these
builds.

Physical validation confirmed both Sharp displays with:

- Leeloo-Micro v1.1 / Rev2 and nice!nano v2; and
- Leeloo-Micro v1.1 / Rev2 and Clickety Split Chiisai.

## RGB and Power Control

The controller-specific Rev2 configurations enable
`CONFIG_ZMK_RGB_UNDERGLOW` and `CONFIG_ZMK_RGB_UNDERGLOW_EXT_POWER` for both
halves. They set `CONFIG_ZMK_RGB_UNDERGLOW_ON_START=n`, keeping RGB off during
startup, and use conservative brightness defaults for the validated hardware.

The controller-specific files provide the correct WS2812 data and active-low
MOSFET routes. With the assigned `EXT_POWER` configuration enabled, ZMK
`RGB_ON`, `RGB_OFF`, and `RGB_TOG` switch the active-low RGB MOSFET while
leaving the display supply available. Do not copy those routes between
controllers.

### Rev1

The original Leeloo-Micro revision retains its established RGB and
external-power configuration. The Rev2 MOSFET compatibility configuration must
not be applied automatically to Rev1.

### Rev2 with nice!nano v2

Leeloo-Micro Rev2 uses an active-low MOSFET to switch the RGB underglow supply
while leaving the display supply available.

The ZMK 4.1 compatibility configuration redirects ZMK `EXT_POWER` from the
normal nice!nano VCC-control route to the MOSFET gate on P1.01. P0.13 remains
asserted for controller VCC and display power. WS2812 data uses P0.06.

Physical testing confirmed:

- keyboard operation;
- split communication;
- both Sharp displays;
- RGB underglow operation;
- RGB settings persistence across power cycles; and
- normal startup and use during the completed functional checkpoint.

### Rev2 with Chiisai

The Chiisai integration keeps P0.06 asserted for the onboard regulator and VCC,
redirects ZMK `EXT_POWER` to rear P0.08 for the active-low RGB MOSFET, and uses
P1.09 for WS2812 data.

A physical bodge connection to rear P0.08 is required for this RGB control
route.

Physical testing confirmed:

- keyboard input;
- split communication;
- both Sharp displays;
- correctly resolved display status information;
- RGB underglow operation; and
- operation with the maintained ZMK 4.1 integration.

## Building Firmware

Build the selected controller board with the shield target for the required
Leeloo-Micro revision and half.

### Leeloo-Micro Rev2 with nice!nano v2

Left half:

```bash
west build -p -d build/leeloo_micro_rev2_left \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_rev2_left
```

Right half:

```bash
west build -p -d build/leeloo_micro_rev2_right \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_rev2_right
```

### Leeloo-Micro Rev2 with Chiisai

Left half:

```bash
west build -p -d build/leeloo_micro_rev2_chiisai_left \
  -b clickety_split_chiisai/nrf52840/zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_rev2_left
```

Right half:

```bash
west build -p -d build/leeloo_micro_rev2_chiisai_right \
  -b clickety_split_chiisai/nrf52840/zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_rev2_right
```

The resulting UF2 file is normally located at:

```text
build/<name>/zephyr/zmk.uf2
```

Build and flash both halves of the split keyboard.

For Rev1, substitute the applicable left or right target from the
hardware-revision table.

## Flashing Firmware

1. Build firmware for the selected revision, controller, and half.
2. Put the controller into its UF2 bootloader.
3. Mount the bootloader storage volume.
4. Copy the corresponding `zmk.uf2` file to the mounted volume.
5. Allow the controller to restart.
6. Repeat the process for the other half.

The exact reset sequence depends on the installed controller and keyboard
hardware. A double reset is commonly used by UF2-capable nRF52840
controllers.

When moving between materially different shield, controller, or settings
configurations, flash an appropriate ZMK settings-reset build before returning
to the normal firmware.

## Keymap Resolution

The maintained default keymap files are:

- `clickety_split_leeloo_micro_left.keymap` and
  `clickety_split_leeloo_micro_right.keymap` for Rev1; both side-specific
  wrappers include `clickety_split_leeloo_micro_rev1_keymap.dtsi`; and
- `clickety_split_leeloo_micro_rev2.keymap` for Rev2.

There is no root `clickety_split_leeloo_micro.keymap` file. Rev1 intentionally
uses the side-specific wrappers so both halves share the maintained Rev1
keymap definition.

A user configuration can provide a keymap matching the selected shield target.
That user keymap is the intended place for layout customization. The
controller-specific files in this shield change electrical routing and
hardware configuration; they do not define a personal typing layout.

When diagnosing an unexpected layout, verify:

- the selected shield target;
- the keymap file name in the user configuration;
- the left and right build entries; and
- whether a settings reset is required after a major configuration change.

## Validation Status

### Build-Validated

The current ZMK 4.1 source tree contains the four revision-specific left and
right Leeloo-Micro shield targets.

The migration work build-validates the Rev2 controller-specific configurations
for:

- nice!nano v2;
- Clickety Split Chiisai;
- dual Sharp Memory LCD routing;
- RGB underglow routing; and
- ZMK `EXT_POWER` integration.

### Generated-Output Validated

Generated Kconfig and Devicetree output were inspected for the Rev2
controller-specific combinations.

The inspection covered:

- shield and controller selection;
- split-half configuration;
- inherited OLED-node replacement;
- Sharp display routing;
- WS2812 data routing;
- active-low RGB MOSFET control;
- controller VCC behavior;
- ZMK `EXT_POWER` assignment; and
- controller-specific GPIO separation.

### Physically Validated

#### Rev2 with nice!nano v2

Leeloo-Micro v1.1 / Rev2 with nice!nano v2 was physically validated for:

- keyboard operation;
- split communication;
- both Sharp displays;
- RGB underglow operation;
- RGB settings persistence across power cycles; and
- normal startup and use during the completed functional checkpoint.

#### Rev2 with Clickety Split Chiisai

Leeloo-Micro v1.1 / Rev2 with Chiisai was physically validated for:

- keyboard input;
- split communication;
- both Sharp LS011B7DH03 160 × 68 Memory LCD displays;
- correctly resolved display status information;
- RGB underglow operation; and
- operation with the maintained ZMK 4.1 integration.

Physical validation applies only to the stated revision, controller, and
tested functions.

### Longer-Term Validation

The following remain useful follow-up checks:

- formal battery-endurance measurement;
- repeated long-duration sleep and wake cycling;
- extended Bluetooth reconnect testing under varied host conditions; and
- longer-term reliability testing across both validated controller
  combinations.

These follow-up items do not invalidate the completed functional checkpoints.

## Compatibility and Limitations

- Use the shield target matching the physical Leeloo-Micro revision.
- Do not apply the Rev2 MOSFET compatibility configuration to Rev1.
- Rev2 display and RGB routing depends on the installed controller.
- Do not add `nice_view` or `nice_view_adapter` to the controller-specific
  Rev2 builds.
- nice!nano v2 Rev2 uses P0.13 for controller VCC, P1.01 for the active-low
  MOSFET gate, and P0.06 for WS2812 data.
- Chiisai Rev2 uses P0.06 for regulator and VCC behavior, rear P0.08 for the
  active-low MOSFET gate, and P1.09 for WS2812 data.
- Chiisai Rev2 RGB control requires a physical bodge connection to rear P0.08.
- P1.01 / D18 is not the Chiisai MOSFET route.
- The Rev2 ZMK `EXT_POWER` handling remains a temporary compatibility solution
  until appropriate upstream power-domain support is available.
- Physical validation of one revision and controller does not automatically
  validate other combinations.
- Rev1 remains supported in source but is outside the current Rev2 physical
  validation claims.

## Migration Notes

The ZMK 4.1 migration preserves established Leeloo-Micro hardware behavior
while moving the shields to consistently prefixed public names.

Intentional decisions include:

- retaining separate Rev1 and Rev2 targets;
- keeping shared matrix behavior separate from controller-specific routing;
- retaining Rev1 OLED support;
- replacing the inherited OLED node with explicit Sharp Memory LCD routes for
  Rev2 controllers;
- keeping the display supply available while independently switching Rev2 RGB;
- limiting the temporary MOSFET compatibility configuration to Rev2;
- preserving ZMK settings behavior and RGB persistence;
- keeping Chiisai-specific routing inside the Leeloo-Micro shield; and
- distinguishing build, generated-output, and physical validation.

The temporary Rev2 compatibility implementation is documented in the README,
controller-specific configuration files, and Devicetree overlays so that its
purpose and replacement boundary remain clear.

## Support

For questions about this hardware, please
[contact Clickety Split](https://clicketysplit.ca/pages/contact-us).

**Clickety Split** — For the love of split keyboards.

<!-- BEGIN CLICKETY SPLIT PM-AWARE VCC RAIL -->
## PM-aware display and RGB power

Leeloo-Micro v1.1/rev2 uses controller-specific power routing for its direct
Sharp LS011B7DH03 nice!view displays and RGB underglow.

| Controller | Display/VCC rail | RGB gate | WS2812 data | LEDs |
| --- | --- | --- | --- | ---: |
| Clickety Split Chiisai | P0.06, active high | P0.08, active low | P1.09 / TX0 | 20 per half |
| nice!nano v2 | P0.13, active high | P1.01, active low | P0.06 | 20 per half |

The shield-owned `zmk,pm-gpio-rail` device keeps the display/VCC rail enabled
during active use and ordinary idle, then turns it off during ZMK deep sleep.
RGB power remains independently controlled through ZMK `EXT_POWER`.

```conf
CONFIG_ZMK_SLEEP=y
CONFIG_ZMK_IDLE_SLEEP_TIMEOUT=1800000
```

ZMK derives `CONFIG_ZMK_PM_DEVICE_SUSPEND_RESUME`; do not assign that hidden
symbol directly. The direct display integration is owned by the keyboard
shield, so do not add the `nice_view` or `nice_view_adapter` shield.

### Validation status

| Controller | Generated build | Two-minute physical test | 30-minute production test |
| --- | --- | --- | --- |
| Clickety Split Chiisai | Passed | Passed | Passed |
| nice!nano v2 | Passed | Passed | Not separately recorded |

On tested hardware, wake restored both displays and RGB enabled/disabled state,
colour, brightness, and saturation.
<!-- END CLICKETY SPLIT PM-AWARE VCC RAIL -->
