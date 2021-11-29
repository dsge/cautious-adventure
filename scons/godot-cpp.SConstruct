args = ARGUMENTS
if not "generate_bindings" in args:
    args["generate_bindings"] = "yes"
if not "custom_api_file" in args:
    args["custom_api_file"] = "/home/geri/workspace/godot/bin/extension_api.json"
#if not "headers_dir" in args:
#    args["headers_dir"] = ["include"]

Export(ARGUMENTS = args)

SConscript('../lib/godot-cpp/SConstruct')