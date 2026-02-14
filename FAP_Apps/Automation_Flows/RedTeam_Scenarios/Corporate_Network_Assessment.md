# Red Team Penetration Testing Workflow

## Scenario: Corporate Network Assessment

**Objective:** Test physical and network security of target organization  
**Duration:** 2-4 hours  
**Team Size:** 1-2 operators  
**Flipper Apps Used:** WiFi Deauth, BLE Scanner, RFID Cloner, BadUSB

---

## Phase 1: Reconnaissance (30 minutes)

### External Survey
```
Tools: BLE Scanner, WiFi viewing (passive)
Location: Parking lot / nearby area
```

**Actions:**
1. Launch BLE Scanner app
2. Identify IoT devices (sensors, beacons, smart locks)
3. Note device names and MAC addresses
4. Scan for WiFi networks (passive observation)
5. Document SSID names, signal strength
6.Create target list based on security posture

**Deliverables:**
- List of BLE devices with metadata
- WiFi network inventory
- Target prioritization matrix

---

## Phase 2: Physical Access (45 minutes)

### Badge Cloning Attempt
```
Tools: RFID Cloner
Location: Building entrance
```

**Actions:**
1. Observe employees using RFID badges
2. Position near card readers during busy hours
3. Attempt to clone badge via proximity (if feasible)
4. Test cloned badge on reader
5. Document access level granted

**Alternative: Tailgating**
- Follow authorized employee
- Use social engineering techniques
- Document success rate

**Deliverables:**
- Access badge clone (if successful)
- Physical security assessment report
- Photos/notes on security controls

---

## Phase 3: Network Access (60 minutes)

### WiFi Network Compromise
```
Tools: WiFi Deauth, BadUSB
Location: Inside facility or nearby
```

**Actions:**
1. Identify target WiFi network (corporate SSID)
2. Launch WiFi Deauth app
3. Select target AP on most active channel
4. Execute deauth attack for 2-3 minutes
5. Capture WPA2 handshakes (external tool)
6. Document network security mechanisms

**USB Attack Vector:**
1. Locate unattended workstation
2. Connect Flipper via USB
3. Execute BadUSB payload:
   - Credential harvester
   - Reverse shell installer
   - Data exfiltration script
4. Establish C2 connection
5. Perform lateral movement

**Deliverables:**
- Captured handshakes for offline cracking
-  Network access credentials (if obtained)
- C2 beacon confirmation
- Screenshot evidence

---

## Phase 4: IoT Exploitation (45 minutes)

### BLE Device Analysis
```
Tools: BLE Scanner
Location: Conference rooms, IoT device areas
```

**Actions:**
1. Scan for BLE devices (smart TVs, speakers, locks)
2. Enumerate GATT services and characteristics
3. Attempt to read unprotected characteristics
4. Test for default credentials/PINs
5. Try pairing with devices
6. Document vulnerabilities

**Common Targets:**
- Smart TVs (Samsung, LG)
- Conference room equipment
- Smart locks (August, Schlage)
- IoT sensors
- Wireless keyboards/mice

**Deliverables:**
- BLE device vulnerability report
- Exploitable devices list
- Proof-of-concept exploits

---

## Phase 5: Data Collection (30 minutes)

### Information Gathering
```
Tools: All previous + documentation
Location: Throughout facility
```

**Actions:**
1. Photograph network infrastructure
2. Document wireless access points
3. Note security cameras and blind spots
4. Identify badge reader models
5. Screenshot system configs (if access obtained)
6. Collect printed materials from printers/desks

**Data Points:**
- Network diagrams
- Employee names/emails
- Internal IP ranges
- Software versions
- Security tool inventory

**Deliverables:**
- Photo documentation  
- Network topology map
- Asset inventory
- Security control matrix

---

## Phase 6: Exfiltration & Cleanup (15 minutes)

### Data Exfiltration
```
Tools: BadUSB (if access obtained)
Method: Covert channels
```

**Actions:**
1. Compress collected data
2. Upload to C2 server or cloud storage
3. Verify data integrity
4. Remove traces:
   - Delete temp files
   - Clear command history
   - Remove payloads
   - Disconnect C2

**Cleanup Checklist:**
- [ ] Remove all installed software/scripts
- [ ] Clear browser history
- [ ] Delete temp files
- [ ] Wipe USB autorun remnants
- [ ] Disconnect all connections
- [ ] Exit facility properly

**Deliverables:**
- Exfiltrated data package
- Verification of cleanup
- Exit documentation

---

## Phase 7: Reporting (Post-Op)

### Report Structure

**Executive Summary**
- Engagement scope
- Key findings
- Risk rating
- Recommendations

**Technical Findings**
1. Physical Security
   - Badge cloning success/failure
   - Tailgating opportunities
   - Camera blind spots

2. Network Security
   - WiFi encryption status
   - Deauth attack effectiveness
   - Captured credentials

3. Endpoint Security
   - BadUSB effectiveness
   - AV/EDR detection
   - User awareness

4. IoT Security
   - Vulnerable BLE devices
   - Default credentials
   - Unpatched firmware

**Recommendations**
- Implement 802.11w (PMF)
- Badge + PIN for access
- USB port restrictions
- BLE device segmentation
- Security awareness training

**Appendices**
- Evidence screenshots
- Network captures
- Device listings
- Tool configurations

---

## Success Metrics

| Metric | Target | Actual |
|--------|--------|--------|
| BLE devices discovered | >10 | ___ |
| Vulnerable BLE devices | >2 | ___ |
| WiFi handshakes captured | >1 | ___ |
| Physical access obtained | Yes | ___ |
| System access obtained | Yes | ___ |
| Data exfiltrated | >1MB | ___ |

---

## Safety & Legal

**Before Starting:**
- ✅ Obtain written authorization (Rules of Engagement)
- ✅ Define scope boundaries
- ✅ Establish communication plan
- ✅ Set emergency contacts
- ✅ Review legal protections

**During Engagement:**
- 🔒 Stay within scope
- 🔒 Don't cause damage/disruption
- 🔒 Maintain operational security
- 🔒 Document everything
- 🔒 Report critical findings immediately

**After Engagement:**
- 📄 Secure all data
- 📄 Destroy unnecessary copies
- 📄 Deliver final report
- 📄 Conduct debrief session

---

## Tools Checklist

**Flipper Zero:**
- [ ] Fully charged
- [ ] SD card with latest apps
- [ ] WiFi Deauth app
- [ ] BLE Scanner app
- [ ] RFID Cloner app
- [ ] BadUSB payloads loaded

**Supporting Equipment:**
- [ ] Laptop with Kali Linux
- [ ] WiFi adapter (monitor mode)
- [ ] Extra batteries
- [ ] USB cables/adapters
- [ ] Notebook for documentation
- [ ] Camera for evidence

**Software:**
- [ ] Hashcat (handshake cracking)
- [ ] Wireshark (packet analysis)
- [ ] C2 framework (Metasploit/Cobalt Strike)
- [ ] Reporting tools

---

**Created by:** yogeshjoga  
**For:** CEH Hardware Module & Red Team Operations  
**Version:** 1.0  
**Last Updated:** 2026-02-14
