package libnative.ui;

import android.content.Context;
import android.graphics.Canvas;
import android.view.MotionEvent;

public class ProgressBar extends android.widget.ProgressBar implements INativeComponent {
    public ProgressBar(Context context) {
        super(context, null, android.R.attr.progressBarStyleHorizontal);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        switch (event.getAction())
        {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_MOVE:
                return ViewExtensions.onInput(this, event);
        }

        return super.onTouchEvent(event);
    }

    @Override
    protected void onDraw(Canvas canvas) { ViewExtensions.onPaint(this, canvas); }

    @Override
    public void onSizeChanged(int w, int h, int oldW, int oldH) {
        super.onSizeChanged(w, h, oldW, oldH);
        ViewExtensions.onSize(this, w, h);
    }
}
