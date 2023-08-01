import javax.swing.*;
import java.awt.*;
import java.awt.datatransfer.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class OleClipSource extends ClipboardOwner {
    private boolean loadedFormats;
    private boolean onlyPasteCFText;
    private ClipFormats customPasteFormats;
    private Clipboard clipboard;
    private List<ClipData> clipDataList;

    public OleClipSource() {
        loadedFormats = false;
        onlyPasteCFText = false;
        customPasteFormats = null;
        clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        clipDataList = new ArrayList<>();
    }

    public boolean doDelayRender() {
        // Not applicable in Java as it automatically manages delayed rendering
        return false;
    }

    public boolean doImmediateRender() {
        if (loadedFormats) {
            return true;
        }

        loadedFormats = true;

        if (customPasteFormats != null) {
            return putFormatOnClipboard(customPasteFormats) > 0;
        }

        int count = clipDataList.size();
        if (count <= 0) {
            return false;
        }

        ClipData clipData = clipDataList.get(0);
        return putFormatOnClipboard(clipData.getFormats()) > 0;
    }

    public int putFormatOnClipboard(ClipFormats formats) {
        Transferable transferable = formats.toTransferable();
        clipboard.setContents(transferable, this);
        return formats.getSize();
    }

    @Override
    public void lostOwnership(Clipboard clipboard, Transferable contents) {
        // Handle lost ownership event
    }
}
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ClipFormats {
    private List<DataFlavor> dataFlavors;
    private List<Object> data;

    public ClipFormats() {
        dataFlavors = new ArrayList<>();
        data = new ArrayList<>();
    }

    public void add(DataFlavor dataFlavor, Object dataObject) {
        dataFlavors.add(dataFlavor);
        data.add(dataObject);
    }

    public int getSize() {
        return dataFlavors.size();
    }

    public Transferable toTransferable() {
        return new Transferable() {
            @Override
            public DataFlavor[] getTransferDataFlavors() {
                return dataFlavors.toArray(new DataFlavor[0]);
            }

            @Override
            public boolean isDataFlavorSupported(DataFlavor flavor) {
                return dataFlavors.contains(flavor);
            }

            @Override
            public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
                int index = dataFlavors.indexOf(flavor);
                if (index == -1) {
                    throw new UnsupportedFlavorException(flavor);
                }
                return data.get(index);
            }
        };
    };
}

public class ClipData {
    private ClipFormats formats;
    public ClipData() {
        formats = new ClipFormats();
    }

    public void addFormat(DataFlavor dataFlavor, Object dataObject) {
        formats.add(dataFlavor, dataObject);
    }

    public ClipFormats getFormats() {
        return formats;
    }
}