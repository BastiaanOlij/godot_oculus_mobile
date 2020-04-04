#include "ovr_input_ns.h"
#include "api/ovr_input.h"
#include "nativescript_common.h"

static const char *kClassName = "OvrInput";

void register_gdnative_input(void *handle) {
	// register the constructor and destructor of the OvrInput class for use in GDScript
	godot_instance_create_func create = { NULL, NULL, NULL };
	create.create_func = &ovr_input_constructor;

	godot_instance_destroy_func destroy = { NULL, NULL, NULL };
	destroy.destroy_func = &ovr_input_destructor;

	nativescript_api->godot_nativescript_register_class(handle, kClassName, "Reference", create, destroy);

	// register all the functions that we want to expose via the OvrInput class in GDScript
	godot_instance_method method = { NULL, NULL, NULL };
	godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

	method.method = &vibrate_controller;
	nativescript_api->godot_nativescript_register_method(handle, kClassName, "vibrate_controller", attributes, method);
}

GDCALLINGCONV void *ovr_input_constructor(godot_object *instance, void *method_data) {
	return init_ovr_config_data_struct();
}

GDCALLINGCONV void ovr_input_destructor(godot_object *instance, void *method_data, void *user_data) {
	if (user_data) {
		reset_ovr_config_data_struct(static_cast<ovr_config_data_struct *>(user_data));
	}
}

GDCALLINGCONV godot_variant vibrate_controller(godot_object *instance, void *method_data, void *p_user_data, int num_args, godot_variant **args) {
	CHECK_USER_DATA(
			const int controller_id = api->godot_variant_as_int(args[0]);
			const double intensity = api->godot_variant_as_real(args[1]);
			api->godot_variant_new_bool(&ret, ovrmobile::vibrate_controller(ovr_mobile_session, controller_id, intensity));

	)
}