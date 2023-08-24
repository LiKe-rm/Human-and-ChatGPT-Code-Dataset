package com.hust;

import weka.core.Instances;
import weka.core.converters.ConverterUtils.DataSource;
import weka.classifiers.trees.J48;
import weka.classifiers.Evaluation;
public class WekaModel {
    public static void main(String[] args) throws Exception {
        DataSource source = new DataSource("D:\\GPTC++\\arff\\6.20.arff");
        Instances data = source.getDataSet();

        data.setClassIndex(0);
        J48 tree = new J48();
        //tree.buildClassifier(data);
        Evaluation eval = new Evaluation(data);
        eval.crossValidateModel(tree, data, 10, new java.util.Random(1));

        System.out.println(eval.toSummaryString());

    }
}
