#include "Python.h"
#include "./lib/sidewinder.cpp"


static PyObject* generateKruskals(PyObject* self, PyObject* args)
{
    int w, h, d=0, del=2;
    PyArg_ParseTuple(args,"ii|ii", &w, &h, &d, &del);
    PyObject* ls = PyList_New(0);
    Kruskals* T = new Kruskals(w, h);
    if ( d != 1){
        T->toggleDisplay();
    }
    T->setDelay(del);
    T->run(1);
    int * mz = T->getMaze();
    for(int i = 0; i < h; i++)
    {
        PyObject* temp = PyList_New(0);
        for ( int j = 0; j < w; j++)
        {
            PyList_Append(temp, PyLong_FromLong(mz[i*w+j]));
        }
        PyList_Append(ls, temp);
    }
    T->printGrid();
    delete T;
    return ls;
}

static PyObject* generatePrims(PyObject* self, PyObject* args)
{
    int w, h, d = 0, del = 2;
    
    PyArg_ParseTuple(args,"ii|ii", &w, &h, &d, &del);

    PyObject* ls = PyList_New(0);
    Prims *P = new Prims(w, h);

    if ( d != 1){
        P->toggleDisplay();
    }
    P->setDelay(del);
    P->run(1);
    int * mz = P->getMaze();
    for(int i = 0; i < h; i++)
    {
        PyObject* temp = PyList_New(0);
        for ( int j = 0; j < w; j++)
        {
            PyList_Append(temp, PyLong_FromLong(mz[i*w+j]));
        }
        PyList_Append(ls, temp);
    }
    P->printGrid();
    delete P;
    return ls;
}

static PyObject* generateRecursiveBacktrack(PyObject* self, PyObject* args)
{
    int w, h, d=0, del=2;
    PyArg_ParseTuple(args,"ii|ii", &w, &h, &d, &del);

    
    RecursiveBacktrack *P = new RecursiveBacktrack(w, h);
    PyObject* ls = PyList_New(0);

    if ( d != 1){
        P->toggleDisplay();
    }
    P->setDelay(del);

    P->run(1);
    int * mz = P->getMaze();
    for(int i = 0; i < h; i++)
    {
        PyObject* temp = PyList_New(0);
        for ( int j = 0; j < w; j++)
        {
            PyList_Append(temp, PyLong_FromLong(mz[i*w+j]));
        }
        PyList_Append(ls, temp);
    }
    P->printGrid();
    delete P;
    return ls;
}


static PyObject* generateAldusBroder(PyObject* self, PyObject* args)
{
    int w, h, d=0, del=2;
    PyArg_ParseTuple(args,"ii|ii", &w, &h, &d, &del);

    
    AldusBroder *P = new AldusBroder(w, h);
    PyObject* ls = PyList_New(0);

    if ( d != 1){
        P->toggleDisplay();
    }
    P->setDelay(del);

    P->run(1);
    int * mz = P->getMaze();
    for(int i = 0; i < h; i++)
    {
        PyObject* temp = PyList_New(0);
        for ( int j = 0; j < w; j++)
        {
            PyList_Append(temp, PyLong_FromLong(mz[i*w+j]));
        }
        PyList_Append(ls, temp);
    }
    P->printGrid();
    delete P;
    return ls;
}

static PyObject* generateSideWinder(PyObject* self, PyObject* args)
{
    int w, h, d=0, del=2;
    PyArg_ParseTuple(args,"ii|ii", &w, &h, &d, &del);

    
    PyObject* ls = PyList_New(0);
    SideWinder *P = new SideWinder(w, h);

    if ( d != 1){
        P->toggleDisplay();
    }
    P->setDelay(del);

    P->run(1);
    int * mz = P->getMaze();
    for(int i = 0; i < h; i++)
    {
        PyObject* temp = PyList_New(0);
        for ( int j = 0; j < w; j++)
        {
            PyList_Append(temp, PyLong_FromLong(mz[i*w+j]));
        }
        PyList_Append(ls, temp);
    }
    P->printGrid();
    delete P;
    return ls;
}

static PyMethodDef mainMethods[] = {
    {"generateKruskals", generateKruskals, METH_VARARGS,"Parameters, int Width , int Heigt, bool Display, int Delay returns a 2d array"},
    {"generatePrims", generatePrims, METH_VARARGS,"Parameters, int Width , int Heigt, bool Display, int Delay returns a 2d array"},
    {"generateRecursiveBacktrack", generateRecursiveBacktrack, METH_VARARGS,"Parameters, int Width , int Heigt, bool Display, int Delay returns a 2d array"},
    {"generateAldusBroder", generateAldusBroder, METH_VARARGS,"Parameters, int Width , int Heigt, bool Display, int Delay returns a 2d array"},
    {"generateSideWinder", generateSideWinder, METH_VARARGS,"Parameters, int Width , int Heigt, bool Display, int Delay returns a 2d array"},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef cpp_module_01 = {
    PyModuleDef_HEAD_INIT,
    "cpp_module_01", "This is a module",
    -1,
    mainMethods
};

PyMODINIT_FUNC PyInit_cpp_module_01(void){

    return PyModule_Create(&cpp_module_01);
}


