import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class CameraFilter {

    private float distortion;
    private float distortionSize;
    private float aberrationAmount;
    private float vignetteSharpness;
    private float vignetteSize;
    private float noiseAmount;

    private final BufferedImage preblur;
    private final BufferedImage postblur;
    private final BlurFilter blur;
    private final Shader shader;

    public CameraFilter(int width, int height) {
        distortion = 0.08f;
        distortionSize = 1.12f;
        aberrationAmount = 0.08f;
        vignetteSharpness = 8f;
        vignetteSize = 0.8f;
        noiseAmount = 0.1f;

        preblur = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        postblur = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        blur = new BlurFilter(width, height, 16, 0.1f, 1, 0.8f);
        shader = new Shader();
        shader.setupShaderFromSource(Shader.GL_FRAGMENT_SHADER, CameraFilterSource.CAMERA_FILTER_SOURCE);
        shader.linkProgram();
    }

    public void begin() {
        Graphics2D g = preblur.createGraphics();
        g.setColor(Color.BLACK);
        g.fillRect(0, 0, preblur.getWidth(), preblur.getHeight());
        g.dispose();
    }

    public void end() {
        blur.begin();
        Graphics2D g = postblur.createGraphics();
        g.drawImage(preblur, 0, 0, null);
        g.dispose();
        blur.end();

        g = postblur.createGraphics();
        g.drawImage(blur.getOutputImage(), 0, 0, null);
        g.dispose();
    }

    public void draw(Graphics2D g) {
        shader.begin();
        shader.setUniformTexture("preblur", preblur);
        shader.setUniformTexture("postblur", postblur);
        shader.setUniform1f("time", System.currentTimeMillis() / 1000f);
        shader.setUniform2f("imageSize", preblur.getWidth(), preblur.getHeight());
        shader.setUniform1f("imageRadius", (float) (Math.sqrt(Math.pow(preblur.getWidth(), 2) + Math.pow(preblur.getHeight(), 2)) / 2.0));
        shader.setUniform1f("distortion", distortion);
        shader.setUniform1f("distortionSize", distortionSize);
        shader.setUniform1f("aberrationAmount", aberrationAmount);
        shader.setUniform1f("vignetteSharpness", vignetteSharpness);
        shader.setUniform1f("vignetteSize", vignetteSize);
        shader.setUniform1f("noiseAmount", noiseAmount);
        g.drawImage(preblur, 0, 0, null);
        shader.end();
    }

    public void setBlurScale(float scale) {
        blur.setScale(scale);
    }

    public void setBlurRotation(float rotation) {
        blur.setRotation(rotation);
    }

    public void setBlurBrightness(float brightness) {
        blur.setBrightness(brightness);
    }

    public void setDistortion(float distortion) {
        this.distortion = distortion;
    }

    public void setDistortionSize(float distortionSize) {
        this.distortionSize = distortionSize;
    }

    public void setAberrationAmount(float aberrationAmount) {
        this.aberrationAmount = aberrationAmount;
    }

    public void setNoiseAmount(float noiseAmount) {
        this.noiseAmount = noiseAmount;
    }

}