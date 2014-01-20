#include <pebble.h>
#include "APPMESSAGE.h"


static int counter = 0;



static void update_ui_from_accel(AccelData *accel_data, uint32_t num_samples) {
  text_layer_set_text(text_layer, text_buffer);
}


static void calibrate_timer(void *data) {


  accel = (AccelData) { .x = 0, .y = 0, .z = 0 };
  accel_service_peek(&accel);


snprintf(text_buffer, 125, "Y:%d" "\n" "X:%d" "\n" "Z:%d", accel.y, accel.x, accel.z);

p = text_buffer;

app_message_outbox_begin(&iter);


Tuplet accel = TupletCString(TODO_KEY_APPEND, p);



  dict_write_tuplet(iter, &accel);
  dict_write_end(iter);

  app_message_outbox_send();

timers = app_timer_register(0 /* milliseconds */, calibrate_timer, NULL);

}


 void timer_callback(void *data) {

counter = 0;
  accel = (AccelData) { .x = 0, .y = 0, .z = 0 };
  accel_service_peek(&accel);

snprintf(text_buffer, 125, "Y:%d" "\n" "X:%d" "\n" "Z:%d", accel.y, accel.x, accel.z);
update_ui_from_accel(&accel, 0);


  timer = app_timer_register(0 /* milliseconds */, timer_callback, NULL);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
if(counter == 0){
app_timer_cancel(timer);
text_layer_set_text(text_layer, text_buffer);

}else
if(counter != 0){
timer = app_timer_register(0, timer_callback, NULL);
}
counter++;

}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
app_timer_cancel(timer);

  accel = (AccelData) { .x = 0, .y = 0, .z = 0 };
  accel_service_peek(&accel);

snprintf(text_buffer, 125, "Y:%d" "\n" "X:%d" "\n" "Z:%d", accel.y, accel.x, accel.z);

text_layer_set_text(text_layer, "Watch phone!");

p = text_buffer;

app_message_outbox_begin(&iter);


Tuplet accel = TupletCString(TODO_KEY_APPEND, p);

  dict_write_tuplet(iter, &accel);
  dict_write_end(iter);

  app_message_outbox_send();

timers = app_timer_register(0 /* milliseconds */, calibrate_timer, NULL);
}




static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
app_timer_cancel(timers);
timer = app_timer_register(0 /* milliseconds */, timer_callback, NULL);
}          




static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}


static void window_load(Window *window) {
accel_data_service_subscribe(0, update_ui_from_accel);
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  text_layer = text_layer_create((GRect) { .origin = { 5, 5 }, .size = { bounds.size.w-0, 100 } });
timer = app_timer_register(0 /* milliseconds */, timer_callback, NULL);
  text_layer_set_overflow_mode(text_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}


static void window_unload(Window *window) {
	app_timer_cancel(timer);
	app_timer_cancel(timers);
  text_layer_destroy(text_layer);
}


static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);

app_message_register_inbox_received(in_received_handler);
   app_message_register_inbox_dropped(in_dropped_handler);
   app_message_register_outbox_sent(out_sent_handler);
   app_message_register_outbox_failed(out_failed_handler);
   app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit(void) {
 accel_data_service_unsubscribe();
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
