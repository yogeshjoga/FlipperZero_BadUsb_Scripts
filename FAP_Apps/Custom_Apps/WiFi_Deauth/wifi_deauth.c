#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>
#include <notification/notification_messages.h>

/*
 * WiFi Deauth App for Flipper Zero
 * 
 * Purpose: Perform WiFi deauthentication attacks for security testing
 * Author: yogeshjoga
 * CEH Module: Module 14 - Hacking Wireless Networks
 * 
 * WARNING: For authorized testing only. Unauthorized deauth attacks are illegal.
 * 
 * Features:
 * - Scan WiFi networks
 * - Select target AP
 * - Send deauth frames
 * - Monitor attack status
 * 
 * Hardware Requirements:
 * - Flipper Zero with ESP32 WiFi module
 * - Or external WiFi adapter via GPIO
 */

#define TAG "WiFiDeauth"

typedef enum {
    EventTypeTick,
    EventTypeKey,
} EventType;

typedef struct {
    EventType type;
    InputEvent input;
} PluginEvent;

typedef enum {
    ViewScanning,
    ViewTargetSelect,
    ViewAttacking,
    ViewResults,
} ViewState;

typedef struct {
    FuriString* ssid;
    uint8_t channel;
    int8_t rssi;
    uint8_t bssid[6];
} WiFiNetwork;

typedef struct {
    ViewState view_state;
    FuriMutex* mutex;
    WiFiNetwork networks[16];
    uint8_t network_count;
    uint8_t selected_index;
    uint32_t packets_sent;
    bool is_attacking;
} WiFiDeauthState;

// Function prototypes
static void wifi_deauth_render_callback(Canvas* canvas, void* ctx);
static void wifi_deauth_input_callback(InputEvent* input_event, void* ctx);
static void scan_wifi_networks(WiFiDeauthState* state);
static void send_deauth_packet(WiFiDeauthState* state);

// Render callback - draws UI
static void wifi_deauth_render_callback(Canvas* canvas, void* ctx) {
    WiFiDeauthState* state = (WiFiDeauthState*)ctx;
    furi_mutex_acquire(state->mutex, FuriWaitForever);

    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);

    switch(state->view_state) {
    case ViewScanning:
        canvas_draw_str(canvas, 2, 10, "WiFi Deauth - Scanning");
        canvas_set_font(canvas, FontSecondary);
        
        char scan_text[32];
        snprintf(scan_text, sizeof(scan_text), "Networks found: %d", state->network_count);
        canvas_draw_str(canvas, 2, 25, scan_text);
        
        canvas_draw_str(canvas, 2, 40, "Scanning for APs...");
        canvas_draw_str(canvas, 2, 55, "Press OK when done");
        break;

    case ViewTargetSelect:
        canvas_draw_str(canvas, 2, 10, "Select Target AP");
        canvas_set_font(canvas, FontSecondary);
        
        // Display list of networks
        for(uint8_t i = 0; i < state->network_count && i < 4; i++) {
            char line_text[64];
            const char* ssid = furi_string_get_cstr(state->networks[i].ssid);
            bool is_selected = (i == state->selected_index);
            
            snprintf(
                line_text,
                sizeof(line_text),
                "%s %s (Ch:%d)",
                is_selected ? ">" : " ",
                ssid,
                state->networks[i].channel);
            
            canvas_draw_str(canvas, 2, 20 + (i * 12), line_text);
        }
        
        canvas_draw_str(canvas, 2, 60, "OK:Attack Back:Exit");
        break;

    case ViewAttacking:
        canvas_draw_str(canvas, 2, 10, "Deauth Attack");
        canvas_set_font(canvas, FontSecondary);
        
        char target_text[32];
        const char* target_ssid = furi_string_get_cstr(
            state->networks[state->selected_index].ssid);
        snprintf(target_text, sizeof(target_text), "Target: %s", target_ssid);
        canvas_draw_str(canvas, 2, 25, target_text);
        
        char packets_text[32];
        snprintf(packets_text, sizeof(packets_text), "Packets sent: %lu", state->packets_sent);
        canvas_draw_str(canvas, 2, 40, packets_text);
        
        canvas_draw_str(canvas, 2, 55, "Attacking...");
        canvas_draw_str(canvas, 2, 63, "Back:Stop");
        break;

    case ViewResults:
        canvas_draw_str(canvas, 2, 10, "Attack Complete");
        canvas_set_font(canvas, FontSecondary);
        
        char result_text[32];
        snprintf(result_text, sizeof(result_text), "Total packets: %lu", state->packets_sent);
        canvas_draw_str(canvas, 2, 25, result_text);
        
        canvas_draw_str(canvas, 2, 40, "Attack stopped");
        canvas_draw_str(canvas, 2, 55, "Back:Menu OK:Again");
        break;
    }

    furi_mutex_release(state->mutex);
}

// Input callback - handles button presses
static void wifi_deauth_input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;

    PluginEvent event = {.type = EventTypeKey, .input = *input_event};
    furi_message_queue_put(event_queue, &event, FuriWaitForever);
}

// Scan for WiFi networks (simplified - actual implementation requires ESP32)
static void scan_wifi_networks(WiFiDeauthState* state) {
    FURI_LOG_I(TAG, "Scanning for WiFi networks...");
    
    // Note: Actual scanning requires ESP32 firmware or external WiFi module
    // This is a placeholder showing structure
    
    // Simulated network data for demonstration
    state->network_count = 3;
    
    state->networks[0].ssid = furi_string_alloc_set("TestNetwork1");
    state->networks[0].channel = 6;
    state->networks[0].rssi = -45;
    
    state->networks[1].ssid = furi_string_alloc_set("TestNetwork2");
    state->networks[1].channel = 11;
    state->networks[1].rssi = -67;
    
    state->networks[2].ssid = furi_string_alloc_set("TestNetwork3");
    state->networks[2].channel = 1;
    state->networks[2].rssi = -82;
    
    FURI_LOG_I(TAG, "Scan complete: %d networks found", state->network_count);
}

// Send deauth packet (simplified - requires hardware support)
static void send_deauth_packet(WiFiDeauthState* state) {
    // Note: Actual packet sending requires ESP32 or compatible WiFi hardware
    // This increments counter to simulate packet transmission
    
    if(state->is_attacking) {
        state->packets_sent++;
        
        // Log every 100 packets
        if(state->packets_sent % 100 == 0) {
            FURI_LOG_I(TAG, "Packets sent: %lu", state->packets_sent);
        }
    }
}

// Main application entry point
int32_t wifi_deauth_app(void* p) {
    UNUSED(p);
    
    FURI_LOG_I(TAG, "WiFi Deauth app started");
    
    // Allocate state
    WiFiDeauthState* state = malloc(sizeof(WiFiDeauthState));
    state->view_state = ViewScanning;
    state->mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    state->network_count = 0;
    state->selected_index = 0;
    state->packets_sent = 0;
    state->is_attacking = false;
    
    // Create event queue
    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(PluginEvent));
    
    // Set up view port
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, wifi_deauth_render_callback, state);
    view_port_input_callback_set(view_port, wifi_deauth_input_callback, event_queue);
    
    // Register view port in GUI
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);
    
    // Notification setup
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    
    // Initial scan
    scan_wifi_networks(state);
    state->view_state = ViewTargetSelect;
    
    // Main event loop
    PluginEvent event;
    bool running = true;
    
    while(running) {
        if(furi_message_queue_get(event_queue, &event, 100) == FuriStatusOk) {
            if(event.type == EventTypeKey) {
                if(event.input.type == InputTypeShort || event.input.type == InputTypeRepeat) {
                    furi_mutex_acquire(state->mutex, FuriWaitForever);
                    
                    switch(state->view_state) {
                    case ViewTargetSelect:
                        if(event.input.key == InputKeyUp) {
                            if(state->selected_index > 0) {
                                state->selected_index--;
                            }
                        } else if(event.input.key == InputKeyDown) {
                            if(state->selected_index < state->network_count - 1) {
                                state->selected_index++;
                            }
                        } else if(event.input.key == InputKeyOk) {
                            state->view_state = ViewAttacking;
                            state->is_attacking = true;
                            state->packets_sent = 0;
                            notification_message(notifications, &sequence_blink_start_cyan);
                        } else if(event.input.key == InputKeyBack) {
                            running = false;
                        }
                        break;
                        
                    case ViewAttacking:
                        if(event.input.key == InputKeyBack) {
                            state->is_attacking = false;
                            state->view_state = ViewResults;
                            notification_message(notifications, &sequence_blink_stop);
                        }
                        break;
                        
                    case ViewResults:
                        if(event.input.key == InputKeyBack) {
                            state->view_state = ViewTargetSelect;
                        } else if(event.input.key == InputKeyOk) {
                            state->view_state = ViewAttacking;
                            state->is_attacking = true;
                            state->packets_sent = 0;
                            notification_message(notifications, &sequence_blink_start_cyan);
                        }
                        break;
                        
                    default:
                        break;
                    }
                    
                    furi_mutex_release(state->mutex);
                }
            }
        }
        
        // Send packets if attacking
        if(state->is_attacking) {
            send_deauth_packet(state);
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
    
    // Free network strings
    for(uint8_t i = 0; i < state->network_count; i++) {
        furi_string_free(state->networks[i].ssid);
    }
    
    furi_mutex_free(state->mutex);
    free(state);
    
    FURI_LOG_I(TAG, "WiFi Deauth app stopped");
    
    return 0;
}
