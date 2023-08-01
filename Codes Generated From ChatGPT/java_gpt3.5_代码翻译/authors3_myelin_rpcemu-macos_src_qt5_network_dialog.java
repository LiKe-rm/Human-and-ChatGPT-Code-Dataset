import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class NetworkDialog extends JDialog {
    private Emulator emulator;
    private Config configCopy;
    private Model modelCopy;

    private JRadioButton netOff;
    private JRadioButton netBridging;
    private JRadioButton netTunnelling;
    private JLabel bridgeLabel;
    private JTextField bridgeName;
    private JLabel tunnellingLabel;
    private JTextField tunnellingName;
    private JButton okButton;
    private JButton cancelButton;

    public NetworkDialog(Emulator emulator, Config configCopy, Model modelCopy, JFrame parent) {
        super(parent, "Configure RPCEmu Networking", true);
        this.emulator = emulator;
        this.configCopy = configCopy;
        this.modelCopy = modelCopy;

        // Create widgets and layout
        netOff = new JRadioButton("Off");
        netBridging = new JRadioButton("Ethernet Bridging");
        netTunnelling = new JRadioButton("IP Tunnelling");

        ButtonGroup networkGroup = new ButtonGroup();
        networkGroup.add(netOff);
        networkGroup.add(netBridging);
        networkGroup.add(netTunnelling);

        bridgeLabel = new JLabel("Bridge Name");
        bridgeName = new JTextField("rpcemu", 15);

        tunnellingLabel = new JLabel("IP Address");
        tunnellingName = new JTextField("172.31.0.1", 15);

        okButton = new JButton("OK");
        cancelButton = new JButton("Cancel");

        // Main layout
        JPanel contentPanel = new JPanel();
        contentPanel.setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();

        c.gridx = 0;
        c.gridy = 0;
        c.gridwidth = 2;
        c.anchor = GridBagConstraints.WEST;
        contentPanel.add(netOff, c);

        c.gridy = 1;
        contentPanel.add(netBridging, c);

        c.gridy = 2;
        contentPanel.add(bridgeLabel, c);

        c.gridx = 1;
        contentPanel.add(bridgeName, c);

        c.gridx = 0;
        c.gridy = 3;
        contentPanel.add(netTunnelling, c);

        c.gridy = 4;
        contentPanel.add(tunnellingLabel, c);

        c.gridx = 1;
        contentPanel.add(tunnellingName, c);

        c.gridx = 0;
        c.gridy = 5;
        c.gridwidth = 1;
        c.anchor = GridBagConstraints.CENTER;
        contentPanel.add(okButton, c);

        c.gridx = 1;
        contentPanel.add(cancelButton, c);

        setContentPane(contentPanel);

        // Connect actions to widgets
        ActionListener radioButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                updateControls();
            }
        };

        netOff.addActionListener(radioButtonListener);
        netBridging.addActionListener(radioButtonListener);
        netTunnelling.addActionListener(radioButtonListener);

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

        // Set the values of the window to the config values
        applyConfig();

        // Remove resize on Dialog
        setResizable(false);
        pack();
    }

    private void updateControls() {
        bridgeLabel.setEnabled(netBridging.isSelected());
        bridgeName.setEnabled(netBridging.isSelected());
        tunnellingLabel.setEnabled(netTunnelling.isSelected());
        tunnellingName.setEnabled(netTunnelling.isSelected());
    }
    
    private void dialogAccepted() {
        NetworkType networkType = NetworkType.OFF;
    
        if (netOff.isSelected()) {
            networkType = NetworkType.OFF;
        }
        if (netBridging.isSelected()) {
            networkType = NetworkType.ETHERNET_BRIDGING;
        }
        if (netTunnelling.isSelected()) {
            networkType = NetworkType.IP_TUNNELLING;
        }
    
        String bridgename = bridgeName.getText();
        String ipAddress = tunnellingName.getText();
    
        if (networkConfigChanged(networkType, bridgename, ipAddress)) {
            emulator.reset();
        }
    
        setVisible(false);
    }
    
    private void dialogRejected() {
        applyConfig();
        setVisible(false);
    }
    
    private void applyConfig() {
        switch (configCopy.networkType) {
            case OFF:
                netOff.setSelected(true);
                break;
            case ETHERNET_BRIDGING:
                netBridging.setSelected(true);
                break;
            case IP_TUNNELLING:
                netTunnelling.setSelected(true);
                break;
            default:
                throw new RuntimeException("Unhandled network type");
        }
    
        updateControls();
    
        if (configCopy.bridgeName != null && !configCopy.bridgeName.isEmpty()) {
            bridgeName.setText(configCopy.bridgeName);
        }
    
        if (configCopy.ipAddress != null && !configCopy.ipAddress.isEmpty()) {
            tunnellingName.setText(configCopy.ipAddress);
        }
    }
    
    private boolean networkConfigChanged(NetworkType networkType, String bridgeName, String ipAddress) {
        // Implement this function to compare the new configuration values with the current ones
        // Return true if any value has changed, otherwise return false
        // This is just a placeholder and you should replace it with the actual implementation
        return false;
    }
}    