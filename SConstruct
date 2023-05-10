#!/usr/bin/env python
import os
import sys

from scons import utils

# default values, adapt them to your setup
default_library_name = "libapp"
default_target_path = "bin/"


host_platform = utils.autoDetectHostPlatform(sys)

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

opts.Add(BoolVariable('include_testrunner', "include testrunner", 'no'))
opts.Add(BoolVariable("show_include_paths", "Show an extended list of the used CPP include paths", "no"))
opts.Add(BoolVariable('verbose', "Show more build time information", 'no'))
opts.Add(PathVariable('override_vscode_godot_absolute_path', "Set VSCode launch.json's Godot absolute paths to this, and then exit without building anything.", '', PathVariable.PathAccept))

# Updates the environment with the option variables.
opts.Update(env)
# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))

if env['override_vscode_godot_absolute_path']:
    path = env['override_vscode_godot_absolute_path']
    if utils.setVsCodeLaunchJsonGodotBinaryAbsolutePaths(path):
        print('\nLaunch.json Godot Absolute Filepath successfully updated to:')
        print(' -', path)
    else:
        print('\nFailed to update Launch.json Godot Absolute Filepath to', path)
        print('No changes were made.')
    sys.exit()

env["app_arch_suffix"] = ''

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

if env["target"] == "debug":
    env.Append(CPPDEFINES=["DEBUG_ENABLED", "DEBUG_METHODS_ENABLED"])
    if env['include_testrunner']:
        env.Append(CPPDEFINES=['INCLUDE_TESTRUNNER'])
        env.Append(CCFLAGS=['-fprofile-arcs', '-ftest-coverage'])
        env.Append(LIBS=['gcov'])

# Check our platform specifics
if env["platform"] == "osx":
    utils.setOsxEnv(env)

elif env["platform"] in ("x11", "linux"):
    utils.setLinuxEnv(env)

elif env["platform"] == "windows":
    utils.setWindowsEnv(env, os)


additionalSconsFilePaths = [
    'scons/godot-cpp.SConstruct',
    'scons/googletest.SConstruct',
    'scons/hypodermic.SConstruct',
    'scons/spdlog.SConstruct',
]

env['app_additionalCppHeaderIncludePaths'] = [] # where to look for #included files during build time
env['app_additionalLibraryPaths'] = [] # where to look for LIBs (aka the elements of 'app_additionalLibraryNames')
env['app_additionalLibraryNames'] = [] 

for sconsFilePath in additionalSconsFilePaths:
    res = SConscript(sconsFilePath)
    if res:
        utils.parseChildSconstructBuildResults(res, env, os)

vsCodeConfigFilesCreated = utils.createVsCodeConfigFilesIfNeeded()
utils.printVerboseMessagesIfNeeded(env, vsCodeConfigFilesCreated)


cppHeaderIncludePaths = []
cppHeaderIncludePaths += env['app_additionalCppHeaderIncludePaths']
# cppHeaderIncludePaths += ["./src"]

# make sure our binding library is properly includes
env.Append(CPPPATH=cppHeaderIncludePaths)
env.Append(LIBPATH=env['app_additionalLibraryPaths'])
env.Append(LIBS=env['app_additionalLibraryNames'])

utils.override_build_output_messages(sys, env) 

# tweak this if you want to use different folders, or more folders, to store your source code in.

def globFolder(folderPath):
    return Glob(pattern = folderPath + '/*.cpp', exclude=None if env['include_testrunner'] else folderPath + '/*.test.cpp')

sources = globFolder('src')
sources += globFolder('src/PlayerControlledEntities')
sources += globFolder('src/Power')

target_name = "{}.{}.{}.{}".format(env["target_name"], env["platform"], env["target"], env['app_arch_suffix'])
library = env.SharedLibrary(target=env["target_path"] + target_name, source=sources)

Default(library)
