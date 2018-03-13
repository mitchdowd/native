package libnative.ui;

import android.content.Context;
import android.graphics.Canvas;
import android.view.MotionEvent;
import android.view.View;
import android.widget.RelativeLayout;

public class ScrollView extends android.widget.ScrollView implements INativeComponent {
    private RelativeLayout _layout;

    public ScrollView(Context context) {
        super(context);

        _layout = new RelativeLayout(context);
        super.addView(_layout);
    }

    @Override
    public void addView(View child)
    {
        _layout.addView(child);
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
