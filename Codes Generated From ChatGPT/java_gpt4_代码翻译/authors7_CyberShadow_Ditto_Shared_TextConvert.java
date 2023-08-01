import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class TextConvert {

    private static final byte[] kUtf8Limits = { (byte) 0xC0, (byte) 0xE0, (byte) 0xF0, (byte) 0xF8, (byte) 0xFC };

    public String multiByteToUnicodeString(String srcString) {
        return new String(srcString.getBytes(StandardCharsets.ISO_8859_1), StandardCharsets.UTF_16LE);
    }

    public String unicodeStringToMultiByte(String srcString) {
        return new String(srcString.getBytes(StandardCharsets.UTF_16LE), StandardCharsets.ISO_8859_1);
    }

    public String convertToChar(String src) {
        return src;
    }

    public String convertToUnicode(String src) {
        return src;
    }

    public boolean convertFromUTF8(String src, StringBuilder dest) {
        dest.setLength(0);
        int i = 0;

        while (i < src.length()) {
            char c = src.charAt(i++);
            if (c < 0x80) {
                dest.append(c);
                continue;
            }

            if (c < 0xC0) {
                dest.append(src);
                return false;
            }

            int numAdds;
            for (numAdds = 1; numAdds < 5; numAdds++) {
                if (c < kUtf8Limits[numAdds]) {
                    break;
                }
            }

            int value = (c - kUtf8Limits[numAdds - 1]);

            while (numAdds > 0) {
                if (i >= src.length()) {
                    dest.append(src);
                    return false;
                }

                char c2 = src.charAt(i++);
                if (c2 < 0x80 || c2 >= 0xC0) {
                    dest.append(src);
                    return false;
                }

                value <<= 6;
                value |= (c2 - 0x80);
                numAdds--;
            }

            if (value < 0x10000) {
                dest.append((char) value);
            } else {
                value -= 0x10000;
                if (value >= 0x100000) {
                    dest.append(src);
                    return false;
                }
                dest.append((char) (0xD800 + (value >> 10)));
                dest.append((char) (0xDC00 + (value & 0x3FF)));
            }
        }

        return true;
    }

    public boolean convertToUTF8(String src, StringBuilder dest) {
        dest.setLength(0);
        int i = 0;

        while (i < src.length()) {
            int value = (int) src.charAt(i++);
            if (value < 0x80) {
                dest.append((char) value);
                continue;
            }

            if (value >= 0xD800 && value < 0xE000) {
                if (value >= 0xDC00) {
                    dest.append(src);
                    return false;
                }

                if (i >= src.length()) {
                    dest.append(src);
                    return false;
                }

                int c2 = (int) src.charAt(i++);
                if (c2 < 0xDC00 || c2 >= 0xE000) {
                    dest.append(src);
                    return false;
                }

                value = ((value - 0xD800) << 10) | (c2 - 0xDC00);
            }

            int numAdds;
            for (numAdds = 1; numAdds < 5; numAdds++) {
                if (value < (((int) 1) << (numAdds * 5 + 6))) {
                    break;
                }
            }
            dest.append((char) (kUtf8Limits[numAdds - 1] + (value >> (6 * numAdds))));
            while (numAdds > 0) {
                numAdds--;
                dest.append((char) (0x80 + ((value >> (6 * numAdds)) & 0x3F)));
            }
        }

        return true;
    }

    public static void main(String[] args) {
        TextConvert converter = new TextConvert();

        String src = "Hello, World!";
        String unicode = converter.multiByteToUnicodeString(src);
        String multibyte = converter.unicodeStringToMultiByte(unicode);

        System.out.println("Original: " + src);
        System.out.println("Unicode: " + unicode);
        System.out.println("Multibyte: " + multibyte);

        StringBuilder fromUtf8 = new StringBuilder();
        converter.convertFromUTF8(src, fromUtf8);
        System.out.println("From UTF-8: " + fromUtf8.toString());

        StringBuilder toUtf8 = new StringBuilder();
        converter.convertToUTF8(src, toUtf8);
        System.out.println("To UTF-8: " + toUtf8.toString());
    }
}
