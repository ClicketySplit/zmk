# Clickety Split Pepito

Pepito is a wireless 3×6+4 split keyboard designed by Clickety Split. This shield definition supports Pepito v1.13 on ZMK 4.1 using a Seeed Studio XIAO nRF52840 controller on each half.

## Supported Targets

Pepito provides two shield targets:

- `clickety_split_pepito_left`
- `clickety_split_pepito_right`

Both targets use the ZMK 4.1 board target:

```text
xiao_ble//zmk
```

The left half is the split central. The right half is the split peripheral.

## Hardware Overview

Each half includes:

- Seeed Studio XIAO nRF52840
- 22-key matrix
- 74HC595-compatible serial shift register for matrix-column expansion
- Sharp LS011B7DH03-compatible 160 × 68 pixel Memory LCD
- Shared SPI bus for the shift register and display

Pepito does not use RGB underglow, an external-power controller, a regulator node, or a shield-specific power domain.

## Shared SPI Architecture

Pepito uses the XIAO SPI bus supplied by the ZMK 4.1 `xiao_ble//zmk` board definition.

| Signal | XIAO pin | nRF52840 pin |
|---|---:|---:|
| SCK | D8 | P1.13 |
| MOSI | D10 | P1.15 |
| Shift-register CS | D7 | Active low |
| Display CS | D6 | Active high |

The devices share the bus as follows:

The matrix expander is declared using the ZMK Devicetree compatible
`zmk,gpio-595`.

| SPI address | Device | Maximum frequency |
|---:|---|---:|
| 0 | 74HC595-compatible GPIO expander | 200 kHz |
| 1 | Sharp LS011B7DH03-compatible display | 1 MHz |

The current XIAO board definition already provides the required SPI pin control. Pepito therefore does not carry a shield-owned board pinctrl override.

## Matrix Layout

The four matrix rows are connected to XIAO D0 through D3 and use pull-down inputs.

The matrix columns are provided by the 74HC595-compatible GPIO expander.

- Left half column order: outputs 1, 2, 3, 4, 5, 6
- Right half column order: outputs 6, 5, 4, 3, 2, 1
- Right half matrix-transform column offset: 6

The reversed right-side ordering preserves the historical Pepito physical matrix mapping.

## Display Support

Each half drives its Sharp Memory LCD directly.

The display configuration includes:

- `sharp,ls0xx`
- 160-pixel width
- 68-pixel height
- serial VCOM inversion
- 33 ms VCOM inversion interval
- ZMK built-in status screen
- dedicated display work queue
- display blanking while idle

Pepito does **not** require `nice_view` or `nice_view_adapter`.

Do not add either adapter shield to the build command.

## Configuration Notes

The left and right targets intentionally use separate configuration fragments.

Both halves enable:

```text
CONFIG_SPI=y
CONFIG_ZMK_DISPLAY=y
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y
CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_STACK_SIZE=4096
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y
```

The right target additionally sets:

```text
CONFIG_ZMK_USB=n
```

The right half is a split peripheral and does not expose ZMK USB HID. This setting also avoids the Kconfig dependency warning that would otherwise result from the application-wide USB default.

Disabling ZMK USB on the right half does not prevent the XIAO bootloader from accepting UF2 firmware during flashing.

## Building

Run the commands from the ZMK workspace root.

### Left Half

```bash
west build \
  -p always \
  -s app \
  -d build/clickety_split_pepito_left \
  -b "xiao_ble//zmk" -- \
  -DSHIELD=clickety_split_pepito_left
```

The generated firmware will be located at:

```text
build/clickety_split_pepito_left/zephyr/zmk.uf2
```

### Right Half

```bash
west build \
  -p always \
  -s app \
  -d build/clickety_split_pepito_right \
  -b "xiao_ble//zmk" -- \
  -DSHIELD=clickety_split_pepito_right
```

The generated firmware will be located at:

```text
build/clickety_split_pepito_right/zephyr/zmk.uf2
```

## Flashing

Flash the matching UF2 to each half:

1. Put the XIAO nRF52840 into its UF2 bootloader, normally by quickly pressing reset twice.
2. Wait for the bootloader storage device to appear.
3. Copy the left UF2 to the left half.
4. Copy the right UF2 to the right half.
5. Allow each controller to restart.

Use the left firmware only on the left half and the right firmware only on the right half.

A settings-reset UF2 may be useful before testing when either controller contains bonds or settings from older firmware.

## Build Warning

ZMK 4.1 currently emits:

```text
warning: Deprecated symbol KSCAN is enabled.
```

Pepito uses ZMK's in-tree `zmk,kscan-gpio-matrix` implementation together with the GPIO-595 driver. The warning is accepted for this migration because the current implementation builds successfully and preserves the historical matrix architecture.

A future migration to ZMK's newer input subsystem should be treated as a separate engineering change and physically tested with Pepito's shift-register-backed columns.

## Validation Status

As of July 18, 2026:

| Validation area | Status |
|---|---|
| ZMK 4.1 left build | Complete |
| ZMK 4.1 right build | Complete |
| Target-specific configuration resolution | Complete |
| Generated Kconfig audit | Complete |
| Generated Devicetree audit | Complete |
| GPIO-595 driver inclusion | Complete |
| Sharp LS0XX driver inclusion | Complete |
| Left/right split-role audit | Complete |
| Matrix row and column-order audit | Complete |
| Physical switch-matrix test | Pending |
| Physical display test | Pending |
| Split pairing and reconnect test | Pending |
| USB HID test | Pending |
| BLE HID test | Pending |
| Sleep and wake test | Pending |
| Longer-term battery and reliability testing | Pending |

Successful compilation and generated-output auditing do not by themselves confirm physical keyboard behavior.

## Migration Notes

The ZMK 4.1 migration:

- replaces the historical `seeeduino_xiao_ble` target with `xiao_ble//zmk`;
- removes the obsolete shield-owned XIAO SPI pinctrl override;
- replaces the unresolved common shield configuration with explicit left and right target fragments;
- preserves the historical keymap;
- preserves the historical matrix transform;
- preserves left and mirrored-right shift-register ordering;
- uses Zephyr's current `sharp,ls0xx` display driver with serial VCOM inversion;
- requires no custom Pepito driver or power-domain workaround.

## Project Links

- Clickety Split: https://clicketysplit.ca/
- Pepito product page: https://clicketysplit.ca/pages/pepito
- ZMK Firmware: https://zmk.dev/
