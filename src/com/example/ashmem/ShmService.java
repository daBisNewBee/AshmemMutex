package com.example.ashmem;

import java.io.IOException;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.os.ParcelFileDescriptor;
import android.os.RemoteException;

public class ShmService extends Service {
	
	private Binder binder = new IShmService.Stub() {
        @Override
        public ParcelFileDescriptor getFD() throws RemoteException {
            Logger.v("into ShmService getFD .pid:"+android.os.Process.myPid());
            int fd =MainActivity.ashmemFd;
            ParcelFileDescriptor pfd = null;
            try {
                pfd = ParcelFileDescriptor.fromFd(fd);
            } catch (IOException e) {
                e.printStackTrace();
            }
            return pfd;
        }
    };

	@Override
	public IBinder onBind(Intent arg0) {
		// TODO Auto-generated method stub
		return binder;
	}

}
