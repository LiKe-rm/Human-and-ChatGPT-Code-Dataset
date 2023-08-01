import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class SelectPasteFormat extends JDialog {
    private IClipFormats clipFormats;
    private int selectedFormat;
    private boolean pasteAsUnicode;
    private JList<String> formatsList;
    private JCheckBox pasteAsUnicodeCheckBox;
    private JButton okButton;
    private JButton cancelButton;

    public SelectPasteFormat(Frame parent, IClipFormats clipFormats) {
        super(parent, true);
        this.clipFormats = clipFormats;
        this.selectedFormat = 0;
        this.pasteAsUnicode = false;

        initComponents();
    }

    private void initComponents() {
        setTitle("Select Paste Format");
        setSize(400, 300);
        setLayout(new BorderLayout());

        formatsList = new JList<>();
        JScrollPane scrollPane = new JScrollPane(formatsList);
        add(scrollPane, BorderLayout.CENTER);

        pasteAsUnicodeCheckBox = new JCheckBox("Paste as Unicode");
        add(pasteAsUnicodeCheckBox, BorderLayout.NORTH);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        add(buttonPanel, BorderLayout.SOUTH);

        okButton = new JButton("OK");
        okButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onOK();
            }
        });
        buttonPanel.add(okButton);

        cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        });
        buttonPanel.add(cancelButton);

        formatsList.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    onOK();
                }
            }
        });

        loadFormats();
    }

    private void loadFormats() {
        if (clipFormats != null) {
            DefaultListModel<String> listModel = new DefaultListModel<>();
            int count = clipFormats.size();
            for (int i = 0; i < count; i++) {
                String formatName = DittoAddinHelpers.getFormatName(clipFormats.get(i).getType());
                listModel.addElement(formatName);
            }
            formatsList.setModel(listModel);
        }
    }

    private void onOK() {
        int pos = formatsList.getSelectedIndex();
        if (pos >= 0 && pos < formatsList.getModel().getSize()) {
            selectedFormat = clipFormats.get(pos).getType();
        }

        pasteAsUnicode = pasteAsUnicodeCheckBox.isSelected();

        setVisible(false);
    }

    private void onCancel() {
        setVisible(false);
    }

    public int getSelectedFormat() {
        return selectedFormat;
    }

    public boolean isPasteAsUnicode() {
        return pasteAsUnicode;
    }
}
