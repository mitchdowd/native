package libnative.ui;

import android.content.Context;
import android.graphics.Canvas;

public class Button extends android.widget.Button {
    public Button(Context context) {
        super(context);
    }

    public void setArea(int x, int y, int width, int height) { ViewExtensions.setArea(this, x, y, width, height); }

    @Override
    protected void onDraw(Canvas canvas) { ViewExtensions.onPaint(this, canvas); }

    @Override
    public void onSizeChanged(int w, int h, int oldW, int oldH) { ViewExtensions.onSize(this, w, h); }
}
