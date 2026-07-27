# Clickety Split | Chiisai

Chiisai is a Pro Micro-compatible wireless keyboard controller designed by
Clickety Split Ltd. It brings the Nordic nRF52840, USB, Bluetooth Low Energy,
UF2 firmware updates, and Clickety Split-specific hardware support to a familiar
controller format.

Chiisai exists so Clickety Split keyboards can use a controller designed
alongside the keyboards themselves, with power, display, and peripheral
integration considered as part of the complete platform.

## Board Target

Use the following qualified ZMK board target:

```text
clickety_split_chiisai/nrf52840/zmk
```

ZMK build configurations and metadata may also use the equivalent short form:

```text
clickety_split_chiisai//zmk
```

Chiisai is used together with the shield target for the selected keyboard and
hardware revision.

## Building Firmware

Build Chiisai with the required Clickety Split shield:

```bash
west build -p -s app \
  -d build/<name> \
  -b clickety_split_chiisai/nrf52840/zmk -- \
  -DSHIELD=<shield_target>
```

The generated UF2 firmware is normally located at:

```text
build/<name>/zephyr/zmk.uf2
```

For split keyboards, build and flash the matching firmware for both halves.

Clickety Split provides a support guide for selecting the correct keyboard
configuration, building firmware with GitHub Actions, and flashing the matching
firmware to each half:

[Firmware builds and configuration](https://clicketysplit.ca/pages/firmware-builds-chiisai)

## Important Notes

- Use the shield target matching the physical keyboard revision.
- Use the correct left or right firmware for each half.
- Some keyboard features require a controller-specific Clickety Split build
  configuration.
- The display is defined directly by the keyboard shield where applicable.
  Use the provided build configuration without adding a separate display
  shield.
- A settings reset may be required when changing between materially different
  firmware configurations.

## More Information

- [Clickety Split](https://clicketysplit.ca)
- [Clickety Split support](https://clicketysplit.ca/pages/support)
- [ZMK firmware documentation](https://zmk.dev)
