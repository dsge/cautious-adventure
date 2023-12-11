import os
import sys
import utils

Import('env')

libraryBasePath = '../lib/hypodermic'

boostLibsBasePath = '../lib/boost'


headerfileIncludePaths = [
    libraryBasePath,
]

for boostSubLibraryPath in Glob(boostLibsBasePath + '/libs/*'):
    path = boostSubLibraryPath.relpath + '/include/'
    if os.path.isdir('../' + path):
        headerfileIncludePaths.append('../' + path)

env.Decider("content-timestamp")

env.Default(libraryBasePath)

ret = {
    'builds': [], 
    'headerfileIncludePaths': list(map(Dir, headerfileIncludePaths))
}
Return('ret')