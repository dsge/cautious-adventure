import os

env = Environment()

# env.Append(CPPPATH = buildtimeIncludePaths) # where to look for #included files
# env.Append(LIBPATH = buildtimeIncludePaths) # where to look for the LIBS
# env.Append(LIBS = libraryNames)

# env.Append( LINKFLAGS = Split('-z origin') )

libraryBasePath = '../lib/hypodermic'

boostLibsBasePath = '../lib/boost'


headerfileIncludePaths = [
    libraryBasePath,
]

for boostSubLibraryPath in Glob(boostLibsBasePath + '/libs/*'):
    path = boostSubLibraryPath.relpath + '/include/'
    if os.path.isdir('../' + path):
        headerfileIncludePaths.append('../' + path)

# env.Append(CPPPATH=headerfileIncludePaths)

Decider("content-timestamp")

Default(libraryBasePath)

# ret = env.StaticLibrary(target= libraryBasePath + '/googletest/build/gtest', source=[libraryBasePath + '/googletest/src/gtest-all.cc'])
ret = {
    'builds': [], 
    'headerfileIncludePaths': list(map(Dir, headerfileIncludePaths))
}
Return('ret')