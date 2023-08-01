import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class RayTracerView extends JPanel implements MouseListener, MouseMotionListener {

    private static final long serialVersionUID = 1L;

    private int oldMouseX, oldMouseY;
    private int mouseX, mouseY;
    private boolean leftClick, rightClick;

    private App app;

    public RayTracerView() {
        app = new App();

        setFocusable(true);
        addMouseListener(this);
        addMouseMotionListener(this);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        app.update();
        app.render(g);
    }

    public void changeResolution(int x, int y) {
        app.resize(x, y);
        app.getRayTracer().getScene().setResolution(x, y);
    }

    @Override
    public void mouseClicked(MouseEvent e) {
    }

    @Override
    public void mousePressed(MouseEvent e) {
        oldMouseX = mouseX = e.getX();
        oldMouseY = mouseY = e.getY();
        if (e.getButton() == MouseEvent.BUTTON1) {
            leftClick = true;
        } else if (e.getButton() == MouseEvent.BUTTON3) {
            rightClick = true;
        }
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        oldMouseX = mouseX = 0;
        oldMouseY = mouseY = 0;
        if (e.getButton() == MouseEvent.BUTTON1) {
            leftClick = false;
        } else if (e.getButton() == MouseEvent.BUTTON3) {
            rightClick = false;
        }
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        if (leftClick) {
            oldMouseX = mouseX;
            oldMouseY = mouseY;

            mouseX = e.getX();
            mouseY = e.getY();

            app.setYaw(app.getYaw() + (mouseX - oldMouseX));
            app.setPitch(app.getPitch() + (mouseY - oldMouseY));
        } else if (rightClick) {
            oldMouseX = mouseX;
            oldMouseY = mouseY;

            mouseX = e.getX();
            mouseY = e.getY();

            float deltaY = (float) (mouseY - oldMouseY);
            app.moveViewPosition(deltaY);
        }
    }

    @Override
    public void mouseMoved(MouseEvent e) {
    }
}
