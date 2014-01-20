#include <pebble.h>
#include "APPMESSAGE.h"

 void out_sent_handler(DictionaryIterator *sent, void *context) {
 APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message worked!");
 text_buffer[0] = 0;
 p = text_buffer;


 }


 void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
 APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Failed to Send!");
 }


 void in_received_handler(DictionaryIterator *received, void *context) {

	text_tuple = dict_find(received, TODO_KEY_APPEND);
 


         
      if(text_tuple){
            APP_LOG(APP_LOG_LEVEL_DEBUG, "Text: %s", text_tuple->value->cstring);
}

 }


 void in_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Dropped!");
 }
