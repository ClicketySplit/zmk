# Clickety Split | Chiisai

- **Designed by:** [Clickety Split](https://clicketysplit.ca)
- **Website:** [clicketysplit.ca](https://clicketysplit.ca)
- **GitHub:** [ClicketySplit](https://github.com/ClicketySplit)

## Overview

Chiisai v1.13 is a Pro Micro-compatible wireless keyboard controller designed
by Clickety Split. It is based on the Nordic Semiconductor nRF52840 and
supports ZMK firmware over USB and Bluetooth Low Energy.

The ZMK 4.1 board definition preserves the proven hardware behavior of the
earlier Chiisai firmware while adopting the current qualified-board structure
used by Zephyr and ZMK.

## Features

- Nordic Semiconductor nRF52840 controller
- Pro Micro-compatible connector layout
- USB and Bluetooth Low Energy keyboard output
- UF2 firmware output
- DC/DC regulator operation
- Persistent ZMK settings storage
- VDDH-based battery-voltage reporting
- UART, I2C, and SPI peripheral routing
- Three additional rear GPIO pads
- Board-controlled external-power output
- Adafruit nRF52 UF2-compatible flash layout

## Board Target

The ZMK-qualified board target is:

```text
clickety_split_chiisai/nrf52840/zmk
```

ZMK metadata and build matrices may represent the same qualified target as:

```text
clickety_split_chiisai//zmk
```

The public board name remains consistently prefixed with
`clickety_split_chiisai`.

## Pro Micro Compatibility

Chiisai exposes the standard 18 Pro Micro GPIO contacts through the board
connector definitions. All 18 connector mappings were compile-validated during
the ZMK 4.1 migration.

The board-owned external-power output uses nRF52840 P0.06. None of the 18
connector GPIO mappings collides with that board power-control signal.

Pro Micro-compatible dimensions and connector placement do not guarantee that
every shield can use every Chiisai feature without a controller-specific
overlay. Shields that use displays, RGB power switching, or unusual peripheral
routing may require explicit Chiisai integration.

## Peripheral Routing

Chiisai provides connector aliases for the established Pro Micro UART, I2C,
and SPI routes. Controller-specific shield definitions can select the required
peripheral and pinctrl configuration.

The following routes are important to current Clickety Split integrations:

| Connector Route  | nRF52840 GPIO | Current Use                                                 |
| ---------------- | ------------- | ----------------------------------------------------------- |
| TX0 / Arduino D1 | P1.09         | UART TX; WS2812 data for Leeloo-family Chiisai integrations |
| Arduino D2       | P1.12         | Sharp Memory LCD MOSI                                       |
| Arduino D3       | P1.13         | Sharp Memory LCD SCK                                        |
| Arduino D4       | P1.14         | Active-high Sharp Memory LCD chip select                    |
| Arduino D18      | P1.01         | Leeloo matrix routing; not the Chiisai RGB MOSFET route     |
| Rear A2 pad      | P0.04         | Additional GPIO with possible analog use                    |
| Rear GPIO pad    | P0.08         | Preferred Leeloo-family RGB MOSFET bodge route              |
| Rear GPIO pad    | P0.12         | Additional GPIO                                             |

The full connector mapping remains defined in
`arduino_pro_micro_pins.dtsi`.

## Power and Battery Reporting

Chiisai uses the nRF52840 DC/DC regulator configuration and the proven RC
low-frequency clock setup from the working hardware implementation.

Battery reporting uses the nRF52840 VDDH measurement path. ZMK settings are
stored persistently in the board flash layout.

The historical board-level `EXT_POWER` node is retained because ZMK external
power settings are associated with the device name. In the generic Chiisai
board configuration:

- P0.06 is an active-high external-power output.
- The output enables the onboard TPS79333-EP regulator and controller VCC.
- External-power initialization uses a 50 ms delay.

A shield may override the GPIO assignment while retaining the historical node
name. The Leeloo-family Chiisai integrations use this mechanism to redirect
ZMK RGB power control to the rear P0.08 pad.

## Bootloader and Flash Layout

The ZMK board target uses an Adafruit nRF52 UF2-compatible flash layout.
Successful builds generate a `zmk.uf2` firmware file.

The partition layout reserves the bootloader and settings regions required by
the working Chiisai configuration. Changing the flash layout should be treated
as a compatibility change and validated carefully on physical hardware.

## Building Firmware

Build Chiisai firmware with the qualified board target and the required shield.

Generic form:

```bash
west build -p -d build/<name> \
  -b clickety_split_chiisai/nrf52840/zmk -- \
  -DSHIELD=<shield_name>
```

Example for the left half of Leeloo-Micro rev2:

```bash
west build -p -d build/leeloo_micro_chiisai_left \
  -b clickety_split_chiisai/nrf52840/zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_rev2_left
```

Example for the right half:

```bash
west build -p -d build/leeloo_micro_chiisai_right \
  -b clickety_split_chiisai/nrf52840/zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_rev2_right
```

The UF2 output is normally available at:

```text
build/<name>/zephyr/zmk.uf2
```

Build both halves when using Chiisai on a split keyboard.

## Flashing Firmware

1. Place the required Chiisai half into its UF2 bootloader.
2. Mount the bootloader storage volume on the host computer.
3. Copy the corresponding `zmk.uf2` file to the mounted volume.
4. Allow the controller to restart.
5. Repeat the process for the other half of a split keyboard.

The bootloader is typically entered by double-tapping the controller reset
input. Use the hardware reset method appropriate to the installed keyboard.

When moving between materially different firmware configurations, a ZMK
settings-reset build may be required before flashing the normal firmware.

## Validated Shield Integrations

### Leeloo-Micro v1.1 / Rev2

Chiisai has been physically validated on Leeloo-Micro v1.1 / rev2 with the
current ZMK 4.1 integration.

The physical test confirmed:

- keyboard input;
- split communication;
- both Sharp LS011B7DH03 160 × 68 Memory LCD displays;
- correctly resolved display status information; and
- RGB underglow operation.

The Chiisai-specific Leeloo-Micro integration uses:

- P0.06 to keep the Chiisai regulator and VCC active;
- rear P0.08 as the active-low RGB MOSFET control through the required bodge
  connection;
- P1.09 / D1 for WS2812 data;
- P1.12 / D2 for Sharp display MOSI;
- P1.13 / D3 for Sharp display SCK; and
- P1.14 / D4 for active-high Sharp display chip select.

### Leeloo Rev3

The Leeloo rev3 Chiisai integration has passed build and generated-output
validation for its controller-specific display and RGB routing.

The current documentation does not claim physical Leeloo rev3 validation with
Chiisai until that specific controller and keyboard combination is tested on
hardware.

## Validation Status

### Build-Validated

The following items compile successfully in the current ZMK 4.1 workspace:

- the qualified Chiisai board target;
- all 18 Pro Micro connector GPIO mappings;
- Chiisai with the supported Leeloo-family shield targets; and
- controller-specific Sharp display and RGB configurations.

### Generated-Output Validated

Generated Kconfig and Devicetree output were inspected for:

- qualified-board selection;
- DC/DC regulator configuration;
- RC low-frequency clock configuration;
- persistent settings storage;
- VDDH battery reporting;
- the P0.06 active-high board power output;
- the 50 ms external-power initialization delay;
- UF2-compatible partitions;
- controller-specific display routing;
- controller-specific RGB power routing; and
- WS2812 data routing.

### Physically Validated

Leeloo-Micro v1.1 / rev2 with Chiisai was physically tested with the current
ZMK 4.1 integration. Keyboard input, split communication, both Sharp displays,
resolved status rendering, and RGB operation were confirmed.

Physical validation applies only to the stated keyboard, revision, controller,
and tested functions.

### Longer-Term Validation

Longer-term validation remains ongoing for:

- battery endurance;
- repeated sleep and wake cycles;
- extended Bluetooth reconnect behavior; and
- long-duration reliability.

## Compatibility and Limitations

- Chiisai is Pro Micro-compatible, but shield-specific display and RGB routing
  may still require a controller-specific overlay.
- The board-level P0.06 external-power behavior must remain accounted for when
  a shield reuses ZMK `EXT_POWER`.
- The Chiisai RGB integrations for Leeloo rev3 and Leeloo-Micro rev2 require
  a rear P0.08 bodge connection for the active-low RGB MOSFET control.
- P1.01 / D18 must not be used as the Chiisai RGB MOSFET route on Leeloo
  because that connector signal is used by the keyboard matrix.
- The temporary Leeloo-family RGB compatibility configuration should be
  replaced when an appropriate upstream ZMK power-domain solution becomes
  available.
- Physical validation of one shield does not automatically validate every
  other Pro Micro-compatible keyboard.

## Migration Notes

The ZMK 4.1 migration preserves the established Chiisai v1.13 hardware
behavior rather than redesigning the controller.

Intentional compatibility decisions include:

- retaining the proven RC low-frequency clock setup;
- retaining VDDH battery reporting;
- retaining persistent settings storage;
- preserving the historical external-power node name;
- retaining the 50 ms power initialization delay;
- using the qualified Zephyr board-target structure; and
- keeping shield-specific routing outside the generic board definition.

## Support

For questions about this hardware, please
[contact Clickety Split](https://clicketysplit.ca/pages/contact-us).

**Clickety Split** — For the love of split keyboards.
