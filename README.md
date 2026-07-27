# NUCLEO-U575ZI-Q + X-NUCLEO-IKS5A1 AI_Inertial Firmware

## Introduction

This repository contains the AI_Inertial firmware project for the [NUCLEO-U575ZI-Q](https://www.st.com/en/evaluation-tools/nucleo-u575zi-q.html) board with the [X-NUCLEO-IKS5A1](https://www.st.com/en/evaluation-tools/x-nucleo-iks5a1.html) expansion board, compatible with the [ST AIoT Craft](https://staiotcraft.st.com/) online platform, which is part of the [ST Edge AI Suite](https://www.st.com/content/st_com/en/st-edge-ai-suite.html).

The project is self-contained and should be opened directly from this firmware folder in Visual Studio Code.

## Features

- Inference with a ML model running on the MLC (Machine Learning Core, decision tree)
- Custom PnPL protocol for firmware control over serial connectivity (ST-LINK VCP)
- Self-contained CMake project with Debug and Release presets
- VS Code configuration for configure, build, and debug operations
- ST-LINK debug workflow through Cortex-Debug
- The firmware can be controlled by the [ST AIoT Craft](https://staiotcraft.st.com/) online platform

## Repository Content

Main folders in this repository:
- `.vscode` for local VS Code workspace configuration
- `Addons`, `Core`, `Drivers`, `Middlewares` for firmware source code
- `AI_INERTIAL` for application-level inertial logic
- `X-CUBE-MEMS1` for MEMS integration support
- `staiotcft_nn_model` for model-related assets
- `cmake` for toolchain and generated CMake support files

## How The Firmware Works

This section summarizes the runtime behavior of the `AI_INERTIAL` firmware for the `NUCLEO-U575ZI-Q + X-NUCLEO-IKS5A1` boards, further described by the UM3525 user manual.

### Functional Overview

For this project, inference runs through one sensor-side target:
- `ISM6HG256X MLC` inference directly on the inertial sensor

At a high level, the firmware is organized in four layers:
- `Application layer`: command handling, telemetry generation, and orchestration
- `Middlewares and libraries`: PnPL manager, JSON serialization, transport, and support libraries
- `Sensor drivers`: low-level access to the sensor and MLC interrupt/result handling
- `Board support`: STM32Cube HAL/BSP, clocks, GPIO, timers, and ST-LINK transport integration

### Startup Sequence

On boot, the firmware initializes power, periodic timer, ST-LINK VCP transport, sensors, and the PnPL command interface. It then prints the supported command format on the serial output.

The default target is `ISM6HG256X MLC`. The firmware loads the default MLC configuration at startup and begins telemetry streaming unless inference is stopped by command.

### Data Flow

For MLC inference, the decision tree runs inside the `ISM6HG256X` sensor. The MCU does not execute the classifier. Instead, it configures the sensor, waits for MLC events, reads result/status registers, and forwards classification telemetry to the host.

### Host Interaction Through PnPL

User interaction happens through ST-LINK virtual COM using JSON-formatted PnPL messages.

Important terminal setting:
- enable `CR+LF` line termination, otherwise commands may not be parsed correctly

Common commands:

```json
{"ism6hg256x_mlc*start_inference":""}
{"ism6hg256x_mlc*stop_inference":""}
{"get_status":"all"}
{"controller*set_dfu_mode":""}
{"controller*switch_bank":""}
```

MLC model loading payload:

```json
{
  "ism6hg256x_mlc*load_model": {
    "arguments": {
      "filename": "model_name",
      "size": 1234,
      "content": "1000F021...5102"
    }
  }
}
```

The `content` field contains the register-configuration payload in hexadecimal text.

## Getting Started

### Prerequisites

Install the following tools:
- STM32CubeCLT with CMake, Ninja, and GNU Arm Embedded toolchain
- Visual Studio Code
- VS Code extensions: CMake Tools, Cortex-Debug, C/C++
- ST-LINK drivers and tools for debug or flashing

### Open The Project

Open this repository in VS Code:
- `NUCLEO-U575ZI-Q+X-NUCLEO-IKS5A1/STAIOTCRAFT_AI_Inertial_NUCLEO-U575ZI-Q_X-NUCLEO-IKS5A1`

Important:
- This project contains its own `.vscode/settings.json`.
- This firmware folder should be opened directly so CMake Tools resolves the project root and presets correctly.

### Configure

From this repository root:

```powershell
cmake --preset Debug
```

### Build

From this repository root:

```powershell
cmake --build --preset Debug
```

Recommended VS Code flow:
1. Open this repository in VS Code.
2. Let CMake Tools detect the project.
3. Use preset `Debug`.
4. Run `CMake: Configure`.
5. Run `CMake: Build`.

## Debug

1. Connect the NUCLEO-U575ZI-Q board through ST-LINK.
2. Build the Debug configuration.
3. Open Run and Debug in VS Code.
4. Select the Cortex-Debug launch configuration.
5. Start the debug session.

Expected debug executable:
- `b/Debug/STAIOTCRAFT_AI_Inertial.elf`

## Output

Typical output files:
- `.elf` debug image
- `.map` linker map file
- `.bin` binary image generated after link

Build output directory:
- `b/Debug`

## Troubleshooting

- If CMake is not found, update `.vscode/settings.json` with the correct `cmake.cmakePath`.
- If the executable is missing, configure and build the project first.
- If ST-LINK is not detected, verify USB connection, board power, and installed drivers.
- If command parsing fails, ensure the serial terminal is configured to send `CR+LF`.

## Notes

- Build artifacts are not tracked in git.
- After cloning, configure and build locally to regenerate the build folder.
- This firmware path focuses on `AI_INERTIAL` with sensor-side `ISM6HG256X MLC` inference.

## ST AIoT Craft compatible firmware

The full list of companion firmware compatible with the [ST AIoT Craft](https://staiotcraft.st.com/) online platform is reported here below.

- Datalogging firmware over USB/serial connectivity
  - [STAIOTCRAFT_SDATALOG_STEVAL-MKBOXPRO](https://github.com/stm32-hotspot/staiotcraft_sdatalog_steval-mkboxpro)
  - [STAIOTCRAFT_SDATALOG_RUST_STEVAL-MKBOXPRO](https://www.st.com/content/st_com/en/products/embedded-software/evaluation-tool-software/stsw-sdatalog-r.html) available as a software package from st.com
  - [STAIOTCRAFT_SDATALOG_NUCLEO-F401RE_X-NUCLEO-IKS5A1](https://github.com/stm32-hotspot/staiotcraft_sdatalog_nucleo-f401re_x-nucleo-iks5a1)
  - [STAIOTCRAFT_SDATALOG_NUCLEO-U575ZI-Q_X-NUCLEO-IKS5A1](https://github.com/stm32-hotspot/staiotcraft_sdatalog_nucleo-u575zi-q_x-nucleo-iks5a1)
  - [STAIOTCRAFT_SDATALOG_NUCLEO-H7A3ZI-Q_X-NUCLEO-IKS5A1](https://github.com/stm32-hotspot/staiotcraft_sdatalog_nucleo-h7a3zi-q_x-nucleo-iks5a1)

- Inference firmware over USB/serial connectivity
  - [STAIOTCRAFT_AI_Inertial_STEVAL-MKBOXPRO](https://github.com/stm32-hotspot/staiotcraft_ai_inertial_steval-mkboxpro)
  - [STAIOTCRAFT_AI_Inertial_STEVAL-STWINBX1](https://github.com/stm32-hotspot/staiotcraft_ai_inertial_steval-stwinbx1)
  - [STAIOTCRAFT_AI_Inertial_STEVAL-STWINKT1B](https://github.com/stm32-hotspot/staiotcraft_ai_inertial_steval-stwinkt1b)
  - [STAIOTCRAFT_AI_Inertial_NUCLEO-F401RE_X-NUCLEO-IKS5A1](https://github.com/stm32-hotspot/staiotcraft_ai_inertial_nucleo-f401re_x-nucleo-iks5a1)
  - [STAIOTCRAFT_AI_Inertial_NUCLEO-U575ZI-Q_X-NUCLEO-IKS5A1](https://github.com/stm32-hotspot/staiotcraft_ai_inertial_nucleo-u575zi-q_x-nucleo-iks5a1)
  - [STAIOTCRAFT_AI_Inertial_NUCLEO-H7A3ZI-Q_X-NUCLEO-IKS5A1](https://github.com/stm32-hotspot/staiotcraft_ai_inertial_nucleo-h7a3zi-q_x-nucleo-iks5a1)

- Inference firmware over Bluetooth Low Energy (BLE) connectivity
  - STAIOTCRAFT_AI_SSM_STEVAL-MKBOXPRO available within the [FP-SNS-STAIOTCFT](https://www.st.com/en/embedded-software/fp-sns-staiotcft.html) function pack for [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)
