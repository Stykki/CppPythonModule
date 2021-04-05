# CppPythonModule

# Installation
After donwloading and unpacking cd into the root directory and run
```
python setup.py build
python setup.py install
```
After installation try running the test module named "testModule.py"

# How to use
After installation generating mazes becomes as easy as
```python
import cpp_module_01

#                                    Width   Height   visible  Display Delay    Seed
prims = cpp_module_01.generatePrims(   6  ,    6    ,    1    ,    30      ,     40    )
kruskals = cpp_module_01.generateKruskals(6,6,1, 30)
aldusBroder = cpp_module_01.generateAldusBroder(6,6,1, 30)
sideWinder = cpp_module_01.generateSideWinder(6,6,1, 30)
recursive = cpp_module_01.generateRecursiveBacktrack(10,10,1, 30)
```

# Non optional parameters
## Width & Height
  The width and Height of the maze
  
# Optional parameters
## Visability
  Wether the maze is displayed during creation
  1 = display
  0 = no display
  
## Display Delay
  time in ms between prints (only matters if visable = 1)
  
## Seed
  Random if 0 else user input
  
