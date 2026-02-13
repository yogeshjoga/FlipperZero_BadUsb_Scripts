# Browser Sync FAP Application

**CEH Module 13 - Physical Security | Advanced Data Exfiltration**

## Overview

A Flipper Zero FAP (Flipper Application Package) that provides an interactive GUI for setting up automated browser data exfiltration to Gmail.

## Features

✅ **Interactive GUI**
- Text input for Gmail address
- Text input for Gmail App Password
- Confirmation screen before execution

✅ **Automated BadUSB Payload**
- Creates PowerShell sync script
- Sets up Windows Task Scheduler
- Runs every 10 minutes
- Persistent (survives reboot)

✅ **Data Collection**
- Chrome passwords & history
- Edge passwords & history
- Firefox passwords & history
- System information

✅ **Gmail Integration**
- SMTP email delivery
- Automatic compression
- Timestamped archives

---

## Installation

### Method 1: Pre-compiled FAP

1. Download `browser_sync.fap`
2. Copy to Flipper SD card: `/ext/apps/BadUSB/`
3. Navigate to Apps → BadUSB → Browser Sync

### Method 2: Compile from Source

```bash
# Clone Flipper firmware
git clone --recursive https://github.com/flipperdevices/flipperzero-firmware.git
cd flipperzero-firmware

# Copy app to user apps
cp -r FAP_Apps/Custom_Apps/Browser_Sync applications_user/

# Build
./fbt fap_browser_sync

# Output: dist/f7-D/apps/BadUSB/browser_sync.fap
```

---

## Usage

### Step 1: Prepare Gmail

1. Go to https://myaccount.google.com/security
2. Enable 2-Step Verification
3. Create App Password:
   - App: Mail
   - Device: Windows Computer
4. **Save the 16-character password**

### Step 2: Launch App

1. On Flipper: Apps → BadUSB → Browser Sync
2. Connect Flipper to target Windows PC
3. Follow on-screen prompts

### Step 3: Enter Credentials

**Screen 1: Email Input**
```
┌────────────────────────┐
│ Enter Gmail Address    │
│                        │
│ ┌────────────────────┐ │
│ │your@gmail.com      │ │
│ └────────────────────┘ │
│                        │
│ OK:Next  Back:Cancel   │
└────────────────────────┘
```

**Screen 2: Password Input**
```
┌────────────────────────┐
│ Enter App Password     │
│                        │
│ ┌────────────────────┐ │
│ │abcd efgh ijkl mnop │ │
│ └────────────────────┘ │
│                        │
│ OK:Next  Back:Cancel   │
└────────────────────────┘
```

**Screen 3: Confirmation**
```
┌────────────────────────┐
│ Browser Sync Setup     │
│                        │
│ Email: your@gmail.com  │
│ Password: ******       │
│                        │
│ Ready to execute       │
│ OK:Run  Back:Cancel    │
└────────────────────────┘
```

### Step 4: Execution

**Screen 4: Running**
```
┌────────────────────────┐
│ Executing Payload      │
│                        │
│ Creating sync script...│
│ Setting up scheduler...│
│ Please wait...         │
│                        │
│                        │
└────────────────────────┘
```

**LED:** Blinking cyan during execution

### Step 5: Complete

**Screen 5: Success**
```
┌────────────────────────┐
│ Setup Complete!        │
│                        │
│ Scheduled task created │
│ Syncs every 10 minutes │
│ Check your Gmail!      │
│                        │
│ Back:Exit              │
└────────────────────────┘
```

**LED:** Success pattern (green blink)

---

## What Gets Created

### Files on Target PC

**Location:** `%APPDATA%\BrowserSync\`

```
BrowserSync/
├── BrowserSync.ps1    (PowerShell extraction script)
└── RunSync.bat        (Batch wrapper)
```

### Scheduled Task

**Name:** `BrowserSyncService`
**Trigger:** Every 10 minutes
**Action:** Run `%APPDATA%\BrowserSync\RunSync.bat`
**Settings:**
- Start when available
- Run on battery power
- Run only if network available

---

## Expected Results

### Gmail Inbox

Every 10 minutes you'll receive:

```
From: your@gmail.com
To: your@gmail.com
Subject: Browser Sync - DESKTOP-PC - 2026-02-14 01:30

Body:
Automated sync from DESKTOP-PC (Username)

Attachment: BrowserData_20260214_013045.zip
```

### Archive Contents

```
BrowserData_20260214_013045.zip
├── chrome_pass.db
├── chrome_hist.db
├── edge_pass.db
├── edge_hist.db
└── info.txt
```

---

## Advantages Over BadUSB Script

| Feature | BadUSB Script | FAP App |
|---------|---------------|---------|
| Gmail input | Manual typing | GUI text input |
| Password input | Manual typing | GUI text input |
| Visual feedback | None | LED + screen |
| Error handling | Limited | Better |
| User experience | Command-line | Interactive GUI |
| Portability | Requires editing | Self-contained |

---

## Troubleshooting

### App won't compile

**Error:** Missing dependencies
**Solution:**
```bash
cd flipperzero-firmware
git submodule update --init --recursive
./fbt
```

### HID not connecting

**Error:** Flipper not recognized as keyboard
**Solution:**
- Ensure USB HID is enabled in Flipper settings
- Try reconnecting USB
- Restart Flipper

### Text input not working

**Solution:**
- Use physical Flipper buttons to type
- OK button confirms
- Back button cancels

### Payload execution fails

**Possible causes:**
1. PowerShell execution policy
2. Antivirus blocking
3. Insufficient permissions

**Check logs:**
```bash
# On Flipper via qFlipper CLI
qFlipper-cli --log
```

---

## Security Warnings

⚠️ **CRITICAL: Authorized Use Only**

This tool is **EXTREMELY POWERFUL** and can:
- Extract all browser passwords
- Maintain persistent access
- Operate covertly

**Legal usage:**
- ✅ Your own device
- ✅ Authorized penetration test
- ✅ Security research (lab environment)

**ILLEGAL usage:**
- ❌ Unauthorized access
- ❌ Workplace without permission
- ❌ Any system you don't own

**Penalties for misuse:**
- Criminal prosecution
- Heavy fines
- Imprisonment

---

## Detection & Countermeasures

### Detection Methods

**Endpoint Detection:**
- Task Scheduler monitoring (SIEM)
- PowerShell script analysis (EDR)
- SMTP traffic to Gmail (network monitoring)

**Manual Detection:**
```powershell
# Check for scheduled task
Get-ScheduledTask -TaskName "BrowserSyncService"

# Check for files
dir $env:APPDATA\BrowserSync
```

### Countermeasures

**For Organizations:**
1. USB port restrictions (Device Guard)
2. Task Scheduler monitoring alerts
3. Block SMTP to external addresses
4. PowerShell logging (ScriptBlock logging)
5. Endpoint Detection and Response (EDR)

**For Users:**
1. Don't leave PC unlocked
2. Physical security awareness
3. Review scheduled tasks periodically
4. Use security keys (YubiKey) instead of passwords

---

## Red Team Usage

### Engagement Scenario

**Target:** Windows workstation
**Objective:** Establish persistent data exfiltration
**Tool:** Browser Sync FAP app

**Steps:**
1. Gain physical access
2. Connect Flipper Zero
3. Launch Browser Sync app
4. Enter attacker Gmail
5. Enter App Password
6. Execute payload
7. Disconnect Flipper
8. Monitor Gmail for data

**Success Criteria:**
- Scheduled task created ✓
- Initial data received ✓
- Persistent sync confirmed ✓
- No detection alerts ✓

### Reporting

```markdown
## Finding: Persistent Browser Data Exfiltration

**Severity:** CRITICAL

**Description:**
Successfully deployed persistent data exfiltration payload via USB BadUSB attack. System continues to send browser credentials and history every 10 minutes.

**Impact:**
- All saved passwords compromised
- Browsing history exposed
- Persistent backdoor established

**Proof:**
- Screenshot of scheduler task
- Email with browser data archive
- Network capture of SMTP traffic

**Recommendations:**
1. Implement USB port restrictions
2. Deploy EDR with USB HID monitoring
3. Enable PowerShell transcription logging
4. User security awareness training
```

---

## Comparison: Script vs FAP

### BadUSB Script (.txt)
**Pros:**
- Simple text file
- Easy to edit
- No compilation needed

**Cons:**
- Requires manual credential entry
- No visual feedback
- Hard to reuse with different emails

### FAP Application (browser_sync.fap)
**Pros:**
- ✅ Interactive GUI
- ✅ Reusable (enter new creds each time)
- ✅ Visual feedback (LED + screen)
- ✅ Better error handling
- ✅ Professional appearance

**Cons:**
- Requires compilation
- Larger file size
- More complex codebase

---

## Future Enhancements

Potential improvements:
- [ ] Support for more browsers (Opera, Brave)
- [ ] Configurable sync interval
- [ ] Webhook support (Discord, Slack)
- [ ] Screenshot capture
- [ ] Keylogger integration
- [ ] C2 callback support

---

## Credits

**Author:** yogeshjoga
**Based on:** BadUSB Browser Sync Script
**Inspired by:** Hak5 Rubber Ducky payloads
**Platform:** Flipper Zero

---

## License

MIT License - Use responsibly and legally

---

## Support

- 🐙 GitHub: https://github.com/yogeshjoga/
- 💼 LinkedIn: https://www.linkedin.com/in/yogeshjoga/
- 📧 Email: jogayogeshedu@gmail.com

---

**Remember: With great power comes great responsibility. Use ethically!**
