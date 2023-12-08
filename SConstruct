#!/usr/bin/env python
import os
import sys

from scons import utils
from scons import appenvironment

EnsureSConsVersion(4, 4)

appenvironment.ensure_godot_binaries()

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
        # allowed_values=("linux", "freebsd", "osx", "windows", "android", "ios", "javascript"),
        allowed_values=("linux", "windows"),
        ignorecase=2,
    )
)

opts.Add(PathVariable("target_path", "The path where the lib is installed.", default_target_path, PathVariable.PathAccept))
opts.Add(PathVariable("target_name", "The library name.", default_library_name, PathVariable.PathAccept))

opts.Add(BoolVariable("use_llvm", "Use the LLVM / Clang compiler", "no"))
opts.Add(BoolVariable("use_mingw", "Use the MinGW compiler instead of MSVC - only effective on Windows", False))
opts.Add(BoolVariable("use_clang_cl", "Use the clang driver instead of MSVC - only effective on Windows", False))
opts.Add(BoolVariable("use_static_cpp", "Link MinGW/MSVC C++ runtime libraries statically", True))

opts.Add(BoolVariable('include_testrunner', "include testrunner", 'no'))
opts.Add(BoolVariable("show_include_paths", "Show an extended list of the used CPP include paths", "no"))
opts.Add(BoolVariable('verbose', "Show more build time information", 'no'))

# Updates the environment with the option variables.
opts.Update(env)
# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))

# Process some arguments
if env["use_llvm"]:
    env["CC"] = "clang"
    env["CXX"] = "clang++"

if env["target"] == "debug":
    env.Append(CPPDEFINES=["DEBUG_ENABLED", "DEBUG_METHODS_ENABLED"])
    if env['include_testrunner']:
        env.Append(CPPDEFINES=['INCLUDE_TESTRUNNER'])
        env.Append(CCFLAGS=['-fprofile-arcs', '-ftest-coverage'])
        env.Append(LIBS=['gcov'])

if env["platform"] == "":
    print("No valid target platform selected.")
    quit()

elif env["platform"] in ("x11", "linux"):
    utils.setLinuxEnv(env)

elif env["platform"] == "windows":
    env['arch'] = 'x86_64'
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
sources += globFolder('src/Enemies')
sources += globFolder('src/UI')

target_name = "{}.{}.{}.{}".format(env["target_name"], env["platform"], env["target"], '64')
library = env.SharedLibrary(target=env["target_path"] + target_name, source=sources)

Default(library)
