package libnative.ui;

import android.app.Activity;
import android.content.Context;
import android.graphics.Canvas;

public class Window extends android.widget.RelativeLayout implements INativeComponent {
    public Window(Context context) {
        super(context);

        setWillNotDraw(false);

        // Window is the main view.
        if (context instanceof Activity)
            ((Activity) context).setContentView(this);
    }

    @Override
    protected void onDraw(Canvas canvas) { ViewExtensions.onPaint(this, canvas); }

    @Override
    public void onSizeChanged(int w, int h, int oldW, int oldH) {
        ViewExtensions.onSize(this, w, h);
    }
}
