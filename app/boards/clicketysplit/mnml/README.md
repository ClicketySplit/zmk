# Clickety Split MNML

**MNML**, pronounced *minimal*, is a family of wireless split keyboards designed by [Clickety Split Ltd.](https://clicketysplit.ca).

MNML keyboards combine low-profile mechanical switches, integrated power management, wireless split operation, and Sharp memory-in-pixel displays in a compact, purpose-built design.

This directory contains the ZMK board definitions and configuration files for the supported MNML layouts.

## MNML Family

| Layout        |             Keys | Firmware targets                                                            | Status                                                       |
| ------------- | ---------------: | --------------------------------------------------------------------------- | ------------------------------------------------------------ |
| MNML 3x5 + 5M |               40 | `clickety_split_mnml_3x5_left//zmk`<br>`clickety_split_mnml_3x5_right//zmk` | ZMK 4.1 builds successfully; hardware validation in progress |
| MNML 3x6 + 5M |               46 | `clickety_split_mnml_3x6_left//zmk`<br>`clickety_split_mnml_3x6_right//zmk` | ZMK 4.1 validated                                            |
| MNML 4x6 + 6M |               60 | Not yet registered                                                          | Planned                                                      |

---

## MNML 3x5 + 5M

The MNML 3x5 is the most compact member of the MNML family.

It provides three rows of five primary keys per half, together with five additional inner and thumb keys per half, for a total of 40 switches.

### Firmware targets

```text
clickety_split_mnml_3x5_left//zmk
clickety_split_mnml_3x5_right//zmk
```

### Build commands

```bash
west build -p \
  -s app \
  -d build/mnml_3x5_left \
  -b clickety_split_mnml_3x5_left//zmk
```

```bash
west build -p \
  -s app \
  -d build/mnml_3x5_right \
  -b clickety_split_mnml_3x5_right//zmk
```

### Development status

The ZMK 4.1 board definitions, hardware configuration, firmware configuration, metadata, and keymap have been migrated successfully.

Both halves currently build successfully. Hardware validation is in progress.

---

## MNML 3x6 + 5M

The MNML 3x6 adds an outer key column to each half while retaining the five-key inner and thumb arrangement.

The layout provides a total of 46 switches.

### Firmware targets

```text
clickety_split_mnml_3x6_left//zmk
clickety_split_mnml_3x6_right//zmk
```

### Build commands

```bash
west build -p \
  -s app \
  -d build/mnml_3x6_left \
  -b clickety_split_mnml_3x6_left//zmk
```

```bash
west build -p \
  -s app \
  -d build/mnml_3x6_right \
  -b clickety_split_mnml_3x6_right//zmk
```

### Development status

The MNML 3x6 board definitions have been migrated to the ZMK 4.1 hardware model and validated on physical hardware.

---

## MNML 4x6 + 6M

The MNML 4x6 + 6M expands the MNML family with four rows of six primary keys per half and six additional inner and thumb keys per half.

The layout provides a total of 60 switches.

Its firmware targets and development status will be documented here when the design is ready for implementation.

---

## Hardware Features

MNML hardware includes:

* Wireless split operation using the Nordic nRF52840
* Fanstel BC840M module with nRF52840-CKAA
* Hot-swappable Kailh Choc v1 switches
* Sharp LS011B7DH03 memory-in-pixel displays

  * 1.08-inch display
  * 160 × 68 pixel resolution
* Integrated single-cell LiPo charging
* MAX17048 battery fuel gauge
* USB-C connectivity with transient-voltage protection
* External 32.768 kHz crystal
* 700 mAh LiPo battery support
* Dedicated power-management circuitry
* UF2 firmware output

## Split Architecture

The left half operates as the split central and provides USB and Bluetooth host output.

The right half operates as a wireless peripheral and communicates with the left half over Bluetooth.

Both halves include their own:

* Key matrix
* Sharp memory display
* MAX17048 battery fuel gauge
* Battery and charging circuitry
* Power-management system

## Firmware Notes

The MNML board definitions use the ZMK and Zephyr hardware model v2 directory structure.

Shared family files are used where practical, while geometry-specific files define:

* Matrix dimensions
* Matrix transforms
* GPIO assignments
* Keymaps
* Board metadata
* Firmware targets

The MNML 3x5 keymap was migrated byte-for-byte from the original MNML v2.13 implementation.

## Development Status

MNML remains under active development and testing.

Firmware should be tested thoroughly on the intended hardware before general release, including:

* Complete matrix operation
* Wireless split connectivity
* USB and Bluetooth output
* Layer, combo, and tap-dance behavior
* Display operation
* Battery reporting
* Charging
* Sleep and wake behavior

## More Information

For more information about MNML or other Clickety Split projects, please visit [clicketysplit.ca](https://clicketysplit.ca).

Questions may be submitted through the [Clickety Split contact page](https://clicketysplit.ca/pages/contact-us).

**Clickety Split Ltd.**
*For the love of split keyboards.*
