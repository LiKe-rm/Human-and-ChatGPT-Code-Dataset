import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class OptionsSheet extends JDialog {
    private final JTabbedPane tabbedPane;

    private final OptionsGeneral generalOptions;
    private final OptionsKeyBoard keyBoardOptions;
    private final OptionsQuickPaste quickPasteOptions;
    private final OptionsCopyBuffers copyBuffers;
    private final OptionsStats stats;
    private final OptionsTypes types;
    private final About about;
    private final OptionFriends friends;
    private final OptionsCopyBuffers copyBuffersOptions;
    private final Window parentWindow;

    public OptionsSheet(String title, Window parentWindow) {
        super(parentWindow, title, ModalityType.APPLICATION_MODAL);

        this.parentWindow = parentWindow;
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);

        tabbedPane = new JTabbedPane();

        generalOptions = new OptionsGeneral();
        keyBoardOptions = new OptionsKeyBoard();
        quickPasteOptions = new OptionsQuickPaste();
        copyBuffers = new OptionsCopyBuffers();
        stats = new OptionsStats();
        types = new OptionsTypes();
        about = new About();

        tabbedPane.addTab("General", generalOptions);
        tabbedPane.addTab("Types", types);
        tabbedPane.addTab("KeyBoard", keyBoardOptions);
        tabbedPane.addTab("Copy Buffers", copyBuffers);
        tabbedPane.addTab("Quick Paste", quickPasteOptions);
        if (g_Opt.getAllowFriends()) {
            friends = new OptionFriends();
            tabbedPane.addTab("Friends", friends);
        } else {
            friends = null;
        }
        tabbedPane.addTab("Stats", stats);
        tabbedPane.addTab("About", about);

        add(tabbedPane, BorderLayout.CENTER);
        pack();

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                onNcDestroy();
            }
        });
    }

    public void onNcDestroy() {
        parentWindow.dispatchEvent(new WindowEvent(parentWindow, WindowEvent.WINDOW_CLOSING));
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame parentFrame = new JFrame("Parent");
            parentFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            parentFrame.setSize(300, 200);

            JButton openOptionsButton = new JButton("Open Options");
            openOptionsButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    OptionsSheet optionsSheet = new OptionsSheet("Ditto", parentFrame);
                    optionsSheet.setLocationRelativeTo(parentFrame);
                    optionsSheet.setVisible(true);
                }
            });

            parentFrame.add(openOptionsButton);
            parentFrame.setVisible(true);
        });
    }
}
