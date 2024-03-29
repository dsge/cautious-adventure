#!/usr/bin/env python
import os
import sys

from scons import utils
from scons import appenvironment

EnsureSConsVersion(4, 4)

# default values, adapt them to your setup
default_library_name = "libapp"
default_target_path = "godot-project/bin/"


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

opts.Add(PathVariable('godot_editor_dir', "The path where the blender and godot-editor should be downloaded to, relative to the repo root folder", './blender-and-godot-editor', PathVariable.PathAccept))

# Updates the environment with the option variables.
opts.Update(env)
# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))

appenvironment.ensure_blender_and_godot_binaries(override_blender_and_godot_editor_path=env['godot_editor_dir'])
utils.setupEnvForPlatform(env, env["platform"])
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

env.Append(CPPDEFINES=['SPDLOG_COMPILED_LIB'])

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
    res = SConscript(sconsFilePath, exports={'env': env.Clone()})
    if res:
        utils.parseChildSconstructBuildResults(res, env, os)

vsCodeConfigFilesCreated = utils.createVsCodeConfigFilesIfNeeded()
utils.printVerboseMessagesIfNeeded(env, vsCodeConfigFilesCreated)


cppHeaderIncludePaths = []
cppHeaderIncludePaths += env['app_additionalCppHeaderIncludePaths']
# cppHeaderIncludePaths += ["./src"]

finalEnv = env.Clone()

# make sure our binding library is properly includes
finalEnv.Append(CPPPATH=cppHeaderIncludePaths)
finalEnv.Append(LIBPATH=env['app_additionalLibraryPaths'])
finalEnv.Append(LIBS=env['app_additionalLibraryNames'])

utils.override_build_output_messages(sys, env) 
utils.override_build_output_messages(sys, finalEnv) 

# tweak this if you want to use different folders, or more folders, to store your source code in.

def globFolder(folderPath):
    return Glob(pattern = folderPath + '/*.cpp', exclude=None if env['include_testrunner'] else folderPath + '/*.test.cpp')

sources = globFolder('godot-project/src')
sources += globFolder('godot-project/src/PlayerControlledEntities')
sources += globFolder('godot-project/src/Enemies')
sources += globFolder('godot-project/src/UI')

target_name = "{}.{}.{}.{}".format(env["target_name"], env["platform"], env["target"], '64')
library = finalEnv.SharedLibrary(target=env["target_path"] + target_name, source=sources)

Default(library)
