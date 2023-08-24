package com.hust;

import java.io.*;
import java.util.*;

import com.hust.arff.Arff;
import com.hust.arff.NormalArff;
import com.hust.arff.SparseArff;
import com.hust.output.Result;
import com.hust.parse.FileParser;
import com.hust.tools.Util;

public class Main {

    public static List<Map<String, Result>> parseFilePathList(List<File> filePathList) {
        List<Map<String, Result>> parseResultList = new ArrayList<>();
        FileParser fileParser = new FileParser();
        for (File file : filePathList) {
            System.out.println("-------- parse file: " + file.getPath() + " --------\n");
            parseResultList.add(fileParser.parseFile(file.getAbsolutePath()));
        }
        return parseResultList;
    }

    public static Map<String, Integer> extractAuthorId(List<File> filePathList) {
        Map<String, Integer> authorId = new HashMap<>();
        for (File file : filePathList) {
            String authorName = file.getPath().split("/|\\\\")[6];
            if (!authorId.containsKey(authorName)) {
                authorId.put(authorName, authorId.size() + 1);
            }
        }
        return authorId;
    }

    public static void main(String[] args) {

        long start = System.currentTimeMillis();

        List<File> rawCodes = new ArrayList<>();
        File dir = new File("D:\\GPTC++\\3.31raw");
        File[] files = dir.listFiles();
        Collections.addAll(rawCodes, files);

        List<File> gptCodes = new ArrayList<>();
        File dir1 = new File("D:\\GPTC++\\3.31gpt");
        File[] files1 = dir1.listFiles();
        Collections.addAll(gptCodes, files1);

        List<File> allFilePathList = new ArrayList<>(rawCodes);
        allFilePathList.addAll(gptCodes);
        List<Map<String, Result>> parseResultList = parseFilePathList(allFilePathList);
        String outputFileName = "D:\\GPTC++\\arff\\6.20.arff";

        Arff arff = new SparseArff(parseResultList);
        for (int i = 0; i < rawCodes.size(); i++) {
            System.out.println("-------- save file: " + rawCodes.get(i).getPath() + " --------\n");
            Map<String, Result> fileFeatures = parseResultList.get(i);
            arff.writeFile(1, "0", fileFeatures, outputFileName, true, true, true);
        }

        for (int i = 0; i < gptCodes.size(); i++) {
            System.out.println("-------- save file: " + gptCodes.get(i).getPath() + " --------\n");
            Map<String, Result> fileFeatures = parseResultList.get(i+rawCodes.size());
            arff.writeFile(2, "0", fileFeatures, outputFileName, true, true, true);
        }

        System.out.println("time cost : ");
        System.out.println(System.currentTimeMillis() - start);
    }
}
