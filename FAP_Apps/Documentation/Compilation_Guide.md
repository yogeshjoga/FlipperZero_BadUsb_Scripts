# Compilation Guide for Flipper Zero FAP Apps

## Quick Start

**Prerequisites:**
- Docker (recommended) OR native toolchain
- Git
- 8GB+ RAM
- 20GB+ free disk space

**Estimated time:** 30-60 minutes for first build

---

## Method 1: Docker (Recommended)

### Step 1: Install Docker

**Windows:**
```powershell
# Download Docker Desktop from docker.com
# Install and restart
```

**Linux:**
```bash
sudo apt update
sudo apt install docker.io docker-compose
sudo usermod -aG docker $USER
# Log out and log back in
```

**macOS:**
```bash
# Download Docker Desktop from docker.com
# Install via DMG
```

### Step 2: Clone Firmware

```bash
# Clone official Flipper firmware
git clone --recursive https://github.com/flipperdevices/flipperzero-firmware.git
cd flipperzero-firmware

# Checkout stable release (recommended)
git checkout release
```

### Step 3: Pull Toolchain Container

```bash
# Pull pre-built development container
docker pull ghcr.io/flipperdevices/flipperzero-toolchain

# Verify
docker images | grep flipper
```

### Step 4: Add Your Apps

```bash
# Navigate to user apps folder
cd applications_user

# Clone this repository
git clone https://github.com/yogeshjoga/FlipperZero_BadUsb_Scripts.git flipper_apps

# Copy FAP apps to applications_user
cp -r flipper_apps/FAP_Apps/Custom_Apps/* .
```

### Step 5: Build FAP Apps

```bash
# Return to firmware root
cd ..

# Build specific app
./fbt fap_wifi_deauth

# Or build all custom apps
./fbt fap_dist

# Output location
ls -lh dist/f7-D/apps/
```

### Step 6: Transfer to Flipper

```bash
# Option 1: Via qFlipper
# - Connect Flipper via USB
# - Open qFlipper
# - Navigate to SD Card/apps/
# - Copy .fap files

# Option 2: Via command line (if qFlipper CLI installed)
qFlipper-cli --upload dist/f7-D/apps/Tools/wifi_deauth.fap /ext/apps/Tools/
```

---

## Method 2: Native Compilation (Linux)

### Ubuntu/Debian

```bash
# Install dependencies
sudo apt update
sudo apt install -y \
    git \
    gcc-arm-none-eabi \
    python3 \
    python3-pip \
    scons \
    clang-format

# Install Python packages
pip3 install --user pillow heatshrink2 protobuf

# Clone firmware
git clone --recursive https://github.com/flipperdevices/flipperzero-firmware.git
cd flipperzero-firmware

# Build toolchain
./fbt

# Add your apps to applications_user/

# Build apps
./fbt fap_APPNAME
```

### Arch Linux

```bash
# Install dependencies
sudo pacman -S arm-none-eabi-gcc git python python-pip scons

# Continue as above...
```

---

## Method 3: GitHub Actions (Automated)

### Create Workflow File

**.github/workflows/build-faps.yml**
```yaml
name: Build FAP Apps

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v3
        with:
          submodules: recursive

      - name: Build FAPs
        uses: flipperdevices/flipperzero-firmware@dev
        with:
          sdk-channel: release
          
      - name: Upload artifacts
        uses: actions/upload-artifact@v3
        with:
          name: fap-files
          path: dist/f7-D/apps/**/*.fap
```

---

## App Structure Requirements

### Minimum Files

```
MyApp/
├── application.fam      # REQUIRED - App manifest
├── my_app.c            # REQUIRED - Main source file
├── my_app.h            # Optional - header file
├── README.md           # Recommended - documentation
└── icons/              # Optional - custom icons
    └── my_app_icon_10x10.png
```

### Application.fam Format

```python
App(
    appid="my_app",                    # Unique identifier
    name="My App",                     # Display name
    apptype=FlipperAppType.EXTERNAL,   # External FAP
    entry_point="my_app_main",         # C function entry point
    requires=[                         # Required services
        "gui",
        "notification",
    ],
    stack_size=2 * 1024,              # Stack size in bytes
    fap_category="Tools",              # App category
    fap_version="1.0",                # Version
    fap_description="App description",
    fap_author="Your Name",
    fap_weburl="https://github.com/...",
    fap_icon="icon.png",              # Icon file
    fap_icon_assets="icons",          # Icon assets folder
)
```

---

## Troubleshooting

### Error: "Submodules not initialized"

```bash
git submodule update --init --recursive
```

### Error: "ARM compiler not found"

**Linux:**
```bash
sudo apt install gcc-arm-none-eabi
```

**macOS:**
```bash
brew install arm-none-eabi-gcc
```

**Windows:**
Use Docker method instead.

### Error: "Python module not found"

```bash
pip3 install --user -r scripts/requirements.txt
```

### Error: "Build failed with undefined reference"

- Check `application.fam` for missing dependencies in `requires` array
- Verify all required Flipper services are listed
- Check for typos in function names

### Error: "Icon not found"

- Ensure icon file exists in specified path
- Icon must be PNG format
- Recommended size: 10x10 pixels for menu icons

---

## Build Options

### Debug Build (with debugging symbols)

```bash
./fbt fap_wifi_deauth DEBUG=1
```

### Release Build (optimized)

```bash
./fbt fap_wifi_deauth COMPACT=1
```

### Clean Build (remove previous builds)

```bash
 ./fbt -c fap_wifi_deauth
```

### Build with Verbose Output

```bash
./fbt fap_wifi_deauth VERBOSE=1
```

---

## Testing

### On-Device Testing

```bash
# Build and launch in emulator (if available)
./fbt launch_app APPSRC=applications_user/wifi_deauth

# Or transfer to real device and test
```

### Unit Testing

```c
// Add to my_app_test.c
#include <furi.h>
#include "../my_app.h"

MU_TEST(test_basic_functionality) {
    // Your test code
    mu_assert(1 == 1, "Math works!");
}

MU_TEST_SUITE(my_app_tests) {
    MU_RUN_TEST(test_basic_functionality);
}

int run_minunit_test_my_app() {
    MU_RUN_SUITE(my_app_tests);
    return MU_REPORT();
}
```

---

## Performance Optimization

### Memory Usage

```c
// Check stack usage
#define TAG "MyApp"
FURI_LOG_I(TAG, "Stack free: %d", uxTaskGetStackHighWaterMark(NULL));
```

### CPU Optimization

```c
// Use efficient loops
for(size_t i = 0; i < count; i++) {
    // Avoid heavy operations in loop
}

// Prefer switch over multiple if-else
switch(state) {
    case STATE_A:
        break;
    case STATE_B:
        break;
}
```

---

## Advanced Topics

### Custom GUI Elements

```c
#include <gui/elements.h>

// Custom draw function
void my_custom_element(Canvas* canvas, uint8_t x, uint8_t y) {
    canvas_draw_box(canvas, x, y, 20, 20);
    canvas_draw_str(canvas, x + 5, y + 15, "Hi");
}
```

### Using Flipper Services

```c
// Storage access
Storage* storage = furi_record_open(RECORD_STORAGE);
File* file = storage_file_alloc(storage);
storage_file_open(file, "/ext/data.txt", FSAM_READ, FSOM_OPEN_EXISTING);
// ... use file
storage_file_close(file);
storage_file_free(file);
furi_record_close(RECORD_STORAGE);
```

### GPIO Control

```c
#include <furi_hal_gpio.h>

// Configure GPIO pin
furi_hal_gpio_init_simple(&gpio_ext_pa7, GpioModeOutputPushPull);

// Set high
furi_hal_gpio_write(&gpio_ext_pa7, true);

// Set low
furi_hal_gpio_write(&gpio_ext_pa7, false);
```

---

##  Resources

**Official Documentation:**
- [FAP Development](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/AppsOnSDCard.md)
- [API Reference](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/doxygen/html/index.html)
- [Flipper Build Tool (FBT)](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/fbt.md)

**Community:**
- Discord: https://flipp.dev/discord
- Forum: https://forum.flipperzero.one/
- Awesome Flipper: https://github.com/djsime1/awesome-flipperzero

---

**Author:** yogeshjoga  
**Last Updated:** 2026-02-14  
**Version:** 1.0
