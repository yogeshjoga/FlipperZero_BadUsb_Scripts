# macOS BadUSB Scripts

This folder contains BadUSB scripts for macOS systems (10.15 Catalina and newer).

## Available Scripts

### 📁 Phishing
- **Keychain_Prompt.txt** - Creates fake macOS keychain unlock dialog

### 🎭 Pranking
- **Volume_Troll.txt** - Sets volume to maximum and uses text-to-speech

### 💉 Payload Installation
- **Reverse_Shell.txt** - Establishes bash reverse shell connection (requires IP/port configuration)

### ⚡ Command Execution
- **System_Info.txt** - Gathers hardware and software information using system_profiler

### 📊 Metadata Extraction
- **WiFi_Info.txt** - Extracts WiFi network information and configurations

### 🔗 URL-Based Installation
- **Homebrew_Installer.txt** - Installs packages via Homebrew (requires Homebrew installed)

## Usage Notes

- Default launcher: `CMD + SPACE` (Spotlight)
- Terminal application name: "terminal"
- Uses osascript for AppleScript automation
- Some scripts leverage built-in `say` command
- **IMPORTANT:** macOS security features may prompt for permissions

## macOS Security Considerations

⚠️ **Recent macOS versions have enhanced security:**
- System Integrity Protection (SIP)
- Gatekeeper restrictions
- Terminal access permissions required
- Notarization requirements for apps

## Compatibility

| macOS Version | Support | Notes |
|---------------|---------|-------|
| macOS 15 Sequoia | ✅ | Full support |
| macOS 14 Sonoma | ✅ | Full support |
| macOS 13 Ventura | ✅ | Full support |
| macOS 12 Monterey | ✅ | Full support |
| macOS 11 Big Sur | ✅ | Full support |
| macOS 10.15 Catalina | ✅ | Full support |

## Security Notes

⚠️ **For authorized security testing only**
