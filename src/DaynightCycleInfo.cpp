#include "includes/DaynightCycleInfo.h"

using namespace app;

void DaynightCycleInfo::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &DaynightCycleInfo::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &DaynightCycleInfo::_process);
    godot::ClassDB::bind_method(godot::D_METHOD("enter_tree"), &DaynightCycleInfo::_enter_tree);
    godot::ClassDB::bind_method(godot::D_METHOD("unhandled_key_input"), &DaynightCycleInfo::_unhandled_key_input);
}

DaynightCycleInfo::DaynightCycleInfo() {
    this->input = godot::Input::get_singleton();
}

void DaynightCycleInfo::_enter_tree() {
    this->infoLabel = app::call_get_node<godot::Label>(this, "InfoLabel");
    auto startup = app::call_get_node<app::Startup>(this, "/root/Startup");
    if (startup) {
        this->daynightCycleManager = startup->getContainer()->resolve< app::DaynightCycleManager >();
    }
}

void DaynightCycleInfo::_ready() {
}

void DaynightCycleInfo::_process(float delta) {
    if (this->daynightCycleManager) {
        this->infoLabel->set_text(godot::String("{0}:{1}\nIsDaytime: {2}\nIsNighttime: {3}").format(godot::Array::make(
            godot::String("%02.0f") % this->daynightCycleManager->getHour(),
            godot::String("%02.0f") % this->daynightCycleManager->getMinute(),
            this->daynightCycleManager->isDaytime(),
            this->daynightCycleManager->isNighttime()
        )));
    }
}

void DaynightCycleInfo::_unhandled_key_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->daynightCycleManager) {
        if (this->input->is_action_just_released(Actions::UI_PLAYPAUSE_DAYNIGHT_CYCLE)) {
            this->daynightCycleManager->playPauseDaynightCycle();
        }
        if (this->input->is_action_just_released(Actions::UI_SET_TIME_NOON)) {
            this->daynightCycleManager->pauseDaynightCycle();
            this->daynightCycleManager->setTime(12.0);
        }
        if (this->input->is_action_just_released(Actions::UI_SET_TIME_MIDNIGHT)) {
            this->daynightCycleManager->pauseDaynightCycle();
            this->daynightCycleManager->setTime(0.0);
        }
    }
}

DaynightCycleInfo::~DaynightCycleInfo() {

}
