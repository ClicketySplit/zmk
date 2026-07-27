# Clickety Split | Leeloo-Micro

Leeloo-Micro is the compact continuation of the original Leeloo design
language. It preserves the familiar column stagger and thumb-key arrangement in
a smaller, more portable 3×5 format.

This directory contains the ZMK shield definitions for the supported
Leeloo-Micro hardware revisions.

## Firmware Targets

| Hardware | Left | Right |
| --- | --- | --- |
| Leeloo-Micro v1.0 / Rev1 | `clickety_split_leeloo_micro_left` | `clickety_split_leeloo_micro_right` |
| Leeloo-Micro v1.1 / Rev2 | `clickety_split_leeloo_micro_rev2_left` | `clickety_split_leeloo_micro_rev2_right` |

## Building Firmware

Use the shield target matching the physical keyboard revision together with the
supported controller board target.

Example for the current Clickety Split Rev2 configuration:

```bash
west build -p -s app \
  -d build/leeloo_micro_rev2_left \
  -b clickety_split_chiisai/nrf52840/zmk -- \
  -DSHIELD=clickety_split_leeloo_micro_rev2_left
```

Replace the shield target and build directory with the matching revision and
half. Build and flash both halves of the keyboard.

Clickety Split provides a support guide for selecting the correct keyboard
configuration, building firmware with GitHub Actions, and flashing the matching
firmware to each half:

[Firmware builds and configuration](https://clicketysplit.ca/pages/firmware-builds-leeloo-micro)

## Important Notes

- Use the shield target matching the physical Leeloo-Micro revision.
- Use the correct left or right firmware for each half.
- Rev2 display and RGB support use the current Clickety Split
  controller-specific configuration.
- The displays are defined directly by the shield. Use the provided build
  configuration without adding a separate display shield.
- The current Chiisai RGB configuration requires the documented hardware
  connection described in the matching build guide.
- Leeloo-Micro Rev2 with Chiisai is physically validated, including direct
  displays, RGB operation, and production sleep and wake behaviour.

## More Information

- [Design history and photos](https://clicketysplit.ca/pages/legacy-designs)
- [Clickety Split support](https://clicketysplit.ca/pages/support)
- [ZMK firmware documentation](https://zmk.dev)
