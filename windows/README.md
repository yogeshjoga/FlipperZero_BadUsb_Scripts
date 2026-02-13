# Windows BadUSB Scripts

This folder contains BadUSB scripts specifically designed for Windows 10/11 systems.

## Available Scripts

### 📁 Phishing
- **Fake_Windows_Login.txt** - Creates fake Windows security prompt to capture credentials

### 🎭 Pranking
- **Wallpaper_Changer.txt** - Changes desktop wallpaper to random image from internet

### 💉 Payload Installation
- **Reverse_Shell.txt** - Establishes PowerShell reverse shell connection (requires IP/port configuration)

### ⚡ Command Execution
- **System_Info.txt** - Gathers comprehensive system information including hardware and network details

### 📊 Metadata Extraction
- **WiFi_Password_Grabber.txt** - Extracts all saved WiFi network passwords
- **Browser_History.txt** - Copies Chrome browser history database

### 🔗 URL-Based Installation
- **App_Installer.txt** - Downloads and silently installs applications from URL

## Usage Notes

- Most scripts use PowerShell with hidden windows
- Default keyboard shortcut: `WIN + R` to open Run dialog
- Scripts typically wait 1-2 seconds for system responses
- **IMPORTANT:** Test in controlled environment first
- Some scripts require customization (IP addresses, URLs, etc.)

## Security Notes

⚠️ **These scripts are for authorized testing only**
- Requires appropriate permissions
- May trigger antivirus/EDR solutions
- Use responsibly and legally
