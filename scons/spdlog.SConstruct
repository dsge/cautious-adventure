
import sys
import utils

env = Environment()

# env.Append(CPPPATH = buildtimeIncludePaths) # where to look for #included files
# env.Append(LIBPATH = buildtimeIncludePaths) # where to look for the LIBS
# env.Append(LIBS = libraryNames)

# env.Append( LINKFLAGS = Split('-z origin') )

env.Append(CCFLAGS=["-fPIC"])
env.Append(CXXFLAGS=["-std=c++17"])

libraryBasePath = '../lib/spdlog'

headerfileIncludePaths = [
    libraryBasePath + '/include/',
]

env.Append(CPPPATH=headerfileIncludePaths)

Decider("content-timestamp")

Default(libraryBasePath)

utils.override_build_output_messages(sys, env) 

env.Append(CPPDEFINES=['SPDLOG_COMPILED_LIB'])

ret = env.StaticLibrary(target= libraryBasePath + '/build/spdlog', source=Glob(libraryBasePath + '/src/*.cpp'))
ret = {
    'builds': [ret[0]], 
    'headerfileIncludePaths': list(map(Dir, headerfileIncludePaths))
}
Return('ret')