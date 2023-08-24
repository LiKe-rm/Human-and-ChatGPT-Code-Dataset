package com.hust.model;

import java.util.List;
import java.util.Map;

import org.antlr.v4.runtime.tree.ParseTreeListener;

public interface Extract extends ParseTreeListener {
    public List<Function> getFunctionList();

    public int getTernaryOperatorNumber();

    public int getControlStructureNumber();

    public int getLiteralNumber();

    public int getNestingDepth();

    public List<Integer> getBranchingNumberList();

    public List<Integer> getTypeNodeDepth();

    public List<Integer> getLeafNodeDepth();

    public Map<String, Double> getTypeNodeFrequency();

    public Map<String, Double> getLeafNodeFrequency();

    public Map<String, Double> getKeywordFrequency();
}
