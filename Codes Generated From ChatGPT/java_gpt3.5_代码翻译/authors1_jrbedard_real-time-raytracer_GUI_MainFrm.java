import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainFrame extends JFrame {
    private RayTracerView rayTracerView;

    public MainFrame() {
        setTitle("Ray Tracer");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(340, 280);
        setResizable(true);

        rayTracerView = new RayTracerView();
        getContentPane().add(rayTracerView);

        JMenuBar menuBar = new JMenuBar();
        JMenu resolutionMenu = new JMenu("Resolution");
        menuBar.add(resolutionMenu);

        JMenuItem res160x120 = new JMenuItem("160x120");
        res160x120.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rayTracerView.changeResolution(160, 120);
            }
        });
        resolutionMenu.add(res160x120);

        JMenuItem res340x280 = new JMenuItem("340x280");
        res340x280.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rayTracerView.changeResolution(340, 280);
            }
        });
        resolutionMenu.add(res340x280);

        JMenuItem res640x480 = new JMenuItem("640x480");
        res640x480.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rayTracerView.changeResolution(640, 480);
            }
        });
        resolutionMenu.add(res640x480);

        JMenuItem res800x600 = new JMenuItem("800x600");
        res800x600.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rayTracerView.changeResolution(800, 600);
            }
        });
        resolutionMenu.add(res800x600);

        setJMenuBar(menuBar);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                MainFrame mainFrame = new MainFrame();
                mainFrame.setVisible(true);
            }
        });
    }
}
