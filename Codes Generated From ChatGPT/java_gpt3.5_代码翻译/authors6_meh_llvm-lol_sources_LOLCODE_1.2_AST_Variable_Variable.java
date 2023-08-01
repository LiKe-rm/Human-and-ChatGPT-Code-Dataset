public class Variable {
    public enum Cast {
        NOOB,
        NUMBR,
        NUMBAR,
        YARN,
        TROOF
    }

    private Cast cast;
    private String value;

    public Variable() {
        this.cast = Cast.NOOB;
        this.value = "";
    }

    public Variable(String value, Cast cast) {
        this.cast = cast;
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public Cast getCast() {
        return cast;
    }

    public void setCast(Cast cast) {
        this.cast = cast;
    }

    public String toYARN() {
        return value;
    }

    public long toNUMBR() {
        switch (cast) {
            case YARN:
            case NUMBR:
            case NUMBAR:
                return Long.parseLong(value);
            case TROOF:
                return "WIN".equals(value) ? 1 : 0;
            default: // NOOB
                return 0;
        }
    }

    public double toNUMBAR() {
        switch (cast) {
            case YARN:
            case NUMBR:
            case NUMBAR:
                return Double.parseDouble(value);
            case TROOF:
                return "WIN".equals(value) ? 1 : 0;
            default: // NOOB
                return 0;
        }
    }

    public boolean toTROOF() {
        switch (cast) {
            case YARN:
                return value.length() > 0;
            case NUMBR:
                return Long.parseLong(value) != 0;
            case NUMBAR:
                return Double.parseDouble(value) != 0;
            case TROOF:
                return "WIN".equals(value);
            default: // NOOB
                return false;
        }
    }
}
