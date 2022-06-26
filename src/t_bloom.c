#define PY_SSIZE_T_CLEAN
#include <Python.h>


extern uint32_t hash_crc32 (char *buffer, size_t length) ;


typedef struct {
    PyObject_HEAD
    Py_ssize_t size; // size of the filter
    uint8_t *array; // filter contents
} Object;


// __init__
static int
tp_init(Object *self, PyObject *args, PyObject *kwds) {
    if (!PyArg_ParseTuple(args, "n", &self->size)) { return -1; }
    self->array = calloc(self->size, sizeof(uint8_t));
    return 0;
}


// destructor
static void
tp_dealloc(Object *self) {
    free(self->array);
    Py_TYPE(self)->tp_free((PyObject *)self);
}


// parse array index from object
static uint64_t
parse_index(Object *self, PyObject *arg) {
    // __hash__ collates -1 to -2. Returns -1 only on error.
    Py_hash_t hash = PyObject_Hash(arg);
    if (hash == -1) {
        PyErr_SetString(PyExc_RuntimeError, "cannot run __hash__ on object");
    }
    // Copy python modulo operator logic.
    return (hash < 0) ? self->size + hash % self->size : hash % self->size;
}


// put
static PyObject *
method_put(Object *self,  PyObject *arg) {
    uint64_t ix = parse_index(self, arg);
    self->array[ix] = 1;
    Py_RETURN_NONE;
}


// del
static PyObject *
method_del(Object *self, PyObject *arg) {
    uint64_t ix = parse_index(self, arg);
    self->array[ix] = 0;
    Py_RETURN_NONE;
}


// has
static PyObject *
method_has(Object *self, PyObject *arg) {
    uint64_t ix = parse_index(self, arg);
    if (self->array[ix] == 1) { Py_RETURN_TRUE; }
    Py_RETURN_FALSE;
}


// len
static PyObject *
method_len(Object *self) {
    return Py_BuildValue("n", self->size);
}


// count
static PyObject *
method_count(Object *self) {
    Py_ssize_t count = 0;
    for (Py_ssize_t i = 0; i < self->size; i++) {
        if (self->array[i] == 1) { count += 1; }
    }
    return Py_BuildValue("n", count);
}


// clear
static PyObject *
method_clear(Object *self) {
    memset(self->array, 0, self->size);
    Py_RETURN_NONE;
}


// dumps
static PyObject *
method_dumps(Object *self) {
    char *buf = malloc(self->size);
    for (Py_ssize_t i = 0; i < self->size; i++) {
        if (self->array[i] == 0) { buf[i] = '0'; } else { buf[i] = '1'; }
    }
    PyObject *out = Py_BuildValue("y#", buf, self->size);
    free(buf);
    return out;
}


static PyMethodDef methods[] = {
    {"put", (PyCFunction)method_put, METH_O,
        PyDoc_STR("Put the value into the filter.")},
    {"del", (PyCFunction)method_del, METH_O,
        PyDoc_STR("Remove the value from the filter.")},
    {"has", (PyCFunction)method_has, METH_O,
        PyDoc_STR("Check if the value is in the filter.")},
    {"len", (PyCFunction)method_len, METH_NOARGS,
        PyDoc_STR("Get the size of the filter.")},
    {"count", (PyCFunction)method_count, METH_NOARGS,
        PyDoc_STR("Count the number of items inserted.")},
    {"clear", (PyCFunction)method_clear, METH_NOARGS,
        PyDoc_STR("Clear the filter contents.")},
    {"dumps", (PyCFunction)method_dumps, METH_NOARGS,
        PyDoc_STR("Dump filter contents into a bytes object.")},
    {NULL} /* Sentinel */
};


PyTypeObject BloomType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "cbloom.Bloom",
    .tp_doc = PyDoc_STR("Bloom filter."),
    .tp_basicsize = sizeof(Object),
    .tp_itemsize = sizeof(uint8_t),
    .tp_dealloc = (destructor)tp_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)tp_init,
    .tp_hash = PyObject_HashNotImplemented,
    .tp_methods = methods,
};
