/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: I:\\workspace\\eclipse\\Ashmem\\src\\com\\example\\ashmem\\IShmService.aidl
 */
package com.example.ashmem;
// Declare any non-default types here with import statements

public interface IShmService extends android.os.IInterface
{
/** Local-side IPC implementation stub class. */
public static abstract class Stub extends android.os.Binder implements com.example.ashmem.IShmService
{
private static final java.lang.String DESCRIPTOR = "com.example.ashmem.IShmService";
/** Construct the stub at attach it to the interface. */
public Stub()
{
this.attachInterface(this, DESCRIPTOR);
}
/**
 * Cast an IBinder object into an com.example.ashmem.IShmService interface,
 * generating a proxy if needed.
 */
public static com.example.ashmem.IShmService asInterface(android.os.IBinder obj)
{
if ((obj==null)) {
return null;
}
android.os.IInterface iin = obj.queryLocalInterface(DESCRIPTOR);
if (((iin!=null)&&(iin instanceof com.example.ashmem.IShmService))) {
return ((com.example.ashmem.IShmService)iin);
}
return new com.example.ashmem.IShmService.Stub.Proxy(obj);
}
@Override public android.os.IBinder asBinder()
{
return this;
}
@Override public boolean onTransact(int code, android.os.Parcel data, android.os.Parcel reply, int flags) throws android.os.RemoteException
{
switch (code)
{
case INTERFACE_TRANSACTION:
{
reply.writeString(DESCRIPTOR);
return true;
}
case TRANSACTION_getFD:
{
data.enforceInterface(DESCRIPTOR);
android.os.ParcelFileDescriptor _result = this.getFD();
reply.writeNoException();
if ((_result!=null)) {
reply.writeInt(1);
_result.writeToParcel(reply, android.os.Parcelable.PARCELABLE_WRITE_RETURN_VALUE);
}
else {
reply.writeInt(0);
}
return true;
}
}
return super.onTransact(code, data, reply, flags);
}
private static class Proxy implements com.example.ashmem.IShmService
{
private android.os.IBinder mRemote;
Proxy(android.os.IBinder remote)
{
mRemote = remote;
}
@Override public android.os.IBinder asBinder()
{
return mRemote;
}
public java.lang.String getInterfaceDescriptor()
{
return DESCRIPTOR;
}
// 跨进程获取fd

@Override public android.os.ParcelFileDescriptor getFD() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
android.os.ParcelFileDescriptor _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_getFD, _data, _reply, 0);
_reply.readException();
if ((0!=_reply.readInt())) {
_result = android.os.ParcelFileDescriptor.CREATOR.createFromParcel(_reply);
}
else {
_result = null;
}
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
}
static final int TRANSACTION_getFD = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
}
// 跨进程获取fd

public android.os.ParcelFileDescriptor getFD() throws android.os.RemoteException;
}
