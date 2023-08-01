import javax.sound.sampled.*;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class RPCEmuSound {
    private SourceDataLine audioLine;
    private int bufferLength;
    private int sampleRate;

    public RPCEmuSound(int bufferLength) {
        this.bufferLength = bufferLength;
        this.sampleRate = 0;
    }

    public void initSoundSystem() {
        changeSampleRate(sampleRate);
    }

    public void changeSampleRate(int sampleRate) {
        this.sampleRate = sampleRate;
        AudioFormat audioFormat = new AudioFormat(sampleRate, 16, 2, true, false);
        DataLine.Info info = new DataLine.Info(SourceDataLine.class, audioFormat);

        try {
            if (audioLine != null) {
                audioLine.stop();
                audioLine.close();
            }

            audioLine = (SourceDataLine) AudioSystem.getLine(info);
            audioLine.open(audioFormat, bufferLength * 4);
            audioLine.start();

        } catch (LineUnavailableException e) {
            e.printStackTrace();
            throw new RuntimeException("Failed to create audio line. No audio will be played.");
        }
    }

    public int getBufferFreeSpace() {
        if (audioLine != null) {
            return audioLine.available();
        } else {
            return bufferLength;
        }
    }

    public void playBuffer(int sampleRate, byte[] buffer) {
        if (sampleRate != this.sampleRate) {
            changeSampleRate(sampleRate);
        }

        if (audioLine != null) {
            audioLine.write(buffer, 0, buffer.length);
        }
    }

    public void pause() {
        if (audioLine != null) {
            audioLine.stop();
        }
    }

    public void restart() {
        if (audioLine != null) {
            audioLine.start();
        }
    }

    public void close() {
        if (audioLine != null) {
            audioLine.stop();
            audioLine.close();
        }
    }
}
