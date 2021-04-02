from distutils.core import setup, Extension

cpp_module_01 = Extension('cpp_module_01', sources=['cpp_module_01.cpp'])

setup( 
        name = 'CPPModule', 
        version='1.0', 
        description='This is a monkey module', 
        ext_modules=[cpp_module_01]
    )
