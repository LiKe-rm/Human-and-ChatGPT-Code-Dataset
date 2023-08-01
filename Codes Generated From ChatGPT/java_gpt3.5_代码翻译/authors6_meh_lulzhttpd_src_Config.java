import org.w3c.dom.*;
import javax.xml.parsers.*;
import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Config {
    private static boolean inited;
    private static String t_log;
    private static Document doc;

    public static void init(String configFile, String configType) throws Exception {
        if (!inited) {
            inited = true;

            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document config;

            try {
                config = builder.parse(new File(configFile));
            } catch (Exception e) {
                throw new Exception("CONFIG_FILE_NOT_FOUND");
            }

            if (config != null) {
                doc = parse(config);
                doc.normalizeDocument();
            } else {
                throw new Exception("CONFIG_PARSE_ERROR");
            }
        }
    }

    public static String get(String attr) {
        String[] parts = attr.split("->");
        boolean error = false;
        String result = "";

        Element actual = doc.getDocumentElement();
        for (int i = 0; i < parts.length; i++) {
            NodeList nodes = actual.getElementsByTagName(parts[i].replaceAll("\\[.*\\]", ""));

            if (nodes.getLength() == 0) {
                error = true;
                break;
            } else if (nodes.getLength() > 1) {
                Matcher matcher = Pattern.compile("\\[(\\d+)]").matcher(parts[i]);
                if (matcher.find()) {
                    int item = Integer.parseInt(matcher.group(1));

                    if (item >= nodes.getLength()) {
                        error = true;
                        break;
                    }

                    actual = (Element) nodes.item(item);
                }

                matcher = Pattern.compile("\\[([^\\[\\]]*)]$").matcher(parts[i]);
                if (matcher.find()) {
                    result = actual.getAttribute(matcher.group(1));
                    break;
                } else {
                    actual = (Element) nodes.item(0);
                }
            } else {
                Matcher matcher = Pattern.compile("\\[(.*)]$").matcher(parts[i]);
                if (matcher.find()) {
                    result = ((Element) nodes.item(0)).getAttribute(matcher.group(1));
                    break;
                } else {
                    actual = (Element) nodes.item(0);
                }
            }
        }

        if (result.isEmpty() && !error) {
            result = actual.getFirstChild().getNodeValue();
        }

        return result;
    }

    public static boolean test(String configFile) {
        return false;
    }

    public static String testLog() {
        return t_log;
    }

    private static Document parse(Document doc) {
        Config.doc = doc;
        fixElement(doc.getDocumentElement());

        NodeList includes = doc.getElementsByTagName("include");

        for (int i = 0; i < includes.getLength(); i++) {
            Element include = (Element) includes.item(i);

            String path = include.getAttribute("path");

            try {
                DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
                DocumentBuilder builder = factory.newDocumentBuilder();
                Document includeDoc = builder.parse(new File(path));

                include.getParentNode().replaceChild(
                        includeDoc.getDocumentElement().cloneNode(true),
                        include
                );
            } catch (Exception e) {
                System.err.println("Could not include " + path);
            }
        }

        return doc;
    }

    private static void fixElement(Element element) {
        NodeList childNodes = element.getChildNodes();

        for (int i = 0; i < childNodes.getLength(); i++) {
            Node node = childNodes.item(i);

            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element ele =                 (Element) node;
                if (ele.hasAttribute("path")) {
                    ele.setAttribute("path", fixPath(ele.getAttribute("path")));
                }
                fixElement(ele);
            }
        }
    }

    private static String fixPath(String path) {
        String fixedPath = path;

        fixedPath = fixedPath.replaceAll("%includes%", Config.get("directories->includes[path]"));
        fixedPath = fixedPath.replaceAll("%modules%", Config.get("directories->modules[path]"));
        fixedPath = fixedPath.replaceAll("%logs%", Config.get("directories->logs[path]"));

        return fixedPath;
    }

    public static void main(String[] args) {
        try {
            Config.init("config.xml", "xml");
            System.out.println(Config.get("some->path->attribute"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

