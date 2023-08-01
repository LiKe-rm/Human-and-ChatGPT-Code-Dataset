import javax.swing.*;
import java.awt.*;
import java.awt.datatransfer.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

public class CopyThread extends Thread {

    private volatile boolean quit = false;
    private volatile boolean configChanged = false;
    private ClipboardViewer clipboardViewer;
    private final CopyConfig localConfig = new CopyConfig();
    private final CopyConfig sharedConfig = new CopyConfig();

    public CopyThread() {
        clipboardViewer = new ClipboardViewer(this);
        clipboardViewer.connectOnStartup(true);
    }

    @Override
    public void run() {
        clipboardViewer.create();
        while (!quit) {
            synchronized (this) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public void onClipboardChange() {
        System.out.println("OnClipboardChange - Start");
        syncConfig();

        if (!localConfig.isCopyOnChange()) {
            return;
        }

        Clip clip = new Clip();
        List<DataFlavor> supportedTypes = localConfig.getSupportedTypes();

        if (CopyBuffer.getInstance().isActive()) {
            supportedTypes = new ArrayList<>();
            Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
            Transferable contents = clipboard.getContents(null);
            DataFlavor[] flavors = contents.getTransferDataFlavors();
            for (DataFlavor flavor : flavors) {
                supportedTypes.add(flavor);
            }
        }

        boolean result = clip.loadFromClipboard(supportedTypes);

        if (!result) {
            // Retry mechanism can be implemented here
        }

        if (result) {
            if (localConfig.isAsyncCopy()) {
                SwingUtilities.invokeLater(() -> localConfig.getClipHandler().clipboardCopied(clip));
            } else {
                localConfig.getClipHandler().clipboardCopied(clip);
            }
        }
    }

    private synchronized void syncConfig() {
        if (configChanged) {
            localConfig.copyFrom(sharedConfig);
            configChanged = false;
        }
    }

    public void setSupportedTypes(List<DataFlavor> types) {
        synchronized (this) {
            sharedConfig.setSupportedTypes(types);
            configChanged = true;
        }
    }

    public void setClipHandler(ClipHandler clipHandler) {
        synchronized (this) {
            sharedConfig.setClipHandler(clipHandler);
            configChanged = true;
        }
    }

    public void setCopyOnChange(boolean value) {
        synchronized (this) {
            sharedConfig.setCopyOnChange(value);
            configChanged = true;
        }
    }

    public void setAsyncCopy(boolean value) {
        synchronized (this) {
            sharedConfig.setAsyncCopy(value);
            configChanged = true;
        }
    }

    public void quit() {
        quit = true;
        synchronized (this) {
            notifyAll();
        }
    }
}

class ClipboardViewer {
    private final CopyThread copyThread;
    private final AtomicBoolean connected = new AtomicBoolean(false);
    private boolean connectOnStartup;

    ClipboardViewer(CopyThread copyThread) {
                this.copyThread = copyThread;
    }

    void create() {
        if (connectOnStartup) {
            connect();
        }
    }

    void connectOnStartup(boolean value) {
        connectOnStartup = value;
    }

    void connect() {
        if (!connected.get()) {
            Toolkit.getDefaultToolkit().getSystemClipboard().addFlavorListener(e -> copyThread.onClipboardChange());
            connected.set(true);
        }
    }

    void disconnect() {
        if (connected.get()) {
            Toolkit.getDefaultToolkit().getSystemClipboard().removeFlavorListener(e -> copyThread.onClipboardChange());
            connected.set(false);
        }
    }
}

interface ClipHandler {
    void clipboardCopied(Clip clip);
}

class CopyConfig {
    private List<DataFlavor> supportedTypes;
    private ClipHandler clipHandler;
    private boolean copyOnChange;
    private boolean asyncCopy;

    public void copyFrom(CopyConfig other) {
        supportedTypes = other.supportedTypes;
        clipHandler = other.clipHandler;
        copyOnChange = other.copyOnChange;
        asyncCopy = other.asyncCopy;
    }
}

