// IShmService.aidl
package com.example.ashmem;

// Declare any non-default types here with import statements

interface IShmService {

    // 跨进程获取fd
    ParcelFileDescriptor getFD();

}