import java.util.ArrayList;
import java.util.List;

public class FormatSQL {
    private enum SpecialTypes {
        INVALID, NOT, OR, AND
    }

    private String variable;
    private StringBuilder where;

    public FormatSQL() {
        this.variable = "";
        this.where = new StringBuilder();
    }

    public void setVariable(String variable) {
        this.variable = variable;
    }

    public String getWhere() {
        return where.toString();
    }

    public void parse(String input) {
        input = input.replace("'", "''")
                .replace("|", " ")
                .replace("[", " ")
                .replace("]", " ")
                .replace("*", "%");

        List<String> tokens = tokenize(input);
        SpecialTypes notValue = SpecialTypes.INVALID;
        SpecialTypes orValue = SpecialTypes.AND;

        for (String token : tokens) {
            SpecialTypes specialType = convertToKey(token);

            switch (specialType) {
                case NOT:
                    notValue = specialType;
                    break;
                case OR:
                case AND:
                    orValue = specialType;
                    break;
                default:
                    addToSQL(token, notValue, orValue);
                    notValue = SpecialTypes.INVALID;
                    orValue = SpecialTypes.AND;
            }
        }
    }

    private List<String> tokenize(String input) {
        List<String> tokens = new ArrayList<>();
        StringBuilder token = new StringBuilder();
        boolean inQuotes = false;

        for (char c : input.toCharArray()) {
            switch (c) {
                case '"':
                    inQuotes = !inQuotes;
                    break;
                case ' ':
                    if (!inQuotes) {
                        tokens.add(token.toString());
                        token.setLength(0);
                    } else {
                        token.append(c);
                    }
                    break;
                default:
                    token.append(c);
            }
        }

        if (token.length() > 0) {
            tokens.add(token.toString());
        }

        return tokens;
    }

    private SpecialTypes convertToKey(String token) {
        token = token.toUpperCase();

        if ("NOT".equals(token) || "!".equals(token)) {
            return SpecialTypes.NOT;
        } else if ("OR".equals(token)) {
            return SpecialTypes.OR;
        } else if ("AND".equals(token)) {
            return SpecialTypes.AND;
        }

        return SpecialTypes.INVALID;
    }

    private String getKeyWordString(SpecialTypes keyword) {
        switch (keyword) {
            case NOT:
                return " NOT ";
            case AND:
                return " AND ";
            case OR:
                return " OR ";
            case INVALID:
                return " ";
        }

        return " ";
    }

    private boolean addToSQL(String token, SpecialTypes notValue, SpecialTypes orValue) {
        token = token.trim();
        String thisSQL;

        if (!token.contains("%") && !token.contains("?")) {
            thisSQL = String.format("%s%sLIKE '%%%s%%'", variable, getKeyWordString(notValue), token);
        } else {
            thisSQL = String.format("%s%sLIKE '%s%%'", variable, getKeyWordString(notValue), token);
        }

        if (where.length() > 0) {
            where.append(getKeyWordString(orValue)).append(thisSQL);
        } else {
            where.append(thisSQL);
        }

        return true;
    }

    public static void main(String[] args) {
        FormatSQL formatSQL = new FormatSQL();
        formatSQL.setVariable("column_name");
        formatSQL.parse("\"some text\" AND [another text] NOT |text| *partial");
        System.out.println(formatSQL.getWhere());
    }
}

public static void main(String[] args) {
    FormatSQL formatSQL = new FormatSQL();
    formatSQL.setVariable("column_name");
    formatSQL.parse("\"some text\" AND [another text] NOT |text| *partial");
    System.out.println(formatSQL.getWhere());
}
