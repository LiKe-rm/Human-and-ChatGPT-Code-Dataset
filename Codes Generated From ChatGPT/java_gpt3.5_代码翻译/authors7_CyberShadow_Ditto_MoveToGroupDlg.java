import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreePath;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class MoveToGroupDialog extends JDialog {
    private JTree tree;
    private DefaultTreeModel treeModel;
    private JButton newGroupButton;
    private int selectedGroup = -1;

    public MoveToGroupDialog(Frame parent) {
        super(parent, true);
        setTitle("Move To Group");

        initComponents();
        pack();
        setLocationRelativeTo(parent);
    }

    private void initComponents() {
        tree = new JTree();
        treeModel = new DefaultTreeModel(new DefaultMutableTreeNode("Root"));
        tree.setModel(treeModel);
        fillTree(treeModel);

        newGroupButton = new JButton("New Group");
        newGroupButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onButtonNewGroup();
            }
        });

        JScrollPane treeScrollPane = new JScrollPane(tree);
        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                        .addComponent(treeScrollPane)
                                        .addComponent(newGroupButton, GroupLayout.Alignment.TRAILING))
                                .addContainerGap())
        );
        layout.setVerticalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addComponent(treeScrollPane)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(newGroupButton)
                                .addContainerGap())
        );

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                onCancel();
            }
        });

        tree.getSelectionModel().addTreeSelectionListener(e -> onOK());
    }

    private void fillTree(DefaultTreeModel model) {
        // Add your tree nodes here, e.g., model.insertNodeInto(new DefaultMutableTreeNode("Group 1"), (DefaultMutableTreeNode) model.getRoot(), 0);
    }

    private int newGroupId(int parentGroupId, String groupName) {
        // Create a new group here and return its ID
        return -1;
    }

    private void onOK() {
        TreePath selectedPath = tree.getSelectionPath();
        if (selectedPath != null) {
            selectedGroup = ((DefaultMutableTreeNode) selectedPath.getLastPathComponent()).hashCode(); // Replace hashCode() with an actual group ID
            setVisible(false);
        }
    }

    private void onCancel() {
        selectedGroup = -1;
        setVisible(false);
    }

    private void onButtonNewGroup() {
        String groupName = JOptionPane.showInputDialog(this, "Enter group name:", "New Group", JOptionPane.PLAIN_MESSAGE);
        if (groupName != null && !groupName.isEmpty()) {
            int parentGroupId = -1;
            TreePath selectedPath = tree.getSelectionPath();
            if (selectedPath != null) {
                parentGroupId = ((DefaultMutableTreeNode) selectedPath.getLastPathComponent()).hashCode(); // Replace hashCode() with an actual group ID
            }
            int newGroupId = newGroupId(parentGroupId, groupName);
            if (newGroupId >= 0) {
                DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(groupName);
                treeModel.insertNodeInto(newNode, (DefaultMutableTreeNode) selectedPath.getLastPathComponent(), 0);
            }
        }
    }

    public int getSelectedGroup() {
        return selectedGroup;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MoveToGroupDialog dialog = new MoveToGroupDialog(null);
            dialog.setVisible(true);
            System.out.println("Selected group: " + dialog.getSelectedGroup());
            System.exit(0);
        });
    }
}
