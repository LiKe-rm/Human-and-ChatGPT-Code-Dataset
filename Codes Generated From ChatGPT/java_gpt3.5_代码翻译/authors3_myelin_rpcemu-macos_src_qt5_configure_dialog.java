import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class ConfigureDialog extends JDialog {
    private Emulator emulator;
    private Config configCopy;
    private Model modelCopy;

    private JList<String> hardwareListWidget;
    private ArrayList<String> hardwareListItems;
    private ButtonGroup memGroup;
    private ButtonGroup vramGroup;
    private JCheckBox soundCheckbox;
    private JSlider refreshSlider;
    private JLabel refreshLabel;

    public ConfigureDialog(Emulator emulator, Config configCopy, Model modelCopy, JFrame parent) {
        super(parent, "Configure RPCEmu", true);
        this.emulator = emulator;
        this.configCopy = configCopy;
        this.modelCopy = modelCopy;

        // Create Hardware Group
        hardwareListItems = new ArrayList<>();
        for (Model model : Model.values()) {
            hardwareListItems.add(model.getNameGui());
        }
        hardwareListWidget = new JList<>(hardwareListItems.toArray(new String[0]));

        JScrollPane hardwareScrollPane = new JScrollPane(hardwareListWidget);
        hardwareScrollPane.setBorder(BorderFactory.createTitledBorder("Hardware"));

        // Create Memory Group
        JPanel memPanel = new JPanel();
        memPanel.setBorder(BorderFactory.createTitledBorder("RAM"));
        memGroup = new ButtonGroup();
        for (String memOption : new String[]{"4 MB", "8 MB", "16 MB", "32 MB (recommended)", "64 MB (recommended)", "128 MB (recommended)", "256 MB"}) {
            JRadioButton radioButton = new JRadioButton(memOption);
            memGroup.add(radioButton);
            memPanel.add(radioButton);
        }

        // Create VRAM Group
        JPanel vramPanel = new JPanel();
        vramPanel.setBorder(BorderFactory.createTitledBorder("VRAM"));
        vramGroup = new ButtonGroup();
        for (String vramOption : new String[]{"None", "2 MB (8 MB if OS supported)"}) {
            JRadioButton radioButton = new JRadioButton(vramOption);
            vramGroup.add(radioButton);
            vramPanel.add(radioButton);
        }

        // Create sound checkbox
        soundCheckbox = new JCheckBox("Sound");

        // Create refresh
        refreshSlider = new JSlider(20, 100);
        refreshSlider.setMajorTickSpacing(20);
        refreshSlider.setMinorTickSpacing(5);
        refreshSlider.setPaintTicks(true);
        refreshSlider.setPaintLabels(true);
        refreshSlider.addChangeListener(e -> {
            refreshLabel.setText(refreshSlider.getValue() + " Hz");
        });

        JPanel refreshPanel = new JPanel(new BorderLayout());
        refreshPanel.setBorder(BorderFactory.createTitledBorder("Video refresh rate"));
        refreshLabel = new JLabel("");
        refreshPanel.add(refreshSlider, BorderLayout.CENTER);
        refreshPanel.add(refreshLabel, BorderLayout.EAST);

        // Create Buttons
        JPanel buttonsPanel = new JPanel();
        JButton okButton = new JButton("OK");
        JButton cancelButton = new JButton("Cancel");
        buttonsPanel.add(okButton);
        buttonsPanel.add(cancelButton);

        // Main layout
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.HORIZONTAL;

        c.gridx = 0;
        c.gridy = 0;
        c.gridwidth = 1;
        c.gridheight = 1;
        add(hardwareScrollPane, c);

        c.gridx = 1;
        c.gridy = 0;
        c.gridwidth = 1;
        c.gridheight = 1;
        add(memPanel, c);

        c.gridx = 0;
        c.gridy = 1;
        c.gridwidth = 1;
        c.gridheight = 1;
        add(vramPanel, c);

        c.gridx = 1;
        c.gridy = 1;
        c.gridwidth = 1;
        c.gridheight = 1;
        add(soundCheckbox, c);

        c.gridx = 0;
        c.gridy = 2;
        c.gridwidth = 2;
        c.gridheight = 1;
        add(refreshPanel, c);

        c.gridx = 0;
        c.gridy = 3;
        c.gridwidth = 2;
        c.gridheight = 1;
        add(buttonsPanel, c);

        // Connect actions to widgets
        okButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogAccepted();
            }
        });

        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogRejected();
            }
        });

        // Set the values in the configure dialog box
        applyConfig();

        // Remove resize on Dialog
        setResizable(false);
        pack();
    }

    private void dialogAccepted() {
        // Fill in the choices from the dialog box and update the emulator's config
        // This method should be implemented according to the emulator's specific requirements
    }

    private void dialogRejected() {
        // Set the values in the dialog back to the current settings
        applyConfig();
    }

    private void applyConfig() {
        // Set the values in the configure dialog box based on the current
        // values of the GUI config copy
        // This method should be implemented according to the emulator's specific requirements
    }

    // You will also need to create classes or enums for the Emulator, Config, and Model.
}

