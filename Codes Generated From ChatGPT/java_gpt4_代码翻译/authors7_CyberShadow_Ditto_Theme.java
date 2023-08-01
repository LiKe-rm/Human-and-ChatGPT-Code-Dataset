import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class Theme {
    private long fileVersion;
    private String author;
    private String notes;

    private Color captionLeft;
    private Color captionRight;
    private Color captionLeftTopMost;
    private Color captionRightTopMost;
    private Color captionLeftNotConnected;
    private Color captionRightNotConnected;
    private Color captionTextColor;
    private Color listBoxOddRowsBG;
    private Color listBoxEvenRowsBG;
    private Color listBoxOddRowsText;
    private Color listBoxEvenRowsText;
    private Color listBoxSelectedBG;
    private Color listBoxSelectedNoFocusBG;
    private Color listBoxSelectedText;
    private Color listBoxSelectedNoFocusText;

    public Theme() {
        captionLeft = new Color(0, 84, 195);
        captionRight = new Color(61, 149, 255);
        captionLeftTopMost = new Color(122, 150, 223);
        captionRightTopMost = new Color(157, 185, 235);
        captionLeftNotConnected = new Color(255, 0, 0);
        captionRightNotConnected = new Color(255, 0, 0);
        captionTextColor = new Color(255, 255, 255);
        listBoxOddRowsBG = new Color(255, 255, 255);
        listBoxEvenRowsBG = new Color(240, 240, 240);
        listBoxOddRowsText = new Color(0, 0, 0);
        listBoxEvenRowsText = new Color(0, 0, 0);
        listBoxSelectedBG = new Color(30, 116, 211);
        listBoxSelectedNoFocusBG = new Color(236, 233, 216);
        listBoxSelectedText = new Color(255, 255, 255);
        listBoxSelectedNoFocusText = new Color(0, 0, 0);
    }

    public boolean load(String themePath, boolean headerOnly) {
        if (themePath == null || themePath.isEmpty()) {
            return false;
        }

        File themeFile = new File(themePath);
        if (!themeFile.exists()) {
            System.err.println("Theme file not found: " + themePath);
            return false;
        }

        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        try {
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(themeFile);
            Element themeElement = document.getDocumentElement();

            fileVersion = Long.parseLong(themeElement.getAttribute("Version"));
            author = themeElement.getAttribute("Author");
            notes = themeElement.getAttribute("Notes");

            if (headerOnly) {
                return true;
            }

            captionLeft = loadElement(themeElement, "CaptionLeft");
            captionRight = loadElement(themeElement, "CaptionRight");
            captionLeftTopMost = loadElement(themeElement, "CaptionLeftTopMost");
            captionRightTopMost = loadElement(themeElement, "CaptionRightTopMost");
            captionLeftNotConnected = loadElement(themeElement, "CaptionLeftNotConnected");
            captionRightNotConnected = loadElement(themeElement, "CaptionRightNotConnected");
            captionTextColor = loadElement(themeElement, "CaptionTextColor");
            listBoxOddRowsBG = loadElement(themeElement, "ListBoxOddRowsBG");
            listBoxEvenRowsBG = loadElement(themeElement, "ListBoxEvenRowsBG");
            listBoxOddRowsText = loadElement(themeElement, "ListBoxOddRowsText");
            listBoxEvenRowsText = loadElement(themeElement, "ListBoxEvenRowsText");
            listBoxSelectedBG = loadElement(themeElement, "ListBoxSelectedBG");
            listBoxSelectedNoFocusBG = loadElement(themeElement, "ListBoxSelectedNoFocusBG");
            listBoxSelectedText = loadElement(themeElement, "ListBoxSelectedText");
            listBoxSelectedNoFocusText = loadElement(themeElement, "ListBoxSelectedNoFocusText");

            return true;
        } catch (ParserConfigurationException | SAXException | IOException e) {
            System.err.println("Error loading theme: " + e.getMessage());
            return false;
        }
    }

    private Color loadElement(Element parent, String nodeName) {
        NodeList nodeList = parent.getElementsByTagName(nodeName);
        if (nodeList.getLength() == 0) {
            System.err.println("Theme Load, error loading Node = " + nodeName);
            return null;
        }

        Element node = (Element) nodeList.item(0);
        String colorValue = node.getTextContent().trim();
        colorValue = colorValue.replace("RGB(", "").replace(")", "");
        String[] rgbValues = colorValue.split(",");

        int r, g, b;
        if (rgbValues.length == 1) {
            r = g = b = Integer.parseInt(rgbValues[0].trim());
        } else if (rgbValues.length == 3) {
            r = Integer.parseInt(rgbValues[0].trim());
            g = Integer.parseInt(rgbValues[1].trim());
            b = Integer.parseInt(rgbValues[2].trim());
        } else {
            System.err.println("Invalid color value: " + colorValue);
            return null;
        }

        return new Color(r, g, b);
    }
}

