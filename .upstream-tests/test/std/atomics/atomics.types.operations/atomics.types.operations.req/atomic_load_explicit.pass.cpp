//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// UNSUPPORTED: libcpp-has-no-threads, pre-sm-60
//  ... assertion fails line 31

// <cuda/std/atomic>

// template <class T>
//     T
//     atomic_load_explicit(const volatile atomic<T>* obj, memory_order m);
//
// template <class T>
//     T
//     atomic_load_explicit(const atomic<T>* obj, memory_order m);

#include <cuda/std/atomic>
#include <cuda/std/type_traits>
#include <cuda/std/cassert>

#include "atomic_helpers.h"

template <class T, cuda::thread_scope>
struct TestFn {
  __host__ __device__
  void operator()() const {
    typedef cuda::std::atomic<T> A;
    A t;
    cuda::std::atomic_init(&t, T(1));
    assert(cuda::std::atomic_load_explicit(&t, cuda::std::memory_order_seq_cst) == T(1));
    volatile A vt;
    cuda::std::atomic_init(&vt, T(2));
    assert(cuda::std::atomic_load_explicit(&vt, cuda::std::memory_order_seq_cst) == T(2));
  }
};

int main(int, char**)
{
    TestEachAtomicType<TestFn>()();

  return 0;
}