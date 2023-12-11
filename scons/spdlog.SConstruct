
import sys
import utils

Import('env')

libraryBasePath = '../lib/spdlog'

headerfileIncludePaths = [
    libraryBasePath + '/include/',
]
env.Replace(CPPPATH=headerfileIncludePaths)

env.Decider("content-timestamp")

env.Default(libraryBasePath)

env.Replace(CPPDEFINES=['SPDLOG_COMPILED_LIB'])

ret = env.StaticLibrary(target= libraryBasePath + '/build/spdlog', source=Glob(libraryBasePath + '/src/*.cpp'))
ret = {
    'builds': [ret[0]], 
    'headerfileIncludePaths': list(map(Dir, headerfileIncludePaths))
}
Return('ret')