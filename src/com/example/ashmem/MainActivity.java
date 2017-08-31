package com.example.ashmem;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends Activity {
	
	public static int ashmemFd;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		ashmemFd = JNIInterface.initAndGetFd2Ashmem();
		Logger.v("initAndGetFd2Ashmem fd:"+ashmemFd);
		
		findViewById(R.id.btnMutx).setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				
				new Thread(){
					public void run(){
						JNIInterface.doOperaNow();
					}
				}.start();
				
				new Thread(){
					public void run(){
						Intent intent = new Intent(MainActivity.this,RemoteService.class);
						startService(intent);
					}
				}.start();
				
				
				
			}
		});
		
		findViewById(R.id.btnComm).setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				
			}
		});
	
	}

}
