import javax.swing.JTextField;
import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.DocumentFilter;
import javax.swing.text.PlainDocument;

public class NumberEdit extends JTextField {
    private long maxNumber;

    public NumberEdit() {
        maxNumber = Long.MAX_VALUE;
        PlainDocument document = (PlainDocument) getDocument();
        document.setDocumentFilter(new NumberFilter());
    }

    public boolean validateNumber(double number) {
        return number <= maxNumber;
    }

    public long getNumber() {
        String text = getText();
        return Long.parseLong(text);
    }

    public double getNumberD() {
        String text = getText();
        return Double.parseDouble(text);
    }

    public boolean setNumber(long number) {
        if (!validateNumber(number)) {
            return false;
        }

        setText(Long.toString(number));
        return true;
    }

    private class NumberFilter extends DocumentFilter {
        @Override
        public void insertString(FilterBypass fb, int offset, String string, AttributeSet attr) throws BadLocationException {
            if (isNumeric(string)) {
                super.insertString(fb, offset, string, attr);
            }
        }

        @Override
        public void replace(FilterBypass fb, int offset, int length, String text, AttributeSet attrs) throws BadLocationException {
            if (isNumeric(text)) {
                super.replace(fb, offset, length, text, attrs);
            }
        }

        private boolean isNumeric(String text) {
            try {
                Double.parseDouble(text);
                return true;
            } catch (NumberFormatException e) {
                return false;
            }
        }
    }
}
