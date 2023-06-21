#include <Python.h>

#include <iostream>
#include <chrono>

#include <opencv2/opencv.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaimgproc.hpp>

static PyObject* preprocess(PyObject *self, PyObject *args, PyObject *keywds){
    int img_w, img_h;

    unsigned char *img_data;

    static char *kwlist[] = {"img_w", "img_h", "img_data", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iiy*", kwlist,
                                     &img_w, &img_h, &img_data))
        return NULL;


    cv::TickMeter npTimer;
    npTimer.start();

    cv::Mat frame(img_h, img_w, CV_8UC3, img_data);
    cv::imshow("preprocess", frame);
    cv::waitKey(0);

    npTimer.stop();

    double npTime = npTimer.getTimeSec();
    
    // Py_RETURN_NONE;

    return PyFloat_FromDouble(npTime);    
}

static PyMethodDef PreprocessMethods[] = {
    {"preprocess", (PyCFunction)preprocess, METH_VARARGS | METH_KEYWORDS, "preprocess the task"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef Preprocess =
{
    PyModuleDef_HEAD_INIT,
    "Preprocess", /* name of module */
    "usage: preprocess()\n", /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    PreprocessMethods
};

PyMODINIT_FUNC PyInit_task(void) {
     return PyModule_Create(&Preprocess);
}