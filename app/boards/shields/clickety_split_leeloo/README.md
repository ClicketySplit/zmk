# Clickety Split | Leeloo

Leeloo is one of the original Clickety Split split-keyboard families. Its
column stagger, balanced spacing, and five-key thumb arrangement helped
establish the design language later carried into Leeloo-Micro and MNML.

This directory contains the ZMK shield definitions for the supported Leeloo
hardware revisions.

## Firmware Targets

| Hardware | Left | Right |
| --- | --- | --- |
| Leeloo Rev1 | `clickety_split_leeloo_left` | `clickety_split_leeloo_right` |
| Leeloo Rev2 | `clickety_split_leeloo_rev2_left` | `clickety_split_leeloo_rev2_right` |
| Leeloo Rev3 | `clickety_split_leeloo_rev3_left` | `clickety_split_leeloo_rev3_right` |

## Building Firmware

Use the shield target matching the physical keyboard revision together with the
supported controller board target.

Example for the current Clickety Split Rev3 configuration:

```bash
west build -p -s app \
  -d build/leeloo_rev3_left \
  -b clickety_split_chiisai/nrf52840/zmk -- \
  -DSHIELD=clickety_split_leeloo_rev3_left
```

Replace the shield target and build directory with the matching revision and
half. Build and flash both halves of the keyboard.

Clickety Split provides a support guide for selecting the correct keyboard
configuration, building firmware with GitHub Actions, and flashing the matching
firmware to each half:

[Firmware builds and configuration](https://clicketysplit.ca/pages/firmware-builds-leeloo)

## Important Notes

- Use the shield target matching the physical Leeloo revision.
- Use the correct left or right firmware for each half.
- Rev3 display and RGB support use the current Clickety Split
  controller-specific configuration.
- The display is defined directly by the shield. Use the provided build
  configuration without adding a separate display shield.
- The current Chiisai RGB configuration requires the documented hardware
  connection described in the matching build guide.
- Leeloo Rev3 with Chiisai is physically validated, including direct
  displays, RGB operation, sleep and wake behaviour.

## More Information

- [Design history and photos](https://clicketysplit.ca/pages/legacy-designs)
- [Clickety Split support](https://clicketysplit.ca/pages/support)
- [ZMK firmware documentation](https://zmk.dev)
