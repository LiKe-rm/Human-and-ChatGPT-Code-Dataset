import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.platform.win32.User32;
import com.sun.jna.platform.win32.WinDef;
import com.sun.jna.platform.win32.WinUser;

import java.awt.*;

public class Main {

    private static final boolean DEBUG = false;
    private static boolean wasFullScreen = false;

    public static void main(String[] args) {
        new Main().run();
    }

    public void run() {
        WinUser.HHOOK hMouseHook = User32.INSTANCE.SetWindowsHookEx(WinUser.WH_MOUSE_LL, this::lowLevelMouseProc, null, 0);

        WinUser.MSG msg = new WinUser.MSG();
        while (User32.INSTANCE.GetMessage(msg, null, 0, 0) > 0) {
            User32.INSTANCE.TranslateMessage(msg);
            User32.INSTANCE.DispatchMessage(msg);
        }

        User32.INSTANCE.UnhookWindowsHookEx(hMouseHook);
        User32.INSTANCE.ClipCursor(null);
    }

    private WinDef.LRESULT lowLevelMouseProc(int nCode, WinDef.WPARAM wParam, WinUser.MSLLHOOKSTRUCT lParam) {
        check();
        Pointer ptr = User32.INSTANCE.GetModuleHandle(null);
        return User32.INSTANCE.CallNextHookEx(hMouseHook, nCode, wParam, lParam.getPointer());
    }

    private void check() {
        WinDef.HWND fg = User32.INSTANCE.GetForegroundWindow();
        WinDef.RECT fgRect = new WinDef.RECT();
        User32.INSTANCE.GetClientRect(fg, fgRect);

        int monW = User32.INSTANCE.GetSystemMetrics(User32.SM_CXSCREEN);
        int monH = User32.INSTANCE.GetSystemMetrics(User32.SM_CYSCREEN);

        if (DEBUG) {
            System.out.printf("%d %d %d %d %d %d\n",
                    fg,
                    fg != User32.INSTANCE.GetDesktopWindow(),
                    fgRect.left == 0,
                    fgRect.top == 0,
                    fgRect.right == monW,
                    fgRect.bottom == monH
            );
        }

        boolean fullScreen =
                fg != null &&
                !fg.equals(User32.INSTANCE.GetDesktopWindow()) &&
                fgRect.left == 0 &&
                fgRect.top == 0 &&
                fgRect.right == monW &&
                fgRect.bottom == monH;

        if (fullScreen != wasFullScreen) {
            if (DEBUG) {
                System.out.printf("%s!\n", fullScreen ? "Locking" : "Unlocking");
            }

            boolean ok = User32.INSTANCE.ClipCursor(fullScreen ? fgRect : null);

            if (DEBUG) {
                System.out.printf("%s!\n", ok ? "Success" : "Failed");
            }

            wasFullScreen = fullScreen;
        }
    }
}
