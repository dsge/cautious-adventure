import os
import sys
import io
from contextlib import redirect_stdout

import utils

args = ARGUMENTS
# if not "generate_bindings" in args:
    # args["generate_bindings"] = "yes"
    # args["generate_bindings"] = "auto"
    # pass
# if not "custom_api_file" in args:
    # args["custom_api_file"] = "/home/geri/workspace/godot/bin/extension_api.json"
#if not "headers_dir" in args:
#    args["headers_dir"] = ["include"]

# Source: https://godotengine.org/article/introducing-gd-extensions
args["target"] = "editor"

Export(ARGUMENTS = args)

libraryBasePath = '../lib/godot-cpp'

# Default(libraryBasePath)




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
opts.Add(EnumVariable("target", "Compilation target", "editor", allowed_values=("editor", "template_release", "template_debug"), ignorecase=2))

#### /Copied from ../lib/godot-cpp/SConstruct

env = Environment()
opts.Update(env)
Help(opts.GenerateHelpText(env))

opts = utils.get_build_output_messages(sys) 

Decider("content-timestamp")

# with redirect_stdout(io.StringIO()) as f:
    # redirect_stdout is used to capture the stdout, so that the
    # "WARNING: Unknown SCons variables were passed and will be ignored:" messages
    # wouldn't be displayed for someone who uses the app's main sconstruct file
    # SConscript(libraryBasePath + '/SConstruct', exports=opts)

SConscript(libraryBasePath + '/SConstruct', exports=opts)

builtFileName = libraryBasePath + "/bin/" + "libgodot-cpp.{}.{}.{}{}".format(env["platform"], env["target"], 'x86_64', '.a')

# Removing builtFileName with `scons -c` also removes the autogenerated object.cpp
Clean(builtFileName, os.path.join(libraryBasePath, "gen", "src", "classes", "object.cpp"))

ret = {
    'builds': [
        env.File(builtFileName)
    ], 
    'headerfileIncludePaths': [
        env.Dir(libraryBasePath + '/'),
        env.Dir(libraryBasePath + '/gdextension/'),
        env.Dir(libraryBasePath + '/include/'),
        env.Dir(libraryBasePath + '/include/godot_cpp/'),
        env.Dir(libraryBasePath + '/include/godot_cpp/classes'),
        env.Dir(libraryBasePath + '/include/godot_cpp/core'),
        env.Dir(libraryBasePath + '/include/godot_cpp/variant'),
        env.Dir(libraryBasePath + '/gen/include/'),
        env.Dir(libraryBasePath + '/gen/include/godot_cpp/classes'),
        env.Dir(libraryBasePath + '/gen/include/godot_cpp/variant'),
    ]
}
Return('ret')
