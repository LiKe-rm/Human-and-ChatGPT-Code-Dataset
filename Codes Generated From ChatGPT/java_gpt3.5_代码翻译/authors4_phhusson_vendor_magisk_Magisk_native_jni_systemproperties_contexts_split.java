import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ContextsSplit {
    private String filename;
    private List<String> contexts;
    private Map<String, String> prefixes;

    public ContextsSplit(String filename) {
        this.filename = filename;
        this.contexts = new ArrayList<>();
        this.prefixes = new HashMap<>();
    }

    public boolean initializePropertiesFromFile(String filename) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.trim().isEmpty() || line.trim().startsWith("#")) {
                    continue;
                }

                String[] parts = line.trim().split("\\s+", 2);
                if (parts.length == 2) {
                    String propPrefix = parts[0];
                    String context = parts[1];

                    if (!propPrefix.startsWith("ctl.")) {
                        if (contexts.contains(context)) {
                            prefixes.put(propPrefix, context);
                        } else {
                            contexts.add(context);
                            prefixes.put(propPrefix, context);
                        }
                    }
                }
            }
            return true;
        } catch (IOException e) {
            return false;
        }
    }

    public boolean initializeProperties() {
        String[] possiblePaths = {
                "/property_contexts",
                "/system/etc/selinux/plat_property_contexts",
                "/vendor/etc/selinux/vendor_property_contexts",
                "/vendor/etc/selinux/nonplat_property_contexts",
                "/plat_property_contexts",
                "/vendor_property_contexts",
                "/nonplat_property_contexts"
        };

        for (String path : possiblePaths) {
            if (new File(path).exists() && initializePropertiesFromFile(path)) {
                return true;
            }
        }

        return false;
    }

    public static void main(String[] args) {
        ContextsSplit contextsSplit = new ContextsSplit("property_data");
        if (contextsSplit.initializeProperties()) {
            System.out.println("Properties initialized successfully.");
        } else {
            System.err.println("Failed to initialize properties.");
        }
    }
}
