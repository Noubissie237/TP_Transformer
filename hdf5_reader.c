#include "hdf5_reader.h"
#include <hdf5.h>
#include <stdio.h>
#include <stdlib.h>

Dataset load_hdf5(const char *filename) {
    Dataset dataset;
    hid_t file_id, dataset_id, dataspace_id;
    herr_t status;

    // Open the HDF5 file
    file_id = H5Fopen(filename, H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Open the dataset
    dataset_id = H5Dopen2(file_id, "/dataset_name", H5P_DEFAULT);
    if (dataset_id < 0) {
        fprintf(stderr, "Error opening dataset in file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Get the dataspace
    dataspace_id = H5Dget_space(dataset_id);
    if (dataspace_id < 0) {
        fprintf(stderr, "Error getting dataspace in file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the dataset and read it
    hsize_t dims[2];
    H5Sget_simple_extent_dims(dataspace_id, dims, NULL);
    dataset.data = (float*)malloc(dims[0] * dims[1] * sizeof(float));
    status = H5Dread(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataset.data);
    if (status < 0) {
        fprintf(stderr, "Error reading dataset in file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Set dataset dimensions
    dataset.num_rows = dims[0];
    dataset.num_cols = dims[1];

    // Close HDF5 resources
    H5Sclose(dataspace_id);
    H5Dclose(dataset_id);
    H5Fclose(file_id);

    return dataset;
}

void free_dataset(Dataset dataset) {
    free(dataset.data);
}
