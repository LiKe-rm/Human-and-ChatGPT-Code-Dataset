import javax.swing.*;
import java.awt.event.*;

public class SizeComboBox extends JComboBox<String> {
    private static final long serialVersionUID = 1L;

    public SizeComboBox() {
        super();
        fillCombo();
    }

    public void selectSize(int size) {
        String sizeString = String.valueOf(size);
        int itemCount = getItemCount();

        for (int i = 0; i < itemCount; i++) {
            if (getItemAt(i).equals(sizeString)) {
                setSelectedIndex(i);
                return;
            }
        }
    }

    private void fillCombo() {
        addItem("8");
        addItem("9");
        addItem("10");
        addItem("11");
        addItem("12");
        addItem("14");
        addItem("16");
        addItem("18");
        addItem("20");
        addItem("22");
        addItem("24");
        addItem("26");
        addItem("28");
        addItem("36");
        addItem("48");
        addItem("72");
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("SizeComboBox Demo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        SizeComboBox sizeComboBox = new SizeComboBox();
        frame.add(sizeComboBox);

        frame.setVisible(true);
    }
}
