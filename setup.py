from distutils.core import setup, Extension

maze_generator = Extension('maze_generator', sources=['maze_generator.cpp'])

setup( 
        name = 'CPPModule', 
        version='1.0', 
        description='This is a monkey module', 
        ext_modules=[maze_generator]
    )
