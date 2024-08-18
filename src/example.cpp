#include "example.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void Example::_bind_methods() {
}

Example::Example() {
	if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
}

Example::~Example() {
}

void Example::_process(double delta) {
	UtilityFunctions::print("Process");
}