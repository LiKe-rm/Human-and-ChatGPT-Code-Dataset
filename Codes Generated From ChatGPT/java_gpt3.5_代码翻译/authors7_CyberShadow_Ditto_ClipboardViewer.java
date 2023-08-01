import javax.swing.*;
import java.awt.*;
import java.awt.datatransfer.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

public class ClipboardViewer extends JFrame {

    private boolean isConnected = false;
    private Clipboard clipboard;
    private Timer reconnectTimer;
    private Timer checkClipboardTimer;
    private CopyHandler copyHandler;
    private List<String> includeApps;
    private List<String> excludeApps;

    public ClipboardViewer(CopyHandler copyHandler) {
        setTitle("Java Clipboard Viewer");
        setSize(300, 100);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        this.clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        this.copyHandler = copyHandler;

        this.includeApps = new ArrayList<>(); // Populate this list with the apps you want to include
        this.excludeApps = new ArrayList<>(); // Populate this list with the apps you want to exclude

        setupReconnectTimer();
        setupCheckClipboardTimer();
    }

    public void connect() {
        System.out.println("Connect to Clipboard");
        isConnected = true;
        reconnectTimer.start();
        checkClipboardTimer.start();
    }

    public void disconnect() {
        System.out.println("Disconnect From Clipboard");
        isConnected = false;
        reconnectTimer.stop();
        checkClipboardTimer.stop();
    }

    private void setupReconnectTimer() {
        reconnectTimer = new Timer(5 * 60 * 1000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!isConnected) {
                    connect();
                }
            }
        });
    }

    private void setupCheckClipboardTimer() {
        checkClipboardTimer = new Timer(1000, new ActionListener() {
            private Transferable previousClipboardContent = clipboard.getContents(null);

            @Override
            public void actionPerformed(ActionEvent e) {
                if (isConnected) {
                    Transferable currentClipboardContent = clipboard.getContents(null);
                    if (currentClipboardContent != previousClipboardContent) {
                        handleClipboardChange(currentClipboardContent);
                        previousClipboardContent = currentClipboardContent;
                    }
                }
            }
        });
    }

    private void handleClipboardChange(Transferable currentClipboardContent) {
        if(validActiveWindow()) {
            System.out.println("Clipboard content changed");
            copyHandler.onClipboardChange(currentClipboardContent);
        }
    }
    private boolean validActiveWindow() {
        String activeApp = getActiveAppName().toLowerCase();
        System.out.println("Active App: " + activeApp);

        boolean includeMatch = false;
        for (String includeApp : includeApps) {
            if (wildCardMatch(activeApp, includeApp.toLowerCase())) {
                System.out.println("Include app names Found Match: " + includeApp + " - " + activeApp);
                includeMatch = true;
                break;
            }
        }

        if (!includeMatch) {
            System.out.println("Didn't find a match to INCLUDE match, NOT SAVING COPY");
            return false;
        }

        for (String excludeApp : excludeApps) {
            if (wildCardMatch(activeApp, excludeApp.toLowerCase())) {
                System.out.println("Exclude app names Found Match: " + excludeApp + " - " + activeApp + " - NOT SAVING COPY");
                return false;
            }
        }

        return true;
    }

    private String getActiveAppName() {
        // Implement this method to return the name of the active application
        return "some_application_name";
    }

    private boolean wildCardMatch(String text, String pattern) {
        // Implement this method to match a text against a pattern with wildcards
        return text.contains(pattern);
    }

    public static void main(String[] args) {
        ClipboardViewer clipboardViewer = new ClipboardViewer(new CopyHandler() {
            @Override
            public void onClipboardChange(Transferable clipboardContent) {
                System.out.println("Handling clipboard change...");
                // Add your clipboard handling code here
            }
        });

        clipboardViewer.setVisible(true);
        clipboardViewer.connect();
    }

    public interface CopyHandler {
        void onClipboardChange(Transferable clipboardContent);
    }
}

