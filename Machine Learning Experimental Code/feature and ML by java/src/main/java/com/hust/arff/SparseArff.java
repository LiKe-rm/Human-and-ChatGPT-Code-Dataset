package com.hust.arff;

import java.util.List;
import java.util.Map;

import com.hust.output.Result;
import com.hust.tools.Util;

public class SparseArff extends Arff {

    private int featuresIndex;

    private int getIndex() {
        featuresIndex += 1;
        return featuresIndex;
    }

    public SparseArff(List<Map<String, Result>> parseResultList) {
        super(parseResultList);
    }

    // write data label
    protected void writeDataAboutLabel(int authorId, String gender, String outputFileName) {
        // Util.writeFile(authorId + "," + gender + ",", outputFileName);
        Util.writeFile("{" + getIndex() + " " + authorId + "," + getIndex() + " " + gender + ",", outputFileName);
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
                    writeString.append(getIndex() + " " + wordUnigramTF.get(key) + ",");
                } else {
                    getIndex();
                }
            }
            Map<String, Double> IncludeTF = fileFeatures.get("IncludeFrequency").getDictResult();
            for (String key : IncludeList) {
                if (key.equals("XXXincludeNumberXXX") || key.equals("XXXimportNumberXXX")){
                    writeString.append(getIndex() + " " + IncludeTF.get(key) + ",");
                }else if (IncludeTF.containsKey(key)) {
                    writeString.append(getIndex() + " true,");
                } else {
                    writeString.append(getIndex() + " false,");
                }
            }
        }
        if (layout) {
            writeString.append(
                    getIndex() + " " + fileFeatures.get("ControlStructureNumber").getScalarResult() / fileLength + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("TernaryNumber").getScalarResult() / fileLength + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("TokenNumber").getScalarResult() / fileLength + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("CommentNumber").getScalarResult() / fileLength + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("LiteralNumber").getScalarResult() / fileLength + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("KeywordNumber").getScalarResult() / fileLength + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("FunctionNumber").getScalarResult() / fileLength + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("NestingDepth").getScalarResult() + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("BranchingFactor").getScalarResult() + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("AverageOfFunctionParamNumber").getScalarResult() + ",");
            writeString
                    .append(getIndex() + " " + fileFeatures.get("VarianceOfFunctionParamNumber").getScalarResult() + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("AverageOfLineLength").getScalarResult() + ",");
            writeString.append(getIndex() + " " + fileFeatures.get("VarianceOfLineLength").getScalarResult() + ",");
        }
        Util.writeFile(writeString.toString(), outputFileName);
    }

    // write data layout features
    @Override
    protected void writeDataAboutLayoutFeatures(Map<String, Result> fileFeatures, String outputFileName) {
        StringBuilder writeString = new StringBuilder();
        double fileLength = fileFeatures.get("FileLength").getScalarResult();
        writeString.append(getIndex() + " " + fileFeatures.get("TabNumber").getScalarResult() / fileLength + ",");
        writeString.append(getIndex() + " " + fileFeatures.get("SpaceNumber").getScalarResult() / fileLength + ",");
        writeString.append(getIndex() + " " + fileFeatures.get("EmptyLineNumber").getScalarResult() / fileLength + ",");
        writeString
                .append(getIndex() + " " + fileFeatures.get("WhiteSpaceNumber").getScalarResult() / fileLength + ",");
        if (fileFeatures.get("NewLineBeforeOpenBrance").getScalarResult() == 1) {
            writeString.append(getIndex() + " " + "true,");
        } else {
            writeString.append(getIndex() + " " + "false,");
        }
        if (fileFeatures.get("TabLeadLines").getScalarResult() == 1) {
            writeString.append(getIndex() + " " + "true,");
        } else {
            writeString.append(getIndex() + " " + "false,");
        }
        Util.writeFile(writeString.toString(), outputFileName);
    }

    // write data syntantic features
    @Override
    protected void writeDataAboutSyntanticFeatures(Map<String, Result> fileFeatures, String outputFileName, boolean layout, boolean wu) {
        StringBuilder writeString = new StringBuilder();
        if (layout) {
            writeString.append(getIndex() + " " + fileFeatures.get("MaxDepthASTNode").getScalarResult() + ",");
            Map<String, Double> typeNodeTF = Util
                    .calculateTermFrequency(fileFeatures.get("TypeNodeFrequency").getDictResult());
            for (String key : typeNodeList) {
                key = key.replace("'", "apostrophesymbol");
                key = key.replace("\n", "carriagereturn");
                if (typeNodeTF.containsKey(key)) {
                    writeString.append(getIndex() + " " + typeNodeTF.get(key) + ",");
                } else {
                    getIndex();
                }
            }
            writeString.append(getIndex() + " " + fileFeatures.get("TypeNodeAverageDepth").getScalarResult() + ",");
        }
        if (wu) {
            Map<String, Double> keywordTF = fileFeatures.get("KeywordTF").getDictResult();
            for (String key : keywordList) {
                key = key.replace("'", "apostrophesymbol");
                key = key.replace("\n", "carriagereturn");
                if (keywordTF.containsKey(key)) {
                    writeString.append(getIndex() + " " + keywordTF.get(key) + ",");
                } else {
                    getIndex();
                }
            }
        }
        if (layout){
            writeString.append(getIndex() + " " + fileFeatures.get("LeafNodeAverageDepth").getScalarResult() + ",");
        }
        if (wu) {
            Map<String, Double> leafNodeTF = Util
                    .calculateTermFrequency(fileFeatures.get("LeafNodeFrequency").getDictResult());
            for (String key : leafNodeList) {
                key = key.replace("'", "apostrophesymbol");
                key = key.replace("\n", "carriagereturn");
                if (leafNodeTF.containsKey(key)) {
                    writeString.append(getIndex() + " " + leafNodeTF.get(key) + ",");
                } else {
                    getIndex();
                }
            }
        }

        Util.writeFile(writeString.toString(), outputFileName);
    }

    @Override
    protected void flush() {
        featuresIndex = -1;
    }
}
