import os
import sys

args = ARGUMENTS
if not "generate_bindings" in args:
    args["generate_bindings"] = "yes"
if not "custom_api_file" in args:
    args["custom_api_file"] = "/home/geri/workspace/godot/bin/extension_api.json"
#if not "headers_dir" in args:
#    args["headers_dir"] = ["include"]

Export(ARGUMENTS = args)

libraryBasePath = '../lib/godot-cpp'

Default(libraryBasePath)

SConscript(libraryBasePath + '/SConstruct')




# godot_headers_path = "../lib/godot-cpp/godot_headers/"
# cpp_bindings_path = "../lib/godot-cpp/"
# cpp_library = "libgodot-cpp"

# env.Append(CPPPATH=['.', godot_headers_path, cpp_bindings_path + 'include/', cpp_bindings_path + 'include/core/', cpp_bindings_path + 'include/gen/'])
# env.Append(LIBPATH=[cpp_bindings_path + 'bin/'])
# env.Append(LIBS=[cpp_library])

#### Copied from ../lib/godot-cpp/SConstruct

# Try to detect the host platform automatically.
# This is used if no `platform` argument is passed
if sys.platform.startswith("linux"):
    host_platform = "linux"
elif sys.platform.startswith("freebsd"):
    host_platform = "freebsd"
elif sys.platform == "darwin":
    host_platform = "osx"
elif sys.platform == "win32" or sys.platform == "msys":
    host_platform = "windows"
else:
    raise ValueError("Could not detect platform automatically, please specify with platform=<platform>")

opts = Variables([], ARGUMENTS)
opts.Add(
    EnumVariable(
        "platform",
        "Target platform",
        host_platform,
        allowed_values=("linux", "freebsd", "osx", "windows", "android", "ios", "javascript"),
        ignorecase=2,
    )
)
opts.Add(EnumVariable("target", "Compilation target", "debug", allowed_values=("debug", "release"), ignorecase=2))

#### /Copied from ../lib/godot-cpp/SConstruct

env = Environment()
opts.Update(env)
Help(opts.GenerateHelpText(env))

ret = {
    'builds': [
        env.File(libraryBasePath + "/bin/" + "libgodot-cpp.{}.{}.{}{}".format(env["platform"], env["target"], '64', '.a'))
    ], 
    'headerfileIncludePaths': [
        libraryBasePath + '/godot_headers/',
        libraryBasePath + '/',
        libraryBasePath + '/include/',
        libraryBasePath + '/include/core/',
        libraryBasePath + '/include/gen',
    ]
}
Return('ret')
