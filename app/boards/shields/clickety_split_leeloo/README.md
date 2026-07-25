# Clickety Split | Leeloo

- **Designed by:** [Clickety Split](https://clicketysplit.ca)
- **Website:** [clicketysplit.ca](https://clicketysplit.ca)
- **GitHub:** [ClicketySplit](https://github.com/ClicketySplit)

## Overview

Leeloo is a family of split ergonomic keyboards designed by Clickety Split.
The ZMK shield definitions support the original Leeloo, Leeloo v2, and
Leeloo v2.1 hardware generations.

The current source tree uses revision-specific shield targets and keeps
controller-specific display and RGB routing separate from the shared keyboard
matrix. This allows established hardware revisions to remain supported without
forcing newer power or display behavior onto earlier boards.

## Features

- Split central and peripheral operation
- Separate left and right shield targets
- Support for three Leeloo hardware generations
- OLED / SSD1306 support in the shared and legacy configurations
- Sharp LS011B7DH03 160 × 68 Memory LCD support for Rev3 integrations
- RGB underglow support
- Controller-specific RGB power handling for Leeloo Rev3
- nice!nano v2 and Clickety Split Chiisai Rev3 integrations
- User-configurable ZMK keymaps
- USB and Bluetooth Low Energy operation through the installed controller
- UF2 firmware output when supported by the selected controller board

## Hardware Revisions and ZMK Targets

| Hardware | Metadata Name | Left Target                       | Right Target                       | Current Documentation Boundary                   |
| -------- | ------------- | --------------------------------- | ---------------------------------- | ------------------------------------------------ |
| Rev1     | Leeloo        | `clickety_split_leeloo_left`      | `clickety_split_leeloo_right`      | Shared legacy configuration retained             |
| Rev2     | Leeloo v2     | `clickety_split_leeloo_rev2_left` | `clickety_split_leeloo_rev2_right` | OLED and RGB configuration retained              |
| Rev3     | Leeloo v2.1   | `clickety_split_leeloo_rev3_left` | `clickety_split_leeloo_rev3_right` | Controller-specific display and RGB integrations |

The Rev1 and Rev2 targets remain available in the ZMK 4.1 source tree. This
README does not claim renewed physical validation for those revisions unless
the exact keyboard, controller, and tested functions are identified.

Rev3 is the primary controller-specific integration in the current migration
workstream.

## Controller Support

### nice!nano v2

Leeloo Rev3 supports nice!nano v2 through controller-specific configuration
files for both halves.

The current compatibility configuration separates display power from the RGB
underglow rail:

- nice!nano P0.13 keeps the controller VCC output asserted so the display
  remains powered;
- nice!nano P1.01 controls the active-low RGB MOSFET gate;
- nice!nano P0.06 carries WS2812 data; and
- ZMK `EXT_POWER` controls the RGB MOSFET route.

This is an established and physically validated compatibility configuration,
but it remains temporary until a suitable upstream ZMK power-domain mechanism
can replace it.

### Clickety Split Chiisai

Leeloo Rev3 also includes controller-specific display and RGB definitions for
Chiisai.

The current Chiisai routing uses:

- P0.06 to keep the Chiisai regulator and controller VCC active;
- rear P0.08 as the active-low RGB MOSFET control through the required bodge
  connection;
- P1.09 / D1 / TX0 for WS2812 data;
- P1.12 / D2 for Sharp display MOSI;
- P1.13 / D3 for Sharp display SCK; and
- P1.14 / D4 for active-high Sharp display chip select.

P1.01 / D18 is used by the Leeloo matrix and must not be treated as the
Chiisai RGB MOSFET route.

The Leeloo Rev3 Chiisai integration has passed build and generated-output
validation. Physical validation is not claimed for that exact combination.

### Shared and Legacy Controller Paths

Rev1, Rev2, and the shared shield files retain the established Pro
Micro-compatible controller structure used by the earlier Leeloo
implementations.

Pro Micro-compatible connector placement does not by itself guarantee that
display, RGB, or power-control behavior is interchangeable between controllers.
Use the controller-specific files provided for the selected revision.

## Display Support

### OLED / SSD1306

The shared and legacy Leeloo definitions retain OLED / SSD1306 support where
used by the applicable hardware revision.

The presence of shared OLED definitions does not mean that every
controller-specific Rev3 integration drives an OLED. Controller-specific
display files determine the actual Rev3 display route.

### Sharp Memory LCD

Leeloo Rev3 includes controller-specific support for the Sharp LS011B7DH03
160 × 68 Memory LCD.

The nice!nano v2 and Chiisai integrations each provide the routing required by
their controller. The Chiisai route uses P1.12 for MOSI, P1.13 for SCK, and
P1.14 for active-high chip select.

The controller-specific Rev3 display definitions are self-contained. Do not
add the supplemental `nice_view` or `nice_view_adapter` shields to these
builds.

Physical Leeloo Rev3 display validation currently applies to the nice!nano v2
combination. The Chiisai display route is build- and generated-output
validated but has not yet been physically confirmed on Leeloo Rev3.

## RGB and Power Control

The controller-specific Rev3 configurations enable
`CONFIG_ZMK_RGB_UNDERGLOW` and `CONFIG_ZMK_RGB_UNDERGLOW_EXT_POWER` for both
halves. They keep RGB off at startup and use conservative brightness defaults
for the validated hardware. The controller-specific files then provide the
correct WS2812 data and active-low MOSFET routes; do not copy those routes
between controllers.

### Rev1 and Rev2

The earlier Leeloo revisions retain their existing RGB and external-power
definitions. The Rev3 MOSFET workaround must not be applied automatically to
those revisions.

### Rev3 with nice!nano v2

Leeloo Rev3 uses an active-low MOSFET to switch the RGB underglow supply while
leaving display power available.

The current ZMK 4.1 compatibility configuration redirects ZMK `EXT_POWER` from
the normal nice!nano VCC-control route to the MOSFET gate on P1.01. P0.13
remains asserted for controller VCC and display power. WS2812 data uses P0.06.

Physical testing confirmed:

- RGB underglow operation;
- display operation while using the independent RGB power route;
- settings persistence;
- cold starts;
- no visible RGB startup flash during the observed tests; and
- extended normal use.

The startup statement describes observed behavior. No oscilloscope capture was
performed to prove the absence of every possible ultra-short electrical
transition.

### Rev3 with Chiisai

The Chiisai integration keeps P0.06 assigned to the board regulator and VCC
behavior, redirects ZMK `EXT_POWER` to rear P0.08 for the active-low RGB
MOSFET, and uses P1.09 for WS2812 data.

A physical bodge connection to rear P0.08 is required for this RGB control
route.

This configuration is build- and generated-output validated. Physical Leeloo
Rev3 validation with Chiisai remains pending.

## Building Firmware

Build the selected controller board with the shield target for the required
Leeloo revision and half.

### Leeloo Rev3 with nice!nano v2

Left half:

```bash
west build -p -d build/leeloo_rev3_left \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_rev3_left
```

Right half:

```bash
west build -p -d build/leeloo_rev3_right \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_rev3_right
```

### Leeloo Rev3 with Chiisai

Left half:

```bash
west build -p -d build/leeloo_rev3_chiisai_left \
  -b clickety_split_chiisai/nrf52840/zmk -- \
  -DSHIELD=clickety_split_leeloo_rev3_left
```

Right half:

```bash
west build -p -d build/leeloo_rev3_chiisai_right \
  -b clickety_split_chiisai/nrf52840/zmk -- \
  -DSHIELD=clickety_split_leeloo_rev3_right
```

The resulting UF2 file is normally located at:

```text
build/<name>/zephyr/zmk.uf2
```

Build and flash both halves of the split keyboard.

For Rev1 or Rev2, substitute the applicable left or right shield target from
the hardware-revision table.

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

- `clickety_split_leeloo_left.keymap` and
  `clickety_split_leeloo_right.keymap` for Rev1; both side-specific wrappers
  include `clickety_split_leeloo_rev1_keymap.dtsi`;
- `clickety_split_leeloo_rev2.keymap` for Rev2; and
- `clickety_split_leeloo_rev3.keymap` for Rev3.

There is no root `clickety_split_leeloo.keymap` file. Rev1 intentionally uses
the side-specific wrappers so both halves share the maintained Rev1 keymap
definition.

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

The current ZMK 4.1 source tree contains and builds the six revision-specific
left and right Leeloo shield targets.

The migration work also build-validates the Rev3 controller-specific
configurations for:

- nice!nano v2;
- Clickety Split Chiisai;
- Sharp Memory LCD routing;
- RGB underglow routing; and
- ZMK `EXT_POWER` integration.

### Generated-Output Validated

Generated Kconfig and Devicetree output were inspected for the Rev3
controller-specific combinations.

The inspection covered:

- shield and controller selection;
- split-half configuration;
- display routing;
- WS2812 data routing;
- active-low RGB MOSFET control;
- controller VCC behavior;
- ZMK `EXT_POWER` assignment; and
- controller-specific GPIO separation.

### Physically Validated

Leeloo Rev3 with nice!nano v2 was physically validated for:

- keyboard matrix operation;
- split communication;
- display operation;
- RGB underglow operation;
- ZMK settings persistence;
- cold starts;
- no visible RGB startup flash during observed tests; and
- extended normal use.

Physical validation applies only to the stated revision, controller, and
tested functions.

Leeloo Rev3 with Chiisai is not included in this physical-validation claim.

### Longer-Term Validation

The following remain useful follow-up checks:

- formal battery-endurance measurement;
- repeated long-duration sleep and wake cycling;
- extended Bluetooth reconnect testing under varied host conditions; and
- oscilloscope capture of the Rev3 RGB power rail during startup.

These follow-up items do not invalidate the completed functional checkpoint.

## Compatibility and Limitations

- Use the shield target matching the physical Leeloo revision.
- Do not apply the Rev3 MOSFET compatibility configuration to Rev1 or Rev2.
- Rev3 display and RGB routing depends on the installed controller.
- nice!nano v2 Rev3 uses P0.13 for controller VCC, P1.01 for the active-low
  MOSFET gate, and P0.06 for WS2812 data.
- Chiisai Rev3 uses P0.06 for board regulator and VCC behavior, rear P0.08 for
  the active-low MOSFET gate, and P1.09 for WS2812 data.
- Chiisai Rev3 RGB control requires a physical bodge connection to rear P0.08.
- P1.01 / D18 is part of the Leeloo matrix and is not the Chiisai MOSFET route.
- The Rev3 ZMK `EXT_POWER` handling remains a temporary compatibility solution
  until appropriate upstream power-domain support is available.
- No visible RGB startup flash was observed during physical testing, but the
  result was not verified with an oscilloscope.
- Physical validation of one revision and controller does not automatically
  validate other combinations.

## Migration Notes

The ZMK 4.1 migration preserves established Leeloo hardware behavior while
moving the shields to consistently prefixed public names.

Intentional decisions include:

- retaining separate Rev1, Rev2, and Rev3 targets;
- keeping shared matrix behavior separate from controller-specific routing;
- retaining legacy OLED support where applicable;
- adding explicit Sharp Memory LCD routes for Rev3 controllers;
- keeping the display supply available while independently switching Rev3 RGB;
- limiting the temporary MOSFET compatibility configuration to Rev3;
- preserving ZMK settings behavior; and
- distinguishing compile-time validation from physical hardware validation.

The temporary Rev3 compatibility implementation is documented in the README,
controller-specific configuration files, and Devicetree overlays so that its
purpose and replacement boundary remain clear.

## Support

For questions about this hardware, please
[contact Clickety Split](https://clicketysplit.ca/pages/contact-us).

**Clickety Split** — For the love of split keyboards.

<!-- BEGIN CLICKETY SPLIT PM-AWARE VCC RAIL -->
## PM-aware display and RGB power

Leeloo v2.1/rev3 uses controller-specific power routing for its direct Sharp
LS011B7DH03 nice!view displays and RGB underglow.

| Controller | Display/VCC rail | RGB gate | WS2812 data | LEDs |
| --- | --- | --- | --- | ---: |
| Clickety Split Chiisai | P0.06, active high | P0.08, active low | P1.09 / TX0 | 29 per half |
| nice!nano v2 | P0.13, active high | P1.01, active low | P0.06 | 29 per half |

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
| Clickety Split Chiisai | Passed | Not yet recorded | Not yet recorded |
| nice!nano v2 | Passed | Passed | Passed |

On tested hardware, wake restored both displays and RGB enabled/disabled state,
colour, brightness, and saturation.
<!-- END CLICKETY SPLIT PM-AWARE VCC RAIL -->
