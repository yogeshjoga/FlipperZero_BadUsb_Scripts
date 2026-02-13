# iOS BadUSB Scripts

This folder contains BadUSB scripts for iOS devices (iOS 14+).

## Available Scripts

### 📁 Phishing
- **Safari_URL.txt** - Opens Safari to specified URL for phishing campaigns

### 🎭 Pranking
- **Siri_Activation.txt** - Activates Siri and makes requests
- **Screenshot_Spam.txt** - Takes multiple rapid screenshots

### ⚡ Command Execution
- **Note_Creator.txt** - Creates notes with automated text

## ⚠️ Important Limitations

**iOS has SEVERE BadUSB limitations:**

### Why iOS is Limited
1. **No Terminal Access** - iOS doesn't have a native terminal (without jailbreak)
2. **Locked Ecosystem** - App sandboxing prevents system-level access
3. **No Script Execution** - Cannot run bash/shell commands
4. **Limited Shortcuts** - Keyboard shortcuts are minimal
5. **Requires Unlock** - Device must be unlocked and on home screen

### What Works
- ✅ Opening apps by typing app names
- ✅ Interacting with visible UI elements
- ✅ Using Siri (if enabled)
- ✅ Taking screenshots (hardware button simulation)
- ✅ Basic text input in apps

### What Doesn't Work
- ❌ System command execution
- ❌ File system access
- ❌ Installing apps/payloads
- ❌ Extracting system information
- ❌ Network configuration changes
- ❌ Most metadata extraction

## Jailbroken Devices

**With jailbreak, possibilities expand:**
- Terminal access via NewTerm or similar
- SSH server can be installed
- System-level command execution
- File system exploration
- Advanced scripting capabilities

**However**, jailbreaking:
- Voids warranty
- Reduces security
- May cause instability
- Is increasingly difficult on newer iOS versions

## Usage Notes

- Device MUST be unlocked
- Scripts are very basic compared to other platforms
- Primarily useful for app automation, not penetration testing
- Voice control (Siri) offers some additional possibilities
- **IMPORTANT:** iOS BadUSB is mostly educational/demo purposes

## Compatibility

| iOS Version | Support | Notes |
|-------------|---------|-------|
| iOS 18 | ⚠️ | Very limited, basic app interaction only |
| iOS 17 | ⚠️ | Very limited, basic app interaction only |
| iOS 16 | ⚠️ | Very limited, basic app interaction only |
| iOS 15 | ⚠️ | Very limited, basic app interaction only |
| iOS 14 | ⚠️ | Very limited, basic app interaction only |

## Recommendations

**For iOS testing, consider:**
- Social engineering approaches instead
- Physical device access for configuration
- iCloud/account-based attacks
- Web-based phishing (works on any platform)
- Focus efforts on macOS instead (same ecosystem, better access)

## Security Notes

⚠️ **For authorized testing only - iOS scripts are primarily educational**
