#ifndef APPMESSAGE_H
#define APPMESSAGE_H

enum {
  TODO_KEY_APPEND,
  TODO_KEY_DELETE,
  TODO_KEY_MOVE,
  TODO_KEY_TOGGLE_STATE,
  TODO_KEY_FETCH,
};
static Window *window;
DictionaryIterator *iter;
static AccelData accel;
static AppTimer *timer;
static AppTimer *timers;
static AppTimer *timerz;
static TextLayer *text_layer;
DictionaryIterator *iter;
Tuple *text_tuple;
char text_buffer[250];
char *p;
int x[1024];
int y[1024];
int z[1024];

static void calibrate_timer(void *data);

 void timer_callback(void *data);

 void out_sent_handler(DictionaryIterator *sent, void *context);


 void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context);


 void in_received_handler(DictionaryIterator *received, void *context);


 void in_dropped_handler(AppMessageResult reason, void *context);



#endif
