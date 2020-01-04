##------------##
## SConscript ##
##-------------------------------------------------------##
## author: Jaegwang Lim @ Dexter Studios                 ##
## last update: 2018.12.05                               ##
##-------------------------------------------------------##

import SCons.Tool
import SCons.Defaults
import os, sys
import shutil
from distutils.dir_util import copy_tree

#################
# C++ Compile   #
#################

cppenv = Environment()
cppenv['ENV']['TERM'] = os.environ['TERM']
cppenv['STATIC_AND_SHARED_OBJECTS_ARE_THE_SAME'] = 1

cppenv.Append( CCFLAGS = '-Wall -O3 -std=c++17 -fPIC' )
cppenv.Append( CCFLAGS = [
    
])

cppenv.Append( CPPPATH = [
    './header',
    '/Users/jaegwang/Library/Python/3.7/include/python3.7m',
    '/usr/local/include/python3.7m',
    '/usr/local/Cellar/python/3.7.6_1/Frameworks/Python.framework/Versions/3.7/include/python3.7m'
])

#cppenv.Append( LIBPATH = LIBRARY_PATH )
cppenv.Append( LIBPATH = [
])

#cppenv.Append( LIBS = LIBRARY_LIST )
cppenv.Append( LIBS = [
])

#cppenv.Append( CPPDEFINES = DEFINE_LIST )
cppenv.Append( CPPDEFINES = [

])

cppenv.Object( Glob('source/*.cpp') )
cppenv.SharedLibrary( 'example.so', Glob('source/*.o'), LINKFLAGS='-undefined dynamic_lookup' )
#cppenv.Program( 'test', Glob('source/*.o') )

os.system('cp -rf libexample.so ../../example.so')
