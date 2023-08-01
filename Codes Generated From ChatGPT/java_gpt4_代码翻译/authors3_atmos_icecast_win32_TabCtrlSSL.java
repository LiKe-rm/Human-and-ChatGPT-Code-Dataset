import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;

public class TabCtrlSSL {
    private JTabbedPane tabbedPane;

    public TabCtrlSSL() {
        tabbedPane = new JTabbedPane();
    }

    public int addSSLPage(String title, int pageID, JPanel panel) {
        tabbedPane.addTab(title, panel);
        int index = tabbedPane.getTabCount() - 1;
        tabbedPane.setComponentAt(index, panel);
        tabbedPane.setToolTipTextAt(index, String.valueOf(pageID));

        tabbedPane.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                int selectedIndex = tabbedPane.getSelectedIndex();
                JPanel selectedPanel = (JPanel) tabbedPane.getComponentAt(selectedIndex);
                selectedPanel.setVisible(true);

                for (int i = 0; i < tabbedPane.getTabCount(); i++) {
                    if (i != selectedIndex) {
                        JPanel panel = (JPanel) tabbedPane.getComponentAt(i);
                        panel.setVisible(false);
                    }
                }
            }
        });

        return index;
    }

    public boolean removeSSLPage(int index) {
        if (index >= tabbedPane.getTabCount()) {
            return false;
        }

        tabbedPane.remove(index);
        return true;
    }

    public int getSSLPageCount() {
        return tabbedPane.getTabCount();
    }

    public String getSSLPageTitle(int index) {
        return tabbedPane.getTitleAt(index);
    }

    public boolean setSSLPageTitle(int index, String title) {
        if (index >= tabbedPane.getTabCount()) {
            return false;
        }

        tabbedPane.setTitleAt(index, title);
        return true;
    }

    public int getSSLPageID(int index) {
        return Integer.parseInt(tabbedPane.getToolTipTextAt(index));
    }

    public int setSSLPageID(int index, int pageID) {
        int oldPageID = getSSLPageID(index);
        tabbedPane.setToolTipTextAt(index, String.valueOf(pageID));
        return oldPageID;
    }

    public boolean activateSSLPage(int index) {
        if (index >= tabbedPane.getTabCount()) {
            return false;
        }

        tabbedPane.setSelectedIndex(index);
        return true;
    }

    public int getSSLActivePage() {
        return tabbedPane.getSelectedIndex();
    }

    public JPanel getSSLPage(int index) {
        return (JPanel) tabbedPane.getComponentAt(index);
    }

    public int getSSLPageIndex(int pageID) {
        for (int i = 0; i < tabbedPane.getTabCount(); i++) {
            if (getSSLPageID(i) == pageID) {
                return i;
            }
        }

        return -1;
    }
}
