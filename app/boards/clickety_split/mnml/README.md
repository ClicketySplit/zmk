# Clickety Split | MNML

MNML, pronounced *minimal*, is a family of integrated wireless split keyboards
designed by Clickety Split Ltd. The family combines the controller, power
management, battery reporting, charging, and direct memory display support on
the keyboard itself.

MNML exists to provide a compact, purpose-built Clickety Split platform without
requiring a separate plug-in controller.

## Firmware Targets

| Layout | Left | Right | Status |
| --- | --- | --- | --- |
| MNML 3×5 + 5M | `clickety_split_mnml_3x5_left//zmk` | `clickety_split_mnml_3x5_right//zmk` | Physically validated through sustained bench testing and extended operational use |
| MNML 3×6 + 5M | `clickety_split_mnml_3x6_left//zmk` | `clickety_split_mnml_3x6_right//zmk` | Physically validated through sustained bench testing and extended operational use |
| MNML 4×6 + 6M | Not yet registered | Not yet registered | In fabrication |

## Building Firmware

Build the required half directly from the qualified board target:

```bash
west build -p -s app \
  -d build/mnml_3x5_left \
  -b clickety_split_mnml_3x5_left//zmk
```

Replace the board target and build directory with the matching layout and half.

The generated UF2 firmware is normally located at:

```text
build/<name>/zephyr/zmk.uf2
```

Clickety Split provides a support guide for selecting the correct keyboard
configuration, building firmware with GitHub Actions, and flashing the matching
firmware to each half:

[Firmware builds and configuration](https://clicketysplit.ca/pages/firmware-builds-mnml)

## Important Notes

- Use the firmware target matching the physical MNML layout and half.
- Flash the matching left and right UF2 files.
- The display and battery reporting hardware are defined directly by the board.
  Use the provided build configuration without adding separate hardware shields.
- A settings reset may be required when moving between materially different
  firmware configurations.

## More Information

- [Clickety Split](https://clicketysplit.ca)
- [Clickety Split support](https://clicketysplit.ca/pages/support)
- [ZMK firmware documentation](https://zmk.dev)
