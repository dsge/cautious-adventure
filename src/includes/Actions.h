#ifndef APP_ACTIONS_H
#define APP_ACTIONS_H
namespace app {
    struct Actions {
        static constexpr char UI_FORWARD[] = "ui_forward";
        static constexpr char UI_BACKWARDS[] = "ui_backwards";
        static constexpr char UI_LEFT[] = "ui_left";
        static constexpr char UI_RIGHT[] = "ui_right";

        static constexpr char UI_ASCEND[] = "ui_ascend";
        static constexpr char UI_DESCEND[] = "ui_descend";

        static constexpr char UI_TOGGLE_MOUSE_CAPTURE[] = "ui_toggle_mouse_capture";

        static constexpr char UI_SET_TIME_NOON[] = "ui_set_time_noon";
        static constexpr char UI_SET_TIME_MIDNIGHT[] = "ui_set_time_midnight";
        static constexpr char UI_PLAYPAUSE_DAYNIGHT_CYCLE[] = "ui_playpause_daynight_cycle";

        static constexpr char UI_SCROLL_ZOOM_IN[] = "ui_scroll_zoom_in";
        static constexpr char UI_SCROLL_ZOOM_OUT[] = "ui_scroll_zoom_out";
    };
}
#endif
