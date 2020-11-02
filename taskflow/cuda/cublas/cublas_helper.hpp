#pragma once

#include "cublas_handle.hpp"

namespace tf {

/** 
@file cublas_helper.hpp
*/

/**
@brief copies vector data from host to device

This method copies @c n elements from a vector @c h in host memory space 
to a vector @c d in GPU memory space. 
The storage spacing between consecutive elements is given by @c inch for 
the source vector @c h and by @c incd for the destination vector @c d.

@tparam T data type
@param stream stream to associate with this copy operation
@param n number of elements
@param d target device pointer
@param incd spacing between consecutive elements in @c d
@param h source host pointer
@param inch spacing between consecutive elements in @c h

*/
template <typename T,
  std::enable_if_t<!std::is_same_v<T, void>, void>* = nullptr
>
void cublas_vset_async(
  cudaStream_t stream, size_t n, const T* h, int inch, T* d, int incd
) {
  TF_CHECK_CUBLAS(
    cublasSetVectorAsync(n, sizeof(T), h, inch, d, incd, stream),
    "failed to run vset_async"
  );
}

/**
@brief similar to tf::cublas_vset_async but operates synchronously
*/
template <typename T,
  std::enable_if_t<!std::is_same_v<T, void>, void>* = nullptr
>
void cublas_vset(size_t n, const T* h, int inch, T* d, int incd) {
  TF_CHECK_CUBLAS(
    cublasSetVector(n, sizeof(T), h, inch, d, incd),
    "failed to run vset"
  );
}

/**
@brief copies vector data from device to host

This method copies @c n elements from a vector @c d in GPU memory space 
to a vector @c h in host memory space. 
The storage spacing between consecutive elements is given by @c inch for 
the target vector @c h and by @c incd for the source vector @c d.

@tparam T data type
@param stream stream to associate with this copy operation
@param n number of elements
@param h target host pointer
@param inch spacing between consecutive elements in @c h
@param d source device pointer
@param incd spacing between consecutive elements in @c d

*/
template <typename T,
  std::enable_if_t<!std::is_same_v<T, void>, void>* = nullptr
>
void cublas_vget_async(
  cudaStream_t stream, size_t n, const T* d, int incd, T* h, int inch
) {
  TF_CHECK_CUBLAS(
    cublasGetVectorAsync(n, sizeof(T), d, incd, h, inch, stream),
    "failed to run vget_async"
  );
}

/**
@brief similar to tf::cublas_vget_async but operates synchronously
*/
template <typename T,
  std::enable_if_t<!std::is_same_v<T, void>, void>* = nullptr
>
void cublas_vget_async(size_t n, const T* d, int incd, T* h, int inch) {
  TF_CHECK_CUBLAS(
    cublasGetVector(n, sizeof(T), d, incd, h, inch), "failed to run vget"
  );
}

}  // end of namespace tf -----------------------------------------------------

