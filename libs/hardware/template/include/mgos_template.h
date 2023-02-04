#pragma once
#include "mgos.h"

#ifdef __cplusplus
extern "C" {
#endif
int mgos_template_init(void);
#ifdef __cplusplus
}
#endif

#define PLANTILLA PlantillaCtrl::getInstance()

class PlantillaCtrl {
   public:
    static PlantillaCtrl *getInstance() {
        static PlantillaCtrl inst;
        return &inst;
    }

    void method1(float param);
    int method2(char param);
    bool method3(int param);

   private:
    PlantillaCtrl();
};
