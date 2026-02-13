# 🐬 Flipper Zero FAP Applications

<div align="center">

![Flipper Zero](https://img.shields.io/badge/Flipper-Zero-orange?style=for-the-badge)
![FAP Apps](https://img.shields.io/badge/FAP-Applications-blue?style=for-the-badge)
![CEH](https://img.shields.io/badge/CEH-Hardware-red?style=for-the-badge)
![Red Team](https://img.shields.io/badge/Red-Team-darkred?style=for-the-badge)

**Custom Flipper Applications for Penetration Testing and Red Team Operations**

</div>

---

## 📋 Table of Contents

- [About](#about)
- [What are FAP Apps?](#what-are-fap-apps)
- [Repository Structure](#repository-structure)
- [Custom Applications](#custom-applications)
- [Automation Flows](#automation-flows)
- [USB Profiles](#usb-profiles)
- [Installation](#installation)
- [Compilation Guide](#compilation-guide)
- [CEH Module Mapping](#ceh-module-mapping)
- [Red Team Usage](#red-team-usage)
- [Contributing](#contributing)
- [Disclaimer](#disclaimer)

---

## 🎯 About

This repository contains custom **Flipper Application Packages (FAP)** designed for:
- 🎓 **CEH (Certified Ethical Hacker) Hardware Module**
- 🔴 **Red Team Operations**
- 🔒 **Penetration Testing**
- 🧪 **Security Research**

All applications are written in C and compiled for Flipper Zero's firmware.

---

## 🤔 What are FAP Apps?

**FAP (Flipper Application Package)** are custom applications that extend Flipper Zero's functionality beyond built-in features.

### FAP vs Built-in Apps

| Feature | Built-in Apps | FAP Apps |
|---------|--------------|----------|
| **Storage** | Internal firmware | SD Card |
| **Updates** | Firmware update required | Independent updates |
| **Development** | Core team only | Community developed |
| **Customization** | Limited | Fully customizable |
| **Size Limit** | Constrained | Flexible |

### Benefits of FAP Apps
- ✅ **Modular** - Install only what you need
- ✅ **Updatable** - Update without firmware reflash
- ✅ **Customizable** - Modify source code for specific needs
- ✅ **Shareable** - Easy distribution
- ✅ **Safe** - Won't brick device if buggy

---

## 📁 Repository Structure

```
FAP_Apps/
├── README.md                       # This file
├── Custom_Apps/                    # C applications
│   ├── WiFi_Deauth/
│   ├── BLE_Scanner/
│   ├── RFID_Cloner/
│   ├── Network_Sniffer/
│   └── GPIO_Automation/
├── Automation_Flows/               # Workflow scripts
│   ├── Pentest_Workflows/
│   ├── RedTeam_Scenarios/
│   └── Multi_Protocol_Attacks/
├── USB_Profiles/                   # USB device profiles
│   ├── HID_Profiles/
│   ├── Mass_Storage/
│   └── Custom_Devices/
└── Documentation/                  # Guides and docs
    ├── Compilation_Guide.md
    ├── Installation.md
    ├── CEH_Module_Mapping.md
    └── RedTeam_Playbooks.md
```

---

## 🔧 Custom Applications

### 1. WiFi Deauth App
**Purpose:** Perform WiFi deauthentication attacks for testing network security.

**Features:**
- Scan for WiFi networks
- Select target AP
- Send deauth packets
- Monitor success rate

**CEH Module:** Module 14 - Hacking Wireless Networks

### 2. BLE Scanner App
**Purpose:** Scan and analyze Bluetooth Low Energy devices.

**Features:**
- BLE device discovery
- Service enumeration
- Characteristic reading
- GATT server interaction

**CEH Module:** Module 16 - IoT and OT Hacking

### 3. RFID Cloner App
**Purpose:** Advanced RFID/NFC cloning with analysis.

**Features:**
- Multi-frequency support (125kHz, 13.56MHz)
- UID modification
- Dump analysis
- Write protection bypass

**CEH Module:** Module 13 - Physical Security

### 4. Network Sniffer App
**Purpose:** Packet capture and analysis on serial interfaces.

**Features:**
- UART/SPI sniffing
- Protocol decoding
- Real-time display
- Log to SD card

**CEH Module:** Module 10 - Sniffing

### 5. GPIO Automation App
**Purpose:** Automate hardware interactions via GPIO pins.

**Features:**
- Pin configuration
- Timed sequences
- Sensor reading
- Relay control

**CEH Module:** Module 13 - Physical Security

---

## 🔄 Automation Flows

### Penetration Testing Workflows

Pre-configured sequences for common pentest scenarios:

1. **Network Reconnaissance Flow**
   - WiFi scanning → BLE discovery → RFID detection → Report generation

2. **Physical Security Assessment**
   - RFID cloning → Badge emulation → Access logging

3. **IoT Device Testing**
   - BLE enumeration → Vulnerability scanning → Exploit delivery

### Red Team Scenarios

Mission-based attack chains:

1. **Initial Access Scenario**
   - BadUSB payload → Credential harvesting → C2 callback

2. **Lateral Movement Scenario**
   - Network sniffing → Protocol analysis → Credential relay

3. **Data Exfiltration Scenario**
   - File collection → Compression → Covert channel upload

---

## 🔌 USB Profiles

### HID Keyboard Profiles
- **Fast Typing** - Optimized for speed
- **Stealth Mode** - Randomized delays
- **Multi-Language** - International keyboard layouts

### Mass Storage Profiles
- **BadUSB + Storage** - Dual-mode operation
- **Autorun Payloads** - Windows autorun.inf exploitation
- **Forensic Images** - Disk image deployment

### Custom Device Emulation
- **Arduino Leonardo** - Microcontroller emulation
- **Rubber Ducky** - Hak5 compatibility mode
- **Custom VID/PID** - Device spoofing

---

## 📥 Installation

### Prerequisites
- Flipper Zero with SD card
- Latest official firmware or custom firmware (Unleashed/Xtreme)
- qFlipper or mobile app for file transfer

### Installation Steps

1. **Download FAP files** from this repository

2. **Transfer to Flipper:**
   - Connect Flipper via USB
   - Open qFlipper
   - Navigate to `SD Card/apps/`
   - Copy `.fap` files to appropriate category folder

3. **Access on Flipper:**
   - Navigate to Applications
   - Find your app category
   - Select and run the app

### Folder Structure on SD Card
```
/ext/apps/
├── Main/           # Main menu apps
├── GPIO/           # GPIO apps
├── Sub-GHz/        # Sub-GHz apps
├── NFC/            # NFC/RFID apps
└── Tools/          # Utility apps
```

---

## 🛠️ Compilation Guide

### Development Environment Setup

**Required Tools:**
- Git
- Docker (recommended) or native toolchain
- Visual Studio Code (optional but recommended)

### Method 1: Using Docker (Recommended)

```bash
# Clone Flipper firmware
git clone --recursive https://github.com/flipperdevices/flipperzero-firmware.git
cd flipperzero-firmware

# Pull development container
docker pull ghcr.io/flipperdevices/flipperzero-toolchain

# Clone this repository into apps_data folder
cd applications_user
git clone https://github.com/yourusername/FlipperZero_FAP_Apps.git

# Build the app
./fbt fap_wifi_deauth
```

### Method 2: Native Compilation

**Linux/macOS:**
```bash
# Install dependencies
sudo apt install git gcc-arm-none-eabi python3

# Clone firmware
git clone --recursive https://github.com/flipperdevices/flipperzero-firmware.git
cd flipperzero-firmware

# Build toolchain
./fbt

# Build your app
./fbt fap_APPNAME
```

**Windows:**
```powershell
# Use WSL2 or install toolchain manually
# Recommended: Use Docker method instead
```

### Building All FAP Apps
```bash
# Build all custom apps
./fbt fap_dist

# Output location
./dist/f7-D/apps/
```

### App Structure
```
MyApp/
├── application.fam         # App manifest
├── my_app.c               # Main source
├── my_app.h               # Header file
├── my_app_icons.c         # Icon assets (optional)
└── README.md              # App documentation
```

---

## 🎓 CEH Module Mapping

This section maps FAP apps to CEH v12 modules:

| CEH Module | Module Name | Relevant Apps |
|------------|-------------|---------------|
| **Module 10** | Sniffing | Network Sniffer, GPIO Automation |
| **Module 13** | Physical Security | RFID Cloner, BadUSB Profiles |
| **Module 14** | Wireless Networks | WiFi Deauth, BLE Scanner |
| **Module 16** | IoT/OT Hacking | BLE Scanner, GPIO Automation |
| **Module 18** | Mobile Platforms | BLE Scanner, NFC Tools |

### Practical Lab Exercises

**CEH Lab 1: RFID Cloning**
- Use RFID Cloner app to read access cards
- Analyze card data structure
- Clone to blank card
- Test access

**CEH Lab 2: WiFi Security**
- Scan networks with WiFi Deauth
- Perform deauth attack
- Capture handshake
- Document findings

**CEH Lab 3: BLE Security**
- Discover BLE devices
- Enumerate services
- Read characteristics
- Identify vulnerabilities

---

## 🔴 Red Team Usage

### Mission Planning

**1. Reconnaissance Phase**
```
Tools: WiFi Deauth, BLE Scanner, RFID Cloner
Goal: Identify attack surface and potential entry points
```

**2. Initial Access**
```
Tools: BadUSB Profiles, RFID Cloner
Goal: Gain physical or logical access to target
```

**3. Persistence**
```
Tools: GPIO Automation, Custom USB Devices
Goal: Maintain access and establish backdoors
```

**4. Exfiltration**
```
Tools: Network Sniffer, Mass Storage Profiles
Goal: Extract data covertly
```

### Red Team Scenarios

#### Scenario 1: Physical Breach
**Objective:** Gain access to secure facility

**Steps:**
1. Clone employee RFID badge using RFID Cloner
2. Enter facility during business hours
3. Deploy BadUSB payload on target workstation
4. Establish reverse shell connection
5. Document access level achieved

#### Scenario 2: WiFi Network Compromise
**Objective:** Gain access to corporate WiFi

**Steps:**
1. Scan for WPA2-Enterprise networks
2. Use WiFi Deauth to capture handshakes
3. Offline cracking (separate tool)
4. Document network security posture

#### Scenario 3: IoT Device Enumeration
**Objective:** Identify vulnerable IoT devices

**Steps:**
1. BLE scan for smart devices
2. Enumerate services and characteristics
3. Identify default credentials
4. Document exploitable devices

---

## 🤝 Contributing

We welcome contributions! Here's how you can help:

### Adding New Apps

1. Fork this repository
2. Create app in `Custom_Apps/YourApp/`
3. Follow Flipper's app structure guidelines
4. Include `application.fam` manifest
5. Add README with usage instructions
6. Test thoroughly on actual hardware
7. Submit Pull Request

### App Guidelines

- ✅ Well-commented code
- ✅ Error handling
- ✅ User-friendly interface
- ✅ Resource cleanup
- ✅ Documentation
- ✅ Proper licensing

### Code Style
Follow Flipper's coding standards:
- Use `snake_case` for functions
- Use `PascalCase` for types
- Include Doxygen comments
- Maximum 100 characters per line

---

## ⚠️ Disclaimer

> **FOR AUTHORIZED SECURITY TESTING ONLY**

### Legal Notice

**These applications are provided for:**
- ✅ Authorized penetration testing
- ✅ Security research
- ✅ Educational purposes (CEH training)
- ✅ Personal device testing

**ILLEGAL USES:**
- ❌ Unauthorized network access
- ❌ RFID cloning for fraud
- ❌ Disruption of services
- ❌ Privacy violations

### Responsible Use
- Only test systems you own or have written authorization to test
- Comply with all applicable laws (CFAA, GDPR, local regulations)
- Obtain proper permissions before red team exercises
- Document all activities for legal compliance
- Respect privacy and data protection laws

**The authors and contributors are NOT responsible for misuse of these tools.**

### Ethical Guidelines
By using these applications, you agree to:
1. Use only for lawful purposes
2. Obtain proper authorization
3. Respect privacy and property
4. Report vulnerabilities responsibly
5. Follow industry best practices

---

## 📚 Resources

### Official Documentation
- [Flipper Zero Docs](https://docs.flipperzero.one/)
- [FAP Development Guide](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/AppsOnSDCard.md)
- [Flipper API Reference](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/AppManifests.md)

### Community Resources
- [Awesome Flipper Zero](https://github.com/djsime1/awesome-flipperzero)
- [Flipper Discord](https://flipp.dev/discord)
- [Reddit r/flipperzero](https://reddit.com/r/flipperzero)

### CEH Resources
- [EC-Council CEH](https://www.eccouncil.org/programs/certified-ethical-hacker-ceh/)
- [CEH Practical](https://www.eccouncil.org/programs/certified-ethical-hacker-ceh-practical/)

---

## 📞 Contact

**Author:** yogeshjoga

- 🐙 **GitHub:** [yogeshjoga](https://github.com/yogeshjoga/)
- 💼 **LinkedIn:** [yogeshjoga](https://www.linkedin.com/in/yogeshjoga/)
- 📧 **Email:** jogayogeshedu@gmail.com

---

## 📜 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

**Note:** Individual apps may have their own licenses. Check each app's directory.

---

<div align="center">

**⭐ Star this repository if you find it useful! ⭐**

**Made with ❤️ for the Security Community**

**Happy (Authorized) Hacking! 🐬**

</div>
