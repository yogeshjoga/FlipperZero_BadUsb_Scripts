# CEH v12 Module Mapping for Flipper Zero FAP Apps

## Overview

This document maps Flipper Zero FAP applications to **CEH (Certified Ethical Hacker) v12** modules, providing practical hands-on exercises aligned with the CEH curriculum.

---

## Module Breakdown

### Module 10: Sniffing

**CEH Topics Covered:**
- Network traffic sniffing
- Protocol analysis
- Packet capture techniques
- Man-in-the-middle attacks

**Flipper Apps:**

| App Name | Functionality | Lab Application |
|----------|---------------|-----------------|
| **Network Sniffer** | UART/SPI packet capture | Monitor serial communications |
| **GPIO Automation** | Pin state monitoring | Capture hardware signals |

**Practical Exercises:**

**Lab 10.1: Serial Sniffer**
1. Connect Flipper to target serial interface
2. Launch Network Sniffer app
3. Configure baud rate
4. Capture traffic
5. Analyze protocols
6. Export logs to SD card

**Skills Gained:**
- Hardware-level sniffing
- Protocol identification
- Data extraction from serial interfaces

---

### Module 13: Physical Security

**CEH Topics Covered:**
- Physical access controls
- Badge cloning
- Lock picking
- Social engineering
- USB attacks

**Flipper Apps:**

| App Name | Functionality | Lab Application |
|----------|---------------|-----------------|
| **RFID Cloner** | Clone 125kHz/13.56MHz cards | Duplicate access badges |
| **BadUSB Profiles** | HID keyboard emulation | Automated attacks via USB |
| **NFC Tools** | NFC tag reading/writing | Clone contactless cards |

**Practical Exercises:**

**Lab 13.1: RFID Access Control Testing**
1. Scan employee badge with RFID Cloner
2. Read UID and data blocks
3. Clone to blank card
4. Test cloned badge on reader
5. Document access level
6. Report findings

**Lab 13.2: BadUSB Attack**
1. Prepare malicious payload
2. Load to Flipper BadUSB
3. Connect to target workstation
4. Execute payload (credential harvester)
5. Analyze results
6. Develop countermeasures

**Skills Gained:**
- RFID security assessment
- USB attack vectors
- Physical penetration testing

---

### Module 14: Hacking Wireless Networks

**CEH Topics Covered:**
- WiFi security assessment
- Deauthentication attacks
- WPA/WPA2 cracking
- Rogue access points
- Wireless reconnaissance

**Flipper Apps:**

| App Name | Functionality | Lab Application |
|----------|---------------|-----------------|
| **WiFi Deauth** | 802.11 deauth frames | Client disconnection |
| **WiFi Scanner** (ESP32) | Network enumeration | SSID discovery |

**Practical Exercises:**

**Lab 14.1: WiFi Security Assessment**
1. Scan for wireless networks
2. Identify target AP (WPA2)
3. Launch deauth attack
4. Capture WPA handshake (with external tool)
5. Analyze encryption strength
6. Document vulnerabilities

**Lab 14.2: Rogue AP Detection**
1. Baseline legitimate APs
2. Monitor for new SSIDs
3. Identify evil twin attacks
4. Test deauth resistance
5. Recommend 802.11w (PMF)

**Skills Gained:**
- WiFi penetration testing
- Handshake capture
- Wireless threat detection

---

### Module 16: IoT and OT Hacking

**CEH Topics Covered:**
- IoT device security
- Bluetooth Low Energy (BLE) attacks
- MQTT protocol analysis
- Smart device exploitation
- Industrial control systems

**Flipper Apps:**

| App Name | Functionality | Lab Application |
|----------|---------------|-----------------|
| **BLE Scanner** | BLE device discovery | IoT enumeration |
| **BLE Analyzer** | GATT service enumeration | Characteristic reading |
| **GPIO Automation** | Industrial I/O control | PLC/SCADA simulation |

**Practical Exercises:**

**Lab 16.1: BLE IoT Security Testing**
1. Scan for BLE devices (smart locks, wearables)
2. Enumerate GATT services
3. Read unprotected characteristics
4. Test for default PINs
5. Attempt unauthorized pairing
6. Document vulnerabilities

**Lab 16.2: Smart Device Exploitation**
1. Target smart TV or speaker
2. Analyze BLE services
3. Identify control characteristics
4. Write values to control device
5. Test access controls
6. Recommend security improvements

**Skills Gained:**
- BLE security assessment
- IoT vulnerability identification
- Smart device penetration testing

---

### Module 18: Mobile Platform Security

**CEH Topics Covered:**
- Mobile device security
- NFC attacks
- Bluetooth vulnerabilities
- App-based attacks

**Flipper Apps:**

| App Name | Functionality | Lab Application |
|----------|---------------|-----------------|
| **NFC Reader** | NFC tag interaction | Mobile payment testing |
| **BLE Scanner** | Phone BLE enumeration | Accessory vulnerability testing |

**Practical Exercises:**

**Lab 18.1: NFC Security Assessment**
1. Scan NFC-enabled smartphone
2. Read NFC tags
3. Test mobile payment cards
4. Attempt tag cloning
5. Evaluate relay attack risks
6. Document findings

**Skills Gained:**
- Mobile NFC security
- Contactless payment testing

---

## Comprehensive Lab Scenarios

### Scenario 1: Corporate Physical Penetration Test

**Modules:** 10, 13, 14, 16  
**Duration:** 4 hours  
**Objective:** Assess physical and logical security

**Phase 1: Reconnaissance (Module 14)**
- WiFi scanning
- BLE device discovery
- Network mapping

**Phase 2: Physical Access (Module 13)**
- RFID badge cloning
- Tailgating attempt
- USB attack on workstation

**Phase 3: Network Access (Module 14)**
- WiFi deauth attack
- Handshake capture
- Credential harvesting

**Phase 4: IoT Enumeration (Module 16)**
- BLE smart device scanning
- GATT service analysis
- Vulnerability documentation

**Deliverables:**
- Penetration test report
- Risk assessment matrix
- Remediation recommendations

---

### Scenario 2: Smart Building Security Audit

**Modules:** 13, 16  
**Duration:** 3 hours  
**Objective:** Evaluate IoT security in smart building

**Tasks:**
1. **Smart Lock Testing**
   - BLE enumeration
   - Authentication bypass attempts
   - Physical security integration

2. **Access Control Assessment**
   - RFID badge security
   - Multi-factor authentication
   - Audit logging

3. **Building Automation**
   - HVAC control systems
   - Lighting system security
   - Sensor network analysis

**Deliverables:**
- IoT security audit report
- Device vulnerability matrix
- Compliance assessment (NIST, ISA/IEC 62443)

---

## Hands-On Lab Equipment

### Required Hardware

| Equipment | Purpose | CEH Modules |
|-----------|---------|-------------|
| Flipper Zero | Multi-tool platform | All |
| ESP32 WiFi Module | WiFi attacks | 14 |
| USB cables | BadUSB attacks | 13 |
| Blank RFID cards | Cloning practice | 13 |
| BLE devices | IoT testing | 16, 18 |
| Raspberry Pi | Lab environment | All |

### Software Tools

| Tool | Purpose | Integration |
|------|---------|-------------|
| qFlipper | Firmware management | Required |
| Wireshark | Packet analysis | Module 10 |
| Hashcat | Password cracking | Module 14 |
| Burp Suite | App testing | Module 18 |
| Metasploit | Exploitation | Modules 13-16 |

---

## CEH Practical Exam Alignment

### CE practical Skills Tested

| Skill | Flipper Application | Pass Criteria |
|-------|---------------------|---------------|
| **Network Scanning** | WiFi Scanner | Identify 5+ APs |
| **Wireless Attacks** | WiFi Deauth | Capture handshake |
| **Physical Security** | RFID Cloner | Clone access badge |
| **IoT Exploitation** | BLE Scanner | Find 3+ vulnerabilities |
| **USB Attacks** | BadUSB | Execute payload successfully |

### Exam Preparation Tips

1. **Practice all labs** in controlled environment
2. **Document every step** for report writing
3. **Time yourself** - CEH Practical is 6 hours
4. **Understand remediation** - not just exploitation
5. **Review legal/ethical** considerations

---

## Certification Alignment

### CEH (Certified Ethical Hacker)
- ✅ Module 10: Sniffing
- ✅ Module 13: Physical Security  
- ✅ Module 14: Wireless Networks
- ✅ Module 16: IoT/OT Hacking
- ✅ Module 18: Mobile Security

### OSCP (Offensive Security Certified Professional)
- Password attacks via BadUSB
- Network enumeration
- Exploit delivery mechanisms

### GPEN (GIAC Penetration Tester)
- Wireless assessment
- Physical penetration
- IoT device testing

---

## Learning Path

### Beginner (0-3 months)
1. Master basic Flipper operations
2. Complete Module 13 labs (Physical Security)
3. Practice RFID cloning
4. Learn BadUSB scripting

### Intermediate (3-6 months)
1. Module 14 labs (WiFi attacks)
2. BLE device enumeration
3. Custom app development
4. Red team scenarios

### Advanced (6-12 months)
1. Full penetration tests
2. Custom FAP development in C
3. IoT/OT security assessments
4. CEH Practical exam preparation

---

## Additional Resources

**EC-Council Official:**
- CEH v12 courseware
- iLabs (hands-on virtual labs)
- CEH Practical exam guide

**Community Resources:**
- Flipper Zero Discord
- r/flipperzero Reddit
- Hacking with Flipper Zero (YouTube)

**Books:**
- "CEH Certified Ethical Hacker All-in-One Exam Guide"
- "The Hacker Playbook 3"
- "IoT Penetration Testing Cookbook"

---

**Author:** yogeshjoga  
**For:** CEH Hardware Module  
**Version:** 1.0 (Aligned with CEH v12)  
**Last Updated:** 2026-02-14
