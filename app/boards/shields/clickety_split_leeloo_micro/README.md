# Clickety Split | Leeloo-Micro

![Leeloo-Micro v1 Wireless](https://github.com/ClicketySplit/build-guides/blob/main/leeloo/images/gallery/Leeloo-Micro-v1-ZMK.jpg)

Keyboard Designer: [clicketysplit.ca](https://clicketysplit.ca)
GitHub: [ClicketySplit](https://github.com/ClicketySplit)
Primary Controller: nice!nano v2

Leeloo-Micro is a compact 3×5+5 split keyboard derived from Leeloo.
It retains the Leeloo column stagger and modifier row while removing the
top row and outer columns.

The shield family supports two Leeloo-Micro hardware revisions.

## Features

- Compact 3×5+5 split layout.
- Kailh Low Profile Choc switches with 18 mm × 18 mm spacing.
- Socketed switch positions.
- Support for one Alps Alpine EC11 rotary encoder on each half.
- Socketed rotary-encoder positions.
- Socketed display support.
- Per-switch RGB lighting.
- Support for 110 mAh and 700 mAh batteries.
- Alps Alpine micro on/off switches.

# Hardware Revisions and ZMK Targets

| Hardware | Left target | Right target | Default keymap |
|---|---|---|---|
| Leeloo-Micro v1.0 / rev1 | `clickety_split_leeloo_micro_left` | `clickety_split_leeloo_micro_right` | `clickety_split_leeloo_micro_rev1_keymap.dtsi` |
| Leeloo-Micro v1.1 / rev2 | `clickety_split_leeloo_micro_rev2_left` | `clickety_split_leeloo_micro_rev2_right` | `clickety_split_leeloo_micro_rev2.keymap` |

The original public target names represent Leeloo-Micro v1.0 and do not
contain `rev1`. The explicit `rev2` targets represent Leeloo-Micro v1.1.

No unprefixed compatibility aliases are provided. All public targets use
the `clickety_split_` namespace.

# Building Leeloo-Micro Firmware

The examples below assume they are run from the root of a ZMK workspace
and use the ZMK 4.1 nice!nano board target:

```text
nice_nano//zmk
```

Useful ZMK references:

- [Introduction to ZMK](https://zmk.dev/docs/)
- [Installing ZMK](https://zmk.dev/docs/user-setup)
- [Customizing ZMK](https://zmk.dev/docs/customization)
- [Development setup](https://zmk.dev/docs/development/setup)

## Leeloo-Micro v1.0 / rev1

```bash
west build -p always -s app \
  -d build/clickety_split_leeloo_micro_left \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_left

west build -p always -s app \
  -d build/clickety_split_leeloo_micro_right \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_right
```

## Leeloo-Micro v1.1 / rev2

The rev2 targets automatically include their RGB power handling and
direct Sharp Memory LCD configuration.

Do not add `nice_view_adapter` or `nice_view` to the rev2 build commands.

```bash
west build -p always -s app \
  -d build/clickety_split_leeloo_micro_rev2_left \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_rev2_left

west build -p always -s app \
  -d build/clickety_split_leeloo_micro_rev2_right \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_rev2_right
```

## Custom ZMK Configuration

Replace `/absolute/path/to/zmk-config/config` with the directory
containing the custom keymap and configuration files.

### Rev1 example

```bash
west build -p always -s app \
  -d build/clickety_split_leeloo_micro_left_custom \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_left \
  -DZMK_CONFIG="/absolute/path/to/zmk-config/config"
```

### Rev2 example

```bash
west build -p always -s app \
  -d build/clickety_split_leeloo_micro_rev2_left_custom \
  -b nice_nano//zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_rev2_left \
  -DZMK_CONFIG="/absolute/path/to/zmk-config/config"
```

A custom rev2 configuration should not add the generic nice!view
adapter shields. The rev2 controller-specific overlay already defines
the display hardware.

# Display Support

## Leeloo-Micro v1.0 / rev1

Rev1 retains the generic ZMK `nice_view_adapter` and `nice_view`
workflow.

The default rev1 keymap source contains a commented display chip-select
override:

```text
clickety_split_leeloo_micro_rev1_keymap.dtsi
```

The override is:

```dts
nice_view_spi: &spi0 {
    cs-gpios = <&pro_micro 4 GPIO_ACTIVE_HIGH>;
};
```

For a custom configuration, place this override in the custom keymap.

A rev1 build using the generic adapter shields resembles:

```bash
west build -p always -s app \
  -d build/clickety_split_leeloo_micro_left_display \
  -b nice_nano//zmk -- \
  -DSHIELD="clickety_split_leeloo_micro_left nice_view_adapter nice_view"
```

The equivalent right-half build uses
`clickety_split_leeloo_micro_right`.

## Leeloo-Micro v1.1 / rev2

Rev2 directly defines the Sharp Memory LCD used by the nice!view
display. The display configuration is owned by the Leeloo-Micro shield
and does not depend on the generic adapter shields.

The rev2 nice!nano v2 configuration:

- enables SPI0;
- uses P0.20 for SCK;
- uses P0.17 for MOSI;
- uses Pro Micro physical pin 4 for display chip select;
- configures chip select as active-high;
- disables the inherited SSD1306 OLED node;
- disables the inherited Pro Micro I2C bus;
- enables the Zephyr `sharp,ls0xx` driver;
- configures a 160 × 68 monochrome display;
- performs VCOM inversion through the serial protocol;
- uses the built-in ZMK status screen;
- blanks the display contents while idle;
- keeps the display supply enabled independently of RGB power.

The direct display definition is included only for these combinations:

```text
clickety_split_leeloo_micro_rev2_left + nice!nano v2
clickety_split_leeloo_micro_rev2_right + nice!nano v2
```

Rev1 and unrelated shields are unaffected.

# Leeloo-Micro Rev2 RGB Power Control

## Hardware Arrangement

Leeloo-Micro rev2 separates the always-available display supply from the
switchable RGB LED supply.

```text
nice!nano P0.13
    -> controller VCC output
    -> display supply
    -> RGB MOSFET source

nice!nano P1.01
    -> active-low RGB MOSFET gate
    -> controlled through ZMK EXT_POWER

nice!nano P0.06
    -> WS2812 data
```

Each keyboard half contains a chain of 20 GRB LEDs.

P0.13 is configured as an output-high GPIO hog. It remains asserted so
the display supply remains available during normal operation.

ZMK's generic external-power device is redirected to P1.01:

```text
RGB enabled
    -> P1.01 low
    -> MOSFET enabled
    -> RGB rail powered

RGB disabled
    -> P1.01 high
    -> MOSFET disabled
    -> RGB rail unpowered
```

This allows `RGB_ON`, `RGB_OFF`, and `RGB_TOG` to control the RGB rail
without switching off the display supply.

## ZMK Configuration

The rev2 nice!nano v2 controller configuration enables:

```conf
CONFIG_ZMK_RGB_UNDERGLOW=y
CONFIG_ZMK_RGB_UNDERGLOW_EXT_POWER=y
CONFIG_ZMK_RGB_UNDERGLOW_ON_START=n

CONFIG_ZMK_RGB_UNDERGLOW_BRT_MAX=10
CONFIG_ZMK_RGB_UNDERGLOW_BRT_START=10
```

RGB is configured to begin disabled when using fresh/default settings.

The maximum and initial brightness are deliberately restricted to 10
during initial hardware validation. These values may be revisited after
electrical, thermal, battery, and visual testing.

The default rev2 keymap defines controls for:

- RGB on;
- RGB off;
- RGB toggle;
- effect selection;
- hue adjustment;
- saturation adjustment;
- brightness adjustment.

Refer to `clickety_split_leeloo_micro_rev2.keymap` for the exact default
positions.

# Compatibility Status

The rev2 RGB implementation uses ZMK's generic EXT_POWER support as a
temporary compatibility mechanism for the active-low RGB MOSFET.

It does not restore or reproduce the earlier ZMK power-domain subsystem.
No custom application driver is required.

The implementation is intentionally isolated to the Leeloo-Micro rev2
nice!nano v2 controller-specific files. It does not alter:

- Leeloo-Micro rev1;
- unrelated Clickety Split shields;
- other controller boards;
- the underlying Sharp display driver;
- ZMK's generic display subsystem.

A future upstream power-domain or power-sequencing solution may replace
this compatibility arrangement while retaining the same hardware
behaviour.

# Validation Status

## Build-validated

The following have been confirmed through clean ZMK 4.1 builds and
generated configuration inspection:

- all four Leeloo-Micro targets build successfully;
- rev1 left and right retain their original firmware output;
- rev1 and rev2 resolve to their intended default keymaps;
- rev2 enables the Sharp display driver;
- rev2 uses SPI0 P0.20/P0.17 and Pro Micro pin 4;
- the inherited OLED node and I2C bus are disabled for rev2 nice!nano v2;
- P0.13 is generated as an output-high GPIO hog;
- EXT_POWER is generated on active-low P1.01;
- P0.06 is generated as the WS2812 SPI output;
- each rev2 half is generated with a 20-LED GRB chain;
- the RGB and display topologies coexist in the generated Devicetree.

## Physical validation still required

The following must be confirmed on Leeloo-Micro rev2 hardware:

- left and right keyboard matrices;
- rotary-encoder direction and resolution;
- wired USB HID;
- Bluetooth HID;
- split central/peripheral communication;
- reconnect and bonding behaviour;
- direct Sharp display operation;
- display content orientation;
- layer and Bluetooth status display;
- display blanking and wake behaviour;
- RGB on, off, and toggle controls;
- effect, colour, saturation, and brightness controls;
- display operation while RGB power is disabled;
- RGB settings persistence;
- complete power-down and cold-start recovery;
- absence of a visible RGB startup flash;
- battery consumption with RGB enabled and disabled.

The configuration requests that RGB begin disabled. This expected boot
behaviour must still be confirmed after a ZMK settings reset and repeated
cold starts.

An oscilloscope or logic analyser would be required to prove the absence
of an extremely short electrical transition that is not visibly
observable.

# Keymap Resolution

The shield directory intentionally does not contain a generic:

```text
clickety_split_leeloo_micro.keymap
```

A generic folder-level keymap would be selected before the
revision-specific rev2 keymap and would shadow it.

The default keymaps are organized as follows:

```text
clickety_split_leeloo_micro_left.keymap
    -> includes clickety_split_leeloo_micro_rev1_keymap.dtsi

clickety_split_leeloo_micro_right.keymap
    -> includes clickety_split_leeloo_micro_rev1_keymap.dtsi

clickety_split_leeloo_micro_rev2_left
    -> uses clickety_split_leeloo_micro_rev2.keymap

clickety_split_leeloo_micro_rev2_right
    -> uses clickety_split_leeloo_micro_rev2.keymap
```

This allows each hardware revision to receive its intended layout while
both halves share the appropriate revision-level keymap source.

# Support

For questions about Leeloo-Micro, please
[contact Clickety Split](https://clicketysplit.ca/pages/contact-us).

Clickety Split
For the love of split keyboards.
