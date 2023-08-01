import javax.swing.*;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreePath;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class GroupTree extends JTree implements TreeSelectionListener {
    private boolean hide;
    private int selectedFolderID;
    private boolean sentAlready;

    public GroupTree() {
        this.hide = true;
        this.selectedFolderID = -1;
        this.sentAlready = false;

        setModel(createTreeModel());
        getSelectionModel().addTreeSelectionListener(this);
        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    sendToParent(getSelectedID());
                } else if (e.getKeyCode() == KeyEvent.VK_ESCAPE) {
                    sendToParent(-1);
                }
            }
        });

        // Fill the tree with data
        fillTree();
    }

    private DefaultTreeModel createTreeModel() {
        DefaultMutableTreeNode rootNode = new DefaultMutableTreeNode("-No Group-");
        rootNode.setUserObject(-1);
        return new DefaultTreeModel(rootNode);
    }

    private void fillTree() {
        // Replace this with your data loading implementation
        DefaultMutableTreeNode rootNode = (DefaultMutableTreeNode) getModel().getRoot();
        rootNode.removeAllChildren();
        sentAlready = false;

        DefaultMutableTreeNode childNode = new DefaultMutableTreeNode("Sample Group");
        childNode.setUserObject(1);
        rootNode.add(childNode);

        // Refresh the tree model
        ((DefaultTreeModel) getModel()).reload();
    }

    @Override
    public void valueChanged(TreeSelectionEvent e) {
        if (hide) {
            TreePath path = e.getNewLeadSelectionPath();
            if (path != null) {
                DefaultMutableTreeNode node = (DefaultMutableTreeNode) path.getLastPathComponent();
                int id = (int) node.getUserObject();
                sendToParent(id);
            }
        }
    }

    private int getSelectedID() {
        TreePath path = getSelectionPath();
        if (path != null) {
            DefaultMutableTreeNode node = (DefaultMutableTreeNode) path.getLastPathComponent();
            return (int) node.getUserObject();
        }
        return -1;
    }

    private void sendToParent(int parentId) {
        if (!sentAlready) {
            sentAlready = true;
            // Implement your custom parent communication here
            System.out.println("Sent to parent: " + parentId);
        }
    }

    public boolean addNode(String text, int id) {
        TreePath path = getSelectionPath();
        if (path == null) {
            return false;
        }

        DefaultMutableTreeNode parentNode = (DefaultMutableTreeNode) path.getLastPathComponent();
        DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(text);
        newNode.setUserObject(id);
        parentNode.add(newNode);
        ((DefaultTreeModel) getModel()).reload();

        return true;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("GroupTree");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(300, 400);

            GroupTree groupTree = new GroupTree();
            JScrollPane scrollPane = new JScrollPane(groupTree);
            frame.add(scrollPane);

            frame.setVisible(true);
        });
    }
}
