#ifndef APP_ACTIONS_H
#define APP_ACTIONS_H
namespace app {
    struct Actions {
        static constexpr char UI_FORWARD[] = "ui_forward";
        static constexpr char UI_BACKWARDS[] = "ui_backwards";
        static constexpr char UI_LEFT[] = "ui_left";
        static constexpr char UI_RIGHT[] = "ui_right";
    };
}
#endif