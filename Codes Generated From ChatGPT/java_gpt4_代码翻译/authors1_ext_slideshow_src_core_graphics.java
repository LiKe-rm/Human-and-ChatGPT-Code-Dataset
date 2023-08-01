import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.net.URL;

public class Slideshow {
    private static final int WIDTH = 800;
    private static final int HEIGHT = 600;

    private BufferedImage[] textures = new BufferedImage[2];
    private int counter = 0;

    public static void main(String[] args) {
        Slideshow slideshow = new Slideshow();
        String imagePath = "path/to/image.jpg";

        try {
            slideshow.loadImage(imagePath, true);
        } catch (IOException e) {
            System.err.println("Failed to load image: " + e.getMessage());
        }
    }

    public Slideshow() {
        // Initialize textures
        textures[0] = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
        textures[1] = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
    }

    public void loadImage(String path, boolean letterbox) throws IOException {
        BufferedImage image;

        if (path.startsWith("http://") || path.startsWith("https://")) {
            URL url = new URL(path);
            image = ImageIO.read(url);
        } else {
            image = ImageIO.read(new File(path));
        }

        if (letterbox) {
            image = applyLetterbox(image);
        }

        swapTextures();
        textures[0] = image;
    }

    private BufferedImage applyLetterbox(BufferedImage image) {
        int imageWidth = image.getWidth();
        int imageHeight = image.getHeight();
        float aspectRatio = (float) imageWidth / imageHeight;
        int letterboxWidth = WIDTH;
        int letterboxHeight = HEIGHT;
        float windowAspectRatio = (float) WIDTH / HEIGHT;

        if (aspectRatio > windowAspectRatio) {
            letterboxHeight = (int) (WIDTH / aspectRatio);
        } else {
            letterboxWidth = (int) (HEIGHT * aspectRatio);
        }

        BufferedImage letterboxed = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
        Graphics2D g2d = letterboxed.createGraphics();
        g2d.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);

        int xOffset = (WIDTH - letterboxWidth) / 2;
        int yOffset = (HEIGHT - letterboxHeight) / 2;

        g2d.drawImage(image, xOffset, yOffset, letterboxWidth, letterboxHeight, null);
        g2d.dispose();

        return letterboxed;
    }

    private void swapTextures() {
        BufferedImage temp = textures[0];
        textures[0] = textures[1];
        textures[1] = temp;
    }

    public void displayImage() {
        // Implement a method to display the current image in `textures[0]`.
        // This could be done using a GUI library, such as JavaFX or Swing.
    }
}
