# WiFi Deauth App

**CEH Module 14 - Hacking Wireless Networks**

## Overview
WiFi Deauthentication attack tool for testing wireless network security. Supports scanning WiFi networks, selecting targets, and sending deauth frames.

## Features
- 📡 WiFi network scanning
- 🎯 Target AP selection
- 📤 Deauth packet transmission
- 📊 Real-time attack statistics
- 🔔 Visual/LED notifications

## Hardware Requirements
- Flipper Zero
- ESP32 WiFi module (connected via GPIO) OR
- ESP32-based WiFi dev board

## Installation

1. **Compile the app:**
   ```bash
   ./fbt fap_wifi_deauth
   ```

2. **Copy to SD card:**
   ```bash
   cp dist/f7-D/apps/Tools/wifi_deauth.fap /path/to/sdcard/apps/Tools/
   ```

3. **Run on Flipper:**
   - Navigate to Apps → Tools
   - Select "WiFi Deauth"

## Usage

### Step 1: Scan Networks
- App automatically scans for WiFi networks on startup
- Wait for scan to complete

### Step 2: Select Target
- Use ↑/↓ to navigate network list
- Press OK to select target

### Step 3: Attack
- Attack begins immediately after selection
- Press Back to stop attack

### Step 4: Results
- View total packets sent
- Press OK to attack again
- Press Back to return to menu

## Controls

| Button | Action |
|--------|--------|
| ↑ | Previous network |
| ↓ | Next network |
| OK | Start attack / Attack again |
| Back | Stop attack / Exit |

## Technical Details

### Deauth Frame Structure
```c
uint8_t deauth_frame[] = {
    0xC0, 0x00,             // Frame Control
    0x3A, 0x01,             // Duration
    // Destination MAC (broadcast or client)
    // Source MAC (target AP)
    // BSSID (target AP)
    0x00, 0x00,             // Sequence number
    0x07, 0x00              // Reason code (Class 3 frame received)
};
```

### Attack Types
1. **Broadcast Deauth** - Disconnects all clients
2. **Targeted Deauth** - Specific client disconnection
3. **Continuous Mode** - Persistent attack

## ESP32 Integration

This app requires ESP32 firmware that supports WiFi injection. Recommended firmware:

- **ESP32-Marauder** - Full WiFi attack suite
- **ESP32-WiFi-Hash-Monster** - Handshake capture
- **Custom ESP32 firmware** - DIY implementation

### Wiring Diagram
```
Flipper GPIO -> ESP32
TX (Pin 13)  -> RX
RX (Pin 14)  -> TX
GND          -> GND
3.3V         -> 3.3V
```

## Legal & Ethical Use

⚠️ **WARNING:** This tool is for AUTHORIZED testing only.

**Legal uses:**
- Testing your own network security
- Authorized penetration testing with written permission
- CEH/security training in lab environments

**ILLEGAL uses:**
- Attacking networks without authorization
- Disrupting public WiFi
- Denial of service attacks on others

**By using this app, you agree to only use it legally and ethically.**

## CEH Lab Exercise

### Lab: WiFi Deauth Attack

**Objective:** Understand WiFi deauthentication attacks

**Setup:**
1. Create test WiFi network (WPA2)
2. Connect test client device
3. Launch WiFi Deauth app on Flipper

**Steps:**
1. Scan for test network
2. Select target AP
3. Initiate deauth attack
4. Observe client disconnection
5. Document findings

**Expected Results:**
- Client disconnects from AP
- Reconnection attempts visible
- Handshake capture possible (with monitor mode)

## Troubleshooting

**Issue: No networks found**
- Solution: Check ESP32 connection
- Verify ESP32 firmware is installed
- Ensure WiFi is enabled on ESP32

**Issue: Attack not effective**
- Causes:
  - Modern devices have deauth protection
  - 802.11w (Protected Management Frames) enabled
  - Wrong channel selected
- Solution: Test on older devices or disable PMF

**Issue: App crashes**
- Solution: Check logs via qFlipper
- Update to latest Flipper firmware
- Recompile with debug symbols

## Performance

| Metric | Value |
|--------|-------|
| Packets/sec | ~100-500 |
| Max range | Depends on ESP32 antenna |
| Supported channels | 1-14 (2.4GHz) |
| Memory usage | ~4KB |
| CPU usage | Low |

## Future Enhancements

- [ ] 5GHz support
- [ ] Handshake capture
- [ ] Evil Twin AP creation
- [ ] WPS attack integration
- [ ] Saved targets list
- [ ] Attack templates

## Credits

- **Author:** yogeshjoga
- **Based on:** ESP32-Marauder by justcallmekoko
- **License:** MIT

## Support

- GitHub: https://github.com/yogeshjoga/
- Email: jogayogeshedu@gmail.com

---

**Remember: With great power comes great responsibility. Use ethically!**
