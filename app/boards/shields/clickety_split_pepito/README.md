# Clickety Split | Pepito

Pepito is a wireless 3×6+4M split keyboard designed by Clickety Split Ltd. It
explored a compact and economical approach to wireless split hardware using one
Seeed Studio XIAO nRF52840 controller and one direct memory display per half.

Pepito helped bridge the earlier Clickety Split shield designs and the later
integrated MNML platform.

## Firmware Targets

Pepito uses the ZMK board target:

```text
xiao_ble//zmk
```

with the following shield targets:

| Half | Shield Target |
| --- | --- |
| Left / central | `clickety_split_pepito_left` |
| Right / peripheral | `clickety_split_pepito_right` |

## Building Firmware

Example for the left half:

```bash
west build -p -s app \
  -d build/clickety_split_pepito_left \
  -b xiao_ble//zmk -- \
  -DSHIELD=clickety_split_pepito_left
```

Replace the shield target and build directory with the right-half values when
building the peripheral firmware.

The generated UF2 firmware is normally located at:

```text
build/<name>/zephyr/zmk.uf2
```

Clickety Split provides a support guide for selecting the correct keyboard
configuration, building firmware with GitHub Actions, and flashing the matching
firmware to each half:

[Firmware builds and configuration](https://clicketysplit.ca/pages/firmware-builds-pepito)

## Important Notes

- Use `clickety_split_pepito_left` for the central half and
  `clickety_split_pepito_right` for the peripheral half.
- The unsuffixed `clickety_split_pepito` name is a shared source stem, not a
  public firmware target.
- The display is defined directly by the shield. Use the provided build
  configuration without adding a separate display shield.
- The current Pepito left and right firmware targets are physically validated
  on hardware.

## More Information

- [Design history and photos](https://clicketysplit.ca/pages/legacy-designs)
- [Clickety Split support](https://clicketysplit.ca/pages/support)
- [ZMK firmware documentation](https://zmk.dev)
