package libnative.ui;

import android.content.Context;
import android.graphics.Canvas;
import android.view.MotionEvent;

public class InputComponent extends android.widget.EditText implements INativeComponent {
    public InputComponent(Context context) {
        super(context);

        setMaxLines(1);
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
    public void onSizeChanged(int w, int h, int oldW, int oldH) { ViewExtensions.onSize(this, w, h); }
}
