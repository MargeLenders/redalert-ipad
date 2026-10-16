# 🪖 Command & Conquer: Red Alert (1996) — Native Port for iPadOS

[![Platform](https://img.shields.io/badge/Platform-iPadOS%2016%2B%20%7C%20macOS%2012%2B%20%7C%20Linux%20%7C%20Android-blue.svg)](https://github.com/MargeLenders/redalert-ipad)
[![Architecture](https://img.shields.io/badge/Architecture-ARM64%20(Apple%20Silicon)%20%7C%20x86__64-orange.svg)](https://github.com/MargeLenders/redalert-ipad)
[![Upstream](https://img.shields.io/badge/Upstream-Fork%20of%20dk8827%2Fra--port-brightgreen.svg)](https://github.com/dk8827/ra-port)
[![Graphics](https://img.shields.io/badge/Graphics-SDL2%20Hardware%20Accelerated-green.svg)](https://www.libsdl.org/)
[![Audio](https://img.shields.io/badge/Audio-DirectSound%20Shim%20%2F%20SDL2%20Audio-purple.svg)](https://www.libsdl.org/)
[![License](https://img.shields.io/badge/License-GPLv3%20with%20additional%20terms-lightgrey.svg)](LICENSE.md)
[![Language: Español](https://img.shields.io/badge/Language-Espa%C3%B1ol-yellow.svg)](README.es.md)

> 📖 *Leer en [Español](README.es.md)*

A high-performance native source port of Westwood Studios' legendary real-time strategy game **Command & Conquer: Red Alert (1996)**, running natively on **iPadOS (iPad)**.

This project is a downstream fork of [`dk8827/ra-port`](https://github.com/dk8827/ra-port), which modernized the original C++ codebase released by Electronic Arts under GPLv3 (<https://github.com/electronicarts/CnC_Red_Alert>).

This fork extends the port into a first-class tablet experience with **native iPadOS 16+ support**, an **authentic 1996 Westwood retro tactical touch HUD**, **1:1 multi-touch gestures**, custom Soviet app icon, and automated tooling for both the iOS Simulator and physical iPads.

---

## ✨ Key Features

* **🎮 1:1 Direct Multi-Touch Controls & Tactical HUD (No Clunky Virtual Joysticks)**:
  * **1-Finger Tap**: Select units, issue move/attack orders, place structures, and interact with the construction sidebar.
  * **1-Finger Drag (Rubber-Band)**: Box-select multiple combat units simultaneously with a visual green selector rectangle.
  * **2-Finger Tap**: Native Right-Click (cancel movement orders, deselect units, abort building placement, or toggle sell/repair mode).
  * **2-Finger Drag**: Smooth battlefield camera panning in any direction.
  * **Authentic 1996 Tactical HUD Dock (leafy side of the screen)**:
    * **`CTRL` (Force Attack)**: Toggle force-attack mode to target ground, bridges, or friendly units. Features an active amber indicator lamp.
    * **`1`, `2`, `3`, `4` (Combat Teams)**: Quick-tap to select assigned combat groups (double-tap centers the camera). Long-press (400ms) assigns selected units to that group (like desktop `Ctrl + 1..4`), verified with a green LED indicator.
    * **`KEY` (Virtual Keyboard)**: Toggles the system on-screen keyboard for text input, saves, and cheats.
    * **`▲` / `▼` (Collapse Arrow)**: Minimizes the HUD dock into a tiny unobtrusive button to free up screen real estate.
* **⚡ Hardware-Accelerated Graphics**:
  * Native SDL2 video backend using GPU-accelerated rendering at native display resolution.
  * Automatic 4:3 aspect ratio correction with integer scaling and pillarboxing.
* **🔊 Authentic EVA & Westwood Sound Engine**:
  * Original 22.05 kHz audio playback with in-game EVA voice announcements, full soundtrack, and FMV video cutscenes with synchronized audio.
* **⚔️ 100% Campaign & Skirmish Support**:
  * Complete Allied and Soviet campaigns are fully playable from start to finish.
  * Local skirmish mode with configurable AI opponents and difficulty levels.
* **💾 Sandbox Save Game Management**:
  * Safe isolated app sandbox storage on iPadOS/iOS (`Documents/`), persisting across updates and reboots.

---

## 🏛️ System Architecture

```
┌────────────────────────────────────────────────────────┐
│             Platform Host Layer                        │
│   • iPadOS: UIKit, UIScene, borderless landscape       │
└──────────────────────────┬─────────────────────────────┘
                           │
                           ▼
┌────────────────────────────────────────────────────────┐
│             SDL2 Platform & Input Layer                │
│   • Hardware-accelerated surface rendering             │
│   • Multitouch pointer tracking & gesture dispatch     │
│   • Audio stream mixing (DirectSound / WinMM shims)    │
└──────────────────────────┬─────────────────────────────┘
                           │
                           ▼
┌────────────────────────────────────────────────────────┐
│      Retro Tactical HUD & Touch Gesture Engine         │
│   • 1996 industrial steel-plate HUD rasterizer         │
│   • Touch hit testing, force attack & team grouping    │
│   • Rubber-band multi-unit selection state machine     │
└──────────────────────────┬─────────────────────────────┘
                           │
                           ▼
┌────────────────────────────────────────────────────────┐
│         Westwood Red Alert 95 Core Engine              │
│   • CONQUER, DISPLAY, SCENARIO, SIDEBAR, TAB, MAP, AI  │
│   • Mixfile (.MIX) virtual file system & LCW unpack    │
│   • VQA movie stream decoder & audio player            │
└────────────────────────────────────────────────────────┘
```

---

## ⚠️ Important: Game Assets Notice

> **NO COPYRIGHTED GAME ASSETS ARE INCLUDED IN THIS REPOSITORY**
> 
> In strict compliance with copyright laws and Electronic Arts' terms, this repository contains **only source code and build tools**. No game assets, `.MIX` archives, movies, speech, music tracks, or disc images are stored here.
> 
> To play the game, you must provide your own legally obtained assets from the original Red Alert discs.

### Where to Get the Game Assets Legally

In 2008, Electronic Arts officially released Command & Conquer: Red Alert as **freeware** for its 12th anniversary. You can use:
1. The official EA freeware ISO disc images:
   * **Allies Disc**: `CD1_ALLIED_DISC.ISO`
   * **Soviet Disc**: `CD2_SOVIET_DISC.ISO`
2. Or your original 1996 retail CDs or disc image backups.

---

## 🚀 Step-by-Step Tutorial: From Scratch to Playing

Follow these simple steps to build and install the game on macOS and your iPad:

### Step 1: Clone This Repository

Open **Terminal** on your Mac and clone this repository:

```bash
git clone https://github.com/MargeLenders/redalert-ipad.git
cd redalert-ipad
```

*(Or clone your own fork if you forked it on GitHub).*

---

### Step 2: Install Build Dependencies

On macOS, install CMake, Ninja, and SDL2 via [Homebrew](https://brew.sh/):

```bash
brew install cmake ninja pkg-config sdl2
xcode-select --install
```

Ensure full **Xcode** (not just Command Line Tools) is installed from the Mac App Store if you plan to build for iOS/iPadOS.

---

### Step 3: Prepare the Game Assets (Discs / ISOs)

1. **Mount both disc images** by double-clicking them in Finder, or via terminal:
   ```bash
   hdiutil mount /path/to/CD1_ALLIED_DISC.ISO
   hdiutil mount /path/to/CD2_SOVIET_DISC.ISO
   ```
   *(They will appear under `/Volumes/CD1` or `/Volumes/REDALERT` and `/Volumes/CD2`).*

2. **Run the automated asset preparation script**:
   ```bash
   scripts/prepare_assets_from_local.sh \
     --allies /Volumes/CD1 \
     --soviet /Volumes/CD2
   ```

3. **Unmount the disc images**:
   ```bash
   hdiutil unmount /Volumes/CD1
   hdiutil unmount /Volumes/CD2
   ```

*The script copies the required `.MIX` archives and `INSTALL/REDALERT.INI` into local `assets/redalert/` (which is git-ignored).*

---

### Step 4: Install on Your iPad

You can install and run the game using a **free personal Apple ID** (no paid \$99/year developer membership required).

1. **Find your Apple Development Team ID**:
   * In Xcode: Open **Settings** (`Cmd + ,`) $\rightarrow$ **Accounts** $\rightarrow$ select your Apple ID $\rightarrow$ **Manage Certificates** (your 10-character Team ID is shown next to your name).
   * Or view it at [developer.apple.com/account](https://developer.apple.com/account).

2. **Compile the optimized Release build for device**:
   ```bash
   RA_IOS_DEVELOPMENT_TEAM=YOUR_TEAM_ID scripts/build_ios_debug.sh --device --release
   ```
   *(Replace `YOUR_TEAM_ID` with your 10-character Team ID).*

3. **Deploy with Xcode**:
   * Connect your iPad to your Mac via USB and tap **Trust This Computer** on the iPad screen.
   * Open the generated Xcode project:
     ```bash
     open ios/build-device/redalert_ios.xcodeproj
     ```
   * In Xcode's top toolbar, select your connected iPad as the run destination.
   * Press **Run** (`Cmd + R`). Xcode will sign the app, embed the prepared game data, and install it on your iPad.

4. **Enable Developer Mode & Trust Certificate on iPad**:
   * On iPadOS 16/17+: Go to **Settings $\rightarrow$ Privacy & Security $\rightarrow$ Developer Mode**, turn it **On**, and reboot the iPad.
   * Go to **Settings $\rightarrow$ General $\rightarrow$ VPN & Device Management**, tap your Apple ID under *Developer App*, and tap **Trust**.
   * Launch **Red Alert** from your iPad home screen and enjoy!

---

## 🎮 iPad Touch Controls Reference

| Gesture / Input | In-Game Action | Description |
| :--- | :--- | :--- |
| **1-Finger Tap** | **Primary Action / Left-Click** | Select unit, issue move or attack command, place buildings, interact with sidebar. |
| **1-Finger Drag** | **Rubber-Band Box Selection** | Drags an authentic selection box to select multiple combat units at once. |
| **2-Finger Tap** | **Right-Click / Cancel** | Cancel orders, deselect units, abort structure placement, or toggle sell/repair. |
| **2-Finger Drag** | **Battlefield Camera Pan** | Smoothly pan the camera across the terrain in any direction. |
| **HUD: `CTRL`** | **Force Attack Toggle** | Forces units to fire at ground, bridges, or friendly structures (amber lamp indicates active mode). |
| **HUD: `1`..`4` (Tap)** | **Recall Combat Team** | Selects assigned unit group. Quick double-tap jumps the camera to their location. |
| **HUD: `1`..`4` (Hold)** | **Assign Combat Team** | Long-press (400ms) assigns current unit selection to that team (green LED confirms assignment). |
| **HUD: `KEY`** | **Virtual Keyboard** | Shows/hides the on-screen keyboard for typing names, saves, or cheats. |
| **HUD: `▲` / `▼`** | **Collapse HUD** | Minimizes the dock to a compact corner button for maximum screen view. |
| **External Mouse** | **Native Pointer** | Works seamlessly with Bluetooth mice, trackpads, and Magic Keyboards. |

---

## 📂 Repository Structure

```
.
├── CMakeLists.txt              # Root CMake build configuration
├── CODE/                       # Original Westwood C++ game engine
├── PORT/
│   ├── MAC/                    # Shared desktop runtime & SDL2 integration
│   │   ├── include/
│   │   │   ├── mobile_touch_hud.h      # Touch HUD state & controls
│   │   │   ├── mobile_touch_art.h      # Authentic 1996 retro steel-plate graphics
│   │   │   └── mobile_touch_gesture.h  # Multi-touch gesture tracker
│   │   └── src/
│   │       └── mac_sdl_runtime.cpp     # SDL2 window, audio & rendering pipeline
│   ├── IOS/                    # iOS entrypoint & writable sandbox setup
│   └── ANDROID/                # Android entrypoint
├── ios/                        # iOS app CMake target & Asset catalog
│   ├── Assets.xcassets         # Soviet hammer & sickle retro app icon
│   ├── CMakeLists.txt          # iOS Xcode project generator
│   └── Info.plist.in           # iOS property list template
├── android/                    # Android Gradle project
├── scripts/                    # Build, preparation, and launch helper scripts
│   ├── prepare_assets_from_local.sh  # Mount and package original game assets
│   ├── build_ios_debug.sh      # Automated iOS simulator and device builder
│   ├── run_ios_simulator.sh    # Boots simulator in landscape & deploys app
│   └── run_mac_dev.sh          # Desktop macOS launcher
├── tests/                      # Unit tests (including mobile HUD & touch gesture tests)
├── README.md                   # This English documentation
└── README.es.md                # Spanish documentation
```

---

## ❓ FAQ & Troubleshooting

#### Q: The build fails with *"Missing local Red Alert assets under assets/redalert"*.
**A:** You haven't prepared the game data. Follow Step 3 in the tutorial: mount the Allied and Soviet disc images and run `scripts/prepare_assets_from_local.sh`.

#### Q: How long does the app stay active on iPad with a free Apple ID?
**A:** Apple free personal certificates remain valid for **7 days**. When expired, simply reconnect your iPad to your Mac, open the project in Xcode, and press **Run** (`Cmd + R`) to refresh it for another 7 days. Your save games will remain untouched. (A paid Apple Developer account lasts 365 days).

#### Q: Xcode displays *"Failed to register bundle identifier"*.
**A:** Bundle identifiers must be unique on Apple's servers. Pass a custom identifier when building:
```bash
RA_IOS_BUNDLE_IDENTIFIER="com.yourname.redalert" scripts/build_ios_debug.sh --device --release
```

#### Q: Where are save games stored on iPad?
**A:** Saves are stored in the app's sandboxed `Documents/` directory and persist across game sessions and app rebuilds.

---

## ⚖️ Legal Disclaimer & Notice

* **Command & Conquer: Red Alert**: © 1996 Electronic Arts Inc. All rights reserved. Neither this repository nor its authors distribute proprietary game assets, archives, or audio.
* **Upstream Port**: Based on the open-source port by [`dk8827/ra-port`](https://github.com/dk8827/ra-port) and the Electronic Arts GPLv3 release (<https://github.com/electronicarts/CnC_Red_Alert>).
* **License**: Released under the **GNU General Public License v3 (GPLv3)** with additional terms. See [LICENSE.md](LICENSE.md) and [NOTICE.md](NOTICE.md).
