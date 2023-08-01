import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class TextConvert {

    public String multiByteToUnicodeString(String srcString) {
        byte[] bytes = srcString.getBytes(StandardCharsets.ISO_8859_1);
        return new String(bytes, StandardCharsets.UTF_16);
    }

    public String unicodeStringToMultiByte(String srcString) {
        byte[] bytes = srcString.getBytes(StandardCharsets.UTF_16);
        return new String(bytes, StandardCharsets.ISO_8859_1);
    }

    public String convertToChar(String src) {
        if (Charset.defaultCharset().equals(StandardCharsets.UTF_16)) {
            return unicodeStringToMultiByte(src);
        } else {
            return src;
        }
    }

    public String convertToUnicode(String src) {
        if (Charset.defaultCharset().equals(StandardCharsets.UTF_16)) {
            return src;
        } else {
            return multiByteToUnicodeString(src);
        }
    }

    public boolean convertFromUTF8(String src, StringBuilder dest) {
        if (Charset.defaultCharset().equals(StandardCharsets.UTF_16)) {
            try {
                byte[] bytes = src.getBytes(StandardCharsets.UTF_8);
                String result = new String(bytes, StandardCharsets.UTF_16);
                dest.append(result);
                return true;
            } catch (Exception e) {
                dest.append(src);
                return false;
            }
        } else {
            dest.append(src);
            return true;
        }
    }

    public boolean convertToUTF8(String src, StringBuilder dest) {
        if (Charset.defaultCharset().equals(StandardCharsets.UTF_16)) {
            try {
                byte[] bytes = src.getBytes(StandardCharsets.UTF_16);
                String result = new String(bytes, StandardCharsets.UTF_8);
                dest.append(result);
                return true;
            } catch (Exception e) {
                dest.append(src);
                return false;
            }
        } else {
            dest.append(src);
            return true;
        }
    }
}
