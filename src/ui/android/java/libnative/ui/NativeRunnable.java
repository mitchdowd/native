package libnative.ui;

public class NativeRunnable implements Runnable {
    private long _funcPtr;

    public NativeRunnable(long funcPtr) {
        this._funcPtr = funcPtr;
    }

    @Override
    public void run() { onRun(_funcPtr); }

    private native void onRun(long funcPtr);
}
