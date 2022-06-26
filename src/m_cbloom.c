#define PY_SSIZE_T_CLEAN
#include <Python.h>


extern PyTypeObject BloomType;
extern PyMethodDef cbloomMethods[];


static PyModuleDef cbloom = {
    PyModuleDef_HEAD_INIT,
    .m_name = "cbloom",
    .m_doc = PyDoc_STR("Compact bloom filter."),
    .m_size = -1,
    .m_methods = cbloomMethods
};


PyMODINIT_FUNC
PyInit_cbloom(void)
{
    // Check type is ready.
    if (PyType_Ready(&BloomType) < 0) { return NULL; }

    // Creating module.
    PyObject *m;
    m = PyModule_Create(&cbloom);
    if (m == NULL) { return NULL; }

    // Add object to the module.
    Py_INCREF(&BloomType);
    if (PyModule_AddObject(m, "Bloom", (PyObject *) &BloomType) < 0) {
        Py_DECREF(&BloomType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
