package com.hust.model;

import java.util.ArrayList;
import java.util.List;

public class Function {
    public String name;
    public String body;
    public int startLine;
    public int endLine;
    public List<Variable> params;
    public List<Variable> localVariables;
    public List<FunctionCall> functionCalls;

    public Function(String name, String body, int startLine, int endLine, List<Variable> params) {
        this.name = name;
        this.body = body;
        this.startLine = startLine;
        this.endLine = endLine;
        this.params = params;
        localVariables = new ArrayList<Variable>();
        functionCalls = new ArrayList<FunctionCall>();
    }

    public void addLocalVariable(Variable variable) {
        this.localVariables.add(variable);
    }
}
