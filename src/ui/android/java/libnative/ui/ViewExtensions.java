package libnative.ui;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Canvas;
import android.view.MotionEvent;
import android.view.View;
import android.widget.RelativeLayout;

class ViewExtensions {
    public static void setArea(View view, int x, int y, int width, int height)
    {
        class ReLayoutRunnable implements Runnable {
            private View _view;

            public ReLayoutRunnable(View view) {
                _view = view;
            }

            public void run() {
                _view.requestLayout();
            }
        }

        RelativeLayout.LayoutParams params = (RelativeLayout.LayoutParams) view.getLayoutParams();

        if (params != null)
        {
            params.leftMargin = x;
            params.topMargin  = y;
            params.width  = width;
            params.height = height;

            onSize(view, width, height);

            // Notify the layout manager of the change.
            view.post(new ReLayoutRunnable(view));
        }
    }

    public static void messageBox(Context owner, String message, String title)
    {
        AlertDialog.Builder alert  = new AlertDialog.Builder(owner);

        alert.setMessage(message);
        alert.setTitle(title);

        alert.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
            }
        });

        alert.create().show();
    }

    public native static boolean onInput(View view, MotionEvent event);
    public native static void onPaint(View view, Canvas canvas);
    public native static void onSize(View view, int width, int height);
}
