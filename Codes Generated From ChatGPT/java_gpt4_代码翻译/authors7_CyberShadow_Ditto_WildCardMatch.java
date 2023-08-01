public class WildCardMatch {
    public WildCardMatch() {
    }

    public boolean wildMatch(String sWild, String sString, String sLimitChar) {
        boolean bAny = false;
        boolean bNextIsOptional = false;
        boolean bAuthorizedChar;

        int i = 0;
        int j = 0;

        while (i < sString.length()) {
            if (j < sWild.length()) {
                if (sWild.charAt(j) == '*') {
                    j++;

                    if (j >= sWild.length()) {
                        while (!sLimitChar.isEmpty() && i < sString.length()) {
                            if (sLimitChar.indexOf(sString.charAt(i)) < 0) {
                                return false;
                            }
                            i++;
                        }
                        return true;
                    }

                    bAny = true;
                    bNextIsOptional = false;
                } else {
                    if (sWild.charAt(j) == '^') {
                        j++;
                        bNextIsOptional = true;
                    } else {
                        bAuthorizedChar = (sLimitChar.isEmpty() || (sLimitChar.indexOf(sString.charAt(i)) >= 0));

                        if (sWild.charAt(j) == sString.charAt(i) ||
                                (sWild.charAt(j) == '?' && bAuthorizedChar) ||
                                (bNextIsOptional && !(bAny && bAuthorizedChar))) {

                            if (sWild.charAt(j) == sString.charAt(i)) {
                                bAny = false;
                            }

                            if (sWild.charAt(j) == sString.charAt(i) || sWild.charAt(j) == '?') {
                                i++;
                            }

                            j++;
                            bNextIsOptional = false;
                        } else {
                            if (bAny && bAuthorizedChar) {
                                i++;
                            } else {
                                return false;
                            }
                        }
                    }
                }
            } else {
                return false;
            }
        }

        if (j < sWild.length() && sWild.charAt(j) == '^') {
            bNextIsOptional = true;
            j++;
        }

        while ((j < sWild.length() && sWild.charAt(j) == '*') || bNextIsOptional) {
            j++;
            bNextIsOptional = false;

            if (j < sWild.length() && sWild.charAt(j) == '^') {
                bNextIsOptional = true;
                j++;
            }
        }

        return j >= sWild.length();
    }

    public static void main(String[] args) {
        WildCardMatch wildCardMatch = new WildCardMatch();
        System.out.println(wildCardMatch.wildMatch("*e*o*", "hello world", ""));
    }
}
