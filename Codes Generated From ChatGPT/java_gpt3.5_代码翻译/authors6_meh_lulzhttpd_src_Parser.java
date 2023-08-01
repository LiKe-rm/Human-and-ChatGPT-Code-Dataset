import org.w3c.dom.Document;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Parser {

    public Parser() {
    }

    public Document load(String configFile, ConfType configType) throws IOException, ParserConfigurationException {
        Document document;

        switch (configType) {
            case NONE:
                return load(configFile, recognize(Files.readString(Path.of(configFile))));
            case LULZHTTPD: {
                XMLParser parser = new XMLParser();
                document = parser.load(configFile);
            }
            break;

            case APACHE: {
                throw new UnsupportedOperationException();
                // Implement ApacheParser and use it here.
            }

            case LIGHTTPD: {
                throw new UnsupportedOperationException();
                // Implement LighttpParser and use it here.
            }
        }

        return document;
    }

    public ConfType parseConfType(String configType) {
        String lowerConfigType = configType.toLowerCase();

        if (lowerConfigType.equals("lulzhttpd")) {
            return ConfType.LULZHTTPD;
        } else if (lowerConfigType.equals("apache")) {
            return ConfType.APACHE;
        } else if (lowerConfigType.equals("lighttpd")) {
            return ConfType.LIGHTTPD;
        } else {
            return ConfType.NONE;
        }
    }

    private ConfType recognize(String text) {
        if (text.matches("(?s)/<\\s*\\?\\s*xml|^\\s*<server>.*")) {
            return ConfType.LULZHTTPD;
        } else if (text.matches("^\\s*ServerRoot.*")) {
            return ConfType.APACHE;
        } else if (text.matches("^\\s*server\\.document-root.*")) {
            return ConfType.LIGHTTPD;
        } else {
            throw new UnsupportedOperationException("Config file not supported");
        }
    }

    public enum ConfType {
        NONE,
        LULZHTTPD,
        APACHE,
        LIGHTTPD
    }
}
