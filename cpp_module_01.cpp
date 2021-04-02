#include "Python.h"

static PyObject* fyrstObj(PyObject* self, PyObject* args)
{
    PyObject* ls = PyList_New(0);
    PyList_Append(ls, PyLong_FromLong(1));
    PyList_Append(ls, PyLong_FromLong(1));
    return ls;
}

static PyMethodDef mainMethods[] = {
    {"fyrstObj", fyrstObj, METH_VARARGS,"return a hello string"},
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


