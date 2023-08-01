import com.google.protobuf.CodedInputStream;
import com.google.protobuf.CodedOutputStream;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class ResetProp {

    public static class Property {
        public String name;
        public String value;

        public Property(String name) {
            this.name = name;
            this.value = "";
        }

        public Property(String name, String value) {
            this.name = name;
            this.value = value;
        }
    }

    public interface ReadCallback {
        void exec(String name, String value);
    }

    private static final String PERSISTENT_PROPERTY_DIR = "path/to/persistent_properties";
    private static final boolean USE_PB = false;

    public static void main(String[] args) {
        // Example usage
    }

    public static void persistGetprop(ReadCallback readCallback) {
        if (USE_PB) {
            pbGetprop(readCallback);
        } else {
            File dir = new File(PERSISTENT_PROPERTY_DIR);
            File[] files = dir.listFiles();
            if (files != null) {
                for (File file : files) {
                    String value = fileGetprop(file.getName());
                    if (!value.isEmpty()) {
                        readCallback.exec(file.getName(), value);
                    }
                }
            }
        }
    }

    public static String persistGetprop(String name) {
        if (USE_PB) {
            Property property = new Property(name);
            persistGetprop((n, v) -> {
                if (n.equals(name)) {
                    property.value = v;
                }
            });
            return property.value;
        } else {
            return fileGetprop(name);
        }
    }

    public static boolean persistDeleteprop(String name) {
        if (USE_PB) {
            List<Property> propList = new ArrayList<>();
            persistGetprop((n, v) -> propList.add(new Property(n, v)));

            propList.removeIf(p -> p.name.equals(name));

            // Serialize properties back
            File outputFile = new File(PERSISTENT_PROPERTY_DIR, "persistent_properties.tmp");
            try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                CodedOutputStream cos = CodedOutputStream.newInstance(fos);

                for (Property prop : propList) {
                    cos.writeString(1, prop.name);
                    cos.writeString(2, prop.value);
                }

                cos.flush();
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            }

            // Replace original file with the new one
            File originalFile = new File(PERSISTENT_PROPERTY_DIR, "persistent_properties");
            try {
                Files.copy(outputFile.toPath(), originalFile.toPath());
                Files.delete(outputFile.toPath());
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            }
            return true;
        } else {
            File file = new File(PERSISTENT_PROPERTY_DIR, name);
            return file.delete();
        }
    }

    private static void pbGetprop(ReadCallback readCallback) {
        // Implement protobuf decoding here
    }

    private static String fileGetprop(String name) {
        File file = new File(PERSISTENT_PROPERTY_DIR, name);
        try {
            return new String(Files.readAllBytes(Paths.get(file.getAbsolutePath()))).trim();
        } catch (IOException e) {
            return "";
        }
    }
}
