package com.example.ashmem;

public class JNIInterface {
	
	static{
		System.loadLibrary("JNIInterface");
	}
	
	public static native int initAndGetFd2Ashmem();
	
	public static native void doOperaNow();
	
	public static native void doOperaLater(int fdReceived);

}
