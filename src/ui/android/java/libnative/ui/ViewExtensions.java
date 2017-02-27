package libnative.ui;

import android.graphics.Canvas;
import android.view.View;

class ViewExtensions {
    public native static void onPaint(View view, Canvas canvas);
    public native static void onSize(View view, int width, int height);
}
