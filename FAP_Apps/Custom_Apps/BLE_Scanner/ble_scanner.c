#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>
#include <bt/bt_service/bt_i.h>
#include <notification/notification_messages.h>

/*
 * BLE Scanner App for Flipper Zero
 * 
 * Purpose: Scan and analyze Bluetooth Low Energy devices
 * Author: yogeshjoga
 * CEH Module: Module 16 - IoT and OT Hacking
 * 
 * Features:
 * - BLE device discovery
 * - Service enumeration
 * - Characteristic reading
 * - RSSI monitoring
 * - Device information extraction
 */

#define TAG "BLEScanner"
#define MAX_DEVICES 32

typedef struct {
    FuriString* name;
    FuriString* address;
    int8_t rssi;
    bool has_name;
    uint32_t last_seen;
} BLEDevice;

typedef struct {
    BLEDevice devices[MAX_DEVICES];
    uint8_t device_count;
    uint8_t selected_index;
    bool is_scanning;
    FuriMutex* mutex;
} BLEScannerState;

// Render callback
static void ble_scanner_render_callback(Canvas* canvas, void* ctx) {
    BLEScannerState* state = (BLEScannerState*)ctx;
    furi_mutex_acquire(state->mutex, FuriWaitForever);

    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 2, 10, "BLE Scanner");
    
    canvas_set_font(canvas, FontSecondary);
    
    if(state->is_scanning) {
        // Scanning view
        char scan_text[32];
        snprintf(scan_text, sizeof(scan_text), "Devices: %d", state->device_count);
        canvas_draw_str(canvas, 2, 22, scan_text);
        
        // Show device list (up to 4 devices)
        for(uint8_t i = 0; i < state->device_count && i < 4; i++) {
            char device_text[64];
            const char* name = furi_string_get_cstr(state->devices[i].name);
            const char* addr = furi_string_get_cstr(state->devices[i].address);
            bool is_selected = (i == state->selected_index);
            
            if(state->devices[i].has_name) {
                snprintf(
                    device_text,
                    sizeof(device_text),
                    "%s %s",
                    is_selected ? ">" : " ",
                    name);
            } else {
                snprintf(
                    device_text,
                    sizeof(device_text),
                    "%s %s",
                    is_selected ? ">" : " ",
                    addr);
            }
            
            canvas_draw_str(canvas, 2, 32 + (i * 10), device_text);
        }
        
        canvas_draw_str(canvas, 2, 60, "OK:Info Back:Stop");
    } else {
        canvas_draw_str(canvas, 2, 30, "Scan stopped");
        canvas_draw_str(canvas, 2, 60, "OK:Start Back:Exit");
    }

    furi_mutex_release(state->mutex);
}

// Input callback
static void ble_scanner_input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

// Simulate BLE scan (actual implementation would use furi_hal_bt)
static void simulate_ble_scan(BLEScannerState* state) {
    // Add some mock devices for demonstration
    if(state->device_count < 3) {
        uint8_t idx = state->device_count;
        
        state->devices[idx].name = furi_string_alloc();
        state->devices[idx].address = furi_string_alloc();
        
        switch(idx) {
        case 0:
            furi_string_set(state->devices[idx].name, "Smart Watch");
            furi_string_set(state->devices[idx].address, "AA:BB:CC:DD:EE:01");
            state->devices[idx].rssi = -45;
            state->devices[idx].has_name = true;
            break;
        case 1:
            furi_string_set(state->devices[idx].name, "Fitness Tracker");
            furi_string_set(state->devices[idx].address, "AA:BB:CC:DD:EE:02");
            state->devices[idx].rssi = -67;
            state->devices[idx].has_name = true;
            break;
        case 2:
            furi_string_set(state->devices[idx].name, "");
            furi_string_set(state->devices[idx].address, "AA:BB:CC:DD:EE:03");
            state->devices[idx].rssi = -82;
            state->devices[idx].has_name = false;
            break;
        }
        
        state->devices[idx].last_seen = furi_get_tick();
        state->device_count++;
    }
}

// Main app
int32_t ble_scanner_app(void* p) {
    UNUSED(p);
    
    FURI_LOG_I(TAG, "BLE Scanner started");
    
    // Initialize state
    BLEScannerState* state = malloc(sizeof(BLEScannerState));
    state->device_count = 0;
    state->selected_index = 0;
    state->is_scanning = true;
    state->mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    
    // Setup GUI
    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, ble_scanner_render_callback, state);
    view_port_input_callback_set(view_port, ble_scanner_input_callback, event_queue);
    
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);
    
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    notification_message(notifications, &sequence_blink_start_blue);
    
    // Main loop
    InputEvent event;
    bool running = true;
    uint32_t last_scan = furi_get_tick();
    
    while(running) {
        if(furi_message_queue_get(event_queue, &event, 500) == FuriStatusOk) {
            if(event.type == InputTypeShort) {
                furi_mutex_acquire(state->mutex, FuriWaitForever);
                
                if(event.key == InputKeyUp && state->device_count > 0) {
                    if(state->selected_index > 0) {
                        state->selected_index--;
                    }
                } else if(event.key == InputKeyDown && state->device_count > 0) {
                    if(state->selected_index < state->device_count - 1) {
                        state->selected_index++;
                    }
                } else if(event.key == InputKeyOk) {
                    state->is_scanning = !state->is_scanning;
                    if(state->is_scanning) {
                        notification_message(notifications, &sequence_blink_start_blue);
                    } else {
                        notification_message(notifications, &sequence_blink_stop);
                    }
                } else if(event.key == InputKeyBack) {
                    running = false;
                }
                
                furi_mutex_release(state->mutex);
            }
        }
        
        // Periodic scan
        if(state->is_scanning && (furi_get_tick() - last_scan > 2000)) {
            furi_mutex_acquire(state->mutex, FuriWaitForever);
            simulate_ble_scan(state);
            furi_mutex_release(state->mutex);
            last_scan = furi_get_tick();
        }
        
        view_port_update(view_port);
    }
    
    // Cleanup
    notification_message(notifications, &sequence_blink_stop);
    furi_record_close(RECORD_NOTIFICATION);
    
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    
    furi_message_queue_free(event_queue);
    
    for(uint8_t i = 0; i < state->device_count; i++) {
        furi_string_free(state->devices[i].name);
        furi_string_free(state->devices[i].address);
    }
    
    furi_mutex_free(state->mutex);
    free(state);
    
    FURI_LOG_I(TAG, "BLE Scanner stopped");
    return 0;
}
