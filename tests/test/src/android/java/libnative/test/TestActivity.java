package libnative.test;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;


public class TestActivity extends Activity {
    // Static Variables
    private static boolean _libIsLoaded = false;
    private static final String META_LIB_NAME = "libnative.test.lib_name";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        loadNativeLibrary();
        onCreate();
    }

    private native void onCreate();

    private void loadNativeLibrary()
    {
        if (!_libIsLoaded) {
            try {
                ActivityInfo info = getPackageManager().getActivityInfo(getIntent().getComponent(), PackageManager.GET_META_DATA);
                if (info.metaData != null) {
                    String libName = info.metaData.getString(META_LIB_NAME);

                    if (libName == null)
                        throw new RuntimeException(META_LIB_NAME + " meta-data tag not provided in manifest");

                    System.loadLibrary(libName);
                    _libIsLoaded = true;
                }
            } catch (PackageManager.NameNotFoundException e) {
                throw new RuntimeException("Error getting native library name", e);
            }
        }
    }
}
