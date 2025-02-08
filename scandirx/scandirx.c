/*
 * This code implements a Python extension module that provides directory walking functionality.
 * It recursively traverses directories and collects all file/folder paths, with optional depth control.
 */

/* Required for certain POSIX functions */
#define _POSIX_C_SOURCE 200809L

/* Include necessary header files */
#include <Python.h>      /* Python/C API */
#include <dirent.h>      /* Directory operations */
#include <sys/stat.h>    /* File status */
#include <string.h>      /* String operations */
#include <stdlib.h>      /* Memory allocation */
#include <stdio.h>       /* I/O operations */

/* Constants */
#define MAX_PATH_LEN 4096        /* Maximum length for file paths */
#define INITIAL_CAPACITY 10      /* Initial size of our paths array */

/* Structure to store a single file/directory path */
typedef struct {
    char path[MAX_PATH_LEN];     /* Store the full path */
} Entry;

/* Global variables to manage our collection of paths */
static Entry *entries = NULL;           /* Dynamic array of paths */
static int entry_count = 0;             /* Current number of paths stored */
static int entry_capacity = INITIAL_CAPACITY;  /* Current array capacity */

/* 
 * Comparison function for sorting paths alphabetically
 * Used by qsort() to sort the final list of paths
 */
static int compare_entries(const void *a, const void *b) {
    return strcmp(((Entry *)a)->path, ((Entry *)b)->path);
}

/* 
 * Ensures we have enough space to store new entries
 * Doubles the capacity when we run out of space
 */
static void ensure_capacity() {
    if (entry_count >= entry_capacity) {
        /* Double the array size */
        entry_capacity *= 2;
        
        /* Reallocate memory for the larger size */
        entries = realloc(entries, entry_capacity * sizeof(Entry));
        
        /* Check if memory allocation failed */
        if (!entries) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }
}

/*
 * Recursively walks through directories collecting paths
 * Parameters:
 * - base_path: Current directory path being processed
 * - current_depth: How deep we are in the directory tree
 * - max_depth: Maximum depth to traverse (-1 for unlimited)
 */
static void walk_dir(const char *base_path, int current_depth, int max_depth) {
    /* Try to open the directory */
    DIR *dir = opendir(base_path);
    if (!dir) return;  /* Skip if we can't open the directory */

    struct dirent *entry;        /* For reading directory entries */
    char sub_path[MAX_PATH_LEN]; /* For building full paths */

    /* Read each entry in the directory */
    while ((entry = readdir(dir)) != NULL) {
        /* Skip the "." and ".." special directories */
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
            continue;

        /* Build the full path by combining base_path and entry name */
        snprintf(sub_path, sizeof(sub_path), "%s/%s", base_path, entry->d_name);
        sub_path[sizeof(sub_path) - 1] = '\0';  /* Ensure null-termination */

        /* Get file/directory information */
        struct stat statbuf;
        if (stat(sub_path, &statbuf) == -1) 
            continue;  /* Skip if we can't get file info */

        /* Store this path in our array */
        ensure_capacity();
        snprintf(entries[entry_count].path, MAX_PATH_LEN, "%s", sub_path);
        entry_count++;

        /* If it's a directory and we haven't reached max_depth, recurse into it */
        if (S_ISDIR(statbuf.st_mode) && (max_depth == -1 || current_depth < max_depth)) {
            walk_dir(sub_path, current_depth + 1, max_depth);
        }
    }
    
    closedir(dir);  /* Clean up: close the directory */
}

/*
 * Python-callable function that initiates the directory walk
 * Args:
 * - src: Source directory path to start from
 * - max_depth: Optional maximum depth to traverse
 * Returns: List of all paths found
 */
static PyObject *walk(PyObject *self, PyObject *args) {
    const char *src;
    int max_depth = -1;  /* Default: unlimited depth */

    /* Parse Python arguments */
    if (!PyArg_ParseTuple(args, "s|i", &src, &max_depth)) {
        return NULL;  /* Return NULL on parsing failure */
    }

    /* Initialize/reset our storage */
    entry_count = 0;
    entry_capacity = INITIAL_CAPACITY;
    entries = malloc(entry_capacity * sizeof(Entry));
    if (!entries) {
        PyErr_NoMemory();
        return NULL;
    }

    /* Do the actual directory walking */
    walk_dir(src, 0, max_depth);

    /* Sort the collected paths */
    qsort(entries, entry_count, sizeof(Entry), compare_entries);

    /* Create Python list to hold results */
    PyObject *result_list = PyList_New(entry_count);
    if (!result_list) return NULL;

    /* Convert all paths to Python strings and add to list */
    for (int i = 0; i < entry_count; i++) {
        PyList_SetItem(result_list, i, PyUnicode_FromString(entries[i].path));
    }

    /* Clean up and return */
    free(entries);
    return result_list;
}

/* Define the methods available in this module */
static PyMethodDef ScandirxMethods[] = {
    {"walk", walk, METH_VARARGS, 
     "Walk a directory and return all file and folder paths. "
     "Args: path (str), max_depth (int, optional)"},
    {NULL, NULL, 0, NULL}  /* Required sentinel value */
};

/* Define the module configuration */
static struct PyModuleDef scandirxmodule = {
    PyModuleDef_HEAD_INIT,
    "_scandirx",                    /* Renamed Module name */
    "Directory walking module",     /* Module documentation */
    -1,                             /* Module keeps state in global variables */
    ScandirxMethods
};

/* Module initialization function */
PyMODINIT_FUNC PyInit__scandirx(void) {  /* Renamed Initialization function */
    return PyModule_Create(&scandirxmodule);
}
