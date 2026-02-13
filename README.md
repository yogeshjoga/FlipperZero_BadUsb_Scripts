# 🐬 Flipper Zero BadUSB Scripts Collection

<div align="center">

![Flipper Zero](https://img.shields.io/badge/Flipper-Zero-orange?style=for-the-badge)
![BadUSB](https://img.shields.io/badge/BadUSB-Scripts-red?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**A comprehensive collection of BadUSB scripts for Flipper Zero - inspired by Hak5 Rubber Ducky**

</div>

---

## 📋 Table of Contents

- [About](#about)
- [Supported Platforms](#supported-platforms)
- [Script Categories](#script-categories)
- [Installation](#installation)
- [Usage](#usage)
- [Script Structure](#script-structure)
- [Contributing](#contributing)
- [Disclaimer](#disclaimer)
- [Credits](#credits)

---

## 🎯 About

This repository contains a curated collection of **BadUSB scripts** for the Flipper Zero device. These scripts leverage the BadUSB attack vector to emulate keyboard inputs, allowing for automated command execution across multiple operating systems.

**Flipper Zero** is a portable multi-tool for pentesters and hardware enthusiasts. Its BadUSB functionality allows it to act as a USB Human Interface Device (HID), making it appear as a keyboard to target systems.

> **Inspired by Hak5 Rubber Ducky** - These scripts follow similar syntax and principles used in Rubber Ducky payloads, adapted for Flipper Zero's DuckyScript implementation.

---

## 💻 Supported Platforms

Our scripts are compatible with the following operating systems:

| Platform | Support | Notes |
|----------|---------|-------|
| 🪟 **Windows** | ✅ Full | Windows 10/11, PowerShell & CMD |
| 🍎 **macOS** | ✅ Full | macOS 10.15+ (Catalina and newer) |
| 🐧 **Linux** | ✅ Full | Ubuntu, Debian, Fedora, Arch, Kali |
| 🤖 **Android** | ✅ Full | Android 8.0+ with USB debugging |
| 📱 **iOS** | ⚠️ Limited | Requires jailbreak for advanced features |

---

## 📂 Script Categories

### 🎣 Phishing
Scripts designed to harvest credentials, create fake login prompts, and social engineering attacks.

- **Fake Login Prompts** - Credential harvesting via mimicked system dialogs
- **DNS Spoofing** - Redirect users to phishing sites
- **Email Harvesters** - Extract email credentials and session tokens
- **WiFi Password Grabbers** - Retrieve saved wireless passwords

### 🎭 Pranking
Harmless (but annoying) scripts for educational purposes and demonstrations.

- **Wallpaper Changers** - Replace desktop wallpapers
- **Mouse Jiggler** - Random mouse movements
- **Text Bombs** - Spam text messages
- **Browser Pranks** - Open multiple tabs/windows
- **Volume Controllers** - Randomly adjust system volume

### 💉 Payload Installation
Scripts that download and execute payloads from remote servers.

- **Reverse Shell Deployers** - Establish remote connections
- **Backdoor Installers** - Create persistent access points
- **Keylogger Deployment** - Install keystroke logging software
- **RAT Installation** - Remote Administration Tools setup

### 🔗 URL-Based Application Installation
Scripts that install applications directly from web sources.

- **Package Managers** - Auto-install via apt, brew, chocolatey
- **Direct Downloads** - Download and execute installers
- **Script Runners** - Execute remote PowerShell/Bash scripts
- **Browser Extensions** - Install browser add-ons automatically

### ⚡ Command Execution
Execute system commands for reconnaissance and system manipulation.

- **System Information Gathering** - Collect OS, hardware, network data
- **Network Scanners** - Enumerate network resources
- **Registry Modifications** - Windows registry changes
- **Service Manipulation** - Start/stop system services
- **User Account Control** - Create/modify user accounts

### 📊 Metadata Extraction
Gather device and system information for reconnaissance.

- **System Profiling** - OS version, installed software, drivers
- **Network Configuration** - IP addresses, MAC addresses, DNS
- **WiFi Network Lists** - Previously connected networks
- **Browser History** - Extract browsing data
- **File System Enumeration** - Document structure analysis
- **Credential Extraction** - Saved passwords and tokens

---

## 🔧 Installation

### Prerequisites
- **Flipper Zero** device with latest firmware
- **qFlipper** or compatible software for file transfer
- USB cable for connecting Flipper Zero to your computer

### Steps

1. **Clone this repository:**
   ```bash
   git clone https://github.com/yourusername/FlipperZero_BadUsb_Scripts.git
   cd FlipperZero_BadUsb_Scripts
   ```

2. **Connect your Flipper Zero** via USB to your computer

3. **Transfer scripts** to your Flipper Zero:
   - Open qFlipper application
   - Navigate to `SD Card/badusb/`
   - Copy desired `.txt` script files to this directory

4. **Safely eject** your Flipper Zero

---

## 🚀 Usage

### Basic Workflow

1. **Navigate** to `BadUSB` app on your Flipper Zero
2. **Select** the desired script from the list
3. **Connect** Flipper Zero to target device via USB
4. **Execute** the script by pressing the OK button
5. **Wait** for the script to complete execution

### Script Execution Tips

- ⏱️ **Timing is crucial** - Ensure scripts have appropriate delays for system response times
- 🎯 **Test first** - Always test scripts in a controlled environment
- 🔄 **Customize** - Modify scripts for specific target configurations
- 📝 **Document** - Keep notes on successful configurations

### Example: Running a Windows Info Gathering Script

```
1. Plug Flipper Zero into Windows PC
2. Navigate to BadUSB app
3. Select "Windows/System_Info.txt"
4. Press OK to execute
5. Script will open PowerShell and gather system information
6. Results saved to target system or exfiltrated
```

---

## 📝 Script Structure

Flipper Zero BadUSB scripts use **DuckyScript** syntax. Here's a basic example:

```duckyscript
REM This is a comment explaining what the script does
DELAY 1000
GUI r
DELAY 500
STRING notepad
ENTER
DELAY 750
STRING Hello from Flipper Zero!
ENTER
```

### Common Commands

| Command | Description | Example |
|---------|-------------|---------|
| `REM` | Comment (ignored during execution) | `REM This opens notepad` |
| `DELAY` | Wait specified milliseconds | `DELAY 1000` (1 second) |
| `STRING` | Type text string | `STRING hello world` |
| `ENTER` | Press Enter key | `ENTER` |
| `GUI` | Windows/CMD key | `GUI r` (Win + R) |
| `CTRL` | Control key modifier | `CTRL c` (Copy) |
| `ALT` | Alt key modifier | `ALT F4` (Close window) |
| `SHIFT` | Shift key modifier | `SHIFT HOME` |
| `TAB` | Tab key | `TAB` |

### Platform-Specific Shortcuts

**Windows:**
- `GUI r` - Run dialog
- `GUI` - Start menu
- `CTRL-SHIFT ESC` - Task Manager

**macOS:**
- `GUI SPACE` - Spotlight
- `GUI t` - Terminal (in some apps)
- `COMMAND` - CMD key (same as GUI)

**Linux:**
- `CTRL-ALT t` - Terminal
- `ALT F2` - Run dialog (varies by DE)

---

## 🤝 Contributing

We welcome contributions! Here's how you can help:

### Adding New Scripts

1. **Fork** this repository
2. **Create** a new branch (`git checkout -b feature/new-script`)
3. **Add** your script in the appropriate category folder
4. **Test** thoroughly on target platform(s)
5. **Document** the script with clear comments
6. **Commit** your changes (`git commit -am 'Add new script: description'`)
7. **Push** to the branch (`git push origin feature/new-script`)
8. **Create** a Pull Request

### Script Guidelines

- ✅ Include clear `REM` comments explaining functionality
- ✅ Test on actual hardware before submitting
- ✅ Specify target OS and version in script header
- ✅ Use appropriate delays for reliability
- ✅ Follow existing naming conventions
- ✅ Provide usage documentation

### Reporting Issues

Found a bug or have a suggestion? [Open an issue](../../issues) with:
- Script name and category
- Target platform and version
- Expected vs. actual behavior
- Steps to reproduce

---

## ⚠️ Disclaimer

> **FOR EDUCATIONAL AND SECURITY RESEARCH PURPOSES ONLY**

This repository and its contents are provided for **educational purposes**, **authorized security testing**, and **research** only. 

### Legal Notice

- 🚫 **Unauthorized access** to computer systems is illegal
- 🚫 **Do not use** these scripts on systems you don't own or have explicit permission to test
- 🚫 **We are not responsible** for misuse or damages caused by these scripts
- ✅ **Always obtain written authorization** before testing
- ✅ **Follow** all applicable laws and regulations

### Ethical Usage

By using these scripts, you agree to:
- Only use on systems you own or have explicit permission to test
- Comply with all local, state, and federal laws
- Take full responsibility for your actions
- Use knowledge gained for defensive security purposes

**The authors and contributors are not liable for any misuse or damage caused by these scripts.**

---

## 🎓 Credits

### Inspiration
- **[Hak5](https://hak5.org/)** - For pioneering USB Rubber Ducky and DuckyScript
- **[Flipper Zero Team](https://flipperzero.one/)** - For creating an amazing multi-tool
- **Security Research Community** - For continuous innovation

### Resources
- [Flipper Zero Official Documentation](https://docs.flipperzero.one/)
- [DuckyScript Documentation](https://docs.hak5.org/hak5-usb-rubber-ducky/)
- [Awesome Flipper Zero](https://github.com/djsime1/awesome-flipperzero)

### Contributors
Thanks to all contributors who have helped build this collection! 🙏

---

## 📜 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

---

## 📞 Contact

Have questions or suggestions? 

- 🐛 **Issues**: [GitHub Issues](../../issues)
- 💬 **Discussions**: [GitHub Discussions](../../discussions)
- � **GitHub**: [yogeshjoga](https://github.com/yogeshjoga/)
- 💼 **LinkedIn**: [yogeshjoga](https://www.linkedin.com/in/yogeshjoga/)
- 📧 **Email**: jogayogeshedu@gmail.com

---

<div align="center">

**⭐ If you find this repository useful, please give it a star! ⭐**

Made with ❤️ by the security research community

**Happy (Ethical) Hacking! 🐬**

</div>
