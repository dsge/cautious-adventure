#!/usr/bin/env python
import os
import sys

from scons import utils

# default values, adapt them to your setup
default_library_name = "libapp"
default_target_path = "bin/"


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
    raise ValueError("Could not detect platform automatically, please specify with " "platform=<platform>")

env = Environment(ENV=os.environ)

opts = Variables([], ARGUMENTS)

# Define our options
opts.Add(EnumVariable("target", "Compilation target", "debug", allowed_values=("debug", "release"), ignorecase=2))
opts.Add(
    EnumVariable(
        "platform",
        "Compilation platform",
        host_platform,
        # We'll need to support these in due times
        # allowed_values=("linux", "freebsd", "osx", "windows", "android", "ios", "javascript"),
        allowed_values=("linux", "windows", "osx"),
        ignorecase=2,
    )
)
opts.Add(EnumVariable("bits", "Target platform bits", "64", ("32", "64")))
opts.Add(BoolVariable("use_llvm", "Use the LLVM / Clang compiler", "no"))
opts.Add(EnumVariable("macos_arch", "Target macOS architecture", "universal", ["universal", "x86_64", "arm64"]))
opts.Add(PathVariable("target_path", "The path where the lib is installed.", default_target_path, PathVariable.PathAccept))
opts.Add(PathVariable("target_name", "The library name.", default_library_name, PathVariable.PathAccept))

opts.Add(BoolVariable("show_include_paths", "Show an extended list of the used CPP include paths", "no"))

# only support 64 at this time..
bits = 64

# Updates the environment with the option variables.
opts.Update(env)
# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))

# This makes sure to keep the session environment variables on Windows.
# This way, you can run SCons in a Visual Studio 2017 prompt and it will find
# all the required tools
if host_platform == "windows" and env["platform"] != "android":
    if env["bits"] == "64":
        env = Environment(TARGET_ARCH="amd64")
    elif env["bits"] == "32":
        env = Environment(TARGET_ARCH="x86")

    opts.Update(env)

# Process some arguments
if env["use_llvm"]:
    env["CC"] = "clang"
    env["CXX"] = "clang++"

if env["platform"] == "":
    print("No valid target platform selected.")
    quit()

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

if env["target"] == "debug":
    env.Append(CPPDEFINES=["DEBUG_ENABLED", "DEBUG_METHODS_ENABLED"])

# Check our platform specifics
if env["platform"] == "osx":
    env["target_path"] += "osx/"
    # cpp_library += ".osx"

    if env["bits"] == "32":
        raise ValueError("Only 64-bit builds are supported for the macOS target.")

    if env["macos_arch"] == "universal":
        env.Append(LINKFLAGS=["-arch", "x86_64", "-arch", "arm64"])
        env.Append(CCFLAGS=["-arch", "x86_64", "-arch", "arm64"])
    else:
        env.Append(LINKFLAGS=["-arch", env["macos_arch"]])
        env.Append(CCFLAGS=["-arch", env["macos_arch"]])

    env.Append(CXXFLAGS=["-std=c++17"])
    if env["target"] == "debug":
        env.Append(CCFLAGS=["-g", "-O2"])
    else:
        env.Append(CCFLAGS=["-g", "-O3"])

    arch_suffix = env["macos_arch"]

elif env["platform"] in ("x11", "linux"):
    # cpp_library += ".linux"
    env.Append(CCFLAGS=["-fPIC"])
    env.Append(CXXFLAGS=["-std=c++17"])
    if env["target"] == "debug":
        env.Append(CCFLAGS=["-g3", "-Og"])
    else:
        env.Append(CCFLAGS=["-g", "-O3"])

    arch_suffix = str(bits)
elif env["platform"] == "windows":
    # cpp_library += ".windows"
    # This makes sure to keep the session environment variables on windows,
    # that way you can run scons in a vs 2017 prompt and it will find all the required tools
    env.Append(ENV=os.environ)

    env.Append(CPPDEFINES=["WIN32", "_WIN32", "_WINDOWS", "_CRT_SECURE_NO_WARNINGS"])
    env.Append(CCFLAGS=["-W3", "-GR"])
    env.Append(CXXFLAGS=["-std:c++17"])
    if env["target"] == "debug":
        env.Append(CPPDEFINES=["_DEBUG"])
        env.Append(CCFLAGS=["-EHsc", "-MDd", "-ZI", "-FS"])
        env.Append(LINKFLAGS=["-DEBUG"])
    else:
        env.Append(CPPDEFINES=["NDEBUG"])
        env.Append(CCFLAGS=["-O2", "-EHsc", "-MD"])

    if not(env["use_llvm"]):
        env.Append(CPPDEFINES=["TYPED_METHOD_BIND"])

    arch_suffix = str(bits)


additionalSconsFilePaths = [
    'scons/godot-cpp.SConstruct',
    'scons/googletest.SConstruct',
    'scons/hypodermic.SConstruct',
]

additionalCppHeaderIncludePaths = [] # where to look for #included files during build time
additionalLibraryPaths = [] # where to look for LIBs
additionalLibraryNames = [] 

for sconsFilePath in additionalSconsFilePaths:
    res = SConscript(sconsFilePath)
    if res:
        if "builds" in res:
            for builtLibrary in res["builds"]:
                libraryPath = os.path.dirname(builtLibrary.path)
                libraryName = os.path.splitext(os.path.basename(builtLibrary.abspath))[0]
                if libraryName.startswith('lib'):
                    libraryName = libraryName[len('lib'):]
                runtimeRelativeLibPath = os.path.basename(libraryPath)

                additionalLibraryPaths.append(libraryPath)
                additionalLibraryNames.append(libraryName)
                # runtimeRelativeLibPaths.append(os.path.join('\\$$ORIGIN', os.pardir, os.pardir, runtimeRelativeLibPath))
        if "headerfileIncludePaths" in res:
            for path in res["headerfileIncludePaths"]:
                additionalCppHeaderIncludePaths.append(path.path)



includePathsDisplayString = '\n   (Rerun with `show_include_paths=yes` to display the list)\n'
if env["show_include_paths"]:
    includePathsDisplayString = utils.printList(additionalCppHeaderIncludePaths)
    

print('----')
print('Building using the following header include paths: ', includePathsDisplayString)
print('Using built libraries: ', utils.printList(additionalLibraryNames))
print('Looking for built libraries in: ', utils.printList(additionalLibraryPaths))


print('Unused but cached local godot binary path: ')
try:
    print(' - ', utils.getCachedGodotBinaryAbsolutePath())
except (FileNotFoundError, ValueError) as e:
    # config file not found at all, or
    # cached godot binary path not found in configfile
    print(' - (not found)')

# utils.setCachedGodotBinaryAbsolutePath('/home/geri/workspace/godot/bin/godot.linuxbsd.opt.tools.64')

print('----')


cppHeaderIncludePaths = []
cppHeaderIncludePaths += additionalCppHeaderIncludePaths
cppHeaderIncludePaths += [".", "./src"]

# make sure our binding library is properly includes
env.Append(CPPPATH=cppHeaderIncludePaths)
env.Append(LIBPATH=additionalLibraryPaths)
env.Append(LIBS=additionalLibraryNames)


utils.override_build_output_messages(sys, env) 


# tweak this if you want to use different folders, or more folders, to store your source code in.
sources = Glob("src/*.cpp")

target_name = "{}.{}.{}.{}".format(env["target_name"], env["platform"], env["target"], arch_suffix)
# print(target_name)
library = env.SharedLibrary(target=env["target_path"] + target_name, source=sources)

Default(library)