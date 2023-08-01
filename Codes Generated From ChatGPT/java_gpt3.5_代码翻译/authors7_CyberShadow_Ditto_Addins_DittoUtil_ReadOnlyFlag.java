import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.BasicFileAttributes;
import java.nio.file.attribute.FileAttribute;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class ReadOnlyFlag {

    public ReadOnlyFlag() {
    }

    public boolean resetReadOnlyFlag(DittoInfo dittoInfo, IClip clip, boolean resetFlag) {
        IClipFormats formats = clip.getClips();
        if (formats != null) {
            List<String> lines = new ArrayList<>();

            loadHDropFiles(lines, formats);
            if (lines.isEmpty()) {
                loadUnicodeFiles(lines, formats);
            }
            if (lines.isEmpty()) {
                loadTextFiles(lines, formats);
            }

            for (String filePath : lines) {
                filePath = filePath.trim().toLowerCase();

                try {
                    File file = new File(filePath);
                    Set<PosixFilePermission> perms = Files.getPosixFilePermissions(file.toPath());

                    if (resetFlag) {
                        perms.add(PosixFilePermission.OWNER_WRITE);
                        perms.add(PosixFilePermission.GROUP_WRITE);
                        perms.add(PosixFilePermission.OTHERS_WRITE);
                    } else {
                        perms.remove(PosixFilePermission.OWNER_WRITE);
                        perms.remove(PosixFilePermission.GROUP_WRITE);
                        perms.remove(PosixFilePermission.OTHERS_WRITE);
                    }

                    Files.setPosixFilePermissions(file.toPath(), perms);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return true;
    }

    private boolean loadUnicodeFiles(List<String> lines, IClipFormats formats) {
        IClipFormat format = formats.findFormatEx("CF_UNICODETEXT");
        if (format != null) {
            String data = format.getData();
            if (data != null) {
                String[] splitLines = data.split("\\r?\\n");
                for (String line : splitLines) {
                    lines.add(line);
                }
            }
        }
        return !lines.isEmpty();
    }

    private boolean loadTextFiles(List<String> lines, IClipFormats formats) {
        IClipFormat format = formats.findFormatEx("CF_TEXT");
        if (format != null) {
            String data = format.getData();
            if (data != null) {
                String[] splitLines = data.split("\\r?\\n");
                for (String line : splitLines) {
                    lines.add(line);
                }
            }
        }
        return !lines.isEmpty();
    }

    private boolean loadHDropFiles(List<String> lines, IClipFormats formats) {
        IClipFormat format = formats.findFormatEx("CF_HDROP");
        if (format != null) {
            List<String> fileList = format.getData();
            if (fileList != null) {
                lines.addAll(fileList);
            }
        }
        return !lines.isEmpty();
    }
}
