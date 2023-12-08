import json
import os.path
from shutil import copyfile
from SCons.Tool import msvc, mingw
import sys
from SCons.Variables import *
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(
    os.path.realpath(__file__)), '..', 'lib', 'godot-cpp', 'tools')))
import my_spawn

def override_build_output_messages(sys, env):

    colors = {}

    # Colors are disabled in non-TTY environments such as pipes. This means
    # that if output is redirected to a file, it will not contain color codes
    if sys.stdout.isatty():
        colors["cyan"] = "\033[96m"
        colors["purple"] = "\033[95m"
        colors["blue"] = "\033[94m"
        colors["green"] = "\033[92m"
        colors["yellow"] = "\033[93m"
        colors["red"] = "\033[91m"
        colors["end"] = "\033[0m"
    else:
        colors["cyan"] = ""
        colors["purple"] = ""
        colors["blue"] = ""
        colors["green"] = ""
        colors["yellow"] = ""
        colors["red"] = ""
        colors["end"] = ""

    compile_source_message = "{}Compiling {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    java_compile_source_message = "{}Compiling {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    compile_shared_source_message = "{}Compiling shared {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_program_message = "{}Linking Program        {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_library_message = "{}Linking Static Library {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    ranlib_library_message = "{}Ranlib Library         {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_shared_library_message = "{}Linking Shared Library {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    java_library_message = "{}Creating Java Archive  {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )

    env.Append(CXXCOMSTR=[compile_source_message])
    env.Append(CCCOMSTR=[compile_source_message])
    env.Append(SHCCCOMSTR=[compile_shared_source_message])
    env.Append(SHCXXCOMSTR=[compile_shared_source_message])
    env.Append(ARCOMSTR=[link_library_message])
    env.Append(RANLIBCOMSTR=[ranlib_library_message])
    env.Append(SHLINKCOMSTR=[link_shared_library_message])
    env.Append(LINKCOMSTR=[link_program_message])
    env.Append(JARCOMSTR=[java_library_message])
    env.Append(JAVACCOMSTR=[java_compile_source_message])

def get_build_output_messages(sys):
    colors = {}

    # Colors are disabled in non-TTY environments such as pipes. This means
    # that if output is redirected to a file, it will not contain color codes
    if sys.stdout.isatty():
        colors["cyan"] = "\033[96m"
        colors["purple"] = "\033[95m"
        colors["blue"] = "\033[94m"
        colors["green"] = "\033[92m"
        colors["yellow"] = "\033[93m"
        colors["red"] = "\033[91m"
        colors["end"] = "\033[0m"
    else:
        colors["cyan"] = ""
        colors["purple"] = ""
        colors["blue"] = ""
        colors["green"] = ""
        colors["yellow"] = ""
        colors["red"] = ""
        colors["end"] = ""

    compile_source_message = "{}Compiling {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    java_compile_source_message = "{}Compiling {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    compile_shared_source_message = "{}Compiling shared {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_program_message = "{}Linking Program        {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_library_message = "{}Linking Static Library {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    ranlib_library_message = "{}Ranlib Library         {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_shared_library_message = "{}Linking Shared Library {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    java_library_message = "{}Creating Java Archive  {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )

    return {
        'CXXCOMSTR': [compile_source_message],
        'SHCCCOMSTR': [compile_shared_source_message],
        'SHCXXCOMSTR': [compile_shared_source_message],
        'ARCOMSTR': [link_library_message],
        'RANLIBCOMSTR': [ranlib_library_message],
        'SHLINKCOMSTR': [link_shared_library_message],
        'LINKCOMSTR': [link_program_message],
        'JARCOMSTR': [java_library_message],
        'JAVACCOMSTR': [java_compile_source_message],
    }

def getConfigFileRelativePath():
    return 'appconfig.local.json'

def getConfigFileGodotBinaryFieldName():
    return 'godotBinaryAbsolutePath'

def getAppConfig():
    try:
        f = open(getConfigFileRelativePath())
    except FileNotFoundError as e:
        raise e
    config = json.load(f)
    f.close()
    return config


def getCachedGodotBinaryAbsolutePath():
    try:
        config = getAppConfig()
    except FileNotFoundError as e:
        raise e
    fieldName = getConfigFileGodotBinaryFieldName()
    if fieldName in config:
        return config[fieldName]
    else:
        raise ValueError("'" + fieldName + "' field not found in '" + getConfigFileRelativePath() + "'")
   
def setCachedGodotBinaryAbsolutePath(godotBinaryAbsolutePath):
    try:
        config = getAppConfig()
    except:
        config = {}
    config[getConfigFileGodotBinaryFieldName()] = godotBinaryAbsolutePath
    json_object = json.dumps(config, indent = 4)
    with open(getConfigFileRelativePath(), "w") as outfile:
        outfile.write(json_object)

def setVsCodeLaunchJsonGodotBinaryAbsolutePaths(godotBinaryAbsolutePath):
    if not godotBinaryAbsolutePath or not os.path.isfile(godotBinaryAbsolutePath):
        print('Invalid filepath: ', godotBinaryAbsolutePath)
        return False
    filePath = '.vscode/launch.json'
    try:
        f = open(filePath)
    except FileNotFoundError as e:
        return False
    launchJsonContents = json.load(f)
    f.close()

    if launchJsonContents and "configurations" in launchJsonContents:
        for config in launchJsonContents["configurations"]:
            if config and "program" in config:
                config["program"] = godotBinaryAbsolutePath
    json_object = json.dumps(launchJsonContents, indent = 4)
    with open(filePath, "w") as outfile:
        outfile.write(json_object)
        return True

def printList(list):
    ret = ''
    if (len(list) > 0):
        ret += '\n'
        for item in list:
            ret += ' - ' + str(item) + '\n'
    return ret

def autoDetectHostPlatform(sys):
    # Try to detect the host platform automatically.
    # This is used if no `platform` argument is passed
    if sys.platform.startswith("linux"):
        ret = "linux"
    elif sys.platform.startswith("freebsd"):
        ret = "freebsd"
    elif sys.platform == "darwin":
        ret = "osx"
    elif sys.platform == "win32" or sys.platform == "msys":
        ret = "windows"
    else:
        raise ValueError("Could not detect platform automatically, please specify with " "platform=<platform>")
    return ret

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags
    
def setLinuxEnv(env):
    # cpp_library += ".linux"
    env.Append(CCFLAGS=["-fPIC", "-Wwrite-strings"])
    env.Append(CXXFLAGS=["-std=c++17"])
    env.Append(LINKFLAGS=["-Wl,-R,'$$ORIGIN'"])
    
    if env["target"] == "debug":
        env.Append(CCFLAGS=["-g", "-Og"])
    else:
        env.Append(CCFLAGS=["-O3"])

def setWindowsEnv(env, os):
    base = None
    if not env["use_mingw"] and msvc.exists(env):
        if env["arch"] == "x86_64":
            env["TARGET_ARCH"] = "amd64"
        elif env["arch"] == "x86_32":
            env["TARGET_ARCH"] = "x86"
        env["is_msvc"] = True

        # MSVC, linker, and archiver.
        msvc.generate(env)
        env.Tool("mslib")
        env.Tool("mslink")

        env.Append(CPPDEFINES=["TYPED_METHOD_BIND", "NOMINMAX"])
        env.Append(CCFLAGS=["/utf-8"])
        env.Append(LINKFLAGS=["/WX"])

        if env["use_clang_cl"]:
            env["CC"] = "clang-cl"
            env["CXX"] = "clang-cl"

        if env["use_static_cpp"]:
            env.Append(CCFLAGS=["/MT"])
        else:
            env.Append(CCFLAGS=["/MD"])

    elif sys.platform == "win32" or sys.platform == "msys":
        env["use_mingw"] = True
        mingw.generate(env)
        # Don't want lib prefixes
        env["IMPLIBPREFIX"] = ""
        env["SHLIBPREFIX"] = ""
        # Want dll suffix
        env["SHLIBSUFFIX"] = ".dll"

        env.Append(CCFLAGS=["-Wwrite-strings"])
        env.Append(LINKFLAGS=["-Wl,--no-undefined"])
        env.Append(CXXFLAGS=["-Wa,-mbig-obj", "-std=c++17"]) # -flto  # -Wa,-mbig-obj
        if env["use_static_cpp"]:
            env.Append(
                LINKFLAGS=[
                    "-static",
                    "-static-libgcc",
                    "-static-libstdc++",
                ]
            )

        # Long line hack. Use custom spawn, quick AR append (to avoid files with the same names to override each other).
        my_spawn.configure(env)

    else:
        env["use_mingw"] = True
        # Cross-compilation using MinGW
        prefix = "i686" if env["arch"] == "x86_32" else env["arch"]
        env["CXX"] = prefix + "-w64-mingw32-g++"
        env["CC"] = prefix + "-w64-mingw32-gcc"
        env["AR"] = prefix + "-w64-mingw32-ar"
        env["RANLIB"] = prefix + "-w64-mingw32-ranlib"
        env["LINK"] = prefix + "-w64-mingw32-g++"
        # Want dll suffix
        env["SHLIBSUFFIX"] = ".dll"

        env.Append(CCFLAGS=["-Wwrite-strings"]) 
        env.Append(LINKFLAGS=["-Wl,--no-undefined"]) 
        env.Append(CXXFLAGS=["-Wa,-mbig-obj", "-std=c++17"]) # -flto  # -Wa,-mbig-obj
        if env["use_static_cpp"]:
            env.Append(
                LINKFLAGS=[
                    "-static",
                    "-static-libgcc",
                    "-static-libstdc++",
                ]
            )

    env.Append(CPPDEFINES=["WINDOWS_ENABLED"])

def parseChildSconstructBuildResults(res, env, os):
    if "builds" in res:
        for builtLibrary in res["builds"]:
            libraryPath = os.path.dirname(builtLibrary.path)
            libraryName = os.path.splitext(os.path.basename(builtLibrary.abspath))[0]
            if libraryName.startswith('lib'):
                libraryName = libraryName[len('lib'):]
            runtimeRelativeLibPath = os.path.basename(libraryPath)

            env['app_additionalLibraryPaths'].append(libraryPath)
            env['app_additionalLibraryNames'].append(libraryName)
            # runtimeRelativeLibPaths.append(os.path.join('\\$$ORIGIN', os.pardir, os.pardir, runtimeRelativeLibPath))
        if "headerfileIncludePaths" in res:
            for path in res["headerfileIncludePaths"]:
                env['app_additionalCppHeaderIncludePaths'].append(path.path)


# If `.vscode/launch.json` does NOT exist, then create it based on `.vscode/launch.json.example`
def createVsCodeConfigFilesIfNeeded():

    targets = {
        '.vscode/launch.json.example': '.vscode/launch.json'
    }
    actuallyCopiedTargets = {}
    copiedAtLeastOne = False
    for originalFile, localFile in targets.items():
        if not os.path.isfile(localFile) and os.path.isfile(originalFile):
            copyfile(originalFile, localFile)
            actuallyCopiedTargets[originalFile] = localFile
            copiedAtLeastOne = True
    if copiedAtLeastOne:
        return actuallyCopiedTargets
    else:
        return False

def printVerboseMessagesIfNeeded(env, vsCodeConfigFilesCreated):
    includePathsDisplayString = '\n   (Rerun with `show_include_paths=yes` to display the list)\n'
    if env["show_include_paths"]:
        includePathsDisplayString = printList(env['app_additionalCppHeaderIncludePaths'])

    if (env['verbose'] or vsCodeConfigFilesCreated):
        print('----')

    if vsCodeConfigFilesCreated:
        print('The following config files were created (you were missing them locally). Make sure to review their contents to match your system:')
        for originalFile, newFile in vsCodeConfigFilesCreated.items():
            print(' - ', originalFile, ' --> ', newFile, sep='')
        print('\n')

    if (env['verbose']):
        print('Building using the following header include paths: ', includePathsDisplayString)
        print('Using built libraries: ', printList(env['app_additionalLibraryNames']))
        print('Looking for built libraries in: ', printList(env['app_additionalLibraryPaths']))

    if (env['verbose'] or vsCodeConfigFilesCreated):
        print('----')