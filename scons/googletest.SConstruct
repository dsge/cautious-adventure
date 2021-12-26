
import sys
import utils

env = Environment()

# env.Append(CPPPATH = buildtimeIncludePaths) # where to look for #included files
# env.Append(LIBPATH = buildtimeIncludePaths) # where to look for the LIBS
# env.Append(LIBS = libraryNames)

# env.Append( LINKFLAGS = Split('-z origin') )

libraryBasePath = '../lib/googletest'

headerfileIncludePaths = [
    libraryBasePath + '/googletest/include/',
    libraryBasePath + '/googletest/include/gtest/',
    libraryBasePath + '/googletest/',
    libraryBasePath + '/googletest/src/'
]

env.Append(CPPPATH=headerfileIncludePaths)
# env.VariantDir('../lib/googletest/build', '../lib/googletest', duplicate=0)

Decider("content-timestamp")

Default(libraryBasePath)

utils.override_build_output_messages(sys, env) 

ret = env.StaticLibrary(target= libraryBasePath + '/googletest/build/gtest', source=[libraryBasePath + '/googletest/src/gtest-all.cc'])
ret = {
    'builds': [ret[0]], 
    'headerfileIncludePaths': list(map(Dir, headerfileIncludePaths))
}
Return('ret')