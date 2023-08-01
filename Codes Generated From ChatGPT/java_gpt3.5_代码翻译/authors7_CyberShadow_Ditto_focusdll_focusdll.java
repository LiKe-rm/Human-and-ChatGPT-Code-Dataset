import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.platform.win32.User32;
import com.sun.jna.platform.win32.WinDef.*;
import com.sun.jna.platform.win32.WinUser.*;
import com.sun.jna.win32.StdCallLibrary;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

interface FocusDLL extends StdCallLibrary {
    FocusDLL INSTANCE = Native.load("FocusDLL", FocusDLL.class);
    void MonitorFocusChanges();
    void StopMonitoringFocusChanges();
    HWND GetCurrentFocus();
}

public class FocusMonitor {
    private static final User32 user32 = User32.INSTANCE;
    private HHOOK hHook;

    public FocusMonitor() {
        user32.SetWinEventHook(User32.EVENT_OBJECT_FOCUS, User32.EVENT_OBJECT_FOCUS, null, new WinEventProc(), 0, 0, User32.WINEVENT_OUTOFCONTEXT);
    }

    public void stopMonitoring() {
        if (hHook != null) {
            user32.UnhookWinEvent(hHook);
            hHook = null;
        }
    }

    public HWND getCurrentFocus() {
        return user32.GetFocus();
    }

    public class WinEventProc implements WinEventProcCallback {
        @Override
        public void callback(HANDLE hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime) {
            System.out.println("Focus changed to: " + hwnd);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Focus Monitor");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(300, 200);

            JTextField textField = new JTextField();
            textField.addKeyListener(new KeyListener() {
                @Override
                public void keyTyped(KeyEvent e) {
                }

                @Override
                public void keyPressed(KeyEvent e) {
                    System.out.println("Key Pressed: " + e.getKeyChar());
                }

                @Override
                public void keyReleased(KeyEvent e) {
                }
            });

            frame.add(textField, BorderLayout.CENTER);
            frame.setVisible(true);

            FocusMonitor focusMonitor = new FocusMonitor();
            Runtime.getRuntime().addShutdownHook(new Thread(() -> focusMonitor.stopMonitoring()));
        });
    }
}
