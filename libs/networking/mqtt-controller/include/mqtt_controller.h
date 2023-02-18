#pragma once
#include "mgos.h"
#include <algorithm>
#include <functional>

#include "mgos_mqtt.h"
#include <string>
#include <vector>
#include <map>


#ifdef __cplusplus
extern "C" {
#endif
int mgos_mqtt_controller_init(void);
#ifdef __cplusplus
}
#endif

#define MQTT_CONTROLLER MqttController::getInstance()

using CallbackAction = std::function<void(mg_str)>;
using MqttActions = std::map<std::string, CallbackAction>;


class MqttController {
   public:
    MqttController(MqttController const &) = delete;
    MqttController(MqttController &&) = delete;
    MqttController &operator=(MqttController const &) = delete;
    MqttController &operator=(MqttController &&) = delete;

    std::string getBaseTopic();
    
    //CallbackAction myaction;
    ///std::function<void(mg_str)> myfucn;
    
    static MqttController &getInstance() {
        static MqttController g_instance;
        return g_instance;
    }

    void messagesLoop(struct mg_connection *c, const char *topic, int topic_len, const char *msg, int msg_len, void *userdata);
    std::string getCommandTopic(std::string topic);
    private:
    MqttActions actions;
    MqttController();  // private constructor
    std::string m_base_topic;

    private:
    void startCook(void);
    void stopCook(void);
    void prender_motor(void);
    std::string incomming_command;
    void processMessage(mg_str payload);

};
