import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.nio.file.Paths;

public class OptionsQuickPaste extends JPanel {
    private static final String DEFAULT_THEME = "(Default)";

    private JCheckBox ensureEntireWindowVisible, showAllInMainList, findAsYouType, drawRTF, showThumbnails,
            descShowLeadingWhiteSpace, historyStartTop, useCtrlNum, showText, promptForDelete;
    private JButton buttonFont, buttonDefaultFont, buttonTheme;
    private JComboBox<String> themeComboBox;
    private JFormattedTextField linesPerRow, transparencyPercent;
    private JRadioButton atCaret, atCursor, atPrevious;

    public OptionsQuickPaste() {
        initComponents();
        initListeners();
    }

    private void initComponents() {
        ensureEntireWindowVisible = new JCheckBox("Ensure Entire Window is Visible");
        showAllInMainList = new JCheckBox("Show All in Main List");
        findAsYouType = new JCheckBox("Find As You Type");
        drawRTF = new JCheckBox("Draw RTF");
        showThumbnails = new JCheckBox("Show Thumbnails");
        descShowLeadingWhiteSpace = new JCheckBox("Desc Show Leading White Space");
        historyStartTop = new JCheckBox("History Start Top");
        useCtrlNum = new JCheckBox("Use Ctrl+Num");
        showText = new JCheckBox("Show Text");
        promptForDelete = new JCheckBox("Prompt for Delete");

        buttonFont = new JButton("Font");
        buttonDefaultFont = new JButton("Default Font");
        buttonTheme = new JButton("Theme");

        themeComboBox = new JComboBox<>();
        fillThemes();

        linesPerRow = new JFormattedTextField();
        transparencyPercent = new JFormattedTextField();

        atCaret = new JRadioButton("At Caret");
        atCursor = new JRadioButton("At Cursor");
        atPrevious = new JRadioButton("At Previous");

        ButtonGroup group = new ButtonGroup();
        group.add(atCaret);
        group.add(atCursor);
        group.add(atPrevious);

        // TODO: Set initial values from the configuration
    }

    private void initListeners() {
        buttonFont.addActionListener(e -> onButtonFont());
        buttonDefaultFont.addActionListener(e -> onButtonDefaultFont());
        buttonTheme.addActionListener(e -> onButtonTheme());
    }

    private void onButtonFont() {
        // TODO: Implement font selection logic
    }

    private void onButtonDefaultFont() {
        // TODO: Implement default font selection logic
    }

    private void onButtonTheme() {
        // TODO: Implement theme selection logic
    }

    private void fillThemes() {
        String themePath = Paths.get(System.getProperty("user.dir"), "themes").toString();
        File themesDir = new File(themePath);
        String[] themeFiles = themesDir.list((dir, name) -> name.endsWith(".xml"));

        if (themeFiles != null) {
            for (String themeFile : themeFiles) {
                themeComboBox.addItem(themeFile.substring(0, themeFile.length() - 4));
            }
        }

        themeComboBox.addItem(DEFAULT_THEME);
        themeComboBox.setSelectedItem(DEFAULT_THEME);

        // TODO: Set initial theme value from the configuration
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("OptionsQuickPaste");
        frame.setContentPane(new OptionsQuickPaste());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }
}
