import javax.swing.*;
import javax.swing.text.*;
import javax.swing.text.rtf.RTFEditorKit;
import java.awt.*;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.Enumeration;

public class RichTextEditor extends JTextPane {

    public RichTextEditor() {
        super();
        setEditorKit(new RTFEditorKit());
    }

    public String getRTF() {
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        try {
            getEditorKit().write(outputStream, getStyledDocument(), 0, getStyledDocument().getLength());
        } catch (IOException | BadLocationException e) {
            e.printStackTrace();
        }
        return outputStream.toString();
    }

    public void setRTF(String rtf) {
        ByteArrayInputStream inputStream = new ByteArrayInputStream(rtf.getBytes());
        try {
            getEditorKit().read(inputStream, getStyledDocument(), 0);
        } catch (IOException | BadLocationException e) {
            e.printStackTrace();
        }
    }

    public String getTextContent() {
        return getText();
    }

    public void setTextContent(String text) {
        setText(text);
    }

    public void setBold(boolean bold) {
        applyStyle(StyleConstants.Bold, bold);
    }

    public void setItalic(boolean italic) {
        applyStyle(StyleConstants.Italic, italic);
    }

    public void setUnderline(boolean underline) {
        applyStyle(StyleConstants.Underline, underline);
    }

    private void applyStyle(AttributeKey attribute, boolean value) {
        int start = getSelectionStart();
        int end = getSelectionEnd();
        MutableAttributeSet attributes = getInputAttributes();
        attributes.addAttribute(attribute, value);
        setCharacterAttributes(attributes, false);
    }

    public void setFontFamily(String fontFamily) {
        applyFontAttribute(StyleConstants.FontFamily, fontFamily);
    }

    public void setFontSize(int fontSize) {
        applyFontAttribute(StyleConstants.FontSize, fontSize);
    }

    private void applyFontAttribute(AttributeKey attribute, Object value) {
        int start = getSelectionStart();
        int end = getSelectionEnd();
        if (start != end) {
            MutableAttributeSet attributes = getInputAttributes();
            attributes.addAttribute(attribute, value);
            setCharacterAttributes(attributes, false);
        }
    }

    public String[] getSystemFonts() {
        GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
        String[] fontNames = ge.getAvailableFontFamilyNames();
        return fontNames;
    }

    public String getSelectedFontFamily() {
        AttributeSet attributes = getCharacterAttributes();
        return StyleConstants.getFontFamily(attributes);
    }

    public int getSelectedFontSize() {
        AttributeSet attributes = getCharacterAttributes();
        return StyleConstants.getFontSize(attributes);
    }

    public void setParagraphAlignment(int alignment) {
        int start = getSelectionStart();
        int end = getSelectionEnd();
        MutableAttributeSet attributes = getInputAttributes();
        attributes.addAttribute(StyleConstants.Alignment, alignment);
        setParagraphAttributes(attributes, false);
    }

    public int getParagraphAlignment() {
        AttributeSet attributes = getParagraphAttributes();
        return StyleConstants.getAlignment(attributes);
    }

}
