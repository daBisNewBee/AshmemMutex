package com.example.ashmem;

import android.util.Log;

public class Logger {
	
	private static final String TAG = "JNI";
	
	public static void v(String msg){
		Log.v(TAG,msg);
	}

}
