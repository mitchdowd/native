package libnative.ui;

import android.app.Activity;
import android.content.Context;
import android.graphics.Canvas;
import android.widget.RelativeLayout;
import android.widget.ScrollView;

public class Window extends RelativeLayout {
    public Window(Context context) {
        super(context);

        setWillNotDraw(false);

        // Window is the main view.
        if (context instanceof Activity) {
            ScrollView parent = new ScrollView(context);

            parent.addView(this);

            ((Activity) context).setContentView(parent);
        }
    }

    @Override
    protected void onDraw(Canvas canvas) { ViewExtensions.onPaint(this, canvas); }

    @Override
    public void onSizeChanged(int w, int h, int oldW, int oldH) { ViewExtensions.onSize(this, w, h); }
}
