#include "RTIAmbassadorTest1.hpp"

class Initialization {

private:
    static void interaction_root_dynamic_init();

    static bool &get_is_initialized() {
        static bool isInitialized = false;
        return isInitialized;
    }

public:
    static void init_1();
};