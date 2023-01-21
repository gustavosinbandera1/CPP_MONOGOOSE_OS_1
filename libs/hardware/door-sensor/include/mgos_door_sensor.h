#pragma once
#include "mgos.h"

#ifdef __cplusplus
extern "C" {
#endif
int mgos_door_sensor_init(void);
#ifdef __cplusplus
}
#endif


class DoorSensor {
   public:
    static DoorSensor *getInstance() {
        static DoorSensor inst;
        return &inst;
    }

    void checkDoor();

   private:
    DoorSensor();
    mgos_timer_id checkDoorTimerId_;
    bool door_closed_;
    bool last_door_closed_;
    int8_t door_closed_cnt_;
};
