#define PY_SSIZE_T_CLEAN
#include <Python.h>


extern uint32_t hash_crc32 (char *buffer, size_t length);
extern uint32_t hash_adler32 (char *buffer, size_t length) ;


static PyObject *
pyhash_crc32(PyObject *self, PyObject *arg) {
    if (PyBytes_CheckExact(arg) != 1) {
        PyErr_SetString(PyExc_TypeError, "is not a bytes object");
    }
    Py_ssize_t size = PyBytes_Size(arg);
    char *buffer = PyBytes_AsString(arg);
    uint32_t checksum = hash_crc32(buffer, size);
    return PyLong_FromUnsignedLongLong(checksum);
}


static PyObject *
pyhash_adler32(PyObject *self, PyObject *arg) {
    if (PyBytes_CheckExact(arg) != 1) {
        PyErr_SetString(PyExc_TypeError, "is not a bytes object");
    }
    Py_ssize_t size = PyBytes_Size(arg);
    char *buffer = PyBytes_AsString(arg);
    uint32_t checksum = hash_adler32(buffer, size);
    return PyLong_FromUnsignedLongLong(checksum);
}


PyMethodDef cbloomMethods[] = {
    {"crc32", pyhash_crc32, METH_O,
        PyDoc_STR("crc32 hash function, returns uint32.")},
    {"adler32", pyhash_adler32, METH_O,
        PyDoc_STR("adler32 hash function return uint32.")},
    {NULL, NULL, 0, NULL}
};
