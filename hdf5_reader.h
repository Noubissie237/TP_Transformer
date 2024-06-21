#ifndef HDF5_READER_H
#define HDF5_READER_H

typedef struct {
    // Définir la structure du Dataset
} Dataset;

Dataset load_hdf5(const char *filename);
void free_dataset(Dataset dataset);

#endif // HDF5_READER_H
