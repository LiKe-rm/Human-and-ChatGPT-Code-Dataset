import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.List;
import javax.imageio.ImageIO;

public class PasteImageAsHtmlImage {
    private static String dibImagePath = System.getProperty("java.io.tmpdir") + File.separator + "ditto";
    private static int dibImageName = 1;

    public PasteImageAsHtmlImage() {
    }

    public boolean convertPathToHtmlImageTag(DittoInfo dittoInfo, IClip clip) {
        boolean result = false;
        IClipFormats formats = clip.getClips();

        if (formats != null) {
            if (dibImagePath.isEmpty()) {
                createLocalPath(true);
            }

            String imgTag = "";

            IClipFormat dibFormat = formats.findFormatEx("CF_DIB");
            if (dibFormat != null) {
                String filePath = dibImagePath + File.separator + dibImageName + ".bmp";
                dibImageName++;

                BufferedImage image = dibFormat.getData();
                try {
                    ImageIO.write(image, "bmp", new File(filePath));
                    imgTag = String.format("<IMG src=\"file:///%s\">", filePath);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } else {
                IClipFormat hDropFormat = formats.findFormatEx("CF_HDROP");
                if (hDropFormat != null) {
                    List<String> fileList = hDropFormat.getData();
                    List<String> imageTags = new ArrayList<>();

                    for (String file : fileList) {
                        String lowerCaseFile = file.toLowerCase();
                        if (lowerCaseFile.endsWith(".bmp") || lowerCaseFile.endsWith(".dib") || lowerCaseFile.endsWith(".jpg") || lowerCaseFile.endsWith(".jpeg")
                                || lowerCaseFile.endsWith(".jpe") || lowerCaseFile.endsWith(".jfif") || lowerCaseFile.endsWith(".gif") || lowerCaseFile.endsWith(".tif")
                                || lowerCaseFile.endsWith(".tiff") || lowerCaseFile.endsWith(".png")) {

                            String tag = String.format("<IMG src=\"file:///%s\">", file);
                            imageTags.add(tag);
                        }
                    }

                    imgTag = String.join("<br>", imageTags);
                }
            }

            if (!imgTag.isEmpty()) {
                formats.deleteAll();
                formats.addNew("HTML Format", imgTag);
                result = true;
            }
        }

        return result;
    }

    public boolean cleanupPastedImages() {
        if (dibImagePath.isEmpty()) {
            createLocalPath(false);
        }

        try {
            Files.walk(Paths.get(dibImagePath)).filter(Files::isRegularFile).forEach(file -> {
                try {
                    Files.delete(file);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });

            return Files.deleteIfExists(Paths.get(dibImagePath));
        } catch (IOException e) {
            e.printStackTrace();
        }

        return false;
    }

    private void createLocalPath(boolean createDir) {
        if (createDir) {
            new File(dibImagePath).mkdir();
        }
    }
}
