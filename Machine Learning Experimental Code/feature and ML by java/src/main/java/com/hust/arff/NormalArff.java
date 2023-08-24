package com.hust.arff;

import java.util.List;
import java.util.Map;

import com.hust.output.Result;
import com.hust.tools.Util;

public class NormalArff extends Arff {

    public NormalArff(List<Map<String, Result>> parseResultList) {
        super(parseResultList);
    }

    // write data label
    protected void writeDataAboutLabel(int authorId, String gender, String outputFileName) {
        Util.writeFile(authorId + "," + gender + ",", outputFileName);
    }

    // write data lexical features
    @Override
    protected void writeDataAboutLexicalFeatures(Map<String, Result> fileFeatures, String outputFileName, boolean wu, boolean layout) {
        StringBuilder writeString = new StringBuilder();
        double fileLength = fileFeatures.get("FileLength").getScalarResult();
        if (wu) {
            Map<String, Double> wordUnigramTF = fileFeatures.get("WordUnigramTF").getDictResult();
            for (String key : wordUnigramList) {
                key = key.replace("'", "apostrophesymbol");
                key = key.replace("\n", "carriagereturn");
                if (wordUnigramTF.containsKey(key)) {
                    writeString.append(wordUnigramTF.get(key) + ",");
                } else {
                    writeString.append("0,");
                }
            }
        }
        if (layout) {
            writeString.append(fileFeatures.get("ControlStructureNumber").getScalarResult() / fileLength + ",");
            writeString.append(fileFeatures.get("TernaryNumber").getScalarResult() / fileLength + ",");
            writeString.append(fileFeatures.get("TokenNumber").getScalarResult() / fileLength + ",");
            writeString.append(fileFeatures.get("CommentNumber").getScalarResult() / fileLength + ",");
            writeString.append(fileFeatures.get("LiteralNumber").getScalarResult() / fileLength + ",");
            writeString.append(fileFeatures.get("KeywordNumber").getScalarResult() / fileLength + ",");
            writeString.append(fileFeatures.get("FunctionNumber").getScalarResult() / fileLength + ",");
            writeString.append(fileFeatures.get("NestingDepth").getScalarResult() + ",");
            writeString.append(fileFeatures.get("BranchingFactor").getScalarResult() + ",");
            writeString.append(fileFeatures.get("AverageOfFunctionParamNumber").getScalarResult() + ",");
            writeString.append(fileFeatures.get("VarianceOfFunctionParamNumber").getScalarResult() + ",");
            writeString.append(fileFeatures.get("AverageOfLineLength").getScalarResult() + ",");
            writeString.append(fileFeatures.get("VarianceOfLineLength").getScalarResult() + ",");
        }
        Util.writeFile(writeString.toString(), outputFileName);
    }

    // write data layout features
    @Override
    protected void writeDataAboutLayoutFeatures(Map<String, Result> fileFeatures, String outputFileName) {
        StringBuilder writeString = new StringBuilder();
        double fileLength = fileFeatures.get("FileLength").getScalarResult();
        writeString.append(fileFeatures.get("TabNumber").getScalarResult() / fileLength + ",");
        writeString.append(fileFeatures.get("SpaceNumber").getScalarResult() / fileLength + ",");
        writeString.append(fileFeatures.get("EmptyLineNumber").getScalarResult() / fileLength + ",");
        writeString.append(fileFeatures.get("WhiteSpaceNumber").getScalarResult() / fileLength + ",");
        if (fileFeatures.get("NewLineBeforeOpenBrance").getScalarResult() == 1) {
            writeString.append("true,");
        } else {
            writeString.append("false,");
        }
        if (fileFeatures.get("TabLeadLines").getScalarResult() == 1) {
            writeString.append("true,");
        } else {
            writeString.append("false,");
        }
        Util.writeFile(writeString.toString(), outputFileName);
    }

    // write data syntantic features
    @Override
    protected void writeDataAboutSyntanticFeatures(Map<String, Result> fileFeatures, String outputFileName, boolean layout, boolean wu) {
        StringBuilder writeString = new StringBuilder();
        if (layout) {
            writeString.append(fileFeatures.get("MaxDepthASTNode").getScalarResult() + ",");
            Map<String, Double> typeNodeTF = Util.calculateTermFrequency(
                    fileFeatures.get("TypeNodeFrequency").getDictResult());
            for (String key : typeNodeList) {
                key = key.replace("'", "apostrophesymbol");
                key = key.replace("\n", "carriagereturn");
                if (typeNodeTF.containsKey(key)) {
                    writeString.append(typeNodeTF.get(key) + ",");
                } else {
                    writeString.append("0,");
                }
            }
            writeString.append(fileFeatures.get("TypeNodeAverageDepth").getScalarResult() + ",");
            Map<String, Double> keywordTF = fileFeatures.get("KeywordTF").getDictResult();
            for (String key : keywordList) {
                key = key.replace("'", "apostrophesymbol");
                key = key.replace("\n", "carriagereturn");
                if (keywordTF.containsKey(key)) {
                    writeString.append(keywordTF.get(key) + ",");
                } else {
                    writeString.append("0,");
                }
            }

            writeString.append(fileFeatures.get("LeafNodeAverageDepth").getScalarResult() + ",");
        }

        Map<String, Double> leafNodeTF = Util
                .calculateTermFrequency(fileFeatures.get("LeafNodeFrequency").getDictResult());
        for (String key : leafNodeList) {
            key = key.replace("'", "apostrophesymbol");
            key = key.replace("\n", "carriagereturn");
            if (leafNodeTF.containsKey(key)) {
                writeString.append(leafNodeTF.get(key) + ",");
            } else {
                writeString.append("0,");
            }
        }
        Util.writeFile(writeString.toString(), outputFileName);
    }

    @Override
    protected void flush() {
    }

    public static void main(String[] args) {
        float a = 22;
        float b = 25;
        float c = a / b;
        Double d = Double.valueOf(c);
        System.out.println(c + "-\n");
        System.out.println(d + "-\n");
    }
}
