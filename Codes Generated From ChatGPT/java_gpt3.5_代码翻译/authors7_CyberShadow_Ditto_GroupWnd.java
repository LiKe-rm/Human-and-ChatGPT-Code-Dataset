import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeSelectionModel;
import java.awt.*;
import java.awt.event.*;

public class GroupWindow extends JFrame {
    private JTree tree;
    private JToolBar toolBar;
    private JButton refreshButton, pinButton, newGroupButton;
    private int selectedGroup;
    private WindowListener windowListener;

    public GroupWindow() {
        selectedGroup = -1;
        initComponents();
    }

    private void initComponents() {
        setTitle("Group Window");

        Container contentPane = getContentPane();
        contentPane.setLayout(new BorderLayout());

        toolBar = new JToolBar();
        refreshButton = new JButton("Refresh");
        refreshButton.addActionListener(e -> onRefresh());
        toolBar.add(refreshButton);

        pinButton = new JButton("Pin");
        pinButton.addActionListener(e -> onPin());
        toolBar.add(pinButton);

        newGroupButton = new JButton("New Group");
        newGroupButton.addActionListener(e -> onNewGroup());
        toolBar.add(newGroupButton);

        contentPane.add(toolBar, BorderLayout.NORTH);

        DefaultMutableTreeNode rootNode = new DefaultMutableTreeNode("Root Node");
        tree = new JTree(rootNode);
        tree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
        tree.addTreeSelectionListener(e -> onTreeSelectionChanged());
        tree.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    onTreeItemDoubleClicked();
                }
            }
        });

        JScrollPane treeView = new JScrollPane(tree);
        contentPane.add(treeView, BorderLayout.CENTER);

        pack();
        setLocationRelativeTo(null);
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
    }

    private void onRefresh() {
        System.out.println("Refreshing the tree...");
        // Refresh the tree data
    }

    private void onPin() {
        System.out.println("Toggling the pin...");
        // Toggle the pin
    }

    private void onNewGroup() {
        System.out.println("Adding a new group...");
        // Add a new group
    }

    private void onTreeSelectionChanged() {
        DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();
        if (node != null) {
            // Do something when the tree selection is changed
            System.out.println("Selection changed: " + node.toString());
        }
    }

    private void onTreeItemDoubleClicked() {
        DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();
        if (node != null) {
            // Do something when a tree item is double-clicked
            System.out.println("Double-clicked: " + node.toString());
        }
    }

    public void setWindowListener(WindowListener listener) {
        this.windowListener = listener;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            GroupWindow window = new GroupWindow();
            window.setVisible(true);
        });
    }
}
