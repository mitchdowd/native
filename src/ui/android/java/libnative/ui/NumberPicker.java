package libnative.ui;

import android.content.Context;
import android.graphics.Canvas;
import android.view.MotionEvent;

public class NumberPicker extends android.widget.NumberPicker implements INativeComponent {
    public NumberPicker(Context context) {
        super(context);

        setWrapSelectorWheel(false);

        // Set default min/max values.
        setMaxValue(Integer.MAX_VALUE);
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
