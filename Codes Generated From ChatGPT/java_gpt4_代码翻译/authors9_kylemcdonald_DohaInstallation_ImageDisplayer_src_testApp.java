import processing.core.*;
import java.io.*;
import java.text.*;
import java.nio.file.*;
import java.util.*;

public class TestApp extends PApplet {
    private static final String DATE_FORMAT = "MM-dd-yyyy";
    private static final String TIME_FORMAT = "HH-mm-ss";
    private static final String IMAGES_DIRECTORY = "images";
    private static final int UPDATE_DIRECTORY_RATE = 5;

    private PImage mostRecentImage;
    private int lastSeconds;

    public static void main(String[] args) {
        PApplet.main("TestApp");
    }

    public void settings() {
        size(800, 600);
    }

    public void setup() {
        frameRate(10);
        lastSeconds = 0;
    }

    private Path getMostRecent(Path path, String format) {
        SimpleDateFormat sdf = new SimpleDateFormat(format);
        Optional<File> mostRecentFile = null;
        try (Stream<Path> paths = Files.walk(path)) {
            mostRecentFile = paths
                .filter(Files::isRegularFile)
                .max(Comparator.comparing(p -> {
                    try {
                        return sdf.parse(p.getFileName().toString());
                    } catch (ParseException e) {
                        return null;
                    }
                }));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return mostRecentFile.orElse(Paths.get("")).toAbsolutePath();
    }

    public void update() {
        int curSeconds = second();
        if (curSeconds != lastSeconds && curSeconds % UPDATE_DIRECTORY_RATE == 0) {
            Path currentDirectory = getMostRecent(Paths.get(IMAGES_DIRECTORY), DATE_FORMAT);
            Path currentImage = getMostRecent(currentDirectory, TIME_FORMAT);
            String curFilename = currentImage.toString();
            System.out.println("Loading image from " + curFilename);
            // sleep for half a cycle to let the image download
            delay(UPDATE_DIRECTORY_RATE * 1000 / 2);
            mostRecentImage = loadImage(curFilename);
        }
        lastSeconds = curSeconds;
    }

    public void draw() {
        update();
        if (mostRecentImage != null) {
            // span horizontally until filled
            float w = mostRecentImage.width;
            float h = mostRecentImage.height;
            float s = (float) width / w;
            mostRecentImage.resize((int) (w * s), (int) (h * s));
            image(mostRecentImage, 0, 0);
        }
    }
}
