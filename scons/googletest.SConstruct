
import sys
import utils
import copy

Import('env')

libraryBasePath = '../lib/googletest'

headerfileIncludePaths = [
    libraryBasePath + '/googletest/include/',
    libraryBasePath + '/googletest/include/gtest/',
    libraryBasePath + '/googletest/',
    libraryBasePath + '/googletest/src/'
]

env.Append(CPPPATH=headerfileIncludePaths)
# env.VariantDir('../lib/googletest/build', '../lib/googletest', duplicate=0)

env.Decider("content-timestamp")

env.Default(libraryBasePath)

ret = env.StaticLibrary(target= libraryBasePath + '/googletest/build/gtest', source=[libraryBasePath + '/googletest/src/gtest-all.cc'])
ret = {
    'builds': [ret[0]], 
    'headerfileIncludePaths': list(map(Dir, headerfileIncludePaths))
}
Return('ret')