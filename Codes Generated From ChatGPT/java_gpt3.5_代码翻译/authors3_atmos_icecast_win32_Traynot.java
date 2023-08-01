import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.TrayIcon.MessageType;

public class TrayNot {
    private SystemTray tray;
    private TrayIcon trayIcon;
    private Image[] iconList;

    public TrayNot(Frame frame, ActionListener listener, String[] iconPaths) {
        if (!SystemTray.isSupported()) {
            System.err.println("System tray is not supported.");
            return;
        }

        tray = SystemTray.getSystemTray();
        iconList = new Image[iconPaths.length];

        for (int i = 0; i < iconPaths.length; i++) {
            iconList[i] = Toolkit.getDefaultToolkit().getImage(iconPaths[i]);
        }

        trayIcon = new TrayIcon(iconList[0], "Icecast2");
        trayIcon.setImageAutoSize(true);
        trayIcon.addActionListener(listener);

        try {
            tray.add(trayIcon);
        } catch (AWTException e) {
            System.err.println("TrayIcon could not be added.");
        }
    }

    public void setState(int id) {
        if (id < 0 || id >= iconList.length) {
            System.err.println("Invalid icon index.");
            return;
        }
        trayIcon.setImage(iconList[id]);
    }

    public void setTip(String tip) {
        trayIcon.setToolTip(tip);
    }

    public void remove() {
        tray.remove(trayIcon);
    }
}
public class Main {
    public static void main(String[] args) {
        Frame frame = new Frame("Tray Demo");
        ActionListener listener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("Tray icon clicked.");
            }
        };

        String[] iconPaths = {"icon1.png", "icon2.png"};
        TrayNot trayNot = new TrayNot(frame, listener, iconPaths);

        // Change the icon
        trayNot.setState(1);

        // Set the tooltip text
        trayNot.setTip("New Tooltip");
    }
}

