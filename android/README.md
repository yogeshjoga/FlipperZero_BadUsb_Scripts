# Android BadUSB Scripts

This folder contains BadUSB scripts for Android devices (Android 8.0+).

## Available Scripts

### 📁 Phishing
- **URL_Opener.txt** - Opens Chrome browser to specified phishing URL

### 🎭 Pranking
- **Message_Spam.txt** - Opens messaging app and types spam messages

### ⚡ Command Execution
- **Device_Info.txt** - Gathers device information using getprop (requires Termux)

### 📊 Metadata Extraction
- **Network_Info.txt** - Extracts network configuration and connectivity info (requires Termux)

### 🔗 URL-Based Installation
- **APK_Installer.txt** - Downloads and installs APK from URL (requires Termux)

## Prerequisites

**Most scripts require Termux:**
- Install from [F-Droid](https://f-droid.org/packages/com.termux/)
- Do NOT use Google Play version (deprecated)
- Grant storage permissions: `termux-setup-storage`

## Usage Notes

- Android BadUSB support is limited compared to desktop OS
- USB Debugging may need to be enabled
- Some scripts require unlocked device
- Delays are longer due to app launch times
- **IMPORTANT:** Device must be unlocked for most scripts

## Compatibility

| Android Version | Support | Notes |
|-----------------|---------|-------|
| Android 14 | ✅ | Full support with Termux |
| Android 13 | ✅ | Full support with Termux |
| Android 12 | ✅ | Full support with Termux |
| Android 11 | ✅ | Full support |
| Android 10 | ✅ | Full support |
| Android 9 | ✅ | Full support |
| Android 8.0-8.1 | ⚠️ | Limited support |

## Limitations

⚠️ **Android BadUSB has several limitations:**
- Device must be unlocked
- Apps must be accessible
- USB settings matter (MTP vs PTP vs charging)
- Manufacturer customizations affect behavior
- Some devices don't support HID keyboard mode

## Security Notes

⚠️ **For authorized testing on owned devices only**
