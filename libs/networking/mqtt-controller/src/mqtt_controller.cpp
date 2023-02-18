#include "mqtt_controller.h"
#include <iostream>
#include "mgos.h"
#include "mgos_timers.h"
//---------------------------------------------------------------------------------------------------------------

MqttController::MqttController() {
    /* Subscription for all the messages for this appliance*/
    m_base_topic = "iot/";
    m_base_topic += mgos_sys_config_get_device_id();
    m_base_topic += "/cmd";

    actions.emplace("/cook/start", [](mg_str payload) {  MQTT_CONTROLLER.startCook();    });
    actions.emplace("/cook/stop", [this](mg_str payload) {  this->stopCook();    });
    actions.emplace("/prender_motor", [this](mg_str payload) {  this->prender_motor(); });
}

void mqtt_controller_cb(struct mg_connection *c, const char *topic, int topic_len, const char *msg, int msg_len, void *userdata) {
  LOG(LL_INFO, ("Receving message ....topic:  %s\n message: %s", topic, msg));
    MQTT_CONTROLLER.messagesLoop(c, topic,topic_len, msg, msg_len, userdata);
}

std::string MqttController::getCommandTopic(std::string topic) {
    // buscar base topic y eliminarlo del topic entrante 
    std::string command(topic);
    std::string::size_type i = command.find(getBaseTopic());
    if (i != std::string::npos) {
        command.erase(i, getBaseTopic().length());
        return command;
    }
    return "";
}

void MqttController::messagesLoop(struct mg_connection *c, const char *topic, int topic_len, const char *msg, int msg_len, void *userdata) {
    std::string in_topic = std::string(topic, topic_len);
    incomming_command = getCommandTopic(in_topic);
    LOG(LL_INFO, ("Incoming topic .... %s", incomming_command.c_str()));
    mg_str payload = mg_mk_str_n(msg, msg_len);
    processMessage(payload);
}

void MqttController::processMessage(mg_str payload) {
    auto it = actions.find(incomming_command);
    if (it != actions.end()) {
        it->second(payload);
        LOG(LL_INFO, ("Command success !!"));
    }
}

static void mqtt_conecction_handler(struct mg_connection *nc, int ev, void *ev_data MG_UD_ARG(void *user_data)) {
    if (ev == MG_EV_MQTT_CONNACK) {
        // subscribe to the topic
        std::string topic = MQTT_CONTROLLER.getBaseTopic();
        topic += "/#";
        LOG(LL_INFO, ("\n----- Connected to Mqtt server........"));
        mgos_mqtt_sub(topic.c_str(), mqtt_controller_cb, NULL);
    }
}

void MqttController::startCook(void)
{
LOG(LL_INFO, ("Iniciando cook process"));
}

void MqttController::stopCook(void)
{
LOG(LL_INFO, ("deteniendo cook process"));

}

void MqttController::prender_motor(void)
{
LOG(LL_INFO, ("........................prendiendo motor........."));
//emitir un evento y poermitir que hardware manager lo escuche
}

//-----------------------------------------------------------------------------------------------
std::string MqttController::getBaseTopic() {
    return m_base_topic;
}
//---------------------------------------------------------------------------------------------------------------
int mgos_mqtt_controller_init() {
    LOG(LL_INFO, ("*************************/////////MQTT CONTROLLER INITIALIZED******************----------"));
    mgos_mqtt_add_global_handler(mqtt_conecction_handler, NULL);
    return true;
}