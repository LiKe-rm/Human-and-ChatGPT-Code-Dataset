package com.hust.parse;

import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.antlr.v4.runtime.*;

import org.antlr.v4.runtime.tree.ParseTreeWalker;

import com.hust.antlr.cpp.CPP14Lexer;
import com.hust.antlr.cpp.CPP14Parser;
import com.hust.antlr.java.JavaLexer;
import com.hust.antlr.java.JavaParser;
import com.hust.model.CppExtract;
import com.hust.model.Extract;
import com.hust.model.Function;
import com.hust.model.JavaExtract;
import com.hust.model.Variable;
import com.hust.output.DictResult;
import com.hust.output.Result;
import com.hust.output.ScalarResult;
import com.hust.tools.Util;
import org.w3c.dom.Text;

public class FileParser {
    Extract listener;
    Map<String, Result> fileFeatures;

    public FileParser() {
    }

    private int countMatchNumber(String code, String rule) {
        Pattern pattern = Pattern.compile(rule);
        Matcher matcher = pattern.matcher(code);
        int count = 0;
        while (matcher.find()) {
            count += 1;
        }
        return count;
    }

    @Deprecated
    protected void calculateUsage(String code) {
        String[] newRules = new String[] {
                "->", ".stream", "Instant.", "LocalDate.", "LocalTime.",
                "LocalDateTime.", "ZonedDateTime.", "Period.",
                "ZoneOffset.", "Clock.", "Optional.", "var", "copyOf(",
                "ByteArrayOutputStream(", ".transferTo", ".isBlank",
                ".strip", ".stripTrailing", ".stripLeading", ".repeat",
                "Pack200."
        };
        String[] oldRules = new String[] {
                "com.sun.awt.AWTUtilities", "sun.misc.Unsafe.defineClass",
                "Thread.destroy", "Thread.stop", "jdk.snmp"
        };
        String[] safetyRules = new String[] {
                "public final", "private final", "SecurityManager",
                "synchronized", "volatile", "ReentrantLock"
        };
        int newUsageNumber = 0, oldUsageNumber = 0, safetyUsageNumber = 0;
        for (String newRule : newRules) {
            newUsageNumber += countMatchNumber(code, newRule);
        }
        for (String oldRule : oldRules) {
            oldUsageNumber += countMatchNumber(code, oldRule);
        }
        for (String safetyRule : safetyRules) {
            safetyUsageNumber += countMatchNumber(code, safetyRule);
        }
        fileFeatures.put("NewUsageNumber", new ScalarResult(newUsageNumber));
        fileFeatures.put("OldUsageNumber", new ScalarResult(oldUsageNumber));
        fileFeatures.put("SafetyUsageNumber", new ScalarResult(safetyUsageNumber));
    }

    @Deprecated
    protected double calculateFunctionAverageLength() {
        if (listener.getFunctionList().size() == 0) {
            return 0;
        }
        int sum = 0;
        for (Function function : listener.getFunctionList()) {
            sum += function.endLine - function.startLine + 1;
        }
        return sum / listener.getFunctionList().size();
    }

    private void calculateWordUnigramFrequency(CommonTokenStream tokens, int type) {
        ArrayList<String> wordUnigrams = new ArrayList<>();
        Pattern pattern = Pattern.compile("\\b\\w+\\b"); // 匹配连续的字母
        StringBuilder comments = new StringBuilder();
        ArrayList<String> names = new ArrayList<>();

        Set<Integer> commentType = new HashSet<Integer>();
        Set<Integer> nameType = new HashSet<Integer>();
        if (type == 0) {
            commentType.add(JavaLexer.LINE_COMMENT);
            commentType.add(JavaLexer.COMMENT);
            commentType.add(JavaLexer.STRING_LITERAL);
            commentType.add(JavaLexer.TEXT_BLOCK);
            nameType.add(JavaLexer.IDENTIFIER);
        } else {
            commentType.add(CPP14Lexer.BlockComment);
            commentType.add(CPP14Lexer.LineComment);
            commentType.add(CPP14Lexer.StringLiteral);
            nameType.add(CPP14Lexer.Identifier);
        }
        List<Token> commentList = tokens.getTokens(0, tokens.size() - 1, commentType);
        Map<String, Double> wordUnigramTF = new HashMap<>();
        if (commentList != null && commentList.size() != 0) {
            for (Token token : commentList) {
                comments.append(token.getText());
            }

            Matcher matcher = pattern.matcher(comments.toString());

            while (matcher.find()) {
                String text = matcher.group();
                ArrayList<String> words = splitText(text);
                for (String word : words) {
                    wordUnigrams.add("comment:" + word);
                }
            }

            for (String word : wordUnigrams) {
                if (wordUnigramTF.containsKey(word)) {
                    wordUnigramTF.put(word, wordUnigramTF.get(word) + 1);
                } else {
                    wordUnigramTF.put(word, 1.0);
                }
            }
            wordUnigramTF.replaceAll((k, v) -> wordUnigramTF.get(k) / wordUnigrams.size());
        }


        List<Token> nameList = tokens.getTokens(0, tokens.size() - 1, nameType);
        Map<String, Double> nameUnigramTF = new HashMap<>();
        if (nameList != null && nameList.size() != 0) {
            for (Token token : nameList) {
                names.addAll(splitText(token.getText()));
            }

            for (String name : names) {
                name = "name:" + name;
                if (nameUnigramTF.containsKey(name)) {
                    nameUnigramTF.put(name, nameUnigramTF.get(name) + 1);
                } else {
                    nameUnigramTF.put(name, 1.0);
                }
            }
            nameUnigramTF.replaceAll((k, v) -> nameUnigramTF.get(k) / names.size());
        }

        wordUnigramTF.putAll(nameUnigramTF);
        fileFeatures.put("WordUnigramTF", new DictResult(wordUnigramTF));
    }

    private ArrayList<String> splitText(String text){
        String[] wordBlocks = text.split("_");
        ArrayList<String> wordsList = new ArrayList<String>();
        for (String wordBlock : wordBlocks) {
            String[] words = wordBlock.split("(?=[A-Z])");

            StringBuilder temp = new StringBuilder();
            for (String word : words) {
                if (word.length() == 1) {
                    temp.append(word);
                } else {
                    if (temp.length() > 0) {
                        wordsList.add(temp.toString().toLowerCase());
                        temp = new StringBuilder();
                    }
                    wordsList.add(word.toLowerCase());
                }
            }
            if (temp.length() > 0) {
                wordsList.add(temp.toString().toLowerCase());
            }
        }

        return wordsList;
    }

    private void calculateIncludeFrequency(String[] fileAllLines, int type) {
        Map<String, Double> includeList = new HashMap<>();
        int count = 0;
        if (type == 0) {
            for (String line : fileAllLines) {
                if (line.startsWith("import")) {
                    count++;
                    // 去掉import和分号，如果后面有注释，去掉注释
                    String word = line.split(";")[0].substring(7).strip();
                    if (includeList.containsKey(word)) {
                        includeList.put(word, includeList.get(word) + 1);
                    }else {
                        includeList.put(word, 1.0);
                    }
                }
            }
            includeList.put("XXXimportNumberXXX", (double) count);
        } else {
            for (String line : fileAllLines) {
                if (line.startsWith("#include")) {
                    count++;
                    String word = line.split("//")[0].split("/\\*")[0].substring(8).strip();
                    if (includeList.containsKey(word)) {
                        includeList.put(word, includeList.get(word) + 1);
                    }else {
                        includeList.put(word, 1.0);
                    }
                }
            }
            includeList.put("XXXincludeNumberXXX", (double) count);
        }

        fileFeatures.put("IncludeFrequency", new DictResult(includeList));
    }
    private void calculateControlNumber() {
        fileFeatures.put("ControlStructureNumber", new ScalarResult(listener.getControlStructureNumber()));
    }

    private void calculateTernaryNumber() {
        fileFeatures.put("TernaryNumber", new ScalarResult(listener.getTernaryOperatorNumber()));
    }

    private void calculateTokenNumber(String fileData) {
        fileFeatures.put("TokenNumber",
                new ScalarResult(fileData.split("[*;\\{\\}\\[\\]()+=\\-&/|%!?:,<>~`\\s\"]").length));
    }

    private void calculateCommentNumber(CommonTokenStream tokens, int type) {
        Set<Integer> commentType = new HashSet<Integer>();
        if (type == 0) {
            commentType.add(JavaLexer.LINE_COMMENT);
            commentType.add(JavaLexer.COMMENT);
        } else {
            commentType.add(CPP14Lexer.BlockComment);
            commentType.add(CPP14Lexer.LineComment);
        }
        List<Token> commentList = tokens.getTokens(0, tokens.size() - 1, commentType);
        fileFeatures.put("CommentNumber", new ScalarResult(commentList == null ? 0 : commentList.size()));
    }

    private void calculateLiteralNumber() {
        fileFeatures.put("LiteralNumber", new ScalarResult(listener.getLiteralNumber()));
    }

    private void calculateFunctionNumber() {
        fileFeatures.put("FunctionNumber", new ScalarResult(listener.getFunctionList().size()));
    }

    // calculate variable 方差
    private double calculateVariable(List<Double> list) {
        double average = 0, variance = 0;
        for (Double number : list) {
            average += number;
        }
        average = average / list.size();
        for (Double number : list) {
            variance += (Math.pow((number - average), 2));
        }
        variance = variance / list.size();
        return variance;
    }

    @Deprecated
    protected double calculateVariableLocationVariance() {
        if (listener.getFunctionList().size() == 0) {
            return 0;
        }
        List<Double> variableRelativeLocation = new ArrayList<>();
        for (Function function : listener.getFunctionList()) {
            int functionStartLine = function.startLine;
            int functionLength = function.endLine - function.startLine + 1;
            for (Variable variable : function.localVariables) {
                variableRelativeLocation.add((double) ((variable.line - functionStartLine + 1) / functionLength));
            }
        }
        return calculateVariable(variableRelativeLocation);
    }

    private void calculateAverageAndVarianceOfFunctionParamNumber() {
        if (listener.getFunctionList().size() == 0) {
            fileFeatures.put("AverageOfFunctionParamNumber", new ScalarResult(0));
            fileFeatures.put("VarianceOfFunctionParamNumber",
                    new ScalarResult(0));
            return;
        }
        int[] functionParamNumber = new int[listener.getFunctionList().size()];
        for (int i = 0; i < listener.getFunctionList().size(); i++) {
            functionParamNumber[i] = listener.getFunctionList().get(i).params.size();
        }
        fileFeatures.put("AverageOfFunctionParamNumber", new ScalarResult(Util.mean(functionParamNumber)));
        fileFeatures.put("VarianceOfFunctionParamNumber",
                new ScalarResult(Util.standardDeviation(functionParamNumber)));
    }

    private void calculateAverageAndVarianceOfLineLength(String[] fileAllLines) {
        if (fileAllLines.length == 0) {
            fileFeatures.put("AverageOfLineLength", new ScalarResult(0));
            fileFeatures.put("VarianceOfLineLength", new ScalarResult(0));
            return;
        }
        int[] lineLength = new int[fileAllLines.length];
        for (int i = 0; i < fileAllLines.length; i++) {
            lineLength[i] = fileAllLines[i].length();
        }
        fileFeatures.put("AverageOfLineLength", new ScalarResult(Util.mean(lineLength)));
        fileFeatures.put("VarianceOfLineLength", new ScalarResult(Util.standardDeviation(lineLength)));
    }

    private void calculateNestingDepth() {
        fileFeatures.put("NestingDepth", new ScalarResult(listener.getNestingDepth()));
    }

    private void calculateBranchingFactor() {
        double branchingFactor = 0;
        for (int branchingNumber : listener.getBranchingNumberList()) {
            branchingFactor += branchingNumber;
        }
        branchingFactor /= listener.getBranchingNumberList().size();
        fileFeatures.put("BranchingFactor", new ScalarResult(branchingFactor));
    }

    private void calcluateWhiteSpaceChar(String fileData) {
        int whiteSpaceNumber = 0;
        int tabNumber = 0;
        int spaceNumber = 0;
        for (int i = 0; i < fileData.length(); i++) {
            if (fileData.charAt(i) == '\t') {
                tabNumber += 1;
                whiteSpaceNumber += 1;
            } else if (fileData.charAt(i) == ' ') {
                spaceNumber += 1;
                whiteSpaceNumber += 1;
            } else if (Character.toString(fileData.charAt(i)).matches("\\s")) {
                whiteSpaceNumber += 1;
            }
        }
        fileFeatures.put("TabNumber", new ScalarResult(tabNumber));
        fileFeatures.put("SpaceNumber", new ScalarResult(spaceNumber));
        fileFeatures.put("WhiteSpaceNumber", new ScalarResult(whiteSpaceNumber));
    }

    private void calcluateTabOrSpaceLeadLinesAndEmptyLineNumber(String[] fileAllLines) {
        int tabLeadNumber = 0;
        int spaceLeadNumber = 0;
        int emptyLineNumber = 0;
        for (String line : fileAllLines) {
            if (line.length() == 0) {
                continue;
            }
            if (line.charAt(0) == '\t') {
                tabLeadNumber += 1;
            } else if (line.charAt(0) == ' ') {
                spaceLeadNumber += 1;
            }
            if (line.matches("\\s*")) {
                emptyLineNumber += 1;
            }
        }
        fileFeatures.put("TabLeadLines", new ScalarResult(tabLeadNumber > spaceLeadNumber ? 1 : 0));
        fileFeatures.put("EmptyLineNumber", new ScalarResult(emptyLineNumber));
    }

    private void calculateNewLineOrOnLineBeforeOpenBrance(CommonTokenStream tokens) {
        int newLineNumber = 0;
        int onLineNumber = 0;
        for (Token token : tokens.getTokens()) {
            if (token.getType() != JavaLexer.LBRACE) {
                continue;
            }
            boolean newLine = false;
            int tokenIndex = token.getTokenIndex();
            for (int i = tokenIndex - 1; i >= 0; i--) {
                int channel = tokens.get(i).getChannel();
                if (channel == JavaLexer.DEFAULT_TOKEN_CHANNEL) {
                    if (newLine) {
                        newLineNumber += 1;
                    } else {
                        onLineNumber += 1;
                    }
                } else if (channel == JavaLexer.SPACE) {
                    newLine = true;
                }
            }
        }
        fileFeatures.put("NewLineBeforeOpenBrance", new ScalarResult(newLineNumber > onLineNumber ? 1 : 0));
    }

    private void calculateTypeNodeFeature() {
        double typeNodeAverageDepth = 0;
        for (int depth : listener.getTypeNodeDepth()) {
            typeNodeAverageDepth += depth;
        }
        typeNodeAverageDepth /= listener.getTypeNodeDepth().size();
        fileFeatures.put("TypeNodeFrequency", new DictResult(listener.getTypeNodeFrequency()));
        fileFeatures.put("TypeNodeAverageDepth", new ScalarResult(typeNodeAverageDepth));
    }

    private void calculateLeafNodeFeatureAndMaxDepthASTNode() {
        double leafNodeAverageDepth = 0;
        int MaxDepthASTNode = 0;
        for (int depth : listener.getLeafNodeDepth()) {
            if (depth > MaxDepthASTNode) {
                MaxDepthASTNode = depth;
            }
            leafNodeAverageDepth += depth;
        }
        leafNodeAverageDepth /= listener.getLeafNodeDepth().size();
        fileFeatures.put("LeafNodeFrequency", new DictResult(listener.getLeafNodeFrequency()));
        fileFeatures.put("LeafNodeAverageDepth", new ScalarResult(leafNodeAverageDepth));
        fileFeatures.put("MaxDepthASTNode", new ScalarResult(MaxDepthASTNode));
    }

    private void calculateKeywordNumberAndFrequency() {
        int keywordNumber = 0;
        for (Double number : listener.getKeywordFrequency().values()) {
            keywordNumber += number;
        }
        for (String keyword : listener.getKeywordFrequency().keySet()) {
            listener.getKeywordFrequency().put(keyword, listener.getKeywordFrequency().get(keyword) / keywordNumber);
        }
        fileFeatures.put("KeywordNumber", new ScalarResult(keywordNumber));
        fileFeatures.put("KeywordTF", new DictResult(listener.getKeywordFrequency()));
    }

    private void extractLexicalFeature(String fileData, String[] fileAllLines, CommonTokenStream tokens, int type) {
        calculateWordUnigramFrequency(tokens, type);
        calculateIncludeFrequency(fileAllLines, type);
        calculateControlNumber();
        calculateTernaryNumber();
        calculateTokenNumber(fileData);
        calculateCommentNumber(tokens, type);
        calculateLiteralNumber();
        calculateFunctionNumber();
        calculateNestingDepth();
        calculateBranchingFactor();
        calculateAverageAndVarianceOfFunctionParamNumber();
        calculateAverageAndVarianceOfLineLength(fileAllLines);
    }


    private void extractLayoutFeature(String fileData, String[] fileAllLines, CommonTokenStream tokens) {
        calcluateTabOrSpaceLeadLinesAndEmptyLineNumber(fileAllLines);
        calcluateWhiteSpaceChar(fileData);
        calculateNewLineOrOnLineBeforeOpenBrance(tokens);
    }

    private void extractSyntacticFeature() {
        calculateLeafNodeFeatureAndMaxDepthASTNode();
        calculateTypeNodeFeature();
        calculateKeywordNumberAndFrequency();
    }

    private CommonTokenStream extractOriginFeatureForJava(String fileData) {
        CharStream charStream = CharStreams.fromString(fileData);
        JavaLexer lexer = new JavaLexer(charStream);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        JavaParser parser = new JavaParser(tokens);
        ParseTreeWalker walker = new ParseTreeWalker();
        listener = new JavaExtract();
        walker.walk(listener, parser.compilationUnit());
        return tokens;
    }

    private CommonTokenStream extractOriginFeatureForCpp(String fileData) {
        CharStream charStream = CharStreams.fromString(fileData);
        CPP14Lexer lexer = new CPP14Lexer(charStream);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        CPP14Parser parser = new CPP14Parser(tokens);
        ParseTreeWalker walker = new ParseTreeWalker();
        listener = new CppExtract();
        walker.walk(listener, parser.translationUnit());
        return tokens;
    }

    private CommonTokenStream extractOriginalFeature(String fileData, String fileName) {
        String[] split = fileName.split("\\.");
        String suffix = split[split.length - 1];
        CommonTokenStream tokens = switch (suffix) {
            case "cpp", "c++" -> extractOriginFeatureForCpp(fileData);
            default -> extractOriginFeatureForJava(fileData);
        };
        return tokens;
    }

    private String[] readFileLines(String fileName) {
        String[] fileAllLines = new String[] {};
        try {
            fileAllLines = Util.readFileAllLines(fileName);
        } catch (IOException e) {
            System.out.println(e);
        }
        return fileAllLines;
    }

    public Map<String, Result> parseFile(String fileName) {
        int type;
        if (fileName.endsWith(".java")) {
            type = 0;
        } else if (fileName.endsWith(".cpp") || fileName.endsWith(".c++")) {
            type = 1;
        } else {
            return null;
        }
        String[] fileAllLines = readFileLines(fileName);
        String fileData = String.join("\n", fileAllLines);

        fileFeatures = new HashMap<String, Result>();
        fileFeatures.put("FileLength", new ScalarResult(fileData.length()));
        fileFeatures.put("FileLineNumber", new ScalarResult(fileAllLines.length));

        CommonTokenStream tokens = extractOriginalFeature(fileData, fileName);
        extractLexicalFeature(fileData, fileAllLines, tokens, type);
        extractLayoutFeature(fileData, fileAllLines, tokens);
        extractSyntacticFeature();
        return fileFeatures;
    }

    public static void main(String[] args) {
        FileParser fileParser = new FileParser();
        CommonTokenStream tokens = fileParser.extractOriginFeatureForCpp("D:\\GPTC++\\3.31raw\\authors12_81Vm3_RakMagic_RakMagic_raknet_AsynchronousFileIO.cpp");
        for (Token token : tokens.getTokens()) {
            System.out.println(token.getText()+" "+token.getType());
        }

        //        Map<String, Result> f = fileParser.parseFile("D:\\GPTC++\\3.31raw\\authors12_81Vm3_RakMagic_RakMagic_raknet_AsynchronousFileIO.cpp");
//        for (String key : f.get("WordUnigramTF").getDictResult().keySet()) {
//            System.out.println(key + " " + f.get("WordUnigramTF").getDictResult().get(key)+"\n");
//        }
//        for (String key : f.get("LeafNodeFrequency").getDictResult().keySet()) {
//            System.out.println(key + " " + f.get("LeafNodeFrequency").getDictResult().get(key)+"\n");
//        }
    }

}
