import java.awt.Component;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class PasteAnyAsText {
    
    public PasteAnyAsText() {
    }
    
    public boolean selectClipToPasteAsText(DittoInfo dittoInfo, IClip clip) {
        boolean ret = false;
        IClipFormats clipFormats = clip.getClips();
        Component dittoWindow = dittoInfo.getDittoWindow();
        CSelectPasteFormat selectPasteFormatDialog = new CSelectPasteFormat(dittoWindow, clipFormats);
        
        if (selectPasteFormatDialog.showDialog() == CSelectPasteFormat.DialogResult.OK) {
            CLIPFORMAT selectedFormat = selectPasteFormatDialog.getSelectedFormat();
            if (selectedFormat != null) {
                IClipFormat clipText = clipFormats.findFormatEx(selectedFormat);
                if (clipText != null) {
                    clipText.setAutoDeleteData(false);
                    ByteBuffer dataBuffer = clipText.getData();
                    
                    if (!selectPasteFormatDialog.pasteAsUnicode()) {
                        int dataSize = dataBuffer.capacity();
                        byte[] byteArray = new byte[dataSize];
                        dataBuffer.get(byteArray);
                        for (int i = 0; i < dataSize; i++) {
                            if (byteArray[i] == 0) {
                                byteArray[i] = ' ';
                            }
                        }
                        dataBuffer = ByteBuffer.wrap(byteArray).order(ByteOrder.nativeOrder());
                        
                        clipFormats.deleteAll();
                        clipFormats.addNew(CLIPFORMAT.CF_TEXT, dataBuffer);
                        
                        IClipFormat newText = clipFormats.findFormatEx(CLIPFORMAT.CF_TEXT);
                        if (newText != null) {
                            newText.setAutoDeleteData(true);
                        }
                    } else {
                        int dataSize = dataBuffer.capacity() / 2;
                        char[] charArray = new char[dataSize];
                        Charset charset = StandardCharsets.UTF_16LE;
                        charset.newDecoder().decode(dataBuffer).get(charArray);
                        
                        for (int i = 0; i < dataSize; i++) {
                            if (charArray[i] == 0) {
                                charArray[i] = ' ';
                            }
                        }
                        dataBuffer = charset.encode(CharBuffer.wrap(charArray)).order(ByteOrder.nativeOrder());
                        
                        clipFormats.deleteAll();
                        clipFormats.addNew(CLIPFORMAT.CF_UNICODETEXT, dataBuffer);
                        
                        IClipFormat newText = clipFormats.findFormatEx(CLIPFORMAT.CF_UNICODETEXT);
                        if (newText != null) {
                            newText.setAutoDeleteData(true);
                        }
                    }
                    
                    ret = true;
                }
            }
        }
        
        return ret;
    }
}
