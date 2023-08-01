import java.awt.*;
import java.awt.datatransfer.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ClipboardSaveRestore {
    private List<ClipFormat> clipboard;

    public ClipboardSaveRestore() {
        clipboard = new ArrayList<>();
    }

    public boolean save() {
        clipboard.clear();
        boolean result = false;
        Clipboard systemClipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        Transferable transferable = systemClipboard.getContents(null);
        DataFlavor[] dataFlavors = transferable.getTransferDataFlavors();

        for (DataFlavor dataFlavor : dataFlavors) {
            try {
                Object data = transferable.getTransferData(dataFlavor);
                ClipFormat clipFormat = new ClipFormat(dataFlavor, data);
                clipboard.add(clipFormat);
                result = true;
            } catch (UnsupportedFlavorException | IOException e) {
                e.printStackTrace();
            }
        }

        return result;
    }

    public boolean restore() {
        boolean result = false;
        Clipboard systemClipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        Transferable transferable = new Transferable() {
            @Override
            public DataFlavor[] getTransferDataFlavors() {
                return clipboard.stream().map(ClipFormat::getDataFlavor).toArray(DataFlavor[]::new);
            }

            @Override
            public boolean isDataFlavorSupported(DataFlavor flavor) {
                return clipboard.stream().anyMatch(clip -> clip.getDataFlavor().equals(flavor));
            }

            @Override
            public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException {
                return clipboard.stream()
                        .filter(clip -> clip.getDataFlavor().equals(flavor))
                        .findFirst()
                        .orElseThrow(UnsupportedFlavorException::new)
                        .getData();
            }
        };

        try {
            systemClipboard.setContents(transferable, null);
            result = true;
        } catch (IllegalStateException e) {
            e.printStackTrace();
        }

        clipboard.clear();

        if (!result) {
            System.err.println("ClipboardSaveRestore::restore failed to restore clipboard");
        }

        return result;
    }

    public boolean restoreTextOnly() {
        boolean result = false;
        Clipboard systemClipboard = Toolkit.getDefaultToolkit().getSystemClipboard();

        for (ClipFormat clipFormat : clipboard) {
            DataFlavor dataFlavor = clipFormat.getDataFlavor();
            if (dataFlavor.equals(DataFlavor.stringFlavor)) {
                String data = (String) clipFormat.getData();
                StringSelection stringSelection = new StringSelection(data);
                systemClipboard.setContents(stringSelection, null);
                result = true;
                break;
            }
        }

        if (!result) {
            System.err.println("ClipboardSaveRestore::restoreTextOnly failed to restore clipboard");
        }

        return result;
    }

    private static class ClipFormat {
        private DataFlavor dataFlavor;
        private Object data;

        public ClipFormat(DataFlavor dataFlavor, Object data) {
            this.dataFlavor = dataFlavor;
            this.data = data;
        }

        public DataFlavor getDataFlavor() {
            return dataFlavor;
        }

        public Object getData() {
            return data;
        }
    }

    public static void main(String[] args) {
        ClipboardSaveRestore clipboardSaveRestore = new ClipboardSaveRestore();
        System.out.println("Saving clipboard contents...");
        boolean saveResult = clipboardSaveRestore.save();
        System.out.println("Save result: " + saveResult);

        System.out.println("Restoring clipboard contents...");
        boolean restoreResult = clipboardSaveRestore.restore();
        System.out.println("Restore result: " + restoreResult);

        System.out.println("Restoring text only from clipboard...");
        boolean restoreTextOnlyResult = clipboardSaveRestore.restoreTextOnly();
        System.out.println("Restore text only result: " + restoreTextOnlyResult);
    }
}

