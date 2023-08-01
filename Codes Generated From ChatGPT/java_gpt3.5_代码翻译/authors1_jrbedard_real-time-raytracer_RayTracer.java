import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RayTracerApp {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            RayTracerFrame frame = new RayTracerFrame();
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setVisible(true);
        });
    }
}

class RayTracerFrame extends JFrame {
    private final RayTracerView rayTracerView;

    public RayTracerFrame() {
        setTitle("Ray Tracer");
        setSize(800, 600);

        rayTracerView = new RayTracerView();
        add(rayTracerView);

        JMenuBar menuBar = new JMenuBar();
        setJMenuBar(menuBar);

        JMenu fileMenu = new JMenu("File");
        menuBar.add(fileMenu);

        JMenuItem openItem = new JMenuItem("Open");
        fileMenu.add(openItem);

        JMenuItem newItem = new JMenuItem("New");
        fileMenu.add(newItem);

        JMenu helpMenu = new JMenu("Help");
        menuBar.add(helpMenu);

        JMenuItem aboutItem = new JMenuItem("About");
        helpMenu.add(aboutItem);
        aboutItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                showAboutDialog();
            }
        });
    }

    private void showAboutDialog() {
        JOptionPane.showMessageDialog(this, "Ray Tracer\nAuthor : Jean-Rene Bedard (jrbedard@gmail.com)");
    }
}

class RayTracerView extends JPanel {

    public RayTracerView() {
        // TODO: Add the view's initialization code here
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        // TODO: Add the view's drawing code here
    }
}
