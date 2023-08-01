import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class BitmapHelper {

    private BufferedImage bufferedImage;

    public BitmapHelper() {
    }

    public void loadImage(String filePath) throws IOException {
        bufferedImage = ImageIO.read(new File(filePath));
    }

    public int getBitmapWidth() {
        return bufferedImage.getWidth();
    }

    public int getBitmapHeight() {
        return bufferedImage.getHeight();
    }

    public BufferedImage getScaledBitmap(int maxWidth, int maxHeight) {
        int width = bufferedImage.getWidth();
        int height = bufferedImage.getHeight();

        int newWidth = maxWidth;
        int newHeight = (int) (((double) newWidth / width) * height);

        if (newHeight > maxHeight) {
            newHeight = maxHeight;
            newWidth = (int) (((double) newHeight / height) * width);
        }

        BufferedImage scaledImage = new BufferedImage(newWidth, newHeight, bufferedImage.getType());
        Graphics2D g = scaledImage.createGraphics();
        g.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
        g.drawImage(bufferedImage, 0, 0, newWidth, newHeight, null);
        g.dispose();

        return scaledImage;
    }

    public void saveScaledBitmap(String filePath, int maxWidth, int maxHeight) throws IOException {
        BufferedImage scaledImage = getScaledBitmap(maxWidth, maxHeight);
        ImageIO.write(scaledImage, "png", new File(filePath));
    }

    public static void main(String[] args) {
        BitmapHelper bitmapHelper = new BitmapHelper();

        try {
            bitmapHelper.loadImage("input_image.png");
            System.out.println("Width: " + bitmapHelper.getBitmapWidth());
            System.out.println("Height: " + bitmapHelper.getBitmapHeight());
            bitmapHelper.saveScaledBitmap("output_image.png", 200, 100);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
