import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;

public class HTMLFormatAggregator {
    private String separator;
    private StringBuilder newText;
    private String sourceUrl;
    private String version;

    public HTMLFormatAggregator(String separator) {
        this.separator = separator;
        this.separator = this.separator.replace("\r\n", "<br>");
        this.newText = new StringBuilder();
        this.sourceUrl = "";
        this.version = "";
    }

    public boolean addClip(String html, int position, int count) {
        if (html == null || html.isEmpty()) {
            return false;
        }

        HTMLFormatStruct htmlData = new HTMLFormatStruct();
        if (htmlData.getData(html)) {
            newText.append(htmlData.getFragment());

            if (sourceUrl.isEmpty()) {
                sourceUrl = htmlData.getSourceUrl();
            }
            if (version.isEmpty()) {
                version = htmlData.getVersion();
            }

            if (position != count - 1) {
                newText.append(separator);
            }
        }

        return true;
    }

    public Transferable getTransferable() {
        HTMLFormatStruct htmlData = new HTMLFormatStruct();
        htmlData.setFragment(newText.toString());
        htmlData.setSourceUrl(sourceUrl);
        htmlData.setVersion(version);

        String htmlFormat = htmlData.serialize();
        return new HTMLTransferable(htmlFormat);
    }

    private static class HTMLTransferable implements Transferable {
        private final String htmlFormat;

        public HTMLTransferable(String htmlFormat) {
            this.htmlFormat = htmlFormat;
        }

        @Override
        public DataFlavor[] getTransferDataFlavors() {
            return new DataFlavor[]{DataFlavor.stringFlavor};
        }

        @Override
        public boolean isDataFlavorSupported(DataFlavor flavor) {
            return DataFlavor.stringFlavor.equals(flavor);
        }

        @Override
        public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
            if (!isDataFlavorSupported(flavor)) {
                throw new UnsupportedFlavorException(flavor);
            }
            return htmlFormat;
        }
    }
}
